#include "Resource.h"
#include <GL/glew.h>
#include <memory>
#include <stb_image/stb_image.h>
#include <string>
#include <vector>

class Texture : public Resource
{
private:
	bool dirty;
	int texWidth, texHeight;
	GLuint id;
	std::vector<unsigned char> pixelData;

public:
	Texture();
	Texture(int texWidth, int texHeight);
	void Load(std::string path);
	void Create(int texWidth, int texHeight);
	void SetPixel(unsigned char r, unsigned char g, unsigned char b);
	GLuint GetId();
	~Texture();
};