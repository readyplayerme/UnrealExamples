// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReadyPlayerMeAvatarConfig.generated.h"

UENUM(BlueprintType)
enum class EAvatarPose : uint8
{
	APose UMETA(DisplayName = "A-Pose"),
	TPose UMETA(DisplayName = "T-Pose")
};

UENUM(BlueprintType)
enum class EAvatarMeshLod : uint8
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
	EAvatarMeshLod MeshLod = EAvatarMeshLod::High;

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

	/** If set to true the hands of the avatars will be included. This property applies only to the half-body avatars. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	bool bUseHands = true;

	/** The selected morph target group (blend shapes) will be included in the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	class UReadyPlayerMeMorphTargetGroup* MorphTargetGroup;
};
