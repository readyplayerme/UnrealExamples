// Copyright © 2023++ Ready Player Me

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRpmAvatarCreatorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
