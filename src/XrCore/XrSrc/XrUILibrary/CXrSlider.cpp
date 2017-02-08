#include "CXrSlider.h"
#include "../Platform/XrPath.h"
#include "../Platform/XrOS.h"

#include <stdio.h>

static IDeviceManager* pIdm=0;
static char LineHTex[] = XR_RES"line16V.pvr";
static char LineVTex[] = XR_RES"line16H.pvr";
static char MaskHTex[] = XR_RES"maskbarH.pvr";
static char MaskVTex[] = XR_RES"maskbarV.pvr";

static int ModeWH[2] = {1,8};

static int ScrollWH[2] = {0,0};
static int LayoutXY[2] = {0,0};
static int FontXY[2] = {0,0};

//static float color[3]={0.9,0.5,0.2};
static float color[3]={1.0,1.0,1.0};

CXrSlider::CXrSlider()
{
	divCount = 0;
}
CXrSlider::~CXrSlider()
{
	if (divIds) delete divIds;
}

Void CXrSlider::InitRes(class IUINode* node, Int32 w, Int32 h)
{
	IXrCore* core = GetXrCoreInterface();
	core->GetDeviceManager(&pIdm);
	RTId = pIdm->CreateRenderTarget(w, h, XR_R8G8B8A8, XR_NONE, 0);
	RTNodeId = core->CreateRenderNodeUI(RenderNodeType_UI2D, RTId, &rtNode);
	RTMtlId = node->CreateMaterialFromRenderTarget(Material_UI_Spirit_With_Mask, RTId, &pRTMtl);
	Void* pData = GenLineRGBA(16, 0, 2, 0xFFFFFFFF);
	//memset(pData, 205, 4*16);
	IMaterial* mtl;
	if (m_mode == ScrollMode_X) {
		line16Tex = pIdm->CreateTexture(pData, 1, 16, XR_R8G8B8A8, XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, 1);
		pRTMtl->SetTransparencyMap(MaskHTex);
		lineMtlId = rtNode->CreateMaterial(Material_UI_Spirit, &mtl);
		mtl->SetDiffuseMap(line16Tex);
		ModeWH[0]=1;
	    ModeWH[1]=8;
		ScrollWH[0] = w/5;
		ScrollWH[1] = h;
		LayoutXY[0] = 2*w/5;
		LayoutXY[1] = 0;
		FontXY[0] = -5;
		FontXY[1] = 28;
	}
	else {
		line16Tex = pIdm->CreateTexture(pData, 16, 1, XR_R8G8B8A8, XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, 1);
		pRTMtl->SetTransparencyMap(MaskVTex);
		lineMtlId = rtNode->CreateMaterial(Material_UI_Spirit, &mtl);
		mtl->SetDiffuseMap(line16Tex);
		ModeWH[0]=8;
	    ModeWH[1]=1;
		ScrollWH[0] = w;
		ScrollWH[1] = h/5;
		LayoutXY[0] = 0;
		LayoutXY[1] = 2*h/5;
		FontXY[0] = 18;
		FontXY[1] = 6;
	}
	delete (char*)pData;
}

Void CXrSlider::SetRange(Int32 low, Int32 high)
{
	m_low = low;
	m_high = high;
}

Void CXrSlider::SetDivider(Int32 div)
{
	m_div = div;	
	divCount = (m_high-m_low)/div;
}

Void CXrSlider::SetMode(ScrollMode mode)
{
	m_mode = mode;
}


Void CXrSlider::SetDividerMul(Int32 multiple)
{
	m_mul = multiple;
}

Void CXrSlider::Add(class IUINode* node, Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y,Int32 w, Int32 h, ScrollMode mode, Int32 low, Int32 high, Int32 div, Int32 mul)
{
	SetMode(mode);
	SetRange(low, high);
	SetDivider(div);
	SetDividerMul(mul);

	if (divCount<=0) return;

	InitRes(node, w, h);

	baseLayerId = node->CreateSpirit(targetIndex, flag, RTMtlId, 1.0, x, y, 0, w, h); 
	m_root = node->GetLayer(baseLayerId);
	m_root->SetEventResponder(this);	
	m_root->DivertEvent(RTNodeId);
	//scrollPanelId = rtNode->CreateScrollPanel(-1, InsertFlag_Default, LayoutXY[0],LayoutXY[1], ScrollWH[0], ScrollWH[1], mode, 120);
	layoutPanelId = rtNode->CreateLayoutPanel(-1, InsertFlag_Default, 0,0, 300, 300, (LayoutMode)mode, 120);
	pPanel = rtNode->GetLayoutPanel(layoutPanelId);

	ITextLayer* text, *text2, *text3;
	CHAR texName[128];

	textMtlId = rtNode->CreateUIFontMaterial(XR_RES"zephyrea.ttf", 0);

	divIds = new int[divCount];

	int i,inc=0;
	for (i=0;i<divCount;i++) {
		if ((inc % m_mul)==0) {
			divIds[i] = rtNode->CreateSpirit(layoutPanelId, InsertFlag_Child,lineMtlId,1.0, 0,0);
			rtNode->CreateTextLayer(divIds[i], InsertFlag_Child, textMtlId, 1.0, FontXY[0], FontXY[1], &text, 16);
			sprintf(texName, "%d", i);
			text->SetText(texName);
			text->SetColor(color[0],color[1],color[2]);
		}
		else {
			divIds[i] = rtNode->CreateSpirit(layoutPanelId, InsertFlag_Child,lineMtlId,1.0, 0,0,0, ModeWH[0], ModeWH[1]);
		}
		inc++;
	}

	ILayoutPanel* testPanel = rtNode->GetLayoutPanel(layoutPanelId);
	
	testPanel->SetInterval(10, 10);
	testPanel->ReArrange();
	m_node = node;
}

Void CXrSlider::GetSilderAP(IAProperty** ppIAPX, IAProperty** ppIAPY)
{
	if (ppIAPX) pPanel->GetCAProperty(AP_X ,ppIAPX);
	if (ppIAPY) pPanel->GetCAProperty(AP_Y ,ppIAPY);
}
