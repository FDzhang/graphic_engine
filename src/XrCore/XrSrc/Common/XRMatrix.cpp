#include <math.h>
#include <string.h>
#include "XRMatrix.h"

/****************************************************************************
** Constants
****************************************************************************/
static const XRMATRIXf	c_mIdentity = {
	{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	}
};

/****************************************************************************
** Functions
****************************************************************************/

/*!***************************************************************************
 @Function			XRMatrixIdentityF
 @Output			mOut	Set to identity
 @Description		Reset matrix to identity matrix.
*****************************************************************************/
void XRMatrixIdentityF(XRMATRIXf &mOut)
{
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


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
	const XRMATRIXf	&mB)
{
	XRMATRIXf mRet;

	/* Perform calculation on a dummy matrix (mRet) */
	mRet.f[ 0] = mA.f[ 0]*mB.f[ 0] + mA.f[ 1]*mB.f[ 4] + mA.f[ 2]*mB.f[ 8] + mA.f[ 3]*mB.f[12];
	mRet.f[ 1] = mA.f[ 0]*mB.f[ 1] + mA.f[ 1]*mB.f[ 5] + mA.f[ 2]*mB.f[ 9] + mA.f[ 3]*mB.f[13];
	mRet.f[ 2] = mA.f[ 0]*mB.f[ 2] + mA.f[ 1]*mB.f[ 6] + mA.f[ 2]*mB.f[10] + mA.f[ 3]*mB.f[14];
	mRet.f[ 3] = mA.f[ 0]*mB.f[ 3] + mA.f[ 1]*mB.f[ 7] + mA.f[ 2]*mB.f[11] + mA.f[ 3]*mB.f[15];

	mRet.f[ 4] = mA.f[ 4]*mB.f[ 0] + mA.f[ 5]*mB.f[ 4] + mA.f[ 6]*mB.f[ 8] + mA.f[ 7]*mB.f[12];
	mRet.f[ 5] = mA.f[ 4]*mB.f[ 1] + mA.f[ 5]*mB.f[ 5] + mA.f[ 6]*mB.f[ 9] + mA.f[ 7]*mB.f[13];
	mRet.f[ 6] = mA.f[ 4]*mB.f[ 2] + mA.f[ 5]*mB.f[ 6] + mA.f[ 6]*mB.f[10] + mA.f[ 7]*mB.f[14];
	mRet.f[ 7] = mA.f[ 4]*mB.f[ 3] + mA.f[ 5]*mB.f[ 7] + mA.f[ 6]*mB.f[11] + mA.f[ 7]*mB.f[15];

	mRet.f[ 8] = mA.f[ 8]*mB.f[ 0] + mA.f[ 9]*mB.f[ 4] + mA.f[10]*mB.f[ 8] + mA.f[11]*mB.f[12];
	mRet.f[ 9] = mA.f[ 8]*mB.f[ 1] + mA.f[ 9]*mB.f[ 5] + mA.f[10]*mB.f[ 9] + mA.f[11]*mB.f[13];
	mRet.f[10] = mA.f[ 8]*mB.f[ 2] + mA.f[ 9]*mB.f[ 6] + mA.f[10]*mB.f[10] + mA.f[11]*mB.f[14];
	mRet.f[11] = mA.f[ 8]*mB.f[ 3] + mA.f[ 9]*mB.f[ 7] + mA.f[10]*mB.f[11] + mA.f[11]*mB.f[15];

	mRet.f[12] = mA.f[12]*mB.f[ 0] + mA.f[13]*mB.f[ 4] + mA.f[14]*mB.f[ 8] + mA.f[15]*mB.f[12];
	mRet.f[13] = mA.f[12]*mB.f[ 1] + mA.f[13]*mB.f[ 5] + mA.f[14]*mB.f[ 9] + mA.f[15]*mB.f[13];
	mRet.f[14] = mA.f[12]*mB.f[ 2] + mA.f[13]*mB.f[ 6] + mA.f[14]*mB.f[10] + mA.f[15]*mB.f[14];
	mRet.f[15] = mA.f[12]*mB.f[ 3] + mA.f[13]*mB.f[ 7] + mA.f[14]*mB.f[11] + mA.f[15]*mB.f[15];

	/* Copy result to mOut */
	mOut = mRet;
}


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
	const float fX,
	const float fY,
	const float fZ)
{
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=fX;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;	mOut.f[13]=fY;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=fZ;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

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
	const float fZ)
{
	mOut.f[ 0]=fX;		mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=fY;		mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=fZ;		mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

/*!***************************************************************************
 @Function Name		XRMatrixRotationXF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an X rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationXF(
	XRMATRIXf	&mOut,
	const float fAngle)
{
	float		fCosine, fSine;

    /* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine	= (float)XRCOS(-fAngle);
    fSine	= (float)XRSIN(-fAngle);
#else
	fCosine	= XRCOS(fAngle);
    fSine	= XRSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to X Rotation */
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=fCosine;	mOut.f[ 9]=fSine;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=-fSine;	mOut.f[10]=fCosine;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

/*!***************************************************************************
 @Function Name		XRMatrixRotationYF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Y rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationYF(
	XRMATRIXf	&mOut,
	const float fAngle)
{
	float		fCosine, fSine;

	/* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine	= (float)XRCOS(-fAngle);
    fSine	= (float)XRSIN(-fAngle);
#else
	fCosine	= XRCOS(fAngle);
    fSine	= XRSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to Y Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=0.0f;	mOut.f[ 8]=-fSine;		mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;		mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;		mOut.f[13]=0.0f;
	mOut.f[ 2]=fSine;		mOut.f[ 6]=0.0f;	mOut.f[10]=fCosine;		mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;		mOut.f[15]=1.0f;
}

/*!***************************************************************************
 @Function Name		XRMatrixRotationZF
 @Output			mOut	Rotation matrix
 @Input				fAngle	Angle of the rotation
 @Description		Create an Z rotation matrix mOut.
*****************************************************************************/
void XRMatrixRotationZF(
	XRMATRIXf	&mOut,
	const float fAngle)
{
	float		fCosine, fSine;

	/* Precompute cos and sin */
#if defined(BUILD_DX9) || defined(BUILD_D3DM) || defined(BUILD_DX10)
	fCosine =	(float)XRCOS(-fAngle);
    fSine =		(float)XRSIN(-fAngle);
#else
	fCosine =	(float)XRCOS(fAngle);
    fSine =		(float)XRSIN(fAngle);
#endif

	/* Create the trigonometric matrix corresponding to Z Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=fSine;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=-fSine;		mOut.f[ 5]=fCosine;	mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;		mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}

/*!***************************************************************************
 @Function Name		XRMatrixTransposeF
 @Output			mOut	Transposed matrix
 @Input				mIn		Original matrix
 @Description		Compute the transpose matrix of mIn.
*****************************************************************************/
void XRMatrixTransposeF(
	XRMATRIXf			&mOut,
	const XRMATRIXf	&mIn)
{
	XRMATRIXf	mTmp;

	mTmp.f[ 0]=mIn.f[ 0];	mTmp.f[ 4]=mIn.f[ 1];	mTmp.f[ 8]=mIn.f[ 2];	mTmp.f[12]=mIn.f[ 3];
	mTmp.f[ 1]=mIn.f[ 4];	mTmp.f[ 5]=mIn.f[ 5];	mTmp.f[ 9]=mIn.f[ 6];	mTmp.f[13]=mIn.f[ 7];
	mTmp.f[ 2]=mIn.f[ 8];	mTmp.f[ 6]=mIn.f[ 9];	mTmp.f[10]=mIn.f[10];	mTmp.f[14]=mIn.f[11];
	mTmp.f[ 3]=mIn.f[12];	mTmp.f[ 7]=mIn.f[13];	mTmp.f[11]=mIn.f[14];	mTmp.f[15]=mIn.f[15];

	mOut = mTmp;
}

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
	const XRMATRIXf	&mIn)
{
	XRMATRIXf	mDummyMatrix;
	double		det_1;
	double		pos, neg, temp;

    /* Calculate the determinant of submatrix A and determine if the
       the matrix is singular as limited by the double precision
       floating-point data representation. */
    pos = neg = 0.0;
    temp =  mIn.f[ 0] * mIn.f[ 5] * mIn.f[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  mIn.f[ 4] * mIn.f[ 9] * mIn.f[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  mIn.f[ 8] * mIn.f[ 1] * mIn.f[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 8] * mIn.f[ 5] * mIn.f[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 4] * mIn.f[ 1] * mIn.f[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 0] * mIn.f[ 9] * mIn.f[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0) || (XRABS(det_1 / (pos - neg)) < 1.0e-15))
	{
        /* Matrix M has no inverse */
        return;
    }
    else
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0 / det_1;
        mDummyMatrix.f[ 0] =   ( mIn.f[ 5] * mIn.f[10] - mIn.f[ 9] * mIn.f[ 6] ) * (float)det_1;
        mDummyMatrix.f[ 1] = - ( mIn.f[ 1] * mIn.f[10] - mIn.f[ 9] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 2] =   ( mIn.f[ 1] * mIn.f[ 6] - mIn.f[ 5] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 4] = - ( mIn.f[ 4] * mIn.f[10] - mIn.f[ 8] * mIn.f[ 6] ) * (float)det_1;
        mDummyMatrix.f[ 5] =   ( mIn.f[ 0] * mIn.f[10] - mIn.f[ 8] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 6] = - ( mIn.f[ 0] * mIn.f[ 6] - mIn.f[ 4] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 8] =   ( mIn.f[ 4] * mIn.f[ 9] - mIn.f[ 8] * mIn.f[ 5] ) * (float)det_1;
        mDummyMatrix.f[ 9] = - ( mIn.f[ 0] * mIn.f[ 9] - mIn.f[ 8] * mIn.f[ 1] ) * (float)det_1;
        mDummyMatrix.f[10] =   ( mIn.f[ 0] * mIn.f[ 5] - mIn.f[ 4] * mIn.f[ 1] ) * (float)det_1;

        /* Calculate -C * inverse(A) */
        mDummyMatrix.f[12] = - ( mIn.f[12] * mDummyMatrix.f[ 0] + mIn.f[13] * mDummyMatrix.f[ 4] + mIn.f[14] * mDummyMatrix.f[ 8] );
        mDummyMatrix.f[13] = - ( mIn.f[12] * mDummyMatrix.f[ 1] + mIn.f[13] * mDummyMatrix.f[ 5] + mIn.f[14] * mDummyMatrix.f[ 9] );
        mDummyMatrix.f[14] = - ( mIn.f[12] * mDummyMatrix.f[ 2] + mIn.f[13] * mDummyMatrix.f[ 6] + mIn.f[14] * mDummyMatrix.f[10] );

        /* Fill in last row */
        mDummyMatrix.f[ 3] = 0.0f;
		mDummyMatrix.f[ 7] = 0.0f;
		mDummyMatrix.f[11] = 0.0f;
        mDummyMatrix.f[15] = 1.0f;
	}

   	/* Copy contents of dummy matrix in pfMatrix */
	mOut = mDummyMatrix;
}

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
	const XRMATRIXf	&mIn)
{
	XRMATRIXf		mTmp;
	float 			*ppfRows[4];
	float 			pfRes[4];
	float 			pfIn[20];
	int				i, j;

	for(i = 0; i < 4; ++i)
		ppfRows[i] = &pfIn[i * 5];

	/* Solve 4 sets of 4 linear equations */
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			ppfRows[j][0] = c_mIdentity.f[i + 4 * j];
			memcpy(&ppfRows[j][1], &mIn.f[j * 4], 4 * sizeof(float));
		}

		XRMatrixLinearEqSolveF(pfRes, (float**)ppfRows, 4);

		for(j = 0; j < 4; ++j)
		{
			mTmp.f[i + 4 * j] = pfRes[j];
		}
	}

	mOut = mTmp;
}

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
	const XRVECTOR3f	&vUp)
{
	XRVECTOR3f f, vUpActual, s, u;
	XRMATRIXf	t;

	f.x = vEye.x - vAt.x;
	f.y = vEye.y - vAt.y;
	f.z = vEye.z - vAt.z;

	XRMatrixVec3NormalizeF(f, f);
	XRMatrixVec3NormalizeF(vUpActual, vUp);
	XRMatrixVec3CrossProductF(s, f, vUpActual);
	XRMatrixVec3CrossProductF(u, s, f);

	mOut.f[ 0] = s.x;
	mOut.f[ 1] = u.x;
	mOut.f[ 2] = -f.x;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = s.y;
	mOut.f[ 5] = u.y;
	mOut.f[ 6] = -f.y;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = s.z;
	mOut.f[ 9] = u.z;
	mOut.f[10] = -f.z;
	mOut.f[11] = 0;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	XRMatrixTranslationF(t, -vEye.x, -vEye.y, -vEye.z);
	XRMatrixMultiplyF(mOut, t, mOut);
}

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
	const XRVECTOR3f	&vUp)
{
	XRVECTOR3f f, vUpActual, s, u;
	XRMATRIXf	t;

	f.x = vAt.x - vEye.x;
	f.y = vAt.y - vEye.y;
	f.z = vAt.z - vEye.z;

	XRMatrixVec3NormalizeF(f, f);
	XRMatrixVec3NormalizeF(vUpActual, vUp);
	XRMatrixVec3CrossProductF(s, f, vUpActual);
	XRMatrixVec3CrossProductF(u, s, f);

	mOut.f[ 0] = s.x;
	mOut.f[ 1] = u.x;
	mOut.f[ 2] = -f.x;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = s.y;
	mOut.f[ 5] = u.y;
	mOut.f[ 6] = -f.y;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = s.z;
	mOut.f[ 9] = u.z;
	mOut.f[10] = -f.z;
	mOut.f[11] = 0;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	XRMatrixTranslationF(t, -vEye.x, -vEye.y, -vEye.z);
	XRMatrixMultiplyF(mOut, t, mOut);
}

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
	const bool  bRotate)
{
	float f, n, fRealAspect;

	if (bRotate)
		fRealAspect = 1.0f / fAspect;
	else
		fRealAspect = fAspect;

	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / (float)XRTAN(fFOVy * 0.5f);
	n = 1.0f / (fFar - fNear);

	mOut.f[ 0] = f / fRealAspect;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = f;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = fFar * n;
	mOut.f[11] = 1;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = -fFar * fNear * n;
	mOut.f[15] = 0;

	if (bRotate)
	{
		XRMATRIXf mRotation, mTemp = mOut;
		XRMatrixRotationZF(mRotation, 90.0f*XR_PI/180.0f);
		XRMatrixMultiplyF(mOut, mTemp, mRotation);
	}
}

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
	const bool  bRotate)
{
	float f, n, fRealAspect;

	if (bRotate)
		fRealAspect = 1.0f / fAspect;
	else
		fRealAspect = fAspect;

	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / (float)XRTAN(fFOVy * 0.5f);
	n = 1.0f / (fNear - fFar);

	mOut.f[ 0] = f / fRealAspect;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = f;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = (fFar + fNear) * n;
	mOut.f[11] = -1;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = (2 * fFar * fNear) * n;
	mOut.f[15] = 0;

	if (bRotate)
	{
		XRMATRIXf mRotation, mTemp = mOut;
		XRMatrixRotationZF(mRotation, -90.0f*XR_PI/180.0f);
		XRMatrixMultiplyF(mOut, mTemp, mRotation);
	}
}

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
	const bool  bRotate)
{
	mOut.f[ 0] = 2 / w;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = 2 / h;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = 1 / (zf - zn);
	mOut.f[11] = zn / (zn - zf);

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	if (bRotate)
	{
		XRMATRIXf mRotation, mTemp = mOut;
		XRMatrixRotationZF(mRotation, -90.0f*XR_PI/180.0f);
		XRMatrixMultiplyF(mOut, mRotation, mTemp);
	}
}

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
	const bool  bRotate)
{
	mOut.f[ 0] = 2 / w;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = 2 / h;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = 1 / (zn - zf);
	mOut.f[11] = zn / (zn - zf);

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	if (bRotate)
	{
		XRMATRIXf mRotation, mTemp = mOut;
		XRMatrixRotationZF(mRotation, -90.0f*XR_PI/180.0f);
		XRMatrixMultiplyF(mOut, mRotation, mTemp);
	}
}

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
	const float	s)
{
	vOut.x = v1.x + s * (v2.x - v1.x);
	vOut.y = v1.y + s * (v2.y - v1.y);
	vOut.z = v1.z + s * (v2.z - v1.z);
}

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
	const XRVECTOR3f	&v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

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
	const XRVECTOR3f	&v2)
{
    XRVECTOR3f result;

	/* Perform calculation on a dummy VECTOR (result) */
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

	/* Copy result in pOut */
	vOut = result;
}

