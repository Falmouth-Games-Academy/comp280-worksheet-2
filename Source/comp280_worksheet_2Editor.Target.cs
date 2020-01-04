// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class comp280_worksheet_2EditorTarget : TargetRules
{
	public comp280_worksheet_2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "comp280_worksheet_2" } );
	}
}
