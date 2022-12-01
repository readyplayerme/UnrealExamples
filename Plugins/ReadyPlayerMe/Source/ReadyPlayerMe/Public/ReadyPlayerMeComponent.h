// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeComponent.generated.h"

class UglTFRuntimeAsset;

/**
 * Responsible for the loading of the avatar and visualizing it by setting the SkeletalMesh of the avatar.
 * It also provides useful functions for loading the avatar and loading a rendered image of the avatar.
 *
 * @see ReadyPlayerMeAvatarLoader
 * @see ReadyPlayerMeRenderLoader
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class READYPLAYERME_API UReadyPlayerMeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	UReadyPlayerMeComponent();

	/** 
	 * Downloads the avatar from the web and generates a skeletal mesh of the avatar.
	 * If the model was previously downloaded and stored locally, the local model will be used for the loading of the avatar. 
	 * 
	 * @param OnLoadCompleted Success callback. Called when the avatar asset is downloaded and the skeletal mesh is set.
	 * @param OnLoadFailed Failure callback. If the avatar fails to load, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Avatar", AutoCreateRefTerm = "OnLoadCompleted,OnLoadFailed"))
	void LoadAvatar(const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed);

	/**
	 * Downloads the avatar from the web using the provided url and generates a skeletal mesh of the avatar.
	 * If the model was previously downloaded and stored locally, the local model will be used for the loading of the avatar. 
	 * 
	 * @param Url Avatar url or shortcode.
	 * @param OnLoadCompleted Success callback. Called when the avatar asset is downloaded and the skeletal mesh is set.
	 * @param OnLoadFailed Failure callback. If the avatar fails to load, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load New Avatar", AutoCreateRefTerm = "OnLoadCompleted,OnLoadFailed"))
	void LoadNewAvatar(const FString& Url, const FAvatarLoadCompleted& OnLoadCompleted, const FAvatarLoadFailed& OnLoadFailed);

	/**
	 * Loads the rendered image of the avatar from the server. By setting the SceneType the avatar can be rendered in different scenes.
	 * 
	 * @param SceneType The type of the scene where the avatar should be rendered.
	 * @param OnCompleted Success callback. Called when the render is loaded and provides the avatar texture as an argument.
	 * @param OnFailed Failure callback. If the render operation fails, the failure callback will be called.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Render", AutoCreateRefTerm = "OnCompleted, OnFailed"))
	void LoadRender(const ERenderSceneType& SceneType, const FDownloadImageCompleted& OnCompleted, const FDownloadImageFailed& OnFailed);

	/** The avatar url or shortcode. It's used to load the avatar from the web. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	FString UrlShortcode;

	/** Provides read-only information about the loaded avatar. Such as the type of the avatar, outfit and gender. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ready Player Me")
	FAvatarMetadata AvatarMetadata;

	/** It provides a flexibility to chose the skeleton that will be used for the loaded avatar.
	 * If it's not set the default skeleton will be used for the loaded avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	USkeleton* TargetSkeleton;

	/** Avatar configuration asset data. Used to load the avatar with the specific configs.
	 * If no config is set, the partner specific configs will be used for loading the avatar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	class UReadyPlayerMeAvatarConfig* AvatarConfig;

	/**
	 * Skeletal mesh component used for setting the skeletal mesh of the loaded avatar.
	 * If not set, It will be initialised with the skeletal mesh component of the parent actor.
	 * For runtime animation retargeting, if the actor has multiple skeletal mesh components, this property needs to be set.
	 */
	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	USkeletalMeshComponent* SkeletalMeshComponent;

	/**
	 * glTFRuntime skeletal mesh config that will be used for loading the avatar.
	 * This property should be changed only for very custom cases.
	 * @note Changing this property might break the avatar.
	 */
	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;

	/**
	 * Immediately cancels the avatar loading.
	 * When the garbage collector is removing the AvatarLoader, avatar loading gets automatically cancelled.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Cancel Avatar"))
	void CancelAvatarLoad();

private:
	UPROPERTY()
	class UReadyPlayerMeAvatarLoader* AvatarLoader;

	UPROPERTY()
	class UReadyPlayerMeRenderLoader* RenderLoader;

	UFUNCTION()
	void OnAvatarDownloaded(UglTFRuntimeAsset* Asset, const FAvatarMetadata& Metadata);

	UFUNCTION()
	void OnSkeletalMeshLoaded(USkeletalMesh* SkeletalMesh);

	void InitSkeletalMeshComponent();

	void LoadSkeletalMesh(UglTFRuntimeAsset* Asset);

	FAvatarDownloadCompleted OnAvatarDownloadCompleted;

	FAvatarLoadCompleted OnAvatarLoadCompleted;

	FglTFRuntimeSkeletalMeshAsync OnSkeletalMeshCallback;
};
