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

void Mesh::Alloc(int vertex_count, int index_count, const unsigned attribs_count[4], unsigned usage)
{
	vertex_size = 0;
	int attribs_size = 0;
	for (int i = 0; i < 4 && attribs_count[i] != 0; i++)
	{
		vertex_size += attribs_count[i] * sizeof(float);
		attribs_size++;
	}
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, nullptr, usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned), nullptr, usage);
	
	for (int i=0, begin=0; i < attribs_size; begin+=attribs_count[i]*sizeof(float), i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribs_count[i], GL_FLOAT, false, vertex_size, (void*) begin);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::CopyData(const void* data, int vertex_count, const unsigned* index, int index_count, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, i * vertex_size, vertex_count * vertex_size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * sizeof(unsigned), index_count * sizeof(unsigned), index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw(unsigned primitive, int count)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(primitive, count, GL_UNSIGNED_INT, (void*) 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
