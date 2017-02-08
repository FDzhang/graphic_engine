#include "CSceneVisitor.h"
#include "CUINode.h"
#include "../CNode.h"
#include "CSceneNode.h"

Void SceneTraverseInfo::Reset()
{
	node = 0;
	transformMatrix = XRMat4::Identity();
	transform.Reset();
}

Int32 CSceneVisitor::isNeedVisit(SceneTraverseInfo& traverseInfo)
{
	return traverseInfo.node->GetEnable();
}

Void CSceneVisitor::visitNode(SceneTraverseInfo& traverseInfo)
{
	//CNode* node = traverseInfo.node;
	//Float32 x,y,z;
	//	
	//x = node->scale.x.Get(), y = node->scale.y.Get(), z=node->scale.z.Get();
	//if (x != 1 || y != 1 || z != 1) {
	//	traverseInfo.ApplyScale(x,y,z);
	//	//traverseInfo.transform.DeltaScale(node->sx.Get(), node->sy.Get(), node->sz.Get());
	//}

	//x = node->position.x.Get(), y = node->position.y.Get(), z=node->position.z.Get();
	//if (x != 0 || y != 0 || z != 0) {
	//	traverseInfo.ApplyTranslation(x,y,z);
	//}
	//x = node->rotation.x.Get(), y = node->rotation.y.Get(), z=node->rotation.z.Get();
	//if (x != 0 || y != 0 || z != 0) {
	//	traverseInfo.ApplyRotation(x,y,z);
	//}

 //   m_continue = TRUE;
	//
	//if (node->isBone()) {
	//	node->m_globalTransform = traverseInfo.transformMatrix;
	//}
	////m_node->AddMeshRender(&traverseInfo);

	////if (layer->GetType() & LayerType_Renderable) {
	////	m_list->UIAddQuad(traverseInfo.x, traverseInfo.y, traverseInfo.z, layer);
	////}
}

Int32 CNodeFinder::isNeedVisit(SceneTraverseInfo& traverseInfo)
{
	return result ? 0 : 1;
}

Void CNodeFinder::visitNode(SceneTraverseInfo& traverseInfo)
{
	CNode* node = traverseInfo.node;
	if (!strcmp(targetName, node->GetName())) {
		result = node;
		m_continue = FALSE;
	}
	else {
		result = 0;
	}
}
