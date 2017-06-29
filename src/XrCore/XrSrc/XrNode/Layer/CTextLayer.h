#ifndef __CTEXTLAYER_H__
#define __CTEXTLAYER_H__
#include "../../Common/XrInternal.h"
#include "../../External/ITextLayer.h"
#include "CLayer.h"

class CTextLayer: public ITextLayer, public CLayer
{
public:
	CTextLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity);
	virtual ~CTextLayer();

	//virtual xr_state SetFontFamily(
	//	/* [in] */ Int32 fontId);

	virtual xr_state SetText(
         /* [in] */ String text);
    virtual const char* GetText();
	virtual xr_state SetText(
         /* [in] */ unsigned int index){return 0;};
    
	virtual xr_state SetFontSize(
         /* [in] */ Float32 size);

	virtual xr_state SetColor(
         /* [in] */ Float32 r,
		 /* [in] */ Float32 g,
		 /* [in] */ Float32 b);

	virtual xr_state GetTextWH(
		/* [out] */ Float32* width,
		/* [out] */ Float32* height);

	virtual Int32 OnAddMesh(Float32* vBuffer, UInt16* iBuffer, Float32 x, Float32 y, Float32 opacity, Int32* vCount, Int32* iCount);

	virtual Int32 GetVertexCount() { return m_stringLen*4; }

	LAYER_DEFAULT_IMPLEMENTATION

private:
	Int32	m_stringLen;
	CHAR	m_text[MaxStringLen];
	CAProperty						r;
	CAProperty						g;
	CAProperty						b;
	CAProperty						fontSize;
	class XrFont*	m_font;
};

#endif  //__CTEXTLAYER_H__

