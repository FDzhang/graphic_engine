/*===========================================================================*\
 * FILE: CAvmStitchViewNode.cpp
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
#include "CAvmStitchViewNode.h"
#include "../AVMData.h"
#include "../GlSV2D.h"
#include "CAvmApaBevOverlay.h"

static char CAR2DICONBMP[] = XR_RES"car_icon_rx5.dds";
static char CAR2DICONBMPBLACK[] = XR_RES"car_icon_rx5_black.dds";

static char c_SV2DFragStaticShaderSrcFile[]   = XR_RES"OVFragShaderSV2DStatic.frg";
static char c_SV2DVertShaderSrcFileLUT[]  = XR_RES"OVVertShaderSV2D.vtx"; 

CAvmStitchViewNode::CAvmStitchViewNode():m_stitchViewCameraParams(0)
{

}
CAvmStitchViewNode::~CAvmStitchViewNode()
{

}
int CAvmStitchViewNode::InitNode(IXrCore* pXrcore)
{	
	if(pXrcore == NULL)
	{
		return AVM_STITCHVIEW_XRCORE_NULL;
	}

	m_xrCore = pXrcore;

   	int meshid[eCarImageMesh+1];
	int modelId,materialID;
	float *pData; 
	unsigned short	 *pIndex;	
	unsigned int BufferSize;

	char *MeshName[eCarImageMesh+1]={"FrontMesh","RearMesh","LeftMesh","RightMesh","FrontLeftMesh","FrontRightMesh","RearLeftMesh","RearRightMesh","Car"};
	char *Model[eCarImageMesh+1]={"0","1","2","3","4","5","6","7","8"};

	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_2D_VERTEX_SHADER);	
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_2D_FRAGMENT_SHADER);	

	m_stitchViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_stitchViewNode);

	Region* stitchViewRegion = NULL;
	CAvmRenderDataBase::GetInstance()->GetStitchViewRegion(&stitchViewRegion);

	m_stitchViewNode->SetRenderROI(stitchViewRegion);

	CAvmRenderDataBase::GetInstance()->GetSv2dData(&m_SV2DData);
	int displayChannel = 2;

	m_renderDelegate = new RenderDelegateSV2D();
	
	m_renderDelegate->Init();

#define Material_MAX 6
    //step 1. prepare for Material ,different camera input image 
	IRenderEffect* pIEffect[Material_MAX];
    int SV2DMTL[Material_MAX];
	float pos[3];

	for(int i=0;i<Material_MAX;i++)
	{
    	SV2DMTL[i] = m_stitchViewNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
		m_SV2DMtl->CreateMaterialEffect(&pIEffect[i]);
		if(i == 4)
		{
			pIEffect[i]->InitShaderFromFile("Effect_SV2DImage", c_SV2DVertShaderSrcFileLUT, c_SV2DFragStaticShaderSrcFile,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
		}
		else
		{
		   	pIEffect[i]->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
		}
		pIEffect[i]->SetRenderDelegate(m_renderDelegate);
		if(i == 0)
		{
		    
			AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,front_camera_index);	
		}
		else if(i ==1)
		{
			AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,rear_camera_index);	
		}
		else if(i == 2)
		{
			AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,left_camera_index);	
		}
		else if(i ==3)
		{
			AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,right_camera_index);	
		}	
		else if(i ==4)
		{
    	    m_SV2DMtl->SetDiffuseMap(CAR2DICONBMP);	
			m_carBodyMtl = m_SV2DMtl;
		}	
		else
		{	
		   AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,right_camera_index); 
		}
	}
	
    //step 2 prepare mesh for 2D stiching
	
    for(int i = 0;i <= 8;i++)
    {
        m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
	    meshid[i] = m_stitchViewNode->CreateMesh(ModelType_Null, 0,0,0,MeshName[i], &m_planeMesh);
	    m_planeMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
		m_planeMesh->SetName(Model[i]);
        m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize);		
	    m_planeMesh->LoadIndexFromArray(pIndex ,2* BufferSize);
    }

    //step 3 combine mesh and material(video texture) together.
    for(int i =0 ;i<=7;i++)
    {
        if(i<eFrontLeftMesh)
        {
            materialID=i;
			//Model[i] = "N";
        }
		else if(i == eFrontLeftMesh || i == eRearLeftMesh)
		{
		   materialID = 2;
		   //Model[i] = "A";
		   
		}
		else if(i<= eRearRightMesh)
		{
		    materialID=3;
			//Model[i] = "A";
			
		}
		else if(i == eCarImageMesh)
		{
		    materialID =4;
			//Model[i] = "P";
			
		}
		else
		{
		    materialID = 5;
			//Model[i] = "N";
			
		}
			
    	modelId = m_stitchViewNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
    	m_SV2Dplane[i]->SetMesh(meshid[i]);
    	m_SV2Dplane[i]->SetName(Model[i]);		
		m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
    }

	int i=8;
	materialID =4;
	modelId = m_stitchViewNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
	m_SV2Dplane[i]->SetMesh(meshid[i]);
	m_SV2Dplane[i]->SetName(Model[i]);		
	m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);


	CAvmRenderDataBase::GetInstance()->SetStitchViewNode(m_stitchViewNode);
	
	CAvmRenderDataBase::GetInstance()->GetStitchViewCameraParams(&m_stitchViewCameraParams);
	
	int m_stitchViewCameraId = m_stitchViewNode->CreateCamera(m_stitchViewCameraParams->fovx, m_stitchViewCameraParams->aspect, m_stitchViewCameraParams->znear, m_stitchViewCameraParams->zfar, &m_stitchViewCamera);
	
	m_stitchViewCamera->Set2DCamera(1);
	const float stitchCameraHeight = 3600.0;
	m_stitchViewCamera->SetPosition(0,0,stitchCameraHeight);
	m_stitchViewCamera->LookAt(0.0,0.0,-0.0);
	m_stitchViewCamera->RotateAround(0,45);
	m_stitchViewNode->SetCamera(m_stitchViewCameraId);
	
	//m_overlay = new CAvmApaBevOverlay;

	return AVM_STITCHVIEW_NORMAL; 
}
int CAvmStitchViewNode::UpdateNode()
{
	//AddOverlay(m_overlay);
	//MockRefreshCarBodyTexture();

	return AVM_STITCHVIEW_NORMAL;
}
int CAvmStitchViewNode::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_stitchViewNode == NULL)
    {
        return AVM_STITCHVIEW_NODE_INIT_FAILED;
    }

	m_stitchViewNode->SetEnable(pVisibilityFlag);
    //AVMData::GetInstance()->SetStitchViewGuideLineVisibility(pVisibilityFlag);
	//AVMData::GetInstance()->SetStitchViewRadarVisibility(pVisibilityFlag);
	m_visibilityFlag = pVisibilityFlag;

	return AVM_STITCHVIEW_NORMAL;
}
int CAvmStitchViewNode::ResetStitchViewNodeRegion(Region* pRegion)
{
	if(m_stitchViewNode == NULL)
    {
        return AVM_STITCHVIEW_NODE_INIT_FAILED;
    }
	m_stitchViewNode->SetRenderROI(pRegion);
	return AVM_STITCHVIEW_NORMAL;
}
int CAvmStitchViewNode::GetAvmStitchViewNode(ISceneNode* pStitchViewNode)
{
    if(m_stitchViewNode == NULL)
    {
        return AVM_STITCHVIEW_NODE_INIT_FAILED;
    }
    pStitchViewNode = m_stitchViewNode;
    return AVM_STITCHVIEW_NORMAL;
}
int CAvmStitchViewNode::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_stitchViewNode->SetClear(pColorFlag, pDepthFlag);
	return AVM_STITCHVIEW_NORMAL;
}
int CAvmStitchViewNode::AddOverlay(IAvmOverlay * pOverlay)
{
	unsigned char apaControl = 1;
	static unsigned char apaInitFlag = 0;
	if(apaControl == 1
		&& apaInitFlag == 0)
	{
		pOverlay->Init(m_stitchViewNode);
		apaInitFlag = 1;
	}

	if(pOverlay)
	{
		pOverlay->Update();
	}
	
	return AVM_STITCHVIEW_NORMAL;
}
void CAvmStitchViewNode::MockRefreshCarBodyTexture()
{
	VehInfoT vehInfo;

	CAvmRenderDataBase::GetInstance()->GetVehInfo(&vehInfo);

	if(vehInfo.bodyStyle == 0)
	{
		m_carBodyMtl->SetDiffuseMap(CAR2DICONBMP);

	}
	else if(vehInfo.bodyStyle == 1)
	{	
		m_carBodyMtl->SetDiffuseMap(CAR2DICONBMPBLACK);
	}
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmStitchViewNode class.
\*===========================================================================*/
