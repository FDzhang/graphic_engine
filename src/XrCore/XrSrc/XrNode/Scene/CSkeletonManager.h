#ifndef __CSKELETON_MANAGER_H__
#define __CSKELETON_MANAGER_H__
#include "../../Common/XrInternal.h"
#include "../Animation/CAProperty.h"

class BonePallete {
public:
	class CNode* GetBoneRoot();
	Int32 boneCount;
	Int32 maxInfNum;
	XRMat4 boneInv[MAX_BONE_NUM];
	XRMat4 meshToBoneTransform;
	XRMat4 bones[MAX_BONE_NUM]; 
	class CNode* owner[MAX_BONE_NUM];
};

class CSkeletonManager
{
public:
	CSkeletonManager();

	Int32 AddBonePallete(BonePallete* pPallete);
	BonePallete* GetBonePallete(Int32 id);
	Void Update();
private:
	CLazySlot<BonePallete, 128> m_bonePalletes;
};

#endif  //__CSKELETON_MANAGER_H__
