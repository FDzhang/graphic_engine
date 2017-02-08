#include "CChineseTextLayer.h"
#include "../Scene/CUINode.h"
#include "../../3rd/Font.h"

#define TOTAL_CHINESE_NUM  36
#define ROW_CHARATER_NUM  6
#define TEXTURE_IMAGE_SIZE_WIDTH  1112.0
#define TEXTURE_IMAGE_SIZE_HEIGHT 998.0

CChineseTextLayer::CChineseTextLayer(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, CMaterial* pMtl, Float32 opacity):
	CLayer(x, y, z, 0, 0, 0, opacity),
	m_stringLen(0)
{
	SetMaterial(pMtl);
	#if 0
	if (pMtl) {
		//m_font = (XrFont*)pMtl->GetDiffuseMap()->extraInfo;
	}
	else m_font = 0;
	#endif
	r._Set(1);
	g._Set(1);
	b._Set(1);
	fontSize._Set(width);
	m_layerType = LayerType_Text;
	m_eventStyle = EventStyle_Receive;
    m_masksToBound = TRUE;
	m_self = (Void*)this;
}

CChineseTextLayer::~CChineseTextLayer()
{
}

xr_state CChineseTextLayer::SetFontSize(
         /* [in] */ Float32 size)
{
	Float32 w, h;
	fontSize.Set(size);
	if (!m_stringLen) return XR_OK;
	//m_font->MeasureText(m_text, fontSize.GetDst(), &w, &h);
	width.Set(size);
	height.Set(size);
	//width.Set(size);
	return XR_OK;
}

xr_state CChineseTextLayer::SetText(unsigned int index)
{

	Float32 w, h;
	m_stringLen = 1;
	//m_font->MeasureText(m_text, fontSize.GetDst(), &w, &h);
	m_text_index = index;
	width.Set(fontSize.GetDst());
	height.Set(fontSize.GetDst());
	return XR_OK;
}

Int32 CChineseTextLayer::OnAddMesh(Float32* vBuffer, UInt16* iBuffer, Float32 x, Float32 y, Float32 opacity, Int32* vCount, Int32* iCount)
{
	//if (!m_stringLen || !m_font) return 0;
	Color color;
	color.Set(r.Get(), g.Get(), b.Get(), opacity);
	//modify this part to get the vbufeer and i buffer for text render.
	return AddText(x, y, fontSize.Get(), m_text_index, vBuffer, iBuffer, vCount, iCount, (Float32*)&color);
	return 0;
}

int CChineseTextLayer::AddText(float x, float y, float size, unsigned int text_index, float* vBuffer, unsigned short* iBuffer, int* vCount, int* iCount, float* color)
{
	float scale = size/FONT_SIZE;
	int dx = 0, num = 0, wordCount=0, VertStartNum = *vCount;

	GenVertex(text_index, x+dx, y, size, &vBuffer[wordCount*4*8], &iBuffer[wordCount*6], VertStartNum, color);



	*vCount += 4;
	*iCount += 6;
	wordCount=1;
	return wordCount;
}
int CChineseTextLayer::GenVertex(unsigned int charNum, float offsetX, float offsetY, float size, float* vBuffer, unsigned short* iBuffer, int VertStartNum, float* color)
{
	int x, y, width, height, horiBearingY, horiBearingX;
	float iTextWidthStep,iTextHeightStep;
	float fwidthtol,fheighttol;
    unsigned int count=charNum;
	if ( count > TOTAL_CHINESE_NUM) return -1;
	
	y = (count / ROW_CHARATER_NUM) ;
	x = (count % ROW_CHARATER_NUM);

//	width = m_texInfo[count].width * scale;
	//height = m_texInfo[count].height * scale;
	//horiBearingY = m_texInfo[count].horiBearingY * scale;
//	horiBearingX = m_texInfo[count].horiBearingX * scale;
    iTextWidthStep = TEXTURE_IMAGE_SIZE_WIDTH/(float)ROW_CHARATER_NUM;
    iTextHeightStep = TEXTURE_IMAGE_SIZE_HEIGHT/(float)((TOTAL_CHINESE_NUM/ROW_CHARATER_NUM));
	x=x*iTextWidthStep;
	y=y*iTextHeightStep;
	fwidthtol=iTextWidthStep*0.01;
	fheighttol = iTextHeightStep*0.1;
	horiBearingX=0;
	horiBearingY=-this->width.GetDst()*0.06;
	size=this->width.GetDst();
#if 0
	vBuffer[0] = offsetX+horiBearingX;
	vBuffer[1] = offsetY-horiBearingY+size;
	vBuffer[2] = color[3];
	vBuffer[3] = color[0];
	vBuffer[4] = color[1];
	vBuffer[5] = color[2];
	vBuffer[6] = float(x)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[7] = float(y)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8+0] = offsetX+horiBearingX;
	vBuffer[8+1] = offsetY-horiBearingY+size+size;
	vBuffer[8+2] = color[3];
	vBuffer[8+3] = color[0];
	vBuffer[8+4] = color[1];
	vBuffer[8+5] = color[2];
	vBuffer[8+6] = float(x)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8+7] = float(y+iTextHeightStep)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8*2+0] = offsetX+horiBearingX+size;
	vBuffer[8*2+1] = offsetY-horiBearingY+size+size;
	vBuffer[8*2+2] = color[3];
	vBuffer[8*2+3] = color[0];
	vBuffer[8*2+4] = color[1];
	vBuffer[8*2+5] = color[2];
	vBuffer[8*2+6] = float(x+iTextWidthStep)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8*2+7] = float(y+iTextHeightStep)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8*3+0] = offsetX+horiBearingX+size;
	vBuffer[8*3+1] = offsetY-horiBearingY+size;
	vBuffer[8*3+2] = color[3];
	vBuffer[8*3+3] = color[0];
	vBuffer[8*3+4] = color[1];
	vBuffer[8*3+5] = color[2];
	vBuffer[8*3+6] = float(x+iTextWidthStep)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8*3+7] = float(y)/TEXTURE_IMAGE_SIZE_HEIGHT;
