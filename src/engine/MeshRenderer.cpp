#include "GameObject.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

MeshRenderer::MeshRenderer()
{}

void MeshRenderer::Init()
{}

void MeshRenderer::Start()
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

	m_texture = std::make_shared<Texture>(m_gameObject.lock()->GetTextureFilePath());
}

void MeshRenderer::Start(GLuint textureID)
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

	m_texture = std::make_shared<Texture>(textureID);
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Render()
{
	Resources::SetUniform("in_Texture", m_texture);
	Resources::Draw(m_sprite.get());
}

void MeshRenderer::Destroy()
{}

GLuint MeshRenderer::GetID()
{
	return m_id;
}

MeshRenderer::~MeshRenderer()
{
}