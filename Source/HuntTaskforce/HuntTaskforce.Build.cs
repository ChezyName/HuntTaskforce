// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HuntTaskforce : ModuleRules
{
	public HuntTaskforce(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","OnlineSubsystem","OnlineSubsystemUtils","Voice"});
		
	}
}
