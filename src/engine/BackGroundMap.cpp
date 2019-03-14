#include "BackGroundMap.h"
#include "CompressedMapLoader.h"
#include "MapChunks.h"
#include "MapSpriteLoader.h"
#include "MeshRenderer.h"
#include "Resources.h"

std::shared_ptr<BackGroundMap> BackGroundMap::Init(std::string fileLocation, 
	std::weak_ptr<CompressedMapLoader> compressedMapLoader, 
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader)
{
	std::shared_ptr<BackGroundMap> map;
	map = std::shared_ptr<BackGroundMap>(new BackGroundMap(fileLocation, compressedMapLoader, mapSpriteLoader));
	map->GenerateBackGroundMap();
	return map;
}

BackGroundMap::BackGroundMap(std::string fileLocation, 
	std::weak_ptr<CompressedMapLoader> compressedMapLoader, 
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader)
{
	this->fileLocation = fileLocation;
	this->compressedMapLoader = compressedMapLoader;
	this->mapSpriteLoader = mapSpriteLoader;
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
	int widthChunks = ((float)mapWidth / 512.0f) + 0.5f;
	int heightChunks = ((float)mapHeight / 512.0f) + 0.5f;

	chunks.reserve(widthChunks * heightChunks);

	SeperateImageData();
	InitMeshInformation();
	for (int y = 0; y < heightChunks; y++)
	{
		for (int x = 0; x < widthChunks; x++)
		{
			MapChunks newChunk(std::dynamic_pointer_cast<BackGroundMap>(shared_from_this()));
			newChunk.CreateChunk(x, y, tileWidth, tileHeight, mapWidth, mapHeight, unCompressedData);
			chunks.push_back(newChunk);
		}
	}

	imageTiles.clear();
	imageData.clear();
	unCompressedData.clear();
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
				int skip = (y * compressedMapWidth * 3 + x * 3) + (i * tileWidth * 3);
				newTile.RGBValues.push_back(imageData.at(skip));
				newTile.RGBValues.push_back(imageData.at(skip + 1));
				newTile.RGBValues.push_back(imageData.at(skip + 2));
			}
		}
		imageTiles.push_back(newTile);
	}

	imageData.clear();
}

void BackGroundMap::InitMeshInformation()
{
	meshRenderer = std::make_shared<MeshRenderer>();
	meshRenderer->StartNoTexture();
}

void BackGroundMap::Display()
{
	for (unsigned int i = 0; i < chunks.size(); i++)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, chunks.at(i).GetPosition());
		model = glm::scale(model, glm::vec3(512, 512, 1));
		
		Resources::SetUniform("in_ModelMat", model);
		meshRenderer->Render(chunks.at(i).GetTexture());
	}	
}

unsigned int BackGroundMap::getImageTilesSize()
{
	return imageTiles.size();
}

unsigned int BackGroundMap::getImageTilesSize(int index)
{
	return imageTiles.at(index).RGBValues.size();
}

unsigned char BackGroundMap::getImageTileData(int tileIndex, int RGBindex)
{
	return imageTiles.at(tileIndex).RGBValues.at(RGBindex);
}

BackGroundMap::~BackGroundMap()
{
}