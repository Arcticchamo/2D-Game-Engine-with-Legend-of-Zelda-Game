#include <stb_image/stb_image.h>

#include <iostream>
#include <vector>

class MapSpriteLoader
{
private:

public:
	void LoadInSpriteMap(std::string fileLocation, std::vector<unsigned char> &imageData);
	
};