// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"

#include "glTFRuntimeParser.h"

class FAvatarGltfConfigCreator
{
public:
	static void OverrideConfig(FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig, const FString& RootBoneName, USkeleton* Skeleton);

	static FglTFRuntimeConfig GetGlTFRuntimeConfig();

};
