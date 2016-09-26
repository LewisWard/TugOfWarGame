// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 16/12/2014
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
