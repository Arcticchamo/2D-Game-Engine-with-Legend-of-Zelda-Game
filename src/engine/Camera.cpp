#include "Camera.h"

Camera::Camera()
{
	m_cameraType = CAMERA_TYPE::CAMERA;
	m_position = glm::vec3(0, 0, 0);
}

Camera::Camera(CAMERA_TYPE _cameraType)
{
	m_cameraType = _cameraType;
	m_position = glm::vec3(0, 0, 0);
}

Camera::~Camera()
{
}

void Camera::CreateCamera(std::string _cameraName, int _screenWidth, int _screenHeight)
{
	//m_viewingMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
	// rot
	m_viewingMatrix = glm::mat4(1.0f);
	//m_viewingMatrix = glm::inverse(m_viewingMatrix);
	//m_projectionMatrix = glm::perspective(glm::radians(45.0f), ((float)_screenWidth / (float)_screenHeight), 0.01f, 1000.0f);
	m_projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f, -1.0f, 1.0f);
}

void Camera::TranslateViewMatrix(glm::vec3 _viewPos)
{
	m_viewingMatrix = glm::translate(m_viewingMatrix, _viewPos);
}

void Camera::UpdateCamera(int _screenWidth, int _screenHeight)
{
	TemporaryMove();
	m_viewingMatrix = glm::mat4(1.0f);
	TranslateViewMatrix(m_position);
	m_projectionMatrix = glm::ortho(0.0f, (float)_screenWidth, (float)_screenHeight, 0.0f, -1.0f, 1.0f);
}

void Camera::TemporaryMove()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W]) m_position.y -= 10.0f;
	if (state[SDL_SCANCODE_S]) m_position.y += 10.0f;
	if (state[SDL_SCANCODE_A]) m_position.x -= 10.0f;
	if (state[SDL_SCANCODE_D]) m_position.x += 10.0f;
}
