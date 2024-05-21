// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeComponent.h"
#include "ReadyPlayerMeAvatarLoader.h"
#include "ReadyPlayerMeMemoryCache.h"
#include "ReadyPlayerMeGameSubsystem.h"
#include "ReadyPlayerMeSettings.h"
#include "UObject/UObjectGlobals.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Utils/AvatarUrlConvertor.h"

UReadyPlayerMeComponent::UReadyPlayerMeComponent()
	: TargetSkeleton(nullptr)
	, AvatarConfig(nullptr)
	, AutoLodConfig(nullptr)
	, SkeletalMeshComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
	OnAvatarDownloadCompleted.BindDynamic(this, &UReadyPlayerMeComponent::OnAvatarDownloaded);
}

void UReadyPlayerMeComponent::LoadAvatar(const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	if (!TargetSkeleton)
	{
		(void)OnLoadFailed.ExecuteIfBound("No target skeleton set");
		return;
	}
	if (UrlShortcode.IsEmpty())
	{
		(void)OnLoadFailed.ExecuteIfBound("Url is empty");
		return;
	}

	OnAvatarLoadCompleted = OnLoadCompleted;

	const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GetWorld()->GetGameInstance());
	if (IsValid(GameSubsystem))
	{
		const FAvatarMemoryCacheData CacheData = GameSubsystem->MemoryCache->GetAvatarCacheData(FAvatarUrlConvertor::GetAvatarId(UrlShortcode), AvatarConfig);
		if (IsValid(CacheData.SkeletalMesh))
		{
			SetAvatarData(CacheData.SkeletalMesh, CacheData.Metadata);
			return;
		}
	}

	AvatarLoader = NewObject<UReadyPlayerMeAvatarLoader>(this,TEXT("AvatarLoader"));
	AvatarLoader->AutoLodConfig = AutoLodConfig;
	AvatarLoader->LoadAvatar(UrlShortcode, AvatarConfig, TargetSkeleton, SkeletalMeshConfig, OnAvatarDownloadCompleted, OnLoadFailed);
}

void UReadyPlayerMeComponent::LoadNewAvatar(const FString& Url, const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	UrlShortcode = Url;
	LoadAvatar(OnLoadCompleted, OnLoadFailed);
}

void UReadyPlayerMeComponent::CancelAvatarLoad()
{
	if(IsValid(AvatarLoader))
	{
		AvatarLoader->CancelAvatarLoad();
	}
}

void UReadyPlayerMeComponent::OnAvatarDownloaded(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata)
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (IsValid(Settings) && Settings->bKeepLoadedAvatarsInMemory)
	{
		const UReadyPlayerMeGameSubsystem* GameSubsystem = UGameInstance::GetSubsystem<UReadyPlayerMeGameSubsystem>(GetWorld()->GetGameInstance());
		if (IsValid(GameSubsystem))
		{
			GameSubsystem->MemoryCache->AddAvatar(FAvatarUrlConvertor::GetAvatarId(UrlShortcode), AvatarConfig, SkeletalMesh, Metadata);
		}
	}
	SetAvatarData(SkeletalMesh, Metadata);
}

void UReadyPlayerMeComponent::SetAvatarData(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata)
{
	AvatarMetadata = Metadata;
	InitSkeletalMeshComponent();
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	(void)OnAvatarLoadCompleted.ExecuteIfBound();
}

void UReadyPlayerMeComponent::InitSkeletalMeshComponent()
{
	if (IsValid(SkeletalMeshComponent))
	{
		return;
	}
	AActor* ThisActor = GetOwner();
	SkeletalMeshComponent = ThisActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMeshComponent)
	{
		SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(ThisActor, TEXT("SkeletalMesh"));
		SkeletalMeshComponent->SetupAttachment(ThisActor->GetRootComponent());
		SkeletalMeshComponent->RegisterComponent();
	}
}
