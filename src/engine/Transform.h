#include "Component.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Transform : public Component
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void Update();
public:
	//Initialize with default origin parameters
	void Init(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	Transform() {}
	~Transform() {}

	//Setters over-right the values with a new value 
	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	//Translate, Rotate and Scale apply a value to the existing value
	void Translate(glm::vec3 position);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	//Generates the model Matrix and returns it
	glm::mat4 GetModelMatrix();
};