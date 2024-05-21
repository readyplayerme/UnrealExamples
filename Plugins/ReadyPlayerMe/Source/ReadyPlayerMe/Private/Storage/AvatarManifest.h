// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FAvatarManifest
{
public:
	void AddAvatarAndEnforceLimit(const FString& AvatarId);
	void AddAvatar(const FString& AvatarId);
	void ClearAvatar(const FString& AvatarId);
	void LockAvatar(const FString& AvatarId);
	void UnlockAvatar(const FString& AvatarId);
	void Clear();

private:
	void EnforceAvatarLimit();
	TArray<FString> GetIdsByOldestDate();
	void Save() const;
	void Load();
	
	TMap<FString, int64> AvatarRecords;
	TSet<FString> LockedAvatars;
	bool bIsManifestLoaded = false;
};
