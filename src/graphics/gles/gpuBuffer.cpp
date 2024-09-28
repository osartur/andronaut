#include "graphics/gles/gpuBuffer.h"

namespace anut
{
namespace gl 
{
GpuBuffer::GpuBuffer(GLenum bufferType)
{
	_type = bufferType;
}

GpuBuffer::~GpuBuffer()
{
	
}

bool GpuBuffer::init()
{
	glGenBuffers(1, &__handle);
	return true;
}

void GpuBuffer::shutdown()
{
	if (initialized())
	{
		glDeleteBuffers(1, &__handle);
		__handle = 0;
	}
}

void GpuBuffer::alloc(GLsizeiptr size, GLenum usage, const void* initialData)
{
	glBindBuffer(_type, __handle);
	glBufferData(_type, size, initialData, usage);
}

void GpuBuffer::copyData(const void* data, GLsizeiptr size, GLintptr offset)
{
	glBindBuffer(_type, __handle);
	glBufferSubData(_type, offset, size, data);
}
} // gl namespace
} // anut namespace

