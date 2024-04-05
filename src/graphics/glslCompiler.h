#if not defined(ANUT_GLSL_COMPILER_H)
#define ANUT_GLSL_COMPILER_H
#include <GLES3/gl32.h>
#include <string>

class GLSLCompiler
{
public:
	GLSLCompiler();
	virtual ~GLSLCompiler();
	
	bool compile(const char* vertFilename, const char* fragFilename);
	unsigned shaderId() const;
	std::string status() const;
	
private:
	bool compile(unsigned shader, const char* sourceFile);
	bool link();
	void reset();
	
	std::string shaderStatus(unsigned shader) const;
	std::string linkerStatus() const;
	
	enum Error : int
	{
		NONE = 0b0,
		VERTEX_SHADER_ERROR = 0b1,
		FRAGMENT_SHADER_ERROR = 0b10,
		COMPILER_ERROR = VERTEX_SHADER_ERROR | FRAGMENT_SHADER_ERROR,
		LINKER_ERROR = 0b100
	};
	
	const char* _vertexShaderFilename;
	const char* _fragmentShaderFilename;
	unsigned _program;
	unsigned _vertexShader;
	unsigned _fragmentShader;
	int _error;
};


inline unsigned GLSLCompiler::shaderId() const 
{
	return _error == NONE ? _program : 0u;
}

#endif
