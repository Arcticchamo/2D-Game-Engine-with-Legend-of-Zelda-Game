#include "Player.h"
#include "MeshRenderer.h"


Player::Player()
{}

Player::Player(std::string _textureFilePath)
{
	m_textureFilePath = _textureFilePath;
}

Player::~Player()
{}

void Player::Start()
{
	m_meshRenderer = AddComponent<MeshRenderer>();


	m_meshRenderer.lock()->Start();
	m_transform.lock()->Start();
}

void Player::Update()
{
	//REPLACE WITH ITERATORS
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Update();
	}

	//m_meshRenderer.lock()->Update();

	//KEY INPUT GOES HERE

	m_transform.lock()->

	//glm::mat4 modelMatrix(1.0f);
	//modelMatrix = glm::translate(modelMatrix, glm::vec3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f));
	//modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0, 0, 1));
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(-50, -50, 0.0f));
	//modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 1));

	//Resources::SetUniform("in_ModelMat", modelMatrix);
}

void Player::Render()
{
	m_meshRenderer.lock()->Render();
}

void Player::Destroy()
{
}

GLuint Player::GetVAO()
{
	return m_meshRenderer.lock()->GetID();
}

