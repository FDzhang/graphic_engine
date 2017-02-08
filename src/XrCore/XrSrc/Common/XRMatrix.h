#ifndef _XRMATRIX_H_
#define _XRMATRIX_H_

#include "../External/xrUtility.h"
#include "assert.h"
/****************************************************************************
** Defines
****************************************************************************/
#define MAT00 0
#define MAT01 1
#define MAT02 2
#define MAT03 3
#define MAT10 4
#define MAT11 5
#define MAT12 6
#define MAT13 7
#define MAT20 8
#define MAT21 9
#define MAT22 10
#define MAT23 11
#define MAT30 12
#define MAT31 13
#define MAT32 14
#define MAT33 15

/****************************************************************************
** Typedefs
****************************************************************************/
/*!***************************************************************************
 2D floating point vector
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
} XRVECTOR2f;

/*!***************************************************************************
 2D fixed point vector
*****************************************************************************/
typedef struct
{
	int x;	/*!< x coordinate */
	int y;	/*!< y coordinate */
} XRVECTOR2x;

/*!***************************************************************************
 3D floating point vector
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
} XRVECTOR3f;

/*!***************************************************************************
 3D fixed point vector
*****************************************************************************/
typedef struct
{
	int x;	/*!< x coordinate */
	int y;	/*!< y coordinate */
	int z;	/*!< z coordinate */
} XRVECTOR3x;

/*!***************************************************************************
 4D floating point vector
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
	float w;	/*!< w coordinate */
} XRVECTOR4f;

/*!***************************************************************************
 4D fixed point vector
*****************************************************************************/
typedef struct
{
	int x;	/*!< x coordinate */
	int y;	/*!< y coordinate */
	int z;	/*!< z coordinate */
	int w;	/*!< w coordinate */
} XRVECTOR4x;

/*!***************************************************************************
 4x4 floating point matrix
*****************************************************************************/

class XRMATRIXf
{
public:
    float* operator [] ( const int Row )
	{
		return &f[Row<<2];
	}
	float f[16];	/*!< Array of float */
};

/*!***************************************************************************
 4x4 fixed point matrix
*****************************************************************************/
class XRMATRIXx
{
public:
    int* operator [] ( const int Row )
	{
		return &f[Row<<2];
	}
	int f[16];
};

/*!***************************************************************************
 3x3 floating point matrix
*****************************************************************************/

class XRMATRIX3f
{
public:
    float* operator [] ( const int Row )
	{
		return &f[Row*3];
	}
	float f[9];	/*!< Array of float */
};

/*!***************************************************************************
 3x3 fixed point matrix
*****************************************************************************/
class XRMATRIX3x
{
public:
    int* operator [] ( const int Row )
	{
		return &f[Row*3];
	}
	int f[9];
};


/****************************************************************************
** Float or fixed
****************************************************************************/
#ifdef XR_FIXED_POINT_ENABLE
	typedef XRVECTOR2x		XRVECTOR2;
	typedef XRVECTOR3x		XRVECTOR3;
	typedef XRVECTOR4x		XRVECTOR4;
	typedef XRMATRIX3x		XRMATRIX3;
	typedef XRMATRIXx			XRMATRIX;
	#define XRMatrixIdentity					XRMatrixIdentityX
	#define XRMatrixMultiply					XRMatrixMultiplyX
	#define XRMatrixTranslation				XRMatrixTranslationX
	#define XRMatrixScaling					XRMatrixScalingX
	#define XRMatrixRotationX					XRMatrixRotationXX
	#define XRMatrixRotationY					XRMatrixRotationYX
	#define XRMatrixRotationZ					XRMatrixRotationZX
	#define XRMatrixTranspose					XRMatrixTransposeX
	#define XRMatrixInverse					XRMatrixInverseX
	#define XRMatrixInverseEx					XRMatrixInverseExX
	#define XRMatrixLookAtLH					XRMatrixLookAtLHX
	#define XRMatrixLookAtRH					XRMatrixLookAtRHX
	#define XRMatrixPerspectiveFovLH			XRMatrixPerspectiveFovLHX
	#define XRMatrixPerspectiveFovRH			XRMatrixPerspectiveFovRHX
	#define XRMatrixOrthoLH					XRMatrixOrthoLHX
	#define XRMatrixOrthoRH					XRMatrixOrthoRHX
	#define XRMatrixVec3Lerp					XRMatrixVec3LerpX
	#define XRMatrixVec3DotProduct			XRMatrixVec3DotProductX
	#define XRMatrixVec3CrossProduct			XRMatrixVec3CrossProductX
	#define XRMatrixVec3Normalize				XRMatrixVec3NormalizeX
	#define XRMatrixVec3Length				XRMatrixVec3LengthX
	#define XRMatrixLinearEqSolve				XRMatrixLinearEqSolveX
