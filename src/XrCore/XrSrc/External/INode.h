#ifndef __INode_H__
#define __INode_H__
#include "xrIntrinsic.h"
#include "IMaterial.h"
#include "IObject.h"

class INode : virtual public IObject
{
public:
    // Common Layer API
    //

    virtual xr_state SetX(
        /* [in] */ Float32 x)=0;

    virtual xr_state SetY(
        /* [in] */ Float32 y)=0;

	virtual xr_state SetZ(
	 /* [in] */ Float32 z)=0;

	virtual xr_state SetDX(
        /* [in] */ Float32 x)=0;

    virtual xr_state SetDY(
        /* [in] */ Float32 y)=0;

	virtual xr_state SetDZ(
	 /* [in] */ Float32 z)=0;

    virtual xr_state SetPosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
		/* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

	virtual xr_state RotateX(
        /* [in] */ Float32 rx)=0;

    virtual xr_state RotateY(
        /* [in] */ Float32 ry)=0;

	virtual xr_state RotateZ(
        /* [in] */ Float32 rz)=0;

	virtual xr_state RotateDX(
        /* [in] */ Float32 rx)=0;

    virtual xr_state RotateDY(
        /* [in] */ Float32 ry)=0;

	virtual xr_state RotateDZ(
        /* [in] */ Float32 rz)=0;

	virtual xr_state Rotate(
		/* [in] */ Float32 rx,
		/* [in] */ Float32 ry,
		/* [in] */ Float32 rz)=0;

	virtual xr_state SelfRotateX(
        /* [in] */ Float32 rx)=0;

    virtual xr_state SelfRotateY(
        /* [in] */ Float32 ry)=0;

	virtual xr_state SelfRotateZ(
        /* [in] */ Float32 rz)=0;

	virtual xr_state SelfRotateDX(
        /* [in] */ Float32 rx)=0;

    virtual xr_state SelfRotateDY(
        /* [in] */ Float32 ry)=0;

	virtual xr_state SelfRotateDZ(
        /* [in] */ Float32 rz)=0;

	virtual xr_state SetScale(
        /* [in] */ Float32 sx,
		/* [in] */ Float32 sy,
		/* [in] */ Float32 sz)=0;

	virtual xr_state SelfScale(
		/* [in] */ Float32 x,
		/* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

    virtual xr_state SetEnable(
        /* [in] */ Boolean flag)=0;

    virtual Boolean GetEnable()=0;

	virtual xr_state SetOpacity(
		/* [in] */ Float32 opacity)=0;

	virtual xr_state GetOpacity(
		/* [out] */ Float32* opacity)=0;

	virtual xr_state SetBrightness(
		/* [in] */ Float32 value)=0;

	virtual xr_state GetBrightness(
		/* [out] */ Float32* value)=0;

	virtual xr_state GetMesh(
		/* [out] */ class IMesh** ppImesh)=0;

	virtual xr_state GetMaterial(
		/* [out] */ class IMaterial** ppIMaterial)=0;

	virtual xr_state SetMesh(
		/* [in] */Int32 meshId)=0;

	virtual xr_state SetMaterial(
		/* [in] */ Int32 materialId)=0;

	//virtual xr_state GetMaterial(
	//	/* [out] */ IMaterial** ppImtl)=0;

	virtual xr_state SetDrawModeBits(
        /* [in] */ UInt32 bits)=0;

	virtual xr_state SetInstancing(
		/* [in] */ Float32* val,
        /* [in] */ UInt32 count)=0;

	virtual xr_state ClearDrawModeBits(
        /* [in] */ UInt32 bits)=0;

    virtual UInt32 GetDrawModeBits()=0;
	
	virtual xr_state ResetPosition()=0;

	virtual xr_state SetCustomTransform(
		/* [in] */ Float32* pMatrix,
		/* [in] */ Boolean transpose)=0;

    virtual xr_state SetTransitionStyle(
		/* [in] */ UInt32 duration,
		/* [in] */ AnimationStyle style,
		/* [in] */ UInt32 type)=0;

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */class IAProperty** ppIAProperty)=0;

    //virtual xr_state Remove()=0;

    //virtual xr_state Detach()=0;

    virtual Float32 GetX()=0;

    virtual Float32 GetY()=0;

	virtual Float32 GetZ()=0;

	virtual const class AABBox& GetBound() const = 0 ;

	virtual Int32 GetId()=0;
};

#endif  //__INode_H__
