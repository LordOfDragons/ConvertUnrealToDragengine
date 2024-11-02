#pragma once

#include "CoreMinimal.h"

class ProjectAsset
{
public:
	typedef TSharedPtr<ProjectAsset> Ref;

	ProjectAsset(const FAssetData &assetData);
	~ProjectAsset();

	inline const FString &GetObjectPath() const{ return pObjectPath; }
	inline const FTopLevelAssetPath &GetAssetPath() const{ return pAssetPath; }

protected:


private:
	FString pObjectPath;
	FTopLevelAssetPath pAssetPath;
};

