#include "Resources.h"

GLuint Resources::globalProgram;


Resources::Resources()
{
}


Resources::~Resources()
{
}

void Resources::Start()
{
	globalProgram = 0;

	std::string vertShader = ReadFile("../shaders/simple.vert");
	std::string fragShader = ReadFile("../shaders/simple.frag");

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = GenerateVertexShader(vertex);
	GLuint fragmentShaderId = GenerateFragmentShader(fragment);

	CreateProgram(vertexShaderId, fragmentShaderId);

	glDetachShader(globalProgram, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(globalProgram, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void Resources::Start(std::string _vert, std::string _frag)
{
	globalProgram = 0;

	std::string vertShader = ReadFile(_vert);
	std::string fragShader = ReadFile(_frag);

	const char *vertex = vertShader.c_str();
	const char *fragment = fragShader.c_str();

	GLuint vertexShaderId = GenerateVertexShader(vertex);
	GLuint fragmentShaderId = GenerateFragmentShader(fragment);

	CreateProgram(vertexShaderId, fragmentShaderId);

	glDetachShader(globalProgram, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(globalProgram, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

std::string Resources::ReadFile(std::string _fileName)
{
	std::ifstream file(_fileName);
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

GLuint Resources::GenerateVertexShader(const char* _vertex)
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

GLuint Resources::GenerateFragmentShader(const char*_fragment)
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

void Resources::CreateProgram(GLuint _vertexId, GLuint _fragmentId)
{
	globalProgram = glCreateProgram();
	glAttachShader(globalProgram, _vertexId);
	glAttachShader(globalProgram, _fragmentId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(globalProgram, 0, "in_Position");
	glBindAttribLocation(globalProgram, 1, "in_Color");
	// Perform the link and check for failure
	glLinkProgram(globalProgram);
	GLint success = 0;
	glGetProgramiv(globalProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
}

void Resources::SetUniform(std::string _uniform, int _value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform1i(uniformId, _value);
	glUseProgram(0);
}

void Resources::SetUniform(std::string _uniform, float _value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform1f(uniformId, _value);
	glUseProgram(0);
}

void Resources::SetUniform(std::string _uniform, glm::vec4 _value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
	glUseProgram(0);
}

void Resources::SetUniform(std::string _uniform, glm::mat4 _value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, _uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

GLuint Resources::GetProgram()
{
	return globalProgram;
}