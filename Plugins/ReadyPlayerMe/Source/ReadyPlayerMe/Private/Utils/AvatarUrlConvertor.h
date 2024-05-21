// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FAvatarUrlConvertor
{
public:
	static FString GetValidatedUrl(const FString& IdUrl);

	static bool IsUrl(const FString& Url);

	static bool IsId(const FString& Id);
	
	static FString GetAvatarId(const FString& IdUrl);

	static FAvatarUri CreateAvatarUri(const FString& Url, class UReadyPlayerMeAvatarConfig* AvatarConfig = nullptr, class UReadyPlayerMeAutoLodConfig* AutoLodConfig = nullptr);
};
