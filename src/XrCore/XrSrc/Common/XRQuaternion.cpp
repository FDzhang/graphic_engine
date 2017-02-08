#include <math.h>
#include <string.h>
#include "XRQuaternion.h"

/****************************************************************************
** Functions
****************************************************************************/

/*!***************************************************************************
 @Function			XRQuaternionIdentityF
 @Output			qOut	Identity quaternion
 @Description		Sets the quaternion to (0, 0, 0, 1), the identity quaternion.
*****************************************************************************/
void XRQuaternionIdentity(XRQuaternion &qOut)
{
	qOut.x = 0;
	qOut.y = 0;
	qOut.z = 0;
	qOut.w = 1;
}

/*!***************************************************************************
 @Function			XRQuaternionRotationAxisF
 @Output			qOut	Rotation quaternion
 @Input				vAxis	Axis to rotate around
 @Input				fAngle	Angle to rotate
 @Description		Create quaternion corresponding to a rotation of fAngle
					radians around submitted vector.
*****************************************************************************/
void XRQuaternionRotationAxis(
	XRQuaternion		&qOut,
	const XRVECTOR3f	&vAxis,
	const float			fAngle)
{
	float	fSin, fCos;

	fSin = (float)XRSIN(fAngle * 0.5f);
	fCos = (float)XRCOS(fAngle * 0.5f);

	/* Create quaternion */
	qOut.x = vAxis.x * fSin;
	qOut.y = vAxis.y * fSin;
	qOut.z = vAxis.z * fSin;
	qOut.w = fCos;

	/* Normalise it */
	XRQuaternionNormalize(qOut);
}

/*!***************************************************************************
 @Function			XRQuaternionToAxisAngleF
 @Input				qIn		Quaternion to transform
 @Output			vAxis	Axis of rotation
 @Output			fAngle	Angle of rotation
 @Description		Convert a quaternion to an axis and angle. Expects a unit
					quaternion.
*****************************************************************************/
void XRQuaternionToAxisAngle(
	const XRQuaternion	&qIn,
	XRVECTOR3f			&vAxis,
	float					&fAngle)
{
	float	fCosAngle, fSinAngle;
	double	temp;

	/* Compute some values */
	fCosAngle	= qIn.w;
	temp		= 1.0f - fCosAngle*fCosAngle;
	fAngle		= (float)XRACOS(fCosAngle)*2.0f;
	fSinAngle	= (float)sqrt(temp);

	/* This is to avoid a division by zero */
	if ((float)fabs(fSinAngle)<0.0005f)
		fSinAngle = 1.0f;

	/* Get axis vector */
	vAxis.x = qIn.x / fSinAngle;
	vAxis.y = qIn.y / fSinAngle;
	vAxis.z = qIn.z / fSinAngle;
}

/*!***************************************************************************
 @Function			XRQuaternionSlerpF
 @Output			qOut	Result of the interpolation
 @Input				qA		First quaternion to interpolate from
 @Input				qB		Second quaternion to interpolate from
 @Input				t		Coefficient of interpolation
 @Description		Perform a Spherical Linear intERPolation between quaternion A
					and quaternion B at time t. t must be between 0.0f and 1.0f
*****************************************************************************/
void XRQuaternionSlerp(
	XRQuaternion			&qOut,
	const XRQuaternion	&qA,
	const XRQuaternion	&qB,
	const float				t)
{
	float		fCosine, fAngle, A, B;

	/* Parameter checking */
	if (t<0.0f || t>1.0f)
	{
		qOut.x = 0;
		qOut.y = 0;
		qOut.z = 0;
		qOut.w = 1;
		return;
	}

	/* Find sine of Angle between Quaternion A and B (dot product between quaternion A and B) */
	fCosine = qA.w*qB.w + qA.x*qB.x + qA.y*qB.y + qA.z*qB.z;

	if (fCosine < 0)
	{
		XRQuaternion qi;

		/*
			<http://www.magic-software.com/Documentation/Quaternions.pdf>

			"It is important to note that the quaternions q and -q represent
			the same rotation... while either quaternion will do, the
			interpolation methods require choosing one over the other.

			"Although q1 and -q1 represent the same rotation, the values of
			Slerp(t; q0, q1) and Slerp(t; q0,-q1) are not the same. It is
			customary to choose the sign... on q1 so that... the angle
			between q0 and q1 is acute. This choice avoids extra
			spinning caused by the interpolated rotations."
		*/
		qi.x = -qB.x;
		qi.y = -qB.y;
		qi.z = -qB.z;
		qi.w = -qB.w;

		XRQuaternionSlerp(qOut, qA, qi, t);
		return;
	}

	fCosine = XR_MIN(fCosine, 1.0f);
	fAngle = (float)XRACOS(fCosine);

	/* Avoid a division by zero */
	if (fAngle==0.0f)
	{
		qOut = qA;
		return;
	}

	/* Precompute some values */
	A = (float)(XRSIN((1.0f-t)*fAngle) / XRSIN(fAngle));
	B = (float)(XRSIN(t*fAngle) / XRSIN(fAngle));

	/* Compute resulting quaternion */
	qOut.x = A * qA.x + B * qB.x;
	qOut.y = A * qA.y + B * qB.y;
	qOut.z = A * qA.z + B * qB.z;
	qOut.w = A * qA.w + B * qB.w;

	/* Normalise result */
	XRQuaternionNormalize(qOut);
}

