#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	components = 0;
	dirty = false;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &id);

	if (!id)
	{
		throw std::exception();
	}
}

void VertexBuffer::add(glm::vec2 data)
{
	if (components != 2 && components != 0)
	{
		throw std::exception();
	}
	this->data.push_back(data.x);
	this->data.push_back(data.y);
	components = 2;
	dirty = true;
}

void VertexBuffer::add(glm::vec3 data)
{
	if (components != 3 && components != 0)
	{
		throw std::exception();
	}
	this->data.push_back(data.x);
	this->data.push_back(data.y);
	this->data.push_back(data.z);
	components = 3;
	dirty = true;
}

void VertexBuffer::add(glm::vec4 data)
{
	if (components != 4 && components != 0)
	{
		throw std::exception();
	}
	this->data.push_back(data.x);
	this->data.push_back(data.y);
	this->data.push_back(data.z);
	this->data.push_back(data.w);
	components = 4;
	dirty = true;
}

int VertexBuffer::getComponents()
{
	return components;
}

int VertexBuffer::getDataSize()
{
	return data.size();
}

GLuint VertexBuffer::getId()
{
	if (dirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		// Upload a copy of the data from memory into the new VBO
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.at(0), GL_STATIC_DRAW);
		// Reset the state
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		dirty = false;
	}

	return id;
}
