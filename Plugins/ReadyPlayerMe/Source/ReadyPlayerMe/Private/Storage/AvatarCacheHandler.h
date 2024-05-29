// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeSettings.h"
#include "ReadyPlayerMeTypes.h"

class FAvatarCacheHandler
{
public:
	FAvatarCacheHandler(const FAvatarUri& AvatarUri, TSharedPtr<class FAvatarManifest> Manifest);
	~FAvatarCacheHandler();

	void SetUpdatedMetadataStr(const FString& MetadataJson, const FString& UpdatedDate);
	void SetModelData(int LodIndex, const TArray<uint8>* Data);

	void SaveAvatarInCache() const;

	void ResetState();

	bool ShouldLoadFromCache() const;

	bool ShouldSaveMetadata() const;
	
	TOptional<FAvatarMetadata> GetLocalMetadata() const;

private:
	bool IsMedataUpdated(const FString& UpdatedDate) const;
	
	const FAvatarUri AvatarUri;

	FString UpdatedMetadataStr;
	TMap<FString, const TArray<uint8>*> ModelDataMap;
	bool bMetadataNeedsUpdate;

	TSharedPtr<class FAvatarManifest> AvatarManifest;
	const FRpmAvatarCacheSettings AvatarCacheSettings;
};
