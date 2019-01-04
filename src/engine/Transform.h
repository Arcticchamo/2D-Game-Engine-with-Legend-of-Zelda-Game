#include "Component.h"

#include <glm/glm.hpp>

class Transform : public Component
{
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

public:
	Transform();
	Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale);
	~Transform();

	void SetPosRotScale(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale);

	void Translate(glm::vec3 _position);
	void Rotate(glm::vec3 _rotation);
	void Scale(glm::vec3 _scale);
	void UpdateModelMatrix();

	void Update();
};