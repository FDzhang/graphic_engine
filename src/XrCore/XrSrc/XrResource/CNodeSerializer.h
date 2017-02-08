#ifndef _CXR_NODE_SERIALIZER_H
#define _CXR_NODE_SERIALIZER_H
#include "../Common/XrInternal.h"
#include "../XrNode/CNode.h"
#include "CFileHandler.h"



#define NodeTableNum 512

struct CNodeSlot
{
	CNode* node;
	int slotId; //slot id of matrix pallete
    Int32		hashA;
    Int32		hashB;
};

class CNodeMap
{
public:
	CNodeMap();
	~CNodeMap();
	Int32 AddNode(CNode* node);
	CNode* QueryNodeByString(String name, Int32* slotId);
private:

	CNodeSlot*			m_map[NodeTableNum];
};


class CNodeSerializer
{
public:
	CNodeSerializer();
	~CNodeSerializer();
	CNode* LoadFromFile(ConstString fileName, class CSceneNode* pScene, Boolean forceUseNormal = TRUE);
	xr_state SaveToFile(String fileName, CNode* node);

	xr_state ReadHeader();
	xr_state LoadMesh();
	xr_state LoadMaterial();
	xr_state LoadBoneSet();
	xr_state LoadAnimation();
	xr_state LoadNodeHierarchy();
	xr_state ProcessStack();

	Boolean WriteNode(CNode* node);
	Void CleanUp();
	Boolean OnError();
	xr_state SetNodeAnimation(CNode* node, Int32 id);

protected:

	Void CalculateTangentArray(long vertexAttributeCount, const XRVec3 *vertex, const Float32 *attribute, long triangleCount, const Int32 *indexBuffer, XRVec4 *tangent);

	struct processElement {
		CNode* node;
		Int32 meshId;
		Int32 mtlId;
		processElement& operator=(const processElement& rhs)
		{
			node = rhs.node;
			meshId = rhs.meshId;
			mtlId = rhs.mtlId;
			return *this;
		}
	};
	xr_state AddMeshMaterial(Int32 id, Int32 mtlId, CNode* node);
	Void FillVertexBufferWI(void* buffer, XRVertexLayout layout, MeshBlock* mesh, Int32 *skeletonID, Int32* maxInf);
	Void FillVertexBufferPNT(void* buffer, Int32 stride, MeshBlock* mesh);
	Void FillVertexBufferPNBT(void* buffer, Int32 stride, MeshBlock* mesh);
	Void FillIndexBuffer(void* buffer, MeshBlock* mesh);
	Void FillMeshBoneIndex();
	Int32 GetDefaultMaterial(Int32 meshId, XRVertexLayout layout);
	Void SetMeshTransformMatrix(CNode* node, Int32 id);
	Int32	verInfo;
	CFileHandler file;

	UInt32  nodeBlockOffset;
	UInt32  meshBlockOffset;
	UInt32  materialBlockOffset;
	UInt32  boneSetBlockOffset;
	UInt32  animationBlockOffset;

	MeshBlock*  meshes;
	MaterialBlock*  mtls;
	Int32*  mtlIds;
	BoneSet*  bones;

	Int32 BoneNodeMesh;
	Int32 defaultMtlPNT;
	Int32 defaultMtlPNTWI;
	Int32 defaultMtlPNBT;
	Int32 defaultMtlPNBTWI;
	Int32 meshCount;
	Int32 materialCount;
	Int32 BonSetCount;

	Boolean loadState;
	Boolean useNormalMap;
	CSceneNode* scene;
	CNode* rootNode;
	class CAnimationStack* m_stack;

	CNodeMap m_nodeMap;
	CStack<processElement, 1024> processStack;
	UInt32  animationStackId;
};

#endif //_CXR_NODE_SERIALIZER_H