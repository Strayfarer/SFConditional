// Copyright Strayfarer & Contributors. Released under the MIT license.

using UnrealBuildTool;

public class SFConditional : ModuleRules
{
	public SFConditional(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bAllowUETypesInNamespaces = true;
		
		PublicDependencyModuleNames.AddRange(
			[
				"Core", 
				"GameplayDebugger"
			]
		);
			
		PrivateDependencyModuleNames.AddRange(
			[
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GameplayDebugger"
			]
		);
	}
}
