// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SystemInformation : ModuleRules
{
	public SystemInformation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[]{"Engine", "Core", "CoreUObject", "Json", "JsonUtilities"});
	}
}
