// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 13/12/2014
#pragma once
#include "Window.h"
#include "Vec3.h"

// some useful structures
struct vert
{
	vec3 vertex;
};
struct vertNormal
{
	vec3 vertex;
	vec3 normal;
};
struct vertUV
{
	vec3 vertex;
	vec2 uv;
};
struct vertNormalUV
{
	vec3 vertex;
	vec3 normal;
	vec2 uv;
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