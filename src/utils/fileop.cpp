#include "utils/fileop.h"
#include <fstream>

std::string ReadFileContent(const char* filename)
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

