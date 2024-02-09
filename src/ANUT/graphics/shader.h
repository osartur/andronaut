#if not defined(ANUT_SHADER_H)
#define ANUT_SHADER_H
#include <GLES3/gl32.h>

class Shader
{
public:
	Shader();
	~Shader();
	
	bool Init(unsigned compiled_program);
	int operator[](const char* uniform_name) const;
	
private:
	unsigned program;
	
	friend void SetCurrentShader(const Shader& target);
};

void SetCurrentShader(const Shader& target);
void SetCurrentShader();


inline int Shader::operator[](const char* uniform_name) const
{
	return glGetUniformLocation(program, uniform_name);
}

#endif
