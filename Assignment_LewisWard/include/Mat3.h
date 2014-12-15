// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Mat2.h"

namespace math
{

//----------------------------------------------------------------------------------------------------------------------
/// \brief  matrix 3 struct
//----------------------------------------------------------------------------------------------------------------------
struct Mat3
{
	vec3 x; ///< x 
	vec3 y; ///< y
	vec3 z; ///< z
	vec3 w; ///< w

	// constructor set matrix to the Identity matrix
	Mat3() : x(1.0f, 0.0f, 0.0f), y(0.0f, 1.0f, 0.0f), z(0.0f, 0.0f, 1.0f), w(0.0f, 0.0f, 0.0f) {};
	// constructor created from three vec2's
	Mat3(vec3 x, vec3 y, vec3 z, vec3 w) : x(x), y(y), z(z), w(w) {};
	// constructor created from Mat2
	Mat3(Mat2 m) : x(m.x), y(m.y), z(0.0f, 0.0f, 1.0f), w(m.w) {};

	friend vec3 rotate(Mat3& m, vec3 a);
	friend vec3 transform(Mat3& m, vec3 a);

	// rotate the matrix on X
	void rotateX(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(1.0f, 0.0f, 0.0f);
		y = vec3(0.0f, ca, sa);
		z = vec3(0.0f, -sa, ca);
		w = vec3();
	}
	// rotate the matrix on Y
	void rotateY(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(ca, 0.0f, -sa);
		y = vec3(0.0f, 1.0f, 0.0f);
		z = vec3(sa, 0.0f, ca);
		w = vec3();
	}
	// rotate the matrix on Z
	void rotateZ(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(ca, sa, 0.0f);
		y = vec3(-sa, ca, 0.0f);
		z = vec3(0.0f, 0.0f, 1.0f);
		w = vec3();
	}

	// translate the transform by local co-ordinates
	void moveOnLocal(vec3 local)
	{
		local = rotate(*this, local);
		w += local;
	}

	// translate the transform by world co-ordinates
	void moveOnGlobal(vec3 global)
	{
		w += global;
	}
};

// rotate vec2 by the matrix
inline vec3 rotate(Mat3& m, vec3 a)
{
	vec3 t = m.x * a.x;
	t += m.y * a.y;
	t += m.z * a.z;
	return t;
}

// transform vec2 by matrix
inline vec3 transform(Mat3& m, vec3 a)
{ return rotate(m, a) + m.w; }

// rotate vec2 by the matrix inverse
inline vec3 inverseRotate(const Mat3& m, vec3 a)
{
	vec3 t;
	t.x = dot(a, m.x) / dot(m.x, m.x);
	t.y = dot(a, m.y) / dot(m.y, m.y);
	t.z = dot(a, m.z) / dot(m.z, m.z);
	return t;
}

// transfrms vec2 by the matrix inverse
inline vec3 inverseTransform(Mat3& m, vec3 a)
{ return inverseRotate(m, a - m.w); }

// invert the matrix
inline Mat3 inverse(const Mat3& m)
{
	const float xSq = 1.0f / dot(m.x, m.x);
	const float ySq = 1.0f / dot(m.y, m.y);
	const float zSq = 1.0f / dot(m.z, m.z);
	Mat3 invert;
	invert.x.x = m.x.x * xSq;
	invert.x.y = m.y.x * ySq;
	invert.x.z = m.z.x * zSq;
	invert.y.x = m.x.y * xSq;
	invert.y.y = m.y.y * ySq;
	invert.y.z = m.z.y * zSq;
	invert.z.x = m.x.z * xSq;
	invert.z.y = m.y.z * ySq;
	invert.z.z = m.z.z * zSq;
	invert.w = -rotate(invert, m.w);
	return invert;
}

}; /// end of namespace
