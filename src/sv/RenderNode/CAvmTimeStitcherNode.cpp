/*===========================================================================*\
 * FILE: CAvmTimeStitcherNode.cpp
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
#include "CAvmTimeStitcherNode.h"
#include "../AVMData.h"
#include "../SVDelegate.h"
#include "../SVNode2DStich.h"
#include "SVNodeSonar.h"
#include "../GlSV2D.h"
#include "CAvmApaBevOverlay.h"
#include "gpu_log.h"

static char CAR2DICONBMP[] = XR_RES"car_icon_rx5.dds";
static char c_SV2DFragStaticShaderSrcFile[]   = XR_RES"OVFragShaderSV2DStatic.frg";
static char c_SV2DVertShaderSrcFileLUT[]  = XR_RES"OVVertShaderSV2D.vtx"; 
static char c_SV2DFragCarImageShaderSrcFile[]   = XR_RES"OVFragShaderSV2DCar.frg";

CAvmTimeStitcherNode::CAvmTimeStitcherNode()
{

}
CAvmTimeStitcherNode::~CAvmTimeStitcherNode()
{

}
int CAvmTimeStitcherNode::InitNode(IXrCore* pXrcore)
{
	int meshid;
	int modelId;
	float *pData; 
	unsigned short	 *pIndex;	
	unsigned int BufferSize;
	int tempmaterialid;
    INode *pNode;
	float pos[3];
    IMaterial* pMtl;
	IMesh *pMesh;
	float *pVertexData;
	XRVertexLayout  data_format;
	Int32 icount;
    INode *pCarImageNode;
	char MeshName[]={"Car"};
	char Model[]={"8"};
	IRenderEffect* pIEffect;
	int SV2DMTL;

	if(pXrcore == NULL)
	{
		return TIME_STITCHER_XRCORE_NULL;
	}

	m_xrCore = pXrcore;

	m_timeStitchNode = new SVNode2DStich;

	m_timeStitchNode->Init();

	CAvmRenderDataBase::GetInstance()->SetTimeStitcherNode(m_timeStitchNode);

	m_renderDelegate = new RenderDelegateSV2D;

	// Interleaved vertex data
	Region* stitchViewRegion = NULL;
	CAvmRenderDataBase::GetInstance()->GetStitchViewRegion(&stitchViewRegion);
	// Interleaved vertex data
	m_stitchViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_stitchViewNode);
	m_stitchViewNode->SetRenderROI(stitchViewRegion);

//render stich aera and ground aera.
	tempmaterialid = m_stitchViewNode->CreateMaterial(Material_Rigid_Texture, &m_stitchViewMtl);
    m_stitchViewMtl->SetDiffuseMap(m_timeStitchNode->GetStichFrameTextureId());

    int lisenceMeshId = m_stitchViewNode->CreateMesh(ModelType_Plane_Dynamic,2,	2,0, "Stich", &pMesh);
	
	int  groundId = m_stitchViewNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0,0,0, 1.0, &pNode);
		
	pMesh->LockData(&pVertexData,&data_format,&icount);
	pVertexData[0]=-1.0;
	pVertexData[1]=-1.0;
	pVertexData[2]=0.0;
	pVertexData[6]=0.0;
	pVertexData[7]=0.0;
		
	pVertexData[8]=1.0;
	pVertexData[9]=-1.0;
	pVertexData[10]=0.0;	
	pVertexData[14]=1.0;
	pVertexData[15]=0.0;

	pVertexData[16]=-1.0;
	pVertexData[17]=1.0;
	pVertexData[18]=0.0;
	pVertexData[22]=0.0;
	pVertexData[23]=1.0;

	pVertexData[24]=1.0;
	pVertexData[25]=1.0;
	pVertexData[26]=0.0;
	pVertexData[30]=1.0;
	pVertexData[31]=1.0;		
		
	pMesh->UnLockData();
	
	pNode->SetMesh(lisenceMeshId);
	
	 //render car image
	//step 2 prepare mesh for 2D stiching
	CAvmRenderDataBase::GetInstance()->GetSv2dData(&m_SV2DData);

	int i = eCarImageMesh;
 	m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
 	meshid = m_stitchViewNode->CreateMesh(ModelType_Null, 0,0,0,MeshName, &m_planeMesh);
 	m_planeMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
 	m_planeMesh->SetName(Model);
 	m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize);		
 	m_planeMesh->LoadIndexFromArray(pIndex ,2* BufferSize);
	SV2DMTL = m_stitchViewNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
	m_SV2DMtl->CreateMaterialEffect(&pIEffect);
	pIEffect->InitShaderFromFile("Effect_SV2DCarImage", c_SV2DVertShaderSrcFileLUT, c_SV2DFragCarImageShaderSrcFile,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate); 
	 
	m_SV2DMtl->SetDiffuseMap(CAR2DICONBMP);

	modelId = m_stitchViewNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 0, &pCarImageNode);
	pCarImageNode->SetMesh(meshid);
	pCarImageNode->SetName(Model);		
	pCarImageNode->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	pCarImageNode->SetEnable(1);

	/////////////////////////////cameraObject//////////////////
	CAvmRenderDataBase::GetInstance()->GetStitchViewCameraParams(&m_stitchViewCameraParams);
	
	m_stitchViewCameraId = m_stitchViewNode->CreateCamera(m_stitchViewCameraParams->fovx, m_stitchViewCameraParams->aspect, m_stitchViewCameraParams->znear, m_stitchViewCameraParams->zfar, &m_stitchViewCamera);
	
	m_stitchViewCamera->Set2DCamera(1);
	const float stitchCameraHeight = 3600.0;
	m_stitchViewCamera->SetPosition(0,0,stitchCameraHeight);
	m_stitchViewCamera->LookAt(0.0,0.0,-0.0);
	m_stitchViewCamera->RotateAround(0,45);
	m_stitchViewNode->SetCamera(m_stitchViewCameraId);

	CAvmRenderDataBase::GetInstance()->SetStitchViewNode(m_stitchViewNode);

	m_overlay = new CAvmApaBevOverlay;

	m_sonarNode = new SVNodeSonar;
	BEV_CONFIG_T bevConfig;
	AVMData::GetInstance()->GetBevConfig(&bevConfig);
    m_sonarNode->Init(&bevConfig,m_stitchViewNode);

	return TIME_STITCHER_NORMAL;
}
int CAvmTimeStitcherNode::UpdateNode()
{
	float steer_angle;
	unsigned char gear_state;
	float speed;
	float left_wheel_speed=0,right_wheel_speed=0;
	float rear_left_wheel_speed=0,rear_right_wheel_speed=0;

	float yawRate = 0.0;

	static unsigned char timeInitFlag = 0;
	static int lastTime = 0;
	int timeInterval = 0;
	int currentTime;

	currentTime = XrGetTime();
	if(timeInitFlag == 0)
	{
		timeInitFlag =1;
		timeInterval = 0;
		
	}
	else
	{
		timeInterval = currentTime-lastTime;
	}
	timeInterval=(int)(AVMData::GetInstance()->m_p_can_data->GetTimeStamp()/1000);

	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);		
	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	AVMData::GetInstance()->m_p_can_data->Get_Wheel_Speed(&right_wheel_speed, &left_wheel_speed, &rear_right_wheel_speed, &rear_left_wheel_speed);	
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);
	AVMData::GetInstance()->m_p_can_data->Get_Yaw_Rate(&yawRate);

	m_timeStitchNode->Update(steer_angle, speed,
						left_wheel_speed, right_wheel_speed,
						gear_state,timeInterval, yawRate);
	m_stitchViewMtl->SetDiffuseMap(m_timeStitchNode->GetStichFrameTextureId());
	//m_stitchViewMtl->SetDiffuseMap(m_timeStitchNode->GetKeyFrameTextureId());

	lastTime = currentTime;

	AddOverlay(m_overlay);
	
	float *pdist =	AVMData::GetInstance()->m_p_can_data->Get_Sonar_dist_list();
	m_sonarNode->Update(steer_angle, speed,
						left_wheel_speed, right_wheel_speed,
						gear_state,timeInterval, yawRate, pdist);

	return TIME_STITCHER_NORMAL;
}
int CAvmTimeStitcherNode::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_stitchViewNode == NULL
		|| m_timeStitchNode == NULL)
    {
        return TIME_STITCHER_NORMAL;
    }

	m_stitchViewNode->SetEnable(pVisibilityFlag);
	m_timeStitchNode->SetEnable(pVisibilityFlag);
    //AVMData::GetInstance()->SetStitchViewGuideLineVisibility(pVisibilityFlag);
	//AVMData::GetInstance()->SetStitchViewRadarVisibility(pVisibilityFlag);
	m_visibilityFlag = pVisibilityFlag;

	return TIME_STITCHER_NORMAL;
}
int CAvmTimeStitcherNode::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_stitchViewNode->SetClear(pColorFlag, pDepthFlag);
	return TIME_STITCHER_NORMAL;
}
int CAvmTimeStitcherNode::AddOverlay(IAvmOverlay * pOverlay)
{
	unsigned char apaControl = 1;
	static unsigned char apaInitFlag = 0;
	if(apaControl == 1
		&& apaInitFlag == 0)
	{
		pOverlay->Init(m_stitchViewNode);
		apaInitFlag = 1;
	}

	if(apaInitFlag == 1
		&& pOverlay)
	{
		pOverlay->Update();
	}
	
	return TIME_STITCHER_NORMAL;
}
int CAvmTimeStitcherNode::UpdateStich2DReslt()
{
	IMesh *pMeshTemp;
   // sv2Ddelegate->Update2DCalibRslt(pData,data_size,pIndex,index_size);
	float *pTemp;
	unsigned int BufSize;
	unsigned int totalBufSize=0;
	unsigned char* pSeamChangeFlag;
	unsigned char pSeamDataChangeFlag;
	GLfloat* pVertex;
	AVMData::GetInstance()->GetStitchAngle(pSeamDataChangeFlag, &pSeamChangeFlag, &pVertex);

	//if(pSeamDataChangeFlag == 1)
	{
		for(int i=0;i<4;i++)
		{
	   
			m_SV2DData->GetVertexBuffer(eFrontLeftMesh+i,&pTemp,&BufSize);
			if(1== pSeamChangeFlag[i])
			{
				memcpy(pTemp,pVertex+7*totalBufSize,BufSize*7*sizeof(GLfloat));
	   	
				m_timeStitchNode->UpdateStich2DReslt(i);
			}
		   
			totalBufSize+=BufSize;
		}
		AVMData::GetInstance()->SetStitchAngle(0, pSeamChangeFlag, pVertex);
	}
	
	return TIME_STITCHER_NORMAL;

}
int CAvmTimeStitcherNode::UpdateExternCalib2DReslt()
{
	GLfloat *pData;
	int data_size;
	GLushort *pIndex;
	int index_size;
	unsigned char updateFlag = 0;
    IMesh *pMeshTemp;

	AVMData::GetInstance()->Get2DParam(updateFlag, &pData, &pIndex);
	if(updateFlag == 1)
	{
		AVMData::GetInstance()->m_2D_lut->UpdateLUT(pData,pIndex);

    	m_timeStitchNode->Update2DStichRslt();

		AVMData::GetInstance()->Set2DParam(0, pData, pIndex);
	}
	return TIME_STITCHER_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmTimeStitcherNode class.
\*===========================================================================*/
