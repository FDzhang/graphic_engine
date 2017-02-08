#ifndef __PROCESSDELEGATE_H__
#define __PROCESSDELEGATE_H__

#include "../External/xrTypes.h"
#include "../External/IRenderDelegate.h"

class ProcessDelegate_Frost : public IProcessDelegate
{ 
public:

	virtual xr_state Init(IMaterial* pMtl);

	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ RenderPass* pPass,
		/* [in] */ class IObject* pIObject); 

	virtual xr_state GetDivisionCount(
		/* [out] */ Int32* dx,
		/* [out] */ Int32* dy); 

	virtual xr_state OnEvent(
		/* [in] */ Float32 param1,
		/* [in] */ Float32 param2,
		/* [in] */ Int32 type)
	{
		return XR_OK;
	}
	virtual xr_state DeInit();

private:
	Int32	m_dx;
	Int32	m_dy;
};

class ProcessDelegate_Ripple : public IProcessDelegate
{ 
public:
	virtual xr_state Init(IMaterial* pMtl);

	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ RenderPass* pPass,
		/* [in] */ class IObject* pIObject); 

	virtual xr_state GetDivisionCount(
		/* [out] */ Int32* dx,
		/* [out] */ Int32* dy); 

	virtual xr_state OnEvent(
		/* [in] */ Float32 param1,
		/* [in] */ Float32 param2,
		/* [in] */ Int32 type);

	virtual xr_state DeInit();

	Void RippleUpdate();

	Void RippleInit();
	Void InitRippleCoeff();

	Void Drop(Float32 x, Float32 y, Float32 weight);
private:
	Int32		m_dx;
	Int32		m_dy;
	Float32*	m_vertexdata;

	Float32*	rippleCoeff;
	Float32*	rippleSource;
	Float32*	rippleDest;

	Float32 texCoordFactorS;
    Float32 texCoordOffsetS;
    Float32 texCoordFactorT;
    Float32 texCoordOffsetT;

	Int32		m_width;
	Int32		m_height;

};

#endif  //__PROCESSDELEGATE_H__
