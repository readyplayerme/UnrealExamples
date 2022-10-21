// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FReadyPlayerMeGlTFConfigCreator
{
public:
	static struct FglTFRuntimeSkeletalMeshConfig GetGlTFRuntimeSkeletalMeshConfig(const FString& RootBoneName, USkeleton* Skeleton = nullptr );

	static struct FglTFRuntimeConfig GetGlTFRuntimeConfig();

private:
	static struct FglTFRuntimeSkeletonConfig GetGlTFRuntimeSkeletonConfig(const FString& RootBoneName, USkeleton* Skeleton);

	static struct FglTFRuntimeMaterialsConfig GetGlTFRuntimeMaterialsConfig();
};
