#if not defined(ANUT_SHADER_H)
#define ANUT_SHADER_H
#include <GLES3/gl32.h>
#include <unordered_map>
#include <string>

class Shader
{
public:
	Shader(unsigned shaderId);
	Shader();
	~Shader();
	
	int operator[](const std::string& uniformName);
	void use();
	
private:
	unsigned _id;
	std::unordered_map<std::string, int> _uniformCache;
};


inline void Shader::use()
{
	glUseProgram(_id);
}

#endif
