// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DragengineLibrary.h"

/**
 * 
 */
class CONVERTUNREALTODRAGENGINE_API SWindowMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWindowMenu)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	FReply OnTestButtonClicked();
	void OnTestCheckboxStateChanged(ECheckBoxState NewState);
	ECheckBoxState IsTestBoxChecked() const;
	FText GetPathDEProject() const;
	void SetPathDEProject(const FText& Text, ETextCommit::Type CommitType);
	FReply OnPathDEProjectSelect();
	 
protected:
	DragengineLibrary pDragengineLibrary;

	bool bIsTestBoxChecked;
	FText pPathDEProject;
};
