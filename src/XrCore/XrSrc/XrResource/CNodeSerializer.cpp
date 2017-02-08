#include "CNodeSerializer.h"
#include "../XrNode/Scene/CSceneNode.h"
#include "../Common/xrDataStruct.cpp"
#include "../Common/stringHash.h"
#include "../XrCore/CAnimationManager.h"
//#define SHOW_BONE
#define NODE_SIZE 0.2
CHAR diffuseDefualt[] = "00tex_master.BMP";
Void ChangeFileSuffix(String dst, String suffix)
{
	size_t namelen = strlen(dst);
	if (namelen<4) return;
	dst[namelen-3]=suffix[0];
	dst[namelen-2]=suffix[1];
	dst[namelen-1]=suffix[2];
}

CNodeMap::CNodeMap()
{
    memset(m_map, 0, 4*NodeTableNum);
}

CNodeMap::~CNodeMap()
{
    Int32 i=0;

    while (i < NodeTableNum)
    {
		SAFE_DELETE(m_map[i]);
        i++;
    }
}

Int32 CNodeMap::AddNode(CNode* node)
{
	Int32 tid;
	if (QueryNodeByString(node->GetName(), &tid)) {
		return -1;
	}
	else {
		if (tid < 0) {
			return -1;
		}

		m_map[tid]->node = node;
		return tid;
	}
}

CNode* CNodeMap::QueryNodeByString(String name, Int32* slotId)
{
    int nHash = HashString(name, HASH_OFFSET),
        nHashA = HashString(name, HASH_A),
        nHashB = HashString(name, HASH_B),
        nHashStart = nHash % NodeTableNum;

    if (nHashStart<0) nHashStart+=NodeTableNum;			//fix minus case
    int nHashPos = nHashStart;

	while (m_map[nHashPos]) {
		if (m_map[nHashPos]->hashA == nHashA && m_map[nHashPos]->hashB == nHashB) {
			*slotId = nHashPos;
			return m_map[nHashPos]->node;
		}
		else {
			nHashPos = (nHashPos + 1) % NodeTableNum;
		}

		if (nHashPos == nHashStart) {
			*slotId = -1;
			return 0;
		}
	}

	m_map[nHashPos] = new CNodeSlot;
	m_map[nHashPos]->hashA = nHashA;
	m_map[nHashPos]->hashB = nHashB;
	*slotId = nHashPos;
	return 0;

}

CNodeSerializer::CNodeSerializer()
{
	mtls = 0;
	mtlIds = 0;
	meshes = 0;
	bones = 0;
	meshCount=0;
	materialCount=0;
	BonSetCount=0;
	loadState = FALSE;
	defaultMtlPNT = -1;
	defaultMtlPNTWI = -1;
	defaultMtlPNBT = -1;
	defaultMtlPNBTWI = -1;
	animationStackId = -1;
	useNormalMap = FALSE;
}

CNodeSerializer::~CNodeSerializer()
{
	CleanUp();
}

Void CNodeSerializer::CleanUp()
{
	Int32 i,j;
	for (i=0;i<meshCount;i++) {
		delete meshes[i].controlPointData;
		delete meshes[i].vertexAttributeData;
		delete meshes[i].indexData;
	}

	for (i=0;i<BonSetCount;i++) {
		BoneSet* boneset = &bones[i];
		for (j=0;j<boneset->boneCount;j++) {
			Bone* bone = &boneset->bone[j];
			delete bone->index;
			delete bone->weight;
		}
		delete boneset->bone;
	}

	SAFE_DELETE(meshes);
	SAFE_DELETE(mtls);
	SAFE_DELETE(bones);

	meshCount=0;
	materialCount=0;
	BonSetCount=0;
	loadState = FALSE;
}

xr_state CNodeSerializer::SaveToFile(String fileName, CNode* node)
{
	return XR_OK;
}

Void CNodeSerializer::FillMeshBoneIndex()
{
	for (Int32 i=0; i<BonSetCount;i++) {
		meshes[bones[i].meshIndex].meshBoneIndex = i;
	}
}

