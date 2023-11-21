// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "ReadyPlayerMeTypes.h"
#include "glTFRuntimeParser.h"
#include "ReadyPlayerMeGlbLoader.generated.h"

UCLASS()
class UReadyPlayerMeGlbLoader : public UObject
{
	GENERATED_BODY()

public:
	UReadyPlayerMeGlbLoader();

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Glb From File"))
	void LoadFromFile(const FString& LocalModelPath, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Load Glb From Data"))
	void LoadFromData(const TArray<uint8>& Data, EAvatarBodyType BodyType, const FGlbLoadCompleted& LoadCompleted);

	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	USkeleton* TargetSkeleton;

	UPROPERTY(BlueprintReadWrite, Category="Ready Player Me")
	FglTFRuntimeSkeletalMeshConfig SkeletalMeshConfig;

private:
	UFUNCTION()
	void OnSkeletalMeshLoaded(USkeletalMesh* SkeletalMesh);

	void LoadSkeletalMesh(class UglTFRuntimeAsset* Asset, EAvatarBodyType BodyType);

	FglTFRuntimeSkeletalMeshAsync OnSkeletalMeshCallback;
	FGlbLoadCompleted OnLoadCompleted;
};
