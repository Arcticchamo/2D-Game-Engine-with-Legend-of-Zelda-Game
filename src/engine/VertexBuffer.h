#include <gl/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class VertexBuffer
{
private:
	GLuint id;
	int components;
	std::vector<GLfloat> data;
	bool dirty;

public:
	VertexBuffer();

	void add(glm::vec2 data);
	void add(glm::vec3 data);
	void add(glm::vec4 data);
	int getComponents();
	int getDataSize();
	GLuint getId();
};