CNode* CNodeSerializer::LoadFromFile(ConstString fileName, CSceneNode* pScene, Boolean forceUseNormal)
{
	scene = pScene;
	useNormalMap |= forceUseNormal;

	if (XRFAILED(file.readOpen(fileName))) return 0;

	if (XRFAILED(ReadHeader())) goto _Exit;
	
	if (XRFAILED(LoadMaterial())) goto _Exit;

	if (XRFAILED(LoadMesh())) goto _Exit;

	if (XRFAILED(LoadBoneSet())) goto _Exit;

	if (XRFAILED(LoadAnimation())) goto _Exit;

	FillMeshBoneIndex();

	if (XRFAILED(LoadNodeHierarchy())) goto _Exit;

	if (XRFAILED(ProcessStack())) goto _Exit;

	loadState = TRUE;
	return rootNode;

_Exit:
	CleanUp();
	return 0;
}

xr_state CNodeSerializer::ReadHeader()
{
	UInt32 out;
	file.read(&out, 4, 1);
	if (!(out == Header_Sig)) return XR_FAILED;

	file.read(&out, 4, 1);
	verInfo = out;

	file.read(&out, 4, 1);
	meshBlockOffset = out;

	file.read(&out, 4, 1);
	materialBlockOffset = out;

	file.read(&out, 4, 1);
	boneSetBlockOffset = out;

	file.read(&out, 4, 1);
	animationBlockOffset = out;

	nodeBlockOffset = file.tell();

	return XR_OK;
}

static APType AP[9]={AP_X,AP_Y,AP_Z,AP_RX,AP_RY,AP_RZ,AP_SX,AP_SY,AP_SZ};
xr_state CNodeSerializer::LoadAnimation()
{

	CAnimationLayer* pLayer;
	CAnimationNode*  pNode;
	int i,j,k,l,out,nodeNum,frameNum,animationLayerNum,curveTypes,type,val,time,nodeIndex;
	float maxDuration=0;
	file.seekFromStart(animationBlockOffset);

	file.read(&out, 4, 1);
	if (!(out == Animation_Block_Sig)) return XR_FAILED;
	file.read(&animationLayerNum, 4, 1);
	if (!animationLayerNum) return XR_OK;
	animationStackId = XRAM->CreateAnimationStack(&m_stack);
	m_stack->SetLayerCount(animationLayerNum);
	for (i=0;i<animationLayerNum;i++) {
		file.read(&out, 4, 1);
		if (!(out == Animation_Layer_Sig)) goto CleanUp;
		pLayer = m_stack->GetLayer(i);
		file.read(&nodeNum, 4, 1);
		pLayer->nodeNum = nodeNum;
		for (j=0;j<nodeNum;j++) {
			file.read(&out, 4, 1);
			if (!(out == Animation_Node_Sig)) goto CleanUp;
			file.read(&nodeIndex, 4, 1);
			file.read(&curveTypes, 4, 1);
			pNode = &pLayer->nodes[nodeIndex];
			pNode->propertys = curveTypes;
			for (k=0;k<9;k++) {
				if (AP[k]&curveTypes) {
					file.read(&out, 4, 1);
					if (!(out == Animation_Curve_Sig)) goto CleanUp;
					file.read(&type, 4, 1);
					file.read(&frameNum, 4, 1);
					pNode->curves[k].frameNum = frameNum;
					pNode->curves[k].type = type;
					pNode->curves[k].frames = new CAnimationFrame[frameNum];
					for (l=0;l<frameNum;l++) {
						file.read(&pNode->curves[k].frames[l].time, 4, 1);
						file.read(&pNode->curves[k].frames[l].value, 4, 1);
						if (maxDuration<pNode->curves[k].frames[l].time) {
							maxDuration = pNode->curves[k].frames[l].time;
						}
					}
				}
			}
		}
		pLayer->duration = maxDuration;
	}
	m_stack->Start();
	return XR_OK;

CleanUp:
	xrprintf("");
	return XR_OK;
}

