#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

class VertexArray;

class ShaderProgram
{
private:
	GLuint m_id;

public:
	ShaderProgram();
	ShaderProgram(std::string, std::string);
	~ShaderProgram();

	std::string ReadFile(std::string);

	GLuint GenerateVertexShader(const char*);
	GLuint GenerateFragmentShader(const char*);
	void CreateProgram(GLuint, GLuint);

	void Draw(GLuint);

	void ShaderProgram::setUniform(std::string, glm::vec4);
	void ShaderProgram::setUniform(std::string, float value);
	void ShaderProgram::setUniform(std::string, int value);
	void ShaderProgram::setUniform(std::string, glm::mat4);

	GLuint getId();
};