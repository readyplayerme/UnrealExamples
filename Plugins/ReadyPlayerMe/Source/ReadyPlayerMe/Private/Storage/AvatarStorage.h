// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"

class FAvatarStorage
{
public:
	static void SaveAvatar(const FString& GlbFilePath, const TArray<uint8>& Data);
	static void SaveJson(const FString& Path, const FString& Content);
	
	static bool AvatarExists(const FAvatarUri& AvatarUri);
	static bool FileExists(const FString& Path);
	static FString LoadJson(const FString& Path);
	static void ClearCache();
	static void DeleteDirectory(const FString& Path);
	static bool IsCacheEmpty();
	static void ClearAvatar(const FString& Guid);
	static TArray<FString> GetSavedAvatars();
	static int64 GetCacheSize();
	static FString GetManifestFilePath();
};
