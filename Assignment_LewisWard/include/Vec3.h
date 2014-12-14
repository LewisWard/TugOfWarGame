// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 29/11/2014
#pragma once
#include "Vec2.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  vec3 struct
//----------------------------------------------------------------------------------------------------------------------
struct vec3
{
	float x; ///< x component
	float y; ///< y component
	float z; ///< z component

	vec3() : x(0.0f), y(0.0f), z(0.0f) {}; ///< sets all to zero
	vec3(float i) : x(i), y(i), z(i) {}; ///< sets x, y and z to the same value 
	vec3(float a, float b, float c) : x(a), y(b), z(c) {}; ///< sets x, y and z to differnet values
	vec3(vec2 v) : x(v.x), y(v.y), z(0.0f) {}; ///< takes a vec2 for x and y and sets z to zero
	vec3(vec2 v, float i) : x(v.x), y(v.y), z(i) {}; ///< takes a vec2 for x and y and set z
	
	// operator overloading
	inline const vec3 operator = (vec3 a)
	{	x = a.x; y = a.y; z = a.z; return *this; }
	inline const vec3 operator += (vec3 a)
	{	x += a.x; y += a.y; z += a.z; return *this; }
	inline const vec3 operator -= (vec3 a)
	{	x -= a.x; y -= a.y; z -= a.z; return *this; }
	inline const vec3 operator *= (vec3 a)
	{	x *= a.x; y *= a.y; z *= a.z; return *this; }
	inline const vec3 operator /= (vec3 a)
	{	x /= a.x; y /= a.y; z /= a.z; return *this; }
};
// add two vectors together
inline vec3 operator + (vec3 a, vec3 b)
{ 
	vec3 temp(0.0f); 
	temp.x = a.x + b.x; 
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	return temp;
}
// subtract two vectors
inline vec3 operator - (vec3 a, vec3 b)
{ 
	vec3 temp(0.0f); 
	temp.x = a.x - b.x; 
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	return temp;
}
// multiplies vector by float (scalar)
inline vec3 operator * (vec3 a, float s)
{ 
	vec3 temp(0.0f); 
	temp.x = a.x * s; 
	temp.y = a.y * s;
	temp.z = a.z * s;
	return temp;
}
// multiplies float (scalar) by vector
inline vec3 operator * (float s, vec3 a)
{ 
	vec3 temp(0.0f); 
	temp.x = a.x * s; 
	temp.y = a.y * s;
	temp.z = a.z * s;
	return temp;
}
// divides vector by float (scalar)
inline vec3 operator / (vec3 a, float s)
{ 
	vec3 temp(0.0f); 
	temp.x = a.x / s; 
	temp.y = a.y / s;
	temp.z = a.z / s;
	return temp;
}
// dot product of two vectors
inline float dot(vec3 a, vec3 b)
{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
// cross product of two vectors
inline vec3 cross(vec3 a, vec3 b)
{
	vec3 temp(0.0f);
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}
// the length of a vector
inline float length(vec3 a)
{ return std::sqrt(dot(a, a)); }
// normalize the vector to a unit length
inline vec3 normalize(vec3 a)
{
	// get the length of the vector
	float l = length(a);
	// // absolute value of the length tested to stop division by zero
	if(std::fabs(l) > 0.000001)
	{
		return vec3(a.x /= l, a.y /= l, a.z /= l);
	}
	else
	{
		return vec3(a.x * 0, a.y * 0, a.z * 0);
	}
}
