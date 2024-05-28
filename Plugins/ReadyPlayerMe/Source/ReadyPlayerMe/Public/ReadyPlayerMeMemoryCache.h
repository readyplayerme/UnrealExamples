// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "ReadyPlayerMeMemoryCache.generated.h"

USTRUCT(BlueprintType)
struct FAvatarMemoryCacheData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString AvatarId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FString AvatarConfigHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReadyPlayerMe")
	FAvatarMetadata Metadata;
};

/**
 * Is used to preload avatars and store the cached skeletal meshes.
 * Cached avatars will be instantiated instantly. 
 */
UCLASS(Blueprintable, BlueprintType)
class READYPLAYERME_API UReadyPlayerMeMemoryCache : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Returns the preload avatar data for a specific avatar.
	 *
	 * @param AvatarId Avatar url.
	 * @param AvatarConfig Avatar config.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	FAvatarMemoryCacheData GetAvatarCacheData(const FString& AvatarId, UReadyPlayerMeAvatarConfig* AvatarConfig) const;

	/**
	 * Adds an already loaded avatar to the memory.
	 *
	 * @param AvatarId Avatar Id or url.
	 * @param AvatarConfig Avatar config.
	 * @param SkeletalMesh Preloaded skeletalMesh of the avatar.
	 * @param Metadata Preloaded avatar Metadata.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void AddAvatar(const FString& AvatarId, UReadyPlayerMeAvatarConfig* AvatarConfig, USkeletalMesh* SkeletalMesh, const FAvatarMetadata& Metadata);

	/**
	 * Removes specific avatar data from the memory.
	 *
	 * @param AvatarId Avatar Id or url.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void ClearAvatar(const FString& AvatarId);

	/** Clears all avatars from the memory. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me")
	void ClearAvatars();

	/** Avatar Data for all the preloaded avatars. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ReadyPlayerMe")
	TArray<FAvatarMemoryCacheData> CachedAvatars;
};
