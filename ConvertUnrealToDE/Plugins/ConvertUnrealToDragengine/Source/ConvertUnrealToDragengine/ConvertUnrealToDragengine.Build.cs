// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ConvertUnrealToDragengine : ModuleRules
{
	public ConvertUnrealToDragengine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicAdditionalLibraries.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "ThirdParty", "Dragengine", "lib", "dragengine.lib")
			}
			);

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "ThirdParty", "Dragengine", "include")
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"EditorFramework",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
			}
			);
		
		PublicDelayLoadDLLs.AddRange(
			new string[]
			{
				"dragengine.dll"
			});

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}
