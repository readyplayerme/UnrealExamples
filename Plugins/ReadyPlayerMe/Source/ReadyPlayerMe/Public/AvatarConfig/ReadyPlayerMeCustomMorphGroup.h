// Copyright © 2021++ Ready Player Me

#pragma once

#include "ReadyPlayerMeMorphTargetGroup.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeCustomMorphGroup.generated.h"

/**
 * Base data asset class for providing custom morph targets to the avatar config.
 * For customization create a blueprint data asset subclass.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeCustomMorphGroup : public UReadyPlayerMeMorphTargetGroup
{
	GENERATED_BODY()

public:
	/** The selected morph targets will be included in the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TSet<EAvatarMorphTarget> MorphTargets;

	virtual void GetTargets(TSet<EStandardMorphTargetGroup>& Groups, TSet<EAvatarMorphTarget>& Targets) const override { Targets = MorphTargets; };
};
