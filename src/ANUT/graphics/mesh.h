#if not defined(ANUT_MESH_H)
#define ANUT_MESH_H

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	void Alloc(int vertex_count, int index_count, const unsigned layout[4], unsigned usage);
	void CopyData(const void* data, int vertex_count, const unsigned* index, int index_count, int i = 0);
	void Draw(unsigned primitive, int count);
	void Free();
	
private:
	unsigned vao;
	unsigned vbo;
	unsigned ibo;
	int vertex_size;
};

#endif
