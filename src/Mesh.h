#include "Component.h"

#include <GL/glew.h>
#include <stb_image/stb_image.h>
#include <string>

class VertexArray;
class VertexBuffer;


class Mesh : public Component
{
private:
	std::shared_ptr<VertexBuffer> m_positions;
	std::shared_ptr<VertexBuffer> m_texCoords;

	std::shared_ptr<VertexArray> m_sprite;

	GLuint m_textureID;

public:

	void Start();
	void Update();
	void Destroy();

	void Init();

	void CreateTexture(std::string);

	GLuint GetID();
	GLuint GetTextureID();

	~Mesh();
};