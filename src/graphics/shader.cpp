#include "graphics/shader.h"

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

int Shader::operator[](const std::string& uniform_name)
{
	auto ref = uniform_cache.find(uniform_name);
	if (ref != uniform_cache.end())
	{
		return ref->second;
	}
	int location = glGetUniformLocation(program, uniform_name.c_str());
	if (location != -1)
	{
		uniform_cache[uniform_name] = location;
	}
	return location;
}

void SetCurrentShader(const Shader& target)
{
	glUseProgram(target.program);
}

void SetCurrentShader()
{
	glUseProgram(0);
}
