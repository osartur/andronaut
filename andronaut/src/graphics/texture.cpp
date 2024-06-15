#include "graphics/texture.h"
#include "vendor/stb_image.h"
#include <cstdint>

namespace anut
{
void Texture::pixelStorageMode(GLenum storageParam, int value)
{
	glPixelStorei(storageParam, value);
}

Texture::Texture(GLenum type)
{
	glGenTextures(1, &_textureId);
	_type = type;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_textureId);
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
	glBindTexture(_type, _textureId);
	glTexImage2D(_type, 0, textureFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	if (mipmap)
	{
		glGenerateMipmap(_type);
	}
	stbi_image_free(data);
	return true;
}

void Texture::parameter(GLenum textureParam, int value)
{
	glBindTexture(_type, _textureId);
	glTexParameteri(_type, textureParam, value);
}

void Texture::bindToUnit(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(_type, _textureId);
}
} // anut namespace

