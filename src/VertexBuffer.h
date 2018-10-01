#include <gl/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class VertexBuffer
{
private:
	GLuint m_id;
	int m_components;
	std::vector<GLfloat> m_data;
	bool m_dirty;

public:
	VertexBuffer();

	void add(glm::vec3);
	void add(glm::vec4);
	int getComponents();
	int getDataSize();
	GLuint getId();
};