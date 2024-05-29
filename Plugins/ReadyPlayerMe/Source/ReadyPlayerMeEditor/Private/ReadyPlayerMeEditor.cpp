// Copyright © 2024 Ready Player Me

#include "ReadyPlayerMeEditor.h"

#include "Analytics/AnalyticsSetup.h"
#include "Analytics/AnalyticsEventLogger.h"
#include "Settings/ProjectPackagingSettings.h"
#include "Runtime/Launch/Resources/Version.h"

#define LOCTEXT_NAMESPACE "FReadyPlayerMeEditorModule"

namespace
{
	void AddGLTFRuntimeToCookingDirectories()
	{
		UProjectPackagingSettings* PackagingSetting = GetMutableDefault<UProjectPackagingSettings>();
		if (!PackagingSetting->DirectoriesToAlwaysCook.ContainsByPredicate([](const auto& Item){ return Item.Path == "/ReadyPlayerMe/glTFRuntime";} ))
		{
			PackagingSetting->DirectoriesToAlwaysCook.Add(FDirectoryPath{"/ReadyPlayerMe/glTFRuntime"});
#if ENGINE_MAJOR_VERSION > 4
			PackagingSetting->TryUpdateDefaultConfigFile();
#else
			PackagingSetting->UpdateDefaultConfigFile();
#endif
		}
	}
}

void FReadyPlayerMeEditorModule::StartupModule()
{
	AddGLTFRuntimeToCookingDirectories();
	FAnalyticsSetup::Startup();
	FAnalyticsEventLogger::Get().LogProperties();
	FAnalyticsEventLogger::Get().LogEvent(ERpmAnalyticsEventType::OpenProject);
}

void FReadyPlayerMeEditorModule::ShutdownModule()
{
	FAnalyticsEventLogger::Get().LogEvent(ERpmAnalyticsEventType::CloseProject);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FReadyPlayerMeEditorModule, ReadyPlayerMeEditor)
