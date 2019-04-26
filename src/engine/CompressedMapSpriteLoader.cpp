#include "CompressedMapSpriteLoader.h"

void CompressedMapSpriteLoader::LoadInSpriteMap(std::string fileLocation, std::vector<unsigned char> &imageData, int &w, int &h)
{
	int width = 0;
	int height = 0;
	int channels = 0;

	unsigned char *data = stbi_load(fileLocation.c_str(), &width, &height, &channels, 3);

	if (!data)
	{
		throw std::exception();
	}

	w = width;
	h = height;

	int size = (width * height) * 3;
	imageData.resize(size);

	for (int i = 0; i < size; i++)
	{
		imageData.at(i) = *(data + i);
	}

	stbi_image_free(data);
}
