#include "GameObject.h"

#include <iostream>
#include <memory>
#include <vector>

class CompressedMapLoader;
class MapSpriteLoader;

class BackGroundMap : public GameObject
{
private:
	int tileWidth;
	int tileHeight;
	int mapWidth;
	int mapHeight;

	std::string fileLocation;
	std::vector<int> unCompressedData;

	std::weak_ptr<CompressedMapLoader> compressedMapLoader;
	std::weak_ptr<MapSpriteLoader> mapSpriteLoader;

public:
	BackGroundMap(std::string fileLocation, std::weak_ptr<CompressedMapLoader> compressedMapLoader, std::weak_ptr<MapSpriteLoader> mapSpriteLoader);

	void GenerateBackGroundMap();






	~BackGroundMap();
};