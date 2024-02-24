#include "graphics/mesh.h"
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
	
	BuildLayout(layout);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, nullptr, usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned), nullptr, usage);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Alloc(int vertex_count, const unsigned layout[4], unsigned usage)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	BuildLayout(layout);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, nullptr, usage);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int Mesh::BuildLayout(const unsigned layout[4])
{
	vertex_size = 0;
	int attribs_count = 0;
	for (int i = 0; i < 4 && layout[i] != 0; i++)
	{
		vertex_size += layout[i] * sizeof(float);
		attribs_count++;
	}
	
	for (int i = 0, offset = 0; i < attribs_count; offset += layout[i] * sizeof(float), i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, layout[i], GL_FLOAT, false, vertex_size, (void*) offset);
	}
}

void Mesh::Copy(int vertex_count, const void* data, int index_count, const unsigned* index, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, i * vertex_size, vertex_count * vertex_size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i * sizeof(unsigned), index_count * sizeof(unsigned), index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Copy(int vertex_count, const void* data, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, i * vertex_size, vertex_count * vertex_size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw(unsigned primitive, int count)
{
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, count);
	glBindVertexArray(0);
}

void Mesh::DrawIndexed(unsigned primitive, int count)
{
	glBindVertexArray(vao);
	// it should work without this line, but it doesn't. WHY?!
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
