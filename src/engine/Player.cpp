#include "Camera.h"
#include "EngineCore.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Resources.h"

#include <SDL2/SDL.h>

void Player::Init(std::string filePath, std::string tag)
{
	this->transform = AddComponent<Transform>();
	this->textureFilePath = filePath;
	this->tag = tag;
	Start();
}

void Player::Start()
{
	meshRenderer = AddComponent<MeshRenderer>();
	//transform = AddComponent<Transform>();

	meshRenderer.lock()->Start();
	transform.lock()->Start();

	transform.lock()->TranslateObject(glm::vec3((640 / 2), (480 / 2), 0.0f));
	transform.lock()->RotateObject(glm::vec3(0));
	transform.lock()->ScaleObject(glm::vec3(10, 10, 1));
	
	transform.lock()->UpdateModelMatrix();


}

/*std::vector<std::shared_ptr<Camera> >::iterator it;
	for (it = cameraList.begin(); it != cameraList.end(); it++)
	{
		if ((*it)->getCameraType() == CAMERA_TYPE::MAIN_CAMERA)
		{
			return (*it);
		}
	}
	return NULL;*/

void Player::Update()
{
	//REPLACE WITH ITERATORS
	for (size_t i = 0; i < components.size(); i++)
	{
		components.at(i)->Update();
	}

	glm::vec3 position(0);
	glm::vec3 rotation(0);
	glm::vec3 scale(1.0f);

	InputController(position, rotation, scale);

	transform.lock()->TranslateObject(position);
	transform.lock()->RotateObject(rotation);
	transform.lock()->ScaleObject(scale);
	
	transform.lock()->UpdateModelMatrix();

	meshRenderer.lock()->Render();
	
	Resources::SetUniform("in_ProjectionMat", engineCore.lock()->GetMainCamera()->GetComponent<Camera>()->GetProjectionMatrix());
	Resources::SetUniform("in_ViewMat", glm::inverse(engineCore.lock()->GetMainCamera()->GetComponent<Camera>()->GetViewMatrix()));
}

void Player::InputController(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP]) position.y -= 10.0f;
	if (state[SDL_SCANCODE_DOWN]) position.y += 10.0f;
	if (state[SDL_SCANCODE_LEFT]) position.x -= 10.0f;
	if (state[SDL_SCANCODE_RIGHT]) position.x += 10.0f;

	//if (state[SDL_SCANCODE_W]) _pos.y -= 10.0f;
	//if (state[SDL_SCANCODE_S]) _pos.y += 10.0f;
	//if (state[SDL_SCANCODE_A]) _pos.x -= 10.0f;
	//if (state[SDL_SCANCODE_D]) _pos.x += 10.0f;

	//if (state[SDL_SCANCODE_E]) _rot.z -= 0.1f;
	//if (state[SDL_SCANCODE_Q]) _rot.z += 0.1f;

	//if (state[SDL_SCANCODE_N]) _scale += 0.5f;
	//if (state[SDL_SCANCODE_M]) _scale -= 0.5f;
}

GLuint Player::GetVAO()
{
	return meshRenderer.lock()->GetID();
}

Player::~Player()
{}


