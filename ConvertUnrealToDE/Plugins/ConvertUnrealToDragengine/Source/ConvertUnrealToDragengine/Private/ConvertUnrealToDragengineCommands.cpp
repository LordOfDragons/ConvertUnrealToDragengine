// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConvertUnrealToDragengineCommands.h"

#define LOCTEXT_NAMESPACE "FConvertUnrealToDragengineModule"

void FConvertUnrealToDragengineCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ConvertUnrealToDragengine", "Bring up ConvertUnrealToDragengine window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
