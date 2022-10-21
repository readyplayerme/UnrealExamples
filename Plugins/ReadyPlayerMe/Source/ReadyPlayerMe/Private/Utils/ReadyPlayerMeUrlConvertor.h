// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FReadyPlayerMeUrlConvertor
{
public:
	static FString GetValidatedUrlShortCode(const FString& UrlShortCode);

	static bool IsUrl(const FString& Url);

	static bool IsShortcode(const FString& Shortcode);

	static FAvatarUri CreateAvatarUri(const FString& Url, class UReadyPlayerMeAvatarConfig* AvatarConfig);
};
