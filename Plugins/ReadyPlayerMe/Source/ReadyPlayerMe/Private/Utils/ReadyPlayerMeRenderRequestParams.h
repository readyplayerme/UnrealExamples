// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FReadyPlayerMeRenderRequestParams
{
public:
	static FString SerializeRenderRequestContent(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender);

	static FString ExtractUrlFromRenderResponse(const FString& JsonString);

private:
	static FString SceneTypeToString(const ERenderSceneType& SceneType);

	static FString GetArmatureTarget(const EAvatarGender& Gender);
};
