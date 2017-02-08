#ifndef __IRENDERDELEGATE_H__
#define __IRENDERDELEGATE_H__
#include "xrIntrinsic.h"

class IRenderDelegate
{ 
public:
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const class XRMat4* pModelMatrix,
		/* [in] */ const class XRMat4* pViewMatrix,
		/* [in] */ const class XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject)=0; 


		virtual Void SetBatchIndex(UInt32 index) {}
};

class IProcessDelegate : public IRenderDelegate
{ 
public:

	virtual xr_state Init(
		/* [in] */ IMaterial* pMtl)=0;
	
	virtual xr_state DeInit()=0;

	virtual xr_state GetDivisionCount(
		/* [out] */ Int32* dx,
		/* [out] */ Int32* dy)=0; 

	virtual xr_state OnEvent(
		/* [in] */ Float32 param1,
		/* [in] */ Float32 param2,
		/* [in] */ Int32 type)=0; 

};

#endif  //__IRENDERDELEGATE_H__
