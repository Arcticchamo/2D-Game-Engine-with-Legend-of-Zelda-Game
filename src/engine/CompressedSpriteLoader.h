#include <stb_image/stb_image.h>
#include <iostream>
#include <vector>

//TODO: COMMENT AND REWORK

class CompressedSpriteLoader
{
public:
	void LoadInSpriteMap(std::string fileLocation, std::vector<unsigned char> &imageData, int &w, int &h);
};