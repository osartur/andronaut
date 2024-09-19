#include "graphics/gles/shader.h"

namespace anut
{
namespace gl
{
Shader::Shader(unsigned shaderProgram)
{
	_program = shaderProgram;
}

Shader::Shader()
{
	_program = 0;
}

Shader::~Shader()
{
	if (_program != 0)
	{
		glDeleteShader(_program);
		_program = 0;
	}
}

int Shader::getUniformLocation(const std::string& uniformName)
{
	auto ref = _uniformCache.find(uniformName);
	if (ref != _uniformCache.end())
	{
		return ref->second;
	}
	
	int location = glGetUniformLocation(_program, uniformName.c_str());
	if (location != -1)
	{
		_uniformCache[uniformName] = location;
	}
	
	return location;
}
} // gl namespace
} // anut namespace

