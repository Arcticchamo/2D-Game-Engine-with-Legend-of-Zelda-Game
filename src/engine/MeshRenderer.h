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
	GLuint id;
	
	std::shared_ptr<Texture> texture;
	std::shared_ptr<VertexBuffer> positions;
	std::shared_ptr<VertexBuffer> texCoords;
	std::shared_ptr<VertexArray> sprite;
public:
	void Start();
	void StartNoTexture();

	void Init();
	void Update();
	
	void Render();
	void Render(std::shared_ptr<Texture> texture);

	GLuint GetID();
	~MeshRenderer();
};