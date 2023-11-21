// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmAvatarCreatorTypes.h"
#include "Blueprint/UserWidget.h"
#include "RpmColorButtonUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FColorButtonSelected, ERpmPartnerAssetColor, AssetColor, int32, ColorIndex);

UCLASS(Abstract)
class RPMAVATARCREATOR_API URpmColorButtonUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Set Selected"))
	void SetSelected(bool IsSelected);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Update UI"))
	void UpdateUI();

	UPROPERTY(BlueprintCallable, Category = "Ready Player Me")
	FColorButtonSelected ColorButtonSelected;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	ERpmPartnerAssetColor AssetColor;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	int32 ColorIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	FColor RgbColor;
};
