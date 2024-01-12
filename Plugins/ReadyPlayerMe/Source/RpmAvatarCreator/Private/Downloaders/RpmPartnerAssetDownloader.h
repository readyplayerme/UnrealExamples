// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

class FRpmPartnerAssetDownloader : public TSharedFromThis<FRpmPartnerAssetDownloader>
{
public:
	FRpmPartnerAssetDownloader(TSharedPtr<class FRequestFactory> RequestFactory, EAvatarBodyType BodyType);

	void DownloadAssets();

	void ClearAssets();

	TArray<FRpmPartnerAsset> GetFilteredAssets(EAvatarGender Gender) const;

	FBaseRequestCompleted& GetPartnerAssetsDownloadCallback();

	bool AreAssetsReady() const;

private:
	void OnAssetsDownloadCompleted(bool bSuccess, ERpmPartnerAssetType AssetType);

	TArray<FRpmPartnerAsset> Assets;

	FBaseRequestCompleted OnPartnerAssetsDownloaded;

	TSharedPtr<class FRequestFactory> RequestFactory;
	TMap<ERpmPartnerAssetType, TSharedPtr<class IBaseRequest>> AssetRequests;
	EAvatarBodyType BodyType;
};
