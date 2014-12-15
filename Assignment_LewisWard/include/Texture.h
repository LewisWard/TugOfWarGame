// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 13/12/2014
#pragma once
#include "Window.h"
#include "Mat3.h"

// some useful structures
struct vert
{
	math::vec3 vertex;
};
struct vertNormal
{
	math::vec3 vertex;
	math::vec3 normal;
};
struct vertUV
{
	math::vec3 vertex;
	math::vec2 uv;
};
struct vertNormalUV
{
	math::vec3 vertex;
	math::vec3 normal;
	math::vec2 uv;
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Texture class
//----------------------------------------------------------------------------------------------------------------------
class Texture
{
public:

	Texture(const char* texture);
	~Texture();

	inline void bind()
	{ glBindTexture(GL_TEXTURE_2D, m_texture); }
	inline void unbind()
	{ glBindTexture(GL_TEXTURE_2D, 0); }

private:
	uint32_t m_texture;
};

