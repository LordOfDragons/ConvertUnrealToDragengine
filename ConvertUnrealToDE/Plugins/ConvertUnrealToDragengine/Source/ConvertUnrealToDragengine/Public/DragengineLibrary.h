#pragma once

#include "CoreMinimal.h"

#include <windows.h>

/**
 * Load Drag[en]gine libary from system wide installation.
 */
class DragengineLibrary
{
public:
	DragengineLibrary();
	~DragengineLibrary();

	inline bool IsReady() const{ return pReady; }
	inline bool IsNotReady() const{ return !pReady; }
	inline const FString &GetPathDragengine() const{ return pPathDragengine; }
	inline const FString &GetProblem() const{ return pProblem; }


private:
	bool pFindDragengine();
	bool pLoadLibraryDragengine();
	bool pLoadLibraryDELauncher();
	static FString pGetLastError();



private:
	FString pPathDragengine;
	FString pPathLibDragengine;
	FString pPathLibDELauncher;

	FString pProblem;

	HMODULE pModuleDragengine;
	HMODULE pModuleDELauncher;

	bool pReady;
};
