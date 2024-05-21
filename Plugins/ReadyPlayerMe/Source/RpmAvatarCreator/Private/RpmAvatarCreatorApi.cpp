// Copyright © 2023++ Ready Player Me


#include "RpmAvatarCreatorApi.h"

#include "ReadyPlayerMeSettings.h"
#include "Downloaders/RpmPartnerAssetDownloader.h"
#include "Downloaders/RpmColorDownloader.h"
#include "Downloaders/RpmAuthManager.h"
#include "Downloaders/RpmAvatarRequestHandler.h"
#include "Requests/RequestFactory.h"
#include "Downloaders/RpmUserAvatarDownloader.h"
#include "Downloaders/RpmAvatarTemplateDownloader.h"
#include "Downloaders/RpmImageDownloader.h"
#include "Engine/SkeletalMesh.h"

URpmAvatarCreatorApi::URpmAvatarCreatorApi()
	: TargetSkeleton(nullptr)
	, BodyType(EAvatarBodyType::FullBody)
	, ImageDownloader(nullptr)
	, AvatarRequestHandler(nullptr)
{
}

void URpmAvatarCreatorApi::Initialize()
{
	RequestFactory = MakeShared<FRequestFactory>();
	AuthManager = MakeShared<FRpmAuthManager>(RequestFactory);
	AuthManager->BindTokenRefreshDelegate();
	ColorDownloader = MakeShared<FRpmColorDownloader>(RequestFactory);
	AssetDownloader = MakeShared<FRpmPartnerAssetDownloader>(RequestFactory, BodyType);
	AvatarTemplateDownloader = MakeShared<FRpmAvatarTemplateDownloader>(RequestFactory);
	UserAvatarDownloader = MakeShared<FRpmUserAvatarDownloader>(RequestFactory);
	ImageDownloader = NewObject<URpmImageDownloader>();
	ImageDownloader->SetRequestFactory(RequestFactory);
	AvatarRequestHandler = NewObject<URpmAvatarRequestHandler>();
	AvatarRequestHandler->SetRequestFactory(RequestFactory);
	AvatarRequestHandler->SetUserAvatarDownloader(UserAvatarDownloader);
	AvatarRequestHandler->ImageDownloader = ImageDownloader;

	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (!IsValid(Settings) || Settings->Subdomain.IsEmpty())
	{
		UE_LOG(LogRpmAvatarCreator, Error, TEXT("Application subdomain is required for the avatar creator. Find the subdomain of your application from the Ready Player Me studio website, and set it in your project settings under the ReadyPlayerMe > Subdomain"));
	}
	if (!IsValid(Settings) || Settings->AppId.IsEmpty())
	{
		UE_LOG(LogRpmAvatarCreator, Error, TEXT("AppId is required for the avatar creator. Find the AppId of your application from the Ready Player Me studio website, and set it in your project settings under the ReadyPlayerMe > AppId"));
	}
	AvatarProperties.Partner = Settings->Subdomain;
	RequestFactory->SetAppId(Settings->AppId);
	RequestFactory->SetSubdomain(Settings->Subdomain);
	AuthManager->LoadUserData();
}

void URpmAvatarCreatorApi::SetPreviewDownloadedDelegate(const FPreviewDownloadCompleted& PreviewDownloaded)
{
	AvatarRequestHandler->OnPreviewDownloaded = PreviewDownloaded;
}

void URpmAvatarCreatorApi::SetSessionExpiredDelegate(const FSessionExpired& SessionExpired)
{
	RequestFactory->SetSessionExpiredDelegate(SessionExpired);
}

FRpmUserData URpmAvatarCreatorApi::GetUserData() const
{
	return AuthManager->GetUserData();
}

void URpmAvatarCreatorApi::AuthAnonymous(const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	AuthManager->AuthAnonymous(Completed, Failed);
}

void URpmAvatarCreatorApi::AuthStart(const FString& Email, bool bIsTypeCode, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	AuthManager->AuthStart(Email, bIsTypeCode, Completed, Failed);
}

void URpmAvatarCreatorApi::ConfirmActivationCode(const FString& Code, const FAuthenticationCompleted& Completed, const FAvatarCreatorFailed& Failed)
{
	AuthManager->ConfirmActivationCode(Code, Completed, Failed);
}

void URpmAvatarCreatorApi::LogOut()
{
	RequestFactory->CancelRequests();
	AuthManager->Logout();
	AssetDownloader->ClearAssets();
	const FString Partner = AvatarProperties.Partner;
	AvatarProperties = {};
	AvatarProperties.Partner = Partner;
}

void URpmAvatarCreatorApi::PropertiesDownloaded(bool bSuccess, ERpmAvatarCreatorError Error)
{
	if (!bSuccess)
	{
		ExecuteEditorReadyCallback(false, Error);
		return;
	}

	AvatarProperties = AvatarRequestHandler->GetAvatarProperties();
	AvatarRequestHandler->Mesh = nullptr;
	if (AvatarProperties.BodyType != BodyType)
	{
		ExecuteEditorReadyCallback(false, Error);
		return;
	}

	AssetDownloader->GetPartnerAssetsDownloadCallback().BindUObject(this, &URpmAvatarCreatorApi::ExecuteEditorReadyCallback, ERpmAvatarCreatorError::AssetDownloadFailure);
	AssetDownloader->DownloadAssets();
	ColorDownloader->GetCompleteCallback().BindUObject(this, &URpmAvatarCreatorApi::ExecuteEditorReadyCallback, ERpmAvatarCreatorError::ColorDownloadFailure);
	ColorDownloader->DownloadColors(AvatarProperties.Id);
	AvatarRequestHandler->GetAvatarPreviewDownloadedCallback().BindUObject(this, &URpmAvatarCreatorApi::ExecuteEditorReadyCallback, ERpmAvatarCreatorError::AvatarPreviewFailure);
	AvatarRequestHandler->DownloadModel(TargetSkeleton);
}

