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
	Mat3() : x(math::vXOne), y(math::vYOne), z(math::vZOne), w(math::vZero) {};

	// constructor created from three vec2's
	Mat3(vec3 x, vec3 y, vec3 z, vec3 w) : x(x), y(y), z(z), w(w) {};
	// constructor created from Mat2

	Mat3(Mat2 m) : x(m.x), y(m.y), z(math::vZOne), w(m.w) {};

	friend vec3 rotate(Mat3& m, vec3 a);
	friend vec3 transform(Mat3& m, vec3 a);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief rotate the matrix on X
	/// \parma float angle
	//----------------------------------------------------------------------------------------------------------------------
	void rotateX(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(math::vXOne);
		y = vec3(0.0f, ca, sa);
		z = vec3(0.0f, -sa, ca);
		w = vec3();
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief rotate the matrix on Y
	/// \parma float angle
	//----------------------------------------------------------------------------------------------------------------------
	void rotateY(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(ca, 0.0f, -sa);
		y = vec3(math::vYOne);
		z = vec3(sa, 0.0f, ca);
		w = vec3();
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief rotate the matrix on Z
	/// \parma float angle
	//----------------------------------------------------------------------------------------------------------------------
	void rotateZ(float angle)
	{
		float ca = std::cosf(angle);
		float sa = std::sinf(angle);
		x = vec3(ca, sa, 0.0f);
		y = vec3(-sa, ca, 0.0f);
		z = vec3(math::vZOne);
		w = vec3();
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief based upon http://stackoverflow.com/questions/11557540/frustum-and-perspective-matrices
	/// \parma float left co-ordinate of frustum
	/// \parma float right co-ordinate of frustum
	/// \parma float bottom co-ordinate of frustum
	/// \parma float top co-ordinate of frustum
	/// \parma float near viewing plane
	/// \parma float far viewing plane
	//----------------------------------------------------------------------------------------------------------------------
	void rightHandFrustum(float l, float r, float b, float t, float planeNear, float planeFar)
	{
		// declear some vectors
		math::vec3 X = math::vXOne, Y = math::vYOne, Z = math::vZOne;

		x = X * (2.0f * planeNear / (r - l)); // X column right (r) - left (l) = direction
		y = Y * (2.0f * planeNear / (t - b)); // Y column top (t) - bottom (b) = height
		z = math::vec3((r + l) / (r - l), (t + b) / (t - b), (planeFar + planeNear) / (planeNear - planeFar)); // Z column

		// set the w component of Z
		z.w = -1.0f;

		// W column
		w = Z * (2.0f * planeFar * planeNear / (planeNear - planeFar));
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \parma float field of view angle (radians)
	/// \parma float aspect ratio of window
	/// \parma float near viewing plane
	/// \parma float far viewing plane
	//----------------------------------------------------------------------------------------------------------------------
	void rightHandPerspective(float angle, float aRatio, float nearPlane, float farPlane)
	{
		// compute near plane rectangual boundary (i.e width and height)
		const float scale = std::tanf(angle / 2.0f) * nearPlane;
		const float right = aRatio * scale;
		const float left = -right; ///< negate right
		const float top = scale;
		const float bottom = -top; ///< negate top

		// compute the frustum
		rightHandFrustum(left, right, bottom, top, nearPlane, farPlane);
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief multiply two 4x4 matrix together, this will transform the child martix to world co-ordinates.
	/// \parma Mat3 parent matrix
	/// \parma Mat3 child martix
	//----------------------------------------------------------------------------------------------------------------------
	void multiplyMatrix(const Mat3& p, const Mat3& c)
	{
		x.x = p.x.x * c.x.x;
		x.y = p.x.y * c.x.x;
		x.z = p.x.z * c.x.x;
		x.w = p.x.w * c.x.x;
		x.x += p.y.x * c.x.y;
		x.y += p.y.y * c.x.y;
		x.z += p.y.z * c.x.y;
		x.w += p.y.w * c.x.y;
		x.x += p.z.x * c.x.z;
		x.y += p.z.y * c.x.z;
		x.z += p.z.z * c.x.z;
		x.w += p.z.w * c.x.z;
		x.x += p.w.x * c.x.w;
		x.y += p.w.y * c.x.w;
		x.z += p.w.z * c.x.w;
		x.w += p.w.w * c.x.w;
		y.x = p.x.x * c.y.x;
		y.y = p.x.y * c.y.x;
		y.z = p.x.z * c.y.x;
		y.w = p.x.w * c.y.x;
		y.x += p.y.x * c.y.y;
		y.y += p.y.y * c.y.y;
		y.z += p.y.z * c.y.y;
		y.w += p.y.w * c.y.y;
		y.x += p.z.x * c.y.z;
		y.y += p.z.y * c.y.z;
		y.z += p.z.z * c.y.z;
		y.w += p.z.w * c.y.z;
		y.x += p.w.x * c.y.w;
		y.y += p.w.y * c.y.w;
		y.z += p.w.z * c.y.w;
		y.w += p.w.w * c.y.w;
		z.x = p.x.x * c.z.x;
		z.y = p.x.y * c.z.x;
		z.z = p.x.z * c.z.x;
		z.w = p.x.w * c.z.x;
		z.x += p.y.x * c.z.y;
		z.y += p.y.y * c.z.y;
		z.z += p.y.z * c.z.y;
		z.w += p.y.w * c.z.y;
		z.x += p.z.x * c.z.z;
		z.y += p.z.y * c.z.z;
		z.z += p.z.z * c.z.z;
		z.w += p.z.w * c.z.z;
		z.x += p.w.x * c.z.w;
		z.y += p.w.y * c.z.w;
		z.z += p.w.z * c.z.w;
		z.w += p.w.w * c.z.w;
		w.x = p.x.x * c.w.x;
		w.y = p.x.y * c.w.x;
		w.z = p.x.z * c.w.x;
		w.w = p.x.w * c.w.x;
		w.x += p.y.x * c.w.y;
		w.y += p.y.y * c.w.y;
		w.z += p.y.z * c.w.y;
		w.w += p.y.w * c.w.y;
		w.x += p.z.x * c.w.z;
		w.y += p.z.y * c.w.z;
		w.z += p.z.z * c.w.z;
		w.w += p.z.w * c.w.z;
		w.x += p.w.x * c.w.w;
		w.y += p.w.y * c.w.w;
		w.z += p.w.z * c.w.w;
		w.w += p.w.w * c.w.w;
	}

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set matrix as an array
	/// \parma float 
	//----------------------------------------------------------------------------------------------------------------------
	void matrixAsArray(float mvpArray[])
	{
		mvpArray[0] = x.x;
		mvpArray[1] = x.y;
		mvpArray[2] = x.z;
		mvpArray[3] = x.w;
		mvpArray[4] = y.x;
		mvpArray[5] = y.y;
		mvpArray[6] = y.z;
		mvpArray[7] = y.w;
		mvpArray[8] = z.x;
		mvpArray[9] = z.y;
		mvpArray[10] = z.z;
		mvpArray[11] = z.w;
		mvpArray[12] = w.x;
		mvpArray[13] = w.y;
		mvpArray[14] = w.z;
		mvpArray[15] = w.w;
	}
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief rotate vec3 by Mat3 
/// \parma Mat3
/// \parma vec3
//----------------------------------------------------------------------------------------------------------------------
inline vec3 rotateMat3(Mat3& m, vec3 v)
{
	vec3 temp = m.x * v.x;
	temp += m.y * v.y;
	temp += m.z * v.z;
	return temp;
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief transform vec3 (point) by Mat3 
/// \parma Mat3
/// \parma vec3
//----------------------------------------------------------------------------------------------------------------------
inline vec3 transformMat3(Mat3& m, vec3 v) { return rotateMat3(m, v) + m.w; }

//----------------------------------------------------------------------------------------------------------------------
/// \brief multiplies child and parent Mat3, the child martix is turned into world co-ordinates
/// \parma Mat3
/// \parma Mat3
//----------------------------------------------------------------------------------------------------------------------
inline Mat3 operator * (Mat3& c, Mat3& p)
{
	Mat3 temp;
	temp.x = rotateMat3(p, c.x);
	temp.y = rotateMat3(p, c.y);
	temp.z = rotateMat3(p, c.z);
	temp.w = transformMat3(p, c.w);
	return temp;
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief rotate vec2 by the matrix
/// \parma Mat3
/// \parma vec3
//----------------------------------------------------------------------------------------------------------------------
inline vec3 rotate(Mat3& m, vec3 a)
{
	vec3 t = m.x * a.x;
	t += m.y * a.y;
	t += m.z * a.z;
	return t;
}


//----------------------------------------------------------------------------------------------------------------------
/// \brief invert the matrix
/// \parma Mat3
//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
/// \brief sets the w.w component to 1
/// \parma Mat3
//----------------------------------------------------------------------------------------------------------------------
inline void addW(Mat3& matrix) { matrix.w.w = 1; }

//----------------------------------------------------------------------------------------------------------------------
/// \brief sets the w.w component to 0
/// \parma Mat3
//----------------------------------------------------------------------------------------------------------------------
inline void removeW(Mat3& matrix) { matrix.w.w = 0; }

}; /// end of namespace
