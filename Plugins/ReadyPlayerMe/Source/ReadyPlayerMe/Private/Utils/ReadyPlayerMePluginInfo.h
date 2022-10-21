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
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(GetPluginName());
		if (Plugin)
		{
			return Plugin->GetDescriptor().VersionName;
		}
		return "";
	}

	static FString GetPluginName()
	{
		return "ReadyPlayerMe";
	}
};
