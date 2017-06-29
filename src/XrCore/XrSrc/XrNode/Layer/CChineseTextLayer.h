#ifndef __CCHINESETEXTLAYER_H__
#define __CCHINESETEXTLAYER_H__
#include "../../Common/XrInternal.h"
#include "../../External/ITextLayer.h"
#include "CLayer.h"

class CChineseTextLayer: public ITextLayer, public CLayer
{
public:
	CChineseTextLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity);
	virtual ~CChineseTextLayer();

	//virtual xr_state SetFontFamily(
	//	/* [in] */ Int32 fontId);

	virtual xr_state SetText(
         /* [in] */ String text){return 0;};
    const char* GetText() { return NULL;}
	virtual xr_state SetText(
         /* [in] */ unsigned int index);


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
	int AddText(float x, float y, float size,  unsigned int text_index, float* vBuffer, unsigned short* iBuffer, int* vCount, int* iCount, float* color);
	int GenVertex(unsigned int charNum, float offsetX, float offsetY, float size, float* vBuffer, unsigned short* iBuffer, int VertStartNum, float* color);

	LAYER_DEFAULT_IMPLEMENTATION

private:
	Int32	m_stringLen;
	CHAR	m_text[MaxStringLen];
	unsigned int m_text_index;
	CAProperty						r;
	CAProperty						g;
	CAProperty						b;
	CAProperty						fontSize;
	class XrFont*	m_font;
};

#endif  //__CCHINESETEXTLAYER_H__

