#include "BackGroundMap.h"
#include "CompressedMapLoader.h"
#include "MapSpriteLoader.h"

BackGroundMap::BackGroundMap(std::string fileLocation, std::weak_ptr<CompressedMapLoader> compressedMapLoader, std::weak_ptr<MapSpriteLoader> mapSpriteLoader)
{
	this->fileLocation = fileLocation;
	
	this->compressedMapLoader = compressedMapLoader;
	this->mapSpriteLoader = mapSpriteLoader;
	GenerateBackGroundMap();
}

void BackGroundMap::GenerateBackGroundMap()
{
	//The first 4 numbers in the uncompressedData are the...
	//Map Width, Map Height, Tile Width, Tile Height
	compressedMapLoader.lock()->UncompressMapTxtFile(fileLocation, unCompressedData);
	
	tileWidth = unCompressedData.at(2);
	tileHeight = unCompressedData.at(3);
	mapWidth = unCompressedData.at(0) / tileWidth;
	mapHeight = unCompressedData.at(1) / tileHeight;

	unCompressedData.erase(unCompressedData.begin(), unCompressedData.begin() + 4);
}

BackGroundMap::~BackGroundMap()
{
}
