#include <GL/glew.h>
#include <iostream>
#include <vector>

class VertexBuffer;

class VertexArray
{
private:
	GLuint m_id;
	std::vector<std::shared_ptr<VertexBuffer> > m_buffers;
	bool m_dirty;

public:

	VertexArray();
	
	void setBuffer(std::string, std::shared_ptr<VertexBuffer>);
	int getVertexCount();
	GLuint getId();
};