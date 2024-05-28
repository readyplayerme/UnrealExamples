// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FMetadataExtractor
{
public:
	static FString GetRootBoneName(const EAvatarBodyType& AvatarBodyType);

	static EAvatarBodyType GetBodyTypeFromAsset(class UglTFRuntimeAsset* GltfRuntimeAsset);

	static FAvatarMetadata ExtractAvatarMetadata(const FString& JsonString);
};
