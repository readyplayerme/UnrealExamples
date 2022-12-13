// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeSkeletonSelector.generated.h"

UENUM(BlueprintType)
enum class ESkeletonType : uint8
{
	Masculine UMETA(DisplayName = "Masculine"),
	Feminine UMETA(DisplayName = "Feminine"),
	HalfBody UMETA(DisplayName = "Half Body"),
};

USTRUCT(BlueprintType)
struct FSkeletonProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	USkeleton* Skeleton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me", meta = (DisplayName = "Anim Class (Optional)",
		Tooltip = "Optionally set the anim generated class after the avatar is loaded"))
	UAnimBlueprintGeneratedClass* AnimGeneratedClass;

	FSkeletonProperties()
		: Skeleton(nullptr)
		, AnimGeneratedClass(nullptr)
	{
	}
};

/**
 * Base data asset class that provides configuration for the avatar loader.
 * For customization create a blueprint data asset subclass. 
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeSkeletonSelector : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Mesh Level of detail. The avatar with high LOD is detailed, but at the same time heavier to load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TMap<ESkeletonType, FSkeletonProperties> Skeletons;

	const FSkeletonProperties* GetSelectedSkeletonProperties(const FAvatarMetadata& Metadata) const;
};