xr_state CNodeSerializer::LoadMesh()
{
	UInt32 out,size,tc=0;
	file.seekFromStart(meshBlockOffset);
	file.read(&out, 4, 1);
	if (!(out == Mesh_Block_Sig)) return XR_FAILED;

	file.read(&out, 4, 1);
	meshCount = out;
	meshes = new MeshBlock[meshCount];
	for (Int32 i=0;i<meshCount;i++) {
		file.read(&out, 4, 1);
		if (!(out == Mesh_Sig)) return XR_FAILED;
		//meshes[i].vertexFormat = XR_VERTEX_LAYOUT_PNT;

		file.read(&out, 4, 1);
		file.read(meshes[i].name, 1, out);

		file.read(&meshes[i].vaType, 4, 1);


		file.read(&meshes[i].controlPointCount, 4, 1);
		size = meshes[i].controlPointCount * 3*4;
		meshes[i].controlPointData = (Float32*)new UInt8[size];
		file.read(meshes[i].controlPointData, 3*4, meshes[i].controlPointCount);

		file.read(&meshes[i].vertexAttributeCount, 4, 1);
		size = meshes[i].vertexAttributeCount * GetVASize(meshes[i].vaType);
		meshes[i].vertexAttributeData = (Float32*)new UInt8[size];
		file.read(meshes[i].vertexAttributeData, GetVASize(meshes[i].vaType), meshes[i].vertexAttributeCount);


		file.read(&meshes[i].indexCount, 4, 1);
		size = meshes[i].indexCount * 4*2;
		meshes[i].indexData = (Int32*)new UInt8[size];
		tc+=meshes[i].indexCount/3;
		file.read(meshes[i].indexData, 4*2, meshes[i].indexCount);
		meshes[i].meshBoneIndex = -1;
	}
	return XR_OK;
}

xr_state CNodeSerializer::LoadMaterial()
{
	UInt32 out, size, i;
	file.seekFromStart(materialBlockOffset);
	file.read(&out, 4, 1);
	if (!(out == Material_Block_Sig)) return XR_FAILED;

	file.read(&out, 4, 1);
	materialCount = out;
	if (!materialCount) {

		return XR_OK;
	}
	mtls = new MaterialBlock[materialCount];
	mtlIds = new Int32[materialCount];

	for (i=0;i<materialCount;i++) {
		file.read(&out, 4, 1);
		if (!(out == Material_Sig)) return XR_FAILED;
		file.read(&out, 4, 1);
		file.read(mtls[i].name, 1, out);

		file.read(mtls[i].ambient, 4, 3);
		file.read(mtls[i].diffuse, 4, 3);
		file.read(mtls[i].specular, 4, 3);
		file.read(mtls[i].emissive, 4, 3);
		file.read(&mtls[i].transparency, 4, 1);
		file.read(&mtls[i].shininess, 4, 1);

		//diffuse
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].diffuseTex, 1, size);

		//normal
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].normalTex, 1, size);
		if (mtls[i].normalTex[0]) {
			useNormalMap |= TRUE;
		}

		//specular
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].specularTex, 1, size);

		//roughness
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].roughnessTex, 1, size);

		//ambient
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].ambientTex, 1, size);

		//emissive
		file.read(&size, sizeof(int), 1);
		file.read(mtls[i].emissiveTex, 1, size);
	}
	for (i=0;i<materialCount;i++) {
		mtlIds[i] = -1;
	}
	return XR_OK;
}

xr_state CNodeSerializer::LoadBoneSet()
{
	UInt32 out, boneCount, linkedCount;
	file.seekFromStart(boneSetBlockOffset);
	file.read(&out, 4, 1);
	if (!(out == BoneSet_Block_Sig)) return XR_FAILED;

	file.read(&out, 4, 1);
	BonSetCount = out;
	if (out==0) return XR_OK;
	bones = new BoneSet[BonSetCount];

	for (Int32 i=0;i<BonSetCount;i++) {
		file.read(&out, 4, 1);
		if (!(out == BoneSet_Sig)) return XR_FAILED;
		file.read(&bones[i].meshIndex, 4, 1);
		file.read(&boneCount, 4, 1);
		bones[i].boneCount = boneCount;
		bones[i].bone = new Bone[boneCount];
		for (Int32 j=0;j<boneCount;j++) {
			file.read(&out, 4, 1);
			if (!(out == Bone_Sig)) return XR_FAILED;

			file.read(&out, 4, 1);
			file.read(bones[i].bone[j].name, 1, out);

			file.read(&bones[i].bone[j].meshTrans, 4, 16);
			file.read(&bones[i].bone[j].bindPos, 4, 16);
			file.read(&linkedCount, 4, 1);
			bones[i].bone[j].index = new Int32[linkedCount];
			bones[i].bone[j].weight = new Float32[linkedCount];
			bones[i].bone[j].linkedVertexCount = linkedCount;
			for (int k=0;k<linkedCount;k++) {
				file.read(&bones[i].bone[j].index[k], 4, 1);
				file.read(&bones[i].bone[j].weight[k], 4, 1);
			}
		}
	}
	
	BoneNodeMesh = scene->CreateMesh(ModelType_Cube, NODE_SIZE,NODE_SIZE,NODE_SIZE, 0, 0);
	return XR_OK;
}

