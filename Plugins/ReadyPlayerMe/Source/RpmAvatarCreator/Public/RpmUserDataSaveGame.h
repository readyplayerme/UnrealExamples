// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmUserDataSaveGame.generated.h"

UCLASS()
class RPMAVATARCREATOR_API URpmUserDataSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Ready Player Me")
	FRpmUserData UserData;
};
