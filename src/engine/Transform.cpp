#include "Transform.h"
#include "Resources.h"

Transform::Transform()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}

Transform::Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale)
{
	position = _posisition;
	rotation = _rotation;
	scale = _scale;
}

Transform::~Transform()
{

}

void Transform::SetPosRotScale(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Transform::Translate(glm::vec3 _position)
{
	position += _position;
}

void Transform::Rotate(glm::vec3 _rotation)
{
	rotation += _rotation;
}

void Transform::Scale(glm::vec3 _scale)
{
	scale += _scale;
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
