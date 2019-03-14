#include "Component.h"

#include <glm/glm.hpp>

class Transform : public Component
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Transform(
		glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));

	~Transform();

	void Position(glm::vec3 position);
	glm::vec3 Position();

	void Rotation(glm::vec3 rotation);
	glm::vec3 Rotation();

	void Scale(glm::vec3 scale);
	glm::vec3 Scale();

	void TranslateObject(glm::vec3 position);
	void RotateObject(glm::vec3 rotation);
	void ScaleObject(glm::vec3 scale);

	void UpdateModelMatrix();

	void Update();
};