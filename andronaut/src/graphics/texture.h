#if not defined(ANUT_TEXTURE_H)
#define ANUT_TEXTURE_H
#include <GLES3/gl32.h>

namespace anut
{
class Texture
{
public:
	static void pixelStorageMode(GLenum storageParam, int value);
	
	Texture(GLenum type);
	~Texture();
	
	bool loadImage(const char* filename, GLint textureFormat, GLenum imageFormat, bool mipmap);
	void parameter(GLenum textureParam, int value);
	void bindToUnit(GLenum textureUnit);
	unsigned resourceId() const;
	GLenum type() const;
	
private:
	unsigned _textureId;
	GLenum _type;
};

inline unsigned Texture::resourceId() const
{
	return _textureId;
}

inline GLenum Texture::type() const
{
	return _type;
}
} // anut namespace

#endif
