#include "Player.h"
#include "MeshRenderer.h"
#include "Resources.h"

#include <SDL2/SDL.h>


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
	m_transform = AddComponent<Transform>();

	m_meshRenderer.lock()->Start();
	m_transform.lock()->Start();

	
	m_transform.lock()->Translate(glm::vec3((640 / 2), (480 / 2), 0.0f));
	m_transform.lock()->Rotate(glm::vec3(0));
	m_transform.lock()->Scale(glm::vec3(100, 100, 1));
	

	m_transform.lock()->UpdateModelMatrix();
}

void Player::Update()
{
	//REPLACE WITH ITERATORS
	for (size_t i = 0; i < m_components.size(); i++)
	{
		m_components.at(i)->Update();
	}

	glm::vec3 position(0);
	glm::vec3 rotation(0);
	glm::vec3 scale(0);

	InputController(position, rotation, scale);

	m_transform.lock()->Translate(position);
	m_transform.lock()->Rotate(rotation);
	m_transform.lock()->Scale(scale);
	
	
	m_transform.lock()->UpdateModelMatrix();

	m_meshRenderer.lock()->Render();
}

void Player::InputController(glm::vec3 & _pos, glm::vec3 & _rot, glm::vec3 & _scale)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP]) _pos.y -= 10.0f;
	if (state[SDL_SCANCODE_DOWN]) _pos.y += 10.0f;
	if (state[SDL_SCANCODE_LEFT]) _pos.x -= 10.0f;
	if (state[SDL_SCANCODE_RIGHT]) _pos.x += 10.0f;

	//if (state[SDL_SCANCODE_W]) _pos.y -= 10.0f;
	//if (state[SDL_SCANCODE_S]) _pos.y += 10.0f;
	//if (state[SDL_SCANCODE_A]) _pos.x -= 10.0f;
	//if (state[SDL_SCANCODE_D]) _pos.x += 10.0f;

	//if (state[SDL_SCANCODE_E]) _rot.z -= 0.1f;
	//if (state[SDL_SCANCODE_Q]) _rot.z += 0.1f;

	//if (state[SDL_SCANCODE_N]) _scale += 0.5f;
	//if (state[SDL_SCANCODE_M]) _scale -= 0.5f;
}

void Player::Destroy()
{
}

GLuint Player::GetVAO()
{
	return m_meshRenderer.lock()->GetID();
}

