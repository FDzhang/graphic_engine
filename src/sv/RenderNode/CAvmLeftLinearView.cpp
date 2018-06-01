/*===========================================================================*\
 * FILE: CAvmLeftLinearView.cpp
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

#include "CAvmLeftLinearView.h"
#include "../AVMData.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"

CAvmLeftLinearView::CAvmLeftLinearView()
{

}
CAvmLeftLinearView::~CAvmLeftLinearView()
{

}
int CAvmLeftLinearView::InitNode(class IXrCore* pXrcore)
{
	if(pXrcore == NULL)
	{
		return LEFT_RIGHT_VIEW_NORMAL;
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
	m_leftLinearViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_leftLinearViewNode);
	//AVMData::GetInstance()->SetLeftLinearViewNode(m_leftLinearViewNode);

 	Region* viewRegion;
	CAvmRenderDataBase::GetInstance()->GetLeftRightViewRegion(&viewRegion, left_camera_index);
	m_leftLinearViewNode->SetRenderROI(viewRegion);

	m_SV2DData = new GlSV2D;
	m_SV2DData->InitLinear();
			
	m_renderDelegate = new RenderDelegateSV2D();
	m_renderDelegate->Init();
	m_renderDelegate->SetChannel(left_camera_index);
	//step 1. prepare for Material ,different camera input image 
	IRenderEffect* pIEffect;
	int SV2DMTL;

	int i = eLeftSingle;
	meshid = m_leftLinearViewNode->CreateMesh(ModelType_Null, 1,0,0,MeshName[i - eFrontSingle], &m_leftLinearViewMesh);
	m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
	m_leftLinearViewMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
	m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize); 	
	m_leftLinearViewMesh->LoadIndexFromArray(pIndex ,2* BufferSize);

	int iSize;
	XRVertexLayout data_format;
	m_leftLinearViewMesh->LockData(&m_leftLinearviewVertex, &data_format, &iSize);

	//step 3 combine mesh and material(video texture) together.
	materialID = 5;

	//--------------------
	SV2DMTL = m_leftLinearViewNode->CreateMaterial(Material_Custom, &m_leftLinearViewMtl);
	m_leftLinearViewMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_leftLinearViewMtl,i - eFrontSingle); 

	pIEffect->InitShaderFromFile("Effect_LeftLinear2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);
	//--------------------- new code

	modelId = m_leftLinearViewNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_leftLinearViewPlane);
	m_leftLinearViewPlane->SetMesh(meshid);
	m_leftLinearViewPlane->SetName(MeshName[i-eFrontSingle]);		
	m_leftLinearViewPlane->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	m_leftLinearViewPlane->SetEnable(0);
	
	/////////////////////////////cameraObject//////////////////
	CAvmRenderDataBase::GetInstance()->GetSingleViewCameraParams(&m_leftLinearViewCameraParams);
	m_leftLinearViewCameraId =  m_leftLinearViewNode->CreateCamera(m_leftLinearViewCameraParams->fovx, m_leftLinearViewCameraParams->aspect, m_leftLinearViewCameraParams->znear, m_leftLinearViewCameraParams->zfar, &m_leftLinearViewCamera);
	m_leftLinearViewNode->SetCamera(m_leftLinearViewCameraId);
	m_leftLinearViewCamera->Set2DCamera(1);
	const float SINGLEVIEW_CAMERA_DEFAULT_HEIGHT = 3600.0;
	m_leftLinearViewCamera->SetPosition(0,0,SINGLEVIEW_CAMERA_DEFAULT_HEIGHT);
	m_leftLinearViewCamera->LookAt(0.0,0.0,-0.0);
	m_leftLinearViewCamera->RotateAround(0,45);

	m_leftLinearViewPlane->SetEnable(1);

	return LEFT_RIGHT_VIEW_NORMAL;
}
int CAvmLeftLinearView::UpdateNode()
{	


	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmLeftLinearView::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_leftLinearViewNode == NULL)
	{
		return LEFT_RIGHT_VIEW_NODE_INIT_FAILED;
	}
	m_leftLinearViewNode->SetEnable(pVisibilityFlag);

	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmLeftLinearView::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_leftLinearViewNode->SetClear(pColorFlag, pDepthFlag);

	return LEFT_RIGHT_VIEW_NORMAL;

}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLeftLinearView class.
\*===========================================================================*/