// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IPluginManager.h"

class FPluginInfo
{
public:
	static FString GetPluginVersion(const FString& Name)
	{
		// Implementation needs to be in the header, because the editor module needs to access it.
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(Name);
		if (Plugin)
		{
			return Plugin->GetDescriptor().VersionName;
		}
		return "";
	}

	static FString GetRpmPluginVersion()
	{
		return GetPluginVersion(GetRPMPluginName());
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
