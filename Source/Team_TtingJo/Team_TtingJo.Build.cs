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

		//JHS : ������ �𸣰����� ������Ͽ� ���� ��ο����� �߻��ؼ� �������� ��θ� �Է��� �ذ�
		PrivateIncludePaths.Add("Team_TtingJo/JHS/");

        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Pulbic");
        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Pravite");
        Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Classes");
    }
}
