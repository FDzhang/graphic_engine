#include "CXrCellular.h"
//#include "CXrDivider.h"
#define UNSELOPACITY 0.6
#define SELOPACITY 1.0
//#define CIRCLE_OPACITY 0.3


xr_state CXrCellular::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 dsX, Float32 dsY, Float32 opacity, String tex1, String tex2, String tex3, Int32 count)
{
	IMaterial* pMtl=0;
	ISpirit* pLayer=0;
	m_itemW = w;
	m_itemH = h;
	m_itemNum = count;
	m_node = node;
	m_dsX = dsX;
	m_dsY = dsY;
	m_mtl1 = node->CreateUIMaterial(Material_AlphaShape, tex1);
	m_mtl2 = node->CreateUIMaterial(Material_AlphaShape, tex2);
	m_mtl3 = node->CreateUIMaterial(Material_AlphaShape, tex3);
	m_textMtl = node->CreateUIFontMaterial(XR_RES"code.otf", 0);

	m_item = new CellularItem[count];
	
	Int32 dx=0;

	m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w+w*dsX,h*count);
	m_root = node->GetLayer(m_rootId);
	m_root->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);
	for (Int32 cnt=0;cnt<count;cnt++) {

#define INNER_SCALE 1.14
		Int32 cellDX;
		if (cnt&1) cellDX = w*dsX;
		else cellDX = 0;
		m_item[cnt].m_layerId1 = node->CreateSpirit(m_rootId, InsertFlag_Child, m_mtl2, UNSELOPACITY, w/2+cellDX, h/2+dx, 0 ,w,h);
		pLayer = node->GetSpirit(m_item[cnt].m_layerId1);
		pLayer->SetAnchorPoint(0.5,0.5);
		pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);
		m_item[cnt].m_layerId2 = node->CreateSpirit(m_rootId, InsertFlag_Child, m_mtl1, UNSELOPACITY, w/2+cellDX, h/2+dx, 0 ,w/INNER_SCALE,h/INNER_SCALE);
		pLayer = node->GetSpirit(m_item[cnt].m_layerId2);
		pLayer->SetAnchorPoint(0.5,0.5);
		pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);

		m_item[cnt].m_baseId = node->CreateSpirit(m_rootId, InsertFlag_Child, m_mtl3, 0.0, w/2+cellDX, h/2+dx, 0 ,w/INNER_SCALE,h/INNER_SCALE);
		pLayer = node->GetSpirit(m_item[cnt].m_baseId);
		pLayer->SetAnchorPoint(0.5,0.5);
		pLayer->SetEventResponder(this);

		pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);
		m_item[cnt].m_fontLayerId = node->CreateTextLayer(m_rootId, InsertFlag_Child, m_textMtl, UNSELOPACITY, w/2+cellDX, h/2+dx, &m_item[cnt].text, h/3);
		m_item[cnt].text->SetTransitionStyle(500, AnimationStyle_EaseOut);
		//m_item[cnt].pLayer = pLayer;

		dx+= h*dsY;

	}

	pLayer = node->GetSpirit(m_item[m_selected].m_layerId1);
	pLayer->SetOpacity(1);
	pLayer = node->GetSpirit(m_item[m_selected].m_layerId2);
	pLayer->SetOpacity(1);
	pLayer = m_node->GetSpirit(m_item[m_selected].m_baseId);
	pLayer->SetOpacity(0);
	m_node->GetLayer(m_item[m_selected].m_fontLayerId)->SetOpacity(SELOPACITY);

	return XR_OK;
}

static Int32 prevSelect=0;
Void CXrCellular::Update()
{
	ISpirit* pLayer=0;
	if (prevSelect != m_selected) {
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_layerId1);
		pLayer->SetOpacity(UNSELOPACITY);
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_layerId2);
		pLayer->SetOpacity(UNSELOPACITY);
		m_item[prevSelect].text->SetOpacity(UNSELOPACITY);
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_baseId);
		pLayer->SetOpacity(0);

		pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId1);
		pLayer->SetOpacity(SELOPACITY);
		pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId2);
		pLayer->SetOpacity(SELOPACITY);
		m_item[m_selected].text->SetOpacity(SELOPACITY);
	}

	//static Float32 delta=0.0;
	if (m_selected>=0) {
			pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId1);
			pLayer->RotateDZ(-1);
		//m_item[m_selected].rotation-=1;
	}
	
}

Boolean CXrCellular::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	ILayer* pLayer=0,*pLayer1=0,*pLayer2=0,*pPrevpLayer=0,*pPrevLayer1=0,*pPrevLayer2=0;
	
	for (Int32 i=0;i<m_itemNum;i++) {
		if (layerId==m_item[i].m_baseId) {
			pPrevpLayer = m_node->GetSpirit(m_item[m_selected].m_baseId);
			pPrevLayer1 =  m_node->GetSpirit(m_item[m_selected].m_layerId1);
			pPrevLayer2 =  m_node->GetSpirit(m_item[m_selected].m_layerId2);
			m_node->GetLayer(m_item[m_selected].m_fontLayerId)->SetOpacity(UNSELOPACITY);
			pLayer = m_node->GetSpirit(layerId);
			pLayer1 =  m_node->GetSpirit(m_item[i].m_layerId1);
			pLayer2 =  m_node->GetSpirit(m_item[i].m_layerId2);
			m_node->GetLayer(m_item[i].m_fontLayerId)->SetOpacity(SELOPACITY);
			if (type == TouchEvent_Down) {
				
				pLayer->SetOpacity(0.9);
				pLayer1->SetOpacity(SELOPACITY);
				pLayer2->SetOpacity(SELOPACITY);
				pPrevpLayer->SetOpacity(0);
				pPrevLayer1->SetOpacity(UNSELOPACITY);
				pPrevLayer2->SetOpacity(UNSELOPACITY);
				m_selected = i;
				if (m_trigger) m_trigger->OnPress(i);
			}
			else if (type == TouchEvent_Up) {
				pLayer->SetOpacity(0.4);
				//pLayer1->SetOpacity(UNSELOPACITY);
				//pLayer2->SetOpacity(UNSELOPACITY);
				if (m_trigger) m_trigger->OnRelease(i, true);
			}

		}
	}
	return TRUE;
}

Void CXrCellular::SetItemText(Int32 num, String text)
{
	Float32 tw, th;
	Float32 dsx;
	if (num<0 || num>m_itemNum) return;
	if (num&1) {
		dsx = m_dsX;
	}
	else dsx=0;

	m_item[num].text->SetText(text);
	m_item[num].text->GetTextWH(&tw,&th);
	m_item[num].text->SetPosition((m_itemW-tw)/2+dsx*m_itemW,m_itemH*0.6+m_itemH*num*m_dsY);
}
