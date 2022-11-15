// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReadyPlayerMeActor.generated.h"

/** Intended to be used as an actor for runtime loading and displaying the avatars. */
UCLASS(BlueprintType)
class READYPLAYERME_API AReadyPlayerMeActor : public AActor
{
	GENERATED_BODY()

public:
	/** Default constructor. Sets default values for this actor's properties. */
	AReadyPlayerMeActor();

	/** The default SkeletalMeshComponent. The skeletal mesh will be set during the avatar loading process. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ready Player Me", meta = (ExposeFunctionCategories = "Ready Player Me", AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMeshComponent;

	/** Handles the loading and setup of the avatar. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ready Player Me", meta = (ExposeFunctionCategories = "Ready Player Me", AllowPrivateAccess = "true"))
	class UReadyPlayerMeComponent* ReadyPlayerMeComponent;
};
