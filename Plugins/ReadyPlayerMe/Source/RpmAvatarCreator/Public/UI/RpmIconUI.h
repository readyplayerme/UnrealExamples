// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RpmIconUI.generated.h"

UCLASS(Abstract)
class RPMAVATARCREATOR_API URpmIconUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Set Icon Texture"))
	void SetIconTexture(UTexture2D* Texture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ready Player Me")
	int32 IconSize = 64;
};
