#include "Player.h"
//#include "VertexBuffer.h"
//#include "VertexArray.h"
//#include "ShaderProgram.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"

Player::Player()
{
	
}

Player::Player(std::string _textureFilePath)
{
	m_textureFilePath = _textureFilePath;
}

Player::~Player()
{
}

void Player::Start()
{
	m_mesh = AddComponent<Mesh>();
	m_meshRenderer = AddComponent<MeshRenderer>();

	m_mesh.lock()->CreateTexture(m_textureFilePath);
}

void Player::Update()
{
	//PLAYER MESHRENDERER RENDERER GOES HERE

	//m_meshRenderer.Lock()->
}

void Player::Destroy()
{
}

void Player::Render()
{
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, m_mesh.lock()->GetTextureID());
	Resources::SetUniform("in_Texture", 1);


	glUseProgram(Resources::GetProgram());
	glBindVertexArray(m_mesh.lock()->GetID());

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glUseProgram(0);
	//m_meshRenderer.lock()->Update();
}

GLuint Player::GetVAO()
{
	return m_meshRenderer.lock()->GetID();
}
