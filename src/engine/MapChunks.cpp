#include "BackGroundMap.h"
#include "MapChunks.h"
#include "Texture.h"

MapChunks::MapChunks(std::shared_ptr<BackGroundMap> map)
{
	backgroundMap = map;
}

void MapChunks::CreateChunk(int widthChunks, int heightChunks, 
	int tileWidth, int tileHeight,
	int mapWidth, int mapHeight,
	std::vector<int> uncompressedData)
{
	//Stores a 512 * 512 grid of pixels, each pixel will contain an RGB value
	std::array <unsigned char, rgbDataSize> rgbData;

	//Number of tiles per 512 * 512 pixel chunk
	int numberOfTilesInChunkX = 512 / tileWidth;
	int numberOfTilesInChunkY = 512 / tileHeight;

	position = glm::vec3(widthChunks * 512, heightChunks * 512, 0.0f);

	int skip = mapWidth / tileWidth; //Gets the number of tiles along X 

	for (int y = 0; y < numberOfTilesInChunkY; y++)
	{
		for (int x = 0; x < numberOfTilesInChunkX; x++)
		{
			int tileRowSkip = y * skip + x;
			int ChunkSkip = (heightChunks * skip * numberOfTilesInChunkY) + (widthChunks * numberOfTilesInChunkX);
			int tileIndex = tileRowSkip + ChunkSkip;
			if (tileIndex < uncompressedData.size())
			{
				tileIndex = uncompressedData.at(tileIndex);
				AssignInformation(tileWidth, tileHeight, tileIndex, x, y, numberOfTilesInChunkX, rgbData);
			}
		}
	}
	CreateTexture(rgbData);

	rgbData.empty();
}

void MapChunks::AssignInformation(
	int tileWidth, int tileHeight, 
	int tileIndex, 
	int tileX, int tileY, 
	int numberOfTilesInChunksX, 
	std::array <unsigned char, rgbDataSize> &rgbData)
{
	int index = 0;

	//Stacked for loop - width tilewidth * 3 - height tile height 
	for (int y = 0; y < tileHeight; y++)
	{
		for (int x = 0; x < tileWidth; x++)
		{								
			int chunkRowSkip = y * chunkWidth * 3 + x * 3; //Chunk row skip
			int tileSkipY = tileY * (numberOfTilesInChunksX * (tileWidth * 3)) * tileHeight;
			int tileSkipX = tileX * tileWidth * 3;
			int skip = chunkRowSkip + (tileSkipY + tileSkipX);

			rgbData.at(skip) = backgroundMap.lock()->getImageTileData(tileIndex, index);
			rgbData.at(skip + 1) = backgroundMap.lock()->getImageTileData(tileIndex, index + 1);
			rgbData.at(skip + 2) = backgroundMap.lock()->getImageTileData(tileIndex, index + 2);

			index += 3;
		}
	}
}

void MapChunks::CreateTexture(std::array <unsigned char, rgbDataSize> &rgbData)
{
	//Create Texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	if (!textureID)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgbData.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture = std::make_shared<Texture>(textureID);
}
