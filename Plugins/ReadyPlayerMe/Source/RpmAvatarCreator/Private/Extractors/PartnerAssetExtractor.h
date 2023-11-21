// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

struct FAssetPaginationData
{
	TArray<FRpmPartnerAsset> Assets;
	int CurrentPage = 0;
	int TotalPages = 0;
	bool bHasNextPage = false;
};

class FPartnerAssetExtractor
{
public:
	static FString GetStringFromAssetType(ERpmPartnerAssetType AssetType);
	static FAssetPaginationData ExtractAssets(const FString& JsonString);
	static TArray<FRpmColorPalette> ExtractColors(const FString& JsonString);
};
