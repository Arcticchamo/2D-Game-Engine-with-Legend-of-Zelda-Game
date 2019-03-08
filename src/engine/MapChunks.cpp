#include "BackGroundMap.h"
#include "MapChunks.h"

MapChunks::MapChunks()
{
	
}

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
	const int rgbDataSize = 512 * 3 * 512;
	std::array <unsigned char, rgbDataSize> rgbData;

	//Number of tiles per 512 * 512 pixel chunk
	int numberOfTilesInChunkX = 512 / tileWidth;
	int numberOfTilesInChunkY = 512 / tileHeight;

	m_transform.lock()->SetPosRotScale(
		glm::vec3(widthChunks * 512, heightChunks * 512, 0.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3(1.0f, 1.0f, 1.0f));
	textureID = 0;
	





	int skip = mapWidth / tileWidth;
	int tracker = 0;

	for (int y = 0; y < numberOfTilesInChunkY; y++)
	{
		for (int x = 0; x < numberOfTilesInChunkX; x++)
		{
			//int index = unCompressedData.at(y * skip + x);
			//int maxSize = imageTiles.at(index).RGBValues.size();

			//for (int i = 0; i < maxSize; i++)
			//{
			//	//rgbData.at(tracker) = imageTiles.at(index).RGBValues.at(i);
			//	//tracker++;
			//}
		}
	}

	

	/*MeshRenderer newMesh;
	newChunk.meshRenderer = newMesh;
	newChunk.meshRenderer.Start(newChunk.textureID);
	tiles.push_back(newChunk);*/
}

void MapChunks::CreateTexture()
{
	//Create Texture
	//glGenTextures(1, &newChunk.textureID);
	/*if (!newChunk.textureID)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, newChunk.textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgbData.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void MapChunks::RenderChunk()
{
	//Render the chunk
}