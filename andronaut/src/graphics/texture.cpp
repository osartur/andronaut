#include "graphics/texture.h"
#include "vendor/stb_image.h"
#include <cstdint>

Texture::Texture(GLenum type)
{
	glGenTextures(1, &_textureId);
	_type = type;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_textureId);
}

bool Texture::loadImage(const char* filename, GLenum format, GLint internalFormat, bool mipmap)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, colorChannels;
	uint8_t* data = stbi_load(filename, &width, &height, &colorChannels, 0);
	if (data == nullptr)
	{
		return false;
	}
	glBindTexture(_type, _textureId);
	glTexImage2D(_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
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

// static
void Texture::pixelStorageMode(GLenum storageParam, int value)
{
	glPixelStorei(storageParam, value);
}