#else
	typedef XRVECTOR2f		XRVECTOR2;
	typedef XRVECTOR3f		XRVECTOR3;
	typedef XRVECTOR4f		XRVECTOR4;
	typedef XRMATRIX3f		XRMATRIX3;
	typedef XRMATRIXf			XRMATRIX;
	#define XRMatrixIdentity					XRMatrixIdentityF
	#define XRMatrixMultiply					XRMatrixMultiplyF
	#define XRMatrixTranslation				XRMatrixTranslationF
	#define XRMatrixScaling					XRMatrixScalingF
	#define XRMatrixRotationX					XRMatrixRotationXF
	#define XRMatrixRotationY					XRMatrixRotationYF
	#define XRMatrixRotationZ					XRMatrixRotationZF
	#define XRMatrixTranspose					XRMatrixTransposeF
	#define XRMatrixInverse					XRMatrixInverseF
	#define XRMatrixInverseEx					XRMatrixInverseExF
	#define XRMatrixLookAtLH					XRMatrixLookAtLHF
	#define XRMatrixLookAtRH					XRMatrixLookAtRHF
	#define XRMatrixPerspectiveFovLH			XRMatrixPerspectiveFovLHF
	#define XRMatrixPerspectiveFovRH			XRMatrixPerspectiveFovRHF
	#define XRMatrixOrthoLH					XRMatrixOrthoLHF
	#define XRMatrixOrthoRH					XRMatrixOrthoRHF
	#define XRMatrixVec3Lerp					XRMatrixVec3LerpF
	#define XRMatrixVec3DotProduct			XRMatrixVec3DotProductF
	#define XRMatrixVec3CrossProduct			XRMatrixVec3CrossProductF
	#define XRMatrixVec3Normalize				XRMatrixVec3NormalizeF
	#define XRMatrixVec3Length				XRMatrixVec3LengthF
	#define XRMatrixLinearEqSolve				XRMatrixLinearEqSolveF
#endif

/****************************************************************************
** Functions
****************************************************************************/

/*!***************************************************************************
 @Function			XRMatrixIdentityF
 @Output			mOut	Set to identity
 @Description		Reset matrix to identity matrix.
*****************************************************************************/
void XRMatrixIdentityF(XRMATRIXf &mOut);

/*!***************************************************************************
 @Function			XRMatrixIdentityX
 @Output			mOut	Set to identity
 @Description		Reset matrix to identity matrix.
*****************************************************************************/
void XRMatrixIdentityX(XRMATRIXx &mOut);

/*!***************************************************************************
 @Function			XRMatrixMultiplyF
 @Output			mOut	Result of mA x mB
 @Input				mA		First operand
 @Input				mB		Second operand
 @Description		Multiply mA by mB and assign the result to mOut
					(mOut = p1 * p2). A copy of the result matrix is done in
					the function because mOut can be a parameter mA or mB.
*****************************************************************************/
void XRMatrixMultiplyF(
	XRMATRIXf			&mOut,
	const XRMATRIXf	&mA,
	const XRMATRIXf	&mB);
/*!***************************************************************************
 @Function			XRMatrixMultiplyX
 @Output			mOut	Result of mA x mB
 @Input				mA		First operand
 @Input				mB		Second operand
 @Description		Multiply mA by mB and assign the result to mOut
					(mOut = p1 * p2). A copy of the result matrix is done in
					the function because mOut can be a parameter mA or mB.
					The fixed-point shift could be performed after adding
					all four intermediate results together however this might
					cause some overflow issues.
*****************************************************************************/
void XRMatrixMultiplyX(
	XRMATRIXx			&mOut,
	const XRMATRIXx	&mA,
	const XRMATRIXx	&mB);

/*!***************************************************************************
 @Function Name		XRMatrixTranslationF
 @Output			mOut	Translation matrix
 @Input				fX		X component of the translation
 @Input				fY		Y component of the translation
 @Input				fZ		Z component of the translation
 @Description		Build a transaltion matrix mOut using fX, fY and fZ.
*****************************************************************************/
void XRMatrixTranslationF(
	XRMATRIXf	&mOut,
	const float	fX,
	const float	fY,
	const float	fZ);
