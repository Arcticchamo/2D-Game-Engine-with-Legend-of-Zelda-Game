#include <iostream>
#include <GL/glew.h>
#include <memory>

#include "GameObject.h"

class VertexBuffer;
class VertexArray;
class ShaderProgram;




class Player : public GameObject
{
private:
	std::shared_ptr<VertexArray> m_attributes;
	std::weak_ptr<ShaderProgram> m_shader;

public:
	Player();
	~Player();

	void Start();
	void Update();
	void Destroy();

	void SetShader(std::shared_ptr<ShaderProgram>);

	std::shared_ptr<VertexArray> GetVAO() { return m_attributes; }
};