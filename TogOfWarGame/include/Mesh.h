// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Texture.h"
#include <vector>
#include <fstream>
#include <string>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Loads and handles .meshes files
//----------------------------------------------------------------------------------------------------------------------
class Mesh
{
public:
	///\brief Constructor
	///\prama const char* mesh file name
	Mesh(const char* meshFile);
	///\brief Destructor
	~Mesh();

	///\brief draw the mesh
	void draw();

	///\brief set the mesh matrix
	///\prama math::Mat3
	inline void setMartix(math::Mat3 model)
	{ m_matrix = model; }

	///\brief get the mesh matrix
	///\return math::Mat3
	inline math::Mat3 martix()
	{ return m_matrix; }

private:
	std::vector<vertNormalUV> m_vertexData; ///< vertex data (vertex, normal, uv)
	std::vector<int> m_indices; ///< indices
	uint32_t m_vbo; ///< VBO
	uint32_t m_ibo; ///< IBO
	math::Mat3 m_matrix; ///< mesh matrix
};
