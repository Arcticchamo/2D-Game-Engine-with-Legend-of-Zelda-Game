#include "BackGroundMap.h"
#include "CompressedMapSpriteLoader.h"
#include "CompressedMapTextLoader.h"
#include "EngineCore.h"
#include "MapChunks.h"

void BackGroundMap::Init(std::string fileLocation)
{
	this->fileLocation = fileLocation;
	//transform = gameObject.lock()->AddComponent<Transform>();
	//meshRenderer = gameObject.lock()->AddComponent<MeshRenderer>("Mesh");
	//meshRenderer.lock()->GetMaterial()->SetShader(GetResources()->Load<Shader>("Shaders"));
	GenerateBackGroundMap();
}

/*loads in the compressed txt index file and condensed sprite sheet*/
void BackGroundMap::GenerateBackGroundMap()
{
	std::string txtString = fileLocation + ".txt";
	std::string pngString = fileLocation + ".png";

	std::vector<unsigned char> compressedImageData;

	//Load in the compressed map sprite image and the uncompressed txt file with the indexing of each tile
	GetEngineCore()->GetMapSpriteLoader()->LoadInSpriteMap(pngString, compressedImageData, compressedMapWidth, compressedMapHeight);
	GetEngineCore()->GetMapTextLoader()->UncompressMapTxtFile(txtString, uncompressedTxtData);

	//The first 4 numbers in the uncompressedData are the
	//Tile Width, Tile Height, Map Width, Map Height
	tileWidth = uncompressedTxtData.at(0);
	tileHeight = uncompressedTxtData.at(1);
	mapWidth = uncompressedTxtData.at(2);
	mapHeight = uncompressedTxtData.at(3);
	uncompressedTxtData.erase(uncompressedTxtData.begin(), uncompressedTxtData.begin() + 4);

	SeperateImageData(compressedImageData); //Seperate the image data
	CreateTileChunks();
}

void BackGroundMap::CreateTileChunks()
{
	//Calculate how many chunks is needed for the map
	//If the map does not divide by 512, go to the next whole number
	//This excess "black space" will be calculated later
	int widthChunks = (int)((float)mapWidth / 512.0f + 0.5f);
	int heightChunks = (int)((float)mapHeight / 512.0f + 0.5f);

	backgroundChunks.reserve(widthChunks * heightChunks);

	for (int y = 0; y < heightChunks; y++)
	{
		for (int x = 0; x < widthChunks; x++)
		{
			std::shared_ptr<GameObject> newChunk = gameObject.lock()->GetEngineCore()->AddGameObject<MapChunks>(std::dynamic_pointer_cast<BackGroundMap>(shared_from_this()));
			newChunk->GetComponent<MapChunks>()->CreateChunk(x, y, tileWidth, tileHeight, mapWidth, mapHeight, uncompressedTxtData);
			backgroundChunks.push_back(newChunk->GetComponent<MapChunks>());
		}
	}

	imageTiles.clear();
	uncompressedTxtData.clear();
}

void BackGroundMap::SeperateImageData(std::vector<unsigned char> &compressedImageData)
{
	//Number of tiles needed to calculate (single line so only need width)
	int numberOfTilesX = compressedMapWidth / tileWidth;
	//Reserve information for speed up
	imageTiles.reserve(numberOfTilesX);

	for (int i = 0; i < numberOfTilesX; i++)
	{
		//Create new ImageDataTile object
		ImageDataTile newTile;
		//The individual tile height and width
		for (int y = 0; y < tileHeight; y++)
		{
			for (int x = 0; x < tileWidth; x++)
			{
				//Skip skips a single row of pixels (timesed by Y)
				int skip = (y * compressedMapWidth * 3 + x * 3) + (i * tileWidth * 3);

				//Assign R, G, B information for individual pixel
				newTile.RGBValues.push_back(compressedImageData.at(skip));
				newTile.RGBValues.push_back(compressedImageData.at(skip + 1));
				newTile.RGBValues.push_back(compressedImageData.at(skip + 2));
			}
		}
		imageTiles.push_back(newTile);
	}
	compressedImageData.clear();
}

void BackGroundMap::Render()
{
	//for (unsigned int i = 0; i < chunks.size(); i++)
	//{
	//	glm::mat4 model(1.0f);
	//	model = glm::translate(model, chunks.at(i).GetPosition());
	//	model = glm::scale(model, glm::vec3(512, 512, 1));
	//	
	//	//Resources::SetUniform("in_ModelMat", model);
	//	//meshRenderer->Render(chunks.at(i).GetTexture());
	//}	
}

//Returns the image tiles size
unsigned int BackGroundMap::getImageTilesSize()
{
	return imageTiles.size();
}

//returns the amount of stored RGB values within a specific tile
unsigned int BackGroundMap::getImageTilesSize(int index)
{
	return imageTiles.at(index).RGBValues.size();
}

//returns a specific RGB value from a specific tile
unsigned char BackGroundMap::getImageTileData(int tileIndex, int RGBindex)
{
	return imageTiles.at(tileIndex).RGBValues.at(RGBindex);
}