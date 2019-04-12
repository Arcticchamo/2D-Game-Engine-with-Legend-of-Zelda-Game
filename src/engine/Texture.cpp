#include "Texture.h"

Texture::Texture()
{

}

std::shared_ptr<Texture> Texture::Init(std::string path)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Load(path);
	return texture;
}

void Texture::Load(std::string path)
{
	int w = 0;
	int h = 0;
	int channels = 0;

	unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 4);

	if (!data)
	{
		throw std::exception();
	}

	glGenTextures(1, &id);

	if (!id)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}



GLuint Texture::GetId()
{
	return id;
}

Texture::~Texture()
{

}