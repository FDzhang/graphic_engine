#include "CXrPanel.h"

static Rect roi[6];
#define TRANSITION_DURATION 500
CXrPanel::CXrPanel(Int32 cornerSize, Int32 BorderWidth, Boolean hollow)
{
	m_cornerSize = cornerSize;
	m_borderWidth = BorderWidth > 0 ? BorderWidth : cornerSize;
	m_hollow = hollow;
}

CXrPanel::CXrPanel()
{
}

Void CXrPanel::SetCornerSize(Int32 cornerSize)
{
	m_cornerSize = cornerSize;
	m_borderWidth = cornerSize;
	m_hollow = FALSE;
}

Void CXrPanel::SetOpacity(Float32 opacity)
{
	Int32 count = m_hollow ? 8 : 9;
	if (m_cornerSize && m_cornerSize>0) {
		for (int i=0;i<count;i++) {
			
			ISpirit* panel = m_node->GetSpirit(m_subLayerId[i]);
			panel->SetOpacity(opacity);
		}
	}
	else {
		ISpirit* panel = m_node->GetSpirit(m_panelId);
		panel->SetOpacity(opacity);
	}
}

Void CXrPanel::SetSize(Float32 w, Float32 h)
{
	m_root->SetWidth(w);
	m_root->SetHeight(h);

	if (m_cornerSize) {
		ArrangeSquareUp();
	}
	else {
		ISpirit* panel = m_node->GetSpirit(m_panelId);
		panel->SetWidth(w);
		panel->SetHeight(h);
	}
}
xr_state CXrPanel::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity, Int32 mtlId)
{
	
	m_node = node;
	m_subLayerMtl = mtlId;
	roi[0].Set(0,0,0.5,0.5);
	roi[1].Set(0.5,0,0.5,0.5);
	roi[2].Set(0,0.5,0.5,0.5);
	roi[3].Set(0.5,0.5,0.5,0.5);
	if (m_borderWidth == m_cornerSize) roi[4].Set(0.5,0.5,0,0);
	else roi[4].Set(0.02,0.5,0,0);
	if (m_cornerSize == -1) roi[4].Set(0,0,1,1);
	m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w,h);
	m_root = node->GetSpirit(m_rootId);
	m_root->MasksToBound(TRUE);
	m_root->SetTransitionStyle(TRANSITION_DURATION, AnimationStyle_EaseOut, AP_X | AP_Y | AP_WIDTH | AP_HEIGHT | AP_OPACITY);

	ISpirit* spirit;
	if (m_cornerSize && m_cornerSize>0) {
		Int32 count = m_hollow ? 8 : 9;
		for (Int32 i=0;i<count;i++) {
			Int32 j = i>4 ? 4 : i;
			m_subLayerId[i] = node->CreateSpirit(m_rootId, InsertFlag_Child,m_subLayerMtl,opacity, 0,0,&roi[j],m_cornerSize,m_cornerSize);
			spirit = node->GetSpirit(m_subLayerId[i]);
			spirit->SetTransitionStyle(TRANSITION_DURATION, AnimationStyle_EaseOut, AP_X | AP_Y | AP_WIDTH | AP_HEIGHT | AP_OPACITY);
		}
		ArrangeSquareUp();
			
	}
	else {
		m_panelId = node->CreateSpirit(m_rootId, InsertFlag_Child, m_subLayerMtl,opacity, 0,0,&roi[4],w,h);
		spirit = node->GetSpirit(m_panelId);
		spirit->SetTransitionStyle(TRANSITION_DURATION, AnimationStyle_EaseOut, AP_X | AP_Y | AP_WIDTH | AP_HEIGHT | AP_OPACITY);
	}

	return XR_OK;
}

xr_state CXrPanel::Add(IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity, String texName)
{
	IMaterial* pMtl=0;
	Int32 subLayerMtl = node->CreateUIMaterial(Material_UI_Spirit, texName, 0 , &pMtl);
	return Add(node, targetIndex, flag, x, y, w, h, opacity, subLayerMtl);
}

Void CXrPanel::ArrangeSquareUp()
{
	#define NEXTLAYER { curr = curr->GetNext(); if (!curr) return; }

	ISpirit* spirit = m_node->GetSpirit(m_subLayerId[0]);
	Float32 hostWidth = m_root->GetWidth(), hostHeight = m_root->GetHeight();
	Float32 cornerWidth = m_cornerSize, cornerHeight = m_cornerSize;

	// leftTop layer
	spirit->SetPosition(0,0);

	//rightTop layer
	spirit = m_node->GetSpirit(m_subLayerId[1]);
	spirit->SetPosition(hostWidth-cornerWidth,0);

	//leftBottom layer
	spirit = m_node->GetSpirit(m_subLayerId[2]);
	spirit->SetPosition(0,hostHeight-cornerHeight);

	//rightBottom layer
	spirit = m_node->GetSpirit(m_subLayerId[3]);
	spirit->SetPosition(hostWidth-cornerWidth, hostHeight-cornerHeight);

	//Left layer
	spirit = m_node->GetSpirit(m_subLayerId[4]);
	spirit->SetPosition(0,cornerHeight);
	spirit->SetWidth(m_borderWidth);
	spirit->SetHeight(hostHeight-2*cornerHeight);

	//Right layer
	spirit = m_node->GetSpirit(m_subLayerId[5]);
	spirit->SetPosition(hostWidth-m_borderWidth,cornerHeight);
	spirit->SetWidth(m_borderWidth);
	spirit->SetHeight(hostHeight-2*cornerHeight);

	//Top layer
	spirit = m_node->GetSpirit(m_subLayerId[6]);
	spirit->SetPosition(cornerWidth,0);
	spirit->SetWidth(hostWidth-2*cornerWidth);
	spirit->SetHeight(m_borderWidth);

	//Bottom layer
	spirit = m_node->GetSpirit(m_subLayerId[7]);
	spirit->SetPosition(cornerWidth,hostHeight-m_borderWidth);
	spirit->SetWidth(hostWidth-2*cornerWidth);
	spirit->SetHeight(m_borderWidth);

	//center layer
	if (m_hollow) return;
	spirit = m_node->GetSpirit(m_subLayerId[8]);
	spirit->SetPosition(cornerWidth,cornerHeight);
	spirit->SetWidth(hostWidth-2*cornerWidth);
	spirit->SetHeight(hostHeight-2*cornerHeight);
}

