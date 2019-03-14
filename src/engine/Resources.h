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
	std::shared_ptr<Texture> texture;
	GLuint uniformId;
};

class Resources
{
private:
	static GLuint globalProgram;
	static std::vector<Sampler> samplers;

public:

	static void Start(std::string vertShader = "../shaders/simple.vert", std::string fragShader = "../shaders/simple.frag");

	static std::string ReadFile(std::string fileName);
	static GLuint GenerateVertexShader(std::string &vertex);
	static GLuint GenerateFragmentShader(std::string &fragment);
	static void CreateProgram(GLuint vertexId, GLuint fragmentId);

	static void Draw(std::weak_ptr<VertexArray> vertex);

	static void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
	static void SetUniform(std::string uniform, int value);
	static void SetUniform(std::string uniform, float value);
	static void SetUniform(std::string uniform, glm::vec4 value);
	static void SetUniform(std::string uniform, glm::mat4 value);

	static GLuint GetProgram();
};

