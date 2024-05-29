// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ReadyPlayerMeGameSubsystem.generated.h"

UCLASS()
class UReadyPlayerMeGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UReadyPlayerMeGameSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintReadOnly, Category="Ready Player Me")
	class UReadyPlayerMeMemoryCache* MemoryCache;

	TSharedPtr<class FAvatarManifest> AvatarManifest;
};