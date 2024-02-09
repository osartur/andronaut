#include "ANUT/graphics/shader.h"

Shader::Shader()
{
	program = 0;
}

Shader::~Shader()
{
	if (program != 0)
	{
		glDeleteProgram(program);
		program = 0;
	}
}

bool Shader::Init(unsigned compiled_program)
{
	program = compiled_program;
	return true;
}

void SetCurrentShader(const Shader& target)
{
	glUseProgram(target.program);
}

void SetCurrentShader()
{
	glUseProgram(0);
}
