#ifndef __IDEVICE_MANAGER_H__
#define __IDEVICE_MANAGER_H__
#include "xrIntrinsic.h"
 
class ISkeleton;
class ISkeletonAnimSeq;
class IMaterialEx;
class IVertexProgram;
class IFragmentProgram;
class IMaterial;

class IDeviceManager
{
public:
    //virtual xr_state Initialize()=0;
	//virtual Int32 CreateMaterial(Material materialType, String name)=0;

	virtual Int32 CreateStreamingTexture(
		/* [in] */ Int32 width,
		/* [in] */ Int32 height,
		/* [in] */ XRBufferFormat format,
		/* [in] */ class ITextureDelegate* pDelegate)=0;

	virtual Int32 CreateTexture(
		/* [in] */ Void* pData,
		/* [in] */ Int32 with,
		/* [in] */ Int32 height,
		/* [in] */ XRBufferFormat format,
		/* [in] */ UInt32 mode,
		/* [in] */ Int32 miplevel=6)=0;
	
	virtual xr_state ReleaseTexture(
		/* [in] */ Int32 id)=0;

	virtual Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ IMaterial** ppMtl) = 0;

	virtual Int32 CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat foramt, XRBufferFormat depth,
     /* [out] */ class IRenderTarget** ppIRenderTarget)=0;

	virtual xr_state UpdateTexture(Void* pData, CTexture* pTexture) = 0;

};

#endif  //__IDEVICE_MANAGER_H__