/*!***************************************************************************
 @Function Name		XRMatrixTranslationX
 @Output			mOut	Translation matrix
 @Input				fX		X component of the translation
 @Input				fY		Y component of the translation
 @Input				fZ		Z component of the translation
 @Description		Build a transaltion matrix mOut using fX, fY and fZ.
*****************************************************************************/
void XRMatrixTranslationX(
	XRMATRIXx	&mOut,
	const int	fX,
	const int	fY,
	const int	fZ);

/*!***************************************************************************
 @Function Name		XRMatrixScalingF
 @Output			mOut	Scale matrix
 @Input				fX		X component of the scaling
 @Input				fY		Y component of the scaling
 @Input				fZ		Z component of the scaling
 @Description		Build a scale matrix mOut using fX, fY and fZ.
*****************************************************************************/
void XRMatrixScalingF(
	XRMATRIXf	&mOut,
	const float fX,
	const float fY,
	const float fZ);

/*!***************************************************************************
 @Function Name		XRMatrixScalingX
 @Output			mOut	Scale matrix
 @Input				fX		X component of the scaling
 @Input				fY		Y component of the scaling
 @Input				fZ		Z component of the scaling
 @Description		Build a scale matrix mOut using fX, fY and fZ.
*****************************************************************************/
void XRMatrixScalingX(
	XRMATRIXx	&mOut,
	const int	fX,
	const int	fY,
	const int	fZ);

/*!***************************************************************************
 @Function Name		XRMatrixRotationXF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an X rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationXF(
	XRMATRIXf	&mOut,
	const float fAngle);

/*!***************************************************************************
 @Function Name		XRMatrixRotationXX
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an X rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationXX(
	XRMATRIXx	&mOut,
	const int	fAngle);

/*!***************************************************************************
 @Function Name		XRMatrixRotationYF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Y rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationYF(
	XRMATRIXf	&mOut,
	const float fAngle);

/*!***************************************************************************
 @Function Name		XRMatrixRotationYX
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Y rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationYX(
	XRMATRIXx	&mOut,
	const int	fAngle);

/*!***************************************************************************
 @Function Name		XRMatrixRotationZF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Z rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationZF(
	XRMATRIXf	&mOut,
	const float fAngle);
/*!***************************************************************************
 @Function Name		XRMatrixRotationZX
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Z rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationZX(
	XRMATRIXx	&mOut,
	const int	fAngle);

/*!***************************************************************************
 @Function Name		XRMatrixTransposeF
 @Output			mOut	Transposed matrix
 @Input				mIn		Original matrix
 @Description		Compute the transpose matrix of mIn.
*****************************************************************************/
void XRMatrixTransposeF(
	XRMATRIXf			&mOut,
	const XRMATRIXf	&mIn);
/*!***************************************************************************
 @Function Name		XRMatrixTransposeX
 @Output			mOut	Transposed matrix
 @Input				mIn		Original matrix
 @Description		Compute the transpose matrix of mIn.
*****************************************************************************/
void XRMatrixTransposeX(
	XRMATRIXx			&mOut,
	const XRMATRIXx	&mIn);

/*!***************************************************************************
 @Function			XRMatrixInverseF
 @Output			mOut	Inversed matrix
 @Input				mIn		Original matrix
 @Description		Compute the inverse matrix of mIn.
					The matrix must be of the form :
					A 0
					C 1
					Where A is a 3x3 matrix and C is a 1x3 matrix.
*****************************************************************************/
void XRMatrixInverseF(
	XRMATRIXf			&mOut,
	const XRMATRIXf	&mIn);
/*!***************************************************************************
 @Function			XRMatrixInverseX
 @Output			mOut	Inversed matrix
 @Input				mIn		Original matrix
 @Description		Compute the inverse matrix of mIn.
					The matrix must be of the form :
					A 0
					C 1
					Where A is a 3x3 matrix and C is a 1x3 matrix.
*****************************************************************************/
void XRMatrixInverseX(
	XRMATRIXx			&mOut,
	const XRMATRIXx	&mIn);

/*!***************************************************************************
 @Function			XRMatrixInverseExF
 @Output			mOut	Inversed matrix
 @Input				mIn		Original matrix
 @Description		Compute the inverse matrix of mIn.
					Uses a linear equation solver and the knowledge that M.M^-1=I.
					Use this fn to calculate the inverse of matrices that
					XRMatrixInverse() cannot.
*****************************************************************************/
void XRMatrixInverseExF(
	XRMATRIXf			&mOut,
	const XRMATRIXf	&mIn);
