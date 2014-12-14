#include "Texture.h"

Texture::Texture(const char* texture)
{
	// create a surface from loading texture
	SDL_Surface* imageSurface = SDL_LoadBMP(texture);

	// generate a texture
	glGenTextures(1, &m_texture);
	// bind texture
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageSurface->w, imageSurface->h, 0,
							 GL_RGB, GL_UNSIGNED_BYTE, imageSurface->pixels);
	// texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// delete the surface, no longer required
	SDL_FreeSurface(imageSurface);
}
Texture::~Texture()
{
	// delete texture
	glDeleteTextures(GL_TEXTURE_2D, &m_texture);
}
