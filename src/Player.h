#include <iostream>
#include <GL/glew.h>
#include <memory>

#include "GameObject.h"

class Mesh;
class MeshRenderer;


class Player : public GameObject
{
private:
	std::weak_ptr<MeshRenderer> m_meshRenderer;
	std::weak_ptr<Mesh> m_mesh;

	std::string m_textureFilePath;

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
