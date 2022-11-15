// Copyright © 2021++ Ready Player Me

#include "ReadyPlayerMeAnalyticsData.h"
#include "ReadyPlayerMe/Private/Utils/ReadyPlayerMePluginInfo.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/EngineVersion.h"

static const FString SDK_TARGET = "Unreal";
static const FString SUBDOMAIN = "Demo";

namespace
{

	FString GetDeviceId()
	{
		const TArray<uint8> MacAddress = FPlatformMisc::GetMacAddress();
		return FMD5::HashBytes(MacAddress.GetData(), MacAddress.Num());
	}
}

FReadyPlayerMeAnalyticsData::FReadyPlayerMeAnalyticsData()
{
	const auto EngineVersion = FEngineVersion::Current();
	AppName = FApp::GetProjectName();
	SDKVersion = FReadyPlayerMePluginInfo::GetPluginVersion();
	SdkTarget = SDK_TARGET;
	Subdomain = SUBDOMAIN;
	UnrealVersion = FString::Printf(TEXT("%d.%d.%d"), EngineVersion.GetMajor(), EngineVersion.GetMinor(), EngineVersion.GetPatch());
	Platform = UGameplayStatics::GetPlatformName();
	DeviceId = GetDeviceId();
	AppIdentifier = UKismetSystemLibrary::GetGameBundleId();
	bIsCppPlugin = FReadyPlayerMePluginInfo::IsCppPlugin();
}
