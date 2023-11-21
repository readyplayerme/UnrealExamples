// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FRenderUrlConvertor
{
public:
	static FString CreateRenderUrl(const FString& Url, const FRpmAvatarRenderProperties& Properties);
};
