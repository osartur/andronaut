#if not defined(ANUT_SHADER_H)
#define ANUT_SHADER_H
#include <GLES3/gl32.h>
#include <unordered_map>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	
	bool Init(unsigned compiled_program);
	int operator[](const std::string& uniform_name);
	
private:
	unsigned program;
	std::unordered_map<std::string, int> uniform_cache;
	
	friend void SetCurrentShader(const Shader& target);
};

void SetCurrentShader(const Shader& target);
void SetCurrentShader();

#endif
