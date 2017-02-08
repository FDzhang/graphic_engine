#ifndef __XRVECTOR_H__
#define __XRVECTOR_H__
#include "../External/xrUtility.h"
#include "assert.h"
#include "XRMatrix.h"
#include "XRQuaternion.h"
#include <string.h>
#include <math.h>

/*!***************************************************************************
** Forward Declarations for vector and matrix structs
****************************************************************************/
struct XRVec4;
struct XRVec3;
struct XRMat3;
struct XRMat4;

/*!***************************************************************************
 @Function			XRLinearEqSolve
 @Input				pSrc	2D array of floats. 4 Eq linear problem is 5x4
							matrix, constants in first column
 @Input				nCnt	Number of equations to solve
 @Output			pRes	Result
 @Description		Solves 'nCnt' simultaneous equations of 'nCnt' variables.
					pRes should be an array large enough to contain the
					results: the values of the 'nCnt' variables.
					This fn recursively uses Gaussian Elimination.
*****************************************************************************/
void XRLinearEqSolve(Float32 * const pRes, Float32 ** const pSrc, const int nCnt);

/*!***************************************************************************
	** XRVec2 2 component vector
	****************************************************************************/
struct XRVec2
{
	Float32 x, y;
	/*!***************************************************************************
		** Constructors
		****************************************************************************/
	/*!***************************************************************************
		@Function			XRVec2
		@Description		Blank constructor.
		*****************************************************************************/
	XRVec2() {}
	/*!***************************************************************************
		@Function			XRVec2
		@Input				fX	X component of vector
		@Input				fY	Y component of vector
		@Description		Simple constructor from 2 values.
		*****************************************************************************/
	XRVec2(Float32 fX, Float32 fY) : x(fX), y(fY) {}
	/*!***************************************************************************
		@Function			XRVec2
		@Input				fValue	a component value
		@Description		Constructor from a single value.
		*****************************************************************************/
	XRVec2(Float32 fValue) : x(fValue), y(fValue) {}
	/*!***************************************************************************
		@Function			XRVec2
		@Input				pVec	an array
		@Description		Constructor from an array
		*****************************************************************************/
	XRVec2(const Float32* pVec) : x(pVec[0]), y(pVec[1]) {}
	/*!***************************************************************************
		@Function			XRVec2
		@Input				v3Vec a Vec3
		@Description		Constructor from a Vec3
		*****************************************************************************/
	XRVec2(const XRVec3& v3Vec);
	/*!***************************************************************************
		** Operators
		****************************************************************************/
	/*!***************************************************************************
		@Function			+
		@Input				rhs another Vec2
		@Returns			result of addition
		@Description		componentwise addition operator for two Vec2s
		*****************************************************************************/
	XRVec2 operator+(const XRVec2& rhs) const
	{
		XRVec2 out(*this);
		return out += rhs;
	}
	/*!***************************************************************************
		@Function			-
		@Input				rhs another Vec2
		@Returns			result of subtraction
		@Description		componentwise subtraction operator for two Vec2s
		****************************************************************************/
	XRVec2 operator-(const XRVec2& rhs) const
	{
		XRVec2 out(*this);
		return out -= rhs;
	}