/*!***************************************************************************
 @Function			XRMatrixInverseExX
 @Output			mOut	Inversed matrix
 @Input				mIn		Original matrix
 @Description		Compute the inverse matrix of mIn.
					Uses a linear equation solver and the knowledge that M.M^-1=I.
					Use this fn to calculate the inverse of matrices that
					XRMatrixInverse() cannot.
*****************************************************************************/
void XRMatrixInverseExX(
	XRMATRIXx			&mOut,
	const XRMATRIXx	&mIn);

/*!***************************************************************************
 @Function			XRMatrixLookAtLHF
 @Output			mOut	Look-at view matrix
 @Input				vEye	Position of the camera
 @Input				vAt		Point the camera is looking at
 @Input				vUp		Up direction for the camera
 @Description		Create a look-at view matrix.
*****************************************************************************/
void XRMatrixLookAtLHF(
	XRMATRIXf			&mOut,
	const XRVECTOR3f	&vEye,
	const XRVECTOR3f	&vAt,
	const XRVECTOR3f	&vUp);
/*!***************************************************************************
 @Function			XRMatrixLookAtLHX
 @Output			mOut	Look-at view matrix
 @Input				vEye	Position of the camera
 @Input				vAt		Point the camera is looking at
 @Input				vUp		Up direction for the camera
 @Description		Create a look-at view matrix.
*****************************************************************************/
void XRMatrixLookAtLHX(
	XRMATRIXx			&mOut,
	const XRVECTOR3x	&vEye,
	const XRVECTOR3x	&vAt,
	const XRVECTOR3x	&vUp);

/*!***************************************************************************
 @Function			XRMatrixLookAtRHF
 @Output			mOut	Look-at view matrix
 @Input				vEye	Position of the camera
 @Input				vAt		Point the camera is looking at
 @Input				vUp		Up direction for the camera
 @Description		Create a look-at view matrix.
*****************************************************************************/
void XRMatrixLookAtRHF(
	XRMATRIXf			&mOut,
	const XRVECTOR3f	&vEye,
	const XRVECTOR3f	&vAt,
	const XRVECTOR3f	&vUp);
/*!***************************************************************************
 @Function			XRMatrixLookAtRHX
 @Output			mOut	Look-at view matrix
 @Input				vEye	Position of the camera
 @Input				vAt		Point the camera is looking at
 @Input				vUp		Up direction for the camera
 @Description		Create a look-at view matrix.
*****************************************************************************/
void XRMatrixLookAtRHX(
	XRMATRIXx			&mOut,
	const XRVECTOR3x	&vEye,
	const XRVECTOR3x	&vAt,
	const XRVECTOR3x	&vUp);

/*!***************************************************************************
 @Function		XRMatrixPerspectiveFovLHF
 @Output		mOut		Perspective matrix
 @Input			fFOVy		Field of view
 @Input			fAspect		Aspect ratio
 @Input			fNear		Near clipping distance
 @Input			fFar		Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create a perspective matrix.
*****************************************************************************/
void XRMatrixPerspectiveFovLHF(
	XRMATRIXf	&mOut,
	const float	fFOVy,
	const float	fAspect,
	const float	fNear,
	const float	fFar,
	const bool  bRotate = false);
/*!***************************************************************************
 @Function		XRMatrixPerspectiveFovLHX
 @Output		mOut		Perspective matrix
 @Input			fFOVy		Field of view
 @Input			fAspect		Aspect ratio
 @Input			fNear		Near clipping distance
 @Input			fFar		Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create a perspective matrix.
*****************************************************************************/
void XRMatrixPerspectiveFovLHX(
	XRMATRIXx	&mOut,
	const int	fFOVy,
	const int	fAspect,
	const int	fNear,
	const int	fFar,
	const bool  bRotate = false);

/*!***************************************************************************
 @Function		XRMatrixPerspectiveFovRHF
 @Output		mOut		Perspective matrix
 @Input			fFOVy		Field of view
 @Input			fAspect		Aspect ratio
 @Input			fNear		Near clipping distance
 @Input			fFar		Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create a perspective matrix.
*****************************************************************************/
void XRMatrixPerspectiveFovRHF(
	XRMATRIXf	&mOut,
	const float	fFOVy,
	const float	fAspect,
	const float	fNear,
	const float	fFar,
	const bool  bRotate = false);
