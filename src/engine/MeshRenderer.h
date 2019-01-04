#include "Component.h"
#include "Texture.h"

#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <string>

class VertexArray;
class VertexBuffer;

class MeshRenderer : public Component
{
private:
	GLuint m_id;
	
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<VertexBuffer> m_positions;
	std::shared_ptr<VertexBuffer> m_texCoords;
	std::shared_ptr<VertexArray> m_sprite;
public:
	MeshRenderer();

	void Start();
	void Start(GLuint textureID);

	void Init();
	void Update();
	void Destroy();
	
	void Render();

	GLuint GetID();
	~MeshRenderer();
};