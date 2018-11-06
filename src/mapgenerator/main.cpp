#include <stb_image/stb_image.h>
#include <stb_image/stb_image_write.h>

#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct TileData
{
	int index = 0;
	std::array<unsigned char, 768> data;
};

struct MapData
{
	unsigned char *data;
	int w, h;
};

struct OutputData
{
	std::vector <unsigned char> data;
	int w, h;
};

void CalculateRGBValues(int _i, int _j, MapData &_map, std::vector<TileData> &_existingTiles, int _index, std::vector<int> _indexTracker);
void GetRGB(int _x, int _y, std::array<unsigned char, 3> &_rgb, MapData &_map);

void PrintTile(TileData& tile, OutputData& output, int idx);
void SetPixels(char r, char g, char b, int x, int y, OutputData& output);

int main()
{
	std::vector<int> indexTracker;


	int channels = 0;

	MapData map;

	map.data = stbi_load("../Zelda_Overworld_Map.png", &map.w, &map.h, &channels, 3);

	std::vector<TileData> existingTiles;

	int index = 0;

	for (size_t i = 0; i < map.h; i += 16)
	{
		for (size_t j = 0; j < map.w; j += 16)
		{
			CalculateRGBValues(i, j, map, existingTiles, index);
			index++;
		}
	}

	const int pointerSize = existingTiles.size() * existingTiles.at(0).data.size();
	
	OutputData output;
	output.data.resize(pointerSize);
	output.h = 16;
	output.w = existingTiles.size() * 16;

	for (size_t i = 0; i < existingTiles.size(); i++)
	{
		PrintTile(existingTiles.at(i), output, i);
	}

	int newWidth = existingTiles.size() * 16;
	int newHeight = 16;
	
	stbi_write_png("Image.png", newWidth, newHeight, 3, &output.data.at(0), 3 * newWidth);

	std::ofstream myfile("test.txt");

	

	if (myfile.is_open())
	{
		for (int i = 0; i < indexTracker.size(); i++)
		{

		}
	}




	free(map.data);
	return 0;
}

void CalculateRGBValues(int _i, int _j, MapData &_map, std::vector<TileData> &_existingTiles, int _index, std::vector<int> _indexTracker)
{
	TileData newTile;
	std::array<unsigned char, 3> rgb;

	for (size_t y = 0; y < 16; y++)
	{
		for (size_t x = 0; x < 16; x++)
		{
			GetRGB(_j + x, _i + y, rgb, _map);
			newTile.data.at(y * 16 * 3 + x * 3) = rgb.at(0);
			newTile.data.at(y * 16 * 3 + x * 3 + 1) = rgb.at(1);
			newTile.data.at(y * 16 * 3 + x * 3 + 2) = rgb.at(2);
		}
	}

	bool found = false;

	for (size_t eti = 0; eti < _existingTiles.size(); eti++) //Tracks the existing tiles index 
	{
		if (!memcmp(&_existingTiles.at(eti).data.at(0), &newTile.data.at(0), newTile.data.size()))
		{
			found = true;
			_indexTracker.push_back(_existingTiles.at(eti).index);
			break;
		}
	}

	if (!found)
	{
		newTile.index = _index;
		_indexTracker.push_back(_index);
		_existingTiles.push_back(newTile);
	}
}

void GetRGB(int _x, int _y, std::array<unsigned char, 3> &_rgb, MapData &_map)
{
	unsigned char* p = _map.data + ((_y * _map.w * 3) + (_x * 3));

	_rgb.at(0) = *p;
	_rgb.at(1) = *(p + 1);
	_rgb.at(2) = *(p + 2);
}

void PrintTile(TileData& tile, OutputData& output, int idx)
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			char r = tile.data.at(y * 16 * 3 + x * 3);
			char g = tile.data.at(y * 16 * 3 + x * 3 + 1);
			char b = tile.data.at(y * 16 * 3 + x * 3 + 2);

			SetPixels(r, g, b, x + idx * 16, y, output);
		}
	}
}

void SetPixels(char r, char g, char b, int x, int y, OutputData& output)
{
	int t = y * output.w * 3 + x * 3;
	output.data.at(t) = r;
	output.data.at(t + 1) = g;
	output.data.at(t + 2) = b;
}