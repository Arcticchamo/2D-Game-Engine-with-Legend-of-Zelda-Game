#include "Resource.h"

#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <memory>
#include <Vector>

class Texture;

struct Sampler
{
	std::shared_ptr<Texture> texture;
	GLuint uniformId;
};

class Shader : public Resource
{
private:
	GLuint id;
	std::vector<Sampler> samplers;

	void Load(std::string path);
	std::string ReadFile(std::string fileName);
	GLuint GenerateVertexShader(std::string &vertex);
	GLuint GenerateFragmentShader(std::string &fragment);
	void CreateProgram(GLuint vertexId, GLuint fragmentId);
public:
	~Shader() {}
	static std::shared_ptr<Shader> Init(std::string path);
	void SetUniform(std::string uniform, std::shared_ptr<Texture> texture);
	void SetUniform(std::string uniform, int value);
	void SetUniform(std::string uniform, float value);
	void SetUniform(std::string uniform, glm::vec4 value);
	void SetUniform(std::string uniform, glm::mat4 value);
	GLuint GetId();
};