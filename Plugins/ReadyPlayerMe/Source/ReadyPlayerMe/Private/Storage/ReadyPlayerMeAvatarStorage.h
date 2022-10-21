// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FReadyPlayerMeAvatarStorage
{
public:
	static void SaveAvatar(const FString& GlbFilePath, const TArray<uint8>& Data);
	static void SaveMetadata(const FString& MetadataFilePath, const FString& Content);
	
	static bool AvatarExists(const FAvatarUri& AvatarUri);
	static bool FileExists(const FString& Path);
	static FString LoadMetadata(const FString& Path);
	static void ClearAvatarCache();
	static void DeleteDirectory(const FString& Path);

private:
	static bool CheckAndRemoveExistingFile(const FString& FilePath);
};
