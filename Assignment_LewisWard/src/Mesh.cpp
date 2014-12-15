// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Mesh.h"

Mesh::Mesh(const char* meshFile)
{
	// gen buffers
	glGenBuffers(GL_ARRAY_BUFFER, &m_vbo);
	glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_ibo);

	std::string meshName;
	size_t objectCount, vertexCount, indicesCount;

	// input file stream
	std::ifstream fileStream(meshFile);

	// if the file is open
	if(fileStream.is_open())
	{
		// read in data
		fileStream >> objectCount;
		fileStream >> meshName;
		fileStream >> vertexCount;
		fileStream >> indicesCount;

		// resize vectors
		m_vertexData.resize(vertexCount);
		m_indices.resize(indicesCount);

		// read vertex data into vector
		for(size_t i = 0; i < m_vertexData.size(); ++i)
		{
			fileStream >> m_vertexData[i].vertex.x >> m_vertexData[i].vertex.y >> m_vertexData[i].vertex.z // vertex
					   >> m_vertexData[i].normal.x >> m_vertexData[i].normal.y >> m_vertexData[i].normal.z // normal
					   >> m_vertexData[i].uv.x >> m_vertexData[i].uv.y; // UV
		}
		// read indices into vector
		for(size_t i = 0; i < m_indices.size(); ++i)
		{
			fileStream >> m_indices[i];
		}

		// number of indices mesh has 
		m_count = m_indices.size();

		// close the file, we are done with it
		fileStream.close();
	}
	else
	{
		std::cout<<"mesh failed to open\n";
	}
}
Mesh::~Mesh()
{
	// clear vectors
	m_vertexData.clear();
	m_indices.clear();
	// delete buffers
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}
void Mesh::draw()
{
	// code
}
