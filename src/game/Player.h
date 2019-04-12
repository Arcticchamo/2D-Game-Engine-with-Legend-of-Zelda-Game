#include <engine/engine.h>
#include <iostream>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Transform;
class MeshRenderer;

class Player : public Component
{
private:
	std::weak_ptr<Transform> transform;
	std::weak_ptr<MeshRenderer> meshRenderer;
	
public:
	void Init();
	void Update();

	void InputController(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale);

	~Player();
};