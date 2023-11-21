// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ReadyPlayerMeEditorSettings.generated.h"

UCLASS(config=EditorPerProjectUserSettings, meta = (DisplayName="Ready Player Me"))

class READYPLAYERMEEDITOR_API UReadyPlayerMeEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UReadyPlayerMeEditorSettings();

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Privacy")
	bool bEnableAnalytics;

	UPROPERTY(Config)
	FString AnalyticsTarget;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
