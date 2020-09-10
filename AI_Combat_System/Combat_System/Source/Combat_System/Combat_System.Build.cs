// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Combat_System : ModuleRules
{
	public Combat_System(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
