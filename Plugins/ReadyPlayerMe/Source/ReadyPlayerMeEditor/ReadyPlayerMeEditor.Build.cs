// Copyright © 2024 Ready Player Me

using UnrealBuildTool;

public class ReadyPlayerMeEditor : ModuleRules
{
	public ReadyPlayerMeEditor(ReadOnlyTargetRules Target) : base(Target) 
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);

		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ReadyPlayerMe"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				"HTTP",
				"Blutility",
				"Projects",
				"DeveloperSettings",
				"UnrealEd"
			}
		);

#if UE_5_0_OR_LATER
		PrivateDependencyModuleNames.Add("DeveloperToolSettings");
		PrivateDependencyModuleNames.Add("LevelEditor");
#endif

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
