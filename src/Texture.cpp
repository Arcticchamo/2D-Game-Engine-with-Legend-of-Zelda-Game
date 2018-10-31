#include "Texture.h"

Texture::Texture(std::string _textureLocation)
{
	int w = 0;
	int h = 0;
	int channels = 0;

	unsigned char *data = stbi_load(_textureLocation.c_str(), &w, &h, &channels, 4);

	if (!data)
	{
		throw std::exception();
	}

	glGenTextures(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetId()
{
	return m_id;
}