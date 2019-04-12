#include "Material.h"
#include "Shader.h"
#include "Texture.h"

#define FLOAT_ATTRIBUTE 1
#define INT_ATTRIBUTE 2
#define TEXTURE_ATTRIBUTE 3
#define MIXED_ATTRIBUTE 4

struct MaterialAttribute
{
	std::string name;
	int type;
	float floatValue;
	std::weak_ptr<Texture> textureValue;
};

Material::Material()
{}

Material::~Material()
{}

void Material::SetShader(std::weak_ptr<Shader> shader)
{
	this->shader = shader;
}

std::shared_ptr<Shader> Material::GetShader()
{
	return shader.lock();
}

void Material::SetValue(std::string name, std::weak_ptr<Texture> value)
{
	MaterialAttribute mat;
	mat.name = name;
	mat.textureValue = value;
	mat.type = TEXTURE_ATTRIBUTE;
	for (std::vector<MaterialAttribute>::iterator it = attributes.begin(); it != attributes.end(); it++)
	{
		if (it->name == mat.name)
		{
			(*it) = mat;
			return;
		}
	}
	attributes.push_back(mat);
}

void Material::SetValue(std::string name, float value)
{
	MaterialAttribute mat;
	mat.name = name;
	mat.floatValue = value;
	mat.type = FLOAT_ATTRIBUTE;

	for (std::vector<MaterialAttribute>::iterator it = attributes.begin(); it != attributes.end(); it++)
	{
		if (it->name == mat.name)
		{
			(*it) = mat;
			return;
		}
	}
	attributes.push_back(mat);
}

void Material::SetValue(std::string name, std::weak_ptr<Texture> textureValue, float floatValue)
{
	MaterialAttribute mat;
	mat.name = name;
	mat.floatValue = floatValue;
	mat.textureValue = textureValue;
	mat.type = MIXED_ATTRIBUTE;

	for (std::vector<MaterialAttribute>::iterator it = attributes.begin(); it != attributes.end(); it++)
	{
		if (it->name == mat.name)
		{
			(*it) = mat;
			return;
		}
	}
	attributes.push_back(mat);
}

void Material::Apply()
{
	for (size_t i = 0; i < attributes.size(); i++)
	{
		if (attributes.at(i).type == TEXTURE_ATTRIBUTE)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, attributes.at(i).textureValue.lock()->GetId());
			glUniform1i(shader.lock()->GetId(), i);
		}
	}
}

void Material::Remove()
{
	for (size_t i = 0; i < attributes.size(); i++)
	{
		if (attributes.at(i).type == TEXTURE_ATTRIBUTE)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}