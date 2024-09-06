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
	unsigned getCompiledProgram() const;
	const std::string& getStatus() const;
	
private:
	bool compile();
	bool compile(unsigned shader, const char* sourceFile);
	std::string getFileContent(const char* filename);
	bool link();
	void reset();
	void logErrors();
	std::string getShaderStatus(unsigned shader) const;
	std::string getLinkerStatus() const;
	
	const char* _vertexShaderFilename;
	const char* _fragmentShaderFilename;
	unsigned _program;
	unsigned _vertexShader;
	unsigned _fragmentShader;
	std::string _log;
	bool _hasFailed;
};

inline const std::string& GLSLCompiler::getStatus() const
{
	return _log;
}

inline unsigned GLSLCompiler::getCompiledProgram() const 
{
	return _hasFailed ? 0u : _program;
}
} // anut namespace

#endif
