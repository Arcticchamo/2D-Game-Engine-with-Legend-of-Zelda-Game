#include "Texture.h"

Texture::Texture()
{

}

std::shared_ptr<Texture> Texture::Init()
{
	//Create a texture ptr, load in the texture and return it
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Create();
	return texture;
}

std::shared_ptr<Texture> Texture::Init(std::string path)
{
	//Create a texture ptr, load in the texture and return it
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Load(path);
	return texture;
}

void Texture::Load(std::string path)
{
	dirty = false;
	//Store the width, height and color channels 
	texWidth = 0;
	texHeight = 0;
	int channels = 0;
	//Load in the data using STB 
	unsigned char *data = stbi_load(path.c_str(), &texWidth, &texHeight, &channels, 4);

	//Error check the image data
	if (!data)
	{
		throw std::exception();
	}

	glGenTextures(1, &id);

	if (!id)
	{
		throw std::exception();
	}
	//Apply the image data and specified parameters to the bound texture and unbind it. 
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Create()
{
	dirty = false;
	texWidth = 0;
	texHeight = 0;

	glGenTextures(1, &id);

	if (!id)
	{
		throw std::exception();
	}
}

void Texture::SetPixel(unsigned char r, unsigned char g, unsigned char b)
{
	pixelData.push_back(r);
	pixelData.push_back(g);
	pixelData.push_back(b);
	dirty = true;
}

GLuint Texture::GetId()
{
	if (dirty)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		//TODO SEE IF WIPING THE VECTOR CLEAR SAVES THE INFORMATION

		dirty = false;
	}

	return id;
}

Texture::~Texture()
{

}