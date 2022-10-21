// Copyright © 2021++ Ready Player Me


#include "ReadyPlayerMeRenderLoader.h"
#include "Utils/ReadyPlayerMeRenderRequestParams.h"
#include "Utils/ReadyPlayerMeUrlConvertor.h"
#include "Utils/ReadyPlayerMeRequestCreator.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Engine/Texture2DDynamic.h"

static const FString& RENDER_API_URL = "https://render.readyplayer.me/render";
constexpr float RENDER_REQUEST_TIMEOUT = 60.f;

void UReadyPlayerMeRenderLoader::OnRenderCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		const FString ImageUrl = FReadyPlayerMeRenderRequestParams::ExtractUrlFromRenderResponse(Response->GetContentAsString());
		if (FReadyPlayerMeUrlConvertor::IsUrl(ImageUrl))
		{
			DownloadRenderedImage(ImageUrl);
			return;
		}
	}
	(void)OnDownloadImageFailed.ExecuteIfBound("Failed to render the portrait");
}

void UReadyPlayerMeRenderLoader::Load(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed)
{
	OnDownloadImageCompleted = OnCompleted;
	OnDownloadImageFailed = OnFailed;
	RequestRender(ModelUrl, SceneType, Gender);
}

void UReadyPlayerMeRenderLoader::RequestRender(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender)
{
	auto HttpRequest = FReadyPlayerMeRequestCreator::MakeHttpRequest(RENDER_API_URL, RENDER_REQUEST_TIMEOUT);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetContentAsString(FReadyPlayerMeRenderRequestParams::SerializeRenderRequestContent(ModelUrl, SceneType, Gender));
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UReadyPlayerMeRenderLoader::OnRenderCallback);
	HttpRequest->ProcessRequest();
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
	OnDownloadImageCompleted.ExecuteIfBound(Texture);
}

void UReadyPlayerMeRenderLoader::OnTexture2DDownloadFailed(UTexture2DDynamic* Texture)
{
	DownloadImageTask = nullptr;
	OnDownloadImageCompleted.ExecuteIfBound(Texture);
}
