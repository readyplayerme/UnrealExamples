// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FAvatarManifestExtractor
{
public:
	static TMap<FString, int64> ExtractAvatarManifest(const FString& JsonString);
	static FString SerializeAvatarManifest(const TMap<FString, int64>& AvatarRecords);
};
