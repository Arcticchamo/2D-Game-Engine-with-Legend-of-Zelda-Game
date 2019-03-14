#include "Resources.h"
#include "Texture.h"
#include "VertexArray.h"

GLuint Resources::globalProgram;
std::vector<Sampler> Resources::samplers;

void Resources::Start(std::string vert, std::string frag)
{
	globalProgram = 0;

	std::string vertShader = ReadFile(vert);
	std::string fragShader = ReadFile(frag);

	GLuint vertexShaderId = GenerateVertexShader(vertShader);
	GLuint fragmentShaderId = GenerateFragmentShader(fragShader);

	CreateProgram(vertexShaderId, fragmentShaderId);

	glDetachShader(globalProgram, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(globalProgram, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

std::string Resources::ReadFile(std::string fileName)
{
	std::ifstream file(fileName);
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

GLuint Resources::GenerateVertexShader(std::string &vertex)
{
	const char* v = vertex.c_str();
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &v, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
	return vertexShaderId;
}

GLuint Resources::GenerateFragmentShader(std::string &fragment)
{
	const char* f = fragment.c_str();
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &f, NULL);
	glCompileShader(fragmentShaderId);
	GLint success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
	return fragmentShaderId;
}

void Resources::CreateProgram(GLuint vertexId, GLuint fragmentId)
{
	globalProgram = glCreateProgram();
	glAttachShader(globalProgram, vertexId);
	glAttachShader(globalProgram, fragmentId);
	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(globalProgram, 0, "in_Position");
	glBindAttribLocation(globalProgram, 1, "in_Color");
	glBindAttribLocation(globalProgram, 2, "in_TexCoord");
	// Perform the link and check for failure
	glLinkProgram(globalProgram);
	GLint success = 0;
	glGetProgramiv(globalProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(globalProgram, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(globalProgram, maxLength, &maxLength, &errorLog[0]);

		throw std::exception();
	}
}

void Resources::Draw(std::weak_ptr<VertexArray> vertex)
{
	glUseProgram(globalProgram);
	glBindVertexArray(vertex.lock()->getId());

	for (size_t i = 0; i < samplers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		if (samplers.at(i).
			
			
			texture)
		{
			glBindTexture(GL_TEXTURE_2D, samplers.at(i).texture->GetId());
			//glBindTexture(GL_TEXTURE_2D, 1);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	glDrawArrays(GL_TRIANGLES, 0, vertex.lock()->getVertexCount());

	for (size_t i = 0; i < samplers.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

void Resources::SetUniform(std::string uniform, std::shared_ptr<Texture> texture)
{
	GLint uniformId = glGetUniformLocation(globalProgram, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	for (size_t i = 0; i < samplers.size(); i++)
	{
		if (samplers.at(i).uniformId == uniformId)
		{
			samplers.at(i).texture = texture;

			glUseProgram(globalProgram);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
		}
	}

	Sampler s;
	s.uniformId = uniformId;
	s.texture = texture;
	samplers.push_back(s);

	glUseProgram(globalProgram);
	glUniform1i(uniformId, samplers.size() - 1);
	glUseProgram(0);
}

void Resources::SetUniform(std::string uniform, int value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform1i(uniformId, value);
	glUseProgram(0);
}

void Resources::SetUniform(std::string uniform, float value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform1f(uniformId, value);
	glUseProgram(0);
}

void Resources::SetUniform(std::string uniform, glm::vec4 value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniform4f(uniformId, value.x, value.y, value.z, value.w);
	glUseProgram(0);
}

void Resources::SetUniform(std::string uniform, glm::mat4 value)
{
	GLint uniformId = glGetUniformLocation(globalProgram, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(globalProgram);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
	glUseProgram(0);
}

GLuint Resources::GetProgram()
{
	return globalProgram;
}