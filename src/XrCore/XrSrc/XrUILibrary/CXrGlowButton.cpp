#include "CXrGlowButton.h"
#include "../XrNode/Scene/CUINode.h"


static char BaseTex[] = XR_RES"button.pvr";
static char GlowTes[] = XR_RES"button.pvr";
static XrRect texRect1(0,0, 0.5, 1);
static XrRect texRect2(0.5,0, 0.5, 1);

Int32 CXrGlowButton::baseMtlId = -1;
Int32 CXrGlowButton::glowMtlId = -1;

Void CXrGlowButton::GetMaterial(class IUINode* node,  Int32 * baseMtl, Int32* glowMtl)
{
	if (baseMtlId == -1) {
		*baseMtl = baseMtlId = node->CreateUIMaterial(Material_UI_Spirit, BaseTex);
	}
	else {
		*baseMtl = baseMtlId;
	}
	if (glowMtlId == -1) {
		*glowMtl = glowMtlId = node->CreateUIMaterial(Material_UI_Glow, GlowTes);
	}
	else {
		*glowMtl = glowMtlId;
	}
}

CXrGlowButton::CXrGlowButton():
	m_isPressed(0)
{
}

CXrGlowButton::~CXrGlowButton()
{
	if (m_node) {
		m_node->RemoveLayer(baseLayerId);
		m_node->RemoveLayer(glowLayerId);
	}
}

//xr_state CXrButton::InitView()
//{
//	return XR_OK;
//}

void CXrGlowButton::OnButtonPressed()
{
	printf("button pressed!\n");
}

xr_state CXrGlowButton::Add(class IUINode* node,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, class IButtonAction* action)
{
	Int32 mtl1, mtl2;
	GetMaterial(node, &mtl1, &mtl2);

	baseLayerId = node->CreateSpirit(targetIndex, flag, mtl1, 1.0, x, y, &texRect1 ,w,h); 
	m_root = node->GetLayer(baseLayerId);
	m_root->SetEventResponder(this);
	glowLayerId = node->CreateSpirit(baseLayerId, InsertFlag_Child, mtl2, 0.0, 0, 0, &texRect2, w, h); 
	glow = node->GetLayer(glowLayerId);
	glow->SetTransitionStyle(500, AnimationStyle_EaseOut);
	buttonAction = action;
	m_node = node;
	return XR_OK;
}

Boolean CXrGlowButton::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		m_isPressed = 1;
		glow->SetOpacity(1.0);
	}
	else if (type == TouchEvent_Up) {
		m_isPressed = 0;
		glow->SetOpacity(0.0);
	}
	return TRUE;
}
