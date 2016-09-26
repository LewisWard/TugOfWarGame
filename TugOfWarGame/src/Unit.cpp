// author : Lewis Ward
// program: Tug Of War Game
// date   : 11/01/2015
// © 2016 Lewis Ward. All rights reserved.
#include "Unit.h"

Unit::Unit()
{
	m_health = 1.0f;
	m_attackDamage = 1.0f;
	m_sprite = NULL;
	m_position;
	m_takingPoint = false;
	m_movementSpeed = 1.0f;
	m_drop = 10.0f;
	m_cost = 7.0f;
}
Unit::Unit(float health, float attack, float movement, float& drop, float& cost, Sprite& sprite)
{
	m_health = health;
	m_attackDamage = attack;
	m_sprite = &sprite;
	m_position;
	m_takingPoint = false;
	m_movementSpeed = movement;
	m_drop = drop;
	m_cost = cost;
}
Unit::~Unit()
{
	// as the pointer doesn't create a 'new' sprite just set it to null. Sprite will be deleted somewhere else.
	m_sprite = NULL;
}
void Unit::draw()
{
	m_sprite->bindSprite();
	if (m_sprite)
		m_sprite->draw();
	m_sprite->unbindSprite();
}
void Unit::update(float dt)
{
	if (m_sprite)
	{
		m_sprite->update(dt);
		// get the sprite position
		m_position = m_sprite->matrix().w;
	}
}
void Unit::update(float dt, math::Mat3 mat)
{
	if (m_sprite)
	{
		m_sprite->update(dt, mat);
		// get the sprite position
		m_position = m_sprite->matrix().w;
	}
}
bool Unit::canMove(Unit& ahead)
{
	// get both units positions
	math::vec3 targetPosition = m_position;
	math::vec3 aheadPosition = ahead.getPosition();

	// compute the range
	float range = targetPosition.x - aheadPosition.x;

	// if in range of the unit ahead time to do something
	if (range >= -2.0f)
	{
		return false;
	}
	return true;
}

// takes two attacking units and manage their health/damage etc
void unitsInCombat(Unit& man, Unit& other, float& dt)
{
	// get both units attack damage
	float manDamage = man.getDamage();
	float otherDamage = other.getDamage();
	// get both units health
	float manHP = man.getHealth();
	float otherHP = other.getHealth();

	// make sure both are alive
	if (manHP > 0.0f && otherHP > 0.0f)
	{
		// apply damage
		manHP -= otherDamage * dt;
		otherHP -= manDamage * dt;
		// is man alive or not
		if (manHP > 0.0f)
		{
			man.health(manHP);
		}
		else
		{
			man.health(manHP);
			man.getSprite()->state(3);
		}

		// is other alive or not
		if (otherHP > 0.0f)
		{
			other.health(otherHP);
		}
		else
		{
			other.health(otherHP);
			other.getSprite()->state(3);
		}
	}
}
