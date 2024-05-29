// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"

class FAnalyticsSetup
{
public:
	static void Startup();
	static void RemoveWidget();
	static void AddWidget();

private:
	static void SetupLogger();
	static void SetupWidget();
	static void SetupSettingsChangedDelegate();
};
