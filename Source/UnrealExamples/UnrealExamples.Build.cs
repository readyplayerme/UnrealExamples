// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealExamples : ModuleRules
{
	public UnrealExamples(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { "ReadyPlayerMe" });

		// Dependencies Web Browser
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
