#include "Camera.h"
#include "EngineCore.h"

void Camera::Init(CAMERA_TYPE cameraType, std::string tag)
{
	this->cameraType = cameraType;
	this->tag = tag;
}

Camera::~Camera()
{
}

void Camera::CreateCamera(
	std::string cameraName, 
	glm::vec3 position,
	glm::vec3 rotation,
	glm::vec3 scale)
{
	name = cameraName;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

glm::vec3 Camera::Position()
{
	return position;
}

void Camera::Position(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Camera::Rotation()
{
	return rotation;
}

void Camera::Rotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

glm::vec3 Camera::Scale()
{
	return scale;
}

void Camera::Scale(glm::vec3 scale)
{
	this->scale = scale;
}

void Camera::Update()
{
	TemporaryMove();
	//MOVEMENT AND STUFF GO HERE!

	//m_viewingMatrix = glm::translate(m_viewingMatrix, m_position);
	//m_viewingMatrix = 
	//Rotate
	//Scale

	//m_projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f, -1.0f, 1.0f);
}

void Camera::TemporaryMove()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W]) position.y -= 10.0f;
	if (state[SDL_SCANCODE_S]) position.y += 10.0f;
	if (state[SDL_SCANCODE_A]) position.x -= 10.0f;
	if (state[SDL_SCANCODE_D]) position.x += 10.0f;

	if (state[SDL_SCANCODE_Q]) scale -= glm::vec3(10.0f, 10.0f, 10.0f);
	if (state[SDL_SCANCODE_E]) scale += glm::vec3(10.0f, 10.0f, 10.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 viewMat(1.0f);
	viewMat = glm::translate(viewMat, position);

	viewMat = glm::rotate(viewMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	viewMat = glm::rotate(viewMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	viewMat = glm::rotate(viewMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	viewMat = glm::scale(viewMat, scale);

	return viewMat;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::ortho(0.0f, (float)engineCore.lock()->GetScreenWidth(), (float)engineCore.lock()->GetScreenHeight(), 0.0f, -1.0f, 1.0f);
}