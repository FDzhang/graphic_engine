/*===========================================================================*\
 * FILE: CAvmFrontRearLinearView.cpp
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

#include "CAvmFrontRearLinearView.h"
#include "../AVMData.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"

CAvmFrontRearLinearView::CAvmFrontRearLinearView()
{

}
CAvmFrontRearLinearView::~CAvmFrontRearLinearView()
{

}
int CAvmFrontRearLinearView::InitNode(class IXrCore* pXrcore)
{
	if(pXrcore == NULL)
	{
		return LINEAR_VIEW_NODE_NORMAL;
	}

	m_xrCore = pXrcore;

	// Interleaved vertex data
	m_linearViewNodeId[0] = m_xrCore->CreateRenderNodeScene(0, &m_linearViewNode[0]);

 	Region* viewRegion;
	CAvmRenderDataBase::GetInstance()->GetLinearViewRegion(&viewRegion);
	m_linearViewNode[0]->SetRenderROI(viewRegion);

	m_linearViewNodeId[1] = m_xrCore->CreateRenderNodeScene(0, &m_linearViewNode[1]);
	m_linearViewNode[1]->SetRenderROI(viewRegion);

	m_SV2DData = new GlSV2D;
	m_SV2DData->InitLinear();
			
	m_renderDelegate = new RenderDelegateSV2D();
	m_renderDelegate->Init();
	m_renderDelegate->SetChannel(rear_camera_index);
	//step 1. prepare for Material ,different camera input image 

	InitPlaneNode(0, eFrontSingle);
	InitPlaneNode(1, eRearSingle);
	
	return LINEAR_VIEW_NODE_NORMAL;
}
int CAvmFrontRearLinearView::InitPlaneNode(int pPlaneIndex, unsigned char pViewIndex)
{
	int meshid;
	int modelId;
	float *pData; 
	unsigned short	 *pIndex;	
	unsigned int BufferSize;	
	char *MeshName[]={"f","r"};
	IRenderEffect* pIEffect;
	int SV2DMTL;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_2D_VERTEX_SHADER);	
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_2D_FRAGMENT_SHADER);

	meshid = m_linearViewNode[pPlaneIndex]->CreateMesh(ModelType_Null, 1,0,0,MeshName[pPlaneIndex], &(m_linearViewMesh[pPlaneIndex]));
	m_SV2DData->GetVertexBuffer(pViewIndex,&pData,&BufferSize);
	m_linearViewMesh[pPlaneIndex]->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
	m_SV2DData->GetIndexBuffer(pViewIndex,&pIndex,&BufferSize); 	
	m_linearViewMesh[pPlaneIndex]->LoadIndexFromArray(pIndex ,2* BufferSize);
	
	int iSize;
	XRVertexLayout data_format;
	m_linearViewMesh[pPlaneIndex]->LockData(&(m_linearViewVertex[pPlaneIndex]), &data_format, &iSize);

	//--------------------
	SV2DMTL = m_linearViewNode[pPlaneIndex]->CreateMaterial(Material_Custom, &m_linearViewMtl);
	m_linearViewMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_linearViewMtl,pViewIndex - eFrontSingle); 

	pIEffect->InitShaderFromFile("Effect_FrontRearLinear", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);
   //--------------------- new code

	modelId = m_linearViewNode[pPlaneIndex]->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_linearViewPlane[pPlaneIndex]);
	m_linearViewPlane[pPlaneIndex]->SetMesh(meshid);
	m_linearViewPlane[pPlaneIndex]->SetName(MeshName[pPlaneIndex]);		
	m_linearViewPlane[pPlaneIndex]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	m_linearViewPlane[pPlaneIndex]->SetEnable(0);
	
	/////////////////////////////cameraObject//////////////////
	CAvmRenderDataBase::GetInstance()->GetSingleViewCameraParams(&m_linearViewCameraParams);
	m_linearViewCameraId[pPlaneIndex] =  m_linearViewNode[pPlaneIndex]->CreateCamera(m_linearViewCameraParams->fovx, m_linearViewCameraParams->aspect, m_linearViewCameraParams->znear, m_linearViewCameraParams->zfar, &m_linearViewCamera[pPlaneIndex]);
	m_linearViewNode[pPlaneIndex]->SetCamera(m_linearViewCameraId[pPlaneIndex]);
	m_linearViewCamera[pPlaneIndex]->Set2DCamera(1);
	const float SINGLEVIEW_CAMERA_DEFAULT_HEIGHT = 3600.0;
	m_linearViewCamera[pPlaneIndex]->SetPosition(0,0,SINGLEVIEW_CAMERA_DEFAULT_HEIGHT);
	m_linearViewCamera[pPlaneIndex]->LookAt(0.0,0.0,-0.0);
	m_linearViewCamera[pPlaneIndex]->RotateAround(0,45);
	m_linearViewPlane[pPlaneIndex]->SetEnable(1);
	
	return LINEAR_VIEW_NODE_NORMAL;
}
int CAvmFrontRearLinearView::UpdateNode()
{	
	unsigned char linear180DegreeViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(linear180DegreeViewCmd);

	if(linear180DegreeViewCmd == LINEAR_FRONT_180_DEGREE_VIEW)
	{
		m_renderDelegate->SetChannel(FRONT_SINGLE_VIEW);
		m_linearViewPlane[0]->SetEnable(1);
		m_linearViewPlane[1]->SetEnable(0);
		//m_180DegreeViewNode->SetClear(TRUE, TRUE); 
	}
	else if(linear180DegreeViewCmd == LINEAR_REAR_180_DEGREE_VIEW)
	{
		m_renderDelegate->SetChannel(REAR_SINGLE_VIEW);	
		//m_180DegreeViewNode->SetClear(TRUE, TRUE);
		m_linearViewPlane[0]->SetEnable(0);
		m_linearViewPlane[1]->SetEnable(1);
	}
	else
	{
		m_linearViewNode[0]->SetClear(m_colorClearFlag, m_depthClearFlag);
		m_linearViewNode[1]->SetClear(m_colorClearFlag, m_depthClearFlag);

		m_linearViewPlane[0]->SetEnable(0);
		m_linearViewPlane[1]->SetEnable(0);
	}

	return LINEAR_VIEW_NODE_NORMAL;
}

int CAvmFrontRearLinearView::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_linearViewNode[1] == NULL)
	{
		return LEFT_RIGHT_VIEW_NODE_INIT_FAILED;
	}
	m_linearViewNode[0]->SetEnable(pVisibilityFlag);
	m_linearViewNode[1]->SetEnable(pVisibilityFlag);

	return LINEAR_VIEW_NODE_NORMAL;
}

int CAvmFrontRearLinearView::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_depthClearFlag = pDepthFlag;
	m_colorClearFlag = pColorFlag;
	
	m_linearViewNode[0]->SetClear(pColorFlag, pDepthFlag);
	m_linearViewNode[1]->SetClear(pColorFlag, pDepthFlag);

	return LINEAR_VIEW_NODE_NORMAL;

}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmFrontRearLinearView class.
\*===========================================================================*/