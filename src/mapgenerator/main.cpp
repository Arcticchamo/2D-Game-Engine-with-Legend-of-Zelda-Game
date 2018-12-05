#include "GenerateTileMap.h"
#include <iostream>

void ErrorCommand();

int main(int argc, char *argv[])
{
	std::string fileLoc;
	int tWidth = 0;
	int tHeight = 0;
	std::string fileOut;

	for (int i = 0; i < argc; i++)
	{
		//Assign information
		//image file path
		if (!std::strcmp(argv[i], "-p")) 
			fileLoc = argv[i + 1];
		//tile width
		if (!std::strcmp(argv[i], "-w")) 
			tWidth = atoi(argv[i + 1]);
		//tile height
		if (!std::strcmp(argv[i], "-h"))
			tHeight = atoi(argv[i + 1]);
		//image output location
		if (!std::strcmp(argv[i], "-o"))
			fileOut = argv[i + 1];
	}

	//If any information was not correctly saved, return and error. 
	if (tWidth == 0 || tHeight == 0 || fileLoc.size() == 0)
	{
		ErrorCommand();
		throw std::exception();
		return 0;
	}
	else
	{
		if (fileOut.length() != 0)
		{
			//Output location entered
			GenerateTileMap tileMap(tWidth, tHeight, fileLoc, fileOut);
			tileMap.Run();
		}
		else
		{
			GenerateTileMap tileMap(tWidth, tHeight, fileLoc);
			tileMap.Run();
		}
	}	
	return 0;
}

void ErrorCommand()
{
	std::cerr << "You are missing some additional arguments!" << std::endl;
	std::cerr << "Your arguments should use the following format:" << std::endl;
	std::cerr << "-p FilePathLocation (the location of your image)" << std::endl;
	std::cerr << "-w TileWidth (the width of each individual tile)" << std::endl;
	std::cerr << "-h TileHeight (the height of each individual tile)" << std::endl;
	std::cerr << "(Optional) -o OutputOfImage (the output location of the final tilesheet" << std::endl;
}