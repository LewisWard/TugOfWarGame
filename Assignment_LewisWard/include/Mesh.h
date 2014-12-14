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

	Mesh(const char* meshFile);
	~Mesh();

	void draw();

private:
	std::vector<vertNormalUV> m_vertexData;
	std::vector<int> m_indices;
	uint32_t m_count;
	uint32_t m_vbo;
	uint32_t m_ibo;
};
