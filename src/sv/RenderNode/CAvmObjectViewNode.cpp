/*===========================================================================*\
 * FILE: CAvmObjectViewNode.cpp
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
#include "CAvmObjectViewNode.h"
#include "../SVNode2DStich.h"
#include "../AVMData.h"
#include "gpu_log.h"


static char GREENTEX[] = XR_RES"green.bmp";
static char BLUETEX[] = XR_RES"blue.bmp";
static char CARENV[] = XR_RES"env.bmp";

static char BMWCARMODEL[] = XR_RES"bmw.mqo";
static char BMWCARTEX[] = XR_RES"texture.dds";
static char BMWCARTEXMASK[] = XR_RES"carmask.bmp";

static char MirrorModel[]=XR_RES"biekemirror.mqo";

static char VANMODEL[] = XR_RES"van.mqo";
static char VANWHEELMODEL[] = XR_RES"vanwheel.mqo";
static char VANRIGHTWHEELMODEL[] = XR_RES"vanwheelright.mqo";
static char VANTEX[] = XR_RES"truckUV90.tga";
static char VANTEXMASK[] = XR_RES"van_mask.bmp";

static char TRUCKMODEL[] = XR_RES"truck.mqo";
static char OTHERTEX[] = XR_RES"texture_other.dds";
static char OTHERTEXMASK[] = XR_RES"mask_other.bmp";

static char *RADARALARMTEX[4] = {XR_RES"red.dds",XR_RES"orange.dds",XR_RES"yellow.dds",XR_RES"green.dds"};

/////////////////////////////////////////////////////////////////////////////////////////////////////
/*static char CAR2DICONBMP[] = XR_RES"Car/sv_car_icon.dds";
static char CARINTTEX[]=XR_RES"Car/car_int_tex.bmp";
static char CARTEXMASK[] = XR_RES"Car/mask1.bmp";
static char CARAMBIENTTEXTMASK[] = XR_RES"Car/car_mask.bmp";
static char CARTEX[] = XR_RES"Car/car_surface.tga";

static char WHEELMODEL[] = XR_RES"Car/wheel.mqo";

static char CARMODEL[] = XR_RES"Car/frame.mqo";
static char CARLIGHTMODEL[] = XR_RES"Car/light.mqo";
static char CARINTMODEL[] = XR_RES"Car/internal.mqo";
static char CARWINDOWMODEL[] = XR_RES"Car/window.mqo";

static char CARLIGHTON[]=XR_RES"Car/light_on.tga";
static char CARLIGHTTEX[]=XR_RES"Car/light.tga";

static char *CARDOORMODEL[4] = {XR_RES"Car/driver_door.mqo",XR_RES"Car/driver_assist_door.mqo",XR_RES"Car/left_rear.mqo",XR_RES"Car/right_rear.mqo"};
static char *CARDOORWINDOWMODEL[4] = {XR_RES"Car/driver_door_w.mqo",XR_RES"Car/driver_assist_door_w.mqo",XR_RES"Car/left_rear_w.mqo",XR_RES"Car/right_rear_w.mqo"};
*/
//------------------------------------
static char CAR2DICONBMP[] = XR_RES"car_icon_rx5.dds";
static char WHEELMODEL[] = XR_RES"envisionwheelsingle.mqo";
static char WHEELMODELRIGHT[] = XR_RES"rx5wheelsingleright.mqo";

static char CARMODEL[] = XR_RES"envision_frame.mqo";
static char CARLIGHTMODEL[] = XR_RES"envision_light.mqo";
static char CARINTMODEL[] = XR_RES"envision_internal.mqo";
static char CARWINDOWMODEL[] = XR_RES"envision_window.mqo";

