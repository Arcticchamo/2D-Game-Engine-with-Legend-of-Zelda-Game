#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum CAMERA_TYPE {MAIN_CAMERA, CAMERA};

class Camera
{
private:
	CAMERA_TYPE m_cameraType;

	glm::mat4 m_viewingMatrix;
	glm::mat4 m_projectionMatrix;
	
public:
	Camera();
	Camera(CAMERA_TYPE);
	~Camera();

	glm::mat4 GetViewMatrix() { return m_viewingMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	void CreateCamera(std::string, int, int);
	void TranslateViewMatrix(glm::vec3);
	void UpdateCamera(int _screenWidth, int _screenHeight);

	CAMERA_TYPE getCameraType() { return m_cameraType; }
};