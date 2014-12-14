// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Window.h"

namespace gls
{
enum shaderType
{
	sVERTEX, sFRAGMENT,
};

/// \brief get a gl error within shader
/// \prama const char* shader file
void glError(const char* file);

//----------------------------------------------------------------------------------------------------------------------
/// \brief  GLSL Shader
//----------------------------------------------------------------------------------------------------------------------
class Shader
{
public:
	/// \brief Constr, create and compile shader
	/// \prama const char* shader source code
	Shader(const char* shaderFile, shaderType type);
	/// \brief Destr
	~Shader();

	/// \brief get the shader source code
	/// \return const char* shader source code
	const char* shaderSource() const;

	/// \brief get the shader object
	/// \return uint32_t shader object
	inline uint32_t shader() const
	{ return m_shader; }

private:
	shaderType m_type;
	uint32_t m_shader;
	std::string m_filename;
	std::string m_source;

	/// \brief load a shader from file, should be called before creating a shader
	/// \prama const char* shader file
	char* loadShaderFile(const char* shaderFilename);
};
////////////////////////////
}; // end of gls namespace
////////////////////////////
