#if not defined(ANUT_GLSL_COMPILER_H)
#define ANUT_GLSL_COMPILER_H
#include <string>

class GLSLCompiler
{
public:
	GLSLCompiler();
	virtual ~GLSLCompiler();
	
	bool Compile(const char* vert_filename, const char* frag_filename);
	unsigned Program() const;
	std::string Status() const;
	
private:
	bool Compile(unsigned shader, const char* source_file);
	bool Link();
	void Reset();
	
	std::string ShaderStatus(unsigned shader) const;
	std::string LinkerStatus() const;
	
	enum Error
	{
		NONE = 0b0,
		VERTEX_SHADER_ERROR = 0b1,
		FRAGMENT_SHADER_ERROR = 0b10,
		COMPILER_ERROR = VERTEX_SHADER_ERROR | FRAGMENT_SHADER_ERROR,
		LINKER_ERROR = 0b100
	};
	
	unsigned program;
	unsigned vertex_shader;
	unsigned fragment_shader;
	
	const char* vertex_name;
	const char* fragment_name;
	int error;
};


inline unsigned GLSLCompiler::Program() const 
{
	return error == NONE ? program : 0;
}

#endif