struct WI{
	UInt8 weight[4];
	UInt8 index[4];
};
struct PNTWI{
	Float32 position[3];
	Float32 Normal[3];
	Float32 Uv[2];
	UInt8 weight[4];
	UInt8 index[4];
};
struct PNBTWI{
	Float32 position[3];
	Float32 Normal[3];
	Float32 Tangent[4];
	Float32 Uv[2];
	UInt8 weight[4];
	UInt8 index[4];
};

Void FillVertexWI(void* buffer, Int32* vertexBoneSlot, Float32 weight, Int32 vertexIndex, Int32 boneIndex, int* maxInf)
{

	WI* vertex = (WI*)buffer;
	if (vertexBoneSlot[vertexIndex]>3) {
		xrprintf("error maxinf count above 4\n");
		return;
	}
	vertex[vertexIndex].index[vertexBoneSlot[vertexIndex]] = boneIndex;
	vertex[vertexIndex].weight[vertexBoneSlot[vertexIndex]] = weight*255;
	vertexBoneSlot[vertexIndex]++;
	if (*maxInf<vertexBoneSlot[vertexIndex]) *maxInf = vertexBoneSlot[vertexIndex];
}

Void CNodeSerializer::FillVertexBufferWI(void* buffer, XRVertexLayout layout, MeshBlock* mesh, Int32 *skeletonID, Int32* maxInf)
{
	Int32* vertexBoneSlot;
	BonePallete pallete;
	CNode* boneNode;
	Int32 id;
	
	BoneSet* boneSet = &bones[mesh->meshBoneIndex];
	if (boneSet->boneCount > MAX_BONE_NUM) {
		boneSet->boneCount = MAX_BONE_NUM;
	}
	pallete.boneCount = boneSet->boneCount;
	//pallete.bones = new XRMat4[boneSet->boneCount];
	//pallete.owner = new CNode*[boneSet->boneCount];
	vertexBoneSlot = new Int32[mesh->vertexAttributeCount];
	WI* WIbuffer = new WI[mesh->controlPointCount];
	memset(WIbuffer, 0, sizeof(WI)*mesh->controlPointCount);
	PNTWI* dstBufferPNTWI = (PNTWI*)buffer;
	PNBTWI* dstBufferPNBTWI = (PNBTWI*)buffer;
	memset(vertexBoneSlot, 0, 4*mesh->vertexAttributeCount);

	for (Int32 i=0;i<boneSet->boneCount;i++) {
		Bone* bone = &boneSet->bone[i];
		boneNode = m_nodeMap.QueryNodeByString(bone->name, &id);
		pallete.owner[i] = boneNode;
		pallete.bones[i] = XRMat4::Identity();
		for (Int32 j=0;j<bone->linkedVertexCount;j++) {
			FillVertexWI(WIbuffer, vertexBoneSlot, bone->weight[j], bone->index[j], i, maxInf);
		}
		XRMat4 trans(bone->meshTrans),bind(bone->bindPos);

		pallete.meshToBoneTransform = trans;
		pallete.boneInv[i] = bind.inverse();
	}

	for (Int32 i=0;i<mesh->indexCount;i++) {
		for (Int32 j=0;j<4;j++) {

			if (layout & XR_VERTEX_LAYOUT_B) {
				dstBufferPNBTWI[mesh->indexData[i*2+1]].index[j] = WIbuffer[mesh->indexData[i*2+0]].index[j];
				dstBufferPNBTWI[mesh->indexData[i*2+1]].weight[j] = WIbuffer[mesh->indexData[i*2+0]].weight[j];
			}
			else {
				dstBufferPNTWI[mesh->indexData[i*2+1]].index[j] = WIbuffer[mesh->indexData[i*2+0]].index[j];
				dstBufferPNTWI[mesh->indexData[i*2+1]].weight[j] = WIbuffer[mesh->indexData[i*2+0]].weight[j];
			}
		}
	}
	pallete.maxInfNum = *maxInf;
	*skeletonID = scene->CreateBonePallete(&pallete);
	
	delete[] vertexBoneSlot;
	delete[] WIbuffer;

	if (layout & XR_VERTEX_LAYOUT_B) FillVertexBufferPNBT((Float32*)buffer, XR_VERTEX_SIZE(XR_VERTEX_LAYOUT_PNBTWI), mesh);
	else FillVertexBufferPNT((Float32*)buffer, XR_VERTEX_SIZE(XR_VERTEX_LAYOUT_PNTWI), mesh);

}

