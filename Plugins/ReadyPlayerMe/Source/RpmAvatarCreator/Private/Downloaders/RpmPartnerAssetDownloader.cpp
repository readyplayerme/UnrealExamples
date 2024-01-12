// Copyright © 2023++ Ready Player Me


#include "RpmPartnerAssetDownloader.h"

#include "Requests/RequestFactory.h"
#include "Extractors/PartnerAssetExtractor.h"

namespace
{
	bool IsAssetFiltered(const FRpmPartnerAsset& Asset, EAvatarGender Gender)
	{
		return Asset.Gender == Gender || Asset.Gender == EAvatarGender::Undefined;
	}
	bool ShouldDownloadAssets(ERpmPartnerAssetType AssetType, EAvatarBodyType BodyType)
	{
		const bool ShouldDownload = (BodyType == EAvatarBodyType::FullBody && AssetType != ERpmPartnerAssetType::Shirt) ||
			(BodyType == EAvatarBodyType::HalfBody && AssetType != ERpmPartnerAssetType::Outfit && AssetType != ERpmPartnerAssetType::Top &&
				AssetType != ERpmPartnerAssetType::Bottom && AssetType != ERpmPartnerAssetType::Footwear);
		return ShouldDownload;
	}
	constexpr int ASSET_REQUEST_LIMIT = 100;
}

FRpmPartnerAssetDownloader::FRpmPartnerAssetDownloader(TSharedPtr<FRequestFactory> RequestFactory, EAvatarBodyType BodyType)
	: RequestFactory(MoveTemp(RequestFactory))
	, BodyType(BodyType)
{
}

void FRpmPartnerAssetDownloader::DownloadAssets()
{
	if (AreAssetsReady())
	{
		(void)OnPartnerAssetsDownloaded.ExecuteIfBound(true);
		OnPartnerAssetsDownloaded.Unbind();
		return;
	}
	for (uint8 AssetTypeInt = 0; AssetTypeInt <= static_cast<uint8>(ERpmPartnerAssetType::Shirt); AssetTypeInt++)
	{
		ERpmPartnerAssetType AssetType = static_cast<ERpmPartnerAssetType>(AssetTypeInt);
		if (ShouldDownloadAssets(AssetType, BodyType))
		{
			auto AssetRequest = RequestFactory->CreateAssetRequest(FPartnerAssetExtractor::GetStringFromAssetType(AssetType), ASSET_REQUEST_LIMIT, 1);
			AssetRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmPartnerAssetDownloader::OnAssetsDownloadCompleted, AssetType);
			AssetRequests.Add(AssetType, AssetRequest);
			AssetRequest->Download();
		}
	}
}

void FRpmPartnerAssetDownloader::ClearAssets()
{
	Assets.Empty();
}

TArray<FRpmPartnerAsset> FRpmPartnerAssetDownloader::GetFilteredAssets(EAvatarGender Gender) const
{
	return Assets.FilterByPredicate([this, Gender](const auto& Asset){ return IsAssetFiltered(Asset, Gender); });
}

bool FRpmPartnerAssetDownloader::AreAssetsReady() const
{
	return AssetRequests.Num() == 0 && Assets.Num() > 0;
}

FBaseRequestCompleted& FRpmPartnerAssetDownloader::GetPartnerAssetsDownloadCallback()
{
	return OnPartnerAssetsDownloaded;
}

void FRpmPartnerAssetDownloader::OnAssetsDownloadCompleted(bool bSuccess, ERpmPartnerAssetType AssetType)
{
	if (bSuccess)
	{
		if (AssetRequests.Contains(AssetType))
		{
			auto AssetRequest = AssetRequests[AssetType];
			const FAssetPaginationData PaginationData = FPartnerAssetExtractor::ExtractAssets(AssetRequest->GetContentAsString());
			if (PaginationData.Assets.Num() != 0)
			{
				Assets.Append(PaginationData.Assets);
			}
			AssetRequests.Remove(AssetType);
			if (PaginationData.bHasNextPage)
			{
				AssetRequest = RequestFactory->CreateAssetRequest(FPartnerAssetExtractor::GetStringFromAssetType(AssetType), ASSET_REQUEST_LIMIT, PaginationData.CurrentPage + 1);
				AssetRequest->GetCompleteCallback().BindSP(AsShared(), &FRpmPartnerAssetDownloader::OnAssetsDownloadCompleted, AssetType);
				AssetRequests.Add(AssetType, AssetRequest);
				AssetRequest->Download();
			}
			if (AssetRequests.Num() == 0)
			{
				(void)OnPartnerAssetsDownloaded.ExecuteIfBound(Assets.Num() != 0);
				OnPartnerAssetsDownloaded.Unbind();
			}
		}
	}
	else
	{
		Assets.Empty();
		AssetRequests.Empty();
		(void)OnPartnerAssetsDownloaded.ExecuteIfBound(false);
		OnPartnerAssetsDownloaded.Unbind();
	}
}
