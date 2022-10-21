// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "ReadyPlayerMeRenderLoader.generated.h"

/**
 * It's responsible for Loading the rendered image from the ModelUrl.
 * ReadyPlayerMeRenderLoader is used by ReadyPlayerMeActorComponent but It can also be used independently.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeRenderLoader : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Loads the rendered image.
	 * 
	 * @param ModelUrl Model url.
	 * @param SceneType The type of the scene where the avatar should be rendered.
	 * @param Gender Gender is needed for rendering the correct pose.
	 * @param OnCompleted Success callback. Called when the render is loaded and provides the avatar texture as an argument.
	 * @param OnFailed Failure callback. If the render operation fails, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load", AutoCreateRefTerm = "OnCompleted, OnFailed"))
	void Load(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed);

private:
	void RequestRender(const FString& ModelUrl, const ERenderSceneType& SceneType, const EAvatarGender& Gender);

	void DownloadRenderedImage(const FString& ImageUrl);

	UFUNCTION()
	void OnTexture2DDownloaded(UTexture2DDynamic* Texture);

	UFUNCTION()
	void OnTexture2DDownloadFailed(UTexture2DDynamic* Texture);

	void OnRenderCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

	UPROPERTY()
	class UAsyncTaskDownloadImage* DownloadImageTask;

	FDownloadImageCompleted OnDownloadImageCompleted;

	FDownloadImageFailed OnDownloadImageFailed;
};
