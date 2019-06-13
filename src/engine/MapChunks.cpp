#include "BackGroundMap.h"
#include "Component.h"
#include "MapChunks.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

MapChunks::MapChunks(std::shared_ptr<BackGroundMap> map)
{
	backgroundMap = map;
}

void MapChunks::CreateChunk(int widthChunks, int heightChunks, int tileWidth, int tileHeight, int mapWidth, int mapHeight, std::vector<int> uncompressedTxtData)
{
	//Stores a 512 * 512 grid of pixels, each pixel will contain an RGB value
	std::array <unsigned char, rgbDataSize> rgbData;

	//Number of tiles per 512 * 512 pixel chunk
	int numberOfTilesInChunkX = 512 / tileWidth;
	int numberOfTilesInChunkY = 512 / tileHeight;

	transform = AddComponent<Transform>(glm::vec3(widthChunks * 512, heightChunks * 512, 0));
	meshRenderer = AddComponent<MeshRenderer>("Mesh");
	meshRenderer.lock()->GetMaterial()->SetShader(GetResources()->Load<Shader>("Shaders"));

	int skip = mapWidth / tileWidth; //Gets the number of tiles along X 

	for (int y = 0; y < numberOfTilesInChunkY; y++)
	{
		for (int x = 0; x < numberOfTilesInChunkX; x++)
		{
			//Works out if the current pixel is on the next line or not
			int tileRowSkip = y * skip + x;
			//This calculation dictates which chunk is currently being worked on and if it needs to jump pixels or not
			int ChunkSkip = (heightChunks * skip * numberOfTilesInChunkY) + (widthChunks * numberOfTilesInChunkX);
			//Combine the two to get the current tile index within the uncompressedTxtData
			size_t tileIndex = tileRowSkip + ChunkSkip;
			//This checks whether the current tile Index is out of bounds. This is excess "black space" which does not exist
			if (tileIndex < uncompressedTxtData.size())
			{
				//Assign Tile Index a index value 
				tileIndex = uncompressedTxtData.at(tileIndex);
				AssignInformation(tileWidth, tileHeight, tileIndex, x, y, numberOfTilesInChunkX, rgbData);
			}
			else
			{
				AssignBlackInformation();
			}
		}
	}
	//TODO - ASSIGN PIXEL DATA
	//CreateTexture(rgbData);

	//Empty all of the garbage information at the end
	rgbData.empty();
}

void MapChunks::AssignInformation(
	int tileWidth, int tileHeight, 
	int tileIndex, 
	int tileX, int tileY, 
	int numberOfTilesInChunksX, 
	std::array <unsigned char, rgbDataSize> &rgbData)
{
	//Index used to track the information stored within each tile
	int index = 0;

	//Stacked for loop - width tilewidth * 3 - height tile height 
	for (int y = 0; y < tileHeight; y++)
	{
		for (int x = 0; x < tileWidth; x++)
		{								
			int chunkRowSkip = y * chunkWidth * 3 + x * 3; //Chunk row skip
			//Tile row skip X and Y
			int tileSkipY = tileY * (numberOfTilesInChunksX * (tileWidth * 3)) * tileHeight;
			int tileSkipX = tileX * tileWidth * 3;
			//Combine the skip variables 
			int skip = chunkRowSkip + (tileSkipY + tileSkipX);
			//Assign to rgbData the values of Red, Green and Blue (Per pixel). 
			//Alpha is currently not calculated
			rgbData.at(skip) = backgroundMap.lock()->getImageTileData(tileIndex, index);
			rgbData.at(skip + 1) = backgroundMap.lock()->getImageTileData(tileIndex, index + 1);
			rgbData.at(skip + 2) = backgroundMap.lock()->getImageTileData(tileIndex, index + 2);

			index += 3;
		}
	}
}

//This assigns black colour information to the chunks, to reduce undefined behaviour 
void MapChunks::AssignBlackInformation()
{
	//TODO - ASSIGN BLACK SQUARE
}

void MapChunks::CreateTexture(std::array <unsigned char, rgbDataSize> &rgbData)
{
	//TODO - CREATE TEXTURE THEN USE A "SETPIXEL()" FUNCTION TO ADD THE INFORMATION OF EACH PIXEL INTO A LOCAL VERTEX
	////Create Texture
	//GLuint textureID;
	//glGenTextures(1, &textureID);
	//if (!textureID)
	//{
	//	throw std::exception();
	//}

	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, &rgbData.at(0));
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//texture = std::make_shared<Texture>(textureID);
}
