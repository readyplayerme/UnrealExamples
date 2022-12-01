// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"

class FReadyPlayerMePluginInfo
{
public:
	static FString GetPluginVersion()
	{
		// Implementation needs to be in the header, because the editor module needs to access it.
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(GetRPMPluginName());
		if (Plugin)
		{
			return Plugin->GetDescriptor().VersionName;
		}
		return "";
	}

	static bool IsCppPlugin()
	{
		// Implementation needs to be in the header, because the editor module needs to access it.
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(GetRPMPluginName());
		if (Plugin)
		{
			return Plugin->GetType() == EPluginType::Project;
		}
		return false;
	}

	static bool IsDracoPluginIncluded()
	{
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(GetDracoPluginName());
		return Plugin.IsValid();
	}

	static FString GetRPMPluginName()
	{
		return "ReadyPlayerMe";
	}

	static FString GetDracoPluginName()
	{
		return "glTFRuntimeDraco";
	}
};
