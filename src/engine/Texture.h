#include <GL/glew.h>
#include <iostream>
#include <stb_image/stb_image.h>

class Texture
{
private:
	GLuint id;

public:

	Texture(std::string);
	Texture(GLuint textureID);
	GLuint GetId();
};