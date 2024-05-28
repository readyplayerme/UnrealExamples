// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ReadyPlayerMeLoadRenderAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadImageCompleted, class UTexture2D*, Texture);

/**
 * Async action, responsible for Loading rendered image from the avatar url.
 */
UCLASS()
class READYPLAYERME_API UReadyPlayerMeLoadRenderAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	 * Creates load render async action.
	 *
	 * @param Url Model url.
	 * @param Properties The properties for defining the render environment.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "Ready Player Me", AutoCreateRefTerm = "Properties"))
	static UReadyPlayerMeLoadRenderAction* LoadAvatarRenderAsync(const FString& Url, const FRpmAvatarRenderProperties& Properties);

	/** Success callback. Called when the render is loaded and provides the avatar texture as an argument. */
	UPROPERTY(BlueprintAssignable)
	FDownloadImageCompleted OnCompleted;

	/** Failure callback. If the render operation fails, the failure callback will be called. */
	UPROPERTY(BlueprintAssignable)
	FDownloadImageCompleted OnFailed;

	/** Load the rendered image. */
	void Load(const FString& Url, const FRpmAvatarRenderProperties& Properties);

private:
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnImageDownloaded(bool bSuccess);

	TSharedPtr<class FAvatarRequest> ImageRequest;
};
