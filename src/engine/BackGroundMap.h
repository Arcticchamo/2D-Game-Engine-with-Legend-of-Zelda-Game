#include "GameObject.h"


//#include "Transform.h"
//#include "MeshRenderer.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include <math.h>

class CompressedMapLoader;
class MapChunks;
class MapSpriteLoader;

//class Transform;
//class MeshRenderer;
//
//struct ChunkData
//{
//	glm::vec3 position;
//
//	MeshRenderer meshRenderer;
//	//Transform transform;
//
//	GLuint textureID;
//};

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
	

	std::weak_ptr<CompressedMapLoader> compressedMapLoader;
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader;

public:

	BackGroundMap(std::string fileLocation,
		std::weak_ptr<CompressedMapLoader> compressedMapLoader,
		std::weak_ptr<MapSpriteLoader> mapSpriteLoader);

	void GenerateBackGroundMap();
	void CreateTileChunks();
	//void CreateChunks(int x, int y);

	void SeperateImageData();

	void Display();

	~BackGroundMap();
};