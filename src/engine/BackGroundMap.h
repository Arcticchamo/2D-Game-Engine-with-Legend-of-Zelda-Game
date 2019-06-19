#include "Component.h"

#include <array>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

class MapChunks;
class GameObject;

struct ImageDataTile
{
	std::vector<unsigned char> RGBAValues;
};

class BackGroundMap : public Component
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

	//Storage Data
	std::string fileLocation;
	std::vector<int> uncompressedTxtData; //Indexing of each tile and where it should be placed
	std::vector<ImageDataTile> imageTiles; //Storage of each individual tile from the 

	std::vector<std::weak_ptr<MapChunks> > backgroundChunks; //Stores each generated map chunk

	void GenerateBackGroundMap();
	void CreateTileChunks();
	void SeperateImageData(std::vector<unsigned char> &compressedImageData);
public:
	void Init(std::string fileLocation);

	unsigned int getImageTilesSize();
	unsigned int getImageTilesSize(int index);
	unsigned char getImageTileData(int tileIndex, int RGBAindex);

	~BackGroundMap() {}
};