/*!***************************************************************************
 @Function		XRMatrixPerspectiveFovRHX
 @Output		mOut		Perspective matrix
 @Input			fFOVy		Field of view
 @Input			fAspect		Aspect ratio
 @Input			fNear		Near clipping distance
 @Input			fFar		Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create a perspective matrix.
*****************************************************************************/
void XRMatrixPerspectiveFovRHX(
	XRMATRIXx	&mOut,
	const int	fFOVy,
	const int	fAspect,
	const int	fNear,
	const int	fFar,
	const bool  bRotate = false);

/*!***************************************************************************
 @Function		XRMatrixOrthoLHF
 @Output		mOut		Orthographic matrix
 @Input			w			Width of the screen
 @Input			h			Height of the screen
 @Input			zn			Near clipping distance
 @Input			zf			Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create an orthographic matrix.
*****************************************************************************/
void XRMatrixOrthoLHF(
	XRMATRIXf	&mOut,
	const float w,
	const float h,
	const float zn,
	const float zf,
	const bool  bRotate = false);
/*!***************************************************************************
 @Function		XRMatrixOrthoLHX
 @Output		mOut		Orthographic matrix
 @Input			w			Width of the screen
 @Input			h			Height of the screen
 @Input			zn			Near clipping distance
 @Input			zf			Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create an orthographic matrix.
*****************************************************************************/
void XRMatrixOrthoLHX(
	XRMATRIXx	&mOut,
	const int	w,
	const int	h,
	const int	zn,
	const int	zf,
	const bool  bRotate = false);

/*!***************************************************************************
 @Function		XRMatrixOrthoRHF
 @Output		mOut		Orthographic matrix
 @Input			w			Width of the screen
 @Input			h			Height of the screen
 @Input			zn			Near clipping distance
 @Input			zf			Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create an orthographic matrix.
*****************************************************************************/
void XRMatrixOrthoRHF(
	XRMATRIXf	&mOut,
	const float w,
	const float h,
	const float zn,
	const float zf,
	const bool  bRotate = false);
/*!***************************************************************************
 @Function		XRMatrixOrthoRHX
 @Output		mOut		Orthographic matrix
 @Input			w			Width of the screen
 @Input			h			Height of the screen
 @Input			zn			Near clipping distance
 @Input			zf			Far clipping distance
 @Input			bRotate		Should we rotate it ? (for upright screens)
 @Description	Create an orthographic matrix.
*****************************************************************************/
void XRMatrixOrthoRHX(
	XRMATRIXx	&mOut,
	const int	w,
	const int	h,
	const int	zn,
	const int	zf,
	const bool  bRotate = false);

/*!***************************************************************************
 @Function			XRMatrixVec3LerpF
 @Output			vOut	Result of the interpolation
 @Input				v1		First vector to interpolate from
 @Input				v2		Second vector to interpolate form
 @Input				s		Coefficient of interpolation
 @Description		This function performs the linear interpolation based on
					the following formula: V1 + s(V2-V1).
*****************************************************************************/
void XRMatrixVec3LerpF(
	XRVECTOR3f		&vOut,
	const XRVECTOR3f	&v1,
	const XRVECTOR3f	&v2,
	const float			s);
/*!***************************************************************************
 @Function			XRMatrixVec3LerpX
 @Output			vOut	Result of the interpolation
 @Input				v1		First vector to interpolate from
 @Input				v2		Second vector to interpolate form
 @Input				s		Coefficient of interpolation
 @Description		This function performs the linear interpolation based on
					the following formula: V1 + s(V2-V1).
*****************************************************************************/
void XRMatrixVec3LerpX(
	XRVECTOR3x		&vOut,
	const XRVECTOR3x	&v1,
	const XRVECTOR3x	&v2,
	const int			s);

/*!***************************************************************************
 @Function			XRMatrixVec3DotProductF
 @Input				v1		First vector
 @Input				v2		Second vector
 @Return			Dot product of the two vectors.
 @Description		This function performs the dot product of the two
					supplied vectors.
*****************************************************************************/
float XRMatrixVec3DotProductF(
	const XRVECTOR3f	&v1,
	const XRVECTOR3f	&v2);
