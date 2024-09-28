#include "graphics/gles/glslCompiler.h"
#include <sstream>
#include <fstream>

namespace anut
{
namespace gl 
{
GlslCompiler::GlslCompiler()
{
	_program = _vertexShader = _fragmentShader = 0u;
	_vertexShaderFilename = _fragmentShaderFilename = nullptr;
	_hasFailed = false;
}

GlslCompiler::~GlslCompiler()
{
	reset();
}

bool GlslCompiler::compile(const char* vertFilename, const char* fragFilename)
{
	reset();
	_vertexShaderFilename = vertFilename;
	_fragmentShaderFilename = fragFilename;
	_program = glCreateProgram();
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	if (!compile())
	{
		logErrors();
		_hasFailed = true;
		return false;
	}
	return true;
}

bool GlslCompiler::compile()
{
	return compile(_vertexShader, _vertexShaderFilename) 
	    && compile(_fragmentShader, _fragmentShaderFilename)
	    && link();
}

bool GlslCompiler::compile(unsigned shader, const char* sourceFile)
{
	std::string content = getFileContent(sourceFile);
	const char* code = content.c_str();
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

std::string GlslCompiler::getFileContent(const char* filename)
{
	std::ifstream f{filename};
	if (!f.is_open())
	{
		return "";
	}
	std::string line, content;
	while (std::getline(f, line))
	{
		content += line + '\n';
	}
	f.close();
	return content;
}

bool GlslCompiler::link()
{
	glAttachShader(_program, _vertexShader);
	glAttachShader(_program, _fragmentShader);
	glLinkProgram(_program);
	int status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

void GlslCompiler::logErrors()
{
	std::stringstream status;
	status << "[!] " << _vertexShaderFilename << ":\n"
	       << getShaderStatus(_vertexShader) << "\n\n";
	
	status << "[!] " << _fragmentShaderFilename << ":\n"
	       << getShaderStatus(_fragmentShader) << "\n\n";
	
	status << "[!] linker:\n" << getLinkerStatus() << "\n";
	_log = status.str();
}

std::string GlslCompiler::getShaderStatus(unsigned shader) const
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

std::string GlslCompiler::getLinkerStatus() const
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

void GlslCompiler::reset()
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
} // gl namespace
} // anut namespace
