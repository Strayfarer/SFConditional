// Copyright Strayfarer & Contributors. Released under the MIT license.

using UnrealBuildTool;

public class SFConditionalTests : ModuleRules
{
    public SFConditionalTests(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            [
                "Core"
            ]
        );

        PrivateDependencyModuleNames.AddRange(
            [
                "CoreUObject",
                "Engine",
                "SFConditional"
            ]
        );
    }
}