#include "BackGroundMap.h"
#include "CompressedMapLoader.h"
#include "MapChunks.h"
#include "MapSpriteLoader.h"
#include "Resources.h"

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

	compressedMapLoader.lock()->UncompressMapTxtFile(txtString, unCompressedData);
	mapSpriteLoader.lock()->LoadInSpriteMap(pngString, imageData, compressedMapWidth, compressedMapHeight);

	//The first 4 numbers in the uncompressedData are the...
	//Tile Width, Tile Height, Map Width, Map Height
	tileWidth = unCompressedData.at(0);
	tileHeight = unCompressedData.at(1);
	mapWidth = unCompressedData.at(2);
	mapHeight = unCompressedData.at(3);

	unCompressedData.erase(unCompressedData.begin(), unCompressedData.begin() + 4);

	CreateTileChunks();
}

void BackGroundMap::CreateTileChunks()
{
	//Calculate how many chunks is needed for the map
	//If the map does not divide by 512, go to the next whole number
	//This "black space" will be calculated later
	int widthChunks = std::ceil(mapWidth / 512);
	int heightChunks = std::ceil(mapHeight / 512);

	chunks.reserve(widthChunks * heightChunks);

	SeperateImageData();

	for (int y = 0; y < heightChunks; y++)
	{
		for (int x = 0; x < widthChunks; x++)
		{
			MapChunks newChunk(std::dynamic_pointer_cast<BackGroundMap>(shared_from_this()));
			newChunk.CreateChunk(x, y, tileWidth, tileHeight, mapWidth, mapHeight, unCompressedData);
			chunks.push_back(newChunk);
		}
	}
}

void BackGroundMap::SeperateImageData()
{
	//Number of tiles needed to calculate (single line so only need width)
	int numberOfTilesX = compressedMapWidth / compressedMapHeight;
	imageTiles.reserve(numberOfTilesX);

	for (int i = 0; i < numberOfTilesX; i++)
	{
		//Create new ImageDataTile object
		ImageDataTile newTile;

		for (int y = 0; y < tileHeight; y++)
		{
			for (int x = 0; x < tileWidth; x++)
			{
				int f = y * compressedMapWidth * 3 + x * 3 + i * (16 * 3);
				newTile.RGBValues.push_back(imageData.at(f));
				newTile.RGBValues.push_back(imageData.at(f + 1));
				newTile.RGBValues.push_back(imageData.at(f + 2));
			}
		}
		imageTiles.push_back(newTile);
	}

	imageData.clear();
}

void BackGroundMap::Display()
{
	//for (unsigned int i = 0; i < tiles.size(); i++)
	//{
	//	glm::mat4 model(1.0f);
	//	model = glm::translate(model, tiles.at(i).position);
	//	model = glm::scale(model, glm::vec3(512, 512, 1));
	//	//model = glm::translate(model, glm::vec3(0, 0, 0));
	//	

	//	//tiles.at(i).transform.UpdateModelMatrix();
	//	Resources::SetUniform("in_ModelMat", model);
	//	tiles.at(i).meshRenderer.Render();
	//}
}

BackGroundMap::~BackGroundMap()
{
}