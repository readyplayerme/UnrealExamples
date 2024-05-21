// Copyright © 2024 Ready Player Me


#include "ReadyPlayerMeAvatarLoader.h"

#include "ReadyPlayerMeAutoLodConfig.h"
#include "ReadyPlayerMeAvatarConfig.h"
#include "ReadyPlayerMeGameSubsystem.h"
#include "Utils/AvatarUrlConvertor.h"
#include "Storage/AvatarCacheHandler.h"
#include "ReadyPlayerMeGlbLoader.h"
#include "Request/AvatarRequest.h"
#include "Utils/MetadataExtractor.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

//TODO: Move the timout to the RPMSettings to make it configurable
constexpr float AVATAR_REQUEST_TIMEOUT = 60.f;
constexpr float METADATA_REQUEST_TIMEOUT = 20.f;

UReadyPlayerMeAvatarLoader::UReadyPlayerMeAvatarLoader()
	: SkeletalMesh(nullptr)
	, AutoLodConfig(nullptr)
	, GlbLoader(nullptr)
	, DownloadedModelCount(0)
	, bIsTryingToUpdate(false)
{
}

void UReadyPlayerMeAvatarLoader::LoadAvatar(const FString& UrlShortcode, UReadyPlayerMeAvatarConfig* AvatarConfig,
	USkeleton* TargetSkeleton, const FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig,
	const FAvatarDownloadCompleted& OnDownloadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	const FString Url = FAvatarUrlConvertor::GetValidatedUrl(UrlShortcode);
	if (Url.IsEmpty())
	{
		(void)OnLoadFailed.ExecuteIfBound("Url invalid");
		return;
	}
	Reset();
	OnAvatarDownloadCompleted = OnDownloadCompleted;
	OnAvatarLoadFailed = OnLoadFailed;
	AvatarUri = FAvatarUrlConvertor::CreateAvatarUri(Url, AvatarConfig, AutoLodConfig);
	const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GetWorld()->GetGameInstance());
	auto AvatarManifest = GameSubsystem ? GameSubsystem->AvatarManifest : nullptr;
	CacheHandler = MakeShared<FAvatarCacheHandler>(*AvatarUri, AvatarManifest);

	GlbLoader = NewObject<UReadyPlayerMeGlbLoader>(this,TEXT("GlbLoader"));
	GlbLoader->SkeletalMeshConfig = SkeletalMeshConfig;
	GlbLoader->TargetSkeleton = TargetSkeleton;

	MetadataRequest = MakeShared<FAvatarRequest>();
	MetadataRequest->GetCompleteCallback().BindUObject(this, &UReadyPlayerMeAvatarLoader::OnMetadataDownloaded);
	MetadataRequest->Download(AvatarUri->MetadataUrl, METADATA_REQUEST_TIMEOUT);
	if (CacheHandler->ShouldLoadFromCache())
	{
		bIsTryingToUpdate = true;
	}
	else
	{
		DownloadAvatarModel();
	}
}

void UReadyPlayerMeAvatarLoader::CancelAvatarLoad()
{
	if (MetadataRequest.IsValid())
	{
		MetadataRequest->CancelRequest();
	}
	for (const auto& Request : ModelRequests)
	{
		Request->CancelRequest();
	}
	Reset();
}

void UReadyPlayerMeAvatarLoader::ProcessReceivedMetadata()
{
	AvatarMetadata = FMetadataExtractor::ExtractAvatarMetadata(MetadataRequest->GetContentAsString());
	CacheHandler->SetUpdatedMetadataStr(MetadataRequest->GetContentAsString(), AvatarMetadata->UpdatedAtDate);
	// If we are not trying to update the avatar, the metadata and the model should be downloaded as the standard flow.
	if (!bIsTryingToUpdate)
	{
		ExecuteSuccessCallback();
		return;
	}
	// If we are trying to update the avatar and the metadata is changed, we check if the metadata is changed, we update the model.
	if (CacheHandler->ShouldSaveMetadata())
	{
		DownloadAvatarModel();
		return;
	}
	// If we are trying to update the avatar, but the metadata is not changed, we loaded the cached avatar.
	LoadGlb(true, AvatarMetadata->BodyType);
}

void UReadyPlayerMeAvatarLoader::ExecuteSuccessCallback()
{
	if (SkeletalMesh != nullptr && AvatarMetadata.IsSet())
	{
		CacheHandler->SaveAvatarInCache();
		(void)OnAvatarDownloadCompleted.ExecuteIfBound(SkeletalMesh, *AvatarMetadata);
		Reset();
	}
}

void UReadyPlayerMeAvatarLoader::TryLoadFromCache()
{
	MetadataRequest->GetCompleteCallback().Unbind();
	for (const auto& Request : ModelRequests)
	{
		Request->GetCompleteCallback().Unbind();
	}
	// We reset the cache handler state to prevent saving of incomplete data
	CacheHandler->ResetState();
	AvatarMetadata = CacheHandler->GetLocalMetadata();
	if (AvatarMetadata.IsSet())
	{
		LoadGlb(true, AvatarMetadata->BodyType);
	}
	else
	{
		ExecuteFailureCallback("Failed to load local metadata");
	}
}

