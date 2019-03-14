#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	
	
	dirty = false;

	buffers.resize(10);

	glGenVertexArrays(1, &id);

	if (!id)
	{
		throw std::exception();
	}
}

void VertexArray::setBuffer(std::string bufferName, std::shared_ptr<VertexBuffer> buffer)
{
	if (bufferName == "in_Position")
	{
		buffers.at(0) = buffer;
	}
	else if (bufferName == "in_Color")
	{
		buffers.at(1) = buffer;
	}
	else if (bufferName == "in_TexCoord")
	{
		buffers.at(2) = buffer;
	}
	else
	{
		throw std::exception();
	}

	dirty = true;
}

int VertexArray::getVertexCount()
{
	if (!buffers.at(0))
	{
		throw std::exception();
	}

	return buffers.at(0)->getDataSize() / buffers.at(0)->getComponents();
}

GLuint VertexArray::getId()
{
	if (dirty)
	{
		glBindVertexArray(id);

		GLuint i = 0;

		for (auto it = buffers.begin(); it != buffers.end(); it++)
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
		dirty = false;
	}

	return id;
}