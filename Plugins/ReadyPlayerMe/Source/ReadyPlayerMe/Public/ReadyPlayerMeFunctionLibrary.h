// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadyPlayerMeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class READYPLAYERME_API UReadyPlayerMeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Ready Player Me", meta = (DisplayName = "Clean Avatar Cache"))
	static void ClearAvatarCache();
	
};
