#ifndef __ITEXTLAYER_H__
#define __ITEXTLAYER_H__
#include "xrTypes.h"
#include "ILayer.h"

class ITextLayer : virtual public ILayer
{
public:
	//virtual xr_state SetBackgroundColor(
 //       /* [in] */ Int32 color)=0;

	//virtual xr_state SetForegroundColor(
 //       /* [in] */Int32 color)=0;

 //   virtual xr_state SetFontFamily(
 //       /* [in] */ String family)=0;

	virtual xr_state SetFontSize(
         /* [in] */ Float32 size)=0;

	virtual xr_state SetText(
         /* [in] */ String text)=0;
	virtual xr_state SetText(
         /* [in] */ unsigned int index)=0;

	virtual xr_state SetColor(
         /* [in] */ Float32 r,
		 /* [in] */ Float32 g,
		 /* [in] */ Float32 b)=0;
	
	virtual xr_state GetTextWH(
		/* [out] */ Float32* width,
		/* [out] */ Float32* height)=0;

	//virtual xr_state SetTextAlignment(
 //        /* [in] */ Int32 style)=0;
};

#endif  //__ITEXTLAYER_H__
