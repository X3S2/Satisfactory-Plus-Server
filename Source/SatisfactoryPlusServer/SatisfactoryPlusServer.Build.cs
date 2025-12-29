// Copyright (c) 2025 X3S2. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class SatisfactoryPlusServer : ModuleRules
{
	public SatisfactoryPlusServer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"SML",
			"FactoryGame"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Json",
			"JsonUtilities"
		});

		// Server-specific configuration
		if (Target.Type == TargetType.Server)
		{
			PublicDefinitions.Add("UE_SERVER=1");
		}
	}
}
