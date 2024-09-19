#if not defined(ANUT_SHADER_H)
#define ANUT_SHADER_H
#include <GLES3/gl32.h>
#include <unordered_map>
#include <string>

namespace anut
{
namespace gl
{
class Shader
{
public:
	Shader(unsigned shaderProgram);
	Shader();
	~Shader();
	
	int getUniformLocation(const std::string& uniformName);
	void use();
	
private:
	unsigned _program;
	std::unordered_map<std::string, int> _uniformCache;
};


inline void Shader::use()
{
	glUseProgram(_program);
}
} // gl namespace
} // anut namespace

#endif