void URpmAvatarCreatorApi::PrepareEditor(const FAvatarEditorReady& EditorReady, const FAvatarCreatorFailed& Failed)
{
	OnEditorReady = EditorReady;
	OnEditorFailed = Failed;

	const ERpmAvatarCreatorError Error = !AvatarProperties.Id.IsEmpty() ?
		ERpmAvatarCreatorError::MetadataDownloadFailure : ERpmAvatarCreatorError::AvatarCreateFailure;
	AvatarRequestHandler->GetAvatarPropertiesDownloadedCallback().BindUObject(this, &URpmAvatarCreatorApi::PropertiesDownloaded, Error);
	if (AvatarProperties.Id.IsEmpty())
	{
		AvatarProperties.BodyType = BodyType;
		AvatarRequestHandler->CreateAvatar(AvatarProperties, SelectedAvatarTemplateId);
	}
	else
	{
		AvatarRequestHandler->DownloadAvatarProperties(AvatarProperties.Id);
	}
}

void URpmAvatarCreatorApi::ExecuteEditorReadyCallback(bool bSuccess, ERpmAvatarCreatorError Error)
{
	if (!OnEditorReady.IsBound())
	{
		return;
	}
	if (!bSuccess)
	{
		(void)OnEditorFailed.ExecuteIfBound(Error);
		OnEditorFailed.Clear();
		OnEditorReady.Clear();
		RequestFactory->CancelRequests();
		return;
	}
	if (AssetDownloader->AreAssetsReady() && IsValid(AvatarRequestHandler->Mesh) && ColorDownloader->GetColors().Num() > 0)
	{
		(void)OnEditorReady.ExecuteIfBound();
		(void)AvatarRequestHandler->OnPreviewDownloaded.ExecuteIfBound(AvatarRequestHandler->Mesh);
		OnEditorFailed.Clear();
		OnEditorReady.Clear();
	}
}

void URpmAvatarCreatorApi::DownloadAvatarTemplates(const FAvatarTemplatesDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed)
{
	AvatarTemplateDownloader->DownloadTemplates(DownloadCompleted, Failed);
}

void URpmAvatarCreatorApi::DownloadUserAvatars(const FUserAvatarsDownloadCompleted& DownloadCompleted, const FAvatarCreatorFailed& Failed)
{
	UserAvatarDownloader->DownloadUserAvatars(DownloadCompleted, Failed);
}

void URpmAvatarCreatorApi::UpdateAvatarAsset(ERpmPartnerAssetType AssetType, const FString& AssetId)
{
	AvatarRequestHandler->UpdateAvatar(AssetType, AssetId);
}

void URpmAvatarCreatorApi::UpdateAvatarColor(ERpmPartnerAssetColor AssetColor, int32 ColorIndex)
{
	AvatarRequestHandler->UpdateAvatar(AssetColor, ColorIndex);
}

void URpmAvatarCreatorApi::PrecompileAvatar(ERpmPartnerAssetType AssetType)
{
	AvatarRequestHandler->Precompile(AssetType, AssetDownloader->GetFilteredAssets(AvatarProperties.Gender));
}

void URpmAvatarCreatorApi::SaveAvatar(const FAvatarSaveCompleted& AvatarSaveCompleted, const FAvatarCreatorFailed& Failed)
{
	AvatarRequestHandler->SaveAvatar(AvatarSaveCompleted, Failed);
}

void URpmAvatarCreatorApi::DeleteAvatar(const FString& AvatarId, bool bIsDraft, const FAvatarDeleteCompleted& AvatarDeleteCompleted, const FAvatarCreatorFailed& Failed)
{
	AvatarRequestHandler->DeleteAvatar(AvatarId, bIsDraft, AvatarDeleteCompleted, Failed);
}

void URpmAvatarCreatorApi::UpdateLockedAssets(const FUpdateLockedAssetsCompleted& UpdateLockedAssetsCompleted, const FAvatarCreatorFailed& Failed)
{
	
}

void URpmAvatarCreatorApi::DownloadImage(const FString& Url, int32 Size, const FImageDownloadCompleted& DownloadCompleted)
{
	return ImageDownloader->DownloadImage(Url, Size, DownloadCompleted);
}

TArray<FRpmPartnerAsset> URpmAvatarCreatorApi::GetFilteredPartnerAssets() const
{
	return AssetDownloader->GetFilteredAssets(AvatarProperties.Gender);
}

TArray<FRpmColorPalette> URpmAvatarCreatorApi::GetColorPalettes() const
{
	return ColorDownloader->GetColors();
}

TArray<FRpmAvatarTemplate> URpmAvatarCreatorApi::GetAvatarTemplates() const
{
	return AvatarTemplateDownloader->GetAvatarTemplates();
}

void URpmAvatarCreatorApi::BeginDestroy()
{
	if (RequestFactory)
	{
		RequestFactory->CancelRequests();
	}
	Super::BeginDestroy();
}
