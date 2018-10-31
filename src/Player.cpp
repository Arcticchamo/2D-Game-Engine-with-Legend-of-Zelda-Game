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
}

void Player::Update()
{
	m_meshRenderer.lock()->Update();
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

