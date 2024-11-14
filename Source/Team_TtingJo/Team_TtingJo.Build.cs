// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team_TtingJo : ModuleRules
{
	public Team_TtingJo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
