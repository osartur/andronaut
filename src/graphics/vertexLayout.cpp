#include "graphics/vertexLayout.h"
#include "graphics/gpuBuffer.h"

namespace anut
{
VertexLayout::VertexLayout()
{
	
}

VertexLayout::~VertexLayout()
{
	
}

bool VertexLayout::init()
{
	glGenVertexArrays(1, &handle);
	return true;
}

void VertexLayout::shutdown()
{
	if (initialized())
	{
		glDeleteVertexArrays(1, &handle);
		handle = 0;
	}
}

void VertexLayout::setVertexBuffer(const GPUBuffer& buffer, unsigned attribIndex, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset)
{
	if (buffer.getBufferType() != GL_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(handle);
	glBindBuffer(GL_ARRAY_BUFFER, buffer.getResourceId());
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, subAttribCount, subAttribType, normalized, stride, (void*) offset);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexLayout::setIndexBuffer(const GPUBuffer& buffer)
{
	if (buffer.getBufferType() != GL_ELEMENT_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.getResourceId());
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexLayout::setVertexAttribFrequency(unsigned attribIndex, unsigned divisor)
{
	glBindVertexArray(handle);
	glVertexAttribDivisor(attribIndex, divisor);
}

void VertexLayout::draw(GLenum primitive, int count) const
{
	glBindVertexArray(handle);
	glDrawArrays(primitive, 0, count);
}

void VertexLayout::drawIndexed(GLenum primitive, int count, GLenum indexType) const
{
	glBindVertexArray(handle);
	glDrawElements(primitive, count, indexType, (void*) 0);
}

void VertexLayout::drawInstanced(GLenum primitive, int count, int instanceCount) const
{
	glBindVertexArray(handle);
	glDrawArraysInstanced(primitive, 0, count, instanceCount);
}

void VertexLayout::drawIndexedInstanced(GLenum primitive, int count, GLenum indexType, int instanceCount) const
{
	glBindVertexArray(handle);
	glDrawElementsInstanced(primitive, count, indexType, (void*) 0, instanceCount);
}
} // anut namespace