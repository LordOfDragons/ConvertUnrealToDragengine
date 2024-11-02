#include "ProjectAssets.h"

ProjectAssets::ProjectAssets() :
pAssetRegistryModule(FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"))),
pAssetRegistry(pAssetRegistryModule.Get())
{
}

ProjectAssets::~ProjectAssets()
{
}

void ProjectAssets::ScanAssets()
{
	pAssets.Empty();

	TArray<FString> pathToScan;
	pathToScan.Add(TEXT("/Game/"));
	pAssetRegistry.ScanPathsSynchronous(pathToScan);
	
	TArray<FAssetData> assets;
	pAssetRegistry.GetAssetsByPath(FName("/Game/"), assets, true);

	const int count = assets.Num();
	int i;
	for(i=0; i<count; i++)
	{
		const TSharedPtr<ProjectAsset> asset(new ProjectAsset(assets[i]));
		pAssets.Add(asset->GetObjectPath(), asset);
	}
}

int ProjectAssets::GetAssetCount() const
{
	return pAssets.Num();
}

ProjectAssets::IterAssets ProjectAssets::CreateAssetsIter() const
{
	return pAssets.CreateConstIterator();
}

