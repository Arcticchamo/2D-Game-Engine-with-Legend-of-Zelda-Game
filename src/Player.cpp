#include "Player.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

Player::Player()
{
	VertexBuffer *positions = new VertexBuffer();
	positions->add(glm::vec3(0.0f, 1.0f, 0.0f));
	positions->add(glm::vec3(0.0f, 0.0f, 0.0f));
	positions->add(glm::vec3(1.0f, 0.0f, 0.0f));

	VertexBuffer *colors = new VertexBuffer();
	colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	m_attributes = std::make_shared<VertexArray>();
	m_attributes->setBuffer("in_Position", positions);
	m_attributes->setBuffer("in_Color", colors);
}

Player::~Player()
{
}

void Player::Start()
{
	


}

void Player::Update()
{
}

void Player::Destroy()
{
}

void Player::SetShader(std::shared_ptr<ShaderProgram> _program)
{
	m_shader = _program;
}