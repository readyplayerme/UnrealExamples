// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadyPlayerMeFunctionLibrary.generated.h"

/**
 * Static functions to be used from the blueprint.
 */
UCLASS()
class READYPLAYERME_API UReadyPlayerMeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Clears all avatars from the persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me | Avatar Caching", meta = (DisplayName = "Clear Avatar Cache", WorldContext = "WorldContextObject"))
	static void ClearAvatarCache(const UObject* WorldContextObject);

	/** Clears a specific avatar from persistent cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me | Avatar Caching", meta = (DisplayName = "Clear Avatar From Cache", WorldContext = "WorldContextObject"))
	static void ClearAvatarFromCache(const UObject* WorldContextObject, const FString& AvatarId);

	/** Is there any avatars present in the persistent cache. */
	UFUNCTION(BlueprintPure, Category = "Ready Player Me | Avatar Caching", meta = (DisplayName = "Is Avatar Cache Empty"))
	static bool IsAvatarCacheEmpty();

	/** Total Avatars stored in persistent cache. */
	UFUNCTION(BlueprintPure, Category = "Ready Player Me | Avatar Caching", meta = (DisplayName = "Get Cached Avatar Count"))
	static int32 GetCachedAvatarCount();

	/** Total Avatars stored in persistent cache. */
	UFUNCTION(BlueprintPure, Category = "Ready Player Me | Avatar Caching", meta = (DisplayName = "Get Avatar Cache Size"))
	static int64 GetAvatarCacheSize();

	/** Get unique id of the avatar. */
	UFUNCTION(BlueprintPure, Category = "Ready Player Me", meta = (DisplayName = "Get Avatar Id"))
	static FString GetAvatarId(const FString& Url);

	/** Clears all avatars from the memory cache. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me | Memory", meta = (DisplayName = "Clear Avatars From Memory", WorldContext = "WorldContextObject"))
	static void ClearAvatarsFromMemory(const UObject* WorldContextObject);

	/** Clears a specific avatar from the memory. */
	UFUNCTION(BlueprintCallable, Category = "Ready Player Me | Memory", meta = (DisplayName = "Clear Avatar From Memory", WorldContext = "WorldContextObject"))
	static void ClearAvatarFromMemory(const UObject* WorldContextObject, const FString& AvatarId);
};
