#include "CXrDivider.h"
#include "../XrNode/Scene/CUINode.h"

#define LENGTH 8
#define INTVAL 2

static int HDashId=-1;
static int VDashId=-1;
static int HLineId=-1;
static int VLineId=-1;

CXrDivider::CXrDivider(Int32 len, Boolean isHorizontal, Boolean isDashed)
{
	m_len = len;
	m_isHorizontal = isHorizontal;
	m_isDashed = isDashed;
}
Void CXrDivider::DeInitTex()
{
	HDashId=-1;
	VDashId=-1;
	HLineId=-1;
	VLineId=-1;
}
Void CXrDivider::InitTex()
{
	IXrCore* core = GetXrCoreInterface();
	IDeviceManager* dm=0;
	core->GetDeviceManager(&dm);
	char* pData;
	if (HDashId == -1) {
		pData = (char*)GenLineRGBA(LENGTH, INTVAL, 0, 0xFFFFFFFF);
		HDashId = dm->CreateTexture(pData, LENGTH, 1, XR_R8G8B8A8, XR_SAMPLER_NEAREST | XR_SAMPLER_WRAP,1);
		VDashId = dm->CreateTexture(pData, 1, LENGTH, XR_R8G8B8A8, XR_SAMPLER_NEAREST | XR_SAMPLER_WRAP,1);
		delete pData;
		pData = (char*)GenLineRGBA(LENGTH, 0, 0, 0xFFFFFFFF);
		HLineId = dm->CreateTexture(pData, LENGTH, 1, XR_R8G8B8A8, XR_SAMPLER_NEAREST | XR_SAMPLER_WRAP,1);
		VLineId = XRDM->CreateTexture(pData, 1, LENGTH, XR_R8G8B8A8, XR_SAMPLER_NEAREST | XR_SAMPLER_WRAP,1);
		delete pData;
	}
	else return;
}

xr_state CXrDivider::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y,Int32 num,Int32 interval)
{

	InitTex();
	IMaterial* mtl=0;
	m_mtlId = node->CreateMaterial(Material_UI_Spirit, &mtl);

	Rect roi;
    for(Int32 i =0;i<num;i++)
    {
    	if (m_isHorizontal) {
    		roi.Set(0,0,m_len/LENGTH,1);
    		if (m_isDashed) mtl->SetDiffuseMap(HDashId);
    		else mtl->SetDiffuseMap(HLineId);
    		m_rootId = node->CreateSpirit(targetIndex, flag, m_mtlId, 1.0, x,y+interval*i,&roi,m_len, 1);
    	}
    	else {
    		roi.Set(0,0,1,m_len/LENGTH);
    		if (m_isDashed) mtl->SetDiffuseMap(VDashId);
    		else mtl->SetDiffuseMap(VLineId);
    		m_rootId = node->CreateSpirit(targetIndex, flag, m_mtlId, 1.0, x+interval*i,y,&roi,1, m_len);
    	}
    }
	m_root = node->GetLayer(m_rootId);
	m_node = node;
	m_thickness=1;
	return XR_OK;
}
Void CXrDivider::Update(void)
{
	m_root->SetScale(m_len/LENGTH,m_thickness);
	//if (m_isHorizontal) m_root->SetWidth(m_len/LENGTH);
	//else m_root->SetHeight(m_len/LENGTH);

}
Void CXrDivider::SetThickness(Int32 thickness)
{
	if (m_isHorizontal) m_root->SetHeight(thickness);
	else m_root->SetWidth(thickness);
	m_thickness = thickness;
}
void CXrDivider::SetColor(float r,float g,float b)
{
    m_root->SetColor(r,g,b);
}

