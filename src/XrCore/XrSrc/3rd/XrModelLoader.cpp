#include "XrFileLoader.h"
#include "../XrNode/CNode.h"
#include "GLMetaseq.h"
#include "../Platform/XrCrt.h"
#include "../XrResource/CDataStream.h"
#include "GpuModelCommon.h"
#include "ModelOFG.h"

static Int32 mqoInitFlag = 0;

xr_state LoadMQOFromFile(String fileName,CMesh* pMesh, Float32 scale, Boolean reserve);
xr_state LoadOFGFromFile(String fileName, CMesh* pMesh, Float32 scale, Boolean reserve);

xr_state _LoadModelFromFile(String fileName, CMesh* pMesh, Float32 scale, Boolean reserve)
{
	Int32 isMQO;
	Int32 isOBJ;
	Int32 isMsh;
	Int32 isOFG;
	char ext[4];
	if ( fileName == NULL ) return XR_FAILED;
	size_t namelen = strlen(fileName);
	ext[0] = tolower(fileName[namelen-3]);
	ext[1] = tolower(fileName[namelen-2]);
	ext[2] = tolower(fileName[namelen-1]);
	ext[3] = 0x00;
	isMQO = (strcmp(ext,"mqo")==0)?1:0;
	isOBJ = (strcmp(ext,"obj")==0)?1:0;
	isMsh = (strcmp(ext,"msh")==0)?1:0;
	isOFG = (strcmp(ext,"ofg")==0)?1:0;

	if (isMQO) {
		return LoadMQOFromFile(fileName, pMesh, scale, reserve);
	}
	else if (isOFG) {
		return LoadOFGFromFile(fileName, pMesh, scale, reserve);
	}

	return XR_OK;
}

xr_state UnloadModel(CMesh* pMesh)
{
	Void* native = pMesh->GetExternalModel();

	if (!native) return XR_FAILED;

	if (pMesh->GetExternalModelFormat() == ModelFormat_MQO) {
		mqoDeleteModel(MQO_MODEL(native));
		pMesh->SetExternalModelFormat(ModelFormat_None);
		pMesh->SetExternalModel(0);
	}
	return XR_OK;
}
xr_state LoadOFGFromFile(String fileName, CMesh* pMesh, Float32 scale, Boolean reserve)
{

	Model_SV *OFGModel = ofgCreateModel(fileName, scale, 0);
	MQO_INNER_OBJECT	*obj;
	MQO_MATERIAL		*mat;
	float *pTemp;
	
	Int32	num;

	if(OFGModel == 0)
	{
		return XR_FAILED;
	}
	pTemp = (float *)OFGModel->vertex_list;
	OFGModel->index_total *=2;

	pMesh->SetupVB(pTemp, XR_VERTEX_LAYOUT_PNT, OFGModel->vertex_total, XR_BUFFER_STATIC);
	pMesh->SetupIB(OFGModel->index_list,OFGModel->index_total,XR_BUFFER_STATIC);


	pMesh->SetExternalModel((Void*)OFGModel);
	pMesh->SetExternalModelFormat(ModelFormat_OFG);
	
	return XR_OK;
}

xr_state LoadMQOFromFile(String fileName, CMesh* pMesh, Float32 scale, Boolean reserve)
{
	if (!mqoInitFlag) {
		mqoInit();
		mqoInitFlag = 1;
	}
	MQO_MODEL MQOModel = mqoCreateModel(fileName, scale, 0);
	MQO_INNER_OBJECT	*obj;
	MQO_MATERIAL		*mat;
	Int32	o, m;
	
	mat = &(MQOModel->obj[0].mat[0]);
	pMesh->SetupVB((Float32*)mat->vertex_t, XR_VERTEX_LAYOUT_PNT, mat->datanum, XR_BUFFER_STATIC);


	if (!reserve) {
		mqoDeleteModel( MQOModel);
		pMesh->SetExternalModelFormat(ModelFormat_None);
	}
	else {
		pMesh->SetExternalModel((Void*)MQOModel);
		pMesh->SetExternalModelFormat(ModelFormat_MQO);
	}
	return XR_OK;
}

//xr_state LoadVertexFromArray(Float32* pData, Int32 format, Int32 datanum, CMesh* pMesh)
//{
//	pMesh->FreeVB();
//	pMesh->FeedVbo(pData, format, datanum);
//	return XR_OK;
//}
//
//xr_state LoadIndexFromArray(Int16* pData, Int32 format, Int32 datanum, CMesh* pMesh)
//{
//	pMesh->FreeVB();
//	pMesh->FeedVbo(pData, format, datanum);
//	return XR_OK;
//}



xr_state LockMeshData(CMesh* pMesh, Float32** ppData, XRVertexLayout* layout, Int32* vertexCount)
{
	CMesh* mesh;
	MQO_MODEL MQOModel;
	MQO_MATERIAL		*mat;
	switch (pMesh->GetExternalModelFormat()) {
		case ModelFormat_MQO :
			MQOModel = (MQO_MODEL)pMesh->GetExternalModel();
			mat =  &MQOModel->obj[0].mat[0];
			*ppData = (Float32*)mat->vertex_t;
			if (layout) *layout = XR_VERTEX_LAYOUT_PNT;
			*vertexCount = mat->datanum;
			break;
		case ModelFormat_OFG :
			xrprintf("ofg model");
        break;			
		default:
			return XR_FAILED;
	}
	return XR_OK;
}

xr_state UnLockMeshData(CMesh* pMesh)
{

	MQO_MODEL MQOModel=0;

	MQO_MATERIAL		*mat;
	switch (pMesh->GetExternalModelFormat()) {
		case ModelFormat_MQO :
			MQOModel = (MQO_MODEL)pMesh->GetExternalModel();
			mat =  &(MQOModel->obj[0].mat[0]);
			pMesh->UpdateVB((Float32*)mat->vertex_t);
			break;
			case ModelFormat_OFG :
			xrprintf("ofg model");
        break;		
		default:
			return XR_FAILED;
	}
	return XR_OK;
}
