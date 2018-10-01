#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	m_dirty = false;

	m_buffers.resize(10);

	glGenVertexArrays(1, &m_id);

	if (!m_id)
	{
		throw std::exception();
	}
}

void VertexArray::setBuffer(std::string _name, VertexBuffer* _buffer)
{
	if (_name == "in_Position")
	{
		m_buffers.at(0) = _buffer;
	}
	else if (_name == "in_Color")
	{
		m_buffers.at(1) = _buffer;
	}
	else
	{
		throw std::exception();
	}

	m_dirty = true;
}

int VertexArray::getVertexCount()
{
	if (!m_buffers.at(0))
	{
		throw std::exception();
	}

	return m_buffers.at(0)->getDataSize() / m_buffers.at(0)->getComponents();
}

GLuint VertexArray::getId()
{
	if (m_dirty)
	{
		glBindVertexArray(m_id);

		GLuint i = 0;

		for (auto it = m_buffers.begin(); it != m_buffers.end(); it++)
		{
			if (*it)
			{
				glBindBuffer(GL_ARRAY_BUFFER, (*it)->getId());
				glVertexAttribPointer(i,
					(*it)->getComponents(), GL_FLOAT, GL_FALSE,
					(*it)->getComponents() * sizeof(GLfloat), (void *)0);
				glEnableVertexAttribArray(i);
			}
			i++;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		m_dirty = false;
	}

	return m_id;
}