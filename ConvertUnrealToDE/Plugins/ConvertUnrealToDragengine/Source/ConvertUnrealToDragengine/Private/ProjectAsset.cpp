#include "ProjectAsset.h"

ProjectAsset::ProjectAsset(const FAssetData& assetData) :
pObjectPath(assetData.GetObjectPathString()),
pAssetPath(assetData.AssetClassPath)
{
}

ProjectAsset::~ProjectAsset()
{
}
