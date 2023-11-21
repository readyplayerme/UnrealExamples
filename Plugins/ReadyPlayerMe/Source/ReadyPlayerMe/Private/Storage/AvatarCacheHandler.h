// Copyright © 2021++ Ready Player Me

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
	void SetModelData(const TArray<uint8>* Data);

	void SaveAvatarInCache() const;

	void ResetState();

	bool ShouldLoadFromCache() const;

	bool ShouldSaveMetadata() const;
	
	TOptional<FAvatarMetadata> GetLocalMetadata() const;

private:
	bool IsMedataUpdated(const FString& UpdatedDate) const;
	
	const FAvatarUri AvatarUri;

	FString UpdatedMetadataStr;
	const TArray<uint8>* ModelData;
	bool bMetadataNeedsUpdate;

	TSharedPtr<class FAvatarManifest> AvatarManifest;
	const FRpmAvatarCacheSettings AvatarCacheSettings;
};
