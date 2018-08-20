#include "CXrSelector.h"
#include "CXrPanel.h"
//#include "CXrDivider.h"
#define UNSELOPACITY 0.6
#define SELOPACITY 0.9
//#define CIRCLE_OPACITY 0.3

struct SelectorItem {
	Int32		m_baseId;
	Int32		m_fontLayerId;
	ITextLayer*	text;
	CXrPanel	m_base;
	CXrPanel	m_hit;
	String		m_text;
};

CXrSelector::~CXrSelector()
{

}
xr_state CXrSelector::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 dx, Int32 dy,  Float32 opacity, const char* BGTex, const char* FGTex, Int32 row, Int32 colume)
{
	IMaterial* pMtl=0;
	ISpirit* pLayer=0;
	m_itemW = w;
	m_itemH = h;
	m_itemNum = row*colume;
	m_rowNum = row;
	m_columeNum = colume; 
	m_node = node;
	m_dx = dx;
	m_dy = dy;
	m_mtl1 = node->CreateUIMaterial(Material_UI_Spirit, BGTex);
	m_mtl2 = node->CreateUIMaterial(Material_UI_Spirit, FGTex);
	m_textMtl = node->CreateUIFontMaterial(XR_RES"code.ttf", 0);
	m_opacity = opacity;
	m_item = new SelectorItem[m_itemNum];
	
	m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w+(dx)*(colume+1),h+(dy)*(row+1));
	m_root = node->GetLayer(m_rootId);

	Int32 lx=0,ly=0,r,c,cnt=0;
	for (c=0;c<colume;c++) {
		for (r=0;r<row;r++) {
			m_item[cnt].m_base.SetCornerSize(m_cornerSize);
			m_item[cnt].m_hit.SetCornerSize(m_cornerSize);
			m_item[cnt].m_base.Add(node, m_rootId, InsertFlag_Child, lx,ly,w,h,m_opacity, m_mtl1);
			m_item[cnt].m_hit.Add(node, m_rootId, InsertFlag_Child, lx,ly,w,h,0, m_mtl2);
			m_item[cnt].m_baseId = m_item[cnt].m_hit.GetRootId();
			m_item[cnt].m_hit.GetRoot()->SetEventResponder(this);
			m_item[cnt].m_fontLayerId = node->CreateTextLayer(m_rootId, InsertFlag_Child, m_textMtl, SELOPACITY, w/2+lx+m_textX, h/2+ly+m_textY, &m_item[cnt].text, h/1.7);
			m_item[cnt].text->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);
			m_item[cnt].text->SetEventResponder(this);
			//m_item[cnt].pLayer = pLayer;

			cnt++;
			ly+= dy;
		}
		ly = 0;
		lx+= dx;
	}
	return XR_OK;
}
xr_state CXrSelector::AddChinese(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 dx, Int32 dy,  Float32 opacity, String BGTex, String FGTex, Int32 row, Int32 colume)
{
	IMaterial* pMtl=0;
	ISpirit* pLayer=0;
	m_itemW = w;
	m_itemH = h;
	m_itemNum = row*colume;
	m_rowNum = row;
	m_columeNum = colume; 
	m_node = node;
	m_dx = dx;
	m_dy = dy;
	m_mtl1 = node->CreateUIMaterial(Material_UI_Spirit, BGTex);
	m_mtl2 = node->CreateUIMaterial(Material_UI_Spirit, FGTex);
	m_textMtl = node->CreateUIChineseFontMaterial(XR_RES"blackch.dds", 0);
	
	//m_textMtl = node->CreateUIFontMaterial(XR_RES"mcg.ttf", 0);
	m_opacity = opacity;
	m_item = new SelectorItem[m_itemNum];
	
	m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w+(dx)*(colume+1),h+(dy)*(row+1));
	m_root = node->GetLayer(m_rootId);

	Int32 lx=0,ly=0,r,c,cnt=0;
	for (c=0;c<colume;c++) {
		for (r=0;r<row;r++) {
			m_item[cnt].m_base.SetCornerSize(m_cornerSize);
			m_item[cnt].m_hit.SetCornerSize(m_cornerSize);
			m_item[cnt].m_base.Add(node, m_rootId, InsertFlag_Child, lx,ly,w,h,m_opacity, m_mtl1);
			m_item[cnt].m_hit.Add(node, m_rootId, InsertFlag_Child, lx,ly,w,h,0, m_mtl2);
			m_item[cnt].m_baseId = m_item[cnt].m_hit.GetRootId();
			m_item[cnt].m_hit.GetRoot()->SetEventResponder(this);
			//m_item[cnt].m_fontLayerId = node->CreateTextLayer(m_rootId, InsertFlag_Child, m_textMtl, SELOPACITY, w/2+lx+m_textX, h/2+ly+m_textY, &m_item[cnt].text, h/1.7);
			//textId = m_lisenceNode->CreateChineseTextLayer(-1, InsertFlag_Default, textMtlId, 1.0, 10, 0, &Chinesetext, 84);
			m_item[cnt].m_fontLayerId = node->CreateChineseTextLayer(m_rootId, InsertFlag_Child, m_textMtl, SELOPACITY, w/2+lx+m_textX, h/2+ly+m_textY, &m_item[cnt].text, h/1.7);

			m_item[cnt].text->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);
			m_item[cnt].text->SetEventResponder(this);
			//m_item[cnt].pLayer = pLayer;

			cnt++;
			ly+= dy;
		}
		ly = 0;
		lx+= dx;
	}
	return XR_OK;
}
static Int32 prevSelect=0;
Void CXrSelector::Update()
{
}

