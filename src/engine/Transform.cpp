#include "Transform.h"

void Transform::Update()
{
}

void Transform::Init(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Transform::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Transform::SetRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Transform::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::vec3 Transform::GetRotation()
{
	return rotation;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

void Transform::Translate(glm::vec3 position)
{
	this->position += position;
}

void Transform::Rotate(glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Transform::Scale(glm::vec3 scale)
{
	this->scale += scale;
}

glm::mat4 Transform::GetModelMatrix()
{
	//Generate an empty mat4
	glm::mat4 modelMatrix(1.0f);
	//Create individual rotation mat4 so that can can be each manipulated seperately and then times together
	glm::mat4 rotXmatrix(1.0f);
	glm::mat4 rotYmatrix(1.0f);
	glm::mat4 rotZmatrix(1.0f);

	//Apply transform elements to mat4
	modelMatrix = glm::translate(modelMatrix, position);

	rotXmatrix = glm::rotate(rotXmatrix, rotation.x, glm::vec3(1, 0, 0));
	rotYmatrix = glm::rotate(rotYmatrix, rotation.y, glm::vec3(0, 1, 0));
	rotZmatrix = glm::rotate(rotZmatrix, rotation.z, glm::vec3(0, 0, 1));
	modelMatrix *= rotZmatrix * rotYmatrix * rotXmatrix;

	modelMatrix = glm::scale(modelMatrix, scale);

	return modelMatrix;
}