void UReadyPlayerMeAvatarLoader::ExecuteFailureCallback(const FString& ErrorMessage)
{
	(void)OnAvatarLoadFailed.ExecuteIfBound(ErrorMessage);
	Reset();
}

void UReadyPlayerMeAvatarLoader::OnMetadataDownloaded(bool bSuccess)
{
	if (!OnAvatarDownloadCompleted.IsBound())
	{
		return;
	}
	if (bSuccess)
	{
		ProcessReceivedMetadata();
	}
	else if (bIsTryingToUpdate)
	{
		TryLoadFromCache();
	}
	else
	{
		ExecuteFailureCallback("Failed to retrieve avatar metadata");
	}
}

void UReadyPlayerMeAvatarLoader::OnGlbLoaded(USkeletalMesh* Mesh)
{
	if (!OnAvatarDownloadCompleted.IsBound())
	{
		return;
	}
	if (Mesh != nullptr)
	{
		SkeletalMesh = Mesh;
		ExecuteSuccessCallback();
	}
	else
	{
		ExecuteFailureCallback("Failed to load the avatar model");
	}
	OnGlbLoadCompleted.Unbind();
}

void UReadyPlayerMeAvatarLoader::OnModelDownloaded(bool bSuccess, int LodIndex)
{
	if (!OnAvatarDownloadCompleted.IsBound())
	{
		return;
	}
	if (bSuccess)
	{
		CacheHandler->SetModelData(LodIndex, &ModelRequests[LodIndex]->GetContent());
		DownloadedModelCount++;
		if (DownloadedModelCount == AvatarUri->ModelLodUrls.Num() + 1)
		{
			const EAvatarBodyType BodyType = AvatarMetadata ? AvatarMetadata->BodyType : EAvatarBodyType::Undefined;
			LoadGlb(false, BodyType);
		}
	}
	else if (bIsTryingToUpdate)
	{
		TryLoadFromCache();
	}
	else
	{
		ExecuteFailureCallback("Failed to retrieve Avatar Meta Data");
	}
}

void UReadyPlayerMeAvatarLoader::DownloadAvatarModel()
{
	TArray<FString> ModelUrls = {AvatarUri->ModelUrl};
	ModelUrls.Append(AvatarUri->ModelLodUrls);
	for (int i = 0; i < ModelUrls.Num(); ++i)
	{
		ModelRequests.Add(MakeShared<FAvatarRequest>());
		ModelRequests[i]->GetCompleteCallback().BindUObject(this, &UReadyPlayerMeAvatarLoader::OnModelDownloaded, i);
		ModelRequests[i]->Download(ModelUrls[i], AVATAR_REQUEST_TIMEOUT);
	}
}

void UReadyPlayerMeAvatarLoader::LoadGlb(bool bFromFile, const EAvatarBodyType BodyType)
{
	OnGlbLoadCompleted.BindDynamic(this, &UReadyPlayerMeAvatarLoader::OnGlbLoaded);
	if (bFromFile)
	{
		if (AvatarUri->ModelLodUrls.Num() == 0)
		{
			GlbLoader->LoadFromFile(AvatarUri->LocalModelPath, BodyType, OnGlbLoadCompleted);
		}
		else
		{
			TArray<FString> ModelLodPaths = {AvatarUri->LocalModelPath};
			ModelLodPaths.Append(AvatarUri->LocalModelLodPaths);
			GlbLoader->LoadFromLodFiles(ModelLodPaths, AutoLodConfig->LODScreenSizes, BodyType, OnGlbLoadCompleted);
		}
	}
	else
	{
		OnGlbLoadCompleted.BindDynamic(this, &UReadyPlayerMeAvatarLoader::OnGlbLoaded);
		if (AvatarUri->ModelLodUrls.Num() == 0)
		{
			GlbLoader->LoadFromData(ModelRequests[0]->GetContent(), BodyType, OnGlbLoadCompleted);
		}
		else
		{
			TArray<const TArray<uint8>*> LodData;
			for (const auto& Request : ModelRequests)
			{
				LodData.Add(&Request->GetContent());
			}
			GlbLoader->LoadFromLodData(LodData, AutoLodConfig->LODScreenSizes, BodyType, OnGlbLoadCompleted);
		}
	}
}

void UReadyPlayerMeAvatarLoader::Reset()
{
	bIsTryingToUpdate = false;
	SkeletalMesh = nullptr;
	GlbLoader = nullptr;
	DownloadedModelCount = 0;
	OnGlbLoadCompleted.Unbind();
	CacheHandler.Reset();
	AvatarMetadata.Reset();
	AvatarUri.Reset();
	MetadataRequest.Reset();
	ModelRequests.Empty();
}

void UReadyPlayerMeAvatarLoader::BeginDestroy()
{
	CancelAvatarLoad();
	Super::BeginDestroy();
}
