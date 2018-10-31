#include "Mesh.h"
#include "VertexArray.h"
#include "VertexBuffer.h"


void Mesh::Start()
{
	
}

void Mesh::Init()
{
	m_positions = std::make_shared<VertexBuffer>();
	m_texCoords = std::make_shared<VertexBuffer>();

	m_positions->add(glm::vec3(0.0f, 0.0f, 0.0f));
	m_positions->add(glm::vec3(0.0f, 1.0f, 0.0f));
	m_positions->add(glm::vec3(1.0f, 1.0f, 0.0f));
	
	m_positions->add(glm::vec3(1.0f, 1.0f, 0.0f));
	m_positions->add(glm::vec3(1.0f, 0.0f, 0.0f));
	m_positions->add(glm::vec3(0.0f, 0.0f, 0.0f));

	m_texCoords->add(glm::vec2(0.0f, 0.0f));
	m_texCoords->add(glm::vec2(0.0f, 1.0f));
	m_texCoords->add(glm::vec2(1.0f, 1.0f));
	
	m_texCoords->add(glm::vec2(1.0f, 1.0f));
	m_texCoords->add(glm::vec2(1.0f, 0.0f));
	m_texCoords->add(glm::vec2(0.0f, 0.0f));

	m_sprite = std::make_shared<VertexArray>();

	m_sprite->setBuffer("in_Position", m_positions);
	m_sprite->setBuffer("in_TexCoord", m_texCoords);
}

void Mesh::CreateTexture(std::string _fileLoc)
{
	/*int w = 0;
	int h = 0;
	int channels = 0;

	unsigned char *data = stbi_load(_fileLoc.c_str(), &w, &h, &channels, 4);

	if (!data) throw std::exception();

	glGenTextures(1, &m_textureID);

	if (!m_textureID) throw std::exception();

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void Mesh::Update()
{
}

void Mesh::Destroy()
{
}

GLuint Mesh::GetID()
{
	return m_sprite->getId();
}

GLuint Mesh::GetTextureID()
{
	return m_textureID;
}

Mesh::~Mesh()
{
}