// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/01/2015
#pragma once
#include "Mesh.h"

class Building
{
public:
	///\brief Constructor
	Building();
	///\brief Constructor
	///\prama float health
	///\prama math::vec3 spawn location
	///\prama Mesh building mesh
	///\prama Texture building texture
	///\prama const char* name of the building
	Building(float& health, math::vec3& spawn, Mesh& mesh, Texture& texture, const char* name);
	///\brief Destructor
	~Building();

	///\brief update the building
	void update();

	///\brief draw the building
	void draw();

	///\brief get the buildings health
	///\return float
	inline float health()
	{ return m_health; }
	///\brief get the buildings mesh
	///\return Mesh*
	inline Mesh* model()
	{ return m_mesh; }
	///\brief get the buildings texture
	///\return Texture*
	inline Texture* texture()
	{ return m_texture; }
	///\brief get the buildings spawn position
	///\return math::vec3
	inline math::vec3 spawn()
	{ return m_spawnPoint; }

	///\brief set the buildings health
	///\prama float
	inline void setHealth(float hp)
	{ m_health = hp; }
	///\brief set the buildings mesh
	///\prama float
	inline void setModel(Mesh& mesh)
	{ m_mesh = &mesh; }
	///\brief set the buildings texture
	///\prama float
	inline void setTexture(Texture& texture)
	{ m_texture = &texture; }
	///\brief set the buildings spawn position
	///\prama float
	inline void setSpawn(math::vec3 p)
	{ m_spawnPoint = p; }


private:
	float m_health; ///< the amount of health the unit has
	Mesh* m_mesh; ///< the model
	Texture* m_texture; ///< texture for the model
	math::vec3 m_spawnPoint; ///< the spawn point for units
	bool m_triggerEvents[3]; ///< events that have/haven't been trigger
	const char* m_baseName; ///< building name
};