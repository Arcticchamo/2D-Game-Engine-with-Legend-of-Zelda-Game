#include "Component.h"

#include <glm/glm.hpp>

class Transform : public Component
{
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	//glm::mat4 m_modelMat;

	glm::mat4 m_positionMat;
	glm::mat4 m_rotationMat;
	glm::mat4 m_scaleMat;

public:
	Transform();
	Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale);
	~Transform();

	void Translate(glm::vec3 _position);
	void Rotate(glm::vec3 _angle);
	void Scale(glm::vec3 _scale);
	void UpdateModelMatrix();

	void Update();
};