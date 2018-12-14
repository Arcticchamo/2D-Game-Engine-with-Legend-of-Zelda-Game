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
	std::string txtString = fileLocation + ".txt";
	std::string pngString = fileLocation + ".png";

	//The first 4 numbers in the uncompressedData are the...
	//Tile Width, Tile Height, Map Width, Map Height
	compressedMapLoader.lock()->UncompressMapTxtFile(txtString, unCompressedData);
	mapSpriteLoader.lock()->LoadInSpriteMap(pngString, imageData);

	tileWidth = unCompressedData.at(0);
	tileHeight = unCompressedData.at(1);
	mapWidth = unCompressedData.at(2);
	mapHeight = unCompressedData.at(3);

	unCompressedData.erase(unCompressedData.begin(), unCompressedData.begin() + 4);

	CreateTileChunks();
}

void BackGroundMap::CreateTileChunks()
{
	int WidthChunks = std::ceil(mapWidth / 512);
	int HeightChunks = std::ceil(mapHeight / 512);

	for (int y = 0; y < HeightChunks; y++)
	{
		for (int x = 0; x < WidthChunks; y++)
		{
			CreateChunk(x, y);
		}
	}
}

void BackGroundMap::CreateChunk(int x, int y) 
{
	//Stores a 512 * 512 grid of pixels, each pixel will contain an RGB value
	//Width * 3 * height (512 * 3 * 512)
	std::array <unsigned char, 786432> rgbData;

	TileData newTile;
	newTile.xPosition = 512 * x;
	newTile.yPosition = 512 * y;





	//NEW LINE CALCULATION
	//y * map.tileHeight * 3 + x * 3
}

void BackGroundMap::GetRGBValues(int dataPos)
{

}

BackGroundMap::~BackGroundMap()
{
}
