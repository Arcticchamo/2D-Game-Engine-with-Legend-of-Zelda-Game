#include "GenerateTileMap.h"

GenerateTileMap::GenerateTileMap()
{
	std::cout << "SHOULD NOT BE CALLED! ERROR IN SOFTWARE!" << std::endl;
	throw std::exception();
}

GenerateTileMap::GenerateTileMap(int tileWidth, int tileHeight, std::string fileLocation)
{
	map.fileLocation = fileLocation;
	map.tileWidth = tileWidth;
	map.tileHeight = tileHeight;
}

GenerateTileMap::GenerateTileMap(int tileWidth, int tileHeight, std::string fileLocation, std::string fileOutputLocation)
{
	map.fileLocation = fileLocation;
	map.tileWidth = tileWidth;
	map.tileHeight = tileHeight;
	output.outputFileLocation = fileOutputLocation;
}

void GenerateTileMap::Run()
{
	GenerateFileName();
	LoadPNGImage();
	GenerateRGB();
	FormatNewTiles();
	CreatePNG();
	CompressAndGenerateSpriteMap();
}

void GenerateTileMap::GenerateFileName()
{
	//Create the file name from the original image 
	std::string temp = map.fileLocation;
	temp = temp.substr(temp.find_last_of("\\/") + 1);
	temp = temp.substr(0, temp.find_last_of("."));
	output.fileName = temp;
}

void GenerateTileMap::LoadPNGImage()
{
	//Load the file
	int channels = 0;
	map.data = stbi_load(map.fileLocation.c_str(), 
		&map.mapWidth, &map.mapHeight, &channels, 3);

	if (map.data == NULL)
	{
		throw std::exception();
	}
}

void GenerateTileMap::GenerateRGB()
{
	//Tracks what the index of the tile is 
	int index = 0;

	indexTracker.push_back(map.tileWidth);
	indexTracker.push_back(map.tileHeight);
	indexTracker.push_back(map.mapWidth);
	indexTracker.push_back(map.mapHeight);

	for (int i = 0; i < map.mapHeight; i += map.tileHeight)
	{
		for (int j = 0; j < map.mapWidth; j += map.tileWidth)
		{
			CalculateRGBValues(i, j, index);
		}
	}
}

void GenerateTileMap::CalculateRGBValues(int _i, int _j, int & _index)
{
	TileData newTile;
	newTile.data.resize(map.tileWidth * map.tileHeight * 3);
	std::array<unsigned char, 3> rgb;

	for (int y = 0; y < map.tileHeight; y++)
	{
		for (int x = 0; x < map.tileWidth; x++)
		{
			GetRGB(_j + x, _i + y, rgb);
			newTile.data.at(y * map.tileHeight * 3 + x * 3) = rgb.at(0);
			newTile.data.at(y * map.tileHeight * 3 + x * 3 + 1) = rgb.at(1);
			newTile.data.at(y * map.tileHeight * 3 + x * 3 + 2) = rgb.at(2);
		}
	}

	bool found = false;

	for (size_t eti = 0; eti < existingTiles.size(); eti++) //Tracks the existing tiles index 
	{
		if (!memcmp(&existingTiles.at(eti).data.at(0), &newTile.data.at(0), newTile.data.size()))
		{
			found = true;
			indexTracker.push_back(existingTiles.at(eti).index);
			break;
		}
	}

	if (!found)
	{
		newTile.index = _index;
		indexTracker.push_back(_index);
		existingTiles.push_back(newTile);

		_index++;
	}
}

void GenerateTileMap::GetRGB(int _x, int _y, std::array<unsigned char, 3>& _rgb)
{
	unsigned char* p = map.data + ((_y * map.mapWidth * 3) + (_x * 3));

	_rgb.at(0) = *p;
	_rgb.at(1) = *(p + 1);
	_rgb.at(2) = *(p + 2);
}

void GenerateTileMap::FormatNewTiles()
{
	const int pointerSize = existingTiles.size() * existingTiles.at(0).data.size();
	output.data.resize(pointerSize);
	output.h = map.tileHeight;
	output.w = existingTiles.size() * map.tileWidth;

	for (size_t i = 0; i < existingTiles.size(); i++)
	{
		PrintTile(existingTiles.at(i), i);
	}
}

void GenerateTileMap::PrintTile(TileData & tile, int idx)
{
	for (int y = 0; y < map.tileHeight; y++)
	{
		for (int x = 0; x < map.tileWidth; x++)
		{
			char r = tile.data.at(y * map.tileHeight * 3 + x * 3);
			char g = tile.data.at(y * map.tileHeight * 3 + x * 3 + 1);
			char b = tile.data.at(y * map.tileHeight * 3 + x * 3 + 2);

			SetPixels(r, g, b, x + idx * map.tileHeight, y);
		}
	}
}

void GenerateTileMap::SetPixels(char r, char g, char b, int x, int y)
{
	int t = y * output.w * 3 + x * 3;
	output.data.at(t) = r;
	output.data.at(t + 1) = g;
	output.data.at(t + 2) = b;
}

void GenerateTileMap::CreatePNG()
{
	int newWidth = existingTiles.size() * map.tileWidth;
	int newHeight = map.tileHeight;

	if (output.outputFileLocation.size() == 0)
	{
		std::string outFileLoc = output.fileName + ".png";
		stbi_write_png(outFileLoc.c_str(), newWidth, newHeight,
					3, &output.data.at(0), 3 * newWidth);
	}
	else
	{
		std::string outFileLoc = output.outputFileLocation + "/" + output.fileName + ".png";
		stbi_write_png(outFileLoc.c_str(), newWidth, newHeight, 
					3, &output.data.at(0), 3 * newWidth);
	}
}

void GenerateTileMap::CompressAndGenerateSpriteMap()
{
	uLong compressedLength = compressBound(indexTracker.size() * sizeof(int));
	std::vector<unsigned char> compressedIndexTracker;
	compressedIndexTracker.resize(compressedLength);
	int compressedStatus = compress(&compressedIndexTracker[0], &compressedLength, 
			(const unsigned char *)&indexTracker[0], indexTracker.size() * sizeof(int));

	if (compressedStatus != Z_OK)
	{
		stbi_image_free(map.data);
		throw std::exception();
	}

	//std::string fileOutLoc = output.outputFileLocation + "/"
	//							+ output.fileName + ".txt";
	//std::FILE *f = fopen(fileOutLoc.c_str(), "wb");

	//if (f == NULL)
	//{
	//	throw std::exception();
	//}

	//for (int i = 0; i < compressedLength; i++)
	//{
	//	fprintf(f, "%c", compressedIndexTracker.at(i));
	//}

	//fclose(f);

	std::ofstream myfile;
	
	if (output.outputFileLocation.length() != 0)
	{
		std::string fileOutLoc = output.outputFileLocation + "/" 
								+ output.fileName + ".txt";
		myfile.open(fileOutLoc.c_str(), std::ios::binary);
	}
	else
	{
		std::string fileOutLoc = output.fileName + ".txt";
		myfile.open(fileOutLoc.c_str(), std::ios::binary);
	}

	if (myfile.is_open())
	{
		//myfile << "w " << map.tileWidth << std::endl;
		//myfile << "h " << map.tileHeight << std::endl;
		for (size_t i = 0; i < compressedLength; i++)
		{
			myfile << compressedIndexTracker.at(i);
		}
		myfile.close();
	}

	stbi_image_free(map.data);
}








