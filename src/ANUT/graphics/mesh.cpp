#include "ANUT/graphics/mesh.h"
#include <GLES3/gl32.h>

Mesh::Mesh()
{
	vao = vbo = ibo = 0;
}

Mesh::~Mesh()
{
	Free();
}

void Mesh::Alloc(int vertex_count, int index_count, const unsigned layout[4], unsigned usage)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	vertex_size = 0;
	for (int i = 0; i < 4; i++)
	{
		vertex_size += layout[i] * sizeof(float);
	}
	
	for (int i=0, begin=0; i < 4 && layout[i] != 0; begin+=layout[i]*sizeof(float), i++)
	{
		glVertexAttribPointer(i, layout[i], GL_FLOAT, false, vertex_size, (void*) begin);
	}
	
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, nullptr, usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned), nullptr, usage);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::CopyData(const void* data, int vertex_count, const unsigned* index, int index_count, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ARRAY_BUFFER, i * vertex_size, vertex_count * vertex_size, data);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * sizeof(unsigned), index_count * sizeof(unsigned), index);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw(unsigned primitive, int count)
{
	glBindVertexArray(vao);
	glDrawElements(primitive, count, GL_UNSIGNED_INT, (void*) 0);
}

void Mesh::Free()
{
	if (vao != 0)
	{
		glDeleteVertexArrays(1, &vao);
	}
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
	}
	if (ibo != 0)
	{
		glDeleteBuffers(1, &ibo);
	}
	
	vao = vbo = ibo = 0;
	vertex_size = 0;
}
