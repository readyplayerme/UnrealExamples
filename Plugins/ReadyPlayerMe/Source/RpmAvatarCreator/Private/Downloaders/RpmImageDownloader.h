// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmImageDownloader.generated.h"

UCLASS()
class URpmImageDownloader : public UObject
{
	GENERATED_BODY()

public:
	void DownloadImage(const FString& ImageUrl, int32 Size, const FImageDownloadCompleted& ImageDownloaded);

	void SetRequestFactory(TSharedPtr<class FRequestFactory> Factory);

	void RemoveImage(const FString& ImageUrl);

private:
	void OnImageDownloadCompleted(bool bSuccess, FString ImageUrl);

	UPROPERTY()
	TMap<FString, UTexture2D*> ImageMap;

	TSharedPtr<class FRequestFactory> RequestFactory;
	TMap<FString, TSharedPtr<class IBaseRequest>> ImageRequests;
	TMap<FString, TArray<FImageDownloadCompleted>> RequestCallbacks;
};
