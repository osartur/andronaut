#if not defined(ANUT_VERTEX_LAYOUT_H)
#define ANUT_VERTEX_LAYOUT_H
#include "graphics/gpuResource.h"
#include <GLES3/gl32.h>

namespace anut
{
class GPUBuffer;
	
class VertexLayout : public anut::GPUResource
{
public:
	VertexLayout();
	virtual ~VertexLayout();
	
	bool init() override;
	void shutdown() override;
	void setVertexBuffer(const GPUBuffer& buffer, unsigned attribIndex, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset);
	void setIndexBuffer(const GPUBuffer& buffer);
	void setVertexAttribFrequency(unsigned attribIndex, unsigned divisor);
	void draw(GLenum primitive, int count) const;
	void drawIndexed(GLenum primitive, int count, GLenum indexType) const;
	void drawInstanced(GLenum primitive, int count, int instanceCount) const;
	void drawIndexedInstanced(GLenum primitive, int count, GLenum indexType, int instanceCount) const;
};
}

#endif

