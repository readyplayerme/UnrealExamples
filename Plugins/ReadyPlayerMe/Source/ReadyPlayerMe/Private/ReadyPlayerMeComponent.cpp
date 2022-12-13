// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeComponent.h"
#include "ReadyPlayerMeAvatarLoader.h"
#include "ReadyPlayerMeRenderLoader.h"
#include "ReadyPlayerMeSkeletonSelector.h"
#include "Utils/ReadyPlayerMeGlTFConfigCreator.h"
#include "Utils/ReadyPlayerMeUrlConvertor.h"
#include "Utils/ReadyPlayerMeMetadataExtractor.h"
#include "glTFRuntimeAsset.h"
#include "UObject/UObjectGlobals.h"
#include "Components/SkeletalMeshComponent.h"
#include "Media/Public/IMediaTracks.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimBlueprintGeneratedClass.h"

UReadyPlayerMeComponent::UReadyPlayerMeComponent()
	: AvatarConfig(nullptr)
	, SkeletalMeshComponent(nullptr)
	, AnimGeneratedClass(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
	OnAvatarDownloadCompleted.BindDynamic(this, &UReadyPlayerMeComponent::OnAvatarDownloaded);
	OnSkeletalMeshCallback.BindDynamic(this, &UReadyPlayerMeComponent::OnSkeletalMeshLoaded);
}

void UReadyPlayerMeComponent::LoadAvatar(const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed)
{
	if (SkeletonSelector == nullptr || SkeletonSelector->Skeletons.Num() == 0)
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
	OnAvatarLoadFailed = OnLoadFailed;
	AvatarLoader = NewObject<UReadyPlayerMeAvatarLoader>(this,TEXT("AvatarLoader"));
	AvatarLoader->LoadAvatar(UrlShortcode, AvatarConfig, OnAvatarDownloadCompleted, OnAvatarLoadFailed);
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

void UReadyPlayerMeComponent::OnAvatarDownloaded(UglTFRuntimeAsset* Asset, const FAvatarMetadata& Metadata)
{
	AvatarMetadata = Metadata;
	LoadSkeletalMesh(Asset);
}

void UReadyPlayerMeComponent::LoadSkeletalMesh(UglTFRuntimeAsset* Asset)
{
	if (AvatarMetadata.BodyType == EAvatarBodyType::Undefined)
	{
		AvatarMetadata.BodyType = FReadyPlayerMeMetadataExtractor::GetBodyTypeFromAsset(Asset);
	}
	const FString RootBoneName = FReadyPlayerMeMetadataExtractor::GetRootBoneName(AvatarMetadata.BodyType);

	const FSkeletonProperties* Properties = SkeletonSelector->GetSelectedSkeletonProperties(AvatarMetadata);
	if (Properties == nullptr || Properties->Skeleton == nullptr)
	{
		(void)OnAvatarLoadFailed.ExecuteIfBound("Incorrect skeleton type is set for the avatar");
		return;
	}
	AnimGeneratedClass = Properties->AnimGeneratedClass;
	FReadyPlayerMeGlTFConfigCreator::OverrideConfig(SkeletalMeshConfig, RootBoneName, Properties->Skeleton);
	Asset->LoadSkeletalMeshRecursiveAsync(RootBoneName, {}, OnSkeletalMeshCallback, SkeletalMeshConfig);
}

void UReadyPlayerMeComponent::OnSkeletalMeshLoaded(USkeletalMesh* SkeletalMesh)
{
	if (SkeletalMesh == nullptr)
	{
		(void)OnAvatarLoadFailed.ExecuteIfBound("Failed to load the skeletal mesh");
		return;
	}
	InitSkeletalMeshComponent();
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	if (AnimGeneratedClass != nullptr)
	{
		SkeletalMeshComponent->SetAnimInstanceClass(AnimGeneratedClass);
	}
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

void UReadyPlayerMeComponent::LoadRender(const ERenderSceneType& SceneType, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed)
{
	UrlShortcode = FReadyPlayerMeUrlConvertor::GetValidatedUrlShortCode(UrlShortcode);
	if (UrlShortcode.IsEmpty())
	{
		(void)OnFailed.ExecuteIfBound("Url invalid");
		return;
	}
	RenderLoader = NewObject<UReadyPlayerMeRenderLoader>(this,TEXT("RenderLoader"));
	RenderLoader->Load(UrlShortcode, SceneType, OnCompleted, OnFailed);
}
