// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

#include "glTFRuntimeParser.h"

class FReadyPlayerMeGlTFConfigCreator
{
public:
	static void OverrideConfig(FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig, const FString& RootBoneName, USkeleton* Skeleton);

	static FglTFRuntimeConfig GetGlTFRuntimeConfig();

};
