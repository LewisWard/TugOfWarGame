// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Vec3.h"

namespace math
{

//----------------------------------------------------------------------------------------------------------------------
/// \brief  matrix 2 struct
//----------------------------------------------------------------------------------------------------------------------
struct Mat2
{
	vec2 x; ///< x axis
	vec2 y; ///< y axis
	vec2 w; ///< w matrix position (transform)

	// constructor set matrix to the Identity matrix
	Mat2() : x(math::v2XOne), y(math::v2YOne), w(math::v2Zero) {};
	// constructor created from three vec2's
	Mat2(vec2 x, vec2 y, vec2 w) : x(x), y(y), w(w) {};
};

};/// End of namespace

