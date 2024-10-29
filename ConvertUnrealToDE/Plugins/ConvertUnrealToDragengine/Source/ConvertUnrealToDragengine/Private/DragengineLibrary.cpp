#include "DragengineLibrary.h"

DragengineLibrary::DragengineLibrary() :
pModuleDragengine(NULL),
pModuleDELauncher(NULL),
pReady(false)
{
	pReady = pFindDragengine()
		&& pLoadLibraryDragengine()
		&& pLoadLibraryDELauncher();
}

DragengineLibrary::~DragengineLibrary()
{
	if (pModuleDELauncher)
	{
		FreeLibrary(pModuleDELauncher);
	}
	if (pModuleDragengine)
	{
		FreeLibrary(pModuleDragengine);
	}
}

bool DragengineLibrary::pFindDragengine()
{
	HKEY hkey;
	LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Drag[en]gine"), 0, KEY_READ, &hkey);
	if (result != ERROR_SUCCESS)
	{
		pProblem.Append(TEXT("RegOpenKeyEx failed: "));
		pProblem.Append(pGetLastError());
		return false;
	}

	TCHAR buffer[512];
	DWORD bufferSize = sizeof(buffer);
	result = RegQueryValueEx(hkey, TEXT("PathEngine"), 0, nullptr,
		reinterpret_cast<LPBYTE>(buffer), &bufferSize);
	if (result != ERROR_SUCCESS)
	{
		pProblem.Append(TEXT("DragengineLibrary: RegQueryValueEx failed: "));
		pProblem.Append(pGetLastError());
		return false;
	}
	
	pPathDragengine.Append(buffer);
	return true;
}

bool DragengineLibrary::pLoadLibraryDragengine()
{
	pPathLibDragengine.Append(pPathDragengine);
	pPathLibDragengine.Append(TEXT("\\Launchers\\Bin\\dragengine.dll"));
	
	pModuleDragengine = LoadLibrary(*pPathLibDragengine);
	if (pModuleDragengine == NULL)
	{
		pProblem.Append(TEXT("Dragengine: LoadLibrary failed: "));
		pProblem.Append(pGetLastError());
		return false;
	}

	return true;
}

bool DragengineLibrary::pLoadLibraryDELauncher()
{
	pPathLibDELauncher.Append(pPathDragengine);
	pPathLibDELauncher.Append(TEXT("\\Launchers\\Bin\\delauncher.dll"));
	
	pModuleDELauncher = LoadLibrary(*pPathLibDELauncher);
	if (pModuleDELauncher == NULL)
	{
		pProblem.Append(TEXT("DELauncher: LoadLibrary failed: "));
		pProblem.Append(pGetLastError());
		return false;
	}

	return true;
}

FString DragengineLibrary::pGetLastError()
{
    const DWORD le = GetLastError();
    if (le== 0)
	{
        return FString(TEXT("<no last error>"));
    }
    
    LPWSTR buf = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS, NULL, le, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buf, 0, NULL);
    
	FString message;
	message.Append(buf, size);
    LocalFree(buf);

    return message;
}
