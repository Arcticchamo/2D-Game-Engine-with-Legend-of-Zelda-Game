#include <iostream>
#include <GL/glew.h>
#include <memory>

#include "GameObject.h"

class MeshRenderer;

class Player : public GameObject
{
private:
	std::weak_ptr<MeshRenderer> m_meshRenderer;
	

public:
	Player();
	Player(std::string);
	~Player();

	void Start();
	void Update();
	void Destroy();

	void Render();

	GLuint GetVAO();
};
