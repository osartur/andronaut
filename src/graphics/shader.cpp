#include "graphics/shader.h"

Shader::Shader(unsigned shaderId)
{
	_id = shaderId;
}

Shader::Shader()
{
	_id = 0;
}

Shader::~Shader()
{
	if (_id != 0)
	{
		glDeleteShader(_id);
		_id = 0;
	}
}

int Shader::operator[](const std::string& uniformName)
{
	auto ref = _uniformCache.find(uniformName);
	if (ref != _uniformCache.end())
	{
		return ref->second;
	}
	
	int location = glGetUniformLocation(_id, uniformName.c_str());
	if (location != -1)
	{
		_uniformCache[uniformName] = location;
	}
	
	return location;
}

