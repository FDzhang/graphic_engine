#include "CSkeletonManager.h"
#include "../CNode.h"

CNode* BonePallete::GetBoneRoot() {
	if (boneCount<1) return 0;
	CNode* temp = owner[0];
	while (temp->GetSuper()) {
		if(!temp->GetSuper()->isBone()) break;
		temp = temp->GetSuper();
	}
	return temp;
}

CSkeletonManager::CSkeletonManager()
{
	for (m_bonePalletes.First();!m_bonePalletes.IsDone();m_bonePalletes.Next()) {
		BonePallete* p = m_bonePalletes.GetCurrent();
		delete p->bones;
		delete p->owner;
		delete p;
	}
};

Int32 CSkeletonManager::AddBonePallete(BonePallete* pPallete)
{
	BonePallete* pallete = new BonePallete;
	pallete->boneCount  = pPallete->boneCount;
	pallete->maxInfNum = pPallete->maxInfNum;
	XrMemcpy(&pallete->bones[0], &pPallete->bones[0], sizeof(XRMat4)*pPallete->boneCount);
	XrMemcpy(&pallete->owner[0], &pPallete->owner[0], 4*pPallete->boneCount);
	XrMemcpy(&pallete->meshToBoneTransform, &pPallete->meshToBoneTransform, 4*16);
	XrMemcpy(&pallete->boneInv, &pPallete->boneInv, 4*16*pPallete->boneCount);

	return m_bonePalletes.Add(pallete);
}

BonePallete* CSkeletonManager::GetBonePallete(Int32 id)
{
	return m_bonePalletes.Get(id);
}

Void CSkeletonManager::Update()
{
	CNode* node;
	for (m_bonePalletes.First();!m_bonePalletes.IsDone();m_bonePalletes.Next()) {
		BonePallete* pallete = m_bonePalletes.GetCurrent();
		for (Int32 i=0;i<pallete->boneCount;i++) {
			node = pallete->owner[i];
			char* name = node->GetName();
			//if (!strcmp(node->GetName(), "root ground")) {
			//	printf("");
			//}
			//XRMatrixMultiply(pallete->bones[i],  (*node->m_boneInv),node->m_globalTransform );
			pallete->bones[i] = node->m_globalTransform * pallete->boneInv[i] * pallete->meshToBoneTransform;
			//pallete->bones[i] = XRMat4::Identity();
		}
	}
}
