#ifndef __ITEXTUREDELEGATE_H__
#define __ITEXTUREDELEGATE_H__
#include "xrTypes.h"
#include "IUpdateDelegate.h"
class ITextureDelegate : public IUpdateDelegate
{ 
public:
	virtual xr_state OnCreate(
		/* [in] */ Int32 width,
		/* [in] */ Int32 height,
		/* [in] */ UInt32 format,
		/* [in/out] */ CTexture* pTexture)=0; 

	virtual xr_state OnUpdate()=0; 

	virtual Boolean NeedUpdate()=0; 

	virtual xr_state OnRelease()=0; 

};

#endif  //__ITEXTUREDELEGATE_H__
