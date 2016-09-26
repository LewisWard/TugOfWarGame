// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 13/12/2014
#pragma once
#include "Window.h"
#include "Mat3.h"

// some useful structures
///\brief vertex data (math::vec3, math::vec2)
struct vertUV
{
	math::vec3 vertex;
	math::vec2 uv;
};
///\brief vertex data (math::vec3, math::vec3, math::vec2)
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
	///\brief Constructor
	///\prama const char* texture file name
	Texture(const char* texture);
	///\brief Destructor
	~Texture();
	
	///\brief bind the texture
	void bind(int slot);

	///\brief unbind the texture
	void unbind();

	///\brief get the texture
	///\return uint32_t
	inline uint32_t texture()
	{ return m_texture; }

private:
	uint32_t m_texture; ///< texture
};
