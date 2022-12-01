// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeAvatarLoader.h"

#include "Utils/ReadyPlayerMeGlTFConfigCreator.h"
#include "Utils/ReadyPlayerMeMetadataExtractor.h"
#include "Utils/ReadyPlayerMeRequestCreator.h"
#include "Utils/ReadyPlayerMeUrlConvertor.h"
#include "Utils/ReadyPlayerMePluginInfo.h"
#include "Storage/ReadyPlayerMeAvatarCacheHandler.h"

#include "Components/SkeletalMeshComponent.h"
#include "glTFRuntimeFunctionLibrary.h"

static const FString HEADER_LAST_MODIFIED = "Last-Modified";
constexpr float METADATA_REQUEST_TIMEOUT = 20.f;
constexpr float AVATAR_REQUEST_TIMEOUT = 60.f;

static const FString HEADER_RPM_SOURCE = "RPM-Source";
static const FString HEADER_RPM_SDK_VERSION = "RPM-SDK-Version";
#if WITH_EDITOR
static const FString UNREAL_SOURCE = "unreal-editor";
#else
static const FString UNREAL_SOURCE = "unreal-runtime";
#endif

namespace
{
	template <typename RequestPtr>
	void AddRPMHeaders(RequestPtr HttpRequest)
	{
		HttpRequest->SetHeader(HEADER_RPM_SOURCE, UNREAL_SOURCE);
		HttpRequest->SetHeader(HEADER_RPM_SDK_VERSION, FReadyPlayerMePluginInfo::GetPluginVersion());
	}
}

UReadyPlayerMeAvatarLoader::UReadyPlayerMeAvatarLoader()
	: GlTFRuntimeAsset(nullptr)
	, bIsTryingToUpdate(false)
{
}

void UReadyPlayerMeAvatarLoader::LoadAvatar(const FString& UrlShortcode, UReadyPlayerMeAvatarConfig* AvatarConfig,
	const FAvatarDownloadCompleted& OnDownloadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	const FString Url = FReadyPlayerMeUrlConvertor::GetValidatedUrlShortCode(UrlShortcode);
	if (UrlShortcode.IsEmpty())
	{
		(void)OnLoadFailed.ExecuteIfBound("Url invalid");
		return;
	}
	Reset();
	OnAvatarDownloadCompleted = OnDownloadCompleted;
	OnAvatarLoadFailed = OnLoadFailed;
	AvatarUri = FReadyPlayerMeUrlConvertor::CreateAvatarUri(Url, AvatarConfig);
	CacheHandler = MakeShared<FReadyPlayerMeAvatarCacheHandler>(*AvatarUri);
	if (CacheHandler->ShouldLoadFromCache())
	{
		bIsTryingToUpdate = true;
		LoadAvatarMetadata();
	}
	else
	{
		LoadAvatarMetadata();
		LoadAvatarModel();
	}
}

void UReadyPlayerMeAvatarLoader::CancelAvatarLoad()
{
	if (!AvatarMetadataRequest.IsValid())
	{
		return;
	}

	if (AvatarMetadataRequest->GetStatus() == EHttpRequestStatus::Type::Processing || AvatarMetadataRequest->GetStatus() == EHttpRequestStatus::Type::NotStarted)
	{
		AvatarMetadataRequest->CancelRequest();
	}

	if (AvatarModelRequest.IsValid() && (AvatarModelRequest->GetStatus() == EHttpRequestStatus::Type::Processing || AvatarModelRequest->GetStatus() == EHttpRequestStatus::Type::NotStarted))
	{
		AvatarModelRequest->CancelRequest();
	}
	Reset();
}

void UReadyPlayerMeAvatarLoader::ProcessReceivedMetadata(const FString& ResponseContent)
{
	if (!bIsTryingToUpdate)
	{
		CacheHandler->SetUpdatedMetadataStr(ResponseContent, AvatarMetadata->LastModifiedDate, bIsTryingToUpdate);
		ExecuteSuccessCallback();
		return;
	}
	if (CacheHandler->IsMetadataChanged(AvatarMetadata->LastModifiedDate))
	{
		CacheHandler->SetUpdatedMetadataStr(ResponseContent, AvatarMetadata->LastModifiedDate, bIsTryingToUpdate);
		LoadAvatarModel();
		return;
	}
	GlTFRuntimeAsset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(AvatarUri->LocalModelPath, false, FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeConfig());
	if (GlTFRuntimeAsset != nullptr)
	{
		ExecuteSuccessCallback();
	}
	else
	{
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to load the model from the local storage"));
		LoadAvatarModel();
	}
}

