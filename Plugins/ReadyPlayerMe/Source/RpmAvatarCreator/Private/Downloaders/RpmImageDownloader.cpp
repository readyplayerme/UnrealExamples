// Copyright © 2023++ Ready Player Me


#include "RpmImageDownloader.h"

#include "Kismet/KismetRenderingLibrary.h"
#include "Requests/RequestFactory.h"

namespace
{
	const FString IMAGE_SIZE_PARAM = "w=";
}

void URpmImageDownloader::SetRequestFactory(TSharedPtr<FRequestFactory> Factory)
{
	RequestFactory = Factory;
}

void URpmImageDownloader::RemoveImage(const FString& ImageUrl)
{
	if (ImageMap.Contains(ImageUrl))
	{
		ImageMap.Remove(ImageUrl);
	}
}

void URpmImageDownloader::DownloadImage(const FString& ImageUrl, int32 Size, const FImageDownloadCompleted& ImageDownloaded)
{
	if (ImageUrl.IsEmpty())
	{
		return;
	}
	if (ImageMap.Contains(ImageUrl))
	{
		(void)ImageDownloaded.ExecuteIfBound(ImageMap[ImageUrl], ImageUrl);
		return;
	}
	if (RequestCallbacks.Contains(ImageUrl))
	{
		RequestCallbacks[ImageUrl].Add(ImageDownloaded);
		return;
	}
	FString UrlWithSize = ImageUrl;
	if (Size > 0)
	{
		UrlWithSize += (ImageUrl.Contains("?") ? "&"  : "?") + IMAGE_SIZE_PARAM + FString::FromInt(Size);
	}
	const auto ImageRequest = RequestFactory->CreateImageRequest(UrlWithSize);
	ImageRequests.Add(ImageUrl, ImageRequest);
	RequestCallbacks.Add(ImageUrl, {ImageDownloaded});
	ImageRequest->GetCompleteCallback().BindUObject(this, &URpmImageDownloader::OnImageDownloadCompleted, ImageUrl);
	ImageRequest->Download();
}

void URpmImageDownloader::OnImageDownloadCompleted(bool bSuccess, FString ImageUrl)
{
	UTexture2D* Texture = nullptr;
	if (bSuccess)
	{
		Texture = UKismetRenderingLibrary::ImportBufferAsTexture2D(this, ImageRequests[ImageUrl]->GetContent());
		ImageMap.Add(ImageUrl, Texture);
	}
	for (auto& Callback : RequestCallbacks[ImageUrl])
	{
		(void)Callback.ExecuteIfBound(Texture, ImageUrl);
	}
	ImageRequests.Remove(ImageUrl);
	RequestCallbacks.Remove(ImageUrl);
}
