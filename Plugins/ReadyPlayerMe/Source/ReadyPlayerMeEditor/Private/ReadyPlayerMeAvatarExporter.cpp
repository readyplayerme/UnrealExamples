// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeAvatarExporter.h"

#include "AssetToolsModule.h"
#include "ReadyPlayerMeAvatarLoader.h"

#include "glTFRuntimeFunctionLibrary.h"

namespace
{
	FglTFRuntimeSkeletalMeshConfig MakeSkeletalMeshConfig(const FString& RootBoneName)
	{
		FglTFRuntimeSkeletonConfig SkeletonConfig;
		SkeletonConfig.bAddRootBone = true;
		SkeletonConfig.RootBoneName = RootBoneName;

		FglTFRuntimeMaterialsConfig MaterialsConfig;
		MaterialsConfig.bMergeSectionsByMaterial = true;

		FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;
		SkeletalMeshConfig.SkeletonConfig = SkeletonConfig;
		SkeletalMeshConfig.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
		SkeletalMeshConfig.MaterialsConfig = MaterialsConfig;

		return SkeletalMeshConfig;
	}
}

UReadyPlayerMeAvatarExporter::UReadyPlayerMeAvatarExporter()
{
	OnAvatarDownloadCompleted.BindDynamic(this, &UReadyPlayerMeAvatarExporter::OnAvatarDownloaded);
	OnLoadFailed.BindDynamic(this, &UReadyPlayerMeAvatarExporter::OnAvatarDownloadFailed);
}

void UReadyPlayerMeAvatarExporter::ExportAvatarWithDialog(const FString& Url)
{
	AvatarLoader = NewObject<UReadyPlayerMeAvatarLoader>(this, TEXT("AvatarLoader"));
	AvatarLoader->LoadAvatar(Url, nullptr, OnAvatarDownloadCompleted, OnLoadFailed);
}

void UReadyPlayerMeAvatarExporter::OnAvatarDownloaded(UglTFRuntimeAsset* Asset, const FAvatarMetadata& Metadata)
{
	const FString RootBoneName = Metadata.BodyType == EAvatarBodyType::FullBody ? "Armature" : "AvatarRoot";

	USkeletalMesh* SkeletalMesh = Asset->LoadSkeletalMeshRecursive(RootBoneName, {}, MakeSkeletalMeshConfig(RootBoneName));

	const FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().ExportAssetsWithDialog(TArray<UObject*>{SkeletalMesh}, true);
}

void UReadyPlayerMeAvatarExporter::OnAvatarDownloadFailed(const FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Failed to download the avatar"));
}