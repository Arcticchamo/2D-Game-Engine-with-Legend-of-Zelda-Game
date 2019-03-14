#include <iostream>
#include <GL/glew.h>
#include <memory>

#include "GameObject.h"


class MeshRenderer;

class Player : public GameObject
{
private:
	std::weak_ptr<MeshRenderer> meshRenderer;
	
public:
	void Init(std::string filePath = "DEFAULT", std::string tag = "GameObject");

	void Start();
	void Update();

	void InputController(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale);

	GLuint GetVAO();

	~Player();
};