void FillPNT(Float32* dst, Float32* cpSrc, Float32* vaSrc)
{
	dst[0]=cpSrc[0];dst[1]=cpSrc[1];dst[2]=cpSrc[2];//position
	dst[3]=vaSrc[0];dst[4]=vaSrc[1];dst[5]=vaSrc[2];//normal
	dst[6]=vaSrc[3];dst[7]=vaSrc[4];//uv
}

void FillPNBT(Float32* dst, Float32* cpSrc, Float32* vaSrc,  Float32* tanSrc)
{
	dst[0]=cpSrc[0];dst[1]=cpSrc[1];dst[2]=cpSrc[2];//position
	dst[3]=vaSrc[0];dst[4]=vaSrc[1];dst[5]=vaSrc[2];//normal
	dst[6]=tanSrc[0];dst[7]=tanSrc[1];dst[8]=tanSrc[2];dst[9]=tanSrc[3];//tangent
	dst[10]=vaSrc[3];dst[11]=vaSrc[4];//uv

	//dst[0]=cpSrc[0];dst[1]=cpSrc[1];dst[2]=cpSrc[2];//position
	//dst[3]=0;dst[4]=0;dst[5]=0;//normal
	//dst[6]=0;dst[7]=0;dst[8]=0;//tangent
	//dst[9]=0;dst[10]=0;//uv

}

void CNodeSerializer::FillVertexBufferPNT(void* buffer, Int32 stride, MeshBlock* mesh)
{
	Float32* dst;
	Float32* cpSrc = mesh->controlPointData;
	Float32* vaSrc = mesh->vertexAttributeData;
	Int32 i,cpid,vaid;
	for (i=0;i<mesh->indexCount; i++) {
		cpid = mesh->indexData[i*2+0];
		vaid = mesh->indexData[i*2+1];
		cpSrc = mesh->controlPointData+cpid*3;
		vaSrc = mesh->vertexAttributeData+vaid*5;
		((UInt8*&)dst) = (UInt8*)buffer+stride*vaid;
		FillPNT(dst, cpSrc, vaSrc);
	}
}
void CNodeSerializer::FillVertexBufferPNBT(void* buffer, Int32 stride, MeshBlock* mesh)
{
	Float32* dst;
	Float32* cpSrc = mesh->controlPointData;
	Float32* vaSrc = mesh->vertexAttributeData;
	Float32 pos1[3],pos2[3],pos3[3];
	Float32 normal1[3],normal2[3],normal3[3];
	Float32 tangent[3];
	Float32 uv[3];
	XRVec4 *tanSrc = new XRVec4[mesh->vertexAttributeCount * 2];
	Int32 i,cpid,vaid,triangleCount = mesh->indexCount/3;
	if (mesh->indexCount%3!=0) {
		xrprintf("triangle count error!\n");
	}

	CalculateTangentArray(mesh->vertexAttributeCount, (XRVec3*)cpSrc, vaSrc, triangleCount, mesh->indexData, tanSrc);
	for (i=0;i<mesh->indexCount; i++) {
		cpid = mesh->indexData[i*2+0];
		vaid = mesh->indexData[i*2+1];
		cpSrc = mesh->controlPointData+cpid*3;
		vaSrc = mesh->vertexAttributeData+vaid*5;
		((UInt8*&)dst) = (UInt8*)buffer+stride*vaid;
		FillPNBT(dst, cpSrc, vaSrc, (Float32*)(&tanSrc[vaid]));
	}
	delete tanSrc;
	//for (i=0;i<triangleCount; i++) {

	//}
}

Void CNodeSerializer::FillIndexBuffer(void* buffer, MeshBlock* mesh)
{
    UInt16* dst = (UInt16*)buffer;
	Int32* src = mesh->indexData;
	for (Int32 i=0;i<mesh->indexCount; i++) {
		dst[i] = src[i*2+1];
	}
}

