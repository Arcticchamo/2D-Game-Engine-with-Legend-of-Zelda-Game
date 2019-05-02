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
	void Load(std::string path);
	void Create();
public:
	Texture();
	static std::shared_ptr<Texture> Init();
	static std::shared_ptr<Texture> Init(std::string path);
	void SetPixel(unsigned char r, unsigned char g, unsigned char b);
	GLuint GetId();
	~Texture();
};