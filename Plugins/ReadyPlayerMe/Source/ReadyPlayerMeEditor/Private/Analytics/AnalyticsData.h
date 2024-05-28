// Copyright © 2024 Ready Player Me

#pragma once

#include "CoreMinimal.h"

struct FAnalyticsData
{
	FString AppName;
	FString SDKVersion;
	FString SdkTarget;
	FString Subdomain;
	FString AppId;
	FString UnrealVersion;
	FString Platform;
	FString DeviceId;
	FString AppIdentifier;
	bool bIsCppPlugin;

	FAnalyticsData();
};
