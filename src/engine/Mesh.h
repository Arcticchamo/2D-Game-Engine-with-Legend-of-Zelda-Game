#include "Resource.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

class VertexArray;

class Mesh : public Resource
{
private:
	std::shared_ptr<VertexArray> sprite;

	void Load(std::string path);
public:
	static std::shared_ptr<Mesh> Init(std::string path);
	int GetTriangleCount();
	GLuint GetId();
	~Mesh();
};