Void CNodeSerializer::SetMeshTransformMatrix(CNode* node, Int32 id)
{
	XRMat4 scale,rotation,translation, boneTrans;

	//node->GetScalingMatrix(&scale);
	//node->GetRotationMatrix(&rotation);
	//node->GetTranslationMatrix(&translation);
	node->ResetPosition();
	 
	//BonePallete* pallete = scene->GetBonePallete(id);
	//CNode* boneRoot = pallete->GetBoneRoot();

	//pallete->meshToBoneTransform = translation * rotation * scale;
	//pallete->meshToBoneTransform = XRMat4::Identity();
	//boneRoot->GetScalingMatrix(&scale);
	//boneRoot->GetRotationMatrix(&rotation);
	//boneRoot->GetTranslationMatrix(&translation);
	//boneRoot->ResetPosition();
	//boneTrans = translation * rotation * scale;

	//pallete->meshToBoneTransform = pallete->meshToBoneTransform;
}

xr_state CNodeSerializer::AddMeshMaterial(Int32 id, Int32 mtlId, CNode* node)
{
	XRVertexLayout layout=XR_VERTEX_LAYOUT_NULL;
	Int32 skeletonID=-1, maxInf=0,temp;
	MeshBlock* meshBlock = &meshes[id];
	UInt8* vbuffer, *ibuffer;
	//meshBlock->meshBoneIndex = -1; 
	if (useNormalMap) {
		layout = XR_VERTEX_LAYOUT_B;
	}
	if (meshBlock->meshBoneIndex != -1) {
		temp = layout | XR_VERTEX_LAYOUT_PNTWI;
		layout = (XRVertexLayout)temp;
		vbuffer = new UInt8[XR_VERTEX_SIZE(layout) * meshBlock->vertexAttributeCount];
		FillVertexBufferWI(vbuffer, layout, meshBlock, &skeletonID, &maxInf);
	}
	else {
		temp = layout | XR_VERTEX_LAYOUT_PNT;
		layout = (XRVertexLayout)temp;
		vbuffer =new UInt8[XR_VERTEX_SIZE(layout) * meshBlock->vertexAttributeCount];
		Int32 stride = XR_VERTEX_SIZE(layout);
		if (layout & XR_VERTEX_LAYOUT_B) FillVertexBufferPNBT(vbuffer, stride, meshBlock);
		else FillVertexBufferPNT(vbuffer, stride, meshBlock);
	}
	ibuffer = new UInt8[2* meshBlock->indexCount];
	FillIndexBuffer(ibuffer, meshBlock);

	CMesh* mesh = new CMesh();
	mesh->SetupVB(vbuffer, layout, meshBlock->vertexAttributeCount, XR_BUFFER_STATIC);
	mesh->SetupIB(ibuffer, 2* meshBlock->indexCount, XR_BUFFER_STATIC);
	if (skeletonID!=-1) {
		mesh->SetBonePalleteId(skeletonID);
		SetMeshTransformMatrix(node, skeletonID);
	}
	Int32 meshId = scene->AddMesh(mesh);

	Int32 mId;
	if (!mtlIds) {
		mId = GetDefaultMaterial(meshId, layout);
		//node->SetMaterial(GetDefaultMaterial(meshId, layout));
	}
	else {
		if (mtlIds[mtlId] == -1) {
			//ChangeFileSuffix(mtls[mtlId].diffuseTex, "PNG");
			if (useNormalMap) mtls[mtlId].type = Material_Rigid_Bump;
			else mtls[mtlId].type = Material_Rigid_Texture;
			mtlIds[mtlId] = scene->CreateMaterialEx(&mtls[mtlId], meshId);
		}
		mId = mtlIds[mtlId];//node->SetMaterial(mtlIds[mtlId]);
	}
	node->AddDrawable(scene->GetMeshObject(meshId), scene->UseMaterialObject(mId));

	delete(vbuffer);
	delete(ibuffer);
	return XR_OK;
}

