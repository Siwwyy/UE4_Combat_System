// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Combat_SystemTarget : TargetRules
{
	public Combat_SystemTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Combat_System");
	}
}