static char CARLIGHTTEX[]=XR_RES"envision_light.tga";
static char CARINTTEX[]=XR_RES"envision_int_tex.bmp";
static char *CARDOORMODEL[4] = {XR_RES"envision_driver_door.mqo",XR_RES"envision_driver_assist_door.mqo",XR_RES"envision_left_rear.mqo",XR_RES"envision_right_rear.mqo"};
static char *CARDOORWINDOWMODEL[4] = {XR_RES"envision_driver_door_w.mqo",XR_RES"envision_driver_assist_door_w.mqo",XR_RES"envision_left_rear_w.mqo",XR_RES"envision_right_rear_w.mqo"};
static char CARTEX[] = XR_RES"envision_black.tga";
static char CARTEX1[] = XR_RES"envision_white.tga";
static char CARAMBIENTTEXTMASK[] = XR_RES"envision_mask.bmp";
static char CARLIGHTON[]=XR_RES"envision_light_on.tga";
static char CARTEXMASK[] = XR_RES"mask1.bmp";
CAvmObjectViewNode::CAvmObjectViewNode():m_objViewCameraParams(0),m_am(0)
{

}
CAvmObjectViewNode::~CAvmObjectViewNode()
{

}
int CAvmObjectViewNode::InitNode(class IXrCore* pXrcore)
{
    if(pXrcore == NULL)
	{
		return AVM_OBJVIEW_XRCORE_NULL;
	}
	m_xrCore = pXrcore;

	int modelId;
    
	float f_camera_aspect;
	Int32 iSUVmtlId;
	Int32 iVanmtlId;
	Int32 iTruckMtlId;
    Int32 iRadarMtlId;
	Int32 iCarLightMtlId,iCarnodeId;

	///////////////////////Object Node/////////////////////////
	m_objViewNodeId = m_xrCore->CreateRenderNodeScene(0, &m_objViewNode);

	m_objViewNode->SetClear(FALSE, TRUE);
	CAvmRenderDataBase::GetInstance()->SetObjectViewNode(m_objViewNode);

    Region* objViewNodeAera = NULL;
    CAvmRenderDataBase::GetInstance()->GetObjectViewRegion(&objViewNodeAera);
    m_objViewNode->SetRenderROI(objViewNodeAera);

	IMaterial* carmtl;
	IMaterial *carlightmtl;
	float door_offset_x;
	float door_offset_y;

    IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
    float ground_width, ground_height;
	INode *ground;

	Bev_3D_Param_T*  bev_3d_param;
    AVMData::GetInstance()->m_usc_data->GetBev3DParam(&bev_3d_param);

    float pos[3]; 
    pos[0] = bev_3d_param->car_model_param.car_pos_x;
    pos[1] = bev_3d_param->car_model_param.car_pos_y;
    pos[2] = bev_3d_param->car_model_param.car_pos_z;
    
    float scale[3];
    scale[0]= bev_3d_param->car_model_param.car_scale_x;
    scale[1]= bev_3d_param->car_model_param.car_scale_y;
    scale[2]= bev_3d_param->car_model_param.car_scale_z;

	tempmaterialid = m_objViewNode->CreateMaterial(Material_Rigid_Texture, &tempcarmtl);
	tempcarmtl->SetDiffuseMap(GREENTEX);
	tempcarmtl->SetEnvironmentMap(BLUETEX);
	m_3dGroundMtl = tempcarmtl;

	Calc3DGroundPos(pos,&ground_width,&ground_height);

    unsigned char isCarTransparentMode = 0;
    CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&isCarTransparentMode);

	if(isCarTransparentMode)
	{
		int lisenceMeshId = m_objViewNode->CreateMesh(ModelType_Plane_Dynamic, 2,2, 0, "ground", &m_groundMesh);
		int groundId = m_objViewNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, 0.0,0.0,0.0,1.0, &m_ground);
		m_ground->SetMesh(lisenceMeshId);
		m_ground->SetEnable(1);
		Calc3DGroundTexture();

	}
	else
	{
		int lisenceMeshId = m_objViewNode->CreateMesh(ModelType_Plane, ground_width/2.0,ground_height/2.0, 0, "ground", &m_groundMesh);
		int groundId = m_objViewNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, pos[0],pos[1],pos[2],1.0, &m_ground);
		m_ground->SetMesh(lisenceMeshId);
		m_ground->RotateDX(90);	
		m_ground->SetEnable(1);
	}

	float opacity = 1.0;
	
	IMaterial* carInternalMtl;
    m_carInternalId = m_objViewNode->CreateMaterial(Material_Glossy_Alpha, &carInternalMtl);
	carInternalMtl->SetOpacity(((opacity - 0.1) > 0.001) ? (opacity - 0.1) : 0.001);
	carInternalMtl->SetDiffuseMap(CARINTTEX);
	carInternalMtl->SetEnvironmentMap(CARENV);
	carInternalMtl->SetAmbientMap(CARTEXMASK);
	iCarnodeId = m_objViewNode->LoadModelFromFile(CARINTMODEL, m_carInternalId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z, 50, &m_CarInternal); //envision

	m_CarInternal->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_CarInternal->SetEnable(1);
	
	m_CarInternal->RotateDY(0);

	m_carmtlId = m_objViewNode->CreateMaterial(Material_Glossy_Alpha, &m_carMtl);
	m_carMtl->SetOpacity(opacity);
	m_carMtl->SetDiffuseMap(CARTEX);
	m_carMtl->SetEnvironmentMap(CARENV);
	m_carMtl->SetAmbientMap(CARAMBIENTTEXTMASK);
	m_carId = m_objViewNode->LoadModelFromFile(CARMODEL, m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z, 50, &m_Car); //envision

	m_Car->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_Car->SetEnable(1);
	
	m_Car->RotateDY(0);

    door_offset_x = bev_3d_param->car_model_param.door_offset_side * 50 * bev_3d_param->car_model_param.car_scale_x;
    door_offset_y = bev_3d_param->car_model_param.door_offset_front * 50 * bev_3d_param->car_model_param.car_scale_z;

	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORMODEL[0], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x-door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z-door_offset_y, 50, &m_CarDoor[0]); //envision

	m_CarDoor[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[0]->SetEnable(1);

	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORMODEL[1], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x+door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z-door_offset_y, 50, &m_CarDoor[1]); //envision

	m_CarDoor[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[1]->SetEnable(1);	
	//m_CarDoor[0]->RotateDY(60);

	door_offset_y =  bev_3d_param->car_model_param.door_offset_rear * 50 * bev_3d_param->car_model_param.car_scale_z;

	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORMODEL[2], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x-door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z+door_offset_y, 50, &m_CarDoor[2]); //envision


	m_CarDoor[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[2]->SetEnable(1);	


	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORMODEL[3], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x+door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z+door_offset_y, 50, &m_CarDoor[3]); //envision

	m_CarDoor[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[3]->SetEnable(1);	

	iCarLightMtlId = m_objViewNode->CreateMaterial(Material_Glossy_Alpha, &m_carLightMtl);
	m_carLightMtl->SetDiffuseMap(CARLIGHTTEX);
	m_carLightMtl->SetOpacity(opacity);
	//carlightmtl->SetDiffuseMap(CARTEX);
	
	m_carLightMtl->SetEnvironmentMap(CARLIGHTON);
	m_carLightMtl->SetAmbientMap(CARTEXMASK);
	iCarnodeId = m_objViewNode->LoadModelFromFile(CARLIGHTMODEL, iCarLightMtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z, 50, &m_CarLight); //envision

	m_carLightMtl->SetAmbientColor(1.0,0.5,0.0,0.0);

	m_CarLight->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_CarLight->SetEnable(1);
	
	m_CarLight->RotateDY(0);


    door_offset_x = bev_3d_param->car_model_param.door_window_offset_side * 50 * bev_3d_param->car_model_param.car_scale_x;
    door_offset_y = bev_3d_param->car_model_param.door_window_offset_front * 50 * bev_3d_param->car_model_param.car_scale_z;


	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORWINDOWMODEL[0], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x-door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z-door_offset_y, 50, &m_carWindow[0]); //envision

	m_carWindow[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_carWindow[0]->SetEnable(1);


	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORWINDOWMODEL[1], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x+door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z-door_offset_y, 50, &m_carWindow[1]); //envision

	m_carWindow[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_carWindow[1]->SetEnable(1);	


    door_offset_y = bev_3d_param->car_model_param.door_window_offset_rear * 50 * bev_3d_param->car_model_param.car_scale_z;

	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORWINDOWMODEL[2], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x-door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z+door_offset_y, 50, &m_carWindow[2]); //envision

	m_carWindow[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_carWindow[2]->SetEnable(1);	


	iCarnodeId = m_objViewNode->LoadModelFromFile(CARDOORWINDOWMODEL[3], m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x+door_offset_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z+door_offset_y, 50, &m_carWindow[3]); //envision

	m_carWindow[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_carWindow[3]->SetEnable(1);	


	iCarnodeId = m_objViewNode->LoadModelFromFile(CARWINDOWMODEL, m_carmtlId, -1, InsertFlag_Default, bev_3d_param->car_model_param.car_pos_x, bev_3d_param->car_model_param.car_pos_y, bev_3d_param->car_model_param.car_pos_z, 50, &m_carWindow[4]); //envision


	m_carWindow[4]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_carWindow[4]->SetEnable(1);
	
	m_carWindow[4]->RotateDY(0);	

#define WHEEL_X_OFFSET 380
#define WHEEL_Y_OFFSET 30
#define WHEEL_ZF_OFFSET 680
#define WHEEL_ZB_OFFSET 730

	IMesh *p_van_wheel;
	IMesh *p_van_wheel_right;

	int wheelMeshId = m_objViewNode->CreateMesh(ModelType_Null, 0,0,0,"wheel", &m_wheelMesh);
	m_wheelMesh->LoadFromFile(WHEELMODEL, bev_3d_param->car_model_param.wheel_model_scale, FALSE);

    modelId = m_objViewNode->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, bev_3d_param->car_model_param.wheel_offset_side, bev_3d_param->car_model_param.wheel_offset_up, -bev_3d_param->car_model_param.wheel_offset_front, 1.1, &m_wheel[0]);
    modelId = m_objViewNode->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, -bev_3d_param->car_model_param.wheel_offset_side, bev_3d_param->car_model_param.wheel_offset_up, -bev_3d_param->car_model_param.wheel_offset_front, 1.1, &m_wheel[1]);
    modelId = m_objViewNode->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, bev_3d_param->car_model_param.wheel_offset_side, bev_3d_param->car_model_param.wheel_offset_up, bev_3d_param->car_model_param.wheel_offset_rear, 1.1, &m_wheel[2]);
    modelId = m_objViewNode->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, -bev_3d_param->car_model_param.wheel_offset_side, bev_3d_param->car_model_param.wheel_offset_up, bev_3d_param->car_model_param.wheel_offset_rear, 1.1, &m_wheel[3]);
	//SetupLisence();

	m_wheel[0]->SetMesh(wheelMeshId);
	m_wheel[1]->SetMesh(wheelMeshId);
	
	m_wheel[2]->SetMesh(wheelMeshId);
	m_wheel[3]->SetMesh(wheelMeshId);

	
