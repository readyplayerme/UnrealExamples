// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMe.h"
#include "ReadyPlayerMeTypes.h"

DEFINE_LOG_CATEGORY(LogReadyPlayerMe);

#define LOCTEXT_NAMESPACE "FReadyPlayerMeModule"

void FReadyPlayerMeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FReadyPlayerMeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FReadyPlayerMeModule, ReadyPlayerMe)