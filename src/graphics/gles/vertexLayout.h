#if not defined(ANUT_VERTEX_LAYOUT_H)
#define ANUT_VERTEX_LAYOUT_H
#include "graphics/gles/gpuResource.h"
#include <GLES3/gl32.h>

namespace anut
{
namespace gl
{
class GpuBuffer;
	
class VertexLayout : public anut::gl::GpuResource
{
public:
	VertexLayout();
	virtual ~VertexLayout();
	
	bool init() override;
	void shutdown() override;
	void addLayout(const GpuBuffer& vb, unsigned attribIndex, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset);
	void setIndexBuffer(const GpuBuffer& eb);
	void setVertexAttribFrequency(unsigned attribIndex, unsigned divisor);
	void draw(GLenum primitive, int count) const;
	void drawIndexed(GLenum primitive, int count, GLenum indexType) const;
	void drawInstanced(GLenum primitive, int count, int instanceCount) const;
	void drawIndexedInstanced(GLenum primitive, int count, GLenum indexType, int instanceCount) const;
};
} // gl namespace
} // anut namespace

#endif

