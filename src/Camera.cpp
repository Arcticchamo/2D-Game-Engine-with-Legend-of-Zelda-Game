#include "Camera.h"

Camera::Camera()
{
	m_cameraType = CAMERA_TYPE::CAMERA;
}

Camera::Camera(CAMERA_TYPE _cameraType)
{
	m_cameraType = _cameraType;
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

void Camera::UpdateCamera()
{

}