Boolean CXrSelector::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	ILayer* pLayer=0,*pLayer1=0,*pLayer2=0,*pPrevpLayer=0,*pPrevLayer1=0,*pPrevLayer2=0;
	
	for (Int32 i=0;i<m_itemNum;i++) {
		if (layerId==m_item[i].m_baseId || layerId==m_item[i].m_fontLayerId) {

			if (type == TouchEvent_Down) {
				Select(i);
				m_item[i].m_hit.SetOpacity(m_HLOpacity+0.2);
				if (m_trigger) m_trigger->OnPress(i);
			}
			else if (type == TouchEvent_Up) {
				m_item[i].m_hit.SetOpacity(m_HLOpacity);
				if (m_trigger) m_trigger->OnRelease(i, true);
			}

		}
	}
	return TRUE;
}

Void CXrSelector::SetTextSize(Int32 size)
{
	Int32 i;
	for (i=0;i<m_itemNum;i++) {
		m_item[i].text->SetFontSize(size);
	}
}

Void CXrSelector::SetItemText(Int32 num,char* text, Int32 size)
{
	Float32 tw, th;
	Float32 dsx, posx, posy;
	if (num<0 || num>m_itemNum) return;

	Int32 r,c;
	c = num / m_rowNum;
	r = num % m_rowNum;
	if (size != -1) m_item[num].text->SetFontSize(size);
	m_item[num].text->SetText(text);
	m_item[num].text->GetTextWH(&tw,&th);

	if (m_textX) posx = m_dx*c+m_textX;
	else posx = (m_itemW-tw)/2+m_dx*c;

	if (m_textY) posy = m_dy*r+m_textY;
	else posy =(th+m_itemH)/2-m_item[num].text->GetHeight()+m_dy*r;

	m_item[num].text->SetPosition(posx,posy);
}

Void CXrSelector::SetChineseItemText(Int32 num, unsigned int  text, Int32 size)
{
	Float32 tw, th;
	Float32 dsx, posx, posy;
	if (num<0 || num>m_itemNum) return;

	Int32 r,c;
	c = num / m_rowNum;
	r = num % m_rowNum;
	if (size != -1) m_item[num].text->SetFontSize(size);
	m_item[num].text->SetText(text);
	m_item[num].text->GetTextWH(&tw,&th);

	if (m_textX) posx = m_dx*c+m_textX;
	else posx = (m_itemW-tw)/2+m_dx*c;

	if (m_textY) posy = m_dy*r+m_textY;
	else posy =(th+m_itemH)/2-m_item[num].text->GetHeight()+m_dy*r;

	m_item[num].text->SetPosition(posx,posy);
}

Void CXrSelector::Select(Int32 num)
{
	if (num == m_selected || num<0 || num >= m_itemNum) return;

	//unhighlight previous button
	if (m_selected>=0) {
		//m_item[m_selected].m_base.SetOpacity(0.5);
		m_item[m_selected].m_hit.SetOpacity(0);
	}

	//m_item[num].m_base.SetOpacity(0);
	m_item[num].m_hit.SetOpacity(m_opacity);
    
//    for (int i=0; i<m_itemNum; i++) {
//        if (i==m_selected) m_item[i].text->SetOpacity(SELOPACITY);
//        else m_item[i].text->SetOpacity(UNSELOPACITY);
//    }
	m_selected = num;
}

Void CXrSelector::ClearSelect()
{
	if (m_selected>=0) {
		//m_item[m_selected].m_base.SetOpacity(0.5);
		m_item[m_selected].m_hit.SetOpacity(0);
	}
	m_selected = -1; 
}
