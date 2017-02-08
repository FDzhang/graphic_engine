#ifndef _CRENDERGROUPLIST_H
#define _CRENDERGROUPLIST_H
#include "../../Common/XrHashMap.h"
#include "../../Common/xrDataStruct.h"
class CMaterial;
class CBatchRender;

#define BatchRenderNumOneGroup	10
//typedef CLazySlot<CBatchRender,10> CRenderGroup;
//struct CRenderGroup : public 

struct CRenderGroup :  public CBiLinkNode<CRenderGroup>
{
	CLazySlot<CBatchRender,BatchRenderNumOneGroup>	m_group;
	Void Reset()
	{
		m_group.Clear();
	}
};

//XrHashMap<CMaterial*,CBatchRender*> CRenderGroup;
class CRenderGroupList
{
public:
	CRenderGroupList();
	Void Render(CPool<CBatchRender>& renderpool);
	Void PreRender(CPool<CBatchRender>& renderpool, class CLight* pLight, const XRMat4* view, const XRMat4* proj);
	Void AddBatchRender(CMaterial* pMtl,CBatchRender* pBatchRender);
	Void Clear();
	CRenderGroup* Find(CMaterial* mtl);
	

protected:
	//XrHashMap<CMaterial*,CRenderGroup*>	m_RenderGroupMap;
	CArray<CRenderGroup*>					m_pRenderGroups;
	CArray<CMaterial*>						m_pMaterials;
	static CPool<CRenderGroup>				sm_RenderGroupPool;
};

#endif