// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 16/12/2014
// © 2016 Lewis Ward. All rights reserved.
#pragma once
#include "Mat3.h"
#include "World.h"

World::World(const char* mesh)
{
	// create new mesh
	m_mesh = new Mesh(mesh);
}
World::~World()
{
	// free memory
	delete m_mesh;
}
void World::draw()
{
	m_mesh->draw();
}
