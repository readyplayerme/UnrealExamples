// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeTypes.h"
#include "Storage/ReadyPlayerMeAvatarCacheHandler.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "Interfaces/IHttpRequest.h"
#include "ReadyPlayerMeAvatarLoader.generated.h"
/**
 * It's responsible for Loading the avatar from the url and storing it in the local storage.
 * ReadyPlayerMeAvatarLoader is used by ReadyPlayerMeActorComponent for loading the avatar.
 */
UCLASS(BlueprintType)
class READYPLAYERME_API UReadyPlayerMeAvatarLoader : public UObject
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	UReadyPlayerMeAvatarLoader();

	/**
	 * Downloads the avatar asset from the Url and saves it in the local storage.
	 *
	 * @param UrlShortcode Avatar url or shortcode.
	 * @param AvatarConfig Config for loading avatar with custom configuration.
	 * @param OnDownloadCompleted Success callback. Called when the avatar asset is downloaded.
	 * @param OnLoadFailed Failure callback. If the avatar fails to load, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Avatar", AutoCreateRefTerm = "OnLoadFailed"))
	void LoadAvatar(const FString& UrlShortcode, class UReadyPlayerMeAvatarConfig* AvatarConfig, const FAvatarDownloadCompleted& OnDownloadCompleted, const FAvatarLoadFailed& OnLoadFailed);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Cancel Avatar Load"))
	void CancelAvatarLoad();

private:
	void OnMetadataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	
	void OnAvatarModelReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	
	void LoadAvatarMetadata();
	
	void LoadAvatarModel();

	void ProcessReceivedMetadata(const FString& ResponseContent);

	void ExecuteSuccessCallback();

	void ExecuteFailureCallback(const FString& ErrorMessage);
	
	void Reset();

	virtual void BeginDestroy() override;

	UPROPERTY()
	UglTFRuntimeAsset* GlTFRuntimeAsset;

	TOptional<FAvatarMetadata> AvatarMetadata;
	TOptional<FAvatarUri> AvatarUri;

	TUniquePtr<FReadyPlayerMeAvatarCacheHandler> CacheHandler;

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;
	FAvatarLoadFailed OnAvatarLoadFailed;

	bool bIsTryingToUpdate;

#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 25
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> AvatarMetadataRequest;
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> AvatarModelRequest;
#else
	TSharedPtr<IHttpRequest> AvatarMetadataRequest;
	TSharedPtr<IHttpRequest> AvatarModelRequest;
#endif
};