/*!***************************************************************************
 @Function			XRMatrixVec3DotProductX
 @Input				v1		First vector
 @Input				v2		Second vector
 @Return			Dot product of the two vectors.
 @Description		This function performs the dot product of the two
					supplied vectors.
					A single >> 16 shift could be applied to the final accumulated
					result however this runs the risk of overflow between the
					results of the intermediate additions.
*****************************************************************************/
int XRMatrixVec3DotProductX(
	const XRVECTOR3x	&v1,
	const XRVECTOR3x	&v2);

/*!***************************************************************************
 @Function			XRMatrixVec3CrossProductF
 @Output			vOut	Cross product of the two vectors
 @Input				v1		First vector
 @Input				v2		Second vector
 @Description		This function performs the cross product of the two
					supplied vectors.
*****************************************************************************/
void XRMatrixVec3CrossProductF(
	XRVECTOR3f		&vOut,
	const XRVECTOR3f	&v1,
	const XRVECTOR3f	&v2);
/*!***************************************************************************
 @Function			XRMatrixVec3CrossProductX
 @Output			vOut	Cross product of the two vectors
 @Input				v1		First vector
 @Input				v2		Second vector
 @Description		This function performs the cross product of the two
					supplied vectors.
*****************************************************************************/
void XRMatrixVec3CrossProductX(
	XRVECTOR3x		&vOut,
	const XRVECTOR3x	&v1,
	const XRVECTOR3x	&v2);

/*!***************************************************************************
 @Function			XRMatrixVec3NormalizeF
 @Output			vOut	Normalized vector
 @Input				vIn		Vector to normalize
 @Description		Normalizes the supplied vector.
*****************************************************************************/
void XRMatrixVec3NormalizeF(
	XRVECTOR3f		&vOut,
	const XRVECTOR3f	&vIn);
/*!***************************************************************************
 @Function			XRMatrixVec3NormalizeX
 @Output			vOut	Normalized vector
 @Input				vIn		Vector to normalize
 @Description		Normalizes the supplied vector.
					The square root function is currently still performed
					in floating-point.
					Original vector is scaled down prior to be normalized in
					order to avoid overflow issues.
*****************************************************************************/
void XRMatrixVec3NormalizeX(
	XRVECTOR3x		&vOut,
	const XRVECTOR3x	&vIn);
/*!***************************************************************************
 @Function			XRMatrixVec3LengthF
 @Input				vIn		Vector to get the length of
 @Return			The length of the vector
  @Description		Gets the length of the supplied vector.
*****************************************************************************/
float XRMatrixVec3LengthF(
	const XRVECTOR3f	&vIn);
/*!***************************************************************************
 @Function			XRMatrixVec3LengthX
 @Input				vIn		Vector to get the length of
 @Return			The length of the vector
 @Description		Gets the length of the supplied vector
*****************************************************************************/
int XRMatrixVec3LengthX(
	const XRVECTOR3x	&vIn);
/*!***************************************************************************
 @Function			XRMatrixLinearEqSolveF
 @Input				pSrc	2D array of floats. 4 Eq linear problem is 5x4
							matrix, constants in first column
 @Input				nCnt	Number of equations to solve
 @Output			pRes	Result
 @Description		Solves 'nCnt' simultaneous equations of 'nCnt' variables.
					pRes should be an array large enough to contain the
					results: the values of the 'nCnt' variables.
					This fn recursively uses Gaussian Elimination.
*****************************************************************************/

void XRMatrixLinearEqSolveF(
	float		* const pRes,
	float		** const pSrc,
	const int	nCnt);
/*!***************************************************************************
 @Function			XRMatrixLinearEqSolveX
 @Input				pSrc	2D array of floats. 4 Eq linear problem is 5x4
							matrix, constants in first column
 @Input				nCnt	Number of equations to solve
 @Output			pRes	Result
 @Description		Solves 'nCnt' simultaneous equations of 'nCnt' variables.
					pRes should be an array large enough to contain the
					results: the values of the 'nCnt' variables.
					This fn recursively uses Gaussian Elimination.
*****************************************************************************/
void XRMatrixLinearEqSolveX(
	int			* const pRes,
	int			** const pSrc,
	const int	nCnt);

void XRMatrixToHeadPitchRoll(XRMATRIXf &mat,float &headDegrees, float &pitchDegrees, float &rollDegrees);
void XRMatrixFromHeadPitchRoll(XRMATRIXf &mOut, float headDegrees, float pitchDegrees, float rollDegrees);

#endif

/*****************************************************************************
 End of file (XRMatrix.h)
*****************************************************************************/

