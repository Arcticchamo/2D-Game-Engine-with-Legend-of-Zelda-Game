#include "Component.h"
//#include "Resources.h"

#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

class Mesh;

class MeshRenderer : public Component
{
private:
	std::weak_ptr<Mesh> m_mesh;

	GLuint m_id;

public:
	MeshRenderer();

	void Start();
	void Init();
	void Update();
	void Destroy();
	
	GLuint GetID();

	~MeshRenderer();
};