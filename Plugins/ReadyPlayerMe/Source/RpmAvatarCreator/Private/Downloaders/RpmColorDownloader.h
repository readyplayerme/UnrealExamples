// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"

class FRpmColorDownloader : public TSharedFromThis<FRpmColorDownloader>
{
public:
	FRpmColorDownloader(TSharedPtr<class FRequestFactory> RequestFactory);

	void DownloadColors(const FString& AvatarId);
	TArray<FRpmColorPalette> GetColors() const;

	FBaseRequestCompleted& GetCompleteCallback();

private:
	void DownloadCompleted(bool bSuccess);

	FBaseRequestCompleted OnColorDownloadCompleted;

private:
	TSharedPtr<class FRequestFactory> RequestFactory;
	TArray<FRpmColorPalette> Colors;
	TSharedPtr<class IBaseRequest> ColorRequest;
};
