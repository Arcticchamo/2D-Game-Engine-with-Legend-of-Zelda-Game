#include <GL/glew.h>
#include <iostream>
#include <vector>

class VertexBuffer;

class VertexArray
{
private:
	GLuint id;
	std::vector<std::shared_ptr<VertexBuffer> > buffers;
	bool dirty;
public:
	VertexArray();
	void setBuffer(std::string bufferName, std::shared_ptr<VertexBuffer> buffer);
	int getVertexCount();
	GLuint getId();
};