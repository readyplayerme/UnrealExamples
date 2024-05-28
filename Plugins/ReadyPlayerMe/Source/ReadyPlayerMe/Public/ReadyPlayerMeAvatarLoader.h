// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeAvatarLoader.generated.h"

/**
 * Responsible for Loading the avatar from the url and storing it in the local storage.
 * ReadyPlayerMeAvatarLoader is used by ReadyPlayerMeComponent for loading the avatar.
 */
UCLASS(BlueprintType, Meta = (ShowWorldContextPin))
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
	 * @param TargetSkeleton skeleton that will be used for the loaded avatar.
	 * @param SkeletalMeshConfig Avatar configuration asset data. Used to load the avatar with the specific configs.
	 * @param OnDownloadCompleted Success callback. Called when the avatar asset is downloaded.
	 * @param OnLoadFailed Failure callback. If the avatar fails to load, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Avatar", AutoCreateRefTerm = "OnLoadFailed,SkeletalMeshConfig", WorldContext = "WorldContextObject"))
	void LoadAvatar(UPARAM(DisplayName="Url") const FString& UrlShortcode, class UReadyPlayerMeAvatarConfig* AvatarConfig,
		USkeleton* TargetSkeleton, const FglTFRuntimeSkeletalMeshConfig& SkeletalMeshConfig,
		const FAvatarDownloadCompleted& OnDownloadCompleted, const FAvatarLoadFailed& OnLoadFailed);

	/**
	 * Cancels the avatar downloading process. This function is called during garbage collection, but it can also be called manually.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Cancel Avatar Load"))
	void CancelAvatarLoad();

	/**
	 * Skeletal Mesh of the loaded avatar.
	 */
	UPROPERTY()
	USkeletalMesh* SkeletalMesh;

	UPROPERTY()
	class UReadyPlayerMeAutoLodConfig* AutoLodConfig;

private:
	UFUNCTION()
	void OnMetadataDownloaded(bool bSuccess);

	UFUNCTION()
	void OnModelDownloaded(bool bSuccess, int LodIndex);

	UFUNCTION()
	void OnGlbLoaded(USkeletalMesh* Mesh);

	void ProcessReceivedMetadata();

	void DownloadAvatarModel();

	void ExecuteSuccessCallback();

	void ExecuteFailureCallback(const FString& ErrorMessage);

	void TryLoadFromCache();

	void LoadGlb(bool bFromFile, const EAvatarBodyType BodyType);

	void Reset();

	virtual void BeginDestroy() override;

	UPROPERTY()
	class UReadyPlayerMeGlbLoader* GlbLoader;

	TOptional<FAvatarMetadata> AvatarMetadata;
	TOptional<FAvatarUri> AvatarUri;

	TSharedPtr<class FAvatarCacheHandler> CacheHandler;
	TSharedPtr<class FAvatarRequest> MetadataRequest;
	TArray<TSharedPtr<class FAvatarRequest>> ModelRequests;

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;
	FAvatarLoadFailed OnAvatarLoadFailed;
	FGlbLoadCompleted OnGlbLoadCompleted;

	int DownloadedModelCount;
	bool bIsTryingToUpdate;
};
