// Fill out your copyright notice in the Description page of Project Settings.

#include "SWindowMenu.h"
#include "SlateOptMacros.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"

#include <dragengine/app/deOSWindows.h>
#include <Winreg.h>

#define LOCTEXT_NAMESPACE "SWindowMenu"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SWindowMenu::Construct(const FArguments& InArgs)
{
	if (pDragengineLibrary.IsReady())
	{
		UE_LOG(LogTemp, Warning, TEXT("Drag[en]gine Ready"));
		UE_LOG(LogTemp, Warning, TEXT("- Engine Path: %s."), *pDragengineLibrary.GetPathDragengine());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Drag[en]gine Not Ready: "), *pDragengineLibrary.GetProblem());
	}

	ChildSlot
	[
	    SNew(SVerticalBox)
	    +SVerticalBox::Slot()
	    .AutoHeight()
	    [
	        SNew(SHorizontalBox)
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
			.AutoWidth()
			.Padding(0, 0, 10, 0)
	        [
	            SNew(STextBlock)
	            .Text(FText::FromString("Drag[en]gine Project"))
	        ]
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
	        [
	            SNew(SEditableTextBox)
					.Text(this, &SWindowMenu::GetPathDEProject)
					.HintText(LOCTEXT("PathDEProjectHint",
						"Full path to Drag[en]gine Project File"))
					.OnTextCommitted(this, &SWindowMenu::SetPathDEProject)
	        ]
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
			.AutoWidth()
	        [
	            SNew(SButton)
	            .Text(FText::FromString("..."))
				.OnClicked(this, &SWindowMenu::OnPathDEProjectSelect)
	        ]
	    ]
	    +SVerticalBox::Slot()
	    .AutoHeight()
	    [
	        SNew(SHorizontalBox)
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
	        [
	            SNew(STextBlock)
	            .Text(FText::FromString("Test Button"))
	        ]
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
	        [
	            SNew(SButton)
		        .Text(FText::FromString("Press Me"))
				.OnClicked(this, &SWindowMenu::OnTestButtonClicked)
	        ]
	    ]
	    +SVerticalBox::Slot()
	    .AutoHeight()
	    [
	        SNew(SHorizontalBox)
	        +SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
	        [
	            SNew(STextBlock)
	            .Text(FText::FromString("Test Checkbox"))
	        ]
	        + SHorizontalBox::Slot()
	        .VAlign(VAlign_Top)
	        [
	            SNew(SCheckBox)
					.OnCheckStateChanged(this, &SWindowMenu::OnTestCheckboxStateChanged)
					.IsChecked(this, &SWindowMenu::IsTestBoxChecked)
	        ]
	    ]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SWindowMenu::OnTestCheckboxStateChanged(ECheckBoxState NewState)
{
	bIsTestBoxChecked = NewState == ECheckBoxState::Checked ? true : false;
}
	 
ECheckBoxState SWindowMenu::IsTestBoxChecked() const
{
	return bIsTestBoxChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

FText SWindowMenu::GetPathDEProject() const
{
	return pPathDEProject;
}

void SWindowMenu::SetPathDEProject(const FText& Text, ETextCommit::Type CommitType){
	pPathDEProject = Text;
	// FString Filename = Text.ToString();
	// Note Slate will append the extension automatically so remove the extension
	// FName BrushName(*FPaths::GetBaseFilename(Filename, false));
}

FReply SWindowMenu::OnPathDEProjectSelect()
{
	const FString SaveFileTypes = FString::Printf(
		TEXT("%s (*.degp)|*.degp"),
		*LOCTEXT("FileTypeDescription", "Drag[en]gine Game Project").ToString());
	TArray<FString> SaveFilenames;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	bool bSaved = false;
	if(DesktopPlatform){
		const FString DefaultBrowsePath = FPaths::ProjectLogDir();
		bSaved = DesktopPlatform->SaveFileDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr),
			LOCTEXT("PathDEProjectTitle", "Select Project File").ToString(),
			DefaultBrowsePath,
			TEXT(""),
			SaveFileTypes,
			EFileDialogFlags::None,
			SaveFilenames
			);
	}

	if (bSaved && SaveFilenames.Num() > 0 && SaveFilenames[0].IsEmpty() == false){
		pPathDEProject = FText::FromString(IFileManager::Get().
			ConvertToAbsolutePathForExternalAppForRead(*SaveFilenames[0]));
	}

	return FReply::Handled();
}

FReply SWindowMenu::OnTestButtonClicked()
{
	if (pDragengineLibrary.IsNotReady())
	{
		return FReply::Handled();
	}

	deOSWindows os;
	TCHAR ws[1024];
	deOSWindows::Utf8ToWide(os.GetPathEngine(), ws, sizeof(ws));

	UE_LOG(LogTemp, Warning, TEXT("Hello, world! The checkbox is %s."),
		(bIsTestBoxChecked ? TEXT("checked") : TEXT("unchecked")));
	UE_LOG(LogTemp, Warning, TEXT("TEST: %s."), ws);
	return FReply::Handled();
}
