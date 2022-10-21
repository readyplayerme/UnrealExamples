// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeAvatarCacheHandler.h"
#include "ReadyPlayerMeAvatarStorage.h"
#include "ReadyPlayerMeSettings.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/ReadyPlayerMeMetadataExtractor.h"


FReadyPlayerMeAvatarCacheHandler::FReadyPlayerMeAvatarCacheHandler(const FAvatarUri& AvatarUri)
	: AvatarUri(AvatarUri)
	, bMetadataNeedsUpdate(false)
{
}

bool FReadyPlayerMeAvatarCacheHandler::IsCachingEnabled()
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		return Settings->bEnableAvatarCaching;
	}
	return false;
}

bool FReadyPlayerMeAvatarCacheHandler::ShouldLoadFromCache() const
{
	return IsCachingEnabled() && FReadyPlayerMeAvatarStorage::AvatarExists(AvatarUri);
}

bool FReadyPlayerMeAvatarCacheHandler::IsMetadataChanged(const FString& LastModifiedDate) const
{
	const FString MetadataStr = FReadyPlayerMeAvatarStorage::LoadMetadata(AvatarUri.LocalMetadataPath);
	if (!MetadataStr.IsEmpty())
	{
		const FAvatarMetadata LocalMetadata = FReadyPlayerMeMetadataExtractor::ExtractAvatarMetadata(MetadataStr);
		if (LocalMetadata.LastModifiedDate == LastModifiedDate)
		{
			return false;
		}
	}
	return true;
}

void FReadyPlayerMeAvatarCacheHandler::SetUpdatedMetadataStr(const FString& MetadataJson, const FString& LastModifiedDate, bool bIsTryingToUpdate)
{
	if (!IsCachingEnabled())
	{
		return;
	}
	bMetadataNeedsUpdate = IsMetadataChanged(LastModifiedDate);
	UpdatedMetadataStr = FReadyPlayerMeMetadataExtractor::AddModifiedDateToMetadataJson(MetadataJson, LastModifiedDate);
	if (bIsTryingToUpdate || (FReadyPlayerMeAvatarStorage::FileExists(AvatarUri.LocalMetadataPath) && bMetadataNeedsUpdate))
	{
		FReadyPlayerMeAvatarStorage::DeleteDirectory(AvatarUri.LocalAvatarDirectory);
	}
}

void FReadyPlayerMeAvatarCacheHandler::SetAvatarResponse(FHttpResponsePtr ResponsePtr)
{
	if (!IsCachingEnabled())
	{
		return;
	}
	// We store the response pointer because we don't want to copy the response content(avatar data).
	AvatarResponsePtr = ResponsePtr;
}

void FReadyPlayerMeAvatarCacheHandler::SaveAvatarInCache() const
{
	if (IsCachingEnabled() && !UpdatedMetadataStr.IsEmpty() && AvatarResponsePtr.IsValid())
	{
		if (bMetadataNeedsUpdate)
		{
			FReadyPlayerMeAvatarStorage::SaveMetadata(AvatarUri.LocalMetadataPath, UpdatedMetadataStr);
		}
		FReadyPlayerMeAvatarStorage::SaveAvatar(AvatarUri.LocalModelPath, AvatarResponsePtr->GetContent());
	}
}
