#include "CTextLayer.h"
#include "../Scene/CUINode.h"
#include "../../3rd/Font.h"

CTextLayer::CTextLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity):
	CLayer(x, y, z, 0, 0, 0, opacity),
	m_stringLen(0)
{
	SetMaterial(pMtl);
	if (pMtl) {
		m_font = (XrFont*)pMtl->GetDiffuseMap()->extraInfo;
	}
	else m_font = 0;
	r._Set(1);
	g._Set(1);
	b._Set(1);
	fontSize._Set(width);
	m_layerType = LayerType_Text;
	m_eventStyle = EventStyle_Receive;
    m_masksToBound = TRUE;
	m_self = (Void*)this;
}

CTextLayer::~CTextLayer()
{
}

xr_state CTextLayer::SetFontSize(
         /* [in] */ Float32 size)
{
	Float32 w, h;
	fontSize.Set(size);
	if (!m_stringLen) return XR_OK;
	m_font->MeasureText(m_text, fontSize.GetDst(), &w, &h);
	width.Set(w);
	height.Set(size);
	//width.Set(size);
	return XR_OK;
}

xr_state CTextLayer::SetText(String text)
{
	Float32 w, h;
	m_stringLen = strlen(text);
	strcpy(m_text, text);
	m_font->MeasureText(m_text, fontSize.GetDst(), &w, &h);
	width.Set(w);
	height.Set(fontSize.GetDst());
	return XR_OK;
}

Int32 CTextLayer::OnAddMesh(Float32* vBuffer, UInt16* iBuffer, Float32 x, Float32 y, Float32 opacity, Int32* vCount, Int32* iCount)
{
	if (!m_stringLen || !m_font) return 0;
	Color color;
	color.Set(r.Get(), g.Get(), b.Get(), opacity);
	return m_font->AddText(x, y, fontSize.Get(), m_text, vBuffer, iBuffer, vCount, iCount, (Float32*)&color);
}

xr_state CTextLayer::SetColor(
     /* [in] */ Float32 r,
	 /* [in] */ Float32 g,
	 /* [in] */ Float32 b)
{
	this->r.Set(r,0,0);
	this->g.Set(g,0,0);
	this->b.Set(b,0,0);
	return XR_OK;
}

xr_state CTextLayer::GetTextWH(
	/* [out] */ Float32* width,
	/* [out] */ Float32* height)
{
	if (!m_stringLen || !m_font) {
		*width = 0;
		*height = 0;
		return XR_OK;
	}
	m_font->MeasureText(m_text, fontSize.GetDst(), width, height);
	return XR_OK;
}
