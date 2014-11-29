// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 29/11/2014
#pragma once
#include <cmath>
#include <cstdint>
#include <stdint.h>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  vec2 struct
//----------------------------------------------------------------------------------------------------------------------
struct vec2
{
	float x; ///< x component
	float y; ///< y component

	// no default constructor to set variables to zero, as you should be using one of the two below.
	vec2(float i) : x(i), y(i) {}; ///< sets both x and y to the same value 
	vec2(float a, float b) : x(a), y(b) {}; ///< sets x and y to differnet values

	// operator overloading
	// EQUALS
	inline const vec2 operator = (vec2 a)
	{	x = a.x; y = a.y; return *this; }
	// ADD EQUALS
	inline const vec2 operator += (vec2 a)
	{	x += a.x; y += a.y; return *this; }
	// SUB EQUALS
	inline const vec2 operator -= (vec2 a)
	{	x -= a.x; y -= a.y; return *this; }
	// TIMES EQUALS
	inline const vec2 operator *= (vec2 a)
	{	x *= a.x; y *= a.y; return *this; }
	// DIVIDE EQUALS
	inline const vec2 operator /= (vec2 a)
	{	x /= a.x; y /= a.y; return *this; }
};
// add two vectors together
inline vec2 operator + (vec2 a, vec2 b)
{ 
	vec2 temp(0.0f); 
	temp.x = a.x + b.x; 
	temp.y = a.y + b.y;
	return temp;
}
// subtract two vectors
inline vec2 operator - (vec2 a, vec2 b)
{ 
	vec2 temp(0.0f); 
	temp.x = a.x - b.x; 
	temp.y = a.y - b.y;
	return temp;
}
// multiplies vector by float (scalar)
inline vec2 operator * (vec2 a, float s)
{ 
	vec2 temp(0.0f); 
	temp.x = a.x * s; 
	temp.y = a.y * s;
	return temp;
}
// multiplies float (scalar) by vector
inline vec2 operator * (float s, vec2 a)
{ 
	vec2 temp(0.0f); 
	temp.x = a.x * s; 
	temp.y = a.y * s;
	return temp;
}
// divides vector by float (scalar)
inline vec2 operator / (vec2 a, float s)
{ 
	vec2 temp(0.0f); 
	temp.x = a.x / s; 
	temp.y = a.y / s;
	return temp;
}
// dot product of two vectors, if you enter the same vector for both parameters you will get the squared length
inline float dot(vec2 a, vec2 b)
{ return (a.x * b.x) + (a.y * b.y); }
// the length of a vector
inline float length(vec2 a)
{ return std::sqrt(dot(a, a)); }
// normalize the vector to a unit length
inline vec2 normalize(vec2 a)
{
	// get the length of the vector
	float l = length(a);
	// absolute value of the length tested to stop division by zero
	if(std::fabs(l) > 0.000001)
	{
		return vec2(a.x /= l, a.y /= l);
	}
	else
	{
		return vec2(a.x * 0, a.y * 0);
	}
}
