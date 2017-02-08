#ifndef __IRENDER_NODE_H__
#define __IRENDER_NODE_H__
#include "xrIntrinsic.h"

class IRenderNode
{
public:

	virtual Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ class IMaterial** ppMtl=0)=0;

	virtual xr_state ReleaseMaterial(
		/* [in] */ Int32 matId)=0;

	virtual xr_state ReleaseMesh(
		/* [in] */ Int32 meshId)=0;

    virtual Int32 CreateMesh(
        /* [in] */ ModelType type,
		/* [in] */ Float32 dx=0,
		/* [in] */ Float32 dy=0,
		/* [in] */ Float32 dz=0,
		/* [in] */ String name=0,
		/* [out] */ class IMesh** ppIMesh=0)=0;
		
	virtual Int32 LoadMesh(
		/* [out] */ IMesh** ppMesh,
		/* [in]  */ String meshName,
		/* [in]  */ Float32 scale) = 0;

	virtual Int32 CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId, class IMaterial** ppIMaterial=0)=0;

	virtual xr_state AddTouchEvent(TouchPackage* pPackage)=0;

    virtual xr_state SetClear(
		/* [in] */ Boolean colorFlag,
		/* [in] */ Boolean depthFlag)=0;

    virtual xr_state SetClearColor(
		/* [in] */ Float32 r,
		/* [in] */ Float32 g,
		/* [in] */ Float32 b,
		/* [in] */ Float32 a)=0;

    virtual Boolean GetClearDepth()=0;

	virtual xr_state SetEnable(
		/* [in] */ Boolean flag)=0;

	virtual xr_state SetRenderROI(
		/* [in] */ Region* reg)=0;

	virtual Region* GetRenderROI()=0;

	virtual Void* GetRealType() = 0;

};

#endif  //__IRENDER_NODE_H__
