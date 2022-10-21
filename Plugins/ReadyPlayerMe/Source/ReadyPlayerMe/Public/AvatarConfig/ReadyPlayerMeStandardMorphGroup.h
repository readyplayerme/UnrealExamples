// Copyright © 2021++ Ready Player Me

#pragma once

#include "ReadyPlayerMeMorphTargetGroup.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeStandardMorphGroup.generated.h"

/**
 * Base data asset class for providing standard morph targets to the avatar config.
 * For customization create a blueprint data asset subclass.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeStandardMorphGroup : public UReadyPlayerMeMorphTargetGroup
{
	GENERATED_BODY()

public:
	/** The selected morph target groups will be included in the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	TSet<EStandardMorphTargetGroup> MorphTargetGroups;

	virtual void GetTargets(TSet<EStandardMorphTargetGroup>& Groups, TSet<EAvatarMorphTarget>& Targets) const override { Groups = MorphTargetGroups; };
};
