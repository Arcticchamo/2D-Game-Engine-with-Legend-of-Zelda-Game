#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

class VertexArray;

class Mesh : public Resource
{
private:
	std::shared_ptr<VertexArray> sprite;

public:
	int GetTriangleCount();
	void Load(std::string path);
	GLuint GetId();
	~Mesh();
};