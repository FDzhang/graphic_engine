#ifndef _XRQUATERNION_H_
#define _XRQUATERNION_H_

#include "XRMatrix.h"

/****************************************************************************
** Typedefs
****************************************************************************/
/*!***************************************************************************
 Floating point Quaternion
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
	float w;	/*!< w coordinate */
} XRQuaternion;
/*!***************************************************************************
 Fixed point Quaternion
*****************************************************************************/


/****************************************************************************
** Functions
****************************************************************************/

/*!***************************************************************************
 @Function			XRQuaternionIdentity
 @Output			qOut	Identity quaternion
 @Description		Sets the quaternion to (0, 0, 0, 1), the identity quaternion.
*****************************************************************************/
void XRQuaternionIdentity(
	XRQuaternion		&qOut);

/*!***************************************************************************
 @Function			XRQuaternionRotationAxis
 @Output			qOut	Rotation quaternion
 @Input				vAxis	Axis to rotate around
 @Input				fAngle	Angle to rotate
 @Description		Create quaternion corresponding to a rotation of fAngle
					radians around submitted vector.
*****************************************************************************/
void XRQuaternionRotationAxis(
	XRQuaternion		&qOut,
	const XRVECTOR3f	&vAxis,
	const float			fAngle);

/*!***************************************************************************
 @Function			XRQuaternionToAxisAngle
 @Input				qIn		Quaternion to transform
 @Output			vAxis	Axis of rotation
 @Output			fAngle	Angle of rotation
 @Description		Convert a quaternion to an axis and angle. Expects a unit
					quaternion.
*****************************************************************************/
void XRQuaternionToAxisAngle(
	const XRQuaternion	&qIn,
	XRVECTOR3f			&vAxis,
	float					&fAngle);

/*!***************************************************************************
 @Function			XRQuaternionSlerp
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
	const float				t);

/*!***************************************************************************
 @Function			XRQuaternionNormalize
 @Modified			quat	Vector to normalize
 @Description		Normalize quaternion.
*****************************************************************************/
void XRQuaternionNormalize(XRQuaternion &quat);


/*!***************************************************************************
 @Function			XRRotationQuaternion
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
	XRMATRIXf &mOut,
	XRQuaternion &quat);

void XRMatrixToQuaternion(
	XRQuaternion	&qOut,
	XRMATRIXf &mat);

/*!***************************************************************************
 @Function			XRQuaternionMultiply
 @Output			qOut	Resulting quaternion
 @Input				qA		First quaternion to multiply
 @Input				qB		Second quaternion to multiply
 @Description		Multiply quaternion A with quaternion B and return the
					result in qOut.
*****************************************************************************/
void XRQuaternionMultiply(
	XRQuaternion			&qOut,
	const XRQuaternion	&qA,
	const XRQuaternion	&qB);

void XrQuaterniontoHeadPitchRoll(
	XRQuaternion			&quat,
	float &head,
	float &pitch,
	float &roll
	);

void XrQuaternionFromHeadPitchRoll(
	XRQuaternion			&qOut,
	float head,
	float pitch,
	float roll
);

#endif
/*****************************************************************************
 End of file (XRQuaternion.h)
*****************************************************************************/

