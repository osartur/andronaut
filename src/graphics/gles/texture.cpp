#include "graphics/gles/texture.h"
#include "vendor/stb_image.h"
#include <cstdint>

namespace anut
{
namespace gl
{
void Texture::setPixelStorageMode(GLenum storageParam, int value)
{
	glPixelStorei(storageParam, value);
}

Texture::Texture(GLenum type)
{
	_type = type;
}

Texture::~Texture()
{
	
}

bool Texture::init()
{
	glGenTextures(1, &__handle);
	return true;
}

void Texture::shutdown()
{
	if (initialized())
	{
		glDeleteTextures(1, &__handle);
		__handle = 0;
	}
}

bool Texture::loadImage(const char* filename, GLint textureFormat, GLenum imageFormat, bool mipmap)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, colorChannels;
	uint8_t* data = stbi_load(filename, &width, &height, &colorChannels, 0);
	if (data == nullptr)
	{
		return false;
	}
	glBindTexture(_type, __handle);
	glTexImage2D(_type, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	if (mipmap)
	{
		glGenerateMipmap(_type);
	}
	stbi_image_free(data);
	return true;
}

void Texture::setParameter(GLenum textureParam, int value)
{
	glBindTexture(_type, __handle);
	glTexParameteri(_type, textureParam, value);
}

void Texture::bindToUnit(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(_type, __handle);
}
} // gl namespace
} // anut namespace

