// Copyright © 2021++ Ready Player Me


#include "Utils/ReadyPlayerMeGlTFConfigCreator.h"
#include "glTFRuntimeParser.h"

FglTFRuntimeSkeletonConfig FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeSkeletonConfig(const FString& RootBoneName, USkeleton* Skeleton)
{
	FglTFRuntimeSkeletonConfig SkeletonConfig;
	SkeletonConfig.CopyRotationsFrom = Skeleton;
	SkeletonConfig.bAddRootBone = true;
	SkeletonConfig.RootBoneName = RootBoneName;
	return SkeletonConfig;
}

FglTFRuntimeMaterialsConfig FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeMaterialsConfig()
{
	FglTFRuntimeMaterialsConfig MaterialsConfig;
	MaterialsConfig.bMergeSectionsByMaterial = true;

	return MaterialsConfig;
}

FglTFRuntimeSkeletalMeshConfig FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeSkeletalMeshConfig(const FString& RootBoneName, USkeleton* Skeleton)
{
	FglTFRuntimeSkeletalMeshConfig RuntimeSkeletalMeshConfig;
	RuntimeSkeletalMeshConfig.SkeletonConfig = GetGlTFRuntimeSkeletonConfig(RootBoneName, Skeleton);
	RuntimeSkeletalMeshConfig.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
	RuntimeSkeletalMeshConfig.MaterialsConfig = GetGlTFRuntimeMaterialsConfig();
	RuntimeSkeletalMeshConfig.bAddVirtualBones = true;
	if (Skeleton)
	{
		RuntimeSkeletalMeshConfig.Skeleton = Skeleton;
	}

	return RuntimeSkeletalMeshConfig;
}

FglTFRuntimeConfig FReadyPlayerMeGlTFConfigCreator::GetGlTFRuntimeConfig()
{
	FglTFRuntimeConfig RuntimeConfig;
	RuntimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
	return RuntimeConfig;
}
