// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Team_TtingJo : ModuleRules
{
	public Team_TtingJo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"Niagara",
            "GameplayCameras", 
			"TemplateSequence"
        });

		//JHS : 왜인지 모르겠지만 헤더파일에 대한 경로오류가 발생해서 수동으로 경로를 입력해 준것
		PrivateIncludePaths.Add("Team_TtingJo/JHS/");

        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Pulbic");
        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Pravite");
        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Classes");
    }
}
