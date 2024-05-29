// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeGlbLoader.h"
#include "Utils/AvatarGltfConfigCreator.h"
#include "Utils/MetadataExtractor.h"
#include "glTFRuntimeFunctionLibrary.h"

UReadyPlayerMeGlbLoader::UReadyPlayerMeGlbLoader()
{
	OnSkeletalMeshCallback.BindDynamic(this, &UReadyPlayerMeGlbLoader::OnSkeletalMeshLoaded);
}
                                              
void UReadyPlayerMeGlbLoader::LoadFromFile(const FString& LocalModelPath, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted)
{
	OnLoadCompleted = LoadCompleted;
	UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(LocalModelPath, false, FAvatarGltfConfigCreator::GetGlTFRuntimeConfig());
	LoadSkeletalMesh(Asset, BodyType);
}

void UReadyPlayerMeGlbLoader::LoadFromData(const TArray<uint8>& Data, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted)
{
	OnLoadCompleted = LoadCompleted;
	UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromData(Data, FAvatarGltfConfigCreator::GetGlTFRuntimeConfig());
	LoadSkeletalMesh(Asset, BodyType);
}

void UReadyPlayerMeGlbLoader::LoadFromLodData(const TArray<const TArray<uint8>*>& LodData, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted)
{
	TArray<FglTFRuntimeMeshLOD> RuntimeLODs;
	UglTFRuntimeAsset* Asset = nullptr;
	for (int i = 0; i < LodData.Num(); ++i)
	{
		UglTFRuntimeAsset* LodAsset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromData(*LodData[i], FAvatarGltfConfigCreator::GetGlTFRuntimeConfig());
		RuntimeLODs.Add({});
		int SkinIndex = i;
		LodAsset->LoadSkinnedMeshRecursiveAsRuntimeLOD("", {}, RuntimeLODs[i], {}, {}, SkinIndex);

		if (i == 0)
		{
			Asset = LodAsset;
		}
	}
	LoadFromLodData(Asset, RuntimeLODs, LODScreenSizes, BodyType, LoadCompleted);
}

void UReadyPlayerMeGlbLoader::LoadFromLodFiles(const TArray<FString>& LocalModelLodPaths, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted)
{
	TArray<FglTFRuntimeMeshLOD> RuntimeLODs;
	UglTFRuntimeAsset* Asset = nullptr;
	for (int i = 0; i < LocalModelLodPaths.Num(); ++i)
	{
		UglTFRuntimeAsset* LodAsset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(LocalModelLodPaths[i], false, FAvatarGltfConfigCreator::GetGlTFRuntimeConfig());
		RuntimeLODs.Add({});
		int SkinIndex = 0;
		LodAsset->LoadSkinnedMeshRecursiveAsRuntimeLOD("", {}, RuntimeLODs[i], {}, {}, SkinIndex);

		if (i == 0)
		{
			Asset = LodAsset;
		}
	}
	LoadFromLodData(Asset, RuntimeLODs, LODScreenSizes, BodyType, LoadCompleted);
}

void UReadyPlayerMeGlbLoader::LoadFromLodData(UglTFRuntimeAsset* Asset, const TArray<FglTFRuntimeMeshLOD>& RuntimeLODs, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted)
{
	if (BodyType == EAvatarBodyType::Undefined)
	{
		BodyType = FMetadataExtractor::GetBodyTypeFromAsset(Asset);
	}
	const FString RootBoneName = FMetadataExtractor::GetRootBoneName(BodyType);
	FAvatarGltfConfigCreator::OverrideConfig(SkeletalMeshConfig, RootBoneName, TargetSkeleton);
	SkeletalMeshConfig.LODScreenSize.Add(0, 1.0f);
	for (int i = 0; i < LODScreenSizes.Num(); ++i)
	{
		SkeletalMeshConfig.LODScreenSize.Add(i + 1, LODScreenSizes[i]);
	}

	USkeletalMesh* SkeletalMesh = Asset->LoadSkeletalMeshFromRuntimeLODs(RuntimeLODs, 0, SkeletalMeshConfig);
	(void)LoadCompleted.ExecuteIfBound(SkeletalMesh);
}

void UReadyPlayerMeGlbLoader::LoadSkeletalMesh(UglTFRuntimeAsset* Asset, EAvatarBodyType BodyType)
{
	if (Asset == nullptr)
	{
		(void)OnLoadCompleted.ExecuteIfBound(nullptr);
		UE_LOG(LogReadyPlayerMe, Warning, TEXT("Failed to load the avatar model"));
	}
	if (BodyType == EAvatarBodyType::Undefined)
	{
		BodyType = FMetadataExtractor::GetBodyTypeFromAsset(Asset);
	}
	const FString RootBoneName = FMetadataExtractor::GetRootBoneName(BodyType);
	FAvatarGltfConfigCreator::OverrideConfig(SkeletalMeshConfig, RootBoneName, TargetSkeleton);
	Asset->LoadSkeletalMeshRecursiveAsync(RootBoneName, {}, OnSkeletalMeshCallback, SkeletalMeshConfig);
}

void UReadyPlayerMeGlbLoader::OnSkeletalMeshLoaded(USkeletalMesh* SkeletalMesh)
{
	(void)OnLoadCompleted.ExecuteIfBound(SkeletalMesh);
}
