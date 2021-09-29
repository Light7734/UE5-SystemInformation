// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SystemInformation : ModuleRules
{
	public SystemInformation(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Engine" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Core" });
	}
}
