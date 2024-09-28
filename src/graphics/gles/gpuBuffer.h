#if not defined(ANUT_BUFFER_H)
#define ANUT_BUFFER_H
#include "graphics/gles/gpuResource.h"
#include <GLES3/gl32.h>

namespace anut
{
namespace gl
{
class GpuBuffer : public anut::gl::GpuResource
{
public:
	GpuBuffer(GLenum bufferType);
	virtual ~GpuBuffer();
	
	bool init() override;
	void shutdown() override;
	void alloc(GLsizeiptr size, GLenum usage, const void* initialData = nullptr);
	void copyData(const void* data, GLsizeiptr size, GLintptr offset = 0 * sizeof(0));
	GLenum getBufferType() const;
	
private:
	GLenum _type;
};

inline GLenum GpuBuffer::getBufferType() const
{
	return _type;
}

} // gl namespace
} // anut namespace

#endif
