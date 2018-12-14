#include "GameObject.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include <math.h>

class CompressedMapLoader;
class MapSpriteLoader;

struct TileData
{
	int xPosition; 
	int yPosition;

	//OPENGL TEXTURE STORAGE INSTEAD OF RGB DATA
};

class BackGroundMap : public GameObject
{
private:
	int tileWidth;
	int tileHeight;
	int mapWidth;
	int mapHeight;

	std::string fileLocation;
	std::vector<int> unCompressedData;
	std::vector<unsigned char> imageData;
	std::vector<TileData> tiles;

	std::weak_ptr<CompressedMapLoader> compressedMapLoader;
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader;

public:

	BackGroundMap(std::string fileLocation,
		std::weak_ptr<CompressedMapLoader> compressedMapLoader,
		std::weak_ptr<MapSpriteLoader> mapSpriteLoader);

	void GenerateBackGroundMap();
	void CreateTileChunks();
	void CreateChunk(int x, int y);
	void GetRGBValues(int dataPos);

	~BackGroundMap();
};