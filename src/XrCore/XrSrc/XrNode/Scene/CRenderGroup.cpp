#include "CRenderGroup.h"
#include "../../Render/XrBatchRender.h"
#include "../../Common/xrDataStruct.cpp"
#include "../../XrNode/Material/CMaterial.h"
#include "../../XrNode/Lighting/CLight.h"

CPool<CRenderGroup> CRenderGroupList::sm_RenderGroupPool ;

CRenderGroupList::CRenderGroupList()
{
}

Void CRenderGroupList::AddBatchRender(CMaterial *pMtl, CBatchRender *pBatchRender)
{
	if( pMtl->GetId() >= m_pRenderGroups.GetCount() ){
		m_pRenderGroups.Append(pMtl->GetId() - m_pRenderGroups.GetCount() + 1, 0);	
	}
	CRenderGroup* pGroup = m_pRenderGroups[pMtl->GetID()];
	if( pGroup ){
		pGroup->m_group.Add(pBatchRender);
	}
	else{
		pGroup = sm_RenderGroupPool.Get();
		m_pRenderGroups[pMtl->GetID()] = pGroup;
		pGroup->m_group.Add(pBatchRender);
		m_pMaterials.Push_back(pMtl);
	}
	//XrHashMap<CMaterial*,CRenderGroup*>::iterator it = m_RenderGroupMap.Find(pMtl);
	//if( it == m_RenderGroupMap.end() ){
	//	it = m_RenderGroupMap.Insert(pMtl,sm_RenderGroupPool.Get());
	//	CRenderGroup& rendergroup = (*(*it));
	//	CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = rendergroup.m_group;
	//	group.Add(pBatchRender);
	//}
	//else{
	//	CRenderGroup& rendergroup = (*(*it));
	//	CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = rendergroup.m_group;
	//	group.Add(pBatchRender);
	//}
}

Void CRenderGroupList::Clear()
{
#if 0
	for( m_pRenderGroups.First(); !m_pRenderGroups.IsDone(); m_pRenderGroups.Next() ){
		CRenderGroup* p = m_pRenderGroups.GetCurrent();
		if( p ){
			sm_RenderGroupPool.Release(p);
			m_pRenderGroups.GetCurrent() = NULL;
		}

	}
	#endif
	m_pRenderGroups.Clear();
	m_pMaterials.Clear();
	//for( XrHashMap<CMaterial*,CRenderGroup*>::iterator it = m_RenderGroupMap.begin();
	//	it != m_RenderGroupMap.end();  ){
	//	sm_RenderGroupPool.Release(*it);
	//}
	//m_RenderGroupMap.Clear();
}

Void CRenderGroupList::Render(CPool<CBatchRender>& renderpool)
{
	CMaterial* pMtl = NULL;
	CBatchRender* pRender = NULL;
	for( m_pMaterials.First(); !m_pMaterials.IsDone(); m_pMaterials.Next()  ){
		pMtl = m_pMaterials.GetCurrent();
		CRenderGroup* rendergroup = m_pRenderGroups[pMtl->GetID()];
		CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = rendergroup->m_group;
		for( group.First(); !group.IsDone(); group.Next()){
			pRender = group.GetCurrent();
			if (!pRender->NeedBlend() && pMtl->IsOpaque()) {
				pRender->Render(pMtl);
				renderpool.Release(pRender);
				group.RemoveCurrent();
			}
		}
		if( !group.GetCount() ){
			sm_RenderGroupPool.Release(rendergroup);
			m_pRenderGroups[pMtl->GetID()] = NULL;
		}
		
	}

	//second pass of rendering blendNode
	for( m_pMaterials.First(); !m_pMaterials.IsDone(); m_pMaterials.Next() ){
		pMtl = m_pMaterials.GetCurrent();
		CRenderGroup* rendergroup = m_pRenderGroups[pMtl->GetID()];
		if( rendergroup ){
			CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = rendergroup->m_group;
			for( group.First(); !group.IsDone(); group.Next()){
				pRender = group.GetCurrent();
			
				pRender->Render(pMtl);
				renderpool.Release(pRender);
				group.RemoveCurrent();
				
			}
			if( !group.GetCount() ){
				sm_RenderGroupPool.Release(rendergroup);
				m_pRenderGroups[pMtl->GetID()] = NULL;
			}
		}
	}

	//m_RenderGroupMap.Clear();
}


Void CRenderGroupList::PreRender(CPool<CBatchRender>& renderpool, CLight* pLight, const XRMat4* view, const XRMat4* proj)
{
	CMaterial* mtl = NULL;
	CBatchRender* pRender = NULL;
	for( m_pMaterials.First(); !m_pMaterials.IsDone(); m_pMaterials.Next()  ){
		mtl = m_pMaterials.GetCurrent();
		CRenderGroup* rendergroup = m_pRenderGroups[mtl->GetID()];
		CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = rendergroup->m_group;
		for( group.First(); !group.IsDone(); group.Next()){
			pRender = group.GetCurrent();
			if (!pRender->NeedBlend()) {
				pRender->PreRender(pLight->GetMaterialRender(mtl), view, proj);
				//renderpool.Release(pRender);
				//group.RemoveCurrent();
			}
		}

		
	}
	
}


CRenderGroup* CRenderGroupList::Find(CMaterial* pMtl)
{
	for( m_pMaterials.First(); !m_pMaterials.IsDone(); m_pMaterials.Next() ){
		if( pMtl == m_pMaterials.GetCurrent() )
			return this->m_pRenderGroups[pMtl->GetId()];
	}
	return NULL;
	//if( m_pMaterials.Empty() || m_pRenderGroups.Empty() )
	//	return NULL;
	//else
	//	return this->m_pRenderGroups[pMtl->GetId()];
}
