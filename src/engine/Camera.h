#include "GameObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include <SDL2/SDL.h>

enum CAMERA_TYPE {MAIN_CAMERA, CAMERA};


class Camera : public GameObject
{
private:
	CAMERA_TYPE cameraType;

	std::string name;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	void Init(CAMERA_TYPE cameraType, std::string tag = "GameObject");
	
	~Camera();

	void CreateCamera(std::string cameraName = "Camera",
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec3 Position();
	void Position(glm::vec3 position);
	glm::vec3 Rotation();
	void Rotation(glm::vec3 rotation);
	glm::vec3 Scale();
	void Scale(glm::vec3 scale);

	void Update();

	void TemporaryMove();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	CAMERA_TYPE getCameraType() { return cameraType; }
};