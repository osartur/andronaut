#include "graphics/glslCompiler.h"
#include "utils/fileop.h"
#include <GLES3/gl32.h>
#include <sstream>

GLSLCompiler::GLSLCompiler()
{
	program = vertex_shader = fragment_shader = 0;
	vertex_name = fragment_name = nullptr;
	error = NONE;
}

GLSLCompiler::~GLSLCompiler()
{
	Reset();
}

bool GLSLCompiler::Compile(const char* vert_filename, const char* frag_filename)
{
	Reset();
	
	vertex_name = vert_filename;
	fragment_name = frag_filename;
	
	program = glCreateProgram();
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	
	if (!Compile(vertex_shader, vert_filename))
	{
		error |= VERTEX_SHADER_ERROR;
	}
	if (!Compile(fragment_shader, frag_filename))
	{
		error |= FRAGMENT_SHADER_ERROR;
	}
	
	if (error & COMPILER_ERROR)
	{
		return false;
	}
	
	if (!Link())
	{
		error = LINKER_ERROR;
		return false;
	}
	
	return true;
}

std::string GLSLCompiler::Status() const
{
	std::stringstream status;
	if (error == LINKER_ERROR)
	{
		status << "linker error:\n" << LinkerStatus() << "\n";
		return status.str();
	}
	
	if (error & VERTEX_SHADER_ERROR)
	{
		status << vertex_name << ":\n" << ShaderStatus(vertex_shader) << "\n";
	}
	if (error & FRAGMENT_SHADER_ERROR)
	{
		status << fragment_name << ":\n" << ShaderStatus(fragment_shader) << "\n";
	}
	return status.str();
}

std::string GLSLCompiler::ShaderStatus(unsigned shader) const
{
	int len;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	std::string message;
	message.resize(len - 1);
	glGetShaderInfoLog(shader, len, nullptr, &message[0]);
	return message;
}

std::string GLSLCompiler::LinkerStatus() const
{
	int len;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	std::string message;
	message.resize(len - 1);
	glGetProgramInfoLog(program, len, nullptr, &message[0]);
	return message;
}

bool GLSLCompiler::Compile(unsigned shader, const char* source_file)
{
	std::string source = ReadFileContent(source_file);
	const char* code = source.c_str();
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	
	return status == GL_TRUE;
}

bool GLSLCompiler::Link()
{
	glLinkProgram(program);
	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

void GLSLCompiler::Reset()
{
	if (vertex_shader)
	{
		//glDetachShader(program, vertex_shader);
		glDeleteShader(vertex_shader);
	}
	if (fragment_shader)
	{
		//glDetachShader(program, fragment_shader);
		glDeleteShader(fragment_shader);
	}
	if (program && error != NONE)
	{
		glDeleteProgram(program);
	}
	
	program = vertex_shader = fragment_shader = 0;
	vertex_name = fragment_name = nullptr;
	error = NONE;
}