/*!***************************************************************************
 @Function			XRMatrixVec3NormalizeF
 @Output			vOut	Normalized vector
 @Input				vIn		Vector to normalize
 @Description		Normalizes the supplied vector.
*****************************************************************************/
void XRMatrixVec3NormalizeF(
	XRVECTOR3f		&vOut,
	const XRVECTOR3f	&vIn)
{
	float	f;
	double temp;

	temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
	temp = 1.0 / sqrt(temp);
	f = (float)temp;

	vOut.x = vIn.x * f;
	vOut.y = vIn.y * f;
	vOut.z = vIn.z * f;
}

/*!***************************************************************************
 @Function			XRMatrixVec3LengthF
 @Input				vIn		Vector to get the length of
 @Return			The length of the vector
  @Description		Gets the length of the supplied vector.
*****************************************************************************/
float XRMatrixVec3LengthF(
	const XRVECTOR3f	&vIn)
{
	double temp;

	temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
	return (float) sqrt(temp);
}

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
	float		** const pSrc,	// 2D array of floats. 4 Eq linear problem is 5x4 matrix, constants in first column.
	const int	nCnt)
{
	int		i, j, k;
	float	f;

#if 0
	/*
		Show the matrix in debug output
	*/
	_RPT1(_CRT_WARN, "LinearEqSolve(%d)\n", nCnt);
	for(i = 0; i < nCnt; ++i)
	{
		_RPT1(_CRT_WARN, "%.8f |", pSrc[i][0]);
		for(j = 1; j <= nCnt; ++j)
			_RPT1(_CRT_WARN, " %.8f", pSrc[i][j]);
		_RPT0(_CRT_WARN, "\n");
	}
#endif

	if(nCnt == 1)
	{
		XrAssert(pSrc[0][1] != 0);
		pRes[0] = pSrc[0][0] / pSrc[0][1];
		return;
	}

	// Loop backwards in an attempt avoid the need to swap rows
	i = nCnt;
	while(i)
	{
		--i;

		if(pSrc[i][nCnt] != 0)
		{
			// Row i can be used to zero the other rows; let's move it to the bottom
			if(i != (nCnt-1))
			{
				for(j = 0; j <= nCnt; ++j)
				{
					// Swap the two values
					f = pSrc[nCnt-1][j];
					pSrc[nCnt-1][j] = pSrc[i][j];
					pSrc[i][j] = f;
				}
			}

			// Now zero the last columns of the top rows
			for(j = 0; j < (nCnt-1); ++j)
			{
				XrAssert(pSrc[nCnt-1][nCnt] != 0);
				f = pSrc[j][nCnt] / pSrc[nCnt-1][nCnt];

				// No need to actually calculate a zero for the final column
				for(k = 0; k < nCnt; ++k)
				{
					pSrc[j][k] -= f * pSrc[nCnt-1][k];
				}
			}

			break;
		}
	}

	// Solve the top-left sub matrix
	XRMatrixLinearEqSolveF(pRes, pSrc, nCnt - 1);

	// Now calc the solution for the bottom row
	f = pSrc[nCnt-1][0];
	for(k = 1; k < nCnt; ++k)
	{
		f -= pSrc[nCnt-1][k] * pRes[k-1];
	}
	XrAssert(pSrc[nCnt-1][nCnt] != 0);
	f /= pSrc[nCnt-1][nCnt];
	pRes[nCnt-1] = f;

#if 0
	{
		float fCnt;

		/*
			Verify that the result is correct
		*/
		fCnt = 0;
		for(i = 1; i <= nCnt; ++i)
			fCnt += pSrc[nCnt-1][i] * pRes[i-1];

		XrAssert(abs(fCnt - pSrc[nCnt-1][0]) < 1e-3);
	}
#endif
}

