// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeAnalyticsSetup.h"

#include "ReadyPlayerMeEditorSettings.h"
#include "ReadyPlayerMeAnalyticsEventLogger.h"
#include "EditorUtilitySubsystem.h"
#include "ReadyPlayerMeSettings.h"

static const FString STARTUP_BLUEPRINT = "/ReadyPlayerMe/Editor/BP_RPM_StartupEditor.BP_RPM_StartupEditor";
static const FName SETTINGS_ENABLE_CACHING = "bEnableAvatarCaching";

namespace
{
	void ProjectSettingsChanged(const FName& PropertyName, UReadyPlayerMeSettings* Settings)
	{
		if (PropertyName == SETTINGS_ENABLE_CACHING)
		{
			FReadyPlayerMeAnalyticsEventLogger::Get().LogEnableAvatarCaching(Settings->bEnableAvatarCaching);
		}
	}
}

void FReadyPlayerMeAnalyticsSetup::Startup()
{
	SetupSettingsChangedDelegate();
	SetupLogger();
	SetupWidget();
}

void FReadyPlayerMeAnalyticsSetup::SetupSettingsChangedDelegate()
{
	UReadyPlayerMeSettings* Settings = GetMutableDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		Settings->SettingsChanged.BindStatic(&ProjectSettingsChanged, Settings);
	}
}

void FReadyPlayerMeAnalyticsSetup::SetupLogger()
{
	const auto EditorSettings = GetDefault<UReadyPlayerMeEditorSettings>();
	auto& Logger = FReadyPlayerMeAnalyticsEventLogger::Get();
	Logger.SetEnabled(EditorSettings->bEnableAnalytics);
	if (!EditorSettings->AnalyticsTarget.IsEmpty())
	{
		Logger.SetAnalyticsTarget(EditorSettings->AnalyticsTarget);
	}
}

void FReadyPlayerMeAnalyticsSetup::SetupWidget()
{
	const auto EditorSettings = GetDefault<UReadyPlayerMeEditorSettings>();
	if (EditorSettings->bDontAskAgain || EditorSettings->bEnableAnalytics)
	{
		RemoveWidget();
	}
	else
	{
		AddWidget();
	}
}

void FReadyPlayerMeAnalyticsSetup::AddWidget()
{
	const auto EditorUtilitySubsystem = GetMutableDefault<UEditorUtilitySubsystem>();
	if (!EditorUtilitySubsystem->StartupObjects.Contains(STARTUP_BLUEPRINT))
	{
		EditorUtilitySubsystem->StartupObjects.Add(STARTUP_BLUEPRINT);
		EditorUtilitySubsystem->SaveConfig();
	}
}

void FReadyPlayerMeAnalyticsSetup::RemoveWidget()
{
	const auto EditorUtilitySubsystem = GetMutableDefault<UEditorUtilitySubsystem>();
	if (EditorUtilitySubsystem->StartupObjects.Contains(STARTUP_BLUEPRINT))
	{
		EditorUtilitySubsystem->StartupObjects.Remove(STARTUP_BLUEPRINT);
		EditorUtilitySubsystem->SaveConfig();
	}
}
