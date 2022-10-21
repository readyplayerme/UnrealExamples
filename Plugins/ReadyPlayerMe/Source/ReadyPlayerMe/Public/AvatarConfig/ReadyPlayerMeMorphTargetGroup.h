// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeMorphTargetGroup.generated.h"

/**
 * Base data asset class that provides morph targets to the avatar config.
 * Do not override this class for the customisation. Override the Standard or Custom TargetGroup instead.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeMorphTargetGroup : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GetTargets(TSet<EStandardMorphTargetGroup>& Groups, TSet<EAvatarMorphTarget>& Targets) const {};
};
