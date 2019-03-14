#include "GameObject.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

void MeshRenderer::Init()
{}

void MeshRenderer::Start()
{
	positions = std::make_shared<VertexBuffer>();
	texCoords = std::make_shared<VertexBuffer>();

	positions->add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->add(glm::vec3(0.0f, 1.0f, 0.0f));
	positions->add(glm::vec3(1.0f, 1.0f, 0.0f));

	positions->add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->add(glm::vec3(1.0f, 0.0f, 0.0f));
	positions->add(glm::vec3(0.0f, 0.0f, 0.0f));

	texCoords->add(glm::vec2(0.0f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 1.0f));

	texCoords->add(glm::vec2(1.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 0.0f));

	sprite = std::make_shared<VertexArray>();

	sprite->setBuffer("in_Position", positions);
	sprite->setBuffer("in_TexCoord", texCoords);

	texture = std::make_shared<Texture>(gameObject.lock()->GetTextureFilePath());
}

void MeshRenderer::StartNoTexture()
{
	positions = std::make_shared<VertexBuffer>();
	texCoords = std::make_shared<VertexBuffer>();

	positions->add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->add(glm::vec3(0.0f, 1.0f, 0.0f));
	positions->add(glm::vec3(1.0f, 1.0f, 0.0f));

	positions->add(glm::vec3(1.0f, 1.0f, 0.0f));
	positions->add(glm::vec3(1.0f, 0.0f, 0.0f));
	positions->add(glm::vec3(0.0f, 0.0f, 0.0f));

	texCoords->add(glm::vec2(0.0f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 1.0f));

	texCoords->add(glm::vec2(1.0f, 1.0f));
	texCoords->add(glm::vec2(1.0f, 0.0f));
	texCoords->add(glm::vec2(0.0f, 0.0f));

	sprite = std::make_shared<VertexArray>();

	sprite->setBuffer("in_Position", positions);
	sprite->setBuffer("in_TexCoord", texCoords);
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Render()
{
	Resources::SetUniform("in_Texture", texture);
	Resources::Draw(sprite);
}

void MeshRenderer::Render(std::shared_ptr<Texture> texture)
{
	Resources::SetUniform("in_Texture", texture);
	Resources::Draw(sprite);
}

GLuint MeshRenderer::GetID()
{
	return id;
}

MeshRenderer::~MeshRenderer()
{
}