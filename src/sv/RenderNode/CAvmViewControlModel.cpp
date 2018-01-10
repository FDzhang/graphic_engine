/*===========================================================================*\
 * FILE: CAvmViewControlModel.h
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
#include "CAvmViewControlModel.h"
#include "../AVMData.h"
#include "CAvm3dViewNode.h"
#include "CAvmSingleViewNode.h"
#include "CAvmStitchViewNode.h"
#include "CAvmObjectViewNode.h"
#include "CAvmMattsView.h"
#include "CAvmLargeSingleView.h"
#include "CAvmTimeStitcherNode.h"
#include "CAvmLinearViewNode.h"
#include "CAvmLeftRightView.h"
#include "CAvmLarge3dView.h"

#include "../GlSV2D.h"


typedef struct Avm3dViewCameraParamsTag
{
	//char  viewIndex[50];
	unsigned char viewIndex;
	float postion_x;
	float postion_y;
	float postion_z;
	float look_x;
	float look_y;
	float look_z;
	float scrollX;
	float scrollY;
	float scrollZ;
	int   camPos;
}
Avm3dViewCameraParamsT;

CAvmViewControlModel::CAvmViewControlModel():m_avm3dViewNode(0),m_avmSingleViewNode(0), 
											m_avmStitchViewNode(0), m_avmObjViewNode(0),
											m_avmTimeStitcherNode(0), m_avm180DegreeView(0),
											m_avmLeftRightView(0),m_avmLarge3dView(0)
{

}
CAvmViewControlModel::~CAvmViewControlModel()
{

}
int CAvmViewControlModel::InitViewNode()
{
	unsigned char init3dViewNode = 0;
	unsigned char initStitchViewNode = 0;
	unsigned char initSingleViewNode = 0;
	unsigned char initObjViewNode = 0;


	unsigned char carTransparentStatus = 1;
	CAvmRenderDataBase::GetInstance()->SetCarTransparentStatus(&carTransparentStatus);

	//CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);

	if(carTransparentStatus == 0)
	{
		m_avmStitchViewNode = new CAvmStitchViewNode;
	}
	else
	{
		m_avmTimeStitcherNode = new CAvmTimeStitcherNode;
	}

	m_avmSingleViewNode= new CAvmSingleViewNode;
	m_avm3dViewNode= new CAvm3dViewNode;
	m_avmObjViewNode= new CAvmObjectViewNode;
	m_avm180DegreeView = new CAvmLinearViewNode;
	m_avmLeftRightView = new CAvmLeftRightView;
	m_avmLarge3dView = new CAvmLarge3dView;

	
	m_xrCore = GetXrCoreInterface();
	m_xrCore->GetDeviceManager(&m_rm);
	m_xrCore->GetAnimationManager(&m_am);

	GlSV2D* sv2d = new GlSV2D;
	sv2d->Init();
	CAvmRenderDataBase::GetInstance()->SetSv2dData(sv2d);

	CAvmRenderDataBase::GetInstance()->SetAnimationManager(m_am);

	Region Stich2DReg,SingleViewReg, SceneViewReg, crossVieRegion, linear180DegreeViewRegion, leftViewReg, rightViewReg;
	float stich2D_region[4];
    float single2D_region[4];
    float scene3D_region[4];
	float linear180DegreeRegion[4];
	float leftViewRegion[4];
	float rightViewRegion[4];

    float stich_region_width = 0.35 *  XrGetScreenWidth();

	float black_width = 80.0;
	float left_panel_width = 100.0;

	stich2D_region[REGION_POS_LEFT] = 0.0 + left_panel_width;
	stich2D_region[REGION_POS_RIGHT] = stich_region_width + left_panel_width;
	stich2D_region[REGION_POS_TOP] = 0+black_width;
	stich2D_region[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;

	single2D_region[REGION_POS_LEFT] = stich_region_width + left_panel_width;
	single2D_region[REGION_POS_RIGHT] = XrGetScreenWidth();
	single2D_region[REGION_POS_TOP] = 0+black_width;
	single2D_region[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;

	scene3D_region[REGION_POS_LEFT] = stich_region_width + left_panel_width;
	scene3D_region[REGION_POS_RIGHT] = XrGetScreenWidth();
	scene3D_region[REGION_POS_TOP] = 0+black_width;
	scene3D_region[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;

	linear180DegreeRegion[REGION_POS_LEFT] = left_panel_width;
	linear180DegreeRegion[REGION_POS_RIGHT] = XrGetScreenWidth();
	linear180DegreeRegion[REGION_POS_TOP] = 0+black_width;
	linear180DegreeRegion[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;

	leftViewRegion[REGION_POS_LEFT] = stich_region_width + left_panel_width;
	leftViewRegion[REGION_POS_RIGHT] = stich_region_width + left_panel_width + (XrGetScreenWidth() - stich_region_width)/2;
	leftViewRegion[REGION_POS_TOP] = 0+black_width;
	leftViewRegion[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;
		
	rightViewRegion[REGION_POS_LEFT] = stich_region_width + (XrGetScreenWidth() - stich_region_width)/2 + left_panel_width ;
	rightViewRegion[REGION_POS_RIGHT] = XrGetScreenWidth();
	rightViewRegion[REGION_POS_TOP] = 0+black_width;
	rightViewRegion[REGION_POS_BOTTOM] = XrGetScreenHeight()-black_width;
	
	Stich2DReg.Set(stich2D_region[REGION_POS_LEFT],stich2D_region[REGION_POS_RIGHT],stich2D_region[REGION_POS_TOP],stich2D_region[REGION_POS_BOTTOM]);
    SceneViewReg.Set(scene3D_region[REGION_POS_LEFT],scene3D_region[REGION_POS_RIGHT],scene3D_region[REGION_POS_TOP] ,scene3D_region[REGION_POS_BOTTOM]);
    SingleViewReg.Set(single2D_region[REGION_POS_LEFT],single2D_region[REGION_POS_RIGHT],single2D_region[REGION_POS_TOP],single2D_region[REGION_POS_BOTTOM]);
	crossVieRegion.Set(0,XrGetScreenWidth(),0,2 * XrGetScreenHeight());
	linear180DegreeViewRegion.Set(linear180DegreeRegion[REGION_POS_LEFT],linear180DegreeRegion[REGION_POS_RIGHT],linear180DegreeRegion[REGION_POS_TOP],linear180DegreeRegion[REGION_POS_BOTTOM]);
	leftViewReg.Set(leftViewRegion[REGION_POS_LEFT],leftViewRegion[REGION_POS_RIGHT],leftViewRegion[REGION_POS_TOP],leftViewRegion[REGION_POS_BOTTOM]);
	rightViewReg.Set(rightViewRegion[REGION_POS_LEFT],rightViewRegion[REGION_POS_RIGHT],rightViewRegion[REGION_POS_TOP],rightViewRegion[REGION_POS_BOTTOM]);


	CAvmRenderDataBase::GetInstance()->SetStitchViewRegion(&Stich2DReg);
	CAvmRenderDataBase::GetInstance()->Set3dViewRegion(&SceneViewReg);
	CAvmRenderDataBase::GetInstance()->SetObjectViewRegion(&SceneViewReg);
	CAvmRenderDataBase::GetInstance()->SetSingleViewRegion(&SingleViewReg);
	//AVMData::GetInstance()->SetFadeRegion(&SingleViewReg);
	CAvmRenderDataBase::GetInstance()->SetLinearViewRegion(&linear180DegreeViewRegion);
	CAvmRenderDataBase::GetInstance()->SetLeftRightViewRegion(&leftViewReg, left_camera_index);
	CAvmRenderDataBase::GetInstance()->SetLeftRightViewRegion(&rightViewReg, right_camera_index);

	SurroundViewCameraParamsT m_stitchCameraParams;
	SurroundViewCameraParamsT m_objectViewCameraParams;
	SurroundViewCameraParamsT m_3dViewCameraParams;	
	SurroundViewCameraParamsT m_180DegreeViewCameraParams;
	m_stitchCameraParams.fovx = 120;
	m_stitchCameraParams.aspect = Float32(XrGetScreenWidth())/XrGetScreenHeight();
	m_stitchCameraParams.znear = 10.0f;
	m_stitchCameraParams.zfar = 16000.0f;
	CAvmRenderDataBase::GetInstance()->SetStitchViewCameraParams(&m_stitchCameraParams);
	CAvmRenderDataBase::GetInstance()->SetSingleViewCameraParams(&m_stitchCameraParams);
	m_objectViewCameraParams.fovx = 35;//35;
	m_objectViewCameraParams.aspect = 1.23265302;//1.05;//1.28265302;
	m_objectViewCameraParams.znear = 4.0f;
	m_objectViewCameraParams.zfar = 12000.0f;
	CAvmRenderDataBase::GetInstance()->SetObjectViewCameraParams(&m_objectViewCameraParams);
	m_3dViewCameraParams.fovx = m_objectViewCameraParams.fovx;
	m_3dViewCameraParams.aspect = m_objectViewCameraParams.aspect;//1.23265302;
	m_3dViewCameraParams.znear = 4.0f;
	m_3dViewCameraParams.zfar = 12000.0f;
	CAvmRenderDataBase::GetInstance()->Set3dViewCameraParams(&m_3dViewCameraParams);
	m_180DegreeViewCameraParams.fovx = 151.0;
	m_180DegreeViewCameraParams.aspect = Float32(XrGetScreenWidth())/XrGetScreenHeight();//1.23265302;
	m_180DegreeViewCameraParams.znear = 10.0f;
	m_180DegreeViewCameraParams.zfar = 16000.0f;
	CAvmRenderDataBase::GetInstance()->SetLinearViewCameraParams(&m_180DegreeViewCameraParams);


	if(m_avmStitchViewNode)
	{
		if(m_avmStitchViewNode->InitNode(m_xrCore) == AVM_STITCHVIEW_NORMAL)
		{
			m_avmStitchViewNode->SetClear(TRUE,TRUE);
			initStitchViewNode = 1;
		}
	}
	if(m_avmTimeStitcherNode)
	{
		if(m_avmTimeStitcherNode->InitNode(m_xrCore) == AVM_STITCHVIEW_NORMAL)
		{
			m_avmTimeStitcherNode->SetClear(TRUE,TRUE);
			initStitchViewNode = 1;
		}
	}

	if(m_avmSingleViewNode->InitNode(m_xrCore) == AVM_SINGLEVIEW_NORMAL)
	{
		m_avmSingleViewNode->SetClear(FALSE, FALSE);
		initSingleViewNode = 1;
	}
	if(m_avm180DegreeView->InitNode(m_xrCore) == LINEAR_VIEW_NODE_NORMAL)
	{
		m_avm180DegreeView->SetClear(FALSE, FALSE);
	}
	if(m_avmLeftRightView->InitNode(m_xrCore) == LEFT_RIGHT_VIEW_NORMAL)
	{
		m_avmLeftRightView->SetClear(FALSE, FALSE);
	}	
	if(m_avm3dViewNode->InitNode(m_xrCore) == AVM_3DVIEW_NORMAL)
	{
		m_avm3dViewNode->SetClear(FALSE,FALSE);
		init3dViewNode = 1;
	}
	if(m_avmObjViewNode->InitNode(m_xrCore) == AVM_OBJVIEW_NORMAL)
	{
		m_avmObjViewNode->SetClear(FALSE,TRUE);
		initObjViewNode = 1;
	}

	CAvmRenderDataBase::GetInstance()->SetStitchViewNodeStatus(&initStitchViewNode);
	CAvmRenderDataBase::GetInstance()->SetSingleViewNodeStatus(&initSingleViewNode);
	CAvmRenderDataBase::GetInstance()->Set3dViewNodeStatus(&init3dViewNode);
	CAvmRenderDataBase::GetInstance()->SetObjectViewNodeStatus(&initObjViewNode);

	float camera_zone[4];
    camera_zone[REGION_POS_LEFT] = 0.0;
    camera_zone[REGION_POS_TOP] = 0.0;
    camera_zone[REGION_POS_RIGHT] = 1.0;
    camera_zone[REGION_POS_BOTTOM] = 1.0; 

	CAvmRenderDataBase::GetInstance()->SetLargeSingleViewRoi(camera_zone, front_camera_index);
	
	CAvmRenderDataBase::GetInstance()->SetLargeSingleViewRoi(camera_zone, left_camera_index);

	CAvmRenderDataBase::GetInstance()->SetLargeSingleViewRoi(camera_zone, right_camera_index);

	camera_zone[REGION_POS_LEFT] = 1.0;
    camera_zone[REGION_POS_TOP] = 0.0;
    camera_zone[REGION_POS_RIGHT] = 0.0;
    camera_zone[REGION_POS_BOTTOM] = 1.0; 
	CAvmRenderDataBase::GetInstance()->SetLargeSingleViewRoi(camera_zone, rear_camera_index);
	

	m_avmMattsView = new CAvmMattsView();
	m_avmMattsView->Init();

	m_avmLargeSingleView = new CAvmLargeSingleView();
	m_avmLargeSingleView->Init();

	m_avmLarge3dView = new CAvmLarge3dView();
	m_avmLarge3dView->Init();

	InitDisplayEffect();

	return AVM_VIEWCONTROLMODEL_NORMAL;
}
int CAvmViewControlModel::InitDisplayEffect()
{
	unsigned char init3dViewNode = 0;
	unsigned char initObjViewNode = 0;
	CAvmRenderDataBase::GetInstance()->Get3dViewNodeStatus(&init3dViewNode);
	CAvmRenderDataBase::GetInstance()->GetObjectViewNodeStatus(&initObjViewNode);
	if(init3dViewNode != 1
		|| initObjViewNode != 1)
	{
		return AVM_VIEWCONTROLMODEL_NORMAL;
	}

	InitBevDisplayEffect();

	InitTourDisplaySecEffect();

	IAProperty* rotX=0, *rotY,*posZ,*rotZ=0;
	IAProperty* sldX=0, *sldY=0;

	m_am->CreateScrollingAnimation(&m_scrollX);
	m_am->CreateScrollingAnimation(&m_scrollY);
	m_am->CreateScrollingAnimation(&m_sliderX);


	m_scrollX->SetRange(-180, 180, 0);
	m_scrollY->SetRange(50, 90, 1);

	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RX, &rotX);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RY, &rotY);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_Z, &posZ);
	
	m_scrollX->BindTarget(rotX);
	m_scrollY->BindTarget(rotY);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RX, &rotX);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RY, &rotY);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_Z, &posZ);	
	m_scrollX->Bind2ndTarget(rotX, 0, 1);
	m_scrollY->Bind2ndTarget(rotY, 0, 1);

	m_scrollY->DockToValue(30);
	
	m_scrollX->DockToValue(15);

	return AVM_VIEWCONTROLMODEL_NORMAL;
}
int CAvmViewControlModel::InitBevDisplayEffect()
{	
	IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
	IAProperty* val=0;
	
#define DISTANCE_SCALE	-400
#define TIME_INT   2
#define PAUSE_TIME  0.8
#define ZOOM_IN_TIME  0.4
#define ZOOM_OUT_TIME 1.2
#define ZOOM_OUT_PAUSE_TIME 1.4
#define ANIMATE_START_TIME 0.8
#define INIT_SCALE	0.05
#define INIT_SCALE_Z	0.05
#define OBJ_ZOOM_IN_DIST  1500.0
#define OBJ_ZOOM_IN_DIST_SIDE  1500.0
#define SIDE_VIEW_ANGLE_Y   20.0
#define REAR_VIEW_ANGLE_Y   20.0
#define FRONT_VIEW_ANGLE_Y   20.0
#define OBJ_ZOOM_OUT_DIST 1500.0
#define FRONT_CAMERA_LOOKAT_X  0.0
#define FRONT_CAMERA_LOOKAT_Y   -500
#define FRONT_CAMERA_LOOKAT_Z  0.0
#define REAR_CAMERA_LOOKAT_X  0.0
#define REAR_CAMERA_LOOKAT_Y   -500.0
#define REAR_CAMERA_LOOKAT_Z   0.0
#define LEFT_CAMERA_LOOKAT_X    0
#define LEFT_CAMERA_LOOKAT_Y   -500.0
#define LEFT_CAMERA_LOOKAT_Z   0.0
#define RIGHT_CAMERA_LOOKAT_X  -(LEFT_CAMERA_LOOKAT_X)
#define RIGHT_CAMERA_LOOKAT_Y  LEFT_CAMERA_LOOKAT_Y
#define RIGHT_CAMERA_LOOKAT_Z   LEFT_CAMERA_LOOKAT_Z
#define BEV_TRAVEL_CAMERA_LOOKAT_X  0
#define BEV_TRAVEL_CAMERA_LOOKAT_Y  -500
#define BEV_TRAVEL_CAMERA_LOOKAT_Z  0


	//float *key_move=0;
	float dist_state[3]={1000,10,0.1};
	float init_state[3];

	float OBJ_CAMERA_DEFAULT_HEIGHT = 3600.0;

	float key_move[]={
	0,    0,  30,  OBJ_CAMERA_DEFAULT_HEIGHT, 	0,0,0,
	ANIMATE_START_TIME,    0,  REAR_VIEW_ANGLE_Y,  1500.0,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,		
	ANIMATE_START_TIME+ZOOM_IN_TIME,	 0,  REAR_VIEW_ANGLE_Y,  OBJ_ZOOM_IN_DIST,REAR_CAMERA_LOOKAT_X,REAR_CAMERA_LOOKAT_Y,REAR_CAMERA_LOOKAT_Z,			    
	ANIMATE_START_TIME+PAUSE_TIME,	 0,  REAR_VIEW_ANGLE_Y,  OBJ_ZOOM_IN_DIST, REAR_CAMERA_LOOKAT_X,REAR_CAMERA_LOOKAT_Y,REAR_CAMERA_LOOKAT_Z,		
	ANIMATE_START_TIME+ZOOM_OUT_TIME,	 0,  REAR_VIEW_ANGLE_Y,  OBJ_ZOOM_OUT_DIST, BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,			
	ANIMATE_START_TIME+ZOOM_OUT_PAUSE_TIME,  0, REAR_VIEW_ANGLE_Y,  OBJ_ZOOM_OUT_DIST,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,		 		
	ANIMATE_START_TIME+TIME_INT,   130,    SIDE_VIEW_ANGLE_Y, 1500.0,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT+ZOOM_IN_TIME,	 130,	 SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST_SIDE,LEFT_CAMERA_LOOKAT_X,LEFT_CAMERA_LOOKAT_Y,LEFT_CAMERA_LOOKAT_Z,			
	ANIMATE_START_TIME+TIME_INT+PAUSE_TIME,   130,	SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST_SIDE,LEFT_CAMERA_LOOKAT_X,LEFT_CAMERA_LOOKAT_Y,LEFT_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT+ZOOM_OUT_TIME,	 130,	SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST, BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT+ZOOM_OUT_PAUSE_TIME,	 130,	  SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT*2,   180,    FRONT_VIEW_ANGLE_Y, 1500.0,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*2+ZOOM_IN_TIME,	 180,	  FRONT_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST,FRONT_CAMERA_LOOKAT_X,FRONT_CAMERA_LOOKAT_Y,FRONT_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*2+PAUSE_TIME,   180,	  FRONT_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST,FRONT_CAMERA_LOOKAT_X,FRONT_CAMERA_LOOKAT_Y,FRONT_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*2+ZOOM_OUT_TIME,	 180,	 FRONT_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST, BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,		
	ANIMATE_START_TIME+TIME_INT*2+ZOOM_OUT_PAUSE_TIME,	 180,	  FRONT_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT*3,   220,	 SIDE_VIEW_ANGLE_Y, 1500.0,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*3+ZOOM_IN_TIME,	 220,	 SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST_SIDE,RIGHT_CAMERA_LOOKAT_X,RIGHT_CAMERA_LOOKAT_Y,RIGHT_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*3+PAUSE_TIME,	 220,	 SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_IN_DIST_SIDE,	RIGHT_CAMERA_LOOKAT_X,RIGHT_CAMERA_LOOKAT_Y,RIGHT_CAMERA_LOOKAT_Z,
	ANIMATE_START_TIME+TIME_INT*3+ZOOM_OUT_TIME,	 220,	 SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z,	
	ANIMATE_START_TIME+TIME_INT*3+ZOOM_OUT_PAUSE_TIME,	 220,	SIDE_VIEW_ANGLE_Y, OBJ_ZOOM_OUT_DIST,BEV_TRAVEL_CAMERA_LOOKAT_X,BEV_TRAVEL_CAMERA_LOOKAT_Y,BEV_TRAVEL_CAMERA_LOOKAT_Z, 	
	ANIMATE_START_TIME+TIME_INT*4,    360,    0, 1500.0,0,0,0,
	ANIMATE_START_TIME+TIME_INT*4+PAUSE_TIME,    360,    46,OBJ_CAMERA_DEFAULT_HEIGHT,	0,0,0,		
	//ANIMATE_START_TIME+TIME_INT*5,    360,    10, 3000.0,

		};	
	//GenerateRadarWaveAnimateKey(&key_move,5.0,dist_state,init_state,2,10);
	m_am->CreateKeyAnimation(key_move, sizeof(key_move)/28, 6, &m_bevdisplay[0],AnimationStyle_KeySimpleLinear,0);
		
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RX,&val);
	m_bevdisplay[0]->BindProperty(0, val);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RY, &val);
	m_bevdisplay[0]->BindProperty(1, val);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_Z, &val);
	m_bevdisplay[0]->BindProperty(2, val);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtX,&val);
	m_bevdisplay[0]->BindProperty(3, val);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtY, &val);
	m_bevdisplay[0]->BindProperty(4, val);
	m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtZ, &val);
	m_bevdisplay[0]->BindProperty(5, val);						
	m_bevdisplay[0]->SetDeltaUpdate(0);
    
	m_am->CreateKeyAnimation(key_move, sizeof(key_move)/28, 6, &m_bevdisplay[1],AnimationStyle_KeySimpleLinear,0);
	
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RX,&val);
	m_bevdisplay[1]->BindProperty(0, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RY, &val);
	m_bevdisplay[1]->BindProperty(1, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_Z, &val);
	m_bevdisplay[1]->BindProperty(2, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtX,&val);
	m_bevdisplay[1]->BindProperty(3, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtY, &val);
	m_bevdisplay[1]->BindProperty(4, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtZ, &val);
	m_bevdisplay[1]->BindProperty(5, val);						
	m_bevdisplay[1]->SetDeltaUpdate(0);

	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::InitTourDisplaySecEffect()
{
	IAProperty* val=0;

#define fTransitionTime 4.0

	float key[]={0 ,0.0,30.0, 0,0,0,
	             fTransitionTime ,180.0,90.0, 0,0,0,
	             2*fTransitionTime,360.0,30.0 ,0,0,0,
		         2*fTransitionTime+1,360.0,45.0 ,0,0,0,
		         2*fTransitionTime+2,360.0,45.0 ,0,0,0,
    };

    m_am->CreateKeyAnimation(key, sizeof(key)/24, 5, &m_bevSecTour[0],AnimationStyle_KeyLinear,0);
    m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RX,&val);
    m_bevSecTour[0]->BindProperty(0, val);
    m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_RY,&val);
    m_bevSecTour[0]->BindProperty(1, val);
    m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtX,&val);
    m_bevSecTour[0]->BindProperty(2, val);
    m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtY,&val);
    m_bevSecTour[0]->BindProperty(3, val);
    m_avmObjViewNode->GetAvmObjViewCamera()->GetCAProperty(AP_CamAtZ,&val);
    m_bevSecTour[0]->BindProperty(4, val);


    m_am->CreateKeyAnimation(key, sizeof(key)/24, 5, &m_bevSecTour[1],AnimationStyle_KeyLinear,0);
    m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RX,&val);
    m_bevSecTour[1]->BindProperty(0, val);
    m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_RY,&val);
    m_bevSecTour[1]->BindProperty(1, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtX,&val);
	m_bevSecTour[1]->BindProperty(2, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtY,&val);
	m_bevSecTour[1]->BindProperty(3, val);
	m_avm3dViewNode->GetAvm3dViewCamera()->GetCAProperty(AP_CamAtZ,&val);
	m_bevSecTour[1]->BindProperty(4, val);
	
	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::SetCurrentView()
{
	ProcessTimeStitcher();
	ProcessSingleViewDisplay();
	ProcessLarge3dView();
	Process3dViewDisplay();
	ProcessTourView();
	ProcessMattsView();
	ProcessLargeSingleView();
	Process180DegreeView();
	ProcessLeftRightView();

	return AVM_VIEWCONTROLMODEL_NORMAL;

}
int CAvmViewControlModel::SetViewNodeVisibility(VisibilityIndexT pFuncId)
{
	unsigned char viewVisibilityFlag = 0;
	CAvmRenderDataBase::GetInstance()->Get3dViewVisibility(pFuncId, viewVisibilityFlag);
	if(m_avm3dViewNode)
	{
		m_avm3dViewNode->SetVisibility(viewVisibilityFlag);
	}
	CAvmRenderDataBase::GetInstance()->GetStitchViewVisibility(pFuncId, viewVisibilityFlag);

	static unsigned char lastViewVisibilityFlag = 255;

	if(viewVisibilityFlag != lastViewVisibilityFlag)
	{
		if(m_avmStitchViewNode)
		{
			m_avmStitchViewNode->SetVisibility(viewVisibilityFlag);
		}
		
		if(m_avmTimeStitcherNode)
		{
			m_avmTimeStitcherNode->SetVisibility(viewVisibilityFlag);
		}
		lastViewVisibilityFlag = viewVisibilityFlag;
	}
	
	CAvmRenderDataBase::GetInstance()->GetSingleViewVisibility(pFuncId, viewVisibilityFlag);
	if(m_avmSingleViewNode)
	{
		m_avmSingleViewNode->SetVisibility(viewVisibilityFlag);
	}
	CAvmRenderDataBase::GetInstance()->GetObjectViewVisibility(pFuncId, viewVisibilityFlag);
	if(m_avmObjViewNode)
	{
		m_avmObjViewNode->SetVisibility(viewVisibilityFlag);
	}
	
	CAvmRenderDataBase::GetInstance()->Get180DegreeViewVisibility(pFuncId, viewVisibilityFlag);
	if(m_avm180DegreeView)
	{
		m_avm180DegreeView->SetVisibility(viewVisibilityFlag);
	}
		
	CAvmRenderDataBase::GetInstance()->GetLeftRightViewVisibility(pFuncId, viewVisibilityFlag);
	if(m_avmLeftRightView)
	{
		m_avmLeftRightView->SetVisibility(viewVisibilityFlag);
	}
	return AVM_VIEWCONTROLMODEL_NORMAL;

}
int CAvmViewControlModel::ProcessTimeStitcher()
{
	if(m_avmTimeStitcherNode
		&& m_avmObjViewNode)
	{
		unsigned char carTransparentStatus = 0;
		CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);
		if(carTransparentStatus)
		{
			m_avmTimeStitcherNode->UpdateNode();
		}
	}
	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::Process180DegreeView()
{
	if(m_avm180DegreeView)
	{
		unsigned char linear180DegreeViewCmd = 0;
		CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(linear180DegreeViewCmd);

		if(linear180DegreeViewCmd == LINEAR_FRONT_180_DEGREE_VIEW
			|| linear180DegreeViewCmd == LINEAR_REAR_180_DEGREE_VIEW)
		{
			CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
			CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
			CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
			CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
			CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
			CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);

			m_avm180DegreeView->UpdateNode();
		}
	}

	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::ProcessSingleViewDisplay()
{
	unsigned char singleViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(singleViewCmd);

	if(singleViewCmd <= RIGHT_SINGLE_VIEW)
	{
		switch(singleViewCmd)
		{
		case FRONT_SINGLE_VIEW:
			singleViewCmd = front_camera_index;
			break;
		case REAR_SINGLE_VIEW:
			singleViewCmd = rear_camera_index;
			break;
		case LEFT_SINGLE_VIEW:
			singleViewCmd =  left_camera_index;
			break;
		case RIGHT_SINGLE_VIEW:
			singleViewCmd = right_camera_index;
			break;
		default:
			break;
		}

		CAvmRenderDataBase::GetInstance()->SetSingleViewChannel(&singleViewCmd);
		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
	}
	if(m_avmSingleViewNode)
	{
		m_avmSingleViewNode->UpdateNode();
	}
	return AVM_VIEWCONTROLMODEL_NORMAL;
}
int CAvmViewControlModel::Process3dViewDisplay()
{
	static unsigned char processTourView = 0;
	unsigned char avm3dViewCmd = 0;
	static unsigned char lastAvm3dViewCmd = 200;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(avm3dViewCmd);

	if(avm3dViewCmd > RIGHT_SINGLE_VIEW
		&& avm3dViewCmd <= BMW_REAR_3D_VIEW
		&& avm3dViewCmd != TOUR_VIEW
		&& lastAvm3dViewCmd != avm3dViewCmd)
	{
		CAvmRenderDataBase::GetInstance()->Set3dViewIndex(avm3dViewCmd);
		
		Avm3dViewMode(avm3dViewCmd);

		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);	
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		lastAvm3dViewCmd = avm3dViewCmd;

	}
	else
	{
		lastAvm3dViewCmd = avm3dViewCmd;
	}

	if(avm3dViewCmd > RIGHT_SINGLE_VIEW
		&& avm3dViewCmd <= BMW_REAR_3D_VIEW)
	{		
		if(m_avmObjViewNode)
		{
			m_avmObjViewNode->UpdateNode();
		}
	}
	return AVM_VIEWCONTROLMODEL_NORMAL;
}
int CAvmViewControlModel::ProcessTourView()
{
	static unsigned char processTourView = 0;
	unsigned char avm3dViewCmd = 0;
	static unsigned char lastAvm3dViewCmd = 200;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(avm3dViewCmd);

	if(avm3dViewCmd == TOUR_VIEW
		&& lastAvm3dViewCmd != avm3dViewCmd)
	{
		CAvmRenderDataBase::GetInstance()->Set3dViewIndex(avm3dViewCmd);	

		Avm3dViewMode(avm3dViewCmd);

		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);

		m_bevSecTour[0]->Start();
		m_bevSecTour[1]->Start();

		lastAvm3dViewCmd = avm3dViewCmd;
	}
	else if(avm3dViewCmd != TOUR_VIEW)
	{
		m_bevSecTour[0]->Stop();
    	m_bevSecTour[1]->Stop(); 
		lastAvm3dViewCmd = avm3dViewCmd;
	}

	return AVM_VIEWCONTROLMODEL_NORMAL;
}
int CAvmViewControlModel::ProcessMattsView()
{
	unsigned char mattsViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(mattsViewCmd);

	if(mattsViewCmd == MATTS_VIEW)
	{	
		mattsViewCmd = four_camera_index;
		CAvmRenderDataBase::GetInstance()->SetSingleViewChannel(&mattsViewCmd);
		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_MATTS_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_MATTS_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_MATTS_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_MATTS_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_MATTS_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_MATTS_FUNC, 0);
	}
	if(m_avmMattsView)
	{
		m_avmMattsView->Update();
	}

	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::ProcessLargeSingleView()
{
	unsigned char singleViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(singleViewCmd);

	if((singleViewCmd <= RIGHT_LARGE_SINGLE_VIEW
		&& singleViewCmd >= FRONT_LARGE_SINGLE_VIEW)
		|| (singleViewCmd >= CAMERA_DEBUG_FRONT_SINGLE_VIEW
		&& singleViewCmd <= CAMERA_DEBUG_REAR_SINGLE_VIEW)
		|| (singleViewCmd >= DVR_FRONT_SINGLE_VIEW
		&& singleViewCmd <= DVR_RIGHT_SINGLE_VIEW))
	{
		switch(singleViewCmd)
		{
		case FRONT_LARGE_SINGLE_VIEW:			
		case CAMERA_DEBUG_FRONT_SINGLE_VIEW:
		case DVR_FRONT_SINGLE_VIEW:
			singleViewCmd = front_camera_index;
			break;
		
		case CAMERA_DEBUG_REAR_SINGLE_VIEW:
		case REAR_LARGE_SINGLE_VIEW:
		case DVR_REAR_SINGLE_VIEW:
			singleViewCmd = rear_camera_index;
			break;
		case LEFT_LARGE_SINGLE_VIEW:		
		case DVR_LEFT_SINGLE_VIEW:
			singleViewCmd =  left_camera_index;
			break;
		case RIGHT_LARGE_SINGLE_VIEW:		
		case DVR_RIGHT_SINGLE_VIEW:
			singleViewCmd = right_camera_index;
			break;

		default:
			break;
		}

		CAvmRenderDataBase::GetInstance()->SetSingleViewChannel(&singleViewCmd);
		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_LARGE_SINGLVIEW_FUNC, 0);

		if(m_avmSingleViewNode)
		{
			m_avmSingleViewNode->UpdateNode();
		}
	}
	if(m_avmLargeSingleView)
	{
		m_avmLargeSingleView->Update();
	}	
	return AVM_VIEWCONTROLMODEL_NORMAL;
}

int CAvmViewControlModel::ProcessLeftRightView()
{
	unsigned char leftRightViewCmd = 0;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(leftRightViewCmd);

	if(leftRightViewCmd == LEFT_RIGHT_LINEAR_VIEW)
	{
		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_VIEW_DISPLAY_FUNC, 1);

	}
	
	return AVM_VIEWCONTROLMODEL_NORMAL;

}
int CAvmViewControlModel::ProcessLarge3dView()
{	
	unsigned char large3dViewCmd = 0;
	static unsigned char lastLarge3dViewCmd = 255;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(large3dViewCmd);

	if(large3dViewCmd == TOUR_LARGE_3D_VIEW
		&& lastLarge3dViewCmd != large3dViewCmd)
	{
		CAvmRenderDataBase::GetInstance()->Set3dViewIndex(TOUR_VIEW);
		Avm3dViewMode(TOUR_VIEW);
		CAvmRenderDataBase::GetInstance()->Set3dViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->SetStitchViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetSingleViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 0);
		CAvmRenderDataBase::GetInstance()->SetObjectViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 1);
		CAvmRenderDataBase::GetInstance()->Set180DegreeViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 0);	
		CAvmRenderDataBase::GetInstance()->SetLeftRightViewVisibility(PROCESS_LARGE_3DVIEW_FUNC, 0);
	
		lastLarge3dViewCmd = large3dViewCmd;

	}
	if(m_avmLarge3dView)
	{
		m_avmLarge3dView->Update();
	}	

	return AVM_VIEWCONTROLMODEL_NORMAL;

}

int CAvmViewControlModel::SetViewNodeVisibility(ViewNodeVisibilityT pViewNodeVisibility[AVM_VIEW_NODE_NUMS])
{

/*	AVMData::GetInstance()->Set3dViewVisibility(pViewNodeVisibility[AVM_3D_VIEW_NODE].funcId, pViewNodeVisibility[AVM_SINGLE_VIEW_NODE].flag);
	AVMData::GetInstance()->SetStitchViewVisibility(pViewNodeVisibility[AVM_STITCH_VIEW_NODE].funcId, pViewNodeVisibility[AVM_STITCH_VIEW_NODE].flag);
	AVMData::GetInstance()->SetSingleViewVisibility(pViewNodeVisibility[AVM_SINGLE_VIEW_NODE].funcId, pViewNodeVisibility[AVM_TIME_STITCHER_VIEW_NODE].flag);
	AVMData::GetInstance()->SetObjectViewVisibility(pViewNodeVisibility[AVM_OBJECT_VIEW_NODE].funcId, pViewNodeVisibility[AVM_OBJECT_VIEW_NODE].flag);
	AVMData::GetInstance()->SetLargeSingleViewVisibility(pViewNodeVisibility[AVM_MATTS_VIEW_NODE].funcId, pViewNodeVisibility[AVM_MATTS_VIEW_NODE].flag);
	AVMData::GetInstance()->SetStitchViewVisibility(pViewNodeVisibility[AVM_LARGESINGLE_VIEW_NODE].funcId, pViewNodeVisibility[AVM_LARGESINGLE_VIEW_NODE].flag);
	AVMData::GetInstance()->Set180DegreeViewVisibility(pViewNodeVisibility[AVM_LINEAR_180VIEW_NODE].funcId, pViewNodeVisibility[AVM_LINEAR_180VIEW_NODE].flag);
	AVMData::GetInstance()->SetObjectViewVisibility(pViewNodeVisibility[AVM_LEFT_RIGHT_VIEW_NODE].funcId, pViewNodeVisibility[AVM_LEFT_RIGHT_VIEW_NODE].flag);
*/
	return AVM_VIEWCONTROLMODEL_NORMAL;

}