/*!***************************************************************************
 @Function			XRQuaternionNormalizeF
 @Modified			quat	Vector to normalize
 @Description		Normalize quaternion.
*****************************************************************************/
void XRQuaternionNormalize(XRQuaternion &quat)
{
	float	fMagnitude;
	double	temp;

	/* Compute quaternion magnitude */
	temp = quat.w*quat.w + quat.x*quat.x + quat.y*quat.y + quat.z*quat.z;
	fMagnitude = (float)sqrt(temp);

	/* Divide each quaternion component by this magnitude */
	if (fMagnitude!=0.0f)
	{
		fMagnitude = 1.0f / fMagnitude;
		quat.x *= fMagnitude;
		quat.y *= fMagnitude;
		quat.z *= fMagnitude;
		quat.w *= fMagnitude;
	}
}

/*!***************************************************************************
 @Function			XRRotationQuaternionF
 @Output			mOut	Resulting rotation matrix
 @Input				quat	Quaternion to transform
 @Description		Create rotation matrix from submitted quaternion.
					Assuming the quaternion is of the form [X Y Z W]:

						|       2     2									|
						| 1 - 2Y  - 2Z    2XY - 2ZW      2XZ + 2YW		 0	|
						|													|
						|                       2     2					|
					M = | 2XY + 2ZW       1 - 2X  - 2Z   2YZ - 2XW		 0	|
						|													|
						|                                      2     2		|
						| 2XZ - 2YW       2YZ + 2XW      1 - 2X  - 2Y	 0	|
						|													|
						|     0			   0			  0          1  |
*****************************************************************************/
void XRQuaternionToMatrix(
	XRMATRIXf				&mOut,
	XRQuaternion	&quat)
{
	typedef float (*p)[4];
	p r = (p)mOut.f;

	float* q = (float*)&quat;
	    /*  Matrix is
     *  | 1 - 2(y^2 + z^2)	2(xy + wz)			2(xz - wy)			0  |
     *  | 2(xy - wz)		1 - 2(x^2 + z^2)	2(yz + wx)			0  |
     *  | 2(xz + wy)		2(yz - wx)			1 - 2(x^2 + y^2)	0  |
     *  | 0					0					0					1  |
	*/
    float x2 = q[0] + q[0]; 
    float y2 = q[1] + q[1]; 
    float z2 = q[2] + q[2];
    float xx = q[0] * x2;
    float xy = q[0] * y2;
    float xz = q[0] * z2;
    float yy = q[1] * y2;
    float yz = q[1] * z2;
    float zz = q[2] * z2;
    float wx = q[3] * x2;
    float wy = q[3] * y2;
    float wz = q[3] * z2;

    r[0][0] = 1.0f - (yy + zz);
    r[0][1] = xy + wz;
    r[0][2] = xz - wy;
    r[0][3] = 0.0f;

    r[1][0] = xy - wz;
    r[1][1] = 1.0f - (xx + zz);
    r[1][2] = yz + wx;
    r[1][3] = 0.0f;

    r[2][0] = xz + wy;
    r[2][1] = yz - wx;
    r[2][2] = 1.0f - (xx + yy);
    r[2][3] = 0.0f;

    r[3][0] = 0.0f;
    r[3][1] = 0.0f;
    r[3][2] = 0.0f;
    r[3][3] = 1.0f;


}

