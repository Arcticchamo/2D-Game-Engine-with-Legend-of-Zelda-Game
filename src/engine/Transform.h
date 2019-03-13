#include "Component.h"

#include <glm/glm.hpp>

class Transform : public Component
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Transform();
	Transform(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale);
	~Transform();

	void SetPosRotScale(glm::vec3 _posisition, glm::vec3 _rotation, glm::vec3 _scale);

	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetRotation(glm::vec3 rotation) { this->rotation = rotation; }
	void SetScale(glm::vec3 scale) { this->scale = scale; }

	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetRotation() { return rotation; }
	glm::vec3 GetScale() { return scale; }

	void Translate(glm::vec3 position);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	void UpdateModelMatrix();

	

	void Update();
};