#endif


	vBuffer[0] = offsetX+horiBearingX;
	vBuffer[1] = offsetY-horiBearingY;
	vBuffer[2] = color[3];
	vBuffer[3] = color[0];
	vBuffer[4] = color[1];
	vBuffer[5] = color[2];
	vBuffer[6] = (float(x)+fwidthtol)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[7] = (float(y)+fheighttol)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8+0] = offsetX+horiBearingX;
	vBuffer[8+1] = offsetY-horiBearingY+size;
	vBuffer[8+2] = color[3];
	vBuffer[8+3] = color[0];
	vBuffer[8+4] = color[1];
	vBuffer[8+5] = color[2];
	vBuffer[8+6] = (float(x)+fwidthtol)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8+7] = (float(y+iTextHeightStep)-0.2*fheighttol)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8*2+0] = offsetX+horiBearingX+size;
	vBuffer[8*2+1] = offsetY-horiBearingY+size;
	vBuffer[8*2+2] = color[3];
	vBuffer[8*2+3] = color[0];
	vBuffer[8*2+4] = color[1];
	vBuffer[8*2+5] = color[2];
	vBuffer[8*2+6] = (float(x+iTextWidthStep)-fwidthtol)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8*2+7] = (float(y+iTextHeightStep)-0.2*fheighttol)/TEXTURE_IMAGE_SIZE_HEIGHT;

	vBuffer[8*3+0] = offsetX+horiBearingX+size;
	vBuffer[8*3+1] = offsetY-horiBearingY;
	vBuffer[8*3+2] = color[3];
	vBuffer[8*3+3] = color[0];
	vBuffer[8*3+4] = color[1];
	vBuffer[8*3+5] = color[2];
	vBuffer[8*3+6] = (float(x+iTextWidthStep)-fwidthtol)/TEXTURE_IMAGE_SIZE_WIDTH;
	vBuffer[8*3+7] = (float(y)+fheighttol)/TEXTURE_IMAGE_SIZE_HEIGHT;

	iBuffer[0] = VertStartNum;
	iBuffer[1] = VertStartNum + 1;
	iBuffer[2] = VertStartNum + 2;
	iBuffer[3] = VertStartNum;
	iBuffer[4] = VertStartNum + 2;
	iBuffer[5] = VertStartNum + 3;
}

xr_state CChineseTextLayer::SetColor(
     /* [in] */ Float32 r,
	 /* [in] */ Float32 g,
	 /* [in] */ Float32 b)
{
	this->r.Set(r,0,0);
	this->g.Set(g,0,0);
	this->b.Set(b,0,0);
	return XR_OK;
}

xr_state CChineseTextLayer::GetTextWH(
	/* [out] */ Float32* width,
	/* [out] */ Float32* height)
{
	if (!m_stringLen ) {
		*width = 0;
		*height = 0;
		return XR_OK;
	}
	*width=this->width.GetDst();
	
	*height=this->height.GetDst();
	//m_font->MeasureText(m_text, fontSize.GetDst(), width, height);
	return XR_OK;
}
