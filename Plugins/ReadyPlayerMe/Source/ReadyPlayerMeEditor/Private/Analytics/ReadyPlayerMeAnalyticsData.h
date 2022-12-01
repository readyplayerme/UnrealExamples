// Copyright © 2021++ Ready Player Me

#pragma once

#include "CoreMinimal.h"

struct FReadyPlayerMeAnalyticsData
{
	FString AppName;
	FString SDKVersion;
	FString SdkTarget;
	FString Subdomain;
	FString UnrealVersion;
	FString Platform;
	FString DeviceId;
	FString AppIdentifier;
	bool bIsCppPlugin;

	FReadyPlayerMeAnalyticsData();
};
