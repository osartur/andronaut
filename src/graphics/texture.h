#if not defined(ANUT_TEXTURE_H)
#define ANUT_TEXTURE_H
#include "graphics/gpuResource.h"
#include <GLES3/gl32.h>

namespace anut
{
class Texture : public anut::GPUResource
{
public:
	static void setPixelStorageMode(GLenum storageParam, int value);
	
	Texture(GLenum type);
	~Texture();
	
	bool init() override;
	void shutdown() override;
	bool loadImage(const char* filename, GLint textureFormat, GLenum imageFormat, bool mipmap);
	void setParameter(GLenum textureParam, int value);
	void bindToUnit(GLenum textureUnit);
	GLenum getTextureType() const;
	
private:
	GLenum _type;
};

inline GLenum Texture::getTextureType() const
{
	return _type;
}
} // anut namespace

#endif
