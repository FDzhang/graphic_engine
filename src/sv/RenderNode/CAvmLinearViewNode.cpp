/*===========================================================================*\
 * FILE: CAvmLinearViewNode.cpp
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
#include "CAvmLinearViewNode.h"
#include "../AVMData.h"

CAvmLinearViewNode::CAvmLinearViewNode():m_depthClearFlag(0),m_colorClearFlag(0)
{

}
CAvmLinearViewNode::~CAvmLinearViewNode()
{

}

int CAvmLinearViewNode::InitNode(class IXrCore* pXrcore)
{
	if(pXrcore == NULL)
	{
		return LINEAR_VIEW_NODE_NORMAL;
	}

	m_xrCore = pXrcore;

	#define PlaneScaleX 14000.0
	#define PlaneScaleY 17000.0
    #define PlaneScaleY_NEG  -17000.0
	
	#define ROTATE_ANGLE 30
	#define ROTATE_LENGTH 3000
//#define SIDEMIRRORDEGREE 0.5 
	int m_meshWidth = 30;
	int m_meshHeight = 30;
    float x_pos[2];
	float z_pos[2];
 	// Interleaved vertex data
	GLfloat* afVertices[3];
	
	IAProperty* rotX=0, *rotY,*posZ,*rotZ=0;
	float Rot[3]={-1.57,0,0};
	afVertices[0]= (GLfloat*)malloc(m_meshWidth*m_meshHeight*8*4);
	afVertices[1] = (GLfloat*)malloc(m_meshWidth*m_meshHeight*8*4);
	afVertices[2] = (GLfloat*)malloc(m_meshWidth*m_meshHeight*8*4);
	
	// buffer file %s,line %d,",__FILE__,__LINE__);
	unsigned short* afIndices = (unsigned short*)malloc((m_meshWidth-1)*(m_meshHeight-1)*6*2);
	
	// buffer file %s,line %d,",__FILE__,__LINE__);
	int slotId=0, x, y;
	XRMat4 Transfom=XRMat4::Scale(1.0,1.0,1.0);
	
#define	UIZ1  -11000.0f

    for(int index=0;index<3;index++)
    {
        if(index == 0)
        {
			x_pos[0]= -PlaneScaleX;
			x_pos[1]=  PlaneScaleX;
            z_pos[0] = UIZ1;
			z_pos[1]=UIZ1;
			
       	}
		else if(index == 1)
		{
		    Transfom = XRMat4::RotationY(3.1415926*(-SIDEMIRRORDEGREE));	
			x_pos[1]= -PlaneScaleX;
			x_pos[0]= -PlaneScaleX;
            z_pos[1]= UIZ1;
			z_pos[0]= 0;
		}
		else
		{
        	Transfom = XRMat4::RotationY(3.1415926*(SIDEMIRRORDEGREE)) ;	
			x_pos[0]= PlaneScaleX;
			x_pos[1]=  PlaneScaleX;
            z_pos[0]= UIZ1;
			z_pos[1]= 0;
		}
        slotId=0;
    	for (y=0; y<m_meshHeight; y++) {
    		for (x=0; x<m_meshWidth; x++) {
				#if 0
    			afVertices[index][slotId*8] = (((float)x)/(m_meshWidth-1)-0.5)*2 * PlaneScaleX;
    			afVertices[index][slotId*8+1] = (((float)y)/(m_meshHeight-1)-0.5) *2 * PlaneScaleY;
    			afVertices[index][slotId*8+2] = UIZ1;
    			afVertices[index][slotId*8+3] = (((float)x)/(m_meshWidth-1)-0.5)*2* PlaneScaleX;
    			afVertices[index][slotId*8+4] = (((float)y)/(m_meshHeight-1)-0.5)*2* PlaneScaleY;
    			afVertices[index][slotId*8+5] = UIZ1;
				#else
    			afVertices[index][slotId*8] =   x_pos[0]+x*(x_pos[1]-x_pos[0])/(m_meshWidth-1);//(((float)x)/(m_meshWidth-1)-0.5)*2 * PlaneScaleX;
    			afVertices[index][slotId*8+1] = PlaneScaleY_NEG +(PlaneScaleY-PlaneScaleY_NEG)*y/m_meshHeight; //(((float)y)/(m_meshHeight-1)-0.5) *2 * PlaneScaleY;
    			afVertices[index][slotId*8+2] = z_pos[0]+x*(z_pos[1]-z_pos[0])/(m_meshWidth-1);
    			afVertices[index][slotId*8+3] = x_pos[0]+x*(x_pos[1]-x_pos[0])/(m_meshWidth-1);
    			afVertices[index][slotId*8+4] = PlaneScaleY_NEG +(PlaneScaleY-PlaneScaleY_NEG)*y/m_meshHeight;//(((float)y)/(m_meshHeight-1)-0.5)*2* PlaneScaleY;
    			afVertices[index][slotId*8+5] = z_pos[0]+x*(z_pos[1]-z_pos[0])/(m_meshWidth-1);

				#endif
    		    AVMData::GetInstance()->CalcUVTextureSV(&afVertices[index][slotId*8],&afVertices[index][slotId*8+3],0);	
    			//CalcCrossViewUVTexture(&afVertices[index][slotId*8],&afVertices[index][slotId*8+3],2,Transfom,m_bev_config.smc.DISTORTION_MODEL);
    
    			afVertices[index][slotId*8+6] = ((float)x)/(m_meshWidth-1);
    			afVertices[index][slotId*8+7] = ((float)y)/(m_meshHeight-1);
    
    			slotId+=1;
    		}
    	}
    }

	slotId = 0;

	for (y=0; y<m_meshHeight-1; y++) {
		for (x=0; x<m_meshWidth-1; x++) {

			afIndices[slotId] = y*m_meshWidth+x;
			afIndices[slotId+1] = y*m_meshWidth+x+1;
			afIndices[slotId+2] = (y+1)*m_meshWidth+x;
			afIndices[slotId+3] = y*m_meshWidth+x+1;
			afIndices[slotId+4] = (y+1)*m_meshWidth+x;
			afIndices[slotId+5] = (y+1)*m_meshWidth+x+1;

			slotId+=6;

		}
	}

	m_180DegreeViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_180DegreeViewNode);
	
	//m_viewNode->SetClear(FALSE, TRUE);
	Region* linearViewRegion;
	CAvmRenderDataBase::GetInstance()->GetLinearViewRegion(&linearViewRegion);
	m_180DegreeViewNode->SetRenderROI(linearViewRegion);

	m_180DegreeViewNode->SetClearColor(0.0,0.0,0.0,1.0);
	int displayChannel = 0;

	m_renderDelegate = new RenderDelegateCV();
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_renderDelegate->Init();
	m_renderDelegate->SetChannel(displayChannel);
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_3D_VERTEX_SHADER);	
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_3D_FRAGMENT_SHADER);	

	IRenderEffect* pIEffect;
	m_180DegreeViewMtlId = m_180DegreeViewNode->CreateMaterial(Material_Custom, &m_180DegreeViewMtl);
	m_180DegreeViewMtl->CreateMaterialEffect(&pIEffect);
	
	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_180DegreeViewMtl,rear_camera_index); 
	pIEffect->InitShaderFromFile("Effect_SV", VertexName, FragShaderName,  sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
	pIEffect->SetRenderDelegate(m_renderDelegate);

    for(int i =0;i<3;i++)
    {
    	m_180DegreeViewMeshId[i] = m_180DegreeViewNode->CreateMesh(ModelType_Null, 0,0,0, "plane", &m_180DegreeViewMesh[i]);
    	m_180DegreeViewMesh[i]->LoadVertexFromArray(afVertices[i], XR_VERTEX_LAYOUT_PNT, m_meshWidth*m_meshHeight);
    	m_180DegreeViewMesh[i]->LoadIndexFromArray(afIndices, (m_meshWidth-1)*(m_meshHeight-1)*6*2);
    }
//#define VIEW_Z -4100
#define VIEW_Z 0

	//int mid = m_viewNode->CreateModel(0, -1, -1, InsertFlag_Default, 18000, 0, -4000, 1.0, &m_plane[0]);
	//m_plane[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X);


	int modelId = m_180DegreeViewNode->CreateModel(0, m_180DegreeViewMtlId, -1, InsertFlag_Default, 0, 0, VIEW_Z, 1.0, &m_180DegreeViewPlane[1]);
	m_180DegreeViewPlane[1]->SetMesh(m_180DegreeViewMeshId[0]);
	m_180DegreeViewPlane[1]->SetName("C");
	//cvdelegate->ProcessModel(m_plane[1],"C");
	//m_plane[1]->SetScale(0,0,1);
	m_180DegreeViewPlane[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	modelId = m_180DegreeViewNode->CreateModel(0, m_180DegreeViewMtlId, -1, InsertFlag_Default, 0, 0, VIEW_Z, 1.0, &m_180DegreeViewPlane[2]);
	m_180DegreeViewPlane[2]->SetMesh(m_180DegreeViewMeshId[1]);
	m_180DegreeViewPlane[2]->SetName("L");
	
	//cvdelegate->ProcessModel(m_plane[2],"L");
	m_180DegreeViewPlane[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y);
	modelId = m_180DegreeViewNode->CreateModel(0, m_180DegreeViewMtlId, -1, InsertFlag_Default,0, 0, VIEW_Z, 1.0, &m_180DegreeViewPlane[3]);
	m_180DegreeViewPlane[3]->SetMesh(m_180DegreeViewMeshId[2]);
	m_180DegreeViewPlane[3]->SetName("R");
	
	//cvdelegate->ProcessModel(m_plane[3],"R");
	m_180DegreeViewPlane[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y);
//#endif

	/////////////////////////////cameraObject//////////////////
	CAvmRenderDataBase::GetInstance()->GetLinearViewCameraParams(&m_180DegreerViewCameraParams);
	m_180DegreeViewCameraId = m_180DegreeViewNode->CreateCamera(m_180DegreerViewCameraParams->fovx, m_180DegreerViewCameraParams->aspect, m_180DegreerViewCameraParams->znear, m_180DegreerViewCameraParams->zfar, &m_180DegreeViewCamera);
	m_180DegreeViewNode->SetCamera(m_180DegreeViewCameraId);

	m_180DegreeViewCamera->SetPosition(0,0,0);
	
	m_180DegreeViewCamera->GetCAProperty(AP_RX, &rotX);
	
	m_180DegreeViewCamera->GetCAProperty(AP_RY, &rotY);
	rotX->Set(0);
	rotY->Set(0);
	m_180DegreeViewNode->SetCamera(m_180DegreeViewCameraId);

	return LINEAR_VIEW_NODE_NORMAL;
}
int CAvmLinearViewNode::UpdateNode()
{

	unsigned char linear180DegreeViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(linear180DegreeViewCmd);

	if(linear180DegreeViewCmd == LINEAR_FRONT_180_DEGREE_VIEW)
	{
		m_renderDelegate->SetChannel(FRONT_SINGLE_VIEW);
		m_180DegreeViewNode->SetClear(TRUE, TRUE);
	}
	else if(linear180DegreeViewCmd == LINEAR_REAR_180_DEGREE_VIEW)
	{
		m_renderDelegate->SetChannel(REAR_SINGLE_VIEW);	
		m_180DegreeViewNode->SetClear(TRUE, TRUE);
	}
	else
	{
		m_180DegreeViewNode->SetClear(m_colorClearFlag, m_depthClearFlag);
	}
	return LINEAR_VIEW_NODE_NORMAL;
}
int CAvmLinearViewNode::SetVisibility(unsigned char pVisibilityFlag)
{
	if(m_180DegreeViewNode == NULL)
    {
        return LINEAR_VIEW_NODE_INIT_FAILED;
    }

	m_180DegreeViewNode->SetEnable(pVisibilityFlag);
    //AVMData::GetInstance()->Set3dViewGuideLineVisibility(pVisibilityFlag);
	//AVMData::GetInstance()->Set3dViewRadarVisibility(pVisibilityFlag);
	m_visibilityFlag = pVisibilityFlag;
	return LINEAR_VIEW_NODE_NORMAL;
}
int CAvmLinearViewNode::ResetLinearViewNodeRegion(Region* pRegion)
{
	return LINEAR_VIEW_NODE_NORMAL;
}
	
ISceneNode*  CAvmLinearViewNode::GetAvmLinearViewNode()
{
	return m_180DegreeViewNode;
}
ICamera* CAvmLinearViewNode::GetAvmLinearViewCamera()
{
	return m_180DegreeViewCamera;
}
int CAvmLinearViewNode::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_depthClearFlag = pDepthFlag;
	m_colorClearFlag = pColorFlag;
	m_180DegreeViewNode->SetClear(pColorFlag, pDepthFlag);
	return LINEAR_VIEW_NODE_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmLinearViewNode class.
\*===========================================================================*/