Int32 CNodeSerializer::GetDefaultMaterial(Int32 meshId, XRVertexLayout layout)
{
	MaterialBlock  mtl;
	if (layout == XR_VERTEX_LAYOUT_PNT) {
		if (-1 == defaultMtlPNT) {
			mtl.SetNull();
			strcpy(mtl.diffuseTex, diffuseDefualt);
			mtl.type = Material_Rigid_Texture;
			defaultMtlPNT = scene->CreateMaterialEx(&mtl, meshId);
		}
		return defaultMtlPNT;
	}
	else if (layout == XR_VERTEX_LAYOUT_PNTWI){
		if (-1 == defaultMtlPNTWI) {
			mtl.SetNull();
			strcpy(mtl.diffuseTex, diffuseDefualt);
			mtl.type = Material_Skinned_Texture;
			defaultMtlPNTWI = scene->CreateMaterialEx(&mtl, meshId);
		}
		return defaultMtlPNTWI;
	}
	else if (layout == XR_VERTEX_LAYOUT_PNBT) {
		if (-1 == defaultMtlPNT) {
			mtl.SetNull();
			strcpy(mtl.diffuseTex, diffuseDefualt);
			mtl.type = Material_Rigid_Bump;
			defaultMtlPNBT = scene->CreateMaterialEx(&mtl, meshId);
		}
		return defaultMtlPNBT;
	}
	else if (layout == XR_VERTEX_LAYOUT_PNBTWI){
		if (-1 == defaultMtlPNTWI) {
			mtl.SetNull();
			strcpy(mtl.diffuseTex, diffuseDefualt);
			mtl.type = Material_Skinned_Bump;
			defaultMtlPNBTWI = scene->CreateMaterialEx(&mtl, meshId);
		}
		return defaultMtlPNBTWI;
	}
	else return -1;

}

Void testMtx()
{
	XRMat4 translation = XRMat4::Translation(0,0,0);
	XRMat4 scale = XRMat4::Scale(0.393701, 0.393701, 0.393701);
	XRMat4 rotX = XRMat4::RotationX(-90.000000);
	XRMat4 trans =  rotX * translation * scale;
}

xr_state CNodeSerializer::SetNodeAnimation(CNode* node, Int32 id)
{
	if (id==-1) return XR_OK;
	Int32 i, count = m_stack->GetLayerCount();
	CAnimationLayer* pLayer;
	CAnimationNode* pNode;
	for (i=0;i<count;i++) {
		pLayer = m_stack->GetLayer(i);
		pLayer->nodes[id].pTarget = node;
	}
	return XR_OK;
}

Boolean CNodeSerializer::WriteNode(CNode* node)
{
	Int32 out,size,meshId,mtlId,bone,i,meshCnt,animationNodeId;
	XRMat4 scale,translation,rotation;
	CHAR byte;
	CHAR name[128];
	CNode* newNode, *tempNode;
	Float32 outVec[3];
	file.read(&size, 4, 1);
	file.read(name, 1, size);
	node->SetName(name);

	//translation
	file.read(outVec, 4, 3);
	node->position.Set(outVec[0], outVec[1], outVec[2]);

	//rotation
	file.read(outVec, 4, 3);
	node->rotation.Set(Deg2Rad(outVec[0]), Deg2Rad(outVec[1]), Deg2Rad(outVec[2]));
	file.read(outVec, 4, 3);
	node->SetPreRotation(Deg2Rad(outVec[0]), Deg2Rad(outVec[1]), Deg2Rad(outVec[2]));
	file.read(outVec, 4, 3);
	node->SetPostRotation(Deg2Rad(outVec[0]), Deg2Rad(outVec[1]), Deg2Rad(outVec[2]));

	//scale
	file.read(outVec, 4, 3);
	node->scale.Set(outVec[0], outVec[1], outVec[2]);

	file.read(&animationNodeId, 4, 1);
	SetNodeAnimation(node, animationNodeId);

	file.read(&meshCnt, 4, 1);

	for(i=0;i<meshCnt;i++) {
		//meshIndex
		file.read(&meshId, 4, 1);
		//mtlIndex
		file.read(&mtlId, 4, 1);
		processElement element;
		element.meshId = meshId;
		element.mtlId = mtlId;
		element.node = node;
		processStack.Push(element);
	}

	//isBone
	file.read(&bone, 4, 1);

	//node->GetScalingMatrix(&scale);
	//node->GetRotationMatrix(&rotation);
	//XRMat4 inv = rotation.inverse();
	//node->GetTranslationMatrix(&translation);
	//trans = (*parentTrans) * translation * rotation * scale;

	if (bone>=0) {
		if (m_nodeMap.AddNode(node)<0) return OnError();
		//node->m_boneInv = new XRMat4;
		//*node->m_boneInv = trans.inverse();
		node->m_boneType = bone;
#ifdef SHOW_BONE
		node->SetMesh(BoneNodeMesh);
		node->SetMaterial(GetDefaultMaterial(BoneNodeMesh, XR_VERTEX_LAYOUT_PNT));
#endif
		node->SetVisible(FALSE);
	}

	file.read(&byte, 1, 1);
	if (byte=='{') {
		newNode = new CNode(scene);
		scene->AddNodeToSlot(newNode);
		//if (newNode->GetName()) {
		//	return FALSE;
		//}
		node->AppendAsChild(newNode);
		if (!WriteNode(newNode)) return OnError();
		file.read(&byte, 1, 1);
	}

	while (byte=='{') {
		tempNode = new CNode(scene);
		scene->AddNodeToSlot(newNode);
		newNode->Append(tempNode);
		if (!WriteNode(tempNode)) return OnError();
		//newNode = tempNode;
		file.read(&byte, 1, 1);
	}

	if  (byte=='}') {
		return TRUE;
	}
	else {
		return OnError();
	}
}

