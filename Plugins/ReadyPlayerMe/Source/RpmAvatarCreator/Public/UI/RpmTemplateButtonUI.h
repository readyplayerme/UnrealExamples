// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "RpmIconUI.h"
#include "RpmAvatarCreatorTypes.h"
#include "RpmTemplateButtonUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTemplateButtonSelected, const FRpmAvatarTemplate&, Template);

UCLASS(Abstract)
class RPMAVATARCREATOR_API URpmTemplateButtonUI : public URpmIconUI
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Set Selected"))
	void SetSelected(bool Selected);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ready Player Me", meta = (DisplayName = "Update UI"))
	void UpdateUI();

	UPROPERTY(BlueprintCallable, Category = "Ready Player Me")
	FTemplateButtonSelected TemplateButtonSelected;

	UPROPERTY(BlueprintReadWrite, Category = "Ready Player Me")
	FRpmAvatarTemplate Template;
};
