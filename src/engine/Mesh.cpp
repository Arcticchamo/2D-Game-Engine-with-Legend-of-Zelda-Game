#include "Mesh.h"
#include "VertexArray.h"

std::shared_ptr<Mesh> Mesh::Init(std::string path)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Load(path);
	return mesh;
}

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
	return sprite->getId();
}

Mesh::~Mesh()
{

}