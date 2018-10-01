#include "ShaderProgram.h"
#include "VertexArray.h"

ShaderProgram::ShaderProgram()
{
	m_id = 0;

	std::string vertShader = ReadFile("../shaders/simple.vert");
	std::string fragShader = ReadFile("../shaders/simple.frag");

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = GenerateVertexShader(vertex);
	GLuint fragmentShaderId = GenerateFragmentShader(fragment);

	CreateProgram(vertexShaderId, fragmentShaderId);

	glDetachShader(m_id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

ShaderProgram::ShaderProgram(std::string _vertex, std::string _fragment)
{
	m_id = 0;

	std::string vertShader = ReadFile(_vertex);
	std::string fragShader = ReadFile(_fragment);

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = GenerateVertexShader(vertex);
	GLuint fragmentShaderId = GenerateFragmentShader(fragment);

	CreateProgram(vertexShaderId, fragmentShaderId);

	glDetachShader(m_id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

ShaderProgram::~ShaderProgram()
{

}

std::string ShaderProgram::ReadFile(std::string _filename)
{
	std::ifstream file(_filename);
	std::string text;

	if (!file.is_open())
	{
		throw std::exception();
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			text += line + "\n";
		}
	}

	file.close();
	return text;
}

GLuint ShaderProgram::GenerateVertexShader(const char *_vertex)
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &_vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
	return vertexShaderId;
}

GLuint ShaderProgram::GenerateFragmentShader(const char *_fragment)
{
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &_fragment, NULL);
	glCompileShader(fragmentShaderId);
	GLint success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
	return fragmentShaderId;
}

void ShaderProgram::CreateProgram(GLuint _vertexId, GLuint _fragmentId)
{
	m_id = glCreateProgram();
	glAttachShader(m_id, _vertexId);
	glAttachShader(m_id, _fragmentId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(m_id, 0, "in_Position");
	glBindAttribLocation(m_id, 1, "in_Color");
	// Perform the link and check for failure
	glLinkProgram(m_id);
	GLint success = 0;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
}

void ShaderProgram::Draw(std::weak_ptr<VertexArray> _vertexArray)
{
	glUseProgram(m_id);
	glBindVertexArray(_vertexArray.lock()->getId());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}

void ShaderProgram::setUniform(std::string _uniform, glm::vec4 _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
	glUseProgram(0);
}

void ShaderProgram::setUniform(std::string _uniform, float _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniform1f(uniformId, _value);
	glUseProgram(0);
}

void ShaderProgram::setUniform(std::string _uniform, glm::mat4 _value)
{
	GLint uniformId = glGetUniformLocation(m_id, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(m_id);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

GLuint ShaderProgram::getId()
{
	return m_id;
}