	/*!***************************************************************************
		@Function			+=
		@Input				rhs another Vec2
		@Returns			result of addition
		@Description		componentwise addition and assignment operator for two Vec2s
		****************************************************************************/
	XRVec2& operator+=(const XRVec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/*!***************************************************************************
		@Function			-=
		@Input				rhs another Vec2
		@Returns			result of subtraction
		@Description		componentwise subtraction and assignment operator for two Vec2s
		****************************************************************************/
	XRVec2& operator-=(const XRVec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/*!***************************************************************************
		@Function			-
		@Input				rhs another Vec2
		@Returns			result of negation
		@Description		negation operator for a Vec2
		****************************************************************************/
	friend XRVec2 operator- (const XRVec2& rhs) { return XRVec2(-rhs.x, -rhs.y); }

	/*!***************************************************************************
		@Function			*
		@Input				lhs scalar
		@Input				rhs a Vec2
		@Returns			result of multiplication
		@Description		multiplication operator for a Vec2
		****************************************************************************/
	friend XRVec2 operator*(const Float32 lhs, const XRVec2&  rhs)
	{
		XRVec2 out(lhs);
		return out *= rhs;
	}

	/*!***************************************************************************
		@Function			/
		@Input				lhs scalar
		@Input				rhs a Vec2
		@Returns			result of division
		@Description		division operator for scalar and Vec2
		****************************************************************************/
	friend XRVec2 operator/(const Float32 lhs, const XRVec2&  rhs)
	{
		XRVec2 out(lhs);
		return out /= rhs;
	}

	/*!***************************************************************************
		@Function			*
		@Input				rhs a scalar
		@Returns			result of multiplication
		@Description		componentwise multiplication by scalar for Vec2
		****************************************************************************/
	XRVec2 operator*(const Float32& rhs) const
	{
		XRVec2 out(*this);
		return out *= rhs;
	}

	/*!***************************************************************************
		@Function			*=
		@Input				rhs a scalar
		@Returns			result of multiplication and assignment
		@Description		componentwise multiplication and assignment by scalar for Vec2
		****************************************************************************/
	XRVec2& operator*=(const Float32& rhs)
	{
		x = VERTTYPEMUL(x, rhs);
		y = VERTTYPEMUL(y, rhs);
		return *this;
	}

	/*!***************************************************************************
		@Function			*=
		@Input				rhs a Vec2
		@Returns			result of multiplication and assignment
		@Description		componentwise multiplication and assignment by Vec2 for Vec2
		****************************************************************************/
	XRVec2& operator*=(const XRVec2& rhs)
	{
		x = VERTTYPEMUL(x, rhs.x);
		y = VERTTYPEMUL(y, rhs.y);
		return *this;
	}

	/*!***************************************************************************
		@Function			/
		@Input				rhs a scalar
		@Returns			result of division
		@Description		componentwise division by scalar for Vec2
		****************************************************************************/
	XRVec2 operator/(const Float32& rhs) const
	{
		XRVec2 out(*this);
		return out /= rhs;
	}

	/*!***************************************************************************
		@Function			/=
		@Input				rhs a scalar
		@Returns			result of division and assignment
		@Description		componentwise division and assignment by scalar for Vec2
		****************************************************************************/
	XRVec2& operator/=(const Float32& rhs)
	{
		x = VERTTYPEDIV(x, rhs);
		y = VERTTYPEDIV(y, rhs);
		return *this;
	}

	/*!***************************************************************************
		@Function			/=
		@Input				rhs a Vec2
		@Returns			result of division and assignment
		@Description		componentwise division and assignment by Vec2 for Vec2
		****************************************************************************/
	XRVec2& operator/=(const XRVec2& rhs)
	{
		x = VERTTYPEDIV(x, rhs.x);
		y = VERTTYPEDIV(y, rhs.y);
		return *this;
	}

	/*!***************************************************************************
	@Function			==
	@Input				rhs a single value
	@Returns			true if the two vectors are equal
	@Description		XRVec2 equality operator
	****************************************************************************/
	bool operator==(const XRVec2& rhs) const
	{
		if(x != rhs.x) return false;
		if(y != rhs.y) return false;
		return true;
	}

	/*!***************************************************************************
	@Function			!=
	@Input				rhs a single value
	@Returns			true if the two vectors are not equal
	@Description		XRVec2 inequality operator
	****************************************************************************/
	bool operator!=(const XRVec2& rhs) const
	{
		if(x == rhs.x)
			return false;

		return true;
	}

	// FUNCTIONS
	/*!***************************************************************************
		@Function			lenSqr
		@Returns			the square of the magnitude of the vector
		@Description		calculates the square of the magnitude of the vector
		****************************************************************************/
	Float32 lenSqr() const
	{
		return VERTTYPEMUL(x,x)+VERTTYPEMUL(y,y);
	}

	/*!***************************************************************************
		@Function			length
		@Returns			the of the magnitude of the vector
		@Description		calculates the magnitude of the vector
		****************************************************************************/
	Float32 length() const
	{
		return (Float32) f2vt(sqrt(vt2f(x)*vt2f(x) + vt2f(y)*vt2f(y)));
	}

	/*!***************************************************************************
		@Function			normalize
		@Returns			the normalized value of the vector
		@Description		normalizes the vector
		****************************************************************************/
	XRVec2 normalize()
	{
		return *this /= length();
	}

	/*!***************************************************************************
		@Function			normalized
		@Returns			returns the normalized value of the vector
		@Description		returns a normalized vector of the same direction as this
		vector
		****************************************************************************/
	XRVec2 normalized() const
	{
		XRVec2 out(*this);
		return out.normalize();
	}

	/*!***************************************************************************
		@Function			rotated90
		@Returns			returns the vector rotated 90?
		@Description		returns the vector rotated 90?
		****************************************************************************/
	XRVec2 rotated90() const
	{
		return XRVec2(-y, x);
	}

	/*!***************************************************************************
		@Function			dot
		@Input				rhs a single value
		@Returns			scalar product
		@Description		calculate the scalar product of two Vec3s
		****************************************************************************/
	Float32 dot(const XRVec2& rhs)
	{
		return VERTTYPEMUL(x, rhs.x) + VERTTYPEMUL(y, rhs.y);
	}

	/*!***************************************************************************
		@Function			ptr
		@Returns			pointer
		@Description		returns a pointer to memory containing the values of the
		Vec3
		****************************************************************************/
	Float32 *ptr() { return (Float32*)this; }

	Void Set(Float32 fX, Float32 fY)
	{
		x = fX;	y = fY;
	}
	Void Set(Float32* data)
	{
		x = data[0];	y = data[1];
	}
};

/*!***************************************************************************
** XRVec3 3 component vector
****************************************************************************/
struct XRVec3 : public XRVECTOR3
{
/*!***************************************************************************
** Constructors
****************************************************************************/
/*!***************************************************************************
 @Function			XRVec3
 @Description		Blank constructor.
*****************************************************************************/
	XRVec3(){}
/*!***************************************************************************
 @Function			XRVec3
 @Input				fX	X component of vector
 @Input				fY	Y component of vector
 @Input				fZ	Z component of vector
 @Description		Simple constructor from 3 values.
*****************************************************************************/
	XRVec3(Float32 fX, Float32 fY, Float32 fZ)
	{
		x = fX;	y = fY;	z = fZ;
	}

	Void Set(Float32 fX, Float32 fY, Float32 fZ)
	{
		x = fX;	y = fY;	z = fZ;
	}

	Void Set(Float32* data)
	{
		x = data[0];	y = data[1];	z = data[2];
	}

/*!***************************************************************************
 @Function			XRVec3
 @Input				fValue	a component value
 @Description		Constructor from a single value.
*****************************************************************************/
	XRVec3(const Float32 fValue)
	{
		x = fValue; y = fValue; z = fValue;
	}
/*!***************************************************************************
 @Function			XRVec3
 @Input				pVec	an array
 @Description		Constructor from an array
*****************************************************************************/
	XRVec3(const Float32* pVec)
	{
		x = (*pVec++); y = (*pVec++); z = *pVec;
	}
/*!***************************************************************************
 @Function			XRVec3
 @Input				v4Vec a XRVec4
 @Description		Constructor from a XRVec4
*****************************************************************************/
	XRVec3(const XRVec4& v4Vec);
/*!***************************************************************************
** Operators
****************************************************************************/
/*!***************************************************************************
 @Function			+
 @Input				rhs another XRVec3
 @Returns			result of addition
 @Description		componentwise addition operator for two XRVec3s
*****************************************************************************/
	XRVec3 operator+(const XRVec3& rhs) const
	{
		XRVec3 out;
		out.x = x+rhs.x;
		out.y = y+rhs.y;
		out.z = z+rhs.z;
		return out;
	}
/*!***************************************************************************
 @Function			-
 @Input				rhs another XRVec3
 @Returns			result of subtraction
 @Description		componentwise subtraction operator for two XRVec3s
****************************************************************************/
	XRVec3 operator-(const XRVec3& rhs) const
	{
		XRVec3 out;
		out.x = x-rhs.x;
		out.y = y-rhs.y;
		out.z = z-rhs.z;
		return out;
	}

/*!***************************************************************************
 @Function			+=
 @Input				rhs another XRVec3
 @Returns			result of addition
 @Description		componentwise addition and assignement operator for two XRVec3s
****************************************************************************/
	XRVec3& operator+=(const XRVec3& rhs)
	{
		x +=rhs.x;
		y +=rhs.y;
		z +=rhs.z;
		return *this;
	}

/*!***************************************************************************
 @Function			-=
 @Input				rhs another XRVec3
 @Returns			result of subtraction
 @Description		componentwise subtraction and assignement operator for two XRVec3s
****************************************************************************/
	XRVec3& operator-=(const XRVec3& rhs)
	{
		x -=rhs.x;
		y -=rhs.y;
		z -=rhs.z;
		return *this;
	}

/*!***************************************************************************
 @Function			-
 @Input				rhs another XRVec3
 @Returns			result of negation
 @Description		negation operator for a XRVec3
****************************************************************************/
	friend XRVec3 operator - (const XRVec3& rhs) { return XRVec3(rhs) *= f2vt(-1); }

/*!***************************************************************************
 @Function			*
 @Input				lhs single value
 @Input				rhs a XRVec3
 @Returns			result of multiplication
 @Description		multiplication operator for a XRVec3
****************************************************************************/
	friend XRVec3 operator*(const Float32 lhs, const XRVec3&  rhs)
	{
		XRVec3 out;
		out.x = VERTTYPEMUL(lhs,rhs.x);
		out.y = VERTTYPEMUL(lhs,rhs.y);
		out.z = VERTTYPEMUL(lhs,rhs.z);
		return out;
	}

/*!***************************************************************************
 @Function			*
 @Input				lhs single value
 @Input				rhs a XRVec3
 @Returns			result of negation
 @Description		negation operator for a XRVec3
****************************************************************************/
	friend XRVec3 operator/(const Float32 lhs, const XRVec3&  rhs)
	{
		XRVec3 out;
		out.x = VERTTYPEDIV(lhs,rhs.x);
		out.y = VERTTYPEDIV(lhs,rhs.y);
		out.z = VERTTYPEDIV(lhs,rhs.z);
		return out;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs a XRMat3
 @Returns			result of multiplication
 @Description		matrix multiplication operator XRVec3 and XRMat3
****************************************************************************/
	XRVec3 operator*(const XRMat3& rhs) const;

/*!***************************************************************************
 @Function			*=
 @Input				rhs a XRMat3
 @Returns			result of multiplication and assignment
 @Description		matrix multiplication and assignment operator for XRVec3 and XRMat3
****************************************************************************/
	XRVec3& operator*=(const XRMat3& rhs);

/*!***************************************************************************
 @Function			*
 @Input				rhs a single value
 @Returns			result of multiplication
 @Description		componentwise multiplication by single dimension value for XRVec3
****************************************************************************/
	XRVec3 operator*(const Float32& rhs) const
	{
		XRVec3 out;
		out.x = VERTTYPEMUL(x,rhs);
		out.y = VERTTYPEMUL(y,rhs);
		out.z = VERTTYPEMUL(z,rhs);
		return out;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs a single value
 @Returns			result of multiplication and assignment
 @Description		componentwise multiplication and assignement by single
					dimension value	for XRVec3
****************************************************************************/
	XRVec3& operator*=(const Float32& rhs)
	{
		x = VERTTYPEMUL(x,rhs);
		y = VERTTYPEMUL(y,rhs);
		z = VERTTYPEMUL(z,rhs);
		return *this;
	}

/*!***************************************************************************
 @Function			/
 @Input				rhs a single value
 @Returns			result of division
 @Description		componentwise division by single
					dimension value	for XRVec3
****************************************************************************/
	XRVec3 operator/(const Float32& rhs) const
	{
		XRVec3 out;
		out.x = VERTTYPEDIV(x,rhs);
		out.y = VERTTYPEDIV(y,rhs);
		out.z = VERTTYPEDIV(z,rhs);
		return out;
	}

/*!***************************************************************************
 @Function			/=
 @Input				rhs a single value
 @Returns			result of division and assignment
 @Description		componentwise division and assignement by single
					dimension value	for XRVec3
****************************************************************************/
	XRVec3& operator/=(const Float32& rhs)
	{
		x = VERTTYPEDIV(x,rhs);
		y = VERTTYPEDIV(y,rhs);
		z = VERTTYPEDIV(z,rhs);
		return *this;
	}

/*!***************************************************************************
 @Function			==
 @Input				rhs a single value
 @Returns			true if the two vectors are equal
 @Description		XRVec3 equality operator
****************************************************************************/
	bool operator==(const XRVec3& rhs) const
	{
		if(x != rhs.x) return false;
		if(y != rhs.y) return false;
		if(z != rhs.z) return false;
		return true;
	}

/*!***************************************************************************
@Function			!=
@Input				rhs a single value
@Returns			true if the two vectors are not equal
@Description		XRVec3 inequality operator
	****************************************************************************/
	bool operator!=(const XRVec3& rhs) const
	{
		if(x == rhs.x)
			return false;

		return true;
	}
	// FUNCTIONS
/*!***************************************************************************
 @Function			lenSqr
 @Returns			the square of the magnitude of the vector
 @Description		calculates the square of the magnitude of the vector
****************************************************************************/
	Float32 lenSqr() const
	{
		return VERTTYPEMUL(x,x)+VERTTYPEMUL(y,y)+VERTTYPEMUL(z,z);
	}

/*!***************************************************************************
 @Function			length
 @Returns			the of the magnitude of the vector
 @Description		calculates the magnitude of the vector
****************************************************************************/
	Float32 length() const
	{
		return (Float32) f2vt(sqrt(vt2f(x)*vt2f(x) + vt2f(y)*vt2f(y) + vt2f(z)*vt2f(z)));
	}

/*!***************************************************************************
 @Function			normalize
 @Returns			the normalized value of the vector
 @Description		normalizes the vector
****************************************************************************/
	XRVec3 normalize()
	{
#if defined(XR_FIXED_POINT_ENABLE)
		// Scale vector by uniform value
		int n = XRABS(x) + XRABS(y) + XRABS(z);
		x = VERTTYPEDIV(x, n);
		y = VERTTYPEDIV(y, n);
		z = VERTTYPEDIV(z, n);

		// Calculate x2+y2+z2/sqrt(x2+y2+z2)
		int f = dot(*this);
		f = VERTTYPEDIV(XRF2X(1.0f), XRF2X(sqrt(XRX2F(f))));

		// Multiply vector components by f
		x = XRXMUL(x, f);
		y = XRXMUL(y, f);
		z = XRXMUL(z, f);
#else
		Float32 len = length();
		x =VERTTYPEDIV(x,len);
		y =VERTTYPEDIV(y,len);
		z =VERTTYPEDIV(z,len);
#endif
		return *this;
	}

/*!***************************************************************************
 @Function			normalized
 @Returns			returns the normalized value of the vector
 @Description		returns a normalized vector of the same direction as this
					vector
****************************************************************************/
	XRVec3 normalized() const
	{
		XRVec3 out;
#if defined(XR_FIXED_POINT_ENABLE)
		// Scale vector by uniform value
		int n = XRABS(x) + XRABS(y) + XRABS(z);
		out.x = VERTTYPEDIV(x, n);
		out.y = VERTTYPEDIV(y, n);
		out.z = VERTTYPEDIV(z, n);

		// Calculate x2+y2+z2/sqrt(x2+y2+z2)
		int f = out.dot(out);
		f = VERTTYPEDIV(XRF2X(1.0f), XRF2X(sqrt(XRX2F(f))));

		// Multiply vector components by f
		out.x = XRXMUL(out.x, f);
		out.y = XRXMUL(out.y, f);
		out.z = XRXMUL(out.z, f);
#else
		Float32 len = length();
		out.x =VERTTYPEDIV(x,len);
		out.y =VERTTYPEDIV(y,len);
		out.z =VERTTYPEDIV(z,len);
#endif
		return out;
	}

/*!***************************************************************************
 @Function			dot
 @Input				rhs a single value
 @Returns			scalar product
 @Description		calculate the scalar product of two XRVec3s
****************************************************************************/
	Float32 dot(const XRVec3& rhs)
	{
		return VERTTYPEMUL(x,rhs.x)+VERTTYPEMUL(y,rhs.y)+VERTTYPEMUL(z,rhs.z);
	}

/*!***************************************************************************
 @Function			cross
 @Returns			returns three-dimensional vector
 @Description		calculate the cross product of two XRVec3s
****************************************************************************/
	XRVec3 cross(const XRVec3& rhs)
	{
		XRVec3 out;
		out.x = VERTTYPEMUL(y,rhs.z)-VERTTYPEMUL(z,rhs.y);
		out.y = VERTTYPEMUL(z,rhs.x)-VERTTYPEMUL(x,rhs.z);
		out.z = VERTTYPEMUL(x,rhs.y)-VERTTYPEMUL(y,rhs.x);
		return out;
	}

/*!***************************************************************************
 @Function			ptr
 @Returns			pointer
 @Description		returns a pointer to memory containing the values of the
					XRVec3
****************************************************************************/
	Float32 *ptr() { return (Float32*)this; }
};

/*!***************************************************************************
** XRVec4 4 component vector
****************************************************************************/
struct XRVec4 : public XRVECTOR4
{
/*!***************************************************************************
** Constructors
****************************************************************************/
/*!***************************************************************************
 @Function			XRVec4
 @Description		Blank constructor.
*****************************************************************************/
	XRVec4(){}

/*!***************************************************************************
 @Function			XRVec3
 @Description		Blank constructor.
*****************************************************************************/
	XRVec4(const Float32 vec)
	{
		x = vec; y = vec; z = vec; w = vec;
	}

/*!***************************************************************************
 @Function			multiple value constructor
 @Input				fX value of x component
 @Input				fY value of y component
 @Input				fZ value of z component
 @Input				fW value of w component
 @Description		Constructs a XRVec4 from 4 separate values
****************************************************************************/
	XRVec4(Float32 fX, Float32 fY, Float32 fZ, Float32 fW)
	{
		x = fX;	y = fY;	z = fZ;	w = fW;
	}
	Void Set(Float32 fX, Float32 fY, Float32 fZ, Float32 fW)
	{
		x = fX;	y = fY;	z = fZ;	w = fW;
	}
	Void Set(Float32* data)
	{
		x = data[0];	y = data[1];	z = data[2];	w = data[3];
	}
/*!***************************************************************************
 @Function			constructor from XRVec3
 @Input				vec3 a XRVec3
 @Input				fW value of w component
 @Description		Constructs a XRVec4 from a vec3 and a w component
****************************************************************************/
	XRVec4(const XRVec3& vec3, Float32 fW)
	{
		x = vec3.x;	y = vec3.y;	z = vec3.z;	w = fW;
	}

/*!***************************************************************************
 @Function			constructor from XRVec3
 @Input				fX value of x component
 @Input				vec3 a XRVec3
 @Description		Constructs a vec4 from a vec3 and a w component
****************************************************************************/
	XRVec4(Float32 fX, const XRVec3& vec3)
	{
		x = fX;	y = vec3.x;	z = vec3.y;	w = vec3.z;
	}

/*!***************************************************************************
 @Function			constructor from array
 @Input				pVec a pointer to an array of four values
 @Description		Constructs a XRVec4 from a pointer to an array of four values
****************************************************************************/
	XRVec4(const Float32* pVec)
	{
		x = (*pVec++); y = (*pVec++); z= (*pVec++); w = *pVec;
	}

/*!***************************************************************************
** XRVec4 Operators
****************************************************************************/
/*!***************************************************************************
 @Function			+
 @Input				rhs another XRVec4
 @Returns			result of addition
 @Description		Addition operator for XRVec4
****************************************************************************/
	XRVec4 operator+(const XRVec4& rhs) const
	{
		XRVec4 out;
		out.x = x+rhs.x;
		out.y = y+rhs.y;
		out.z = z+rhs.z;
		out.w = w+rhs.w;
		return out;
	}

/*!***************************************************************************
 @Function			-
 @Input				rhs another XRVec4
 @Returns			result of subtraction
 @Description		Subtraction operator for XRVec4
****************************************************************************/
	XRVec4 operator-(const XRVec4& rhs) const
	{
		XRVec4 out;
		out.x = x-rhs.x;
		out.y = y-rhs.y;
		out.z = z-rhs.z;
		out.w = w-rhs.w;
		return out;
	}

/*!***************************************************************************
 @Function			+=
 @Input				rhs another XRVec4
 @Returns			result of addition and assignment
 @Description		Addition and assignment operator for XRVec4
****************************************************************************/
	XRVec4& operator+=(const XRVec4& rhs)
	{
		x +=rhs.x;
		y +=rhs.y;
		z +=rhs.z;
		w +=rhs.w;
		return *this;
	}

/*!***************************************************************************
 @Function			-=
 @Input				rhs another XRVec4
 @Returns			result of subtraction and assignment
 @Description		Subtraction and assignment operator for XRVec4
****************************************************************************/
	XRVec4& operator-=(const XRVec4& rhs)
	{
		x -=rhs.x;
		y -=rhs.y;
		z -=rhs.z;
		w -=rhs.w;
		return *this;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs a XRMat4
 @Returns			result of multiplication
 @Description		matrix multiplication for XRVec4 and XRMat4
****************************************************************************/
	XRVec4 operator*(const XRMat4& rhs) const;

/*!***************************************************************************
 @Function			*=
 @Input				rhs a XRMat4
 @Returns			result of multiplication and assignement
 @Description		matrix multiplication and assignment for XRVec4 and XRMat4
****************************************************************************/
	XRVec4& operator*=(const XRMat4& rhs);

/*!***************************************************************************
 @Function			*
 @Input				rhs a single dimension value
 @Returns			result of multiplication
 @Description		componentwise multiplication of a XRVec4 by a single value
****************************************************************************/
	XRVec4 operator*(const Float32& rhs) const
	{
		XRVec4 out;
		out.x = VERTTYPEMUL(x,rhs);
		out.y = VERTTYPEMUL(y,rhs);
		out.z = VERTTYPEMUL(z,rhs);
		out.w = VERTTYPEMUL(w,rhs);
		return out;
	}

/*!***************************************************************************
 @Function			*=
 @Input				rhs a single dimension value
 @Returns			result of multiplication and assignment
 @Description		componentwise multiplication and assignment of a XRVec4 by
				a single value
****************************************************************************/
	XRVec4& operator*=(const Float32& rhs)
	{
		x = VERTTYPEMUL(x,rhs);
		y = VERTTYPEMUL(y,rhs);
		z = VERTTYPEMUL(z,rhs);
		w = VERTTYPEMUL(w,rhs);
		return *this;
	}

/*!***************************************************************************
 @Function			/
 @Input				rhs a single dimension value
 @Returns			result of division
 @Description		componentwise division of a XRVec4 by a single value
****************************************************************************/
	XRVec4 operator/(const Float32& rhs) const
	{
		XRVec4 out;
		out.x = VERTTYPEDIV(x,rhs);
		out.y = VERTTYPEDIV(y,rhs);
		out.z = VERTTYPEDIV(z,rhs);
		out.w = VERTTYPEDIV(w,rhs);
		return out;
	}

/*!***************************************************************************
 @Function			/=
 @Input				rhs a single dimension value
 @Returns			result of division and assignment
 @Description		componentwise division and assignment of a XRVec4 by
					a single value
****************************************************************************/
	XRVec4& operator/=(const Float32& rhs)
	{
		x = VERTTYPEDIV(x,rhs);
		y = VERTTYPEDIV(y,rhs);
		z = VERTTYPEDIV(z,rhs);
		w = VERTTYPEDIV(w,rhs);
		return *this;
	}

/*!***************************************************************************
 @Function			*
 @Input				lhs a single dimension value
 @Input				rhs a XRVec4
 @Returns			result of muliplication
 @Description		componentwise multiplication of a XRVec4 by
					a single value
****************************************************************************/
friend XRVec4 operator*(const Float32 lhs, const XRVec4&  rhs)
{
	XRVec4 out;
	out.x = VERTTYPEMUL(lhs,rhs.x);
	out.y = VERTTYPEMUL(lhs,rhs.y);
	out.z = VERTTYPEMUL(lhs,rhs.z);
	out.w = VERTTYPEMUL(lhs,rhs.w);
	return out;
}

/*!***************************************************************************
 @Function			==
 @Input				rhs a single value
 @Returns			true if the two vectors are equal
 @Description		XRVec4 equality operator
****************************************************************************/
	bool operator==(const XRVec4& rhs) const
	{
		if(x != rhs.x) return false;
		if(y != rhs.y) return false;
		if(z != rhs.z) return false;
		if(w != rhs.w) return false;
		return true;
	}

/*!***************************************************************************
@Function			!=
@Input				rhs a single value
@Returns			true if the two vectors are not equal
@Description		XRVec4 inequality operator
	****************************************************************************/
	bool operator!=(const XRVec3& rhs) const
	{
		if(x == rhs.x)
			return false;

		return true;
	}
/*!***************************************************************************
** Functions
****************************************************************************/
/*!***************************************************************************
 @Function			lenSqr
 @Returns			square of the magnitude of the vector
 @Description		calculates the square of the magnitude of the vector
****************************************************************************/
	Float32 lenSqr() const
	{
		return VERTTYPEMUL(x,x)+VERTTYPEMUL(y,y)+VERTTYPEMUL(z,z)+VERTTYPEMUL(w,w);
	}

/*!***************************************************************************
 @Function			length
 @Returns			the magnitude of the vector
 @Description		calculates the magnitude of the vector
****************************************************************************/
	Float32 length() const
	{
		return (Float32) f2vt(sqrt(vt2f(x)*vt2f(x) + vt2f(y)*vt2f(y) + vt2f(z)*vt2f(z) + vt2f(w)*vt2f(w)));
	}

/*!***************************************************************************
 @Function			normalize
 @Returns			normalized vector
 @Description		calculates the normalized value of a XRVec4
****************************************************************************/
	XRVec4 normalize()
	{
		Float32 len = length();
		x =VERTTYPEDIV(x,len);
		y =VERTTYPEDIV(y,len);
		z =VERTTYPEDIV(z,len);
		w =VERTTYPEDIV(w,len);
		return *this;
	}
/*!***************************************************************************
 @Function			normalized
 @Returns			normalized vector
 @Description		returns a normalized vector of the same direction as this
					vector
****************************************************************************/
	XRVec4 normalized() const
	{
		XRVec4 out;
		Float32 len = length();
		out.x =VERTTYPEDIV(x,len);
		out.y =VERTTYPEDIV(y,len);
		out.z =VERTTYPEDIV(z,len);
		out.w =VERTTYPEDIV(w,len);
		return out;
	}

/*!***************************************************************************
 @Function			dot
 @Returns			scalar product
 @Description		returns a normalized vector of the same direction as this
					vector
****************************************************************************/
	Float32 dot(const XRVec4& rhs)
	{
		return VERTTYPEMUL(x,rhs.x)+VERTTYPEMUL(y,rhs.y)+VERTTYPEMUL(z,rhs.z)+VERTTYPEMUL(w,rhs.w);
	}

/*!***************************************************************************
 @Function			ptr
 @Returns			pointer to vector values
 @Description		returns a pointer to memory containing the values of the
					XRVec3
****************************************************************************/
	Float32 *ptr() { return (Float32*)this; }
};

/*!***************************************************************************
** XRMat3 3x3 Matrix
****************************************************************************/
struct XRMat3 : public XRMATRIX3
{
/*!***************************************************************************
** Constructors
****************************************************************************/
/*!***************************************************************************
 @Function			XRMat3
 @Description		Blank constructor.
*****************************************************************************/
	XRMat3(){}
/*!***************************************************************************
 @Function			XRMat3
 @Input				pMat an array of values for the matrix
 @Description		Constructor from array.
*****************************************************************************/
	XRMat3(const Float32* pMat)
	{
		Float32* ptr = f;
		for(int i=0;i<9;i++)
		{
			(*ptr++)=(*pMat++);
		}
	}

/*!***************************************************************************
 @Function			XRMat3
 @Input				m0 matrix value
 @Input				m1 matrix value
 @Input				m2 matrix value
 @Input				m3 matrix value
 @Input				m4 matrix value
 @Input				m5 matrix value
 @Input				m6 matrix value
 @Input				m7 matrix value
 @Input				m8 matrix value
 @Description		Constructor from distinct values.
*****************************************************************************/
	XRMat3(Float32 m0,Float32 m1,Float32 m2,
		Float32 m3,Float32 m4,Float32 m5,
		Float32 m6,Float32 m7,Float32 m8)
	{
		f[0]=m0;f[1]=m1;f[2]=m2;
		f[3]=m3;f[4]=m4;f[5]=m5;
		f[6]=m6;f[7]=m7;f[8]=m8;
	}

/*!***************************************************************************
 @Function			XRMat3
 @Input				mat - a XRMat4
 @Description		Constructor from 4x4 matrix - uses top left values
*****************************************************************************/
	XRMat3(const XRMat4& mat);

/****************************************************************************
** XRMat3 OPERATORS
****************************************************************************/
/*!***************************************************************************
 @Function			()
 @Input				row			row of matrix
 @Input				column		column of matrix
 @Returns			value of element
 @Description		Returns the value of the element at the specified row and column 
					of the XRMat3
*****************************************************************************/
	Float32& operator()(const int row, const int column)
	{
		return f[column*3+row];
	}
/*!***************************************************************************
 @Function			()
 @Input				row			row of matrix
 @Input				column		column of matrix
 @Returns			value of element
 @Description		Returns the value of the element at the specified row and column 
					of the XRMat3
*****************************************************************************/
	const Float32& operator()(const int row, const int column) const
	{
		return f[column*3+row];
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs another XRMat3
 @Returns			result of multiplication
 @Description		Matrix multiplication of two 3x3 matrices.
*****************************************************************************/
	XRMat3 operator*(const XRMat3& rhs) const
	{
		XRMat3 out;
		// col 1
		out.f[0] =	VERTTYPEMUL(f[0],rhs.f[0])+VERTTYPEMUL(f[3],rhs.f[1])+VERTTYPEMUL(f[6],rhs.f[2]);
		out.f[1] =	VERTTYPEMUL(f[1],rhs.f[0])+VERTTYPEMUL(f[4],rhs.f[1])+VERTTYPEMUL(f[7],rhs.f[2]);
		out.f[2] =	VERTTYPEMUL(f[2],rhs.f[0])+VERTTYPEMUL(f[5],rhs.f[1])+VERTTYPEMUL(f[8],rhs.f[2]);

		// col 2
		out.f[3] =	VERTTYPEMUL(f[0],rhs.f[3])+VERTTYPEMUL(f[3],rhs.f[4])+VERTTYPEMUL(f[6],rhs.f[5]);
		out.f[4] =	VERTTYPEMUL(f[1],rhs.f[3])+VERTTYPEMUL(f[4],rhs.f[4])+VERTTYPEMUL(f[7],rhs.f[5]);
		out.f[5] =	VERTTYPEMUL(f[2],rhs.f[3])+VERTTYPEMUL(f[5],rhs.f[4])+VERTTYPEMUL(f[8],rhs.f[5]);

		// col3
		out.f[6] =	VERTTYPEMUL(f[0],rhs.f[6])+VERTTYPEMUL(f[3],rhs.f[7])+VERTTYPEMUL(f[6],rhs.f[8]);
		out.f[7] =	VERTTYPEMUL(f[1],rhs.f[6])+VERTTYPEMUL(f[4],rhs.f[7])+VERTTYPEMUL(f[7],rhs.f[8]);
		out.f[8] =	VERTTYPEMUL(f[2],rhs.f[6])+VERTTYPEMUL(f[5],rhs.f[7])+VERTTYPEMUL(f[8],rhs.f[8]);
		return out;
	}

/*!***************************************************************************
 @Function			+
 @Input				rhs another XRMat3
 @Returns			result of addition
 @Description		element by element addition operator.
*****************************************************************************/
	XRMat3 operator+(const XRMat3& rhs) const
	{
		XRMat3 out;
		Float32 const *lptr = f, *rptr = rhs.f;
		Float32 *outptr = out.f;
		for(int i=0;i<9;i++)
		{
			(*outptr++) = (*lptr++) + (*rptr++);
		}
		return out;
	}

/*!***************************************************************************
 @Function			-
 @Input				rhs another XRMat3
 @Returns			result of subtraction
 @Description		element by element subtraction operator.
*****************************************************************************/
	XRMat3 operator-(const XRMat3& rhs) const
	{
		XRMat3 out;
		Float32 const *lptr = f, *rptr = rhs.f;
		Float32 *outptr = out.f;
		for(int i=0;i<9;i++)
		{
			(*outptr++) = (*lptr++) - (*rptr++);
		}
		return out;
	}

/*!***************************************************************************
 @Function			+=
 @Input				rhs another XRMat3
 @Returns			result of addition and assignment
 @Description		element by element addition and assignment operator.
*****************************************************************************/
	XRMat3& operator+=(const XRMat3& rhs)
	{
		Float32 *lptr = f;
		Float32 const *rptr = rhs.f;
		for(int i=0;i<9;i++)
		{
			(*lptr++) += (*rptr++);
		}
		return *this;
	}

/*!***************************************************************************
 @Function			-=
 @Input				rhs another XRMat3
 @Returns			result of subtraction and assignment
 @Description		element by element subtraction and assignment operator.
*****************************************************************************/
	XRMat3& operator-=(const XRMat3& rhs)
	{
		Float32 *lptr = f;
		Float32 const *rptr = rhs.f;
		for(int i=0;i<9;i++)
		{
			(*lptr++) -= (*rptr++);
		}
		return *this;
	}

/*!***************************************************************************
 @Function			*=
 @Input				rhs another XRMat3
 @Returns			result of multiplication and assignment
 @Description		Matrix multiplication and assignment of two 3x3 matrices.
*****************************************************************************/
	XRMat3& operator*=(const XRMat3& rhs)
	{
		XRMat3 out;
		// col 1
		out.f[0] =	VERTTYPEMUL(f[0],rhs.f[0])+VERTTYPEMUL(f[3],rhs.f[1])+VERTTYPEMUL(f[6],rhs.f[2]);
		out.f[1] =	VERTTYPEMUL(f[1],rhs.f[0])+VERTTYPEMUL(f[4],rhs.f[1])+VERTTYPEMUL(f[7],rhs.f[2]);
		out.f[2] =	VERTTYPEMUL(f[2],rhs.f[0])+VERTTYPEMUL(f[5],rhs.f[1])+VERTTYPEMUL(f[8],rhs.f[2]);

		// col 2
		out.f[3] =	VERTTYPEMUL(f[0],rhs.f[3])+VERTTYPEMUL(f[3],rhs.f[4])+VERTTYPEMUL(f[6],rhs.f[5]);
		out.f[4] =	VERTTYPEMUL(f[1],rhs.f[3])+VERTTYPEMUL(f[4],rhs.f[4])+VERTTYPEMUL(f[7],rhs.f[5]);
		out.f[5] =	VERTTYPEMUL(f[2],rhs.f[3])+VERTTYPEMUL(f[5],rhs.f[4])+VERTTYPEMUL(f[8],rhs.f[5]);

		// col3
		out.f[6] =	VERTTYPEMUL(f[0],rhs.f[6])+VERTTYPEMUL(f[3],rhs.f[7])+VERTTYPEMUL(f[6],rhs.f[8]);
		out.f[7] =	VERTTYPEMUL(f[1],rhs.f[6])+VERTTYPEMUL(f[4],rhs.f[7])+VERTTYPEMUL(f[7],rhs.f[8]);
		out.f[8] =	VERTTYPEMUL(f[2],rhs.f[6])+VERTTYPEMUL(f[5],rhs.f[7])+VERTTYPEMUL(f[8],rhs.f[8]);
		*this = out;
		return *this;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs a single value
 @Returns			result of multiplication and assignment
 @Description		element multiplication by a single value.
*****************************************************************************/
	XRMat3& operator*(const Float32 rhs)
	{
		for (int i=0; i<9; ++i)
		{
			f[i]*=rhs;
		}
		return *this;
	}
/*!***************************************************************************
 @Function			*=
 @Input				rhs a single value
 @Returns			result of multiplication and assignment
 @Description		element multiplication and assignment by a single value.
*****************************************************************************/
	XRMat3& operator*=(const Float32 rhs)
	{
		for (int i=0; i<9; ++i)
		{
			f[i]*=rhs;
		}
		return *this;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs another XRVec3
 @Returns			result of multiplication
 @Description		Matrix multiplication of 3x3 matrix and vec3
*****************************************************************************/
	XRVec3 operator*(const XRVec3& rhs) const
	{
		XRVec3 out;
		out.x = VERTTYPEMUL(rhs.x,f[0])+VERTTYPEMUL(rhs.y,f[3])+VERTTYPEMUL(rhs.z,f[6]);
		out.y = VERTTYPEMUL(rhs.x,f[1])+VERTTYPEMUL(rhs.y,f[4])+VERTTYPEMUL(rhs.z,f[7]);
		out.z = VERTTYPEMUL(rhs.x,f[2])+VERTTYPEMUL(rhs.y,f[5])+VERTTYPEMUL(rhs.z,f[8]);

		return out;
	}


	// FUNCTIONS
/*!***************************************************************************
** Functions
*****************************************************************************/
/*!***************************************************************************
 @Function			determinant
 @Returns			result of multiplication
 @Description		Matrix multiplication and assignment of 3x3 matrix and vec3
*****************************************************************************/
	Float32 determinant() const
	{
		return VERTTYPEMUL(f[0],(VERTTYPEMUL(f[4],f[8])-VERTTYPEMUL(f[7],f[5])))
			- VERTTYPEMUL(f[3],(VERTTYPEMUL(f[1],f[8])-VERTTYPEMUL(f[7],f[2])))
			+ VERTTYPEMUL(f[6],(VERTTYPEMUL(f[1],f[5])-VERTTYPEMUL(f[4],f[2])));
	}

/*!***************************************************************************
 @Function			inverse
 @Returns			inverse mat3
 @Description		Calculates multiplicative inverse of this matrix
*****************************************************************************/
	XRMat3 inverse() const
	{
		XRMat3 out;


		Float32 recDet = determinant();
		XrAssert(recDet!=0);
		recDet = VERTTYPEDIV(f2vt(1.0f),recDet);

		//TODO: deal with singular matrices with more than just an assert

		// inverse is 1/det * adjoint of M

		// adjoint is transpose of cofactor matrix

		// do transpose and cofactors in one step

		out.f[0] = VERTTYPEMUL(f[4],f[8]) - VERTTYPEMUL(f[5],f[7]);
		out.f[1] = VERTTYPEMUL(f[2],f[7]) - VERTTYPEMUL(f[1],f[8]);
		out.f[2] = VERTTYPEMUL(f[1],f[5]) - VERTTYPEMUL(f[2],f[4]);

		out.f[3] = VERTTYPEMUL(f[5],f[6]) - VERTTYPEMUL(f[3],f[8]);
		out.f[4] = VERTTYPEMUL(f[0],f[8]) - VERTTYPEMUL(f[2],f[6]);
		out.f[5] = VERTTYPEMUL(f[2],f[3]) - VERTTYPEMUL(f[0],f[5]);

		out.f[6] = VERTTYPEMUL(f[3],f[7]) - VERTTYPEMUL(f[4],f[6]);
		out.f[7] = VERTTYPEMUL(f[1],f[6]) - VERTTYPEMUL(f[0],f[7]);
		out.f[8] = VERTTYPEMUL(f[0],f[4]) - VERTTYPEMUL(f[1],f[3]);

		out *= recDet;
		return out;
	}

/*!***************************************************************************
 @Function			transpose
 @Returns			transpose 3x3 matrix
 @Description		Calculates the transpose of this matrix
*****************************************************************************/
	XRMat3 transpose() const
	{
		XRMat3 out;
		out.f[0] = f[0];	out.f[3] = f[1];	out.f[6] = f[2];
		out.f[1] = f[3];	out.f[4] = f[4];	out.f[7] = f[5];
		out.f[2] = f[6];	out.f[5] = f[7];	out.f[8] = f[8];
		return out;
	}

/*!***************************************************************************
 @Function			ptr
 @Returns			pointer to an array of the elements of this XRMat3
 @Description		Calculates transpose of this matrix
*****************************************************************************/
	Float32 *ptr() { return (Float32*)&f; }

/*!***************************************************************************
** Static factory functions
*****************************************************************************/
/*!***************************************************************************
 @Function			Identity
 @Returns			a XRMat3 representation of the 3x3 identity matrix
 @Description		Generates an identity matrix
*****************************************************************************/
	static XRMat3 Identity()
	{
		XRMat3 out;
		out.f[0] = 1;out.f[1] = 0;out.f[2] = 0;
		out.f[3] = 0;out.f[4] = 1;out.f[5] = 0;
		out.f[6] = 0;out.f[7] = 0;out.f[8] = 1;
		return out;
	}

/*!***************************************************************************
 @Function			RotationX
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the X axis
*****************************************************************************/
	static XRMat3 RotationX(Float32 angle);

/*!***************************************************************************
 @Function			RotationY
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the Y axis
*****************************************************************************/
	static XRMat3 RotationY(Float32 angle);

/*!***************************************************************************
 @Function			RotationZ
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the Z axis
*****************************************************************************/
	static XRMat3 RotationZ(Float32 angle);

/*!***************************************************************************
 @Function			Scale
 @Returns			a XRMat3 corresponding to the requested scaling transformation
 @Description		Calculates a matrix corresponding to scaling of fx, fy and fz
					times in each axis.
*****************************************************************************/
	static XRMat3 Scale(const Float32 fx,const Float32 fy,const Float32 fz)
	{
		return XRMat3(fx,0,0,
			0,fy,0,
			0,0,fz);
	}


/*!***************************************************************************
 @Function			Translation
 @Returns			a XRMat3 corresponding to the requested translation
 @Description		Calculates a matrix corresponding to a transformation
					of tx and ty times in each axis.
*****************************************************************************/
	static XRMat3 Translation(const Float32 tx, const Float32 ty)
	{
		return XRMat3( f2vt(1),    0,  0,
			0,    f2vt(1),  0,
			tx,  ty,  f2vt(1));
	}

};

/*!***************************************************************************
** XRMat4 4x4 Matrix
****************************************************************************/
struct XRMat4 : public XRMATRIX
{
/*!***************************************************************************
** Constructors
****************************************************************************/
/*!***************************************************************************
 @Function			XRMat4
 @Description		Blank constructor.
*****************************************************************************/
	XRMat4(){}
/*!***************************************************************************
 @Function			XRMat4
 @Input				m0 matrix value
 @Input				m1 matrix value
 @Input				m2 matrix value
 @Input				m3 matrix value
 @Input				m4 matrix value
 @Input				m5 matrix value
 @Input				m6 matrix value
 @Input				m7 matrix value
 @Input				m8 matrix value
 @Input				m9 matrix value
 @Input				m10 matrix value
 @Input				m11 matrix value
 @Input				m12 matrix value
 @Input				m13 matrix value
 @Input				m14 matrix value
 @Input				m15 matrix value
 @Description		Constructor from array.
*****************************************************************************/
	XRMat4(Float32 m0,Float32 m1,Float32 m2,Float32 m3,
		Float32 m4,Float32 m5,Float32 m6,Float32 m7,
		Float32 m8,Float32 m9,Float32 m10,Float32 m11,
		Float32 m12,Float32 m13,Float32 m14,Float32 m15)
	{
		f[0]=m0;f[1]=m1;f[2]=m2;f[3]=m3;
		f[4]=m4;f[5]=m5;f[6]=m6;f[7]=m7;
		f[8]=m8;f[9]=m9;f[10]=m10;f[11]=m11;
		f[12]=m12;f[13]=m13;f[14]=m14;f[15]=m15;
	}
/*!***************************************************************************
 @Function			XRMat4
 @Input				mat A pointer to an array of 16 VERTTYPEs
 @Description		Constructor from distinct values.
*****************************************************************************/
	XRMat4(const Float32* mat)
	{
		Float32* ptr = f;
		for(int i=0;i<16;i++)
		{
			(*ptr++)=(*mat++);
		}
	}

/****************************************************************************
** XRMat4 OPERATORS
****************************************************************************/
/*!***************************************************************************
 @Function			()
 @Input				r - row of matrix
 @Input				c - column of matrix
 @Returns			value of element
 @Description		Returns value of the element at row r and colun c of the
					XRMat4
*****************************************************************************/
	Float32& operator()(const int r, const int c)
	{
		return f[c*4+r];
	}

/*!***************************************************************************
 @Function			()
 @Input				r - row of matrix
 @Input				c - column of matrix
 @Returns			value of element
 @Description		Returns value of the element at row r and colun c of the
					XRMat4
*****************************************************************************/
	const Float32& operator()(const int r, const int c) const
	{
		return f[c*4+r];
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs another XRMat4
 @Returns			result of multiplication
 @Description		Matrix multiplication of two 4x4 matrices.
*****************************************************************************/
	XRMat4 operator*(const XRMat4& rhs) const;

/*!***************************************************************************
 @Function			+
 @Input				rhs another XRMat4
 @Returns			result of addition
 @Description		element by element addition operator.
*****************************************************************************/
	XRMat4 operator+(const XRMat4& rhs) const
	{
		XRMat4 out;
		Float32 const *lptr = f, *rptr = rhs.f;
		Float32 *outptr = out.f;
		for(int i=0;i<16;i++)
		{
			(*outptr++) = (*lptr++) + (*rptr++);
		}
		return out;
	}

/*!***************************************************************************
 @Function			-
 @Input				rhs another XRMat4
 @Returns			result of subtraction
 @Description		element by element subtraction operator.
*****************************************************************************/
	XRMat4 operator-(const XRMat4& rhs) const
	{
		XRMat4 out;
		for(int i=0;i<16;i++)
		{
			out.f[i] = f[i]-rhs.f[i];
		}
		return out;
	}

/*!***************************************************************************
 @Function			+=
 @Input				rhs another XRMat4
 @Returns			result of addition and assignment
 @Description		element by element addition and assignment operator.
*****************************************************************************/
	XRMat4& operator+=(const XRMat4& rhs)
	{
		Float32 *lptr = f;
		Float32 const *rptr = rhs.f;
		for(int i=0;i<16;i++)
		{
			(*lptr++) += (*rptr++);
		}
		return *this;
	}

/*!***************************************************************************
 @Function			-=
 @Input				rhs another XRMat4
 @Returns			result of subtraction and assignment
 @Description		element by element subtraction and assignment operator.
*****************************************************************************/
	XRMat4& operator-=(const XRMat4& rhs)
	{
		Float32 *lptr = f;
		Float32 const *rptr = rhs.f;
		for(int i=0;i<16;i++)
		{
			(*lptr++) -= (*rptr++);
		}
		return *this;
	}


/*!***************************************************************************
 @Function			*=
 @Input				rhs another XRMat4
 @Returns			result of multiplication and assignment
 @Description		Matrix multiplication and assignment of two 4x4 matrices.
*****************************************************************************/
	XRMat4& operator*=(const XRMat4& rhs)
	{
		XRMat4 result;
		// col 0
		result.f[0] =	VERTTYPEMUL(f[0],rhs.f[0])+VERTTYPEMUL(f[4],rhs.f[1])+VERTTYPEMUL(f[8],rhs.f[2])+VERTTYPEMUL(f[12],rhs.f[3]);
		result.f[1] =	VERTTYPEMUL(f[1],rhs.f[0])+VERTTYPEMUL(f[5],rhs.f[1])+VERTTYPEMUL(f[9],rhs.f[2])+VERTTYPEMUL(f[13],rhs.f[3]);
		result.f[2] =	VERTTYPEMUL(f[2],rhs.f[0])+VERTTYPEMUL(f[6],rhs.f[1])+VERTTYPEMUL(f[10],rhs.f[2])+VERTTYPEMUL(f[14],rhs.f[3]);
		result.f[3] =	VERTTYPEMUL(f[3],rhs.f[0])+VERTTYPEMUL(f[7],rhs.f[1])+VERTTYPEMUL(f[11],rhs.f[2])+VERTTYPEMUL(f[15],rhs.f[3]);

		// col 1
		result.f[4] =	VERTTYPEMUL(f[0],rhs.f[4])+VERTTYPEMUL(f[4],rhs.f[5])+VERTTYPEMUL(f[8],rhs.f[6])+VERTTYPEMUL(f[12],rhs.f[7]);
		result.f[5] =	VERTTYPEMUL(f[1],rhs.f[4])+VERTTYPEMUL(f[5],rhs.f[5])+VERTTYPEMUL(f[9],rhs.f[6])+VERTTYPEMUL(f[13],rhs.f[7]);
		result.f[6] =	VERTTYPEMUL(f[2],rhs.f[4])+VERTTYPEMUL(f[6],rhs.f[5])+VERTTYPEMUL(f[10],rhs.f[6])+VERTTYPEMUL(f[14],rhs.f[7]);
		result.f[7] =	VERTTYPEMUL(f[3],rhs.f[4])+VERTTYPEMUL(f[7],rhs.f[5])+VERTTYPEMUL(f[11],rhs.f[6])+VERTTYPEMUL(f[15],rhs.f[7]);

		// col 2
		result.f[8] =	VERTTYPEMUL(f[0],rhs.f[8])+VERTTYPEMUL(f[4],rhs.f[9])+VERTTYPEMUL(f[8],rhs.f[10])+VERTTYPEMUL(f[12],rhs.f[11]);
		result.f[9] =	VERTTYPEMUL(f[1],rhs.f[8])+VERTTYPEMUL(f[5],rhs.f[9])+VERTTYPEMUL(f[9],rhs.f[10])+VERTTYPEMUL(f[13],rhs.f[11]);
		result.f[10] =	VERTTYPEMUL(f[2],rhs.f[8])+VERTTYPEMUL(f[6],rhs.f[9])+VERTTYPEMUL(f[10],rhs.f[10])+VERTTYPEMUL(f[14],rhs.f[11]);
		result.f[11] =	VERTTYPEMUL(f[3],rhs.f[8])+VERTTYPEMUL(f[7],rhs.f[9])+VERTTYPEMUL(f[11],rhs.f[10])+VERTTYPEMUL(f[15],rhs.f[11]);

		// col 3
		result.f[12] =	VERTTYPEMUL(f[0],rhs.f[12])+VERTTYPEMUL(f[4],rhs.f[13])+VERTTYPEMUL(f[8],rhs.f[14])+VERTTYPEMUL(f[12],rhs.f[15]);
		result.f[13] =	VERTTYPEMUL(f[1],rhs.f[12])+VERTTYPEMUL(f[5],rhs.f[13])+VERTTYPEMUL(f[9],rhs.f[14])+VERTTYPEMUL(f[13],rhs.f[15]);
		result.f[14] =	VERTTYPEMUL(f[2],rhs.f[12])+VERTTYPEMUL(f[6],rhs.f[13])+VERTTYPEMUL(f[10],rhs.f[14])+VERTTYPEMUL(f[14],rhs.f[15]);
		result.f[15] =	VERTTYPEMUL(f[3],rhs.f[12])+VERTTYPEMUL(f[7],rhs.f[13])+VERTTYPEMUL(f[11],rhs.f[14])+VERTTYPEMUL(f[15],rhs.f[15]);

		*this = result;
		return *this;
	}

/*!***************************************************************************
 @Function			*
 @Input				rhs a single value
 @Returns			result of multiplication and assignment
 @Description		element multiplication by a single value.
*****************************************************************************/
	XRMat4& operator*(const Float32 rhs)
	{
		for (int i=0; i<16; ++i)
		{
			f[i]*=rhs;
		}
		return *this;
	}
/*!***************************************************************************
 @Function			*=
 @Input				rhs a single value
 @Returns			result of multiplication and assignment
 @Description		element multiplication and assignment by a single value.
*****************************************************************************/
	XRMat4& operator*=(const Float32 rhs)
	{
		for (int i=0; i<16; ++i)
		{
			f[i]*=rhs;
		}
		return *this;
	}

/*!***************************************************************************
 @Function			=
 @Input				rhs another XRMat4
 @Returns			result of assignment
 @Description		element assignment operator.
*****************************************************************************/
	XRMat4& operator=(const XRMat4& rhs)
	{
		for (int i=0; i<16; ++i)
		{
			f[i] =rhs.f[i];
		}
		return *this;
	}
/*!***************************************************************************
 @Function			*
 @Input				rhs a XRVec4
 @Returns			result of multiplication
 @Description		Matrix multiplication of 4x4 matrix and vec3
*****************************************************************************/
	XRVec4 operator*(const XRVec4& rhs) const
	{
		XRVec4 out;
		out.x = VERTTYPEMUL(rhs.x,f[0])+VERTTYPEMUL(rhs.y,f[4])+VERTTYPEMUL(rhs.z,f[8])+VERTTYPEMUL(rhs.w,f[12]);
		out.y = VERTTYPEMUL(rhs.x,f[1])+VERTTYPEMUL(rhs.y,f[5])+VERTTYPEMUL(rhs.z,f[9])+VERTTYPEMUL(rhs.w,f[13]);
		out.z = VERTTYPEMUL(rhs.x,f[2])+VERTTYPEMUL(rhs.y,f[6])+VERTTYPEMUL(rhs.z,f[10])+VERTTYPEMUL(rhs.w,f[14]);
		out.w = VERTTYPEMUL(rhs.x,f[3])+VERTTYPEMUL(rhs.y,f[7])+VERTTYPEMUL(rhs.z,f[11])+VERTTYPEMUL(rhs.w,f[15]);

		return out;
	}

/*!***************************************************************************
 @Function			*=
 @Input				rhs a XRVec4
 @Returns			result of multiplication and assignment
 @Description		Matrix multiplication and assignment of 4x4 matrix and vec3
*****************************************************************************/
	XRVec4 operator*=(const XRVec4& rhs) const
	{
		XRVec4 out;
		out.x = VERTTYPEMUL(rhs.x,f[0])+VERTTYPEMUL(rhs.y,f[4])+VERTTYPEMUL(rhs.z,f[8])+VERTTYPEMUL(rhs.w,f[12]);
		out.y = VERTTYPEMUL(rhs.x,f[1])+VERTTYPEMUL(rhs.y,f[5])+VERTTYPEMUL(rhs.z,f[9])+VERTTYPEMUL(rhs.w,f[13]);
		out.z = VERTTYPEMUL(rhs.x,f[2])+VERTTYPEMUL(rhs.y,f[6])+VERTTYPEMUL(rhs.z,f[10])+VERTTYPEMUL(rhs.w,f[14]);
		out.w = VERTTYPEMUL(rhs.x,f[3])+VERTTYPEMUL(rhs.y,f[7])+VERTTYPEMUL(rhs.z,f[11])+VERTTYPEMUL(rhs.w,f[15]);

		return out;
	}

/*!***************************************************************************
 @Function			inverse
 @Returns			inverse mat4
 @Description		Calculates multiplicative inverse of this matrix
					The matrix must be of the form :
					A 0
					C 1
					Where A is a 3x3 matrix and C is a 1x3 matrix.
*****************************************************************************/
	XRMat4 inverse() const;

/*!***************************************************************************
 @Function			inverseEx
 @Returns			inverse mat4
 @Description		Calculates multiplicative inverse of this matrix
					Uses a linear equation solver and the knowledge that M.M^-1=I.
					Use this fn to calculate the inverse of matrices that
					inverse() cannot.
*****************************************************************************/
	XRMat4 inverseEx() const
	{
		XRMat4 out;
		Float32 		*ppRows[4];
		Float32 		pRes[4];
		Float32 		pIn[20];
		int				i, j;

		for(i = 0; i < 4; ++i)
			ppRows[i] = &pIn[i * 5];

		/* Solve 4 sets of 4 linear equations */
		for(i = 0; i < 4; ++i)
		{
			for(j = 0; j < 4; ++j)
			{
				ppRows[j][0] = XRMat4::Identity().f[i + 4 * j];
				memcpy(&ppRows[j][1], &f[j * 4], 4 * sizeof(Float32));
			}

			XRLinearEqSolve(pRes, (Float32**)ppRows, 4);

			for(j = 0; j < 4; ++j)
			{
				out.f[i + 4 * j] = pRes[j];
			}
		}

		return out;
	}

/*!***************************************************************************
 @Function			transpose
 @Returns			transpose mat4
 @Description		Calculates transpose of this matrix
*****************************************************************************/
	XRMat4 transpose() const
	{
		XRMat4 out;
		out.f[0] = f[0];		out.f[1] = f[4];		out.f[2] = f[8];		out.f[3] = f[12];
		out.f[4] = f[1];		out.f[5] = f[5];		out.f[6] = f[9];		out.f[7] = f[13];
		out.f[8] = f[2];		out.f[9] = f[6];		out.f[10] = f[10];		out.f[11] = f[14];
		out.f[12] = f[3];		out.f[13] = f[7];		out.f[14] = f[11];		out.f[15] = f[15];
		return out;
	}

/*!***************************************************************************
 @Function			postTranslate
 @Input				tx distance of translation in x axis
 @Input				ty distance of translation in y axis
 @Input				tz distance of translation in z axis
 @Returns			Returns this
 @Description		Alters the translation component of the transformation matrix.
*****************************************************************************/
	XRMat4& postTranslate(Float32 tx, Float32 ty, Float32 tz)
	{
		f[12] += VERTTYPEMUL(tx,f[0])+VERTTYPEMUL(ty,f[4])+VERTTYPEMUL(tz,f[8]);
		f[13] += VERTTYPEMUL(tx,f[1])+VERTTYPEMUL(ty,f[5])+VERTTYPEMUL(tz,f[9]);
		f[14] += VERTTYPEMUL(tx,f[2])+VERTTYPEMUL(ty,f[6])+VERTTYPEMUL(tz,f[10]);
		f[15] += VERTTYPEMUL(tx,f[3])+VERTTYPEMUL(ty,f[7])+VERTTYPEMUL(tz,f[11]);

//			col(3) += tx * col(0) + ty * col(1) + tz * col(2);
		return *this;
	}

/*!***************************************************************************
 @Function			postTranslate
 @Input				tvec translation vector
 @Returns			Returns this
 @Description		Alters the translation component of the transformation matrix.
*****************************************************************************/
	XRMat4& postTranslate(const XRVec3& tvec)
	{
		return postTranslate(tvec.x, tvec.y, tvec.z);
	}

/*!***************************************************************************
 @Function			postTranslate
 @Input				tx distance of translation in x axis
 @Input				ty distance of translation in y axis
 @Input				tz distance of translation in z axis
 @Returns			Returns this
 @Description		Translates the matrix from the passed parameters
*****************************************************************************/
	XRMat4& preTranslate(Float32 tx, Float32 ty, Float32 tz)
	{
		f[0]+=VERTTYPEMUL(f[3],tx);	f[4]+=VERTTYPEMUL(f[7],tx);	f[8]+=VERTTYPEMUL(f[11],tx);	f[12]+=VERTTYPEMUL(f[15],tx);
		f[1]+=VERTTYPEMUL(f[3],ty);	f[5]+=VERTTYPEMUL(f[7],ty);	f[9]+=VERTTYPEMUL(f[11],ty);	f[13]+=VERTTYPEMUL(f[15],ty);
		f[2]+=VERTTYPEMUL(f[3],tz);	f[6]+=VERTTYPEMUL(f[7],tz);	f[10]+=VERTTYPEMUL(f[11],tz);	f[14]+=VERTTYPEMUL(f[15],tz);

//			row(0) += tx * row(3);
//			row(1) += ty * row(3);
//			row(2) += tz * row(3);
		return *this;
	}

/*!***************************************************************************
 @Function			postTranslate
 @Input				tvec translation vector
 @Returns			Returns the translation defined by the passed parameters
 @Description		Translates the matrix from the passed parameters
*****************************************************************************/
	XRMat4& preTranslate(const XRVec3& tvec)
	{
		return preTranslate(tvec.x, tvec.y, tvec.z);
	}
/*!***************************************************************************
 @Function			ptr
 @Returns			pointer to an array of the elements of this XRMat4
 @Description		Calculates transpose of this matrix
*****************************************************************************/
	Float32 *ptr() { return (Float32*)&f; }

/*!***************************************************************************
** Static factory functions
*****************************************************************************/
/*!***************************************************************************
 @Function			Identity
 @Returns			a XRMat4 representation of the 4x4 identity matrix
 @Description		Generates an identity matrix
*****************************************************************************/
	static XRMat4 Identity()
	{
		XRMat4 out;
		out.f[0] = f2vt(1);out.f[1] = 0;out.f[2] = 0;out.f[3] = 0;
		out.f[4] = 0;out.f[5] = f2vt(1);out.f[6] = 0;out.f[7] = 0;
		out.f[8] = 0;out.f[9] = 0;out.f[10] = f2vt(1);out.f[11] = 0;
		out.f[12] = 0;out.f[13] = 0;out.f[14] = 0;out.f[15] = f2vt(1);
		return out;
	}

	Void MakeIdentity()
	{
		f[0] = f2vt(1);f[1] = 0;f[2] = 0;f[3] = 0;
		f[4] = 0;f[5] = f2vt(1);f[6] = 0;f[7] = 0;
		f[8] = 0;f[9] = 0;f[10] = f2vt(1);f[11] = 0;
		f[12] = 0;f[13] = 0;f[14] = 0;f[15] = f2vt(1);
	}

/*!***************************************************************************
 @Function			RotationX
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the X axis
*****************************************************************************/
	static XRMat4 RotationX(Float32 angle);
/*!***************************************************************************
 @Function			RotationY
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the Y axis
*****************************************************************************/
	static XRMat4 RotationY(Float32 angle);
/*!***************************************************************************
 @Function			RotationZ
 @Returns			a XRMat3 corresponding to the requested rotation
 @Description		Calculates a matrix corresponding to a rotation of angle
					degrees about the Z axis
*****************************************************************************/
	static XRMat4 RotationZ(Float32 angle);

/*!***************************************************************************
 @Function			Scale
 @Returns			a XRMat3 corresponding to the requested scaling transformation
 @Description		Calculates a matrix corresponding to scaling of fx, fy and fz
					times in each axis.
*****************************************************************************/
	static XRMat4 Scale(const Float32 fx,const Float32 fy,const Float32 fz)
	{
		return XRMat4(fx,0,0,0,
			0,fy,0,0,
			0,0,fz,0,
			0,0,0,f2vt(1));
	}

/*!***************************************************************************
 @Function			Translation
 @Returns			a XRMat4 corresponding to the requested translation
 @Description		Calculates a 4x4 matrix corresponding to a transformation
					of tx, ty and tz distance in each axis.
*****************************************************************************/
	static XRMat4 Translation(const Float32 tx, const Float32 ty, const Float32 tz)
	{
		return XRMat4(f2vt(1),0,0,0,
			0,f2vt(1),0,0,
			0,0,f2vt(1),0,
			tx,ty,tz,f2vt(1));
	}

/*!***************************************************************************
** Clipspace enum
** Determines whether clip space Z ranges from -1 to 1 (OGL) or from 0 to 1 (D3D)
*****************************************************************************/
	enum eClipspace { OGL, D3D };

/*!***************************************************************************
 @Function			Ortho
 @Input				left view plane
 @Input				top view plane
 @Input				right view plane
 @Input				bottom view plane
 @Input				nearPlane the near rendering plane
 @Input				farPlane the far rendering plane
 @Input				cs which clipspace convention is being used
 @Input				bRotate is the viewport in portrait or landscape mode
 @Returns			Returns the orthogonal projection matrix defined by the passed parameters
 @Description		Translates the matrix from the passed parameters
*****************************************************************************/
	static XRMat4 Ortho(Float32 left, Float32 top, Float32 right,
		Float32 bottom, Float32 nearPlane, Float32 farPlane, const eClipspace cs, bool bRotate = false)
	{
		Float32 rcplmr = VERTTYPEDIV(Float32(1),(left - right));
		Float32 rcpbmt = VERTTYPEDIV(Float32(1),(bottom - top));
		Float32 rcpnmf = VERTTYPEDIV(Float32(1),(nearPlane - farPlane));

		XRMat4 result;

		if (bRotate)
		{
			result.f[0]=0;		result.f[4]=VERTTYPEMUL(2,rcplmr); result.f[8]=0; result.f[12]=VERTTYPEMUL(-(right+left),rcplmr);
			result.f[1]=VERTTYPEMUL(-2,rcpbmt);	result.f[5]=0;		result.f[9]=0;	result.f[13]=VERTTYPEMUL((top+bottom),rcpbmt);
		}
		else
		{
			result.f[0]=VERTTYPEMUL(-2,rcplmr);	result.f[4]=0; result.f[8]=0; result.f[12]=VERTTYPEMUL(right+left,rcplmr);
			result.f[1]=0;		result.f[5]=VERTTYPEMUL(-2,rcpbmt);	result.f[9]=0;	result.f[13]=VERTTYPEMUL((top+bottom),rcpbmt);
		}
		if (cs == D3D)
		{
			result.f[2]=0;	result.f[6]=0;	result.f[10]=-rcpnmf;	result.f[14]=VERTTYPEMUL(nearPlane,rcpnmf);
		}
		else
		{
			result.f[2]=0;	result.f[6]=0;	result.f[10]=VERTTYPEMUL(-2,rcpnmf);	result.f[14]=VERTTYPEMUL(nearPlane + farPlane,rcpnmf);
		}
		result.f[3]=0;	result.f[7]=0;	result.f[11]=0;	result.f[15]=1;

		return result;
	}


/*!***************************************************************************
 @Function			LookAtRH
 @Input				vEye position of 'camera'
 @Input				vAt target that camera points at
 @Input				vUp up vector for camera
 @Returns			Returns the view matrix defined by the passed parameters
 @Description		Create a look-at view matrix for a right hand coordinate
					system
*****************************************************************************/
	static XRMat4 LookAtRH(const XRVec3& vEye, const XRVec3& vAt, const XRVec3& vUp)
		{ return LookAt(vEye, vAt, vUp, true); }
/*!***************************************************************************
 @Function			LookAtLH
 @Input				vEye position of 'camera'
 @Input				vAt target that camera points at
 @Input				vUp up vector for camera
 @Returns			Returns the view matrix defined by the passed parameters
 @Description		Create a look-at view matrix for a left hand coordinate
					system
*****************************************************************************/
	static XRMat4 LookAtLH(const XRVec3& vEye, const XRVec3& vAt, const XRVec3& vUp)
		{ return LookAt(vEye, vAt, vUp, false);	}

/*!***************************************************************************
 @Function		PerspectiveRH
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a right hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveRH(Float32 width, Float32 height, Float32 nearPlane,
		Float32 farPlane, const eClipspace cs, bool bRotate = false)
		{ return Perspective(width, height, nearPlane, farPlane, cs, true, bRotate); }

/*!***************************************************************************
 @Function		PerspectiveLH
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a left hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveLH(Float32 width, Float32 height, Float32 nearPlane, Float32 farPlane, const eClipspace cs, bool bRotate = false)
		{ return Perspective(width, height, nearPlane, farPlane, cs, false, bRotate); }

/*!***************************************************************************
 @Function		PerspectiveFloatDepthRH
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a right hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFloatDepthRH(Float32 width, Float32 height, Float32 nearPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFloatDepth(width, height, nearPlane, cs, true, bRotate); }

/*!***************************************************************************
 @Function		PerspectiveFloatDepthLH
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a left hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFloatDepthLH(Float32 width, Float32 height, Float32 nearPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFloatDepth(width, height, nearPlane, cs, false, bRotate); }

/*!***************************************************************************
 @Function		PerspectiveFovRH
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a right hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFovRH(Float32 fovy, Float32 aspect, Float32 nearPlane, Float32 farPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFov(fovy, aspect, nearPlane, farPlane, cs, true, bRotate); }
/*!***************************************************************************
 @Function		PerspectiveFovLH
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a left hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFovLH(Float32 fovy, Float32 aspect, Float32 nearPlane, Float32 farPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFov(fovy, aspect, nearPlane, farPlane, cs, false, bRotate); }

/*!***************************************************************************
 @Function		PerspectiveFovRH
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a right hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFovFloatDepthRH(Float32 fovy, Float32 aspect, Float32 nearPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFovFloatDepth(fovy, aspect, nearPlane, cs, true, bRotate); }
/*!***************************************************************************
 @Function		PerspectiveFovLH
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRotate is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix for a left hand coordinate
				system
*****************************************************************************/
	static XRMat4 PerspectiveFovFloatDepthLH(Float32 fovy, Float32 aspect, Float32 nearPlane, const eClipspace cs, bool bRotate = false)
		{ return PerspectiveFovFloatDepth(fovy, aspect, nearPlane, cs, false, bRotate); }

/*!***************************************************************************
 @Function			LookAt
 @Input				vEye position of 'camera'
 @Input				vAt target that camera points at
 @Input				vUp up vector for camera
 @Input				bRightHanded handedness of coordinate system
 @Returns			Returns the view matrix defined by the passed parameters
 @Description		Create a look-at view matrix
*****************************************************************************/
	static XRMat4 LookAt(const XRVec3& vEye, const XRVec3& vAt, const XRVec3& vUp, bool bRightHanded)
	{
		XRVec3 vForward, vUpNorm, vSide;
		XRMat4 result;

		vForward = (bRightHanded) ? vEye - vAt : vAt - vEye;

		vForward.normalize();
		vUpNorm = vUp.normalized();
		vSide   = vUpNorm.cross( vForward);
		vSide = vSide.normalized();
		vUpNorm = vForward.cross(vSide);

		result.f[0]=vSide.x;	result.f[4]=vSide.y;	result.f[8]=vSide.z;		result.f[12]=0;
		result.f[1]=vUpNorm.x;	result.f[5]=vUpNorm.y;	result.f[9]=vUpNorm.z;		result.f[13]=0;
		result.f[2]=vForward.x; result.f[6]=vForward.y;	result.f[10]=vForward.z;	result.f[14]=0;
		result.f[3]=0;			result.f[7]=0;			result.f[11]=0;				result.f[15]=f2vt(1);


		result.postTranslate(-vEye);
		return result;
	}

/*!***************************************************************************
 @Function		Perspective
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			which clipspace convention is being used
 @Input			bRightHanded	handedness of coordinate system
 @Input			bRotate		is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	Create a perspective matrix
*****************************************************************************/
	static XRMat4 Perspective(
		Float32 width, Float32 height,
		Float32 nearPlane, Float32 farPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		Float32 n2 = VERTTYPEMUL(f2vt(2),nearPlane);
		Float32 rcpnmf = VERTTYPEDIV(f2vt(1),(nearPlane - farPlane));

		XRMat4 result;
		if (bRotate)
		{
			result.f[0] = 0;	result.f[4]=VERTTYPEDIV(-n2,width);	result.f[8]=0;	result.f[12]=0;
			result.f[1] = VERTTYPEDIV(n2,height);	result.f[5]=0;	result.f[9]=0;	result.f[13]=0;
		}
		else
		{
			result.f[0] = VERTTYPEDIV(n2,width);	result.f[4]=0;	result.f[8]=0;	result.f[12]=0;
			result.f[1] = 0;	result.f[5]=VERTTYPEDIV(n2,height);	result.f[9]=0;	result.f[13]=0;
		}
		if (cs == D3D)
		{
			result.f[2] = 0;	result.f[6]=0;	result.f[10]=VERTTYPEMUL(farPlane,rcpnmf);	result.f[14]=VERTTYPEMUL(VERTTYPEMUL(farPlane,rcpnmf),nearPlane);
		}
		else
		{
			result.f[2] = 0;	result.f[6]=0;	result.f[10]=VERTTYPEMUL(farPlane+nearPlane,rcpnmf);	result.f[14]=VERTTYPEMUL(VERTTYPEMUL(farPlane,rcpnmf),n2);
		}
		result.f[3] = 0;	result.f[7]=0;	result.f[11]=f2vt(-1);	result.f[15]=0;

		if (!bRightHanded)
		{
			result.f[10] = VERTTYPEMUL(result.f[10], f2vt(-1));
			result.f[11] = f2vt(1);
		}

		return result;
	}

/*!***************************************************************************
 @Function		Perspective
 @Input			width		width of viewplane
 @Input			height		height of viewplane
 @Input			nearPlane	near clipping distance
 @Input			cs			which clipspace convention is being used
 @Input			bRightHanded	handedness of coordinate system
 @Input			bRotate		is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	perspective calculation where far plane is assumed to be at an infinite distance and the screen
				space Z is inverted
*****************************************************************************/
	static XRMat4 PerspectiveFloatDepth(
		Float32 width, Float32 height,
		Float32 nearPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		Float32 n2 = VERTTYPEMUL(2,nearPlane);

		XRMat4 result;
		if (bRotate)
		{
			result.f[0] = 0;	result.f[4]=VERTTYPEDIV(-n2,width);	result.f[8]=0;	result.f[12]=0;
			result.f[1] = VERTTYPEDIV(n2,height);	result.f[5]=0;	result.f[9]=0;	result.f[13]=0;
		}
		else
		{
			result.f[0] = VERTTYPEDIV(n2,width);	result.f[4]=0;	result.f[8]=0;	result.f[12]=0;
			result.f[1] = 0;	result.f[5]=VERTTYPEDIV(n2,height);	result.f[9]=0;	result.f[13]=0;
		}
		if (cs == D3D)
		{
			result.f[2] = 0;	result.f[6]=0;	result.f[10]=0;	result.f[14]=nearPlane;
		}
		else
		{
			result.f[2] = 0;	result.f[6]=0;	result.f[10]=(bRightHanded?(Float32)1:(Float32)-1);	result.f[14]=n2;
		}
		result.f[3] = (Float32)0;	result.f[7]=(Float32)0;	result.f[11]= (bRightHanded?(Float32)-1:(Float32)1);	result.f[15]=(Float32)0;

		return result;
	}

/*!***************************************************************************
 @Function		Perspective
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			farPlane	far clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRightHanded	handedness of coordinate system
 @Input			bRotate		is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	perspective calculation where field of view is used instead of near plane dimensions
*****************************************************************************/
	static XRMat4 PerspectiveFov(
		Float32 fovy, Float32 aspect,
		Float32 nearPlane, Float32 farPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		Float32 height = VERTTYPEMUL(VERTTYPEMUL(f2vt(2.0f),nearPlane),XRTAN(VERTTYPEMUL(fovy,f2vt(0.5f))));
		if (bRotate) return Perspective(height, VERTTYPEDIV(height,aspect), nearPlane, farPlane, cs, bRightHanded, bRotate);
		return Perspective(VERTTYPEMUL(height,aspect), height, nearPlane, farPlane, cs, bRightHanded, bRotate);
	}

/*!***************************************************************************
 @Function		Perspective
 @Input			fovy		angle of view (vertical)
 @Input			aspect		aspect ratio of view
 @Input			nearPlane	near clipping distance
 @Input			cs			cs which clipspace convention is being used
 @Input			bRightHanded	handedness of coordinate system
 @Input			bRotate		is the viewport in portrait or landscape mode
 @Returns		Perspective matrix
 @Description	perspective calculation where field of view is used instead of near plane dimensions
				and far plane is assumed to be at an infinite distance with inverted Z range
*****************************************************************************/
	static XRMat4 PerspectiveFovFloatDepth(
		Float32 fovy, Float32 aspect,
		Float32 nearPlane,
		const eClipspace cs,
		bool bRightHanded,
		bool bRotate = false)
	{
		Float32 height = VERTTYPEMUL(VERTTYPEMUL(2,nearPlane), XRTAN(VERTTYPEMUL(fovy,0.5)));
		if (bRotate) return PerspectiveFloatDepth(height, VERTTYPEDIV(height,aspect), nearPlane, cs, bRightHanded, bRotate);
		return PerspectiveFloatDepth(VERTTYPEMUL(height,aspect), height, nearPlane, cs, bRightHanded, bRotate);
	}
};

#endif /*__XRVECTOR_H__*/

/*****************************************************************************
End of file (XRVector.h)
*****************************************************************************/

