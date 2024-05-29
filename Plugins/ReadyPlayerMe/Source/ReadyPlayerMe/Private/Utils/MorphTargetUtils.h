// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FMorphTargetUtils
{
public:
	static FString MorphTargetToString(EAvatarMorphTarget MorphTarget);
	static FString MorphTargetGroupToString(EStandardMorphTargetGroup Group);
};
