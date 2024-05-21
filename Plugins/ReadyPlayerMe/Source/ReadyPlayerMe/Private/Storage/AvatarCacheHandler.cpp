// Copyright © 2024 Ready Player Me


#include "AvatarCacheHandler.h"
#include "AvatarStorage.h"
#include "AvatarManifest.h"
#include "Utils/MetadataExtractor.h"

namespace
{
	FRpmAvatarCacheSettings GetAvatarCacheSettings()
	{
		const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
		if (Settings)
		{
			return Settings->AvatarCacheSettings;
		}
		return {};
	}
}

FAvatarCacheHandler::FAvatarCacheHandler(const FAvatarUri& AvatarUri, TSharedPtr<class FAvatarManifest> Manifest)
	: AvatarUri(AvatarUri)
	, bMetadataNeedsUpdate(false)
	, AvatarManifest(MoveTemp(Manifest))
	, AvatarCacheSettings(GetAvatarCacheSettings())
{
	if (AvatarCacheSettings.bEnableAvatarCaching && AvatarCacheSettings.bEnableAutomaticCacheCleaning && AvatarManifest.IsValid())
	{
		AvatarManifest->LockAvatar(AvatarUri.Guid);
	}
}

FAvatarCacheHandler::~FAvatarCacheHandler()
{
	if (AvatarCacheSettings.bEnableAvatarCaching && AvatarCacheSettings.bEnableAutomaticCacheCleaning && AvatarManifest.IsValid())
	{
		AvatarManifest->UnlockAvatar(AvatarUri.Guid);
	}
}


bool FAvatarCacheHandler::ShouldLoadFromCache() const
{
	return AvatarCacheSettings.bEnableAvatarCaching && FAvatarStorage::AvatarExists(AvatarUri);
}

bool FAvatarCacheHandler::IsMedataUpdated(const FString& UpdatedDate) const
{
	const auto Metadata = GetLocalMetadata();
	if (Metadata.IsSet())
	{
		return Metadata->UpdatedAtDate != UpdatedDate;
	}
	return true;
}

TOptional<FAvatarMetadata> FAvatarCacheHandler::GetLocalMetadata() const
{
	const FString MetadataStr = FAvatarStorage::LoadJson(AvatarUri.LocalMetadataPath);
	if (!MetadataStr.IsEmpty())
	{
		return FMetadataExtractor::ExtractAvatarMetadata(MetadataStr);
	}
	return {};
}

bool FAvatarCacheHandler::ShouldSaveMetadata() const
{
	return bMetadataNeedsUpdate;
}

void FAvatarCacheHandler::SetUpdatedMetadataStr(const FString& MetadataJson, const FString& UpdatedDate)
{
	if (!AvatarCacheSettings.bEnableAvatarCaching)
	{
		return;
	}
	bMetadataNeedsUpdate = IsMedataUpdated(UpdatedDate);
	UpdatedMetadataStr = MetadataJson;
	if (FAvatarStorage::FileExists(AvatarUri.LocalMetadataPath) && bMetadataNeedsUpdate)
	{
		FAvatarStorage::DeleteDirectory(AvatarUri.LocalAvatarDirectory);
	}
}

void FAvatarCacheHandler::SetModelData(int LodIndex, const TArray<uint8>* Data)
{
	if (!AvatarCacheSettings.bEnableAvatarCaching)
	{
		return;
	}
	// We store the pointer because we don't want to copy the avatar data.
	if (LodIndex == 0)
	{
		ModelDataMap.Add(AvatarUri.LocalModelPath, Data);
	}
	else
	{
		ModelDataMap.Add(AvatarUri.LocalModelLodPaths[LodIndex - 1], Data);
	}
}

void FAvatarCacheHandler::SaveAvatarInCache() const
{
	if (AvatarCacheSettings.bEnableAvatarCaching && ModelDataMap.Num() != 0)
	{
		if (bMetadataNeedsUpdate)
		{
			FAvatarStorage::SaveJson(AvatarUri.LocalMetadataPath, UpdatedMetadataStr);
		}
		for (const auto& Pair : ModelDataMap)
		{
			FAvatarStorage::SaveAvatar(Pair.Key, *Pair.Value);
		}
		if (AvatarCacheSettings.bEnableAutomaticCacheCleaning && AvatarManifest.IsValid())
		{
			AvatarManifest->AddAvatarAndEnforceLimit(AvatarUri.Guid);
		}
	}
}

void FAvatarCacheHandler::ResetState()
{
	UpdatedMetadataStr = "";
	ModelDataMap.Empty();
	bMetadataNeedsUpdate = false;
};
