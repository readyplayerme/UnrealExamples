// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FReadyPlayerMeRenderUrlConvertor
{
public:
	static FString CreateRenderUrl(const FString& ModelUrl, const ERenderSceneType& SceneType);

private:
	static FString SceneTypeToString(const ERenderSceneType& SceneType);
};
