// sorry! I'll remake this

#if not defined(ANUT_MESH_H)
#define ANUT_MESH_H

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	// with index
	void Alloc(int vertex_count, int index_count, const unsigned layout[4], unsigned usage);
	void Copy(int vertex_count, const void* data, int index_count, const unsigned* index, int i = 0);
	// no index
	void Alloc(int vertex_count, const unsigned layout[4], unsigned usage);
	void Copy(int vertex_count, const void* data, int i = 0);
	
	void Draw(unsigned primitive, int count);
	void DrawIndexed(unsigned primitive, int count);
	void Free();
	
private:
	int BuildLayout(const unsigned layout[]);
	
	unsigned vao;
	unsigned vbo;
	unsigned ibo;
	int vertex_size;
};

#endif
