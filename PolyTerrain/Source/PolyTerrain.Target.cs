// Copyright Edwin Zhang

using UnrealBuildTool;
using System.Collections.Generic;

public class PolyTerrainTarget : TargetRules
{
	public PolyTerrainTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "PolyTerrain" } );
	}
}
