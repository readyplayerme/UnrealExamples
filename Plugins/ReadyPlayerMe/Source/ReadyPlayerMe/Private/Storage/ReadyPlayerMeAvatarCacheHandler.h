// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "Interfaces/IHttpRequest.h"

class FReadyPlayerMeAvatarCacheHandler
{
public:
	explicit FReadyPlayerMeAvatarCacheHandler(const FAvatarUri& AvatarUri);
	bool IsMetadataChanged(const FString& LastModifiedDate) const;

	void SetUpdatedMetadataStr(const FString& MetadataJson, const FString& LastModifiedDate, bool bIsTryingToUpdate);
	void SetAvatarResponse(FHttpResponsePtr ResponsePtr);

	void SaveAvatarInCache() const;

	bool ShouldLoadFromCache() const;

	static bool IsCachingEnabled();

private:
	const FAvatarUri AvatarUri;

	FString UpdatedMetadataStr;
	FHttpResponsePtr AvatarResponsePtr;
	bool bMetadataNeedsUpdate;
};
