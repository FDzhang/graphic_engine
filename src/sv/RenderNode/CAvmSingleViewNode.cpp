/*===========================================================================*\
 * FILE: CAvmSingleViewNode.cpp
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/
#include "CAvmSingleViewNode.h"
#include "../AVMData.h"
#include "../GlSV2D.h"

static char CAR2DICONBMP[] = XR_RES"car_icon_rx5.dds";
static char c_SV2DFragStaticShaderSrcFile[]   = XR_RES"OVFragShaderSV2DStatic.frg";
static char c_SV2DVertShaderSrcFileLUT[]  = XR_RES"OVVertShaderSV2D.vtx"; 

CAvmSingleViewNode::CAvmSingleViewNode()
{
}
CAvmSingleViewNode::~CAvmSingleViewNode()
{
}

int CAvmSingleViewNode::InitNode(IXrCore* pXrcore)
{	
	if(pXrcore == NULL)
	{
		return AVM_SINGLEVIEW_XRCORE_NULL;
	}

	m_xrCore = pXrcore;

	int meshid;
	int modelId,materialID;
	float *pData; 
	unsigned short	 *pIndex;	
	unsigned int BufferSize;
	
	char *MeshName[]={"f","b","l","r"};

    float pos[3];
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_2D_VERTEX_SHADER);	
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_2D_FRAGMENT_SHADER);
	// Interleaved vertex data
	m_singleViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_singleViewNode);
 
 	Region* singleViewRegion;
	AVMData::GetInstance()->GetSingleViewRegion(&singleViewRegion);
	m_singleViewNode->SetRenderROI(singleViewRegion);
			
	AVMData::GetInstance()->GetSv2dData(&m_SV2DData);

	m_renderDelegate = new RenderDelegateSV2D();
	m_renderDelegate->Init();
	//step 1. prepare for Material ,different camera input image 
	IRenderEffect* pIEffect;
	int SV2DMTL;
/*	SV2DMTL = m_singleViewNode->CreateMaterial(Material_Custom, &m_SVSingleMtl);
	m_SVSingleMtl->CreateMaterialEffect(&pIEffect);
	
	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SVSingleMtl,front_camera_index); 

	pIEffect->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);
	
	*/ //Original Code

    for(int i = eFrontSingle;i<=eRightSingle;i++)
    {
	//step 2 prepare mesh for 2D stiching

		m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);

		AVMData::GetInstance()->SetSingleViewRoi(pData, i - eFrontSingle);

		meshid = m_singleViewNode->CreateMesh(ModelType_Null, 1,0,0,MeshName[i-eFrontSingle], &(m_singleViewMesh[i - eFrontSingle]));
		m_singleViewMesh[i - eFrontSingle]->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
		m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize); 	
		m_singleViewMesh[i - eFrontSingle]->LoadIndexFromArray(pIndex ,2* BufferSize);
		
		int iSize;
		XRVertexLayout data_format;
		m_singleViewMesh[i - eFrontSingle]->LockData(&(m_singleviewVertex[i - eFrontSingle]), &data_format, &iSize);

		//step 3 combine mesh and material(video texture) together.
		materialID = 5;

		//--------------------
		SV2DMTL = m_singleViewNode->CreateMaterial(Material_Custom, &m_SVSingleMtl);
		m_SVSingleMtl->CreateMaterialEffect(&pIEffect);
	
		AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SVSingleMtl,i - eFrontSingle); 

		pIEffect->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
		pIEffect->SetRenderDelegate(m_renderDelegate);
	   //--------------------- new code

		modelId = m_singleViewNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
		m_SV2Dplane[i]->SetMesh(meshid);
		m_SV2Dplane[i]->SetName(MeshName[i-eFrontSingle]);		
		m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
		m_SV2Dplane[i]->SetEnable(0);
	
    }
	m_SV2Dplane[eFrontSingle]->SetEnable(0);
	
	/////////////////////////////cameraObject//////////////////
	AVMData::GetInstance()->GetSingleViewCameraParams(&m_singleViewCameraParams);
	m_singleViewCameraId = m_singleViewNode->CreateCamera(m_singleViewCameraParams->fovx, m_singleViewCameraParams->aspect, m_singleViewCameraParams->znear, m_singleViewCameraParams->zfar, &m_singleViewCamera);
	m_singleViewNode->SetCamera(m_singleViewCameraId);
		//m_singleViewNode->SetEnable(1);
	m_singleViewCamera->Set2DCamera(1);
	const float SINGLEVIEW_CAMERA_DEFAULT_HEIGHT = 3600.0;
	m_singleViewCamera->SetPosition(0,0,SINGLEVIEW_CAMERA_DEFAULT_HEIGHT);
	m_singleViewCamera->LookAt(0.0,0.0,-0.0);
	m_singleViewCamera->RotateAround(0,45);

	AVMData::GetInstance()->SetSingleViewNode(m_singleViewNode);
	AVMData::GetInstance()->SetSingleViewPlaneNode(m_SV2Dplane);
	AVMData::GetInstance()->SetSingleViewVertex(m_singleviewVertex);
	AVMData::GetInstance()->SetSingleViewMesh(m_singleViewMesh);

	return AVM_SINGLEVIEW_NORMAL;
}
int CAvmSingleViewNode::UpdateNode()
{
	unsigned char singleViewCmd = 0;
	AVMData::GetInstance()->GetSingleViewChannel(singleViewCmd);
		
    for(int i = eFrontSingle;i<=eRightSingle;i++)
    {
        if(i == singleViewCmd + eFrontSingle)
        {           
			m_SV2Dplane[i]->SetEnable(1);
        }
		else
		{
			m_SV2Dplane[i]->SetEnable(0);	
		}
    }

	m_renderDelegate->SetChannel(singleViewCmd);

	return AVM_SINGLEVIEW_NORMAL;
}
int CAvmSingleViewNode::SetVisibility(unsigned char pVisibilityFlag)
{	
	if(m_singleViewNode == NULL)
    {
        return AVM_SINGLEVIEW_NODE_INIT_FAILED;
    }

	m_singleViewNode->SetEnable(pVisibilityFlag);
    //AVMData::GetInstance()->Set3dViewGuideLineVisibility(pVisibilityFlag);
	//AVMData::GetInstance()->Set3dViewRadarVisibility(pVisibilityFlag);
	m_visibilityFlag = pVisibilityFlag;
	return AVM_SINGLEVIEW_NORMAL;
}
int CAvmSingleViewNode::ResetSingleViewNodeRegion(Region* pRegion)
{
	if(m_singleViewNode == NULL)
    {
        return AVM_SINGLEVIEW_NODE_INIT_FAILED;
    }
	m_singleViewNode->SetRenderROI(pRegion);
	return AVM_SINGLEVIEW_NORMAL;
}
int CAvmSingleViewNode::GetAvmSingleViewNode(ISceneNode* pSingleViewNode)
{
    if(m_singleViewNode == NULL)
    {
        return AVM_SINGLEVIEW_NODE_INIT_FAILED;
    }
    pSingleViewNode = m_singleViewNode;
    return AVM_SINGLEVIEW_NORMAL;
}
int CAvmSingleViewNode::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_singleViewNode->SetClear(pColorFlag, pDepthFlag);
	return AVM_SINGLEVIEW_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmSingleViewNode class.
\*===========================================================================*/