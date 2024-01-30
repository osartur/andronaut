#include "graphics/shader.h"
#include "utils/fileop.h"
#include <GLES3/gl32.h>
#include <string>

Shader::Shader()
{
	vshader = fshader = program = 0;
}

Shader::~Shader()
{
	Delete();
}

bool Shader::Init(const char* vert_filename, const char* frag_filename)
{
	program = glCreateProgram();
	vshader = glCreateShader(GL_VERTEX_SHADER);
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	
	if (!Compile(vert_filename, vshader))
	{
		return false;
	}
	if (!Compile(frag_filename, fshader))
	{
		return false;
	}
	glLinkProgram(program);
	return true;
}

void Shader::Delete()
{
	if (vshader != 0)
	{
		glDeleteShader(vshader);
	}
	if (fshader != 0)
	{
		glDeleteShader(fshader);
	}
	if (program != 0)
	{
		glDeleteProgram(program);
	}
}

bool Shader::Compile(const char* filename, unsigned target_shader)
{
	std::string code = ReadFileContent(filename);
	const char* tmp = code.c_str();
	glShaderSource(target_shader, 1, &tmp, nullptr);
	glCompileShader(target_shader);
	
	int status;
	glGetShaderiv(target_shader, GL_COMPILE_STATUS, &status);
	
	return status;
}

void SetCurrentShader(const Shader& target)
{
	glUseProgram(target.program);
}

void SetCurrentShader()
{
	glUseProgram(0);
}
