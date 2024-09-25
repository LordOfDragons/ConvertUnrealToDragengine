// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ConvertUnrealToDragengineStyle.h"

class FConvertUnrealToDragengineCommands : public TCommands<FConvertUnrealToDragengineCommands>
{
public:

	FConvertUnrealToDragengineCommands()
		: TCommands<FConvertUnrealToDragengineCommands>(TEXT("ConvertUnrealToDragengine"), NSLOCTEXT("Contexts", "ConvertUnrealToDragengine", "ConvertUnrealToDragengine Plugin"), NAME_None, FConvertUnrealToDragengineStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};