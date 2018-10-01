#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	m_components = 0;
	m_dirty = false;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}
}

void VertexBuffer::add(glm::vec3 _data)
{
	if (m_components != 3 && m_components != 0)
	{
		throw std::exception();
	}
	m_data.push_back(_data.x);
	m_data.push_back(_data.y);
	m_data.push_back(_data.z);
	m_components = 3;
	m_dirty = true;
}

void VertexBuffer::add(glm::vec4 _data)
{
	if (m_components != 4 && m_components != 0)
	{
		throw std::exception();
	}
	m_data.push_back(_data.x);
	m_data.push_back(_data.y);
	m_data.push_back(_data.z);
	m_data.push_back(_data.w);
	m_components = 4;
	m_dirty = true;
}

int VertexBuffer::getComponents()
{
	return m_components;
}

int VertexBuffer::getDataSize()
{
	return m_data.size();
}

GLuint VertexBuffer::getId()
{
	if (m_dirty)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		// Upload a copy of the data from memory into the new VBO
		glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), &m_data.at(0), GL_STATIC_DRAW);
		// Reset the state
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	return m_id;
}
