#ifndef __IAPROPERTY_H__
#define __IAPROPERTY_H__
#include "xrIntrinsic.h"
 
class IAProperty
{
public:

	virtual Void Set(
		/* [in] */ Float32 val, 
		/* [in] */ UInt32 style, 
		/* [in] */ UInt32 duration)=0;

	virtual Void Delta(
		/* [in] */ Float32 dval, 
		/* [in] */ UInt32 style, 
		/* [in] */ UInt32 duration)=0;

	virtual Void Set(
		/* [in] */ Float32 val)=0;

	virtual Void Delta(
		/* [in] */ Float32 dval)=0;

	virtual Void SetTransitionStyle(
		/* [in] */ UInt32 style, 
		/* [in] */ UInt32 duration)=0;

	virtual Float32 Get()=0;

	virtual Void SetAPDelegate(
		/* [in] */ class IAnimationDelegate* apdelegate)=0;
	//virtual xr_state SetBackgroundColor(
 //       /* [in] */ Int32 color)=0;

	//virtual xr_state SetForegroundColor(
 //       /* [in] */Int32 color)=0;

	//virtual xr_state SetFontSize(
 //        /* [in] */ Int32 size)=0;

	//virtual xr_state SetTextAlignment(
 //        /* [in] */ Int32 style)=0;
};

#endif  //__ICAPROPERTY_H__
