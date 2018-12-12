#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <SDL2/SDL.h>

enum CAMERA_TYPE {MAIN_CAMERA, CAMERA};

class Camera
{
private:
	CAMERA_TYPE m_cameraType;

	glm::mat4 m_viewingMatrix;
	glm::mat4 m_projectionMatrix;
	
	glm::vec3 m_position;

public:
	Camera();
	Camera(CAMERA_TYPE);
	~Camera();

	glm::mat4 GetViewMatrix() { return m_viewingMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	void CreateCamera(std::string, int, int);
	void TranslateViewMatrix(glm::vec3);
	void UpdateCamera(int _screenWidth, int _screenHeight);

	void TemporaryMove();

	CAMERA_TYPE getCameraType() { return m_cameraType; }
};