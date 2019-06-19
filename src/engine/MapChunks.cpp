#include "BackGroundMap.h"
#include "GameObject.h"
#include "MapChunks.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

void MapChunks::Init(std::shared_ptr<BackGroundMap> map)
{
	backgroundMap = map;
}

void MapChunks::CreateChunk(int widthChunks, int heightChunks, int tileWidth, int tileHeight, int mapWidth, int mapHeight, std::vector<int> uncompressedTxtData)
{
	//Stores a 512 * 512 grid of pixels, each pixel will contain an RGBA value	
	std::vector<unsigned char> rgbaData(rgbaDataSize);

	//Number of tiles per 512 * 512 pixel chunk
	int numberOfTilesInChunkX = 512 / tileWidth;
	int numberOfTilesInChunkY = 512 / tileHeight;

	transform = gameObject.lock()->AddComponent<Transform>(
		glm::vec3(widthChunks * 512, heightChunks * 512, 0), //Position
		glm::vec3(0,0,0), //Rotation
		glm::vec3(512, 512, 1)); //Scale

	meshRenderer = gameObject.lock()->AddComponent<MeshRenderer>("Mesh");
	meshRenderer.lock()->GetMaterial()->SetShader(GetResources()->Load<Shader>("Shaders"));

	int tilesAlongX = mapWidth / tileWidth; //Gets the number of tiles along X 

	for (int y = 0; y < numberOfTilesInChunkY; y++)
	{
		for (int x = 0; x < numberOfTilesInChunkX; x++)
		{
			//Works out if the current pixel is on the next line or not
			int tileRowSkip = y * tilesAlongX + x;
			//This calculation dictates which chunk is currently being worked on and if it needs to jump pixels or not
			int ChunkRowSkip = (heightChunks * tilesAlongX * numberOfTilesInChunkY) + (widthChunks * numberOfTilesInChunkX);
			//Combine the two to get the current tile index within the uncompressedTxtData
			size_t tileIndex = tileRowSkip + ChunkRowSkip;
			//This checks whether the current tile Index is out of bounds. This is excess "black space" which does not exist
			if (tileIndex < uncompressedTxtData.size())
			{
				//Assign Tile Index a index value 
				tileIndex = uncompressedTxtData.at(tileIndex);
				AssignInformation(tileWidth, tileHeight, tileIndex, x, y, numberOfTilesInChunkX, rgbaData);
			}
			else
			{
				//Assign black to the null information
				AssignBlackInformation(tileWidth, tileHeight, x, y, numberOfTilesInChunkX, rgbaData);
			}
		}
	}
	CreateTexture(rgbaData);

	//Empty all of the garbage information at the end
	rgbaData.empty();
}

void MapChunks::AssignInformation(
	int tileWidth, int tileHeight, 
	int tileIndex, 
	int tileX, int tileY, 
	int numberOfTilesInChunksX, 
	std::vector<unsigned char> &rgbaData)
{
	//Index used to track the information stored within each tile
	int index = 0;

	//Stacked for loop - width tilewidth * 3 - height tile height 
	for (int y = 0; y < tileHeight; y++)
	{
		for (int x = 0; x < tileWidth; x++)
		{								
			int chunkRowSkip = y * chunkWidth * 4 + x * 4; //Chunk row skip
			//Tile row skip X and Y
			int tileSkipY = tileY * (numberOfTilesInChunksX * (tileWidth * 4)) * tileHeight;
			int tileSkipX = tileX * tileWidth * 4;
			//Combine the skip variables 
			int skip = chunkRowSkip + (tileSkipY + tileSkipX);
			//Assign to rgbaData the values of Red, Green and Blue (Per pixel)
			rgbaData.at(skip) = backgroundMap.lock()->getImageTileData(tileIndex, index);
			rgbaData.at(skip + 1) = backgroundMap.lock()->getImageTileData(tileIndex, index + 1);
			rgbaData.at(skip + 2) = backgroundMap.lock()->getImageTileData(tileIndex, index + 2);
			rgbaData.at(skip + 3) = backgroundMap.lock()->getImageTileData(tileIndex, index + 3);

			index += 4;
		}
	}
}

//This assigns black colour information to the chunks, to reduce undefined behaviour 
void MapChunks::AssignBlackInformation(
	int tileWidth, int tileHeight,
	int tileX, int tileY,
	int numberOfTilesInChunksX,
	std::vector<unsigned char> &rgbaData)
{
	//Index used to track the information stored within each tile
	int index = 0;

	//Stacked for loop - width tilewidth * 3 - height tile height 
	for (int y = 0; y < tileHeight; y++)
	{
		for (int x = 0; x < tileWidth; x++)
		{
			int chunkRowSkip = y * chunkWidth * 4 + x * 4; //Chunk row skip
			//Tile row skip X and Y
			int tileSkipY = tileY * (numberOfTilesInChunksX * (tileWidth * 4)) * tileHeight;
			int tileSkipX = tileX * tileWidth * 4;
			//Combine the skip variables 
			int skip = chunkRowSkip + (tileSkipY + tileSkipX);

			//Assign to rgbaData the value 0 for black 
			rgbaData.at(skip) = 0;
			rgbaData.at(skip + 1) = 0;
			rgbaData.at(skip + 2) = 0;
			rgbaData.at(skip + 3) = 0;

			index += 4;
		}
	}
}

void MapChunks::CreateTexture(std::vector<unsigned char> &rgbaData)
{
	//Assign "texture" with a fresh set of information. 
	texture = GetResources()->Create<Texture>(512, 512);
	//Assign the pixel data to the texture
	for (size_t i = 0; i < rgbaData.size(); i += 4)
	{
		texture->SetPixel(rgbaData.at(i), rgbaData.at(i + 1), rgbaData.at(i + 2), rgbaData.at(i + 3));
	}
	//Assign the texture to the material attached to the object
	meshRenderer.lock()->GetMaterial()->SetValue("Chunk_Texture", texture);
}
