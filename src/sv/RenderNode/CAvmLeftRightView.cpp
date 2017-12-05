/*===========================================================================*\
 * FILE: CAvmLeftRightView.cpp
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

#include "CAvmLeftRightView.h"
#include "../AVMData.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"

CAvmLeftRightView::CAvmLeftRightView()
{

}
CAvmLeftRightView::~CAvmLeftRightView()
{

}
int CAvmLeftRightView::InitNode(class IXrCore* pXrcore)
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
	m_leftRightViewNodeId[0] = m_xrCore->CreateRenderNodeScene(0, &m_leftRightViewNode[0]);
 
 	Region* viewRegion;
	AVMData::GetInstance()->GetLeftRightViewRegion(&viewRegion, left_camera_index);
	m_leftRightViewNode[0]->SetRenderROI(viewRegion);

	m_leftRightViewNodeId[1] = m_xrCore->CreateRenderNodeScene(0, &m_leftRightViewNode[1]);

	AVMData::GetInstance()->GetLeftRightViewRegion(&viewRegion, right_camera_index);
	m_leftRightViewNode[1]->SetRenderROI(viewRegion);

	m_SV2DData = new GlSV2D;
	m_SV2DData->Init();
			
	m_renderDelegate = new RenderDelegateSV2D();
	m_renderDelegate->Init();
	m_renderDelegate->SetChannel(left_right_camera_index);
	//step 1. prepare for Material ,different camera input image 
	IRenderEffect* pIEffect;
	int SV2DMTL;
/*	SV2DMTL = m_singleViewNode->CreateMaterial(Material_Custom, &m_SVSingleMtl);
	m_SVSingleMtl->CreateMaterialEffect(&pIEffect);
	
	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SVSingleMtl,front_camera_index); 

	pIEffect->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);
	
	*/ //Original Code
    for(int i = eLeftSingle;i<= eRightSingle;i++)
    {
	//step 2 prepare mesh for 2D stiching

		
		//AVMData::GetInstance()->SetLeftRightViewRoi(pData, i - eFrontSingle);

		meshid = m_leftRightViewNode[i - eLeftSingle]->CreateMesh(ModelType_Null, 1,0,0,MeshName[i - eFrontSingle], &(m_leftRightViewMesh[i - eLeftSingle]));
		m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
		m_leftRightViewMesh[i - eLeftSingle]->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
		m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize); 	
		m_leftRightViewMesh[i - eLeftSingle]->LoadIndexFromArray(pIndex ,2* BufferSize);
		
		int iSize;
		XRVertexLayout data_format;
		m_leftRightViewMesh[i - eLeftSingle]->LockData(&(m_leftRightviewVertex[i - eLeftSingle]), &data_format, &iSize);

		//step 3 combine mesh and material(video texture) together.
		materialID = 5;

		//--------------------
		SV2DMTL = m_leftRightViewNode[i - eLeftSingle]->CreateMaterial(Material_Custom, &m_leftRightViewMtl);
		m_leftRightViewMtl->CreateMaterialEffect(&pIEffect);
	
		AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_leftRightViewMtl,i - eFrontSingle); 

		pIEffect->InitShaderFromFile("Effect_LeftRight2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
		pIEffect->SetRenderDelegate(m_renderDelegate);
	   //--------------------- new code

		modelId = m_leftRightViewNode[i - eLeftSingle]->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_leftRightViewPlane[i - eLeftSingle]);
		m_leftRightViewPlane[i - eLeftSingle]->SetMesh(meshid);
		m_leftRightViewPlane[i - eLeftSingle]->SetName(MeshName[i-eFrontSingle]);		
		m_leftRightViewPlane[i - eLeftSingle]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
		m_leftRightViewPlane[i - eLeftSingle]->SetEnable(0);
		
		/////////////////////////////cameraObject//////////////////
		AVMData::GetInstance()->GetSingleViewCameraParams(&m_leftRightViewCameraParams);
		m_leftRightViewCameraId[i - eLeftSingle] =  m_leftRightViewNode[i - eLeftSingle]->CreateCamera(m_leftRightViewCameraParams->fovx, m_leftRightViewCameraParams->aspect, m_leftRightViewCameraParams->znear, m_leftRightViewCameraParams->zfar, &m_leftRightViewCamera[i - eLeftSingle]);
		m_leftRightViewNode[i - eLeftSingle]->SetCamera(m_leftRightViewCameraId[i - eLeftSingle]);
		m_leftRightViewCamera[i - eLeftSingle]->Set2DCamera(1);
		const float SINGLEVIEW_CAMERA_DEFAULT_HEIGHT = 3600.0;
		m_leftRightViewCamera[i - eLeftSingle]->SetPosition(0,0,SINGLEVIEW_CAMERA_DEFAULT_HEIGHT);
		m_leftRightViewCamera[i - eLeftSingle]->LookAt(0.0,0.0,-0.0);
		m_leftRightViewCamera[i - eLeftSingle]->RotateAround(0,45);
    }
	m_leftRightViewPlane[0]->SetEnable(1);
	m_leftRightViewPlane[1]->SetEnable(1);

	return LEFT_RIGHT_VIEW_NORMAL;
}
int CAvmLeftRightView::UpdateNode()
{	


	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmLeftRightView::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_leftRightViewNode[1] == NULL)
	{
		return LEFT_RIGHT_VIEW_NODE_INIT_FAILED;
	}
	m_leftRightViewNode[0]->SetEnable(pVisibilityFlag);
	m_leftRightViewNode[1]->SetEnable(pVisibilityFlag);

	return LEFT_RIGHT_VIEW_NORMAL;
}

int CAvmLeftRightView::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_leftRightViewNode[0]->SetClear(pColorFlag, pDepthFlag);
	m_leftRightViewNode[1]->SetClear(pColorFlag, pDepthFlag);

	return LEFT_RIGHT_VIEW_NORMAL;

}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLeftRightView class.
\*===========================================================================*/