void UReadyPlayerMeAvatarLoader::ExecuteSuccessCallback()
{
	if (GlTFRuntimeAsset != nullptr && AvatarMetadata.IsSet())
	{
		(void)OnAvatarDownloadCompleted.ExecuteIfBound(GlTFRuntimeAsset, AvatarMetadata.GetValue());
		CacheHandler->SaveAvatarInCache();
		Reset();
	}
}

void UReadyPlayerMeAvatarLoader::ExecuteFailureCallback(const FString& ErrorMessage)
{
	(void)OnAvatarLoadFailed.ExecuteIfBound(ErrorMessage);
	Reset();
}

void UReadyPlayerMeAvatarLoader::OnMetadataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (!OnAvatarDownloadCompleted.IsBound())
	{
		return;
	}
	if (bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		AvatarMetadata = FReadyPlayerMeMetadataExtractor::ExtractAvatarMetadata(Response->GetContentAsString());
		AvatarMetadata->LastModifiedDate = Response->GetHeader(HEADER_LAST_MODIFIED);
		ProcessReceivedMetadata(Response->GetContentAsString());
	}
	else
	{
		ExecuteFailureCallback("Failed to retrieve avatar metadata");
	}
}

void UReadyPlayerMeAvatarLoader::OnAvatarModelReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (!OnAvatarDownloadCompleted.IsBound())
	{
		return;
	}
	if (bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		UE_LOG(LogReadyPlayerMe, Log, TEXT("Model Downloaded in [%.1fs]"), (FDateTime::Now() - AvatarDownloadTime).GetTotalSeconds());
		GlTFRuntimeAsset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromData(Response->GetContent(), FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeConfig());
		if (GlTFRuntimeAsset == nullptr)
		{
			ExecuteFailureCallback("Failed to load the avatar model");
			return;
		}
		CacheHandler->SetAvatarResponse(Response);
		ExecuteSuccessCallback();
	}
	else
	{
		ExecuteFailureCallback("Failed to retrieve Avatar Meta Data");
	}
}

void UReadyPlayerMeAvatarLoader::LoadAvatarMetadata()
{
	AvatarMetadataRequest = FReadyPlayerMeRequestCreator::MakeHttpRequest(AvatarUri->MetadataUrl, METADATA_REQUEST_TIMEOUT);
	AddRPMHeaders(AvatarMetadataRequest);
	AvatarMetadataRequest->OnProcessRequestComplete().BindUObject(this, &UReadyPlayerMeAvatarLoader::OnMetadataReceived);
	AvatarMetadataRequest->ProcessRequest();
}

void UReadyPlayerMeAvatarLoader::LoadAvatarModel()
{
	AvatarDownloadTime = FDateTime::Now();
	AvatarModelRequest = FReadyPlayerMeRequestCreator::MakeHttpRequest(AvatarUri->ModelUrl, AVATAR_REQUEST_TIMEOUT);
	AvatarModelRequest->OnProcessRequestComplete().BindUObject(this, &UReadyPlayerMeAvatarLoader::OnAvatarModelReceived);
	AddRPMHeaders(AvatarModelRequest);
	AvatarModelRequest->ProcessRequest();
}

void UReadyPlayerMeAvatarLoader::Reset()
{
	bIsTryingToUpdate = false;
	GlTFRuntimeAsset = nullptr;
	CacheHandler.Reset();
	AvatarMetadata.Reset();
	AvatarUri.Reset();
	OnAvatarDownloadCompleted.Unbind();
	OnAvatarLoadFailed.Unbind();
	AvatarModelRequest.Reset();
	AvatarMetadataRequest.Reset();
}

void UReadyPlayerMeAvatarLoader::BeginDestroy()
{
	CancelAvatarLoad();
	Super::BeginDestroy();
}
