// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 16/12/2014
#pragma once
#include "Mat3.h"
#include "Mesh.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  World (Level)
//----------------------------------------------------------------------------------------------------------------------
class World
{
public:
	///\brief Constructor
	///\prama const char* mesh file name
	World(const char* mesh);
	///\brief Destructor
	~World();

	///\brief draw the world
	void draw();

private:
	Mesh* m_mesh; ///< mesh
};