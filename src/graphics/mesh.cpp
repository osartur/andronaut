#include "graphics/mesh.h"
#include "graphics/vertex.h"
#include <GLES3/gl32.h>

Mesh::Mesh()
{
	vao = vbo = ibo = 0;
}

Mesh::~Mesh()
{
	Free();
}

void Mesh::Alloc(int count, const Vertex* data)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (4 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	unsigned usage = data == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), data, usage);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	vertex_count = count;
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
}

void Mesh::MoveData(const Vertex* data, int count, int i)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, i * sizeof(Vertex), count * sizeof(Vertex), data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Draw(const Mesh& target, unsigned primitive, int size)
{
	glBindVertexArray(target.vao);
	glDrawArrays(primitive, 0, size);
	glBindVertexArray(0);
}
