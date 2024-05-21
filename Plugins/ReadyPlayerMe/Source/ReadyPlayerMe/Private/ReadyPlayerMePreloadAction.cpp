// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMePreloadAction.h"

#include "ReadyPlayerMeAvatarLoader.h"
#include "ReadyPlayerMeGameSubsystem.h"
#include "ReadyPlayerMeMemoryCache.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
#include "Utils/AvatarUrlConvertor.h"

UReadyPlayerMePreloadAction* UReadyPlayerMePreloadAction::PreloadAvatarsAsync(UObject* WorldContextObject, const FAvatarPreloadData& PreloadData)
{
	UReadyPlayerMePreloadAction* Action = NewObject<UReadyPlayerMePreloadAction>(WorldContextObject);
	Action->PreloadData = PreloadData;
	return Action;
}

void UReadyPlayerMePreloadAction::Activate()
{
	if (GetWorld() == nullptr || PreloadData.AvatarIds.Num() == 0 || PreloadData.TargetSkeleton == nullptr)
	{
		OnFailed.Broadcast();
		return;
	}
	Preload();
}

void UReadyPlayerMePreloadAction::Preload()
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GameInstance);
	MemoryCache = GameSubsystem->MemoryCache;
	for (const FString& Url : PreloadData.AvatarIds)
	{
		const FString AvatarId = FAvatarUrlConvertor::GetAvatarId(Url);
		const FAvatarMemoryCacheData CacheData = MemoryCache->GetAvatarCacheData(AvatarId, PreloadData.AvatarConfig);
		if (CacheData.SkeletalMesh == nullptr)
		{
			UReadyPlayerMeAvatarLoader* AvatarLoader = NewObject<UReadyPlayerMeAvatarLoader>(this);
			FAvatarDownloadCompleted OnAvatarDownloadCompleted;
			FAvatarLoadFailed OnLoadFailed;
			OnAvatarDownloadCompleted.BindDynamic(this, &UReadyPlayerMePreloadAction::OnAvatarDownloaded);
			OnLoadFailed.BindDynamic(this, &UReadyPlayerMePreloadAction::OnAvatarLoadFailed);
			AvatarLoader->AutoLodConfig = PreloadData.AutoLodConfig;
			AvatarLoader->LoadAvatar(AvatarId, PreloadData.AvatarConfig, PreloadData.TargetSkeleton,
				PreloadData.SkeletalMeshConfig, OnAvatarDownloadCompleted, OnLoadFailed);
			AvatarLoaders.Add(AvatarId, AvatarLoader);
		}
	}
	if (AvatarLoaders.Num() == 0)
	{
		OnCompleted.Broadcast();
	}
}

void UReadyPlayerMePreloadAction::OnAvatarDownloaded(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata)
{
	if (AvatarLoaders.Num() == 0)
	{
		return;
	}
	const auto FoundItemMap = AvatarLoaders.FilterByPredicate([SkeletalMesh](const auto& Pair)
	{
		return Pair.Value->SkeletalMesh == SkeletalMesh;
	});
	const FString AvatarId = FoundItemMap.begin()->Key;
	MemoryCache->AddAvatar(AvatarId, PreloadData.AvatarConfig, SkeletalMesh, Metadata);
	AvatarLoaders.Remove(AvatarId);
	CompleteLoading();
}

void UReadyPlayerMePreloadAction::OnAvatarLoadFailed(const FString& ErrorMessage)
{
	if (AvatarLoaders.Num() == 0)
	{
		return;
	}
	++FailedRequestCount;
	CompleteLoading();
}

void UReadyPlayerMePreloadAction::CompleteLoading()
{
	if (AvatarLoaders.Num() == FailedRequestCount)
	{
		AvatarLoaders.Empty();
		if (FailedRequestCount == 0)
		{
			OnCompleted.Broadcast();
		}
		else
		{
			OnFailed.Broadcast();
		}
	}
}


void UReadyPlayerMePreloadAction::BeginDestroy()
{
	if (AvatarLoaders.Num() > 0)
	{
		OnCompleted.Clear();
		OnFailed.Clear();
		AvatarLoaders.Empty();
	}

	Super::BeginDestroy();
}
