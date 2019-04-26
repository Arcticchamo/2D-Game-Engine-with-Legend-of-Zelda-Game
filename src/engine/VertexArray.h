#include <GL/glew.h>
#include <iostream>
#include <vector>

class VertexBuffer;

//Vertex Array creates and stored buffers 
//Vertex Array is directly controlled by the MeshRenderer of an Object
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
	GLuint GetId();
};