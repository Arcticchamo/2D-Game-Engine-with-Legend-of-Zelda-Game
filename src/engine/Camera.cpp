#include "Camera.h"
#include "EngineCore.h"
#include "GameObject.h"
#include "Transform.h"

void Camera::Init()
{
	this->cameraType = CAMERA_TYPE::MAIN_CAMERA;
	//Each camera will need a transform for the view matrix
	this->transform = gameObject.lock()->AddComponent<Transform>();
	//Assign a default position
	transform->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//Push the camera GameObject into a vector stored inside the engine
	GetEngineCore()->cameraList.push_back(gameObject);
}

void Camera::Init(CAMERA_TYPE cameraType)
{
	this->cameraType = cameraType;
	//Each camera will need a transform for the view matrix
	this->transform = gameObject.lock()->AddComponent<Transform>();
	//Assign a default position
	transform->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//Push the camera GameObject into a vector stored inside the engine
	GetEngineCore()->cameraList.push_back(gameObject);
}

glm::mat4 Camera::GetViewMatrix()
{
	//Generates the view matrix from the cameras current position
	//This uses a 3D styled setup for the possible use of Isometric view points within the engine (TODO: Future expansion on this feature set)

	//TODO ---DELETE LATER, THIS IS JUST FOR TESTING--
	transform->SetPosition(Movement(transform->GetPosition()));

	glm::mat4 viewMat(1.0f);
	viewMat = glm::translate(viewMat, transform->GetPosition());

	viewMat = glm::rotate(viewMat, transform->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::rotate(viewMat, transform->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat = glm::rotate(viewMat, transform->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

	viewMat = glm::scale(viewMat, transform->GetScale());

	return viewMat;
}

glm::vec3 Camera::Movement(glm::vec3 position)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN]) position.y -= 1.0f;
	if (state[SDL_SCANCODE_UP]) position.y += 1.0f;
	if (state[SDL_SCANCODE_LEFT]) position.x -= 1.0f;
	if (state[SDL_SCANCODE_RIGHT]) position.x += 1.0f;
	return position;
}

Camera::~Camera()
{
}