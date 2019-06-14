#include "Mesh.h"
#include "VertexArray.h"

//Creates the mesh insde of the VertexArray Constructor 
//TODO - MAKE IT SO THAT THEY ACTUALLY LOAD MESHES AND NOT THE DEFAULT SQUARE
void Mesh::Load(std::string path)
{
	filePath = path;
	sprite = std::make_shared<VertexArray>();
}

int Mesh::GetTriangleCount()
{
	return sprite->getVertexCount();
}

GLuint Mesh::GetId()
{
	return sprite->GetId();
}

Mesh::~Mesh()
{

}