#define	TURN_DEGREE 3.14/5
	//init wheel rotation key
	float key[]={
		0,		0,		0, 
		2.0,	0.07,	0,
		6.0,	0.1,	0.1,
		10.0,	0.2,	0,
		20.0,	0.15,	-0.1,
		24.0,	0.0,	0.0};
	
	CAvmRenderDataBase::GetInstance()->GetAnimationManager(&m_am);
	m_am->CreateKeyAnimation(key, sizeof(key)/12,2, &m_wheelRot);
		
	IAProperty* val=0;
	
	int wheel_max_num = 4;
	
	for (int i = 0;i < wheel_max_num; i++)	
	{
		m_wheel[i]->GetCAProperty(AP_RX, &val);
		m_wheelRot->BindProperty(0, val);
		if (i%4<2) {
		m_wheel[i]->GetCAProperty(AP_RY, &val);
		m_wheelRot->BindProperty(1, val);
		}
	}
	m_wheelRot->SetDeltaUpdate(0);

	CAvmRenderDataBase::GetInstance()->GetObjectViewCameraParams(&m_objViewCameraParams);

	m_objViewCameraId = m_objViewNode->CreateCamera(m_objViewCameraParams->fovx, m_objViewCameraParams->aspect, 
													m_objViewCameraParams->znear, m_objViewCameraParams->zfar, &m_objViewCamera);

	const float objectCameraDefaultHeight = 3600.0;
	m_objViewCamera->SetPosition(0, 0, objectCameraDefaultHeight);
	m_objViewCamera->LookAt(0.0,0,-0.0);
	m_objViewNode->SetCamera(m_objViewCameraId);
    
    m_Car->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
    m_CarLight->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
    m_CarInternal->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
		
    m_CarDoor[0]->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
    m_CarDoor[1]->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
    m_CarDoor[2]->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
    m_CarDoor[3]->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);	
   
    for(int i =0;i<5;i++)
	{
		m_carWindow[i]->SetScale(bev_3d_param->car_model_param.car_scale_x, bev_3d_param->car_model_param.car_scale_y, bev_3d_param->car_model_param.car_scale_z);
	}

    return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::UpdateNode()
{
	ProcessDoorStatus();
	ProcessWheelTurn();
	ProcessWheelRoll();

	unsigned char carTransparentStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);
	if(carTransparentStatus)
	{
		static SVNode2DStich* timeStitchNode =  NULL;
		if(timeStitchNode == NULL)
		{
			CAvmRenderDataBase::GetInstance()->GetTimeStitcherNode(&timeStitchNode);
		}
		m_3dGroundMtl->SetDiffuseMap(timeStitchNode->GetGroundTextureId());
	}
	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::ProcessWheelTurn()
{
	IAProperty *val;
	float wheel_angle = 0.0;
	float steeringWheel = 0.0;
	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steeringWheel);

	wheel_angle = -(steeringWheel/600.0)*60.0*3.1415926/180.0;

	int wheelNumbers = 0;
	wheelNumbers = 4;

    for (int i=0;i<wheelNumbers;i++)
	{

	   if (i%4<2) {
	   m_wheel[i]->GetCAProperty(AP_RY, &val);
	   val->Set(wheel_angle);
	   }
	}

	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::ProcessWheelRoll()
{
	static int vehicleState = 1;
    static float vehicleSpeed = 0.0;
    static float lastVehicleSpeed = 0.0;

	unsigned char gearState = 0;
	float speed = 0.0;

	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gearState);
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);

    if(vehicleSpeed > 6.29 )
    {
        vehicleSpeed = 0.0;
    }
    if(GEAR_R == gearState)
    {
        vehicleState = -1;
    }
    else
    {
        vehicleState = 1;
    }

    vehicleSpeed += (0.005 * speed) ;

    IAProperty* val=0;
	int wheelNumbers = 0;
	wheelNumbers = 4;

    for (int i=0;i<wheelNumbers;i++)
    {
        m_wheel[i]->GetCAProperty(AP_RX, &val);
        val->Set(vehicleState * vehicleSpeed);
    }
	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::Calc3DGroundTexture()
{
	float car_rect_image[4];
	float car_rect_adjust[4];
	float texture[4];
	float *pVertexData;
	XRVertexLayout data_format;
    int icount;
	IMesh *groundmesh;
	float pos[3];
	float ground_width,ground_height;
	Calc3DGroundPos(pos,&ground_width,&ground_height);

	for (int i =0; i<4;i++)
	{
		AVMData::GetInstance()->m_2D_lut->GetCarRect(&car_rect_image[i],i);
		AVMData::GetInstance()->m_2D_lut->GetCarShadowAdjust(&car_rect_adjust[i],i);
	    car_rect_adjust[i]=car_rect_image[i]+car_rect_adjust[i];
	}

	SVNode2DStich* stitchNode = NULL;
	CAvmRenderDataBase::GetInstance()->GetTimeStitcherNode(&stitchNode);
	if(stitchNode)
    {
		stitchNode->CalcShadowTextureCoord(car_rect_image,car_rect_adjust,texture);
	}
	else
	{
		return AVM_OBJVIEW_NODE_INIT_FAILED;
	}
	m_ground->GetMesh(&groundmesh);
	m_groundMesh->LockData(&pVertexData,&data_format,&icount);
    pVertexData[0] = pos[0]-ground_width/2.0;
    pVertexData[1] = pos[1];
	pVertexData[2] = pos[2]-ground_height/2.0;
	pVertexData[6]=texture[rect_left];
	pVertexData[7]=1-texture[rect_bottom];
	
    pVertexData[8] = pos[0]+ground_width/2.0;
	
    pVertexData[9] = pos[1];
	pVertexData[10] = pos[2]-ground_height/2.0;	
	pVertexData[14]=texture[rect_right];
	pVertexData[15]=1-texture[rect_bottom];
	pVertexData[16] = pos[0]-ground_width/2.0;
	
    pVertexData[17] = pos[1];
	pVertexData[18] = pos[2]+ground_height/2.0;
	pVertexData[22]=texture[rect_left];
	pVertexData[23]=1-texture[rect_top];	
	pVertexData[24] = pos[0]+ground_width/2.0;
	
    pVertexData[25] = pos[1];
	pVertexData[26] = pos[2]+ground_height/2.0;
	pVertexData[30]=texture[rect_right];
	pVertexData[31]=1-texture[rect_top];		

	
    groundmesh->UnLockData();

	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::Calc3DGroundPos(float *pPose,float *pWidth,float*pHeight)
{
	float car_point[4];
	GpuCvPoint2D32f car_rect[2];
    float car_adjust_point[4];
	GpuCvPoint2D32f car_rect_world[2];
	float pModelPoint[6];
	float pWorldPint[6];
	
    int i=0;


	for(i=0;i<4;i++)
	{
	    AVMData::GetInstance()->m_2D_lut->GetCarRect(&car_point[i],i);
		
	    //AVMData::GetInstance()->m_2D_lut->GetCarShadowAdjust(&car_adjust_point[i],i);
		//car_point[i]+=car_adjust_point[i];
	}

	car_rect[0].x = car_point[rect_left];
	car_rect[0].y = car_point[rect_top];
	car_rect[1].x = car_point[rect_right];
	car_rect[1].y = car_point[rect_bottom];
	
    for(i = 0;i<2;i++)
    {
	    AVMData::GetInstance()->m_2D_lut->CvtPointImage2Wolrd(car_rect[i],&car_rect_world[i]);

		pWorldPint[3*i] = car_rect_world[i].x;
	    pWorldPint[3*i+1] = car_rect_world[i].y;
        pWorldPint[3*i+2] = 0;
		
        AVMData::GetInstance()->cvtWorldPoint2ModelPoint3D(&pModelPoint[3*i],&pWorldPint[3*i]);
    }

	*pWidth = pModelPoint[3]-pModelPoint[0];
	*pHeight = pModelPoint[2]-pModelPoint[5];
    pPose[0] = (pModelPoint[3]+pModelPoint[0])/2.0;
    pPose[1] = pModelPoint[1];
    pPose[2] = (pModelPoint[2]+pModelPoint[5])/2.0;

	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::ProcessDoorStatus()
{
	static unsigned char preDriverDoorState = 100;
	static unsigned char prePassengerDoorState = 100;
	static unsigned char preRearRightDoorState = 100;
	static unsigned char preRearLeftDoorState = 100;

	unsigned char driverDoorState = 0;
	unsigned char passengerDoorState = 0;
	unsigned char rearRightDoorState = 0;
	unsigned char rearLeftDoorState = 0;
	AVMData::GetInstance()->m_p_can_data->Get_Door_State(&driverDoorState, &passengerDoorState, &rearRightDoorState, &rearLeftDoorState);

	if(preDriverDoorState != driverDoorState)
	{
		if(DOOR_OPEN == driverDoorState)
			DoorAction(DRIVER_DOOR_POS,DOOR_OPEN);
		else
			DoorAction(DRIVER_DOOR_POS,DOOR_CLOSE);

		preDriverDoorState = driverDoorState;
	}

	if(prePassengerDoorState != passengerDoorState)
	{
		if(DOOR_OPEN == passengerDoorState)
			DoorAction(PASSENGER_DOOR_POS,DOOR_OPEN * (-1));
		else
			DoorAction(PASSENGER_DOOR_POS,DOOR_CLOSE);

		prePassengerDoorState = passengerDoorState;
	}

	if(preRearRightDoorState != rearRightDoorState)
	{
		if(DOOR_OPEN == rearRightDoorState)
			DoorAction(REAR_RIGHT_DOOR_POS,DOOR_OPEN * (-1));
		else
			DoorAction(REAR_RIGHT_DOOR_POS,DOOR_CLOSE);

		preRearRightDoorState = rearRightDoorState;

	}

	if(preRearLeftDoorState != rearLeftDoorState)
	{
		if(DOOR_OPEN == rearLeftDoorState)
			DoorAction(REAR_LEFT_DOOR_POS,DOOR_OPEN);
		else
			DoorAction(REAR_LEFT_DOOR_POS,DOOR_CLOSE);

		preRearLeftDoorState = rearLeftDoorState;
	}


	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::DoorAction(int pDoorIndex,int pDoorState, float pRotateAngle)
{
   	m_CarDoor[pDoorIndex]->RotateY(pDoorState*pRotateAngle);
	m_carWindow[pDoorIndex]->RotateY(pDoorState*pRotateAngle);
	return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::SetVisibility(unsigned char pVisibilityFlag)
{
    if(m_objViewNode == NULL)
    {
        return AVM_OBJVIEW_NODE_INIT_FAILED;
    }

    m_objViewNode->SetEnable(pVisibilityFlag);
    m_visibilityFlag = pVisibilityFlag;
    	
    return AVM_OBJVIEW_NORMAL;
}
int CAvmObjectViewNode::ResetObjViewNodeRegion(Region* pRegion)
{
	if(m_objViewNode == NULL)
    {
        return AVM_OBJVIEW_NODE_INIT_FAILED;
    }
	m_objViewNode->SetRenderROI(pRegion);
	return AVM_OBJVIEW_NORMAL;
}

ISceneNode* CAvmObjectViewNode::GetAvmObjViewNode()
{
    return  m_objViewNode;
}
ICamera* CAvmObjectViewNode::GetAvmObjViewCamera()
{
	return m_objViewCamera;
}
int CAvmObjectViewNode::SetClear(unsigned char pColorFlag, unsigned char pDepthFlag)
{
	m_objViewNode->SetClear(pColorFlag, pDepthFlag);
	return AVM_OBJVIEW_NORMAL;
}
void CAvmObjectViewNode::MockRefreshCarBodyTexture()
{
	static int cnt = 0;
	static int frameCnt = 0;
	char CARTEXW[] = XR_RES"envision_white.tga";

	char avd, avd2;

	if(frameCnt%25 == 0)
	{
		if(cnt % 3 == 0)
		{
			m_carMtl->SetDiffuseMap(CARTEXW);
		}
		else
		{
			m_carMtl->SetDiffuseMap(CARTEX);
		}
		
		cnt ++;
	}
	frameCnt ++;

}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/21/17   Jensen Wang   Create the CAvm3dViCAvmObjectViewNodeewNode class.
\*===========================================================================*/
