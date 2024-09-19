#include "graphics/gles/gpuBuffer.h"

namespace anut
{
namespace gl 
{
GPUBuffer::GPUBuffer(GLenum bufferType)
{
	_type = bufferType;
}

GPUBuffer::~GPUBuffer()
{
	
}

bool GPUBuffer::init()
{
	glGenBuffers(1, &handle);
	return true;
}

void GPUBuffer::shutdown()
{
	if (initialized())
	{
		glDeleteBuffers(1, &handle);
		handle = 0;
	}
}

void GPUBuffer::alloc(GLsizeiptr size, GLenum usage, const void* initialData)
{
	glBindBuffer(_type, handle);
	glBufferData(_type, size, initialData, usage);
}

void GPUBuffer::copyData(const void* data, GLsizeiptr size, GLintptr offset)
{
	glBindBuffer(_type, handle);
	glBufferSubData(_type, offset, size, data);
}
} // gl namespace
} // anut namespace

