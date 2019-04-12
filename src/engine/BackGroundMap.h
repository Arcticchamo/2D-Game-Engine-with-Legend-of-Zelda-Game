#include "GameObject.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include <math.h>

/*
WORK IN PROGRESS
COMMENT
TODO: TURN THIS INTO A COMPONENT!
GET IT TO WORK AUTOMATICALLY.
*/

class CompressedMapLoader;
class MapChunks;
class MapSpriteLoader;
class MeshRenderer;

struct ImageDataTile
{
	std::vector<unsigned char> RGBValues;
};

class BackGroundMap : public GameObject
{
private:
	//Size of each individual tile (pre Chunk)
	int tileWidth;
	int tileHeight;
	//Size of the Original map file 
	int mapWidth;
	int mapHeight;
	//Size of the compressed map file
	int compressedMapWidth;
	int compressedMapHeight;

	std::string fileLocation;
	std::vector<int> unCompressedData;
	std::vector<unsigned char> imageData;
	std::vector<ImageDataTile> imageTiles;

	std::vector<MapChunks> chunks;	
	
	std::shared_ptr<MeshRenderer> meshRenderer;

	std::weak_ptr<CompressedMapLoader> compressedMapLoader;
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader;


	BackGroundMap(std::string fileLocation,
		std::weak_ptr<CompressedMapLoader> compressedMapLoader,
		std::weak_ptr<MapSpriteLoader> mapSpriteLoader);

	void GenerateBackGroundMap();
	void CreateTileChunks();
	void SeperateImageData();
	void InitMeshInformation();

public:

	static std::shared_ptr<BackGroundMap> Init(std::string fileLocation,
		std::weak_ptr<CompressedMapLoader> compressedMapLoader,
		std::weak_ptr<MapSpriteLoader> mapSpriteLoader);

	void Display();

	unsigned int getImageTilesSize();
	unsigned int getImageTilesSize(int index);
	unsigned char getImageTileData(int tileIndex, int RGBindex);

	~BackGroundMap();
};