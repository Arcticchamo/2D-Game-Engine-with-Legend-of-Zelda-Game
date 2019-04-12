#include "Resource.h"

#include <GL/glew.h>
#include <memory>
#include <stb_image/stb_image.h>
#include <string>

class Texture : public Resource
{
private:
	GLuint id;
	void Load(std::string path);
public:
	Texture();
	static std::shared_ptr<Texture> Init(std::string path);
	GLuint GetId();
	~Texture();
};