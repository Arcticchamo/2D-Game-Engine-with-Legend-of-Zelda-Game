
#include <miniz/miniz.h>

#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>

struct TileData
{
	int index = 0;
	std::vector<unsigned char> data;
};

struct MapData
{
	unsigned char *data;
	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	std::string fileLocation;
};

struct OutputData
{
	std::vector <unsigned char> data;
	int w, h;
	std::string fileName;
	std::string outputFileLocation;
};

class GenerateTileMap
{
private:
	MapData map;
	OutputData output;

	std::vector<TileData> existingTiles; //stores the seperated tiles
	std::vector<int> indexTracker; //Stores the index of each repeated tile

public:

	GenerateTileMap();
	GenerateTileMap(int tileWidth, int tileHeight, std::string fileLocation);
	GenerateTileMap(int tileWidth, int tileHeight, std::string fileLocation, std::string fileOutputLocation);

	void Run();

	void GenerateFileName();
	void LoadPNGImage();
	void GenerateRGBA();
	void FormatNewTiles();
	void CreatePNG();
	void CompressAndGenerateSpriteMap();

	void CalculateRGBValues(int _i, int _j, int &_index);
	void GetRGBA(int _x, int _y, std::array<unsigned char, 4> &_rgba);
	void PrintTile(TileData& tile, int idx);
	void SetPixels(char r, char g, char b, char a, int x, int y);
};