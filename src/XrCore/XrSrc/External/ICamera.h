#ifndef __ICAMERA_H__
#define __ICAMERA_H__
#include "xrIntrinsic.h"
 
class ICamera
{
public:

    virtual xr_state SetPosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

    virtual xr_state SetOrientation(
        /* [in] */ Float32 head,
        /* [in] */ Float32 pitch,
		/* [in] */ Float32 roll)=0;

	virtual Void SetPerspective(
		/* [in] */ Float32 fovx, 
		/* [in] */ Float32 aspect, 
		/* [in] */ Float32 znear, 
		/* [in] */ Float32 zfar)=0;

	virtual Void SetFOV(
		/* [in] */ Float32 fov)=0;

	virtual Void SetFOVDelta(
		/* [in] */ Float32 fov)=0;

	virtual Void SetCustomProjectionMatrix(
		/* [in] */ Float32* pMatrix,
		/* [in] */ Boolean transpose)=0;

	virtual Void SetOrthognal(
		/* [in] */ Float32 l, 
		/* [in] */ Float32 r, 
		/* [in] */ Float32 t, 
		/* [in] */ Float32 b, 
		/* [in] */ Float32 n, 
		/* [in] */ Float32 f)=0;

	virtual Void LookAt(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y, 
		/* [in] */ Float32 z)=0;

	virtual Void LockLookAt(
		/* [in] */ Boolean flag)=0;

	virtual Void RotateAround(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y)=0;

	virtual Void RotateAroundDelta(
		/* [in] */ Float32 dx, 
		/* [in] */ Float32 dy)=0;

	virtual Void MoveAround(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y)=0;

	virtual Void MoveAroundDelta(
		/* [in] */ Float32 dx, 
		/* [in] */ Float32 dy)=0;
	virtual void Set2DCamera(bool camera_flag)=0;

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */class IAProperty** ppIAProperty) = 0;
};

#endif  //__ICAMERA_H__
