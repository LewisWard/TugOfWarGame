// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Shader.h"

// GL Shaders namespace
namespace gls
{
//----------------------------------------------------------------------------------------------------------------------
/// \brief  Program for shader
//----------------------------------------------------------------------------------------------------------------------
class Program
{
public:
	/// \brief Constr
	Program() : m_program(0){};
	/// \brief Destr
	~Program();

	bool create(const Shader* const vertex, const Shader* const fragment);

	void bind() const;

	void unbind() const;

	inline uint32_t program()
	{ return m_program; }

private:
	uint32_t m_program;
};
////////////////////////////
}; // end of gls namespace
////////////////////////////
