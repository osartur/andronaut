#if not defined(ANUT_BUFFER_H)
#define ANUT_BUFFER_H
#include <GLES3/gl32.h>

namespace anut
{
class GPUBuffer
{
public:
	GPUBuffer(GLenum bufferType);
	virtual ~GPUBuffer();
	
	void alloc(GLsizeiptr size, GLenum usage, const void* initialData = nullptr);
	void copyData(const void* data, GLsizeiptr size, GLintptr offset = 0 * sizeof(float));
	unsigned resourceId() const;
	GLenum type() const;
	
private:
	unsigned _id;
	GLenum _type;
};

inline unsigned GPUBuffer::resourceId() const
{
	return _id;
}

inline GLenum GPUBuffer::type() const
{
	return _type;
}


class VertexLayout
{
public:
	VertexLayout();
	virtual ~VertexLayout();
	
	void vertexBuffer(unsigned attribIndex, const GPUBuffer& target, int subAttribCount, GLenum subAttribType, bool normalized, int stride, int offset);
	void indexBuffer(const GPUBuffer& target);
	void draw(GLenum primitive, int count) const;
	void drawIndexed(GLenum primitive, int count, GLenum indexType) const;
	
private:
	unsigned _id;
};
} // anut namespace

#endif
