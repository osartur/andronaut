#if not defined(ANUT_GLSL_COMPILER_H)
#define ANUT_GLSL_COMPILER_H
#include <GLES3/gl32.h>
#include <string>

namespace anut
{
class GLSLCompiler
{
public:
	GLSLCompiler();
	virtual ~GLSLCompiler();
	
	bool compile(const char* vertFilename, const char* fragFilename);
	const std::string& status() const;
	unsigned shaderId() const;
	
private:
	bool compile(unsigned shader, const char* sourceFile);
	bool link();
	void reset();
	void logErrors();
	std::string shaderStatus(unsigned shader) const;
	std::string linkerStatus() const;
	
	const char* _vertexShaderFilename;
	const char* _fragmentShaderFilename;
	unsigned _program;
	unsigned _vertexShader;
	unsigned _fragmentShader;
	std::string _log;
	bool _hasFailed;
};

inline const std::string& GLSLCompiler::status() const
{
	return _log;
}

inline unsigned GLSLCompiler::shaderId() const 
{
	return _hasFailed ? 0u : _program;
}
} // anut namespace

#endif