void XRMatrixToHeadPitchRoll(XRMATRIXf &mat,float &headDegrees, float &pitchDegrees, float &rollDegrees)
{

    float thetaX = asinf(mat.f[6]);
    float thetaY = 0.0f;
    float thetaZ = 0.0f;

    if (thetaX < XR_PI)
    {
        if (thetaX > -XR_PI)
        {
            thetaZ = atan2f(-mat.f[4], mat.f[5]);
            thetaY = atan2f(-mat.f[2], mat.f[10]);
        }
        else
        {
            // Not a unique solution.
            thetaZ = -atan2f(mat.f[8], mat.f[0]);
            thetaY = 0.0f;
        }
    }
    else
    {
        // Not a unique solution.
        thetaZ = atan2f(mat.f[8], mat.f[0]);
        thetaY = 0.0f;
    }
	headDegrees = thetaY;
    pitchDegrees = thetaX;
    rollDegrees = thetaZ;

}

void XRMatrixFromHeadPitchRoll(XRMATRIXf &mOut, float headDegrees, float pitchDegrees, float rollDegrees)
{
    // Constructs a rotation matrix based on a Euler Transform.
    // We use the popular NASA standard airplane convention of 
    // heading-pitch-roll (i.e., RzRxRy).

    float cosH = cosf(headDegrees);
    float cosP = cosf(pitchDegrees);
    float cosR = cosf(rollDegrees);
    float sinH = sinf(headDegrees);
    float sinP = sinf(pitchDegrees);
    float sinR = sinf(rollDegrees);

    mOut.f[0] = cosR * cosH - sinR * sinP * sinH;
    mOut.f[1] = sinR * cosH + cosR * sinP * sinH;
    mOut.f[2] = -cosP * sinH;
	mOut.f[3] = 0.0;

    mOut.f[4] = -sinR * cosP;
    mOut.f[5] = cosR * cosP;
    mOut.f[6] = sinP;
	mOut.f[7] = 0.0;

    mOut.f[8] = cosR * sinH + sinR * sinP * cosH;
    mOut.f[9] = sinR * sinH - cosR * sinP * cosH;
    mOut.f[10] = cosP * cosH;
	mOut.f[11] = 0.0;

	mOut.f[12] = 0.0;
	mOut.f[13] = 0.0;
	mOut.f[14] = 0.0;
	mOut.f[15] = 1.0;
}

/*****************************************************************************
 End of file (XRMatrixF.cpp)
*****************************************************************************/

