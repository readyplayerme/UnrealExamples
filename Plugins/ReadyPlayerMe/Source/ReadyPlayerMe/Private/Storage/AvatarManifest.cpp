// Copyright © 2024 Ready Player Me


#include "AvatarManifest.h"

#include "ReadyPlayerMeSettings.h"
#include "Storage/AvatarStorage.h"
#include "Utils/AvatarManifestExtractor.h"

void FAvatarManifest::AddAvatarAndEnforceLimit(const FString& AvatarId)
{
	AddAvatar(AvatarId);
	EnforceAvatarLimit();
}

void FAvatarManifest::AddAvatar(const FString& AvatarId)
{
	if (!AvatarRecords.Contains(AvatarId))
	{
		AvatarRecords.Add(AvatarId, FDateTime::Now().ToUnixTimestamp());
	}
}

void FAvatarManifest::LockAvatar(const FString& AvatarId)
{
	Load();
	LockedAvatars.Add(AvatarId);
	if (AvatarRecords.Contains(AvatarId))
	{
		AvatarRecords[AvatarId] = FDateTime::Now().ToUnixTimestamp();
		Save();
	}
}

void FAvatarManifest::UnlockAvatar(const FString& AvatarId)
{
	LockedAvatars.Remove(AvatarId);
}

void FAvatarManifest::ClearAvatar(const FString& AvatarId)
{
	Load();
	AvatarRecords.Remove(AvatarId);
	Save();
}

void FAvatarManifest::Clear()
{
	Load();
	AvatarRecords.Empty();
	Save();
}

void FAvatarManifest::Load()
{
	if (bIsManifestLoaded)
	{
		return;
	}
	const FString ManifestFilename = FAvatarStorage::GetManifestFilePath();
	if (!FAvatarStorage::FileExists(ManifestFilename))
	{
		const TArray<FString> SavedAvatars = FAvatarStorage::GetSavedAvatars();
		for (const auto& AvatarId : SavedAvatars)
		{
			AvatarRecords.Add(AvatarId, FDateTime::Now().ToUnixTimestamp());
		}
		Save();
	}
	const FString JsonStr = FAvatarStorage::LoadJson(ManifestFilename);
	if (!JsonStr.IsEmpty())
	{
		AvatarRecords = FAvatarManifestExtractor::ExtractAvatarManifest(JsonStr);
	}
	bIsManifestLoaded = true;
}

void FAvatarManifest::Save() const
{
	FAvatarStorage::SaveJson(FAvatarStorage::GetManifestFilePath(), FAvatarManifestExtractor::SerializeAvatarManifest(AvatarRecords));
}

TArray<FString> FAvatarManifest::GetIdsByOldestDate()
{
	AvatarRecords.ValueSort(TGreater<int64>());
	TArray<FString> SortedIds;
	AvatarRecords.GetKeys(SortedIds);
	for (const FString& BlockedAvatar : LockedAvatars)
	{
		SortedIds.Remove(BlockedAvatar);
	}
	return SortedIds;
}

void FAvatarManifest::EnforceAvatarLimit()
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (!bIsManifestLoaded)
	{
		Load();
	}
	int32 CurrentAvatarCount = AvatarRecords.Num();
	if (CurrentAvatarCount <= Settings->AvatarCacheSettings.CachedAvatarLimit)
	{
		return;
	}
	TArray<FString> AvatarQueue = GetIdsByOldestDate();
	while (CurrentAvatarCount > Settings->AvatarCacheSettings.CachedAvatarLimit && AvatarQueue.Num() != 0)
	{
		const FString AvatarId = AvatarQueue.Pop();
		FAvatarStorage::ClearAvatar(AvatarId);
		AvatarRecords.Remove(AvatarId);
		CurrentAvatarCount--;
	}
	Save();
}
