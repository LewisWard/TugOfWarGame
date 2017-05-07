// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 16/12/2014
// � 2016 Lewis Ward. All rights reserved.
#pragma once
#include "Mat3.h"
#include "Mesh.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  World (Level)
//----------------------------------------------------------------------------------------------------------------------
class World
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma const char* mesh file name
	//----------------------------------------------------------------------------------------------------------------------
	World(const char* mesh);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~World();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief draw the world
	//----------------------------------------------------------------------------------------------------------------------
	void draw();

private:
	Mesh* m_mesh; ///< mesh
};