#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include <vector>

class Texture;
class VertexArray;

struct Sampler
{
	std::shared_ptr<Texture> m_texture;
	GLuint uniformId;
};

class Resources
{
private:
	static GLuint globalProgram;
	static std::vector<Sampler> samplers;

public:
	Resources();
	~Resources();

	static void Start();
	static void Start(std::string, std::string);

	static std::string ReadFile(std::string);
	static GLuint GenerateVertexShader(const char*);
	static GLuint GenerateFragmentShader(const char*);
	static void CreateProgram(GLuint, GLuint);

	static void Draw(VertexArray*);

	static void SetUniform(std::string, int);
	static void SetUniform(std::string, std::shared_ptr<Texture>);
	static void SetUniform(std::string, float);
	static void SetUniform(std::string, glm::vec4);
	static void SetUniform(std::string, glm::mat4);



	static GLuint GetProgram();
};

