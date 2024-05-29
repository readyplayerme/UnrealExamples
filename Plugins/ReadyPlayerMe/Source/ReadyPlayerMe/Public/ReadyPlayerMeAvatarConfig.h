// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeAvatarConfig.generated.h"

UENUM(BlueprintType)
enum class EAvatarPose : uint8
{
	APose UMETA(DisplayName = "A-Pose"),
	TPose UMETA(DisplayName = "T-Pose")
};

UENUM(BlueprintType)
enum class EAvatarLod : uint8
{
	High UMETA(DisplayName = "High (0)"),
	Medium UMETA(DisplayName = "Medium (1)"),
	Low UMETA(DisplayName = "Low (2)")
};

UENUM(BlueprintType)
enum class EAvatarTextureAtlas : uint8
{
	None UMETA(DisplayName = "None"),
	High UMETA(DisplayName = "High (1024)"),
	Medium UMETA(DisplayName = "Medium (512)"),
	Low UMETA(DisplayName = "Low (256)")
};

UENUM(BlueprintType)
enum class EAvatarTextureSizeLimit : uint8
{
	Limit_1024 UMETA(DisplayName = "1024"),
	Limit_512 UMETA(DisplayName = "512"),
	Limit_256 UMETA(DisplayName = "256")
};

UENUM(BlueprintType)
enum class EAvatarTextureChannel : uint8
{
	BaseColor UMETA(DisplayName = "Base Color"),
	Normal UMETA(DisplayName = "Normal"),
	MetallicRoughness UMETA(DisplayName = "Metallic Roughness"),
	Emissive UMETA(DisplayName = "Emissive"),
	Occlusion UMETA(DisplayName = "Occlusion")
};

/**
 * Base data asset class that provides configuration for the avatar loader.
 * For customization create a blueprint data asset subclass. 
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeAvatarConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Mesh Level of detail. The avatar with high LOD is detailed, but at the same time heavier to load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarLod Lod = EAvatarLod::High;

	/** Avatar Pose. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarPose Pose = EAvatarPose::APose;

	/** By enabling texture atlas the textures will be merged into a single texture.
	 * With the texture atlas enabled the avatar will be rendered with a single draw call. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarTextureAtlas TextureAtlas = EAvatarTextureAtlas::None;

	/** Provides ability to change the texture size. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	EAvatarTextureSizeLimit TextureSizeLimit = EAvatarTextureSizeLimit::Limit_1024;

	/** Provides ability to select the texture channels that need to be included in the avatar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TSet<EAvatarTextureChannel> TextureChannels =
		{ EAvatarTextureChannel::BaseColor,
		EAvatarTextureChannel::Normal,
		EAvatarTextureChannel::MetallicRoughness,
		EAvatarTextureChannel::Emissive,
		EAvatarTextureChannel::Occlusion };

	/** If set to true the hands of the avatars will be included. This property applies only to the half-body avatars. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	bool bUseHands = true;

	/**
	 * If set to true the avatar will be compressed with the Mesh-Opt compression.
	 * Mesh-Opt compression will effectively reduce the size of the avatar by compressing the mesh geometry.
	 *
	 * @note Currently Mesh-Opt compression only works when the `TextureAtlas` property is set.
	 * @note Mesh-Opt compression should not be used along with the Draco compression.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	bool bUseMeshOptCompression = false;

	/**
	 * If set to true the avatar will be compressed with the Draco mesh compression.
	 *
	 * @note If the glTFRuntimeDraco plugin is not listed as a project dependency, this property will be ignored.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	bool bUseDracoMeshCompression = false;

	/** The selected morph target groups (blend shapes) will be included in the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TSet<EStandardMorphTargetGroup> MorphTargetGroups;

	/** The selected morph targets (blend shapes) will be included in the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TSet<EAvatarMorphTarget> MorphTargets;
};
