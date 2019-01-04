#include "BackGroundMap.h"
#include "CompressedMapLoader.h"
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

	//The first 4 numbers in the uncompressedData are the...
	//Tile Width, Tile Height, Map Width, Map Height
	compressedMapLoader.lock()->UncompressMapTxtFile(txtString, unCompressedData);
	mapSpriteLoader.lock()->LoadInSpriteMap(pngString, imageData, compressedMapWidth, compressedMapHeight);

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

	SeperateImageData();

	for (int y = 0; y < HeightChunks; y++)
	{
		for (int x = 0; x < WidthChunks; x++)
		{
			CreateChunks(x, y);
		}
	}


	//Run through each txt element 
	//Save that specific tile in the vector
	

}

void BackGroundMap::CreateChunks(int x, int y) 
{
	//Stores a 512 * 512 grid of pixels, each pixel will contain an RGB value
	const int rgbDataSize = 512 * 3 * 512;
	std::array <unsigned char, rgbDataSize> rgbData;

	//Number of tiles per 512 * 512 pixel chunk
	int numberOfTilesInChunkX = 512 / tileWidth;
	int numberOfTilesInChunkY = 512 / tileHeight;

	//Create the tile 
	ChunkData newChunk;
	newChunk.position.x = x * 512;
	newChunk.position.y = y * 512;
	newChunk.position.z = 0;
	newChunk.textureID = 0;

	int skip = mapWidth / tileWidth;
	int tracker = 0;

	for (int y = 0; y < numberOfTilesInChunkY; y++)
	{
		for (int x = 0; x < numberOfTilesInChunkX; x++)
		{
			int index = unCompressedData.at(y * skip + x);
			int maxSize = imageTiles.at(index).RGBValues.size();

			for (int i = 0; i < maxSize; i++)
			{
				rgbData.at(tracker) = imageTiles.at(index).RGBValues.at(i);
				tracker++;
			}
		}
	}

	//Create Texture
	glGenTextures(1, &newChunk.textureID);
	if (!newChunk.textureID)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, newChunk.textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgbData.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	MeshRenderer newMesh;
	//Transform trans;

	newChunk.meshRenderer = newMesh;
	//newChunk.transform = trans;
	newChunk.meshRenderer.Start(newChunk.textureID);
	

	tiles.push_back(newChunk);
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
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, tiles.at(i).position);
		model = glm::scale(model, glm::vec3(512, 512, 1));
		//model = glm::translate(model, glm::vec3(0, 0, 0));
		

		//tiles.at(i).transform.UpdateModelMatrix();
		Resources::SetUniform("in_ModelMat", model);
		tiles.at(i).meshRenderer.Render();
	}
}

BackGroundMap::~BackGroundMap()
{
}