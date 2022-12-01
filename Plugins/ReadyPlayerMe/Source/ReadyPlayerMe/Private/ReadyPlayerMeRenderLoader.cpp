// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeRenderLoader.h"
#include "Utils/ReadyPlayerMeRenderUrlConvertor.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Engine/Texture2DDynamic.h"

void UReadyPlayerMeRenderLoader::Load(const FString& ModelUrl, const ERenderSceneType& SceneType, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed)
{
	OnDownloadImageCompleted = OnCompleted;
	OnDownloadImageFailed = OnFailed;
	const FString Url = FReadyPlayerMeRenderUrlConvertor::CreateRenderUrl(ModelUrl, SceneType);
	DownloadRenderedImage(Url);
}

void UReadyPlayerMeRenderLoader::DownloadRenderedImage(const FString& ImageUrl)
{
	DownloadImageTask = NewObject<UAsyncTaskDownloadImage>();
	DownloadImageTask->OnSuccess.AddDynamic(this, &UReadyPlayerMeRenderLoader::OnTexture2DDownloaded);
	DownloadImageTask->OnFail.AddDynamic(this, &UReadyPlayerMeRenderLoader::OnTexture2DDownloadFailed);
	DownloadImageTask->Start(ImageUrl);
}

void UReadyPlayerMeRenderLoader::OnTexture2DDownloaded(UTexture2DDynamic* Texture)
{
	DownloadImageTask = nullptr;
	(void)OnDownloadImageCompleted.ExecuteIfBound(Texture);
}

void UReadyPlayerMeRenderLoader::OnTexture2DDownloadFailed(UTexture2DDynamic*)
{
	DownloadImageTask = nullptr;
	(void)OnDownloadImageFailed.ExecuteIfBound(TEXT("Failed to Download the image"));
}
