/*===========================================================================*\
 * FILE: CAvm3dViewNode.cpp
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
#include "CAvm3dViewNode.h"
#include "../AVMData.h"

static char OVERLAPMASK[] = XR_RES"mask.bmp";
static char OVERLAPMASKREAR[] = XR_RES"maskrear.bmp";

static char skyR[]	= XR_RES"skylrex.mqo";
static char skyL[]	= XR_RES"skylrex.mqo";
static char skyF[]	= XR_RES"skyfbex.mqo";
static char skyB[]	= XR_RES"skyfbex.mqo";
static char skyFA[]	= XR_RES"skyfbaex.mqo";
static char skyBA[]	= XR_RES"skyfbaex.mqo";
static char skyFC[]	= XR_RES"skyfbcylinder.mqo";
static char skyBC[]	= XR_RES"skyfbcylinder.mqo";

int CAvm3dViewNode::InitNode(IXrCore* pXrcore)
{
	if(pXrcore == NULL)
	{
		return AVM_3DVIEW_XRCORE_NULL;
	}

	m_xrCore = pXrcore;
	//m_sceneMode = SceneMode_Free; //--wjx-------

	Region* avm3dViewAera;
	float cameraAspect;
	m_3dViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_3dViewNode);

	m_3dViewNode->SetClearColor(1.0,1.0,0.0,0.5);
	m_3dViewNode->SetClear(TRUE, TRUE);
    
	AVMData::GetInstance()->Get3dViewRegion(&avm3dViewAera);
    m_3dViewNode->SetRenderROI(avm3dViewAera);	

	m_renderDelegate = new RenderDelegateSV();
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	BEV_CONFIG_T  config;
	AVMData::GetInstance()->GetBevConfig(&config);

	m_renderDelegate->Init(config);

	Bev_3D_Param_T*  bev_3d_param;
    AVMData::GetInstance()->m_usc_data->GetBev3DParam(&bev_3d_param);

	int SVMTL[4];

	IMaterial* pISVmtl;
	IRenderEffect* pIEffect;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_3D_VERTEX_SHADER);	
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_3D_FRAGMENT_SHADER);		
	for(int i =0;i<4;i++)
	{
    	SVMTL[i] = m_3dViewNode->CreateMaterial(Material_Custom, &pISVmtl);
        pISVmtl->CreateMaterialEffect(&pIEffect);
    	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pISVmtl,i);	
		if(i<3)
    	pISVmtl->SetAmbientMap(OVERLAPMASK);
		else
		pISVmtl->SetAmbientMap(OVERLAPMASKREAR);
			
    	AVMData::GetInstance()->m_cam_source->SetCameraSourceMask(pISVmtl->GetAmbientMap()->texid,i);	
    
    	pIEffect->InitShaderFromFile("Effect_SV", VertexName, FragShaderName, sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
    	pIEffect->SetRenderDelegate(m_renderDelegate);
	}

#define SV_Y_POS 0
	int modelId;
	INode* pImdl;

	modelId = m_3dViewNode->LoadModelFromFile(skyR ,SVMTL[0], -1, InsertFlag_Default, 0, SV_Y_POS, -0,	bev_3d_param->model_param.model_scale, &pImdl);

	m_renderDelegate->ProcessModel(pImdl, "3");
	
	modelId = m_3dViewNode->LoadModelFromFile(skyL ,SVMTL[1], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "2");

	modelId = m_3dViewNode->LoadModelFromFile(skyF ,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "0");

	modelId = m_3dViewNode->LoadModelFromFile(skyB ,SVMTL[3], -1, InsertFlag_Default, 0, SV_Y_POS, -0,	bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "1");	

	modelId = m_3dViewNode->LoadModelFromFile(skyFA ,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "4");

	modelId = m_3dViewNode->LoadModelFromFile(skyBA ,SVMTL[3], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "5");
	
	modelId = m_3dViewNode->LoadModelFromFile(skyFC,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "6");

	modelId = m_3dViewNode->LoadModelFromFile(skyBC ,SVMTL[3], -1, InsertFlag_Default, 0, SV_Y_POS, -0, bev_3d_param->model_param.model_scale, &pImdl);
	m_renderDelegate->ProcessModel(pImdl, "7");

	/////////////////////////////cameraScene//////////////////

	AVMData::GetInstance()->Get3dViewCameraParams(&m_3dViewCameraParams);
	m_3dViewCameraId = m_3dViewNode->CreateCamera(m_3dViewCameraParams->fovx, m_3dViewCameraParams->aspect, 
												m_3dViewCameraParams->znear, m_3dViewCameraParams->zfar, &m_3dViewCamera);
	//m_freeModeFOV = m_3dViewCameraParams->fovx; //------wjx---------
	//camera->SetOrientation(0, 0, 0);
	const float SCENE_CAMERA_DEFAULT_HEIGHT = 3600.0;
	m_3dViewCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
	m_3dViewCamera->LookAt(0.0,0.0,0.0);
	//camera->RotateAround(2,2);
	m_3dViewNode->SetCamera(m_3dViewCameraId);

    return AVM_3DVIEW_NORMAL;
}
int CAvm3dViewNode::UpdateNode()
{

}
int CAvm3dViewNode::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_3dViewNode == NULL)
    {
        return AVM_3DVIEW_NODE_INIT_FAILED;
    }

	m_3dViewNode->SetEnable(pVisibilityFlag);
    //AVMData::GetInstance()->Set3dViewGuideLineVisibility(pVisibilityFlag);
	//AVMData::GetInstance()->Set3dViewRadarVisibility(pVisibilityFlag);
	m_visibilityFlag = pVisibilityFlag;

	return AVM_3DVIEW_NORMAL;
}
int CAvm3dViewNode::Reset3dViewNodeRegion(Region* pRegion)
{
	if(m_3dViewNode == NULL)
    {
        return AVM_3DVIEW_NODE_INIT_FAILED;
    }
	m_3dViewNode->SetRenderROI(pRegion);
	return AVM_3DVIEW_NORMAL;
}
int CAvm3dViewNode::GetAvm3dViewNode(ISceneNode* p3dViewNode)
{
    if(m_3dViewNode == NULL)
    {
        return AVM_3DVIEW_NODE_INIT_FAILED;
    }
    p3dViewNode = m_3dViewNode;
    return AVM_3DVIEW_NORMAL;
}


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvm3dViewNode class.
\*===========================================================================*/