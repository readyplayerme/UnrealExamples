// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeGlTFConfigCreator.h"

void FReadyPlayerMeGlTFConfigCreator::OverrideConfig(FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig, const FString& RootBoneName, USkeleton* Skeleton)
{
	SkeletalMeshConfig.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
	SkeletalMeshConfig.bAddVirtualBones = true;
	SkeletalMeshConfig.Skeleton = Skeleton;
	SkeletalMeshConfig.MaterialsConfig.bMergeSectionsByMaterial = true;

	SkeletalMeshConfig.SkeletonConfig.CopyRotationsFrom = Skeleton;
	SkeletalMeshConfig.SkeletonConfig.bAddRootBone = true;
	SkeletalMeshConfig.SkeletonConfig.RootBoneName = RootBoneName;
}

FglTFRuntimeConfig FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeConfig()
{
	FglTFRuntimeConfig RuntimeConfig;
	RuntimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
	return RuntimeConfig;
}
