// author : Lewis Ward
// program: Tug Of War Game
// date   : 17/01/2015
// © 2016 Lewis Ward. All rights reserved.
#include "Building.h"

Building::Building()
{
	m_health = 1.0f;
	m_mesh = NULL;
	m_texture = NULL;

	math::vec3 temp(0.0f, 0.0f, -4.0f);
	m_spawnPoint = temp;

	m_triggerEvents[0] = false;
	m_triggerEvents[1] = false;
	m_triggerEvents[2] = false;
}
Building::Building(float& health, math::vec3& spawn, Mesh& mesh, Texture& texture, const char* name)
{
	m_health = health;
	m_mesh = &mesh;
	m_texture = &texture;
	m_spawnPoint = spawn;
	m_baseName = name;

	m_triggerEvents[0] = false;
	m_triggerEvents[1] = false;
	m_triggerEvents[2] = false;
}
Building::~Building()
{
	// these will be deleted somewhere else in the program, so just set pointers to null
	m_mesh = NULL;
	m_texture = NULL;
}
void Building::update()
{
	if (!m_triggerEvents[0] && m_health < 37.5f)
	{
		std::cout << m_baseName << " is less then 75 % health!\n";
		m_triggerEvents[0] = true;
	}
	else if (!m_triggerEvents[1] && m_health < 25.0f)
	{
		std::cout << m_baseName << " is less then 50 % health!\n";
		m_triggerEvents[1] = true;
	}
	else if (!m_triggerEvents[2] && m_health < 12.5f)
	{
		std::cout << m_baseName << " is less then 25% health!\n";
		m_triggerEvents[2] = true;
	}
}
void Building::draw()
{
	// bind the texture, draw the mesh then unbind the texture
	m_texture->bind(0);
	m_mesh->draw();
	m_texture->unbind();
}
