#if not defined(ANUT_TEXTURE_H)
#define ANUT_TEXTURE_H
#include <GLES3/gl32.h>

class Texture
{
public:
	static void pixelStorageMode(GLenum storageParam, int value);
	
	Texture(GLenum type);
	~Texture();
	
	bool loadImage(const char* filename, GLenum format, GLint internalFormat, bool mipmap);
	void parameter(GLenum textureParam, int value);
	
private:
	unsigned _textureId;
	GLenum _type;
};


#endif
