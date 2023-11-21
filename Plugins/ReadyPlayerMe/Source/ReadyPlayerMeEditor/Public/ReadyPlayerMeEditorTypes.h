// Copyright © 2021++ Ready Player Me
#pragma once

#include "ReadyPlayerMeEditorTypes.generated.h"

UENUM(BlueprintType)
enum class ERpmAnalyticsEventType : uint8
{
	OpenProject UMETA(DisplayName = "Open Project"),
	CloseProject UMETA(DisplayName = "Close Project"),
	EnableCaching UMETA(DisplayName = "Enable Caching"),
	SetUserProperties UMETA(DisplayName = "Set User Properties"),
	AllowLogging UMETA(DisplayName = "Allow Logging"),
	OpenIntegrationGuide UMETA(DisplayName = "Open Integration Guide"),
	LoadQuickStartScene UMETA(DisplayName = "Load Quick Start Scene"),
	OpenAvatarDocumentation UMETA(DisplayName = "Open Avatar Documentation"),
	OpenSamplesDocumentation UMETA(DisplayName = "Open Samples Documentation"),
	OpenAnimationDocumentation UMETA(DisplayName = "Open Animation Documentation"),
	OpenAvatarCreatorDocumentation UMETA(DisplayName = "Open Avatar Creator Documentation"),
	ViewPrivacyPolicy UMETA(DisplayName = "View Privacy Policy"),
};
