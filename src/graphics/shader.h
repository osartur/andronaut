#if not defined(ANUT_SHADER_H)
#define ANUT_SHADER_H

class Shader
{
public:
	Shader();
	~Shader();
	
	bool Init(const char* vert_filename, const char* frag_filename);
	void Delete();
	
private:
	bool Compile(const char* filename, unsigned target_shader);
	
	unsigned program;
	unsigned vshader;
	unsigned fshader;
	
	friend void SetCurrentShader(const Shader& target);
};

void SetCurrentShader(const Shader& target);
void SetCurrentShader();

#endif
