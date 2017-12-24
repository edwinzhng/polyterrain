// Copyright Edwin Zhang

using System.IO;
using UnrealBuildTool;

public class PolyTerrain : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; ; }
    }

    private string LibraryPath
    {
        get { return Path.Combine(ModulePath, "../../Libraries/"); }
    }

    public PolyTerrain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });
        switch (Target.Platform)
        {
            // 64-bit Windows
            case UnrealTargetPlatform.Win64:
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "accidental-noise-library", "build", "ANL", "x64", "ANL.lib"));
                break;

            // 32-bit Windows
            case UnrealTargetPlatform.Win32:
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "accidental-noise-library", "build", "ANL", "x86", "ANL.lib"));
                break;

            // Mac
            case UnrealTargetPlatform.Mac:
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "accidental-noise-library", "build", "ANL", "Universal", "libANL.a"));
                break;

            // Linux
            case UnrealTargetPlatform.Linux:
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "accidental-noise-library", "build", "ANL", "x64", "libANL.a"));
                break;

            default:
                break;
        }

        PublicIncludePaths.Add(Path.Combine(LibraryPath, "polyvox", "include"));
        PublicIncludePaths.Add(Path.Combine(LibraryPath, "accidental-noise-library"));
    }
}