void XRMatrixToQuaternion(XRQuaternion	&qOut, XRMATRIXf &mat)
{
	typedef float (*p)[4];
	p r = (p)mat.f;
	float* q = (float*)&qOut;

    float s = 0.0f;
    float trace = r[0][0] + r[1][1] + r[2][2];

    if (trace > 0.0f)
    {
        s = sqrtf(trace + 1.0f);
        q[3] = s * 0.5f;
        s = 0.5f / s;
        q[0] = (r[1][2] - r[2][1]) * s;
        q[1] = (r[2][0] - r[0][2]) * s;
        q[2] = (r[0][1] - r[1][0]) * s;
    }
    else
    {
        int nxt[3] = {1, 2, 0};
        int i = 0, j = 0, k = 0;

        if (r[1][1] > r[0][0])
            i = 1;

        if (r[2][2] > r[i][i])
            i = 2;

        j = nxt[i];
        k = nxt[j];
        s = sqrtf((r[i][i] - (r[j][j] + r[k][k])) + 1.0f);

        q[i] = s * 0.5f;
        s = 0.5f / s;
        q[3] = (r[j][k] - r[k][j]) * s;
        q[j] = (r[i][j] + r[j][i]) * s;
        q[k] = (r[i][k] + r[k][i]) * s;
    }
}

/*!***************************************************************************
 @Function			XRQuaternionMultiplyF
 @Output			qOut	Resulting quaternion
 @Input				qA		First quaternion to multiply
 @Input				qB		Second quaternion to multiply
 @Description		Multiply quaternion A with quaternion B and return the
					result in qOut.
*****************************************************************************/
void XRQuaternionMultiply(
	XRQuaternion			&qOut,
	const XRQuaternion	&qA,
	const XRQuaternion	&qB)
{
	XRVECTOR3f	CrossProduct;

	/* Compute scalar component */
	qOut.w = (qA.w*qB.w) - (qA.x*qB.x + qA.y*qB.y + qA.z*qB.z);

	/* Compute cross product */
	CrossProduct.x = qA.y*qB.z - qA.z*qB.y;
	CrossProduct.y = qA.z*qB.x - qA.x*qB.z;
	CrossProduct.z = qA.x*qB.y - qA.y*qB.x;

	/* Compute result vector */
	qOut.x = (qA.w * qB.x) + (qB.w * qA.x) + CrossProduct.x;
	qOut.y = (qA.w * qB.y) + (qB.w * qA.y) + CrossProduct.y;
	qOut.z = (qA.w * qB.z) + (qB.w * qA.z) + CrossProduct.z;

	/* Normalize resulting quaternion */
	XRQuaternionNormalize(qOut);
}

void XrQuaterniontoHeadPitchRoll(
	XRQuaternion			&quat,
	float &head,
	float &pitch,
	float &roll)
{
    XRMATRIX m;
	XRQuaternionToMatrix(m, quat);
	XRMatrixToHeadPitchRoll(m, head, pitch, roll);

}

void QuatZ(XRQuaternion &r, float radians)
{
    float cosa = cosf(radians * 0.5f);
    float sina = sinf(radians * 0.5f);

    r.x = 0.0f;
    r.y = 0.0f;
	r.z = sina;
    r.w = cosa;
}

void XrQuaternionFromHeadPitchRoll(
	XRQuaternion			&qOut,
	float head,
	float pitch,
	float roll)
{
    XRMATRIX m;
    XRMatrixFromHeadPitchRoll(m, head, pitch, roll);
    XRMatrixToQuaternion(qOut, m);
}