// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class COAEditorTarget : TargetRules
{
	public COAEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		CppStandard = CppStandardVersion.Default;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bLegacyParentIncludePaths = false;
		WindowsPlatform.bStrictConformanceMode = true;
		bOverrideBuildEnvironment = true;

		ExtraModuleNames.AddRange( new string[] { "COA" } );
	}
}
