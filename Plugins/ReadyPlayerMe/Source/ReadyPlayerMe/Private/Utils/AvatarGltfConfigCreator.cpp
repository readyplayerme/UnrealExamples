// Copyright © 2024 Ready Player Me


#include "AvatarGltfConfigCreator.h"

void FAvatarGltfConfigCreator::OverrideConfig(FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig, const FString& RootBoneName, USkeleton* Skeleton)
{
	SkeletalMeshConfig.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
	SkeletalMeshConfig.bAddVirtualBones = true;
	SkeletalMeshConfig.Skeleton = Skeleton;

	SkeletalMeshConfig.SkeletonConfig.CopyRotationsFrom = Skeleton;
	SkeletalMeshConfig.SkeletonConfig.bAddRootBone = true;
	SkeletalMeshConfig.SkeletonConfig.RootBoneName = RootBoneName;
}

FglTFRuntimeConfig FAvatarGltfConfigCreator::GetGlTFRuntimeConfig()
{
	FglTFRuntimeConfig RuntimeConfig;
	RuntimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
	return RuntimeConfig;
}
