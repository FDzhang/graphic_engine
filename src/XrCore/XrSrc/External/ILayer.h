#ifndef __ILAYER_H__
#define __ILAYER_H__
#include "xrIntrinsic.h"
#include "IMaterial.h"
#include "IObject.h"

class ILayer : virtual public IObject
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
        /* [in] */ Float32 y)=0;

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
		/* [in] */ Float32 y)=0;

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

    virtual xr_state SetWidth(
        /* [in] */ Float32 width)=0;

    virtual xr_state SetHeight(
        /* [in] */ Float32 height)=0;

	virtual xr_state SetScale(
        /* [in] */ Float32 xs,
		/* [in] */ Float32 ys)=0;

    virtual xr_state SetEnable(
        /* [in] */ Boolean enable)=0;

    virtual xr_state SetBackColor(
        /* [in] */ UInt32 color)=0;

	virtual xr_state SetOpacity(
		/* [in] */ Float32 opacity)=0;

    virtual xr_state MasksToBound(
        /* [in] */ Boolean flag)=0;

    virtual xr_state SetAnchorPoint(
        /* [in] */ Float32 anchorX,
        /* [in] */ Float32 anchorY)=0;

    virtual xr_state Remove()=0;

	virtual xr_state Release()=0;

    virtual xr_state Detach()=0;

    virtual xr_state SetTransitionStyle(
    /* [in] */ UInt32 duration,
    /* [in] */ AnimationStyle style,
	/* [in] */ UInt32 type=AP_ALL)=0;

    virtual xr_state BringForward()=0;

    virtual xr_state SendBackward()=0;

    virtual xr_state SendTo(
        /* [in] */ Int32 toIndex,
        /* [in] */ Int32 flag)=0;

    virtual xr_state BringToFront()=0;

    virtual xr_state LayerSendToBack()=0;

	virtual Float32 GetWidth()=0;

    virtual Float32 GetHeight()=0;

    virtual Float32 GetX()=0;

    virtual Float32 GetY()=0;

	virtual Float32 GetZ()=0;

    virtual Float32 GetAbsoluteX()=0;

    virtual Float32 GetAbsoluteY()=0;

    virtual Boolean GetEnable()=0;

	virtual Int32 GetId()=0;

	virtual xr_state SetColor(
         /* [in] */ Float32 r,
		 /* [in] */ Float32 g,
		 /* [in] */ Float32 b)=0;

	virtual xr_state GetColor(
         /* [out] */ Float32* r,
		 /* [out] */ Float32* g,
		 /* [out] */ Float32* b)=0;

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */class IAProperty** ppIAProperty) = 0;

	virtual xr_state SetMaterialROI(
		/* [in] */ Region* pRoi)=0;

	virtual xr_state SetEventResponder(class IEventResponder* responder)=0;
	virtual	xr_state DivertEvent(Int32 RTNodeId)=0;
};

#endif  //__ILAYER_H__
