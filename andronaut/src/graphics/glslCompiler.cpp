#include "graphics/glslCompiler.h"
#include "utils/fileop.h"
#include <sstream>

namespace anut
{
GLSLCompiler::GLSLCompiler()
{
	_program = _vertexShader = _fragmentShader = 0u;
	_vertexShaderFilename = _fragmentShaderFilename = nullptr;
	_hasFailed = false;
}

GLSLCompiler::~GLSLCompiler()
{
	reset();
}

bool GLSLCompiler::compile(const char* vertFilename, const char* fragFilename)
{
	reset();
	_vertexShaderFilename = vertFilename;
	_fragmentShaderFilename = fragFilename;
	_program = glCreateProgram();
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	if (!(compile(_vertexShader, vertFilename) &&
	      compile(_fragmentShader, fragFilename) &&
	      link()))
	{
		logErrors();
		_hasFailed = true;
		return false;
	}
	return true;
}

bool GLSLCompiler::compile(unsigned shader, const char* sourceFile)
{
	std::string content = readFileContent(sourceFile);
	const char* code = content.c_str();
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

bool GLSLCompiler::link()
{
	glAttachShader(_program, _vertexShader);
	glAttachShader(_program, _fragmentShader);
	glLinkProgram(_program);
	int status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

void GLSLCompiler::logErrors()
{
	std::stringstream status;
	status << "[!] " << _vertexShaderFilename << ":\n"
	       << shaderStatus(_vertexShader) << "\n\n";
	
	status << "[!] " << _fragmentShaderFilename << ":\n"
	       << shaderStatus(_fragmentShader) << "\n\n";
	
	status << "[!] linker:\n" << linkerStatus() << "\n";
	_log = status.str();
}

std::string GLSLCompiler::shaderStatus(unsigned shader) const
{
	int len;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len == 0)
	{
		return std::string("No errors or warnings detected");
	}
	std::string message;
	message.resize(len - 1);
	glGetShaderInfoLog(shader, len, nullptr, &message[0]);
	return message;
}

std::string GLSLCompiler::linkerStatus() const
{
	int len;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &len);
	if (len == 0)
	{
		return std::string("No errors or warnings detected");
	}
	std::string message;
	message.resize(len - 1);
	glGetProgramInfoLog(_program, len, nullptr, &message[0]);
	return message;
}

void GLSLCompiler::reset()
{
	if (_vertexShader != 0)
	{
		//glDetachShader(_program, _vertexShader);
		glDeleteShader(_vertexShader);
	}
	if (_fragmentShader != 0)
	{
		//glDetachShader(_program, _fragmentShader);
		glDeleteShader(_fragmentShader);
	}
	if (_program != 0 && _hasFailed)
	{
		glDeleteProgram(_program);
	}
	
	_program = _vertexShader = _fragmentShader = 0u;
	_vertexShaderFilename = _fragmentShaderFilename = nullptr;
	_hasFailed = false;
}
} // anut namespace
