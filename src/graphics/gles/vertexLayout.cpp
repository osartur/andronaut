#include "graphics/gles/vertexLayout.h"
#include "graphics/gles/gpuBuffer.h"

namespace anut
{
namespace gl
{
VertexLayout::VertexLayout()
{
	
}

VertexLayout::~VertexLayout()
{
	
}

bool VertexLayout::init()
{
	glGenVertexArrays(1, &__handle);
	return true;
}

void VertexLayout::shutdown()
{
	if (initialized())
	{
		glDeleteVertexArrays(1, &__handle);
		__handle = 0;
	}
}

void VertexLayout::addLayout(const GpuBuffer& vb, unsigned attribIndex, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset)
{
	if (vb.getBufferType() != GL_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(__handle);
	glBindBuffer(GL_ARRAY_BUFFER, vb.getId());
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, subAttribCount, subAttribType, normalized, stride, (void*) offset);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexLayout::setIndexBuffer(const GpuBuffer& eb)
{
	if (eb.getBufferType() != GL_ELEMENT_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(__handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb.getId());
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexLayout::setVertexAttribFrequency(unsigned attribIndex, unsigned divisor)
{
	glBindVertexArray(__handle);
	glVertexAttribDivisor(attribIndex, divisor);
}

void VertexLayout::draw(GLenum primitive, int count) const
{
	glBindVertexArray(__handle);
	glDrawArrays(primitive, 0, count);
}

void VertexLayout::drawIndexed(GLenum primitive, int count, GLenum indexType) const
{
	glBindVertexArray(__handle);
	glDrawElements(primitive, count, indexType, (void*) 0);
}

void VertexLayout::drawInstanced(GLenum primitive, int count, int instanceCount) const
{
	glBindVertexArray(__handle);
	glDrawArraysInstanced(primitive, 0, count, instanceCount);
}

void VertexLayout::drawIndexedInstanced(GLenum primitive, int count, GLenum indexType, int instanceCount) const
{
	glBindVertexArray(__handle);
	glDrawElementsInstanced(primitive, count, indexType, (void*) 0, instanceCount);
}
} // gl namespace
} // anut namespace