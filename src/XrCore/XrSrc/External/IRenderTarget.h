#ifndef __IXRENDERTARGET_H__
#define __IXRENDERTARGET_H__

#include "xrIntrinsic.h"

class IRenderTarget
{
public:
	virtual Void GetSize(
		/* [out] */ Int32* width, 
		/* [out] */ Int32* height)=0;

	virtual Int32 GetId()=0;

	virtual Int32 GetTextureId()=0;
};

#endif  //__IXRENDERTARGET_H__
