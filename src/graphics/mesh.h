#if not defined(ANUT_MESH_H)
#define ANUT_MESH_H

class Vertex;

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	void Alloc(int count, const Vertex* data = nullptr);
	void Free();
	void MoveData(const Vertex* data, int count, int i = 0);
	
private:
	unsigned vao;
	unsigned vbo;
	unsigned ibo;
	unsigned vertex_count;
	
	friend void Draw(const Mesh& target, unsigned primitive, int size);
};

void Draw(const Mesh& target, unsigned primitive, int size);

#endif
