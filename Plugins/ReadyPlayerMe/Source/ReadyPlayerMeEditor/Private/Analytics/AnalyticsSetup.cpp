// Copyright © 2024 Ready Player Me

#include "AnalyticsSetup.h"

#include "ReadyPlayerMeEditorSettings.h"
#include "AnalyticsEventLogger.h"
#include "EditorUtilitySubsystem.h"
#include "ReadyPlayerMeSettings.h"

static const FString STARTUP_BLUEPRINT = "/ReadyPlayerMe/ReadyPlayerMe/Editor/BP_RPM_StartupEditor.BP_RPM_StartupEditor";
static const FName SETTINGS_ENABLE_CACHING = "bEnableAvatarCaching";

namespace
{
	void ProjectSettingsChanged(const FName& PropertyName, UReadyPlayerMeSettings* Settings)
	{
		if (PropertyName == SETTINGS_ENABLE_CACHING)
		{
			FAnalyticsEventLogger::Get().LogEnableAvatarCaching(Settings->AvatarCacheSettings.bEnableAvatarCaching);
		}
	}
}

void FAnalyticsSetup::Startup()
{
	SetupSettingsChangedDelegate();
	SetupLogger();
	SetupWidget();
}

void FAnalyticsSetup::SetupSettingsChangedDelegate()
{
	UReadyPlayerMeSettings* Settings = GetMutableDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		Settings->SettingsChanged.BindStatic(&ProjectSettingsChanged, Settings);
	}
}

void FAnalyticsSetup::SetupLogger()
{
	const auto EditorSettings = GetDefault<UReadyPlayerMeEditorSettings>();
	auto& Logger = FAnalyticsEventLogger::Get();
	Logger.SetEnabled(EditorSettings->bEnableAnalytics);
	if (!EditorSettings->AnalyticsTarget.IsEmpty())
	{
		Logger.SetAnalyticsTarget(EditorSettings->AnalyticsTarget);
	}
}

void FAnalyticsSetup::SetupWidget()
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (!Settings)
	{
		return;
	}
	if (Settings->Subdomain.IsEmpty())
	{
		AddWidget();
	}
	else
	{
		RemoveWidget();
	}
}

void FAnalyticsSetup::AddWidget()
{
	const auto EditorUtilitySubsystem = GetMutableDefault<UEditorUtilitySubsystem>();
	if (!EditorUtilitySubsystem->StartupObjects.Contains(STARTUP_BLUEPRINT))
	{
		EditorUtilitySubsystem->StartupObjects.Add(STARTUP_BLUEPRINT);
		EditorUtilitySubsystem->SaveConfig();
	}
}

void FAnalyticsSetup::RemoveWidget()
{
	const auto EditorUtilitySubsystem = GetMutableDefault<UEditorUtilitySubsystem>();
	if (EditorUtilitySubsystem->StartupObjects.Contains(STARTUP_BLUEPRINT))
	{
		EditorUtilitySubsystem->StartupObjects.Remove(STARTUP_BLUEPRINT);
		EditorUtilitySubsystem->SaveConfig();
	}
}
