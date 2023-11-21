// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

#include "glTFRuntimeParser.h"

class FGlTFConfigCreator
{
public:
	static FglTFRuntimeSkeletalMeshConfig GetSkeletalMeshConfig(const FString& RootBoneName, USkeleton* Skeleton);

	static FglTFRuntimeConfig GetGlTFRuntimeConfig();

};
