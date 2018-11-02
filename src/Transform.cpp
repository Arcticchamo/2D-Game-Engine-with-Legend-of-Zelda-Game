#include "Transform.h"
#include "Resources.h"

Transform::Transform()
{
	m_position = glm::vec3(0, 0, 0);
	m_rotation = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(0, 0, 0);

	//m_modelMat = glm::mat4(1.0f);

	m_positionMat = glm::mat4(1.0f);
	m_rotationMat = glm::mat4(1.0f);
	m_scaleMat = glm::mat4(1.0f);
}

Transform::Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale)
{
	m_position = _posisition;
	m_rotation = _rotation;
	m_scale = _scale;

	//m_modelMat = glm::mat4(1.0f);

	m_positionMat = glm::mat4(1.0f);
	m_rotationMat = glm::mat4(1.0f);
	m_scaleMat = glm::mat4(1.0f);
}

Transform::~Transform()
{

}

void Transform::Translate(glm::vec3 _position)
{
	m_position += _position;
	glm::translate(m_positionMat, m_position);
}

void Transform::Rotate(glm::vec3 _angle)
{
	glm::mat4 rotXmatrix(1.0f);
	glm::mat4 rotYmatrix(1.0f);
	glm::mat4 rotZmatrix(1.0f);

	m_rotation += _angle;

	glm::rotate(rotXmatrix, m_rotation.x, glm::vec3(1, 0, 0));
	glm::rotate(rotYmatrix, m_rotation.y, glm::vec3(0, 1, 0));
	glm::rotate(rotZmatrix, m_rotation.z, glm::vec3(0, 0, 1));
	
	m_rotationMat = rotZmatrix * rotYmatrix * rotXmatrix;
}

void Transform::Scale(glm::vec3 _scale)
{
	glm::scale(m_scaleMat, _scale);
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 m_modelMat(1.0f);
	m_modelMat = m_positionMat * m_rotationMat * m_scaleMat;

	Resources::SetUniform("in_ModelMat", m_modelMat);

	//m_modelMat = glm::mat4(1.0f);
	m_positionMat = glm::mat4(1.0f);
	m_rotationMat = glm::mat4(1.0f);
	m_scaleMat = glm::mat4(1.0f);
}

void Transform::Update()
{
	
}
