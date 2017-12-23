// Copyright Edwin Zhang

using UnrealBuildTool;
using System.Collections.Generic;

public class PolyTerrainEditorTarget : TargetRules
{
	public PolyTerrainEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "PolyTerrain" } );
	}
}
