// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeGlbLoader.generated.h"

UCLASS()
class UReadyPlayerMeGlbLoader : public UObject
{
	GENERATED_BODY()

public:
	UReadyPlayerMeGlbLoader();

	void LoadFromFile(const FString& LocalModelPath, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	void LoadFromData(const TArray<uint8>& Data, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	void LoadFromLodData(const TArray<const TArray<uint8>*>& LodData, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	void LoadFromLodFiles(const TArray<FString>& LocalModelLodPaths, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	UPROPERTY()
	USkeleton* TargetSkeleton;

	UPROPERTY()
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;

private:
	UFUNCTION()
	void OnSkeletalMeshLoaded(USkeletalMesh* SkeletalMesh);

	void LoadSkeletalMesh(class UglTFRuntimeAsset* Asset, EAvatarBodyType BodyType);

	void LoadFromLodData(UglTFRuntimeAsset* Asset, const TArray<FglTFRuntimeMeshLOD>& RuntimeLODs, const TArray<float>& LODScreenSizes, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	FglTFRuntimeSkeletalMeshAsync OnSkeletalMeshCallback;
	FGlbLoadCompleted OnLoadCompleted;
};
