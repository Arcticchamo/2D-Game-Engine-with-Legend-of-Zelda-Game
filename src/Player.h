#include <iostream>
#include <GL/glew.h>
#include <memory>

class VertexBuffer;
class VertexArray;
class ShaderProgram;

class Player
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

};