#include <miniz/miniz.h>
#include <miniz/miniz_tinfl.h>
#include <miniz/miniz_tdef.h>

#include <iostream>
#include <vector>

#include <stdio.h>

//Class designed to take a compressed map sprite sheet 
//text file and uncompress it
class CompressedMapLoader
{
private:

public:
	CompressedMapLoader() {}
	~CompressedMapLoader() {}

	void UncompressMapTxtFile(std::string fileLocation, std::vector<int> &uncompressedData);
	void LoadFile(std::string fileLocation, std::vector<unsigned char> &compressedData);
};