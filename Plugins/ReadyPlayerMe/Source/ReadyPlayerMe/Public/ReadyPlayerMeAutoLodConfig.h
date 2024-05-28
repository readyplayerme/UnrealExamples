// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReadyPlayerMeAutoLodConfig.generated.h"

/**
 * Base data asset class that provides configuration for the avatar loader.
 * For customization create a blueprint data asset subclass. 
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeAutoLodConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Provides ability to select the texture channels that need to be included in the avatar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TArray<class UReadyPlayerMeAvatarConfig*> AutoLodConfigs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TArray<float> LODScreenSizes;
};