int CAvmViewControlModel::Avm3dViewMode(unsigned char pViewIndex)
{
	 Avm3dViewCameraParamsT cameraParams[BMW_REAR_3D_VIEW - FRONT_3D_VIEW + 1] = 
	{   {FRONT_3D_VIEW, 0.0, 0.0, 3600.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, CameraPosition_Free}, //rear 3d
		//{FRONT_3D_VIEW, 0.0, 0.0, 2820.0, 0.0, 0.0, -580.0, 0.0, 25.0, 0.0, CameraPosition_Free},
		{REAR_3D_VIEW, 0.0, 0.0, 3600.0, 0.0, 0.0, 0.0, 180.0, 25.0, 0.0, CameraPosition_Free},
		{LEFT_FRONT_3D_VIEW, 1000.0, 100.0, 2000.0, 800.0, 100.0, 500.0, -10.0, 75.0, 0.0, CameraPosition_Left},
		{RIGHT_FRONT_3D_VIEW, 400.0, 0.0, 3500.0, 400.0, 0.0, 0.0, 0.0, 25.0, 0.0, CameraPosition_Right},
		{LEFT_REAR_3D_VIEW, -400.0, 0.0, 3500.0, -400.0, 0.0, 0.0, 180.0, 25.0, CameraPosition_Left_Rear},
		{RIGHT_REAR_3D_VIEW, 400.0, 0.0, 3500.0, 400.0, 0.0, 0.0, 180.0, 25.0, 0.0, CameraPosition_Right_Rear},
		{LEFT_TURN_SIGNAL_3D_VIEW, -400.0, 0.0, 3500.0, -400.0, 0.0, 0.0, 0.0, 50.0, 0.0, CameraPosition_Left_Front},
		{RIGHT_TURN_SIGNAL_3D_VIEW, 400.0, 0.0, 3500.0, 400.0, 0.0, 0.0, 0.0, 50.0, 0.0, CameraPosition_Right_Front},
		{LEFT_REAR_TURN_SIGNAL_3D_VIEW, -400.0, 0.0, 3500.0, -400.0, 0.0, 0.0, 180.0, 50.0, 0.0, CameraPosition_Left_Rear_Light},
		{RIGHT_REAR_TURN_SIGNAL_3D_VIEW, 400.0, 0.0, 3500.0, 400.0, 0.0, 0.0, 180.0, 50.0, 0.0, CameraPosition_Right_Rear_Light},
		{LEFT_HIGHT_SPEED_TURN_3D_VIEW, 400.0, 0.0, 3500.0, 400.0, 0.0, 0.0, 180.0, 25.0, 0.0, CameraPosition_Left_Front_Light},
		{RIGHT_HIGHT_SPEED_TURN_3D_VIEW, -400.0, 0.0, 3500.0, -400.0, 0.0, 0.0, 180.0, 25.0, 0.0, CameraPosition_Right_Front_Light},
		{TOUR_VIEW, 0.0, 0.0, 2600.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, CameraPosition_Free},
		{BOSH_FRONT_VIEW, 0.0, -500.0, -20.0, 0.0, -500.0, -40.0, 0.0, 0.0, 0.0, CameraPosition_BOSCH_Front},
		{BOSH_FRONT_VIEW_TOP, 0.0, 800.0, -520.0, 0.0, 800.0, -1040.0, 0.0, 90.0, 0.0, CameraPosition_BOSCH_Front_Top},
		{BOSH_REAR_VIEW_TOP, 0.0, 400.0, 560.0, 0.0, 400.0, 1120.0, 0.0, 90.0, 0.0, CameraPosition_BOSCH_Rear_Top_REVERSE},
		{LEFT_MIRROR_VIEW, 0.0, 400.0, 560.0, 0.0, 400.0, 1120.0, 0.0, 90.0, 0.0, CameraPosition_BOSCH_Rear_Top_REVERSE},
		{RIGHT_MIRROR_VIEW, 0.0, 400.0, 560.0, 0.0, 400.0, 1120.0, 0.0, 90.0, 0.0, CameraPosition_BOSCH_Rear_Top_REVERSE},
	 	{BMW_REAR_VIEW, -3600.0, 0.0, 0.0, -300.0, 0.0, 25.0 , 0.0, CameraPosition_BMW_3D_Rear},
		{BMW_LEFT_VIEW, -3600.0, -100.0, 0.0, 0.25*(-3600.0), -100.0, 0.0, 0.0, 38.0, 0.0,CameraPosition_BMW_Left}, //left 3d
		{BMW_RIGHT_VIEW, 3600.0, -100.0, 0.0, 0.25*(3600.0), -100.0, 0.0, 0.0, 38.0, 0.0, CameraPosition_BMW_Right}, //right 3d
		{BMW_LEFT_FRONT_VIEW, -2000.0, -100.0, -2250.0,  0.25*(-2000.0), -100.0, 0.3*(-2250.0), 0.0, 38.0, 0.0, CameraPosition_BMW_Left_Front}, //front left 3d
		{BMW_RIGHT_FRONT_VIEW, 2000.0, -100.0, -2250.0,  0.25*(2000.0), -100.0, 0.3*(-2250.0), 0.0, 38.0, 0.0, CameraPosition_BMW_Right_Front}, //front right 3d
		{BMW_LEFT_REAR_VIEW, -1150.0, -100.0, 2950.0, 0.5*(-1150.0), -100.0, 0.2*(2950.0), 0.0, 38.0, 0.0, CameraPosition_BMW_Left_Rear}, //rear left 3d
		{BMW_RIGHT_REAR_VIEW, 1150.0, -100.0, 2950.0, 0.5*(1150.0), -100.0, 0.2*(2950.0), 0.0, 38.0, 0.0, CameraPosition_BMW_Right_Rear}, //rear right 3d
	    {BMW_REAR_3D_VIEW, 0.0, 0.0, -3600.0, 0.0, 0.0, -300.0, 0.0, 25.0 , 0.0, CameraPosition_BMW_3D_Rear}, //front 3d
		//{BMW_REAR_3D_VIEW, 0.0, 0.0, 3000.0, 0.0, 0.0, -600.0, 0.0, 22.0 , 0.0, CameraPosition_BMW_3D_Rear},

	};


	m_avm3dViewNode->GetAvm3dViewCamera()->SetPosition(cameraParams[pViewIndex - FRONT_3D_VIEW].postion_x, cameraParams[pViewIndex - FRONT_3D_VIEW].postion_y, cameraParams[pViewIndex - FRONT_3D_VIEW].postion_z);
	m_avm3dViewNode->GetAvm3dViewCamera()->LookAt(cameraParams[pViewIndex - FRONT_3D_VIEW].look_x,cameraParams[pViewIndex - FRONT_3D_VIEW].look_y,cameraParams[pViewIndex - FRONT_3D_VIEW].look_z);

	m_avmObjViewNode->GetAvmObjViewCamera()->SetPosition(cameraParams[pViewIndex - FRONT_3D_VIEW].postion_x, cameraParams[pViewIndex - FRONT_3D_VIEW].postion_y, cameraParams[pViewIndex - FRONT_3D_VIEW].postion_z);
	m_avmObjViewNode->GetAvmObjViewCamera()->LookAt(cameraParams[pViewIndex - FRONT_3D_VIEW].look_x,cameraParams[pViewIndex - FRONT_3D_VIEW].look_y,cameraParams[pViewIndex - FRONT_3D_VIEW].look_z);

	m_scrollX->DockToValue(0);
	m_scrollY->DockToValue(25);


	 return AVM_VIEWCONTROLMODEL_NORMAL;
 }
int CAvmViewControlModel::UpdateStitchAngle()
{
	if(m_avmTimeStitcherNode)
	{
		m_avmTimeStitcherNode->UpdateStich2DReslt();
	}
	return AVM_VIEWCONTROLMODEL_NORMAL;

}
int CAvmViewControlModel::UpdateExternCalib2DReslt()
{
	if(m_avmTimeStitcherNode)
	{
		m_avmTimeStitcherNode->UpdateExternCalib2DReslt();
	}	
	return AVM_VIEWCONTROLMODEL_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/23/17   Jensen Wang   Create the CAvmViewControlModel class.
\*===========================================================================*/
