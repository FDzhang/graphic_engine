#ifndef __IMESH_H__
#define __IMESH_H__
#include "xrIntrinsic.h"
#include "IMaterial.h"
#include "IObject.h"

class IMesh : public IObject
{
public:
    // Common Layer API
    //
	//virtual Int32 GetId()=0;

	virtual xr_state SetupVB(
		/* [in] */ Void* vertexData,
		/* [in] */ XRVertexLayout layout,
		/* [in] */ Int32 count,
		/* [in] */ XRBufferUsage usage)=0;

	virtual xr_state SetupIB(
		/* [in] */ Void* indexData,
		/* [in] */ Int32 size,
		/* [in] */ XRBufferUsage usage)=0;

	virtual xr_state GenPrimitive(
		/* [in] */ Float32 xs, 
		/* [in] */ Float32 ys, 
		/* [in] */ Float32 zs, 
		/* [in] */ ModelType type,
		/* [in] */ Region* roi=0)=0;

	virtual xr_state LockData(
		/* [out] */ Float32** ppData,
		/* [out] */ XRVertexLayout* format,
		/* [out] */ Int32* vertexCount)=0;

	virtual xr_state LoadFromFile(
		/* [in] */ String name,
		/* [in] */ Float32 scale=1.0,
		/* [in] */ Boolean reserve=FALSE)=0;

	virtual xr_state UnLockData()=0;

	virtual xr_state LoadVertexFromArray(
		/* [in] */ Float32* pData,
		/* [in] */ XRVertexLayout format,
		/* [in] */ Int32 count)=0;

	virtual xr_state LoadIndexFromArray(
		/* [in] */ UInt16* pIndex,
		/* [in] */ Int32 count)=0;
	virtual unsigned char  GetEnable()=0;
	virtual xr_state SetEnable(unsigned char enable)=0;
	virtual void SetRenderPlot(unsigned char flag)=0;
	virtual unsigned char GetRenderPlot(void)=0;
	
	virtual xr_state UpdateVertexNum(Int32 vertex_count)=0;
};

#endif  //__IMESH_H__
