// Copyright © 2023++ Ready Player Me


#include "GlTFConfigCreator.h"

FglTFRuntimeSkeletalMeshConfig FGlTFConfigCreator::GetSkeletalMeshConfig(const FString& RootBoneName, USkeleton* Skeleton)
{
	FglTFRuntimeSkeletalMeshConfig Config;
	Config.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
	Config.bAddVirtualBones = true;
	Config.Skeleton = Skeleton;
	Config.MaterialsConfig.bMergeSectionsByMaterial = true;
	Config.MaterialsConfig.SpecularFactor = 0.5f;

	Config.SkeletonConfig.CopyRotationsFrom = Skeleton;
	Config.SkeletonConfig.bAddRootBone = true;
	Config.SkeletonConfig.RootBoneName = RootBoneName;
	Config.bIgnoreMissingBones = true;
	Config.SkeletonConfig.bAssignUnmappedBonesToParent = true;
	return Config;
}

FglTFRuntimeConfig FGlTFConfigCreator::GetGlTFRuntimeConfig()
{
	FglTFRuntimeConfig RuntimeConfig;
	RuntimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
	return RuntimeConfig;
}
