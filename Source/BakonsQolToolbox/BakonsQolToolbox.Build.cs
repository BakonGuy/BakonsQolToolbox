// Some copyright should be here...

using UnrealBuildTool;

public class BakonsQolToolbox : ModuleRules
{
	public BakonsQolToolbox(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", });
		PrivateDependencyModuleNames.AddRange(new string[] { "Projects", "CoreUObject", "Engine", "Slate", "SlateCore", });
		DynamicallyLoadedModuleNames.AddRange(new string[] { });

		if( Target.bBuildEditor )
		{
			PrivateDependencyModuleNames.Add("UnrealEd");
		}
	}
}
