#include "graphics/buffer.h"

namespace anut
{
// ********* GPU BUFFER ********* 

GPUBuffer::GPUBuffer(GLenum bufferType)
{
	_type = bufferType;
	glGenBuffers(1, &_id);
}

GPUBuffer::~GPUBuffer()
{
	glDeleteBuffers(1, &_id);
}

void GPUBuffer::alloc(GLsizeiptr size, GLenum usage, const void* initialData)
{
	glBindBuffer(_type, _id);
	glBufferData(_type, size, initialData, usage);
}

void GPUBuffer::copyData(const void* data, GLsizeiptr size, GLintptr offset)
{
	glBindBuffer(_type, _id);
	glBufferSubData(_type, offset, size, data);
}


// ********* VERTEX LAYOUT ********* 

VertexLayout::VertexLayout()
{
	glGenVertexArrays(1, &_id);
}

VertexLayout::~VertexLayout()
{
	glDeleteVertexArrays(1, &_id);
}

void VertexLayout::vertexBuffer(unsigned attribIndex, const GPUBuffer& target, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset)
{
	if (target.type() != GL_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(_id);
	glBindBuffer(GL_ARRAY_BUFFER, target.resourceId());
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, subAttribCount, subAttribType, normalized, stride, (void*) offset);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexLayout::indexBuffer(const GPUBuffer& target)
{
	if (target.type() != GL_ELEMENT_ARRAY_BUFFER)
	{
		// TODO: throw error
		return;
	}
	glBindVertexArray(_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, target.resourceId());
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexLayout::vertexAttribFrequency(unsigned attribIndex, unsigned divisor)
{
	glBindVertexArray(_id);
	glVertexAttribDivisor(attribIndex, divisor);
}

void VertexLayout::draw(GLenum primitive, int count) const
{
	glBindVertexArray(_id);
	glDrawArrays(primitive, 0, count);
}

void VertexLayout::drawIndexed(GLenum primitive, int count, GLenum indexType) const
{
	glBindVertexArray(_id);
	glDrawElements(primitive, count, indexType, (void*) 0);
}

void VertexLayout::drawInstanced(GLenum primitive, int count, int instanceCount) const
{
	glBindVertexArray(_id);
	glDrawArraysInstanced(primitive, 0, count, instanceCount);
}

void VertexLayout::drawIndexedInstanced(GLenum primitive, int count, GLenum indexType, int instanceCount) const
{
	glBindVertexArray(_id);
	glDrawElementsInstanced(primitive, count, indexType, (void*) 0, instanceCount);
}

} // anut namespace

