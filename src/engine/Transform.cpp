#include "Transform.h"
#include "Resources.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Transform::~Transform()
{

}

void Transform::Position(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Transform::Position()
{
	return position;
}

void Transform::Rotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

glm::vec3 Transform::Rotation()
{
	return rotation;
}

void Transform::Scale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 Transform::Scale()
{
	return scale;
}

void Transform::TranslateObject(glm::vec3 position)
{
	this->position += position;
}

void Transform::RotateObject(glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Transform::ScaleObject(glm::vec3 scale)
{
	this->scale += scale;
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 modelMatrix(1.0f);

	glm::mat4 rotXmatrix(1.0f);
	glm::mat4 rotYmatrix(1.0f);
	glm::mat4 rotZmatrix(1.0f);

	modelMatrix = glm::translate(modelMatrix, position);

	rotXmatrix = glm::rotate(rotXmatrix, rotation.x, glm::vec3(1, 0, 0));
	rotYmatrix = glm::rotate(rotYmatrix, rotation.y, glm::vec3(0, 1, 0));
	rotZmatrix = glm::rotate(rotZmatrix, rotation.z, glm::vec3(0, 0, 1));

	modelMatrix *= rotZmatrix * rotYmatrix * rotXmatrix;

	modelMatrix = glm::scale(modelMatrix, scale);

	Resources::SetUniform("in_ModelMat", modelMatrix);
}

void Transform::Update()
{
	
}
