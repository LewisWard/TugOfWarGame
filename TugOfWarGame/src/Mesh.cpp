// author : Lewis Ward
// program: Tug Of War Game
// date   : 14/12/2014
#pragma once
#include "Mesh.h"

Mesh::Mesh(const char* meshFile)
{
	// gen buffers
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

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

		float requiredPadding = 0;

		// read vertex data into vector
		for(size_t i = 0; i < m_vertexData.size(); ++i)
		{
			fileStream >> m_vertexData[i].vertex.x >> m_vertexData[i].vertex.y >> m_vertexData[i].vertex.z // vertex
								 >> m_vertexData[i].normal.x >> m_vertexData[i].normal.y >> m_vertexData[i].normal.z // normal
								 >> requiredPadding >> requiredPadding >> requiredPadding // bi-normal
								 >> requiredPadding >> requiredPadding >> requiredPadding // tangent
								 >> m_vertexData[i].uv.x >> m_vertexData[i].uv.y; // UV
		}
		// read indices into vector
		for(size_t i = 0; i < m_indices.size(); ++i)
		{
			fileStream >> m_indices[i];
		}
		
		// close the file, we are done with it
		fileStream.close();

		// genereate a buffer
		glGenBuffers(1, &m_vbo);
		// bind
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertNormalUV)*m_vertexData.size(), &m_vertexData[0], GL_STATIC_DRAW);
		// unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// genereate a buffer
		glGenBuffers(1, &m_ibo);
		// bind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
		// unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	// enable vertex data and indices data arrays
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	//Const foat pointer that points to a offset of NULL
	const float* coordinate = 0;
	// enable vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertNormalUV), coordinate);
	glEnableVertexAttribArray(0);

	// enable normal
	glVertexAttribPointer(1, 3, GL_FLOAT, true, sizeof(vertNormalUV), coordinate + 4);
	glEnableVertexAttribArray(1);

	// enable texture
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertNormalUV), coordinate + 8);
	glEnableVertexAttribArray(2);

	// draw the indexed triangles from the VBO
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

	// disable editing of array
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// empty buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
