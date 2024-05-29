// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ReadyPlayerMePreloadAction.generated.h"

USTRUCT(BlueprintType)
struct FAvatarPreloadData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	TArray<FString> AvatarIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	class UReadyPlayerMeAvatarConfig* AvatarConfig = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	USkeleton* TargetSkeleton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ready Player Me")
	class UReadyPlayerMeAutoLodConfig* AutoLodConfig = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAvatarPreloadCompleted);

/**
 * Async action, responsible for preloading avatars in memory to be used in the same game session.
 */
UCLASS()
class READYPLAYERME_API UReadyPlayerMePreloadAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/**
	 * Preloads the avatar data so the avatars would be instantiated instantly when loading them from the ReadyPlayerMeComponent.
	 * 
	 * @param WorldContextObject Object is passed automatically through the blueprint interface.
	 * @param PreloadData List of avatar data needed for preloading.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "Ready Player Me", AutoCreateRefTerm = "PreloadData", WorldContext = "WorldContextObject"))
	static UReadyPlayerMePreloadAction* PreloadAvatarsAsync(UObject* WorldContextObject, const FAvatarPreloadData& PreloadData);
	
	/** Success callback. Called when the avatars are preloaded. */
	UPROPERTY(BlueprintAssignable)
	FAvatarPreloadCompleted OnCompleted;

	/** Failure callback. If the preload operation fails, the failure callback will be called. */
	UPROPERTY(BlueprintAssignable)
	FAvatarPreloadCompleted OnFailed;

	/** Execute the async action */
	virtual void Activate() override;

private:
	virtual void BeginDestroy() override;

	UFUNCTION()
	void OnAvatarDownloaded(USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata);

	UFUNCTION()
	void OnAvatarLoadFailed(const FString& ErrorMessage);

	void Preload();
	void CompleteLoading();

private:
	UPROPERTY()
	TMap<FString, class UReadyPlayerMeAvatarLoader*> AvatarLoaders;

	UPROPERTY()
	class UReadyPlayerMeMemoryCache* MemoryCache = nullptr;

	FAvatarPreloadData PreloadData;
	int32 FailedRequestCount = 0;
};
