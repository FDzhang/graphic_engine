#ifndef __CSCENE_VISITOR_H__
#define __CSCENE_VISITOR_H__
#include "../../Common/XrInternal.h"
#include "../../Common/XrMathEx.h"
inline Void ApplyRotationMatrix(Float32 x, Float32 y, Float32 z, XRMat4* mat)
{		
		if (z !=0) {
			(*mat) = (*mat) * XRMat4::RotationZ(z);
		}
		if (y !=0) {
			(*mat) = (*mat) *  XRMat4::RotationY(y);
		}

		if (x !=0) {
			(*mat) =  (*mat) * XRMat4::RotationX(x);
		}

}

inline Void ApplyScalingMatrix(Float32 x, Float32 y, Float32 z, XRMat4* mat)
{
	if (x !=1.0 || y !=1.0 || z!= 1.0) {
		(*mat) = XRMat4::Scale(x,y,z)*(*mat);
	}
}


struct SceneTraverseInfo {
    SceneTraverseInfo()
    {
        node = 0;
    }

	Void ApplyTranslation(Float32 x, Float32 y, Float32 z)
	{
		transform.DeltaTranslation(x,y,z);
		transformMatrix = transformMatrix * XRMat4::Translation(x, y, z);//*transformMatrix;
	}

	Void ApplyRotation(Float32 x, Float32 y, Float32 z)
	{
		transform.DeltaRotation(x,y,z);
		ApplyRotationMatrix(x, y, z, &transformMatrix);
	}

	Void ApplyScale(Float32 x, Float32 y, Float32 z)
	{
		transform.DeltaScale(x,y,z);
		ApplyScalingMatrix(x,y,z, &transformMatrix);
	}

	Void Reset();
    class CNode*		node;
    TransformInfo		transform;
	XRMat4			transformMatrix;
};

class CSceneVisitor
{
public:
    CSceneVisitor(class CSceneNode* node)
    {
		m_node = node;
        m_continue = TRUE;
    }

    virtual Boolean isContinue() { return m_continue; }
    virtual Int32 isNeedVisit(SceneTraverseInfo& traverseInfo);
    virtual Void visitNode(SceneTraverseInfo& traverseInfo);

protected:
	CSceneNode* m_node;
	Boolean m_continue;
};

class CNodeFinder : public CSceneVisitor
{
public:
	 CNodeFinder(CSceneNode* node):
	 result(0),
	 CSceneVisitor(node){}
	virtual Int32 isNeedVisit(SceneTraverseInfo& traverseInfo);
	virtual Void visitNode(SceneTraverseInfo& traverseInfo);
	CNode* GetResult() { return result; }
	Void SetTargetName(ConstString name) {
		targetName = (String)name;
	}
private:
	String targetName;
	CNode* result;
};

#endif  //__CSCENE_VISITOR_H__