Boolean CNodeSerializer::OnError()
{
	return FALSE;
}

xr_state CNodeSerializer::LoadNodeHierarchy()
{
	UInt32 out,size;
	CHAR byte;
	file.seekFromStart(nodeBlockOffset);
	file.read(&out, 4, 1);
	if (!(out == Scene_Block_Sig)) return XR_FAILED;

	file.read(&byte, 1, 1);
	if (byte=='{') {
		CNode* node = new CNode(scene);
		if (!WriteNode(node)) {
			rootNode = 0;
		}
		else {
			rootNode = node;
		}
	}
	else rootNode = 0;

	if (rootNode) return XR_OK;
	else return XR_FAILED;
}

xr_state CNodeSerializer::ProcessStack()
{
	processElement element;
	while(processStack.Pop(element)) {
		AddMeshMaterial(element.meshId, element.mtlId, element.node);
	}
	return XR_OK;
}

void CNodeSerializer::CalculateTangentArray(long vertexAttributeCount, const XRVec3 *vertex, const Float32* attribute, long triangleCount, const Int32 *indexBuffer, XRVec4 *tangent)
{
    XRVec3 *tan1 = new XRVec3[vertexAttributeCount * 2];
    XRVec3 *tan2 = tan1 + vertexAttributeCount;
    memset(tan1, 0, vertexAttributeCount * sizeof(XRVec3) * 2);
    for (long a = 0; a < triangleCount; a++)
    {
        const XRVec3& v1 = vertex[indexBuffer[a*6+0]];
        const XRVec3& v2 = vertex[indexBuffer[a*6+2]];
        const XRVec3& v3 = vertex[indexBuffer[a*6+4]];
		
		Int32 i1=indexBuffer[a*6+1],i2=indexBuffer[a*6+3],i3=indexBuffer[a*6+5];
        XRVec2 w1(&attribute[3+i1*5]);
        XRVec2 w2(&attribute[3+i2*5]);
        XRVec2 w3(&attribute[3+i3*5]);

        XRVec3 a1(&attribute[0+i1*5]);
        XRVec3 a2(&attribute[0+i2*5]);
        XRVec3 a3(&attribute[0+i3*5]);

        float x1 = v2.x - v1.x;
        float x2 = v3.x - v1.x;
        float y1 = v2.y - v1.y;
        float y2 = v3.y - v1.y;
        float z1 = v2.z - v1.z;
        float z2 = v3.z - v1.z;
        
        float s1 = w2.x - w1.x;
        float s2 = w3.x - w1.x;
        float t1 = w2.y - w1.y;
        float t2 = w3.y - w1.y;
        
        float r = 1.0F / (s1 * t2 - s2 * t1);
        XRVec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                (t2 * z1 - t1 * z2) * r);
        XRVec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                (s1 * z2 - s2 * z1) * r);
        
        tan1[i1] += sdir;
        tan1[i2] += sdir;
        tan1[i3] += sdir;
        
        tan2[i1] += tdir;
        tan2[i2] += tdir;
        tan2[i3] += tdir;
    }
    
    for (long a = 0; a < vertexAttributeCount; a++)
    {
        XRVec3 n(&attribute[a*5]);
        XRVec3 t = tan1[a];
        
        // Gram-Schmidt orthogonalize
		XRVec3 temp = (t - n * n.dot(t)).normalize();
        tangent[a].x = temp.x;
		tangent[a].y = temp.y;
		tangent[a].z = temp.z;
        // Calculate handedness
        tangent[a].w = (n.cross(t).dot(tan2[a]) < 0.0F) ? -1.0F : 1.0F;

		if ( tangent[a].w == 1.0) {
			xrprintf("");
		}
		else {
			xrprintf("");
		}
    }
    
    delete[] tan1;
}


