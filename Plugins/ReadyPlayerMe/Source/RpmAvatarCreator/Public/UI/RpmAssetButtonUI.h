// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmIconUI.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmAssetButtonUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAssetButtonSelected, const FRpmPartnerAsset&, Asset);

UCLASS(Abstract)
class RPMAVATARCREATOR_API URpmAssetButtonUI : public URpmIconUI
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Set Selected"))
	void SetSelected(bool Selected);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Update UI"))
	void UpdateUI();

	UPROPERTY(BlueprintCallable, Category = "Ready Player Me")
	FAssetButtonSelected AssetButtonSelected;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	FRpmPartnerAsset Asset;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	bool bIsSelected;
};
