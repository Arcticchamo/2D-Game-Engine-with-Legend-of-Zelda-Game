#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

class Transform;
enum CAMERA_TYPE {MAIN_CAMERA, CAMERA};


class Camera : public Component
{
private:
	//Tracks the independant camera types (TODO: Currently Depricated, could be used later)
	CAMERA_TYPE cameraType;
	std::shared_ptr<Transform> transform;
public:
	//Initialize the Camera Component with predetermined values
	void Init();
	void Init(CAMERA_TYPE cameraType);
	//Returns the view Matrix, Only the camera needs to handle this
	glm::mat4 GetViewMatrix();
	//Currently not required (TODO: Currenly Depricated, could be used later)
	CAMERA_TYPE getCameraType() { return cameraType; }
	~Camera();
};