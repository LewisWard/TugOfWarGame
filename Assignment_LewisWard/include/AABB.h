// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 16/12/2014
#pragma once
#include "vec3.h"

namespace math
{

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Axis Aligned Bounding Box
//----------------------------------------------------------------------------------------------------------------------
struct AABB
{
	vec2 min;
	vec2 max;

	// constructor
	AABB() : min(-1.0f, -1.0f), max(1.0f, 1.0f) {}

	math::vec2 middle() const
	{
		// return the miidle point of the AABB
		return (max + min) * 0.5f;
	}

	bool containsPoint(vec2 p) const
	{
		// returns true if point is within AABB
		return p.x >= min.x && p.y >= min.y && p.x <= max.x && p.y <= max.y;
	}

	bool containsAABB(AABB aabb) const
	{
		// returns true if AABB is within AABB
		return aabb.min.x >= min.x && aabb.min.y >= min.y && aabb.max.x <= max.x && aabb.max.y <= max.y;
	}
};

}; /// end of namespace math
