// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConvertUnrealToDragengineStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FConvertUnrealToDragengineStyle::StyleInstance = nullptr;

void FConvertUnrealToDragengineStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FConvertUnrealToDragengineStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FConvertUnrealToDragengineStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ConvertUnrealToDragengineStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FConvertUnrealToDragengineStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ConvertUnrealToDragengineStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ConvertUnrealToDragengine")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ConvertUnrealToDragengine.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FConvertUnrealToDragengineStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FConvertUnrealToDragengineStyle::Get()
{
	return *StyleInstance;
}
