// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 13/12/2014
// � 2016 Lewis Ward. All rights reserved.
#include "Texture.h"

Texture::Texture(const char* texture)
{
	// most of this code for converting a SDL_Surface to glTexture is based upon link below: 
	// http://www.sdltutorials.com/sdl-tip-sdl-surface-to-opengl-texture

	// create a surface from loading texture
	SDL_Surface* imageSurface = IMG_Load(texture);

	// if the image was loaded
	if (imageSurface)
	{
		// generate a texture
		glGenTextures(1, &m_texture);
		// bind texture
		glBindTexture(GL_TEXTURE_2D, m_texture);
		
		// select the right texture data for textures, some have Alpha channels others don't
		if (imageSurface->format->BytesPerPixel == 4)
		{
			// texture data (PNG with Alpha channel)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageSurface->pixels);
		}
		else
		{
			// texture data (JPEG without Alpha channel)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageSurface->w, imageSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageSurface->pixels);
		}

		// texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	// delete the surface, no longer required
	SDL_FreeSurface(imageSurface);
}

Texture::~Texture()
{
	// delete textures
	glDeleteTextures(1, &m_texture);
}
void Texture::bind(int slot)
{
	// bind the buffer
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
void Texture::unbind()
{
	// unbind buffer
	glBindTexture(GL_TEXTURE_2D, 0);
}
