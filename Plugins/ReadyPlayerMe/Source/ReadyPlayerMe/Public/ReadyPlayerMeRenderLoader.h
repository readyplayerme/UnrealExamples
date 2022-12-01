// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
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
	 * @param OnCompleted Success callback. Called when the render is loaded and provides the avatar texture as an argument.
	 * @param OnFailed Failure callback. If the render operation fails, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load", AutoCreateRefTerm = "OnCompleted, OnFailed"))
	void Load(const FString& ModelUrl, const ERenderSceneType& SceneType, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed);

private:
	void DownloadRenderedImage(const FString& ImageUrl);

	UFUNCTION()
	void OnTexture2DDownloaded(UTexture2DDynamic* Texture);

	UFUNCTION()
	void OnTexture2DDownloadFailed(UTexture2DDynamic* Texture);

	UPROPERTY()
	class UAsyncTaskDownloadImage* DownloadImageTask;

	FDownloadImageCompleted OnDownloadImageCompleted;

	FDownloadImageFailed OnDownloadImageFailed;
};
