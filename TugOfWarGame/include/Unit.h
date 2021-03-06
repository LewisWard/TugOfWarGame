// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 11/01/2015
// � 2016 Lewis Ward. All rights reserved.
#pragma once
#include "Sprite.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  A unit that the player or enemy builds
//----------------------------------------------------------------------------------------------------------------------
class Unit
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	//----------------------------------------------------------------------------------------------------------------------
	Unit();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma float unit health
	/// \parma float attack damage
	/// \parma float movement speed 
	/// \parma float gold dropped when killed
	/// \parma float gold cost to build
	/// \parma Sprite sprite
	//----------------------------------------------------------------------------------------------------------------------
	Unit(float health, float attack, float movement, float& gold, float& cost, Sprite& sprite);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Unit();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief draw the unit
	//----------------------------------------------------------------------------------------------------------------------
	void draw();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief update the unit
	/// \parma float Delta Time
	//----------------------------------------------------------------------------------------------------------------------
	void update(float dt);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief update the unit
	/// \parma float Delta Time
	/// \parma math::Mat3 martix
	//----------------------------------------------------------------------------------------------------------------------
	void update(float dt, math::Mat3 mat);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief check to see if the unit can move forwards
	/// \parma Unit the unit in front of this one (ally or enemy)
	/// \return bool if the unit can move
	//----------------------------------------------------------------------------------------------------------------------
	bool canMove(Unit& ahead);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the unit health
	/// \parma float health
	//----------------------------------------------------------------------------------------------------------------------
	inline void health(float h) { m_health = h; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the unit attack damage
	/// \parma float damage
	//----------------------------------------------------------------------------------------------------------------------
	inline void damage(float d) { m_attackDamage = d; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set if the unit is on point
	/// \parma bool
	//----------------------------------------------------------------------------------------------------------------------
	inline void point(bool p) { m_takingPoint = p; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit health
	/// \return float health
	//----------------------------------------------------------------------------------------------------------------------
	inline float getHealth() { return m_health; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit attack damage
	/// \return float damage
	//----------------------------------------------------------------------------------------------------------------------
	inline float getDamage() { return m_attackDamage; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit sprite
	/// \return Sprite* sprite
	//----------------------------------------------------------------------------------------------------------------------
	inline Sprite* getSprite() { return m_sprite; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit position
	/// \return math::vec3 position
	//----------------------------------------------------------------------------------------------------------------------
	inline math::vec3 getPosition() { return m_position; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get if the unit is on point
	/// \return bool
	//----------------------------------------------------------------------------------------------------------------------
	inline bool getPoint() { return m_takingPoint; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit movement speed
	/// \return float speed
	//----------------------------------------------------------------------------------------------------------------------
	inline float getMove() { return m_movementSpeed; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit gold cost
	/// \return float cost
	//----------------------------------------------------------------------------------------------------------------------
	inline float getGoldCost() { return m_cost; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the unit gold drop
	/// \return float drop
	//----------------------------------------------------------------------------------------------------------------------
	inline float getGoldDrop() { return m_drop; }

private:
	float m_health; ///< the amount of health the unit has
	float m_attackDamage; ///< the amount of attack damage the unit does
	Sprite* m_sprite; ///< sprite sheet of the unit
	math::vec3 m_position; ///< the position of the unit
	bool m_takingPoint; ///< is the unit taken point, if so can attack the enemy
	float m_movementSpeed; ///< the movement spped of the unit
	float m_drop; ///< gold dropped when killed
	float m_cost; ///< cost to build the unit
};

// takes two attacking units and manage their health/damage etc
void unitsInCombat(Unit& man, Unit& other, float& dt);
