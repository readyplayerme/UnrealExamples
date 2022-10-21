// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FReadyPlayerMeMetadataExtractor
{
public:
	static FString GetRootBoneName(const EAvatarBodyType& AvatarBodyType);

	static EAvatarBodyType GetBodyTypeFromAsset(class UglTFRuntimeAsset* GltfRuntimeAsset);

	static FAvatarMetadata ExtractAvatarMetadata(const FString& JsonString);

	static FString AddModifiedDateToMetadataJson(const FString& JsonString, const FString& LastModifiedDate);
};
