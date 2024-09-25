// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConvertUnrealToDragengine.h"
#include "ConvertUnrealToDragengineStyle.h"
#include "ConvertUnrealToDragengineCommands.h"
#include "SWindowMenu.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ConvertUnrealToDragengineTabName("ConvertUnrealToDragengine");

#define LOCTEXT_NAMESPACE "FConvertUnrealToDragengineModule"

void FConvertUnrealToDragengineModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FConvertUnrealToDragengineStyle::Initialize();
	FConvertUnrealToDragengineStyle::ReloadTextures();

	FConvertUnrealToDragengineCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FConvertUnrealToDragengineCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FConvertUnrealToDragengineModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FConvertUnrealToDragengineModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ConvertUnrealToDragengineTabName, FOnSpawnTab::CreateRaw(this, &FConvertUnrealToDragengineModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FConvertUnrealToDragengineTabTitle", "Unreal -> Drag[en]gine"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FConvertUnrealToDragengineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FConvertUnrealToDragengineStyle::Shutdown();

	FConvertUnrealToDragengineCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ConvertUnrealToDragengineTabName);
}

TSharedRef<SDockTab> FConvertUnrealToDragengineModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SWindowMenu)
		];
}

void FConvertUnrealToDragengineModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ConvertUnrealToDragengineTabName);
}

void FConvertUnrealToDragengineModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FConvertUnrealToDragengineCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FConvertUnrealToDragengineCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FConvertUnrealToDragengineModule, ConvertUnrealToDragengine)