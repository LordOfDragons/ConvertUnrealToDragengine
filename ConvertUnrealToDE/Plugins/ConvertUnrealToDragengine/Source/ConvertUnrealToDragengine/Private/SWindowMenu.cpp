// Fill out your copyright notice in the Description page of Project Settings.


#include "SWindowMenu.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SWindowMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
	    SNew(SVerticalBox)
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

FReply SWindowMenu::OnTestButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello, world! The checkbox is %s."),
		(bIsTestBoxChecked ? TEXT("checked") : TEXT("unchecked")));
	return FReply::Handled();
}
