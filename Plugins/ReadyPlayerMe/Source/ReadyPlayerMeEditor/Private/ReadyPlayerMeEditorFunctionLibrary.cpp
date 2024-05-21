// Copyright © 2024 Ready Player Me


#include "ReadyPlayerMeEditorFunctionLibrary.h"

#include "EditorUtilitySubsystem.h"
#include "Editor.h"
#include "ReadyPlayerMeEditorSettings.h"
#include "ReadyPlayerMeSettings.h"
#include "Analytics/AnalyticsEventLogger.h"
#include "Analytics/AnalyticsSetup.h"
#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION > 4
#include "LevelEditorSubsystem.h"
#endif

void UReadyPlayerMeEditorFunctionLibrary::SetRpmSettings(const FString& Subdomain, const FString& AppId)
{
	UReadyPlayerMeSettings* Settings = GetMutableDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		Settings->Subdomain = Subdomain;
		Settings->AppId = AppId;
#if ENGINE_MAJOR_VERSION > 4
		Settings->TryUpdateDefaultConfigFile();
#else
		Settings->UpdateDefaultConfigFile();
#endif
		FAnalyticsSetup::RemoveWidget();
	}
}

void UReadyPlayerMeEditorFunctionLibrary::EnableAnalytics()
{
	UReadyPlayerMeEditorSettings* Settings = GetMutableDefault<UReadyPlayerMeEditorSettings>();
	if (Settings)
	{
		Settings->bEnableAnalytics = true;
#if ENGINE_MAJOR_VERSION > 4
		Settings->TryUpdateDefaultConfigFile();
#else
		Settings->UpdateDefaultConfigFile();
#endif
		FAnalyticsEventLogger::Get().EnableAnalytics();
		FAnalyticsSetup::RemoveWidget();
	}
}

FString UReadyPlayerMeEditorFunctionLibrary::GetSubdomain()
{
	const UReadyPlayerMeSettings* Settings = GetDefault<UReadyPlayerMeSettings>();
	if (Settings)
	{
		return Settings->Subdomain;
	}
	return {};
}

void UReadyPlayerMeEditorFunctionLibrary::LogRpmEvent(ERpmAnalyticsEventType EventType)
{
	FAnalyticsEventLogger::Get().LogEvent(EventType);
}

void UReadyPlayerMeEditorFunctionLibrary::CloseEditorWidget(const FString& Name)
{
	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	if (IsValid(EditorUtilitySubsystem))
	{
		auto Found = EditorUtilitySubsystem->RegisteredTabs.FilterByPredicate([Name](const auto& Pair){ return Pair.Key.ToString().Contains(Name);});
		if (Found.Num() != 0)
		{
			EditorUtilitySubsystem->CloseTabByID(Found.begin()->Key);
		}
	}
}

void UReadyPlayerMeEditorFunctionLibrary::LoadQuickStartLevel(const FString& LevelPath)
{
#if ENGINE_MAJOR_VERSION > 4
	if (ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>())
	{
		LevelEditorSubsystem->LoadLevel(LevelPath);
	}
#endif
}