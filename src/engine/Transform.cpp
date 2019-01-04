#include "Transform.h"
#include "Resources.h"

Transform::Transform()
{
	m_position = glm::vec3(0, 0, 0);
	m_rotation = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
}

Transform::Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale)
{
	m_position = _posisition;
	m_rotation = _rotation;
	m_scale = _scale;
}

Transform::~Transform()
{

}

void Transform::SetPosRotScale(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale)
{
	m_position = _posisition;
	m_rotation = _rotation;
	m_scale = _scale;
}

void Transform::Translate(glm::vec3 _position)
{
	m_position += _position;
}

void Transform::Rotate(glm::vec3 _rotation)
{
	m_rotation += _rotation;
}

void Transform::Scale(glm::vec3 _scale)
{
	m_scale += _scale;
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 modelMatrix(1.0f);

	glm::mat4 rotXmatrix(1.0f);
	glm::mat4 rotYmatrix(1.0f);
	glm::mat4 rotZmatrix(1.0f);

	modelMatrix = glm::translate(modelMatrix, m_position);

	rotXmatrix = glm::rotate(rotXmatrix, m_rotation.x, glm::vec3(1, 0, 0));
	rotYmatrix = glm::rotate(rotYmatrix, m_rotation.y, glm::vec3(0, 1, 0));
	rotZmatrix = glm::rotate(rotZmatrix, m_rotation.z, glm::vec3(0, 0, 1));

	modelMatrix *= rotZmatrix * rotYmatrix * rotXmatrix;

	modelMatrix = glm::scale(modelMatrix, m_scale);

	Resources::SetUniform("in_ModelMat", modelMatrix);
}

void Transform::Update()
{
	
}
