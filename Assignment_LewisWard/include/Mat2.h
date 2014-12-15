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
	Mat2() : x(1.0f, 0.0f), y(0.0f, 1.0f), w(0.0f, 0.0f) {};
	// constructor created from three vec2's
	Mat2(vec2 x, vec2 y, vec2 w) : x(x), y(y), w(w) {};

	friend vec2 rotate(Mat2& m, vec2 a);
	friend vec2 transform(Mat2& m, vec2 a);

	// translate the transform by local co-ordinates
	void moveOnLocal(vec2 local)
	{
		local = rotate(*this, local);
		w += local;
	}

	// translate the transform by world co-ordinates
	void moveOnGlobal(vec2 global)
	{
		w += global;
	}
};

// rotate vec2 by the matrix
inline vec2 rotate(Mat2& m, vec2 a)
{
	vec2 t = m.x * a.x;
	t += m.y * a.y;
	return t;
}

// transform vec2 by matrix
inline vec2 transform(Mat2& m, vec2 a)
{ return rotate(m, a) + m.w; }

// rotate vec2 by the matrix inverse
inline vec2 inverseRotate(Mat2& m, vec2 a)
{
	vec2 t;
	t.x = dot(a, m.x) / dot(m.x, m.x);
	t.y = dot(a, m.y) / dot(m.y, m.y);
	return t;
}

// transfrms vec2 by the matrix inverse
inline vec2 inverseTransform(Mat2& m, vec2 a)
{ return inverseRotate(m, a - m.w); }

};/// End of namespace

