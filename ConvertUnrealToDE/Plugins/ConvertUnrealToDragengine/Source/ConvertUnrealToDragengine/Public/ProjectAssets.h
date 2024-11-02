#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "ProjectAsset.h"

#include <windows.h>

class ProjectAssets
{
public:
	typedef TMap<FString, ProjectAsset::Ref> MapAssets;
	typedef MapAssets::TConstIterator IterAssets;

	ProjectAssets();
	~ProjectAssets();

	void ScanAssets();

	int GetAssetCount() const;
	const MapAssets &GetAssets() const{ return pAssets; }
	IterAssets CreateAssetsIter() const;

private:
	FAssetRegistryModule &pAssetRegistryModule;
	IAssetRegistry &pAssetRegistry;
	MapAssets pAssets;
};

