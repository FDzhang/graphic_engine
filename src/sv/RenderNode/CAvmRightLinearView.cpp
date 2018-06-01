
/*===========================================================================*\
 * FILE: CAvmRightLinearView.cpp
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

#include "CAvmRightLinearView.h"
#include "../AVMData.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"

CAvmRightLinearView::CAvmRightLinearView()
{

}
CAvmRightLinearView::~CAvmRightLinearView()
{

}
int CAvmRightLinearView::InitNode(class IXrCore* pXrcore)
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
	m_rightLinearViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_rightLinearViewNode);
	//AVMData::GetInstance()->SetRightLinearViewNode(m_rightLinearViewNode);

 	Region* viewRegion;
	CAvmRenderDataBase::GetInstance()->GetLeftRightViewRegion(&viewRegion, right_camera_index);
	m_rightLinearViewNode->SetRenderROI(viewRegion);

	m_SV2DData = new GlSV2D;
	m_SV2DData->InitLinear();
			
	m_renderDelegate = new RenderDelegateSV2D();
	m_renderDelegate->Init();
	m_renderDelegate->SetChannel(right_camera_index);
	//step 1. prepare for Material ,different camera input image 
	IRenderEffect* pIEffect;
	int SV2DMTL;

	int i = eRightSingle;
	meshid = m_rightLinearViewNode->CreateMesh(ModelType_Null, 1,0,0,MeshName[i - eFrontSingle], &m_rightLinearViewMesh);
	m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
	m_rightLinearViewMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
	m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize); 	
	m_rightLinearViewMesh->LoadIndexFromArray(pIndex ,2* BufferSize);

	int iSize;
	XRVertexLayout data_format;
	m_rightLinearViewMesh->LockData(&m_rightLinearviewVertex, &data_format, &iSize);

	//step 3 combine mesh and material(video texture) together.
	materialID = 5;

	//--------------------
	SV2DMTL = m_rightLinearViewNode->CreateMaterial(Material_Custom, &m_rightLinearViewMtl);
	m_rightLinearViewMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_rightLinearViewMtl,i - eFrontSingle); 

	pIEffect->InitShaderFromFile("Effect_RightLinear2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);
	//--------------------- new code

	modelId = m_rightLinearViewNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_rightLinearViewPlane);
	m_rightLinearViewPlane->SetMesh(meshid);
	m_rightLinearViewPlane->SetName(MeshName[i-eFrontSingle]);		
	m_rightLinearViewPlane->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	m_rightLinearViewPlane->SetEnable(0);
	
	/////////////////////////////cameraObject//////////////////
	CAvmRenderDataBase::GetInstance()->GetSingleViewCameraParams(&m_rightLinearViewCameraParams);
	m_rightLinearViewCameraId =  m_rightLinearViewNode->CreateCamera(m_rightLinearViewCameraParams->fovx, m_rightLinearViewCameraParams->aspect, m_rightLinearViewCameraParams->znear, m_rightLinearViewCameraParams->zfar, &m_rightLinearViewCamera);
	m_rightLinearViewNode->SetCamera(m_rightLinearViewCameraId);
	m_rightLinearViewCamera->Set2DCamera(1);
	const float SINGLEVIEW_CAMERA_DEFAULT_HEIGHT = 3600.0;
	m_rightLinearViewCamera->SetPosition(0,0,SINGLEVIEW_CAMERA_DEFAULT_HEIGHT);
	m_rightLinearViewCamera->LookAt(0.0,0.0,-0.0);
	m_rightLinearViewCamera->RotateAround(0,45);

	m_rightLinearViewPlane->SetEnable(1);

	return LEFT_RIGHT_VIEW_NORMAL;
}
int CAvmRightLinearView::UpdateNode()
{	


	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmRightLinearView::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_rightLinearViewNode == NULL)
	{
		return LEFT_RIGHT_VIEW_NODE_INIT_FAILED;
	}
	m_rightLinearViewNode->SetEnable(pVisibilityFlag);

	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmRightLinearView::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_rightLinearViewNode->SetClear(pColorFlag, pDepthFlag);

	return LEFT_RIGHT_VIEW_NORMAL;

}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmRightLinearView class.
\*===========================================================================*/