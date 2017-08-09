#include "SVScene.h"
#include "SVDelegate.h"
#include "SVNode2DStich.h"
#include "SVNodeEMirror.h"
#include "GlSVOverlayAPA.h"
#include "GlSVOverlayStichWheel.h"
#include "SVNodeAdasHmi.h"
#include "RenderNode/SVNodeCrossImage.h"
#include "RenderNode/SVNodeSonar.h"
#include "gpu_log.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
extern IAnimationManager* am;
extern float g_MaterialColor[3];
extern float g_MaterialAlpha;
extern APAOverlayStruct g_APA_Result;
//#define ALI
#define CAR_MODEL
#define CAR_TRANSPARENT 
#define ENVISION_CAR_MODEL
//#define GWM_H7_CAR_MODEL
/*extern functions start*/
//extern functions end
extern int LoadDataFile(char *pFileName,GLfloat **pContent,int num);
extern GLfloat fCarView[];
//Surround View Necessary Object
#define SCALE_CAR_MIDDLE  0.2
#define SCALE_CAR_MIDDLE_SPECIAL_Z  0.85
#define CAMERA_MODEL_SCALE  0.8
#define SCALE_3D_TO_2D_X 0.34447
#ifdef ALI
#define OBJ_CAMERA_DEFAULT_HEIGHT 3600.0
#define SCENE_CAMERA_DEFAULT_HEIGHT 3600.0
#else
#define OBJ_CAMERA_DEFAULT_HEIGHT 3600.0
#define SCENE_CAMERA_DEFAULT_HEIGHT 3600.0
#endif
#define CAMERA_ZOOMIN_DEFAULT_HEIGHT 6600.0
unsigned int *g_uiAverageIllum;

char skyR[]	= XR_RES"skylrex.mqo";
char skyL[]	= XR_RES"skylrex.mqo";
char skyF[]	= XR_RES"skyfbex.mqo";
char skyB[]	= XR_RES"skyfbex.mqo";
char skyFA[]	= XR_RES"skyfbaex.mqo";
char skyBA[]	= XR_RES"skyfbaex.mqo";
char skyFC[]	= XR_RES"skyfbcylinder.mqo";
char skyBC[]	= XR_RES"skyfbcylinder.mqo";



char CONTROLPANELFRONT[] = XR_RES"front_ctl.bmp";
char CONTROLPANELREAR[] = XR_RES"rear_ctl.bmp";
char CONTROLPANELLEFT[] = XR_RES"left_ctl.bmp";
char CONTROLPANELRIGHT[] = XR_RES"right_ctl.bmp";



char OVLSINGLE[] = XR_RES"overlaysingle.dds";


char REMINDSAFE[]=XR_RES"saferemind.dds";
char OVERLAPMASK[] = XR_RES"mask.bmp";
char OVERLAPMASKREAR[] = XR_RES"maskrear.bmp";


#ifdef RX5_CAR_MODEL
char CAR2DICON[] = XR_RES"car_icon_rx5.dds";
char WHEELMODEL[] = XR_RES"rx5wheelsingle.mqo";
char WHEELMODELRIGHT[] = XR_RES"rx5wheelsingleright.mqo";

char CARMODEL[] = XR_RES"RX5_1.mqo";
char CARLIGHTMODEL[] = XR_RES"RX5_1_light.mqo";
char CARINTMODEL[] = XR_RES"rx5_internal.mqo";
char CARWINDOWMODEL[] = XR_RES"RX5_1_window.mqo";


char CARLIGHTTEX[]=XR_RES"rx5_light.tga";
char CARINTTEX[]=XR_RES"rx5_int.bmp";
char *CARDOORMODEL[4] = {XR_RES"driver_door.mqo",XR_RES"driver_assist_door.mqo",XR_RES"left_rear.mqo",XR_RES"right_rear.mqo"};
char *CARDOORWINDOWMODEL[4] = {XR_RES"driver_door_w.mqo",XR_RES"driver_assist_door_w.mqo",XR_RES"left_rear_w.mqo",XR_RES"right_rear_w.mqo"};
char CARLIGHTON[]=XR_RES"rx5_light_on.tga";

char CARTEX[] = XR_RES"RX5_1_D.tga";
char RX5TEXMASK[] = XR_RES"rx5_1_mask.bmp";
#endif


#ifdef ENVISION_CAR_MODEL
char CAR2DICON[] = XR_RES"car_icon_rx5.dds";
char WHEELMODEL[] = XR_RES"envisionwheelsingle.mqo";
char WHEELMODELRIGHT[] = XR_RES"rx5wheelsingleright.mqo";

char CARMODEL[] = XR_RES"envision_frame.mqo";
char CARLIGHTMODEL[] = XR_RES"envision_light.mqo";
char CARINTMODEL[] = XR_RES"envision_internal.mqo";
char CARWINDOWMODEL[] = XR_RES"envision_window.mqo";

char CARLIGHTTEX[]=XR_RES"envision_light.tga";
char CARINTTEX[]=XR_RES"envision_int_tex.bmp";
char *CARDOORMODEL[4] = {XR_RES"envision_driver_door.mqo",XR_RES"envision_driver_assist_door.mqo",XR_RES"envision_left_rear.mqo",XR_RES"envision_right_rear.mqo"};
char *CARDOORWINDOWMODEL[4] = {XR_RES"envision_driver_door_w.mqo",XR_RES"envision_driver_assist_door_w.mqo",XR_RES"envision_left_rear_w.mqo",XR_RES"envision_right_rear_w.mqo"};
char CARTEX[] = XR_RES"envision_white.tga";
char RX5TEXMASK[] = XR_RES"envision_mask.bmp";
char CARLIGHTON[]=XR_RES"envision_light_on.tga";

#endif
#ifdef GWM_H7_CAR_MODEL
char CAR2DICON[] = XR_RES"car_icon_rx5.dds";
char WHEELMODEL[] = XR_RES"GWM_H7_wheel.mqo";
char WHEELMODELRIGHT[] = XR_RES"rx5wheelsingleright.mqo";

char CARMODEL[] = XR_RES"GWM_H7_frame.mqo";
char CARLIGHTMODEL[] = XR_RES"GWM_H7_light.mqo";
char CARINTMODEL[] = XR_RES"GWM_H7_internal.mqo";
char CARWINDOWMODEL[] = XR_RES"GWM_H7_window.mqo";

char CARLIGHTON[]=XR_RES"GWM_H7_light_on.tga";

char CARLIGHTTEX[]=XR_RES"GWM_H7_light.tga";
char CARINTTEX[]=XR_RES"GWM_H7_int_tex.bmp";
char *CARDOORMODEL[4] = {XR_RES"GWM_H7_driver_door.mqo",XR_RES"GWM_H7_driver_assist_door.mqo",XR_RES"GWM_H7_left_rear.mqo",XR_RES"GWM_H7_right_rear.mqo"};
char *CARDOORWINDOWMODEL[4] = {XR_RES"GWM_H7_driver_door_w.mqo",XR_RES"GWM_H7_driver_assist_door_w.mqo",XR_RES"GWM_H7_left_rear_w.mqo",XR_RES"GWM_H7_right_rear_w.mqo"};


char CARTEX[] = XR_RES"GWM_H7_white.tga";
char RX5TEXMASK[] = XR_RES"GWM_H7_mask.bmp";

#endif
char CARTEXMASK[] = XR_RES"mask1.bmp";

#define CUT_LINE 8
#define FADE_BORDER 20


//#define ALIBABA_HMI


//Car Model Object

char c_SV2DVertShaderSrcFileLUT[]  = XR_RES"OVVertShaderSV2D.vtx";
char c_SV2DFragStaticShaderSrcFile[]   = XR_RES"OVFragShaderSV2DStatic.frg";
char c_SV2DFragCarImageShaderSrcFile[]   = XR_RES"OVFragShaderSV2DCar.frg";


char BMWCARMODEL[] = XR_RES"bmw.mqo";
char BMWCARTEX[] = XR_RES"texture.dds";
char BMWCARTEXMASK[] = XR_RES"carmask.bmp";

char VANMODEL[] = XR_RES"van.mqo";
char VANWHEELMODEL[] = XR_RES"vanwheel.mqo";
char VANRIGHTWHEELMODEL[] = XR_RES"vanwheelright.mqo";
char VANTEX[] = XR_RES"truckUV90.tga";
char VANTEXMASK[] = XR_RES"van_mask.bmp";


char TRUCKMODEL[] = XR_RES"truck.mqo";
char OTHERTEX[] = XR_RES"texture_other.dds";
char OTHERTEXMASK[] = XR_RES"mask_other.bmp";

char MirrorModel[]=XR_RES"biekemirror.mqo";

//Other Product Object

#define RADAR_MODEL_SCALE  12
#define RSDS_MODEL_SCALE  0.6

char IFVODEL[] = XR_RES"ifv.mqo";
char RADARWAVEMODEL[] = XR_RES"radarwave.mqo";
char RADARWAVEBULLETMODEL[] = XR_RES"wavebullet.mqo";
char ESRMODEL[] = XR_RES"esr.mqo";
char RSDSMODEL[] = XR_RES"rsds.mqo";
char CAMERAMODEL[]=XR_RES"camera_step.mqo";
char BEVMODEL[]=XR_RES"bevcontroller.mqo";
char YELLOWTEX[] = XR_RES"yellow.bmp";
char BLUETEX[] = XR_RES"blue.bmp";
char REDTEX[] = XR_RES"red.bmp";
char OVERLAYTEX[] = XR_RES"overlayali.dds";
//char OVERLAYTEX[] = XR_RES"overlay_white_re.dds";
//char OVERLAYTEX[] = XR_RES"car_icon_rx5.dds";

//char OVERLAYTEX[] = XR_RES"car_icon_rx5.dds";



char RADARALARM[] = XR_RES"red.dds";

char CARENV[] = XR_RES"env.bmp";
char WAVETEX[] = XR_RES"wave.bmp";
char GREENTEX[] = XR_RES"green.bmp";
char IFVWAVETEX[]=XR_RES"ifvwave.bmp";

char *RADARALARMTEX[4] = {XR_RES"red.dds",XR_RES"orange.dds",XR_RES"yellow.dds",XR_RES"green.dds"};

#define _DATAPGSPARA_ XR_RES"pgs.txt"

int videoid[4];
static float left_plane = 100.0;
static float black_plane = 80.0;
Region FadeLeftReg, CenterReg, FadeRightReg,MapPlateReg;
//Region Stich2DReg, RightReg, RightTopFadeReg,RightBottomFadeReg,RightBottomSingleReg;
Region Stich2DReg,SingleViewReg, UIControlReg,RightReg, RightTopFadeReg,RightBottomFadeReg;


//Local Definition
IKeyAnimation* wheelRot=0;
IKeyAnimation* bulletrun=0;
IKeyAnimation* bevdisplay[2]={0,0};
IKeyAnimation* bevTour[2]={0,0};
IKeyAnimation* bevSecTour[2]={0,0};


class OnPlayFinished : public IVideoDelegate
{
public:
	virtual void OnFinish()
        {
            if (wheelRot) {
                //wheelRot->Start();
            }
        }

};
#define OVERLAY_POINT_NUM  40
void SVScene::InitOverlay(BEV_CONFIG_T pConfig , ISceneNode *pNode,IMesh **pMesh,INode **OverlayNode,GlSVOverlay *pOverlayData,unsigned char calib_mode,float *pos)
{

    IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
	Overlay_Para Overlay_data_cfg;
	Dynamic_Overlay_Para Overlay_data_cfg_private;
	Float32 *p_Overlay_Data;
	Int32 iSize;
	XRVertexLayout data_format;
	SV_VEHICLE_PARAM_T *p_veh_param=NULL;
	tempmaterialid = pNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
	if(calib_mode == calib_2D_SINGLE)
	{
        tempcarmtl->SetDiffuseMap(OVLSINGLE);
	}
	else
	{

        tempcarmtl->SetDiffuseMap(OVERLAYTEX);
	}

	//tempcarmtl->SetDiffuseMap(OVLSINGLE);
	tempcarmtl->SetEnvironmentMap(BLUETEX);


	int lisenceMeshId = pNode->CreateMesh(ModelType_Plane_Dynamic,2,  OVERLAY_POINT_NUM,0, "ground", pMesh);
	int groundId = pNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, OverlayNode);

	(*OverlayNode)->SetMesh(lisenceMeshId);
	//m_overlay->RotateDX(90);
	(*OverlayNode)->SetEnable(pConfig.smc_hmi.GROUND_MODEL_ENABLE);

    (*pMesh)->LockData(&p_Overlay_Data,&data_format,&iSize);
    AVMData::GetInstance()->GetVehicleParam(&p_veh_param);
    Overlay_data_cfg.dynamic_overlay_point_num = OVERLAY_POINT_NUM;
	Overlay_data_cfg.vehicle_length = p_veh_param->vehicle_length;
	Overlay_data_cfg.vehicle_width = p_veh_param->vehicle_width;
	Overlay_data_cfg.vehicle_axis_length = p_veh_param->vehicle_axis_length;
	Overlay_data_cfg.vehicle_front_wheel2bumper_length = p_veh_param->vehicle_front_wheel_to_bumper;
	Overlay_data_cfg.vehicle_rear_wheel2bumper_length = p_veh_param->vehicle_rear_wheel_to_bumper;
	Overlay_data_cfg.model_scale = SCALE_3D_TO_2D_X;
	for(int i=0;i<4;i++)
	{
        // Overlay_data_cfg.vehicle_min_radius[i] = 4.68;
        //	Overlay_data_cfg.vehicle_max_steering[i] = 588;
	}
	Overlay_data_cfg_private.Vehicle_Max_Deg_Steering_Wheel_Left_Turn = p_veh_param->vehicle_max_steering_wheel[left_turn_max];
	Overlay_data_cfg_private.Vehicle_Max_Deg_Steering_Wheel_Right_Turn =  p_veh_param->vehicle_max_steering_wheel[right_turn_max];
	Overlay_data_cfg_private.Vehicle_Min_Radius_Gear_D_Left_Turn_Rear_Axis_Cent = p_veh_param->vehicle_min_radius[left_turn_foward_radius];
	Overlay_data_cfg_private.Vehicle_Min_Radius_Gear_D_Right_Turn_Rear_Axis_Cent = p_veh_param->vehicle_min_radius[right_turn_foward_radius];
	Overlay_data_cfg_private.Vehicle_Min_Radius_Gear_R_Left_Turn_Rear_Axis_Cent = p_veh_param->vehicle_min_radius[left_turn_backward_radius];
	Overlay_data_cfg_private.Vehicle_Min_Radius_Gear_R_Right_Turn_Rear_Axis_Cent = p_veh_param->vehicle_min_radius[right_turn_backward_radius];;
	Overlay_data_cfg_private.overlay_length = 2000;
    Overlay_data_cfg.m_calib_center_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CY);
	Overlay_data_cfg.m_calib_center_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CX);
	Overlay_data_cfg.m_calib_mmpp_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMY);
	Overlay_data_cfg.m_calib_mmpp_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMX);

	AVMData::GetInstance()->m_exParam->GetCameraPos(Overlay_data_cfg.m_front_cam_pos_wld,front_camera_index);
 	Overlay_data_cfg.m_model_bottom = -m_bev_config.smc_hmi.SPACE_MODEL_Y_MIN*m_bev_config.smc_hmi.SPACE_MODEL_SCALE_SIZE;
	
	//Overlay_data_cfg.m_model_bottom = m_bev_config.smc_hmi.SPACE_MODEL_Y_MIN;
	//memcpy(Overlay_data_cfg.m_rear_cam_pos_wld,&(PoseTrans[3*3]),3*sizeof(float));
	
	AVMData::GetInstance()->m_exParam->GetCameraPos(Overlay_data_cfg.m_rear_cam_pos_wld,rear_camera_index);
    pOverlayData->Init(Overlay_data_cfg);
	pOverlayData->InitPrivate(Overlay_data_cfg_private);
    pOverlayData->SetUpBuffer(p_Overlay_Data,OVERLAY_POINT_NUM,8,calib_mode);

}

OnPlayFinished onPlayFinished;

void SVScene::InitMirrorNode(BEV_CONFIG_T pConfig , ISceneNode *pNode,float *pPose,float *scale)
{

	int meshid;
	int modelId,materialID;
	float *pData;
	unsigned short	 *pIndex;
	unsigned int BufferSize;
	IMesh *pMesh;
	IMaterial *pMtl;
	int i =8;
    //step 1. prepare for Material ,different camera input image
	IRenderEffect* pIEffect;
	int SV2DMTL;

	char *MeshName[]={"M","b","l","r"};
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_3D_VERTEX_SHADER);
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_3D_FRAGMENT_SHADER);

	cvdelegate = new RenderDelegateCV();

	cvdelegate->Init();
	cvdelegate->SetChannel(0);


	SV2DMTL = pNode->CreateMaterial(Material_Custom, &pMtl);
	pMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pMtl,rear_camera_index);
	pIEffect->InitShaderFromFile("Effect_SV", VertexName, FragShaderName,  sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
	pIEffect->SetRenderDelegate(cvdelegate);



	int groundId = pNode->LoadModelFromFile(MirrorModel, SV2DMTL, -1, InsertFlag_Default, pPose[0], pPose[1], pPose[2], 50, &m_mirror[0]);
	m_mirror[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
    m_mirror[0]->SetScale(scale[0],scale[1],scale[2]);
    m_mirror[0]->SetName(MeshName[0]);


    cvdelegate->ProcessMirrorModel(m_mirror[0],MeshName[0]);


}



void SVScene::InitSceneNode(BEV_CONFIG_T  pConfig)
{
    Region *ScennodeAera;
	float f_camera_aspect;
	m_scenenodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_sceneNode);
#ifndef ALI
	m_sceneNode->SetClearColor(1.0,1.0,0.0,0.5);

	m_sceneNode->SetClear(TRUE, TRUE);
#endif
    //m_sceneNode->SetClearColor(1.0,1.0,0.0,0.5);

	m_sceneNode->SetClear(TRUE, TRUE);
    //m_sceneNode->SetRenderROI(&RightTopFadeReg);
    m_sceneNode->SetRenderROI(&RightReg);

	//m_sceneNode->SetClearColor(1.0,1.0,0.0,0.5);

	//InitVideo();
#if 0
	ITextureDelegate* tdelegate[4];

	for (int i=0;i<4;i++) {
		tdelegate[i] = new VideoTextureDelegate(i);

		// buffer file %s,line %d",__FILE__,__LINE__);
		videoid[i] = rm->CreateStreamingTexture(640, 480, XR_R8G8B8, tdelegate[i]);
	}
#endif
	//Int32 videomtlId = sceneNode->CreateMaterial(Material_Simple_Video, &videomtl[0]);
	svdelegate = new RenderDelegateSV();

	// buffer file %s,line %d",__FILE__,__LINE__);
	svdelegate->Init(pConfig);


	int SVMTL[4];

	IMaterial* pISVmtl;
	IRenderEffect* pIEffect;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_3D_VERTEX_SHADER);
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_3D_FRAGMENT_SHADER);
	for(int i =0;i<4;i++)
	{

    	SVMTL[i] = m_sceneNode->CreateMaterial(Material_Custom, &pISVmtl);
        pISVmtl->CreateMaterialEffect(&pIEffect);
    	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pISVmtl,i);
		if(i!=1)
            pISVmtl->SetAmbientMap(OVERLAPMASK);
		else
            pISVmtl->SetAmbientMap(OVERLAPMASKREAR);

    	AVMData::GetInstance()->m_cam_source->SetCameraSourceMask(pISVmtl->GetAmbientMap()->texid,i);

    	pIEffect->InitShaderFromFile("Effect_SV", VertexName, FragShaderName, sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
    	pIEffect->SetRenderDelegate(svdelegate);
	}




#define SV_Y_POS 0
	int modelId;
	INode* pImdl;
#if 1
	modelId = m_sceneNode->LoadModelFromFile(skyR ,SVMTL[3], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);

	svdelegate->ProcessModel(pImdl, "3");
	m_SkyNode[0]=pImdl;

	modelId = m_sceneNode->LoadModelFromFile(skyL ,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "2");

	m_SkyNode[1]=pImdl;
#endif
#if 1
	modelId = m_sceneNode->LoadModelFromFile(skyF ,SVMTL[0], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);

	svdelegate->ProcessModel(pImdl, "0");
	m_SkyNode[2]=pImdl;

	modelId = m_sceneNode->LoadModelFromFile(skyB ,SVMTL[1], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "1");	
    m_SkyNode[3]=pImdl;	

#endif
	modelId = m_sceneNode->LoadModelFromFile(skyFA ,SVMTL[0], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "4");

	modelId = m_sceneNode->LoadModelFromFile(skyBA ,SVMTL[1], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "5");

	modelId = m_sceneNode->LoadModelFromFile(skyFC,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "6");
	m_pPanaramaNode[0] = pImdl;
	m_pPanaramaNode[0]->SetEnable(0);

	modelId = m_sceneNode->LoadModelFromFile(skyBC ,SVMTL[3], -1, InsertFlag_Default, 0, SV_Y_POS, -0, pConfig.smc_hmi.SPACE_MODEL_SCALE_SIZE, &pImdl);
	svdelegate->ProcessModel(pImdl, "7");
	m_pPanaramaNode[1] = pImdl;
	m_pPanaramaNode[1]->SetEnable(0);


	float pos[3];
	pos[0] = 0;
	pos[1] =0;
	pos[2] = 0;


    // InitOverlay(m_bev_config,m_sceneNode,&m_overlaymesh,&m_overlay,&m_overlay_data,calib_3D,pos);
    IMesh *pRadar;
	INode *pRadaNode=NULL;
	m_RadarAlarm_Mesh[0]=NULL;
	InitRadarAlram(m_bev_config,m_sceneNode,&m_RadarAlarm_Mesh[0],&m_RadarAlarm_Node[0],m_radar_alram,&m_RadarAlarm_Mtl[0],calib_3D);

skipDome:
	/////////////////////////////cameraScene//////////////////
	ScennodeAera = m_sceneNode->GetRenderROI();
	f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);
	//f_camera_aspect=1.5;

	f_camera_aspect = 1.23265302;
#ifdef ALI
	//int cameraId = m_sceneNode->CreateCamera(m_freeModeFOV, CAMERA_ASPECT, 4.0f, 12000.0f, &m_sceneCamera);

	f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);
    int cameraId = m_sceneNode->CreateCamera(m_freeModeFOV, f_camera_aspect, 4.0f, 12000.0f, &m_sceneCamera);
//int cameraId = m_sceneNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 4.0f, 12000.0f, &m_sceneCamera);

#else
	int cameraId = m_sceneNode->CreateCamera(m_freeModeFOV, f_camera_aspect, 4.0f, 12000.0f, &m_sceneCamera);
//int cameraId = m_sceneNode->CreateCamera(m_freeModeFOV, f_camera_aspect, 4.0f, 12000.0f, &m_sceneCamera);

#endif
	//camera->SetOrientation(0, 0, 0);
	m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
	m_sceneCamera->LookAt(0.0,0.0,0.0);
	//camera->RotateAround(2,2);
	m_sceneNode->SetCamera(cameraId);

	//EnterTopView(0);

#ifdef EMIRROR
	m_sceneNode->SetEnable(1);
#endif

}

void SVScene::InitObjectNode(BEV_CONFIG_T  pConfig)
{

	int modelId;
    Region *ScennodeAera;
	float f_camera_aspect;
	Int32 iSUVmtlId;
	Int32 iVanmtlId;
	Int32 iTruckMtlId;
    Int32 iRadarMtlId;
	Int32 iCarLightMtlId,iCarnodeId;

	///////////////////////Object Node/////////////////////////
	m_objectnodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_objectNode);

	m_objectNode->SetClear(FALSE, TRUE);
    m_objectNode->SetRenderROI(&RightReg);
	IMaterial* carmtl;
	IMaterial *carlightmtl;
	float door_offset_x;
	float door_offset_y;


    IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
    float ground_width, ground_height;
	INode *ground;
	IMesh *groundmesh;
    float pos[3];
	pos[0] = m_bev_config.smc_hmi.CAR_MODEL_POSITION_X;
	pos[1] = m_bev_config.smc_hmi.CAR_MODEL_POSITION_Y;
	pos[2] = m_bev_config.smc_hmi.CAR_MODEL_POSITION_Z;
	float scale[3];
	scale[0]= m_bev_config.smc_hmi.CAR_MODEL_SCALE_X;
	scale[1]= m_bev_config.smc_hmi.CAR_MODEL_SCALE_Y;

	scale[2]= m_bev_config.smc_hmi.CAR_MODEL_SCALE_Z;



	ISceneNode*	object_render_node;
	object_render_node = m_objectNode;
	tempmaterialid = object_render_node->CreateMaterial(Material_Rigid_Texture, &tempcarmtl);
	tempcarmtl->SetDiffuseMap(GREENTEX);
	tempcarmtl->SetEnvironmentMap(BLUETEX);
	m_3d_ground_Mtl = tempcarmtl;

	Calc3DGroundPos(pos,&ground_width,&ground_height);
#if 0
	int lisenceMeshId = object_render_node->CreateMesh(ModelType_Plane, pConfig.smc_hmi.GROUND_MODEL_WIDTH,pConfig.smc_hmi.GROUND_MODEL_HEIGHT, 0, "ground", &groundmesh);
	int groundId = object_render_node->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, pConfig.smc_hmi.GROUND_MODEL_POS_X, pConfig.smc_hmi.GROUND_MODEL_POS_Y,pConfig.smc_hmi.GROUND_MODEL_POS_Z, 1.0, &m_ground);
#endif

#ifdef CAR_TRANSPARENT
	int lisenceMeshId = object_render_node->CreateMesh(ModelType_Plane_Dynamic, 2,2, 0, "ground", &m_groundmesh);
//	int lisenceMeshId = object_render_node->CreateMesh(ModelType_Plane_Dynamic, ground_width/2.0,ground_height/2.0, 0, "ground", &m_groundmesh);

	int groundId = object_render_node->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, 0,0,0,1.0, &m_ground);

	m_ground->SetMesh(lisenceMeshId);
	//m_ground->RotateDX(90);	
	m_ground->SetEnable(pConfig.smc_hmi.GROUND_MODEL_ENABLE);
#else
	int lisenceMeshId = object_render_node->CreateMesh(ModelType_Plane, ground_width/2.0,ground_height/2.0, 0, "ground", &groundmesh);
	int groundId = object_render_node->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, pos[0],pos[1],pos[2],1.0, &m_ground);

	m_ground->SetMesh(lisenceMeshId);
	m_ground->RotateDX(90);	
	m_ground->SetEnable(pConfig.smc_hmi.GROUND_MODEL_ENABLE);
#endif
    iCarLightMtlId = object_render_node->CreateMaterial(Material_RigidColor_Texture, &carlightmtl);
	carlightmtl->SetDiffuseMap(CARINTTEX);
	carlightmtl->SetEnvironmentMap(CARENV);
	carlightmtl->SetAmbientMap(CARTEXMASK);
	iCarnodeId = object_render_node->LoadModelFromFile(CARINTMODEL, iCarLightMtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z, 50, &m_CarInternal); //envision



	m_CarInternal->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_CarInternal->SetEnable(1);
	
	m_CarInternal->RotateDY(0);
	m_carmtlId = object_render_node->CreateMaterial(Material_Glossy, &carmtl);
	carmtl->SetDiffuseMap(CARTEX);
	carmtl->SetEnvironmentMap(CARENV);
	carmtl->SetAmbientMap(RX5TEXMASK);
	m_carId = object_render_node->LoadModelFromFile(CARMODEL, m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z, 50, &m_Car); //envision



	m_Car->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_Car->SetEnable(1);

	m_Car->RotateDY(0);






    door_offset_x = 13*50*pConfig.smc_hmi.CAR_MODEL_SCALE_X;
#ifdef RX5_CAR_MODEL	
    door_offset_y = 9.5*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef ENVISION_CAR_MODEL

    door_offset_y = 15*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef GWM_H7_CAR_MODEL
	
    door_offset_y = 14*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif

	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORMODEL[0], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X-door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z-door_offset_y, 50, &m_CarDoor[0]); //envision



	m_CarDoor[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[0]->SetEnable(1);



	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORMODEL[1], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X+door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z-door_offset_y, 50, &m_CarDoor[1]); //envision



	m_CarDoor[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[1]->SetEnable(1);
	//m_CarDoor[0]->RotateDY(60);


#ifdef RX5_CAR_MODEL

    door_offset_y = 6.5*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef ENVISION_CAR_MODEL

    door_offset_y = 1.9*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef GWM_H7_CAR_MODEL
	
    door_offset_y = 4*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif

	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORMODEL[2], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X-door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z+door_offset_y, 50, &m_CarDoor[2]); //envision



	m_CarDoor[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[2]->SetEnable(1);


	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORMODEL[3], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X+door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z+door_offset_y, 50, &m_CarDoor[3]); //envision



	m_CarDoor[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_CarDoor[3]->SetEnable(1);

	iCarLightMtlId = object_render_node->CreateMaterial(Material_RigidColor_Texture, &m_carlightmtl);
	m_carlightmtl->SetDiffuseMap(CARLIGHTTEX);

	//carlightmtl->SetDiffuseMap(CARTEX);

	m_carlightmtl->SetEnvironmentMap(CARLIGHTON);
	m_carlightmtl->SetAmbientMap(CARTEXMASK);
	iCarnodeId = object_render_node->LoadModelFromFile(CARLIGHTMODEL, iCarLightMtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z, 50, &m_CarLight); //envision
	//iCarnodeId = object_render_node->LoadModelFromFile(CARINTMODEL, iCarLightMtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z, 50, &m_CarLight); //envision

	m_carlightmtl->SetAmbientColor(1.0,0.5,0.0,0.0);


	m_CarLight->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_CarLight->SetEnable(1);

	m_CarLight->RotateDY(0);





    door_offset_x = 13*50*pConfig.smc_hmi.CAR_MODEL_SCALE_X;
#ifdef RX5_CAR_MODEL	
    door_offset_y = 9.5*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef ENVISION_CAR_MODEL

    door_offset_y = 15*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef GWM_H7_CAR_MODEL
	
    door_offset_y = 14*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif

	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORWINDOWMODEL[0], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X-door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z-door_offset_y, 50, &m_Car_Window[0]); //envision



	m_Car_Window[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_Car_Window[0]->SetEnable(1);


	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORWINDOWMODEL[1], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X+door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z-door_offset_y, 50, &m_Car_Window[1]); //envision



	m_Car_Window[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_Car_Window[1]->SetEnable(1);
	//m_CarDoor[0]->RotateDY(60);


#ifdef RX5_CAR_MODEL	

    door_offset_y = 6.5*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif
#ifdef ENVISION_CAR_MODEL

    door_offset_y = 1.9*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif

#ifdef GWM_H7_CAR_MODEL
	
    door_offset_y = 4*50*pConfig.smc_hmi.CAR_MODEL_SCALE_Z;
#endif

	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORWINDOWMODEL[2], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X-door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z+door_offset_y, 50, &m_Car_Window[2]); //envision



	m_Car_Window[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_Car_Window[2]->SetEnable(1);


	iCarnodeId = object_render_node->LoadModelFromFile(CARDOORWINDOWMODEL[3], m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X+door_offset_x, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z+door_offset_y, 50, &m_Car_Window[3]); //envision



	m_Car_Window[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_SRY);
	m_Car_Window[3]->SetEnable(1);


	iCarnodeId = object_render_node->LoadModelFromFile(CARWINDOWMODEL, m_carmtlId, -1, InsertFlag_Default, pConfig.smc_hmi.CAR_MODEL_POSITION_X, pConfig.smc_hmi.CAR_MODEL_POSITION_Y, pConfig.smc_hmi.CAR_MODEL_POSITION_Z, 50, &m_Car_Window[4]); //envision



	m_Car_Window[4]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_Car_Window[4]->SetEnable(1);

	m_Car_Window[4]->RotateDY(0);



	g_MaterialAlpha = 0.95;

    // InitMirrorNode(m_bev_config,m_objectNode,pos,scale);

#ifdef CAR_MODEL

	iSUVmtlId = object_render_node->CreateMaterial(Material_Glossy_Color, &carmtl);
	carmtl->SetDiffuseMap(BMWCARTEX);
	carmtl->SetEnvironmentMap(CARENV);
	carmtl->SetAmbientMap(BMWCARTEXMASK);
	m_iSUVId = object_render_node->LoadModelFromFile(BMWCARMODEL, iSUVmtlId, -1, InsertFlag_Default, -10, -40, -590, 26.5, &m_SUV);
	m_SUV->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_SUV->SetEnable(0);




	iVanmtlId = object_render_node->CreateMaterial(Material_Glossy_Color, &carmtl);
	carmtl->SetDiffuseMap(VANTEX);
	carmtl->SetEnvironmentMap(CARENV);

	carmtl->SetAmbientMap(VANTEXMASK);
	m_iVanId = object_render_node->LoadModelFromFile(VANMODEL, iVanmtlId, -1, InsertFlag_Default, -10, -100, -580, 24, &m_VAN);
	m_VAN->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_VAN->SetEnable(0);



	iTruckMtlId = object_render_node->CreateMaterial(Material_Glossy_Color, &carmtl);
	carmtl->SetDiffuseMap(OTHERTEX);
	carmtl->SetEnvironmentMap(CARENV);
	carmtl->SetAmbientMap(OTHERTEXMASK);


	m_iTruckId = object_render_node->LoadModelFromFile(TRUCKMODEL, iTruckMtlId, -1, InsertFlag_Default, -50, 80, -520, 22, &m_TRUCK);
	m_TRUCK->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_TRUCK->SetEnable(0);

#endif


//m_Car->SetEnable(0);
#define WHEEL_X_OFFSET 380
#define WHEEL_Y_OFFSET 30
#define WHEEL_ZF_OFFSET 680
#define WHEEL_ZB_OFFSET 730
    IMesh *p_van_wheel;
	IMesh *p_van_wheel_right;

	int wheelMeshId = object_render_node->CreateMesh(ModelType_Null, 0,0,0,"wheel", &m_wheelMesh);
	m_wheelMesh->LoadFromFile(WHEELMODEL, pConfig.smc_hmi.WHEEL_MODEL_SCALE, FALSE);
#if 0
    int rightwheelMeshId = object_render_node->CreateMesh(ModelType_Null, 0,0,0,"wheel", &m_wheelMesh);
	m_wheelMesh->LoadFromFile(WHEELMODELRIGHT, pConfig.smc_hmi.WHEEL_MODEL_SCALE, FALSE);
#endif
#ifdef CAR_MODEL
	int vanwheelMeshId = object_render_node->CreateMesh(ModelType_Null, 0,0,0,"vanwheel", &p_van_wheel);
	p_van_wheel->LoadFromFile(VANWHEELMODEL, 21, FALSE);

	int vanwheelMeshIdright = object_render_node->CreateMesh(ModelType_Null, 0,0,0,"vanwheel", &p_van_wheel_right);
	p_van_wheel_right->LoadFromFile(VANRIGHTWHEELMODEL, 21, FALSE);
#endif
	modelId = object_render_node->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_WIDTH, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_UP, -pConfig.smc_hmi.WHEEL_MODEL_OFFSET_FRONT, 1.1, &m_wheel[0]);
	modelId = object_render_node->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, -pConfig.smc_hmi.WHEEL_MODEL_OFFSET_WIDTH, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_UP, -pConfig.smc_hmi.WHEEL_MODEL_OFFSET_FRONT, 1.1, &m_wheel[1]);
	modelId = object_render_node->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_WIDTH, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_UP, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_REAR, 1.1, &m_wheel[2]);
	modelId = object_render_node->CreateModel(0, m_carmtlId, m_carId, InsertFlag_Child, -pConfig.smc_hmi.WHEEL_MODEL_OFFSET_WIDTH, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_UP, pConfig.smc_hmi.WHEEL_MODEL_OFFSET_REAR, 1.1, &m_wheel[3]);

	SetupLisence();
#if 0
	rightwheelMeshId = wheelMeshId;

	m_wheel[0]->SetMesh(rightwheelMeshId);
	m_wheel[1]->SetMesh(wheelMeshId);

	m_wheel[2]->SetMesh(rightwheelMeshId);
	m_wheel[3]->SetMesh(wheelMeshId);
#else
	m_wheel[0]->SetMesh(wheelMeshId);
	m_wheel[1]->SetMesh(wheelMeshId);

	m_wheel[2]->SetMesh(wheelMeshId);
	m_wheel[3]->SetMesh(wheelMeshId);

#endif
#ifdef CAR_MODEL
#define SUV_WHEEL_X_OFFSET 520
#define SUV_WHEEL_Y_OFFSET -280
#define SUV_WHEEL_ZF_OFFSET 850
#define SUV_WHEEL_ZB_OFFSET 1050
    modelId = object_render_node->CreateModel(0, m_carmtlId, m_iSUVId, InsertFlag_Child, SUV_WHEEL_X_OFFSET, SUV_WHEEL_Y_OFFSET, -SUV_WHEEL_ZF_OFFSET, 2, &m_wheel[4]);
    modelId = object_render_node->CreateModel(0, m_carmtlId, m_iSUVId, InsertFlag_Child, -SUV_WHEEL_X_OFFSET, SUV_WHEEL_Y_OFFSET, -SUV_WHEEL_ZF_OFFSET, 2, &m_wheel[5]);
    modelId = object_render_node->CreateModel(0, m_carmtlId, m_iSUVId, InsertFlag_Child, SUV_WHEEL_X_OFFSET, SUV_WHEEL_Y_OFFSET, SUV_WHEEL_ZB_OFFSET, 2, &m_wheel[6]);
    modelId = object_render_node->CreateModel(0, m_carmtlId, m_iSUVId, InsertFlag_Child, -SUV_WHEEL_X_OFFSET, SUV_WHEEL_Y_OFFSET, SUV_WHEEL_ZB_OFFSET,2, &m_wheel[7]);
    m_wheel[4]->SetMesh(wheelMeshId);
    m_wheel[5]->SetMesh(wheelMeshId);
    m_wheel[6]->SetMesh(wheelMeshId);
    m_wheel[7]->SetMesh(wheelMeshId);
#define VAN_WHEEL_X_OFFSET 480
#define VAN_WHEEL_Y_OFFSET -230
#define VAN_WHEEL_ZF_OFFSET 720
#define VAN_WHEEL_ZB_OFFSET 820
#define VAN_WHEEL_ZBB_OFFSET 1320

    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, -VAN_WHEEL_ZF_OFFSET, 1.0, &m_wheel[8]);
    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, -VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, -VAN_WHEEL_ZF_OFFSET, 1.0, &m_wheel[9]);
    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, VAN_WHEEL_ZB_OFFSET, 1.0, &m_wheel[10]);
    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, -VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, VAN_WHEEL_ZB_OFFSET, 1.0, &m_wheel[11]);
    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, VAN_WHEEL_ZBB_OFFSET, 1.0, &m_wheel[12]);
    modelId = object_render_node->CreateModel(0, iVanmtlId, m_iVanId, InsertFlag_Child, -VAN_WHEEL_X_OFFSET, VAN_WHEEL_Y_OFFSET, VAN_WHEEL_ZBB_OFFSET, 1.0, &m_wheel[13]);

    m_wheel[8]->SetMesh(vanwheelMeshIdright);
    m_wheel[9]->SetMesh(vanwheelMeshId);
    m_wheel[10]->SetMesh(vanwheelMeshIdright);
    m_wheel[11]->SetMesh(vanwheelMeshId);
    m_wheel[12]->SetMesh(vanwheelMeshIdright);
    m_wheel[13]->SetMesh(vanwheelMeshId);
#endif
#define	TURN_DEGREE 3.14/5
	//init wheel rotation key
    float key[]={
        0,	   0,	0,
        2.0,	0.07, 0,
        6.0,	0.1, 0.1,
        10.0,	 0.2,0,
        20.0,	0.15,-0.1,
        24.0,	0.0,0.0};

    am->CreateKeyAnimation(key, sizeof(key)/12,2, &wheelRot);

    IAProperty* val=0;
#ifdef CAR_MODEL
    for (int i=0;i<14;i++)
#else
        for (int i=0;i<4;i++)
#endif
        {
			m_wheel[i]->GetCAProperty(AP_RX, &val);
			wheelRot->BindProperty(0, val);
			if (i%4<2) {
                m_wheel[i]->GetCAProperty(AP_RY, &val);
                wheelRot->BindProperty(1, val);
			}
		}
    wheelRot->SetDeltaUpdate(0);
#ifdef CAR_MODEL
	//wheelRot->Start();
#define SCALE_CAR_MIDDLE  0.54
	//m_Car->SetScale(SCALE_CAR_MIDDLE*0.2,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*0.65);d
    m_SUV->SetScale(SCALE_CAR_MIDDLE*0.9,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*0.9);
    m_VAN->SetScale(SCALE_CAR_MIDDLE*0.9,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*0.95);
    m_TRUCK->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE);

#define OFFSET_CAR_MODDLE -220.0
	//m_Car->SetDY(OFFSET_CAR_MODDLE);
	m_SUV->SetDY(OFFSET_CAR_MODDLE);
	m_VAN->SetDY(OFFSET_CAR_MODDLE);
	m_TRUCK->SetDY(OFFSET_CAR_MODDLE);
#define OFFSET_CAR_MODDLE_Z 500.0
	//m_Car->SetDZ(OFFSET_CAR_MODDLE_Z);
	m_SUV->SetDZ(OFFSET_CAR_MODDLE_Z);
	m_VAN->SetDZ(OFFSET_CAR_MODDLE_Z);
	m_TRUCK->SetDZ(OFFSET_CAR_MODDLE_Z);
#define OFFSET_CAR_MODDLE_X 40.0
	//m_Car->SetDZ(OFFSET_CAR_MODDLE_Z);
	m_SUV->SetDX(OFFSET_CAR_MODDLE_X);
	m_VAN->SetDX(OFFSET_CAR_MODDLE_X);
	m_TRUCK->SetDX(OFFSET_CAR_MODDLE_X);

#endif

    ScennodeAera = m_sceneNode->GetRenderROI();
    f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);

    f_camera_aspect = 1.23265302;
#ifdef ALI
	//int cameraId = object_render_node->CreateCamera(m_freeModeFOV, f_camera_aspect, 4.0f, 12000.0f, &m_objectCamera);
    int cameraId = object_render_node->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 4.0f, 12000.0f, &m_objectCamera);

#else
	int cameraId = object_render_node->CreateCamera(m_freeModeFOV, f_camera_aspect, 4.0f, 12000.0f, &m_objectCamera);
#endif
	//camera->SetOrientation(0, 0, 0);
	m_objectCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
	m_objectCamera->LookAt(0.0,0,-0.0);
	//camera->RotateAround(2,2);
	object_render_node->SetCamera(cameraId);



    m_Car->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
	m_CarLight->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
	m_CarInternal->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
	m_CarDoor[0]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);

	m_CarDoor[1]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);

	m_CarDoor[2]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
	m_CarDoor[3]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
	m_Car_Window[4]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);
    for(int i =0;i<5;i++)
        m_Car_Window[i]->SetScale(pConfig.smc_hmi.CAR_MODEL_SCALE_X, pConfig.smc_hmi.CAR_MODEL_SCALE_Y, pConfig.smc_hmi.CAR_MODEL_SCALE_Z);

	//m_objectCamera = m_sceneCamera;
    //m_Car->SetEnable(0);
	//m_mirror[0]->SetScale(1000.0,1000.0,1000.0);
	//m_SUV->SetScale(1.1,1.0,1.0);
#ifdef EMIRROR
    m_objectNode->SetEnable(0);
#endif

}
#define RADAR_ALARM_POINT_NUM 2
#define RADAR_ALARM_MESH_NUM 8
void SVScene::InitRadarAlram(BEV_CONFIG_T  pConfig,ISceneNode* p_render_node,IMesh *pMesh[],INode *OverlayNode[],GlSVRadarAlarm radar_alarm[],IMaterial* material[],unsigned char calib_mode)
{

	IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
	Overlay_Para radar_data_cfg;
	RADAR_ALARM_CONFIG radar_data_cfg_private;

	Float32 *p_Overlay_Data;
	Int32 iSize;
	XRVertexLayout data_format;
    float pos[3]={0.0,-0,0};




    for(int i =0;i<RADAR_ALARM_MESH_NUM;i++)
    {
    	tempmaterialid = p_render_node->CreateMaterial(Material_Rigid_Blend, &material[i]);
	    material[i]->SetDiffuseMap(RADARALARM);
	    int lisenceMeshId = p_render_node->CreateMesh(ModelType_Plane_Dynamic,2,  RADAR_ALARM_POINT_NUM,0, "radaralarm",&pMesh[i]);

	    int groundId = p_render_node->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &OverlayNode[i]);

    	OverlayNode[i]->SetMesh(lisenceMeshId);
    	OverlayNode[i]->SetEnable(0);


        pMesh[i]->LockData(&p_Overlay_Data,&data_format,&iSize);

        radar_data_cfg.dynamic_overlay_point_num = RADAR_ALARM_POINT_NUM;
        radar_data_cfg.vehicle_length = pConfig.smc_hmi.VEHICLE_LENGTH;
        radar_data_cfg.vehicle_width = 1855;
        radar_data_cfg.vehicle_axis_length = 2700;
        radar_data_cfg.vehicle_front_wheel2bumper_length = 956;
        radar_data_cfg.vehicle_rear_wheel2bumper_length = 889;
        radar_data_cfg.model_scale = SCALE_3D_TO_2D_X;

        AVMData::GetInstance()->m_exParam->GetCameraPos(radar_data_cfg.m_front_cam_pos_wld,2);

        radar_data_cfg.m_model_bottom = pConfig.smc_hmi.SPACE_MODEL_Y_MIN;
        //memcpy(radar_data_cfg.m_rear_cam_pos_wld,&(PoseTrans[3*3]),3*sizeof(float));
        AVMData::GetInstance()->m_exParam->GetCameraPos(radar_data_cfg.m_rear_cam_pos_wld,3);

        radar_data_cfg.m_calib_center_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CY);
        radar_data_cfg.m_calib_center_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CX);
        radar_data_cfg.m_calib_mmpp_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMY);
        radar_data_cfg.m_calib_mmpp_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMX);
        radar_data_cfg.m_model_bottom = -m_bev_config.smc_hmi.SPACE_MODEL_Y_MIN*m_bev_config.smc_hmi.SPACE_MODEL_SCALE_SIZE;
        radar_data_cfg_private.obstacle_height = 200;
        radar_alarm[i].Init(radar_data_cfg);
        radar_alarm[i].InitPrivate(radar_data_cfg_private,i,0);
        radar_alarm[i].SetUpBuffer(p_Overlay_Data,RADAR_ALARM_POINT_NUM,8,calib_mode);

    }

}



void SVScene::InitProductModel()
{
    Int32 iRadarMtlId;
    IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
	IAProperty* val=0;

	IMaterial* carmtl;

	iRadarMtlId = m_objectNode->CreateMaterial(Material_Glossy, &carmtl);
	carmtl->SetDiffuseMap(YELLOWTEX );
	carmtl->SetEnvironmentMap(CARENV);
	carmtl->SetAmbientMap(OTHERTEXMASK);

	m_iRadarId = m_objectNode->LoadModelFromFile(IFVODEL, iRadarMtlId, -1, InsertFlag_Default, 0, -140, -100,0.8, &m_ifv);
	m_ifv->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_ifv->SetEnable(0);
	m_ifv->RotateDX(90);
	m_ifv->RotateDY(-90);

	m_iRadarId = m_objectNode->LoadModelFromFile(ESRMODEL, iRadarMtlId, -1, InsertFlag_Default, 0, -370, -580,RADAR_MODEL_SCALE, &m_radar[1]);
	m_radar[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_radar[1]->SetEnable(0);
	m_radar[1]->RotateDY(180);

	m_iRadarId = m_objectNode->LoadModelFromFile(RSDSMODEL, iRadarMtlId, -1, InsertFlag_Default, 190, -310, 560,RSDS_MODEL_SCALE, &m_rsds[0]);
	m_rsds[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_rsds[0]->SetEnable(0);

	m_rsds[0]->RotateDY(-200);

	m_iRadarId = m_objectNode->LoadModelFromFile(RSDSMODEL, iRadarMtlId, -1, InsertFlag_Default, -190,-310, 560,RSDS_MODEL_SCALE, &m_rsds[1]);
	m_rsds[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_rsds[1]->SetEnable(0);
	m_rsds[1]->RotateDZ(180);
	m_rsds[1]->RotateDY(160);


	m_iRadarId = m_objectNode->LoadModelFromFile(CAMERAMODEL, iRadarMtlId, -1, InsertFlag_Default, 300, -250, -130,CAMERA_MODEL_SCALE, &m_bev[1]);
	m_bev[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_bev[1]->RotateDY(100);
	m_bev[1]->RotateDX(40);
	m_bev[1]->SetEnable(0);

	m_iRadarId = m_objectNode->LoadModelFromFile(CAMERAMODEL, iRadarMtlId, -1, InsertFlag_Default, -300, -250, -130,CAMERA_MODEL_SCALE, &m_bev[2]);
	m_bev[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_bev[2]->SetEnable(0);
	m_bev[2]->RotateDX(40);
	m_bev[2]->RotateDY(-100);

	m_iRadarId = m_objectNode->LoadModelFromFile(CAMERAMODEL, iRadarMtlId, -1, InsertFlag_Default, 0, -350, -590,CAMERA_MODEL_SCALE, &m_bev[3]);
	m_bev[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_bev[3]->SetEnable(0);

	m_bev[3]->RotateDX(40);

	m_iRadarId = m_objectNode->LoadModelFromFile(CAMERAMODEL, iRadarMtlId, -1, InsertFlag_Default, 0, -250, 610,CAMERA_MODEL_SCALE, &m_bev[4]);
	m_bev[4]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_bev[4]->SetEnable(0);
	m_bev[4]->RotateDY(180);

	m_bev[4]->RotateDX(40);
	m_iRadarId = m_objectNode->LoadModelFromFile(BEVMODEL, iRadarMtlId, -1, InsertFlag_Default, 0, -340, 350,CAMERA_MODEL_SCALE, &m_bev[0]);
	m_bev[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
	m_bev[0]->SetEnable(0);
	m_bev[0]->RotateDY(180);

	m_bev[0]->RotateDX(90);


	float color[3]={1.0,0.0,0.0};

    InitRadarWaveMesh(3600.0,10,10,20,0,&m_RadarWaveMesh,&m_RadarWavePlane[0],color,WAVETEX);
    m_RadarWavePlane[0]->RotateDX(90);

    m_RadarWavePlane[0]->RotateDY(-80);

    m_RadarWavePlane[0]->SetPosition(0,-370,-580);
    m_RadarWavePlane[0]->SetEnable(0);

    color[0]=1.0;
    color[1]=0.0;
    color[2]=0.0;
    InitRadarWaveMesh(1600.0,10,20,160,0,&m_RadarWaveMesh,&m_RadarWavePlane[1],color,WAVETEX);
    m_RadarWavePlane[1]->RotateDX(90);
    m_RadarWavePlane[1]->RotateDY(120);
    m_RadarWavePlane[1]->SetPosition(190,-310,560);
    m_RadarWavePlane[1]->SetEnable(0);

    InitRadarWaveMesh(1600.0,10,20,160,0,&m_RadarWaveMesh,&m_RadarWavePlane[2],color,WAVETEX);
    m_RadarWavePlane[2]->RotateDX(90);
    m_RadarWavePlane[2]->RotateDY(220);
    m_RadarWavePlane[2]->SetPosition(-190,-310,560);
    m_RadarWavePlane[2]->SetEnable(0);

    color[0]=1.0;
    color[1]=1.0;
    color[2]=0.0;
    InitRadarWaveMesh(2000.0,10,10,60,0,&m_RadarWaveMesh,&m_RadarWavePlane[3],color,WAVETEX);
    m_RadarWavePlane[3]->RotateDX(90);
    m_RadarWavePlane[3]->RotateDY(-60);
    m_RadarWavePlane[3]->SetPosition(0,-370,-580);
    m_RadarWavePlane[3]->SetEnable(0);


	tempmaterialid = m_objectNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
	tempcarmtl->SetDiffuseMap(WAVETEX);
	tempcarmtl->SetEnvironmentMap(BLUETEX);
#define DISTANCE_SCALE	-400
#define TIME_INT   0.3
#define INIT_SCALE	0.5
#define INIT_SCALE_Z	0.75
	modelid = m_objectNode->LoadModelFromFile(RADARWAVEBULLETMODEL, tempmaterialid, -1, InsertFlag_Default, 0, -100, 0, 1, &m_radarwave_bullet[0]);
	//m_radarwave_bullet[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ|AP_X | AP_Y | AP_Z);
	m_radarwave_bullet[0]->SetEnable(0);
	m_radarwave_bullet[0]->RotateDX(-90);
	m_radarwave_bullet[0]->RotateDY(180);
	m_radarwave_bullet[0]->RotateDZ(-1);
    //float *key_move=0;
    float dist_state[3]={1000,10,0.1};
    float init_state[3];
    float key_move[]={
  	    0,     0,     0,0,
	    TIME_INT,    1*DISTANCE_SCALE,    INIT_SCALE,  INIT_SCALE_Z,
		TIME_INT*2,    4*DISTANCE_SCALE,    INIT_SCALE*4, INIT_SCALE_Z*4,
		TIME_INT*3,    9*DISTANCE_SCALE,    INIT_SCALE*9, INIT_SCALE_Z*9,
		TIME_INT*4,    16*DISTANCE_SCALE,    INIT_SCALE*16, INIT_SCALE_Z*16,
		TIME_INT*5,   25*DISTANCE_SCALE,     INIT_SCALE*25, INIT_SCALE_Z*25,
		TIME_INT*5+0.01,   36*DISTANCE_SCALE,     INIT_SCALE*0, INIT_SCALE_Z*0


    };

    m_radarwave_bullet[0]->GetCAProperty(AP_Z, &val);
    init_state[0] = val->Get();
    m_radarwave_bullet[0]->SetScale(1.0,2.0,1.0);
    m_radarwave_bullet[0]->GetCAProperty(AP_SX, &val);

    init_state[1] = val->Get();
    init_state[2] = 0.6;
    //GenerateRadarWaveAnimateKey(&key_move,5.0,dist_state,init_state,2,10);
    am->CreateKeyAnimation(key_move, sizeof(key_move)/16, 3, &bulletrun,AnimationStyle_KeySimpleLinear);

    m_radarwave_bullet[0]->GetCAProperty(AP_Z, &val);
    bulletrun->BindProperty(0, val);
    m_radarwave_bullet[0]->GetCAProperty(AP_SZ, &val);
    bulletrun->BindProperty(1, val);
    m_radarwave_bullet[0]->GetCAProperty(AP_SX, &val);
    bulletrun->BindProperty(2, val);

    bulletrun->SetDeltaUpdate(0);
    //bulletrun->Start();
    //InitRadarWaveEffect();
    tempmaterialid = m_objectNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
    tempcarmtl->SetDiffuseMap(REDTEX);
    tempcarmtl->SetEnvironmentMap(CARENV);

    modelid = m_objectNode->LoadModelFromFile(RADARWAVEMODEL, tempmaterialid, -1, InsertFlag_Default, 0, -140, -160, 5, &m_radarwave[0]);
    m_radarwave[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY | AP_SZ);
    m_radarwave[0]->SetEnable(0);
    m_radarwave[0]->RotateDX(-90);
    m_radarwave[0]->RotateDY(1);
    m_radarwave[0]->RotateDZ(-1);
    m_radarwave[0]->SetScale(3,6,2.0);

    color[0]=1.0;
    color[1]=0.0;
    color[2]=0.0;
    InitRadarWaveMesh(3000.0,1,10,60,0,&m_RadarWaveMesh,&m_RadarWavePlane[4],color,IFVWAVETEX,0.2);
    m_RadarWavePlane[4]->RotateDX(90);
    m_RadarWavePlane[4]->RotateDY(-60);
    m_RadarWavePlane[4]->SetPosition(0,-140,-120);
    m_RadarWavePlane[4]->SetEnable(0);




}

void SVScene::InitTourDisplayEffect()
{
	IAProperty* val=0;

#define fTransitionTime 4.0
#if 0
	float key[]={fTransitionTime ,0.0,20.0,
	             10.0+fTransitionTime,180.0,0.0,
	             18.0+fTransitionTime,360.0,20.0 ,
	             26.0+fTransitionTime,540.0,90.0  ,
	             34.0+fTransitionTime,720.0,20.0};
	float key[]={0,0.0,0.0,
	             1,0,0.0,
	             2,25,25,
	             3,50,50.0,
	             4,90,90.0};
#endif

	float key[]={0 ,0.0,30.0,
	             2*fTransitionTime,180.0,90.0,
	             3*fTransitionTime,360.0,30.0  ,
	             4*fTransitionTime,720.0,45.0};


    am->CreateKeyAnimation(key, sizeof(key)/12, 2, &bevTour[0],AnimationStyle_KeySpline,0);
    m_objectCamera->GetCAProperty(AP_RX,&val);
    bevTour[0]->BindProperty(0, val);
    m_objectCamera->GetCAProperty(AP_RY,&val);
    bevTour[0]->BindProperty(1, val);


    am->CreateKeyAnimation(key, sizeof(key)/12, 2, &bevTour[1],AnimationStyle_KeySpline,0);
    m_sceneCamera->GetCAProperty(AP_RX,&val);
    bevTour[1]->BindProperty(0, val);
    m_sceneCamera->GetCAProperty(AP_RY,&val);
    bevTour[1]->BindProperty(1, val);


}

//void SVScene::CreateMeshFromFile(GLfloat *pVertex,unsigned short *pIndex,int dstWidth, int dstHeight)
//{




//}
void SVScene::Init2DStichAVMNode()
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

	m_stich_node = new SVNode2DStich;

	m_stich_node->Init();
	sv2Ddelegate = new RenderDelegateSV2D;


	// Interleaved vertex data
	m_2DAVMNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_2DAVMNode);
	m_2DAVMNode->SetRenderROI(&Stich2DReg);






//render stich aera and ground aera.
	tempmaterialid = m_2DAVMNode->CreateMaterial(Material_Rigid_Texture, &m_pstich_Mtl);
    m_pstich_Mtl->SetDiffuseMap(m_stich_node->GetStichFrameTextureId());

    int lisenceMeshId = m_2DAVMNode->CreateMesh(ModelType_Plane_Dynamic,2,	2,0, "Stich", &pMesh);


	int  groundId = m_2DAVMNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0,0,0, 1.0, &pNode);

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

//render overlay;
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    InitOverlay(m_bev_config,m_2DAVMNode,&m_overlaymesh_2d,&m_overlay_2d,&m_overlay_data_2d,calib_2D_STICH,pos);

    //render car image
    m_pNodeSonar = new SVNodeSonar;
    m_pNodeSonar->Init(&m_bev_config,m_2DAVMNode);


#if 0

    AVM_Calib_2D_T result;
	 
	 
    result.center_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CX);
    result.center_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CY);
    result.ppmm_x= AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMX);
    result.ppmm_y= AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMY);
	 
	 
	 
    m_APA_overlay = new GlSVOverlayAPA;
    m_APA_overlay->Init(m_2DAVMNode,XR_RES,result);
			
		
#endif

	

	//step 2 prepare mesh for 2D stiching
    int i = eCarImageMesh;
 	m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
 	meshid = m_2DAVMNode->CreateMesh(ModelType_Null, 0,0,0,MeshName, &m_planeMesh);
 	m_planeMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
 	m_planeMesh->SetName(Model);
 	m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize);
 	m_planeMesh->LoadIndexFromArray(pIndex ,2* BufferSize);
    SV2DMTL = m_2DAVMNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
    m_SV2DMtl->CreateMaterialEffect(&pIEffect);
    pIEffect->InitShaderFromFile("Effect_SV2DCarImage", c_SV2DVertShaderSrcFileLUT, c_SV2DFragCarImageShaderSrcFile,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(sv2Ddelegate); 
	
	 
	m_SV2DMtl->SetDiffuseMap(CAR2DICON);

	m_stich_wheel=new GlSVOverlayStichWheel;
	m_stich_wheel->Init(m_2DAVMNode,XR_RES,m_veh_param);

	modelId = m_2DAVMNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 0, &pCarImageNode);
	pCarImageNode->SetMesh(meshid);
	pCarImageNode->SetName(Model);		
	pCarImageNode->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	pCarImageNode->SetEnable(1);
	InitRadarAlram(m_bev_config,m_2DAVMNode,&m_RadarAlarm_Mesh_2d[0],&m_RadarAlarm_Node_2d[0],m_radar_alram_2d,&m_RadarAlarm_Mtl_2d[0],calib_2D_STICH);

	/////////////////////////////cameraObject//////////////////
#ifdef ALI
	int cameraId = m_2DAVMNode->CreateCamera(120, CAMERA_ASPECT, 10.0f, 16000.0f, &m_2dviewCamera);
#else
	int cameraId = m_2DAVMNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_2dviewCamera);
#endif



	m_2dviewCamera->Set2DCamera(1);
	m_2dviewCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	m_2dviewCamera->LookAt(0.0,0.0,-0.0);
	m_2dviewCamera->RotateAround(0,45);
	m_2DAVMNode->SetCamera(cameraId);
#ifndef ALI
	InitSingleViewNode(m_SV2DData);
#endif
}


void SVScene::Init2DAVMNode()
{
#ifdef CAR_TRANSPARENT
    Init2DStichAVMNode();
#else

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


	// Interleaved vertex data
	m_2DAVMNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_2DAVMNode);
	m_2DAVMNode->SetRenderROI(&Stich2DReg);


	//m_2DAVMNode->SetClear(TRUE, TRUE);
    //m_2DAVMNode->SetClearColor(0.0,0.0,0.0,1.0);
	int displayChannel = 2;


	sv2Ddelegate = new RenderDelegateSV2D();

	//sv2DImagedelegate = new RenderDelegateSV2DImage();
	sv2Ddelegate->Init();
#define Material_MAX 6
    //step 1. prepare for Material ,different camera input image
	IRenderEffect* pIEffect[Material_MAX];
    int SV2DMTL[Material_MAX];
    float pos[3];


	for(int i=0;i<Material_MAX;i++)
	{
    	SV2DMTL[i] = m_2DAVMNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
        m_SV2DMtl->CreateMaterialEffect(&pIEffect[i]);
		if(i == 4)
		{
			pIEffect[i]->InitShaderFromFile("Effect_SV2DImage", c_SV2DVertShaderSrcFileLUT, c_SV2DFragStaticShaderSrcFile,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
            //pIEffect[i]->SetRenderDelegate(sv2DImagedelegate);
		}
		else
		{
		   	pIEffect[i]->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);


		}
		pIEffect[i]->SetRenderDelegate(sv2Ddelegate);
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
    	    m_SV2DMtl->SetDiffuseMap(CAR2DICON);
			//m_SV2DMtl->SetDiffuseMap(RADARALARMTEX[0]);

    	    //m_SV2DMtl->SetDiffuseMap(ARROUNDVIEWRIGHT);
		}
		else
		{

            AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,right_camera_index);
		}


	}
	//Load 2D Lookup table
	//SV2DData.Init();

    //step 2 prepare mesh for 2D stiching
    for(int i =0;i<=8;i++)
    {
        m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
	    meshid[i] = m_2DAVMNode->CreateMesh(ModelType_Null, 0,0,0,MeshName[i], &m_planeMesh);
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


    	modelId = m_2DAVMNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
    	m_SV2Dplane[i]->SetMesh(meshid[i]);
    	m_SV2Dplane[i]->SetName(Model[i]);
		m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
    }

	//m_ground->SetMesh(lisenceMeshId);
	//m_ground->RotateDX(90);
	//m_ground->SetEnable(pConfig.smc_hmi.GROUND_MODEL_ENABLE);
    //InitOverlay(m_bev_config,m_2DAVMNode,m_overlaymesh,m_overlay,&m_overlay_data);

 	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

    InitOverlay(m_bev_config,m_2DAVMNode,&m_overlaymesh_2d,&m_overlay_2d,&m_overlay_data_2d,calib_2D_STICH,pos);



	int i=8;
    materialID =4;
	modelId = m_2DAVMNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
	m_SV2Dplane[i]->SetMesh(meshid[i]);
	m_SV2Dplane[i]->SetName(Model[i]);
	m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	InitRadarAlram(m_bev_config,m_2DAVMNode,&m_RadarAlarm_Mesh_2d[0],&m_RadarAlarm_Node_2d[0],m_radar_alram_2d,&m_RadarAlarm_Mtl_2d[0],calib_2D_STICH);

	/////////////////////////////cameraObject//////////////////
	//int cameraId = m_viewNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.f, 16000.0f, &m_viewCamera);
#ifdef ALI
	int cameraId = m_2DAVMNode->CreateCamera(120, CAMERA_ASPECT, 10.0f, 16000.0f, &m_2dviewCamera);
#else
	int cameraId = m_2DAVMNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_2dviewCamera);
#endif

	//camera->SetOrientation(0, 0, 0);
	//m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
	//m_objectCamera->LookAt(0.0,0,-0.0);
	//camera->RotateAround(2,2);

	m_2dviewCamera->Set2DCamera(1);
	m_2dviewCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	m_2dviewCamera->LookAt(0.0,0.0,-0.0);
	m_2dviewCamera->RotateAround(0,45);
	m_2DAVMNode->SetCamera(cameraId);
#ifndef ALI
	InitSingleViewNode(m_SV2DData);
#endif
#endif
}

void SVScene::Init2DGroundNodeRT(int j)
{


	Int32 tempmaterialid;
    ICamera*pCamera;
	IMesh *pGroundMesh;
    INode *pGroundNode;
	int cameraId;
    // float *pVertexData;
	XRVertexLayout  data_format;
	Int32 icount;
	int i=0;
    float *pVertexData;

    // for(int j =0;j<2;j++)
    // {
    int ground_id = rm->CreateRenderTarget(XrGetScreenWidth()*0.3, XrGetScreenHeight(), XR_R8G8B8A8, XR_NONE, &m_groundRT[j]);


    // Interleaved vertex data
    m_GroundNodeId = g_pIXrCore->CreateRenderNodeScene(ground_id, &m_GroundNode[j]);




    //create material
    tempmaterialid = m_GroundNode[j]->CreateMaterial(Material_Rigid_Texture, &m_ground_mtl[j]);
    //m_ground_mtl->SetDiffuseMap(m_lisenceRT->GetTextureId());
    m_ground_mtl[j]->SetDiffuseMap(RADARALARMTEX[j]);
    int lisenceMeshId = m_GroundNode[j]->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "ground", &pGroundMesh);
    //int lisenceMeshId = m_GroundNode->CreateMesh(ModelType_Plane,1,  1,0, "ground", &pGroundMesh);

    //int lisenceMeshId = m_GroundNode->CreateMesh(ModelType_Plane,1,  1,0, "ground", &pGroundMesh);
    int groundId = m_GroundNode[j]->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0,0,0, 1.0, &pGroundNode);
    m_pMeshStichGround[j] = pGroundMesh;

    m_pMeshStichGround[j]->LockData(&pVertexData,&data_format,&icount);
    pVertexData[0]=-1.0;
    pVertexData[1]=-1.0;
    pVertexData[2]=0.0;
    pVertexData[8]=1.0;
    pVertexData[9]=-1.0;
    pVertexData[10]=0.0;
    pVertexData[16]=-1.0;
    pVertexData[17]=1.0;
    pVertexData[18]=0.0;
    pVertexData[24]=1.0;
    pVertexData[25]=1.0;
    pVertexData[26]=0.0;

    m_pMeshStichGround[j]->UnLockData();

    cameraId = m_GroundNode[j]->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &pCamera);
    pCamera->Set2DCamera(1);
    pCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
    pCamera->LookAt(0.0,0.0,-0.0);
    pCamera->RotateAround(0,45);
    m_GroundNode[j]->SetCamera(cameraId);

    pGroundNode->SetMesh(lisenceMeshId);
    // }
}

void SVScene::Init2DAVMNodeRT()
{

	int meshid[eCarImageMesh+1];
	int modelId,materialID;
	float *pData;
	unsigned short	 *pIndex;
	unsigned int BufferSize;


	char *MeshName[eCarImageMesh+1]={"FrontMesh","RearMesh","LeftMesh","RightMesh","FrontLeftMesh","FrontRightMesh","RearLeftMesh","RearRightMesh","Car"};
	char *Model[eCarImageMesh+1]={"0","1","2","3","4","5","6","7","8"};

	int rtid = rm->CreateRenderTarget(XrGetScreenWidth()*0.3, XrGetScreenHeight(), XR_R8G8B8A8, XR_NONE, &m_lisenceRT);

	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_2D_VERTEX_SHADER);
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_2D_FRAGMENT_SHADER);
	// Interleaved vertex data
	m_2DAVMNodeId = g_pIXrCore->CreateRenderNodeScene(rtid, &m_2DAVMNode);
	//m_2DAVMNode->SetRenderROI(&Stich2DReg);


	m_2DAVMNode->SetClear(TRUE, TRUE);
    m_2DAVMNode->SetClearColor(0.0,0.0,0.0,1.0);
	int displayChannel = 2;


	sv2Ddelegate = new RenderDelegateSV2D();

	//sv2DImagedelegate = new RenderDelegateSV2DImage();
	sv2Ddelegate->Init();
#define Material_MAX 6
    //step 1. prepare for Material ,different camera input image
	IRenderEffect* pIEffect[Material_MAX];
    int SV2DMTL[Material_MAX];
    float pos[3];


	for(int i=0;i<Material_MAX;i++)
	{
    	SV2DMTL[i] = m_2DAVMNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
    	m_SV2DMtl->CreateMaterialEffect(&pIEffect[i]);
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
    	    //m_SV2DMtl->SetDiffuseMap(CAR2DICON);

    	    m_SV2DMtl->SetDiffuseMap(m_lisenceRT->GetTextureId());

		}
		else
		{

		    AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,right_camera_index);
		}
		if(i == 4)
		{
			pIEffect[i]->InitShaderFromFile("Effect_SV2DImage", c_SV2DVertShaderSrcFileLUT, c_SV2DFragStaticShaderSrcFile,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
            //pIEffect[i]->SetRenderDelegate(sv2DImagedelegate);
		}
		else
		{
		   	pIEffect[i]->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);


		}
        pIEffect[i]->SetRenderDelegate(sv2Ddelegate);
	}
	//Load 2D Lookup table
	//SV2DData.Init();

    //step 2 prepare mesh for 2D stiching
    for(int i =0;i<=8;i++)
    {
        m_SV2DData->GetVertexBuffer(i,&pData,&BufferSize);
	    meshid[i] = m_2DAVMNode->CreateMesh(ModelType_Null, 0,0,0,MeshName[i], &m_planeMesh);
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


    	modelId = m_2DAVMNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
    	m_SV2Dplane[i]->SetMesh(meshid[i]);
    	m_SV2Dplane[i]->SetName(Model[i]);
		m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
    }

	//m_ground->SetMesh(lisenceMeshId);
	//m_ground->RotateDX(90);
	//m_ground->SetEnable(pConfig.smc_hmi.GROUND_MODEL_ENABLE);
    //InitOverlay(m_bev_config,m_2DAVMNode,m_overlaymesh,m_overlay,&m_overlay_data);


	int i=8;
    materialID =4;
	modelId = m_2DAVMNode->CreateModel(0, SV2DMTL[materialID], -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
	m_SV2Dplane[i]->SetMesh(meshid[i]);
	m_SV2Dplane[i]->SetName(Model[i]);
	m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);

	/////////////////////////////cameraObject//////////////////
	//int cameraId = m_viewNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.f, 16000.0f, &m_viewCamera);
	int cameraId = m_2DAVMNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_2dviewCamera);

	//camera->SetOrientation(0, 0, 0);
	//m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
	//m_objectCamera->LookAt(0.0,0,-0.0);
	//camera->RotateAround(2,2);

	m_2dviewCamera->Set2DCamera(1);
	m_2dviewCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	m_2dviewCamera->LookAt(0.0,0.0,-0.0);
	m_2dviewCamera->RotateAround(0,45);
	m_2DAVMNode->SetCamera(cameraId);
	InitSingleViewNode(m_SV2DData);
	//m_ground_mtl->SetDiffuseMap(m_lisenceRT->GetTextureId());
	Init2DAVMNodeRTDraw(cameraId);


}

void SVScene::InitTourDisplaySecEffect()
{
	IAProperty* val=0;

#define fTransitionTime 5.0
#if 0
	float key[]={0 ,0.0,30.0, 0,0,0,
	             fTransitionTime ,180.0,90.0, 0,0,0,
	             2*fTransitionTime,360.0,30.0 ,0,0,0,
		         2*fTransitionTime+1,360.0,45.0 ,0,0,0,
		         2*fTransitionTime+2,360.0,45.0 ,0,-1000,0,
	             3*fTransitionTime+2,540.0,45.0,  0,-1000,0,
	             4*fTransitionTime+2,720.0,45.0  , 0,-1000,0,
                 4*fTransitionTime+3,720.0,45.0  , 0,0,0,};
#else
	float key[]={0 ,0.0,30.0, 0,0,0,
	             fTransitionTime ,180.0,90.0, 0,0,0,
	             2*fTransitionTime,360.0,30.0 ,0,0,0,
		         2*fTransitionTime+1,360.0,45.0 ,0,0,0,
		         2*fTransitionTime+2,360.0,45.0 ,0,0,0,
    };

#endif
    am->CreateKeyAnimation(key, sizeof(key)/24, 5, &bevSecTour[0],AnimationStyle_KeyLinear,0);
    m_objectCamera->GetCAProperty(AP_RX,&val);
    bevSecTour[0]->BindProperty(0, val);
    m_objectCamera->GetCAProperty(AP_RY,&val);
    bevSecTour[0]->BindProperty(1, val);
    m_objectCamera->GetCAProperty(AP_CamAtX,&val);
    bevSecTour[0]->BindProperty(2, val);
    m_objectCamera->GetCAProperty(AP_CamAtY,&val);
    bevSecTour[0]->BindProperty(3, val);
    m_objectCamera->GetCAProperty(AP_CamAtZ,&val);
    bevSecTour[0]->BindProperty(4, val);


    am->CreateKeyAnimation(key, sizeof(key)/24, 5, &bevSecTour[1],AnimationStyle_KeyLinear,0);
    m_sceneCamera->GetCAProperty(AP_RX,&val);
    bevSecTour[1]->BindProperty(0, val);
    m_sceneCamera->GetCAProperty(AP_RY,&val);
    bevSecTour[1]->BindProperty(1, val);
	m_sceneCamera->GetCAProperty(AP_CamAtX,&val);
	bevSecTour[1]->BindProperty(2, val);
	m_sceneCamera->GetCAProperty(AP_CamAtY,&val);
	bevSecTour[1]->BindProperty(3, val);
	m_sceneCamera->GetCAProperty(AP_CamAtZ,&val);
	bevSecTour[1]->BindProperty(4, val);


}


void SVScene::InitBevDisplayEffect()
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
    am->CreateKeyAnimation(key_move, sizeof(key_move)/28, 6, &bevdisplay[0],AnimationStyle_KeySimpleLinear,0);

    m_objectCamera->GetCAProperty(AP_RX,&val);
    bevdisplay[0]->BindProperty(0, val);
    m_objectCamera->GetCAProperty(AP_RY, &val);
    bevdisplay[0]->BindProperty(1, val);
    m_objectCamera->GetCAProperty(AP_Z, &val);
    bevdisplay[0]->BindProperty(2, val);
    m_objectCamera->GetCAProperty(AP_CamAtX,&val);
    bevdisplay[0]->BindProperty(3, val);
    m_objectCamera->GetCAProperty(AP_CamAtY, &val);
    bevdisplay[0]->BindProperty(4, val);
    m_objectCamera->GetCAProperty(AP_CamAtZ, &val);
    bevdisplay[0]->BindProperty(5, val);
    bevdisplay[0]->SetDeltaUpdate(0);

	am->CreateKeyAnimation(key_move, sizeof(key_move)/28, 6, &bevdisplay[1],AnimationStyle_KeySimpleLinear,0);

    m_sceneCamera->GetCAProperty(AP_RX,&val);
    bevdisplay[1]->BindProperty(0, val);
    m_sceneCamera->GetCAProperty(AP_RY, &val);
    bevdisplay[1]->BindProperty(1, val);
    m_sceneCamera->GetCAProperty(AP_Z, &val);
    bevdisplay[1]->BindProperty(2, val);
    m_sceneCamera->GetCAProperty(AP_CamAtX,&val);
    bevdisplay[1]->BindProperty(3, val);
    m_sceneCamera->GetCAProperty(AP_CamAtY, &val);
    bevdisplay[1]->BindProperty(4, val);
    m_sceneCamera->GetCAProperty(AP_CamAtZ, &val);
    bevdisplay[1]->BindProperty(5, val);
	bevdisplay[1]->SetDeltaUpdate(0);


}

void SVScene::GenerateRadarWaveAnimateKey(float **fKey,float time_period,float *dist_state,float *init_state,int item_num,int key_num)
{
	*fKey = new float[(item_num+1)*(key_num+1)];
	float acc = ((dist_state[0]-init_state[0])*2)/(time_period*time_period);
	float scale_step =(dist_state[1]-init_state[1])/key_num;
	float alpha_step =(dist_state[2]-init_state[2])/key_num;
	float *p = *fKey;
    for(int i=0;i<key_num;i++)
    {
        p[i*(item_num+1)]= (time_period/key_num)*i;
		p[i*(item_num+1)+1]= 0.5*acc*p[i*(item_num+1)]*p[i*(item_num+1)]+init_state[0];
		p[i*(item_num+1)+2]= scale_step*i+init_state[1];
		//p[i*item_num+3]= scale_step*i+init_state[2];
    }

	p[key_num*(item_num+1)]= (time_period/key_num)*key_num;
	p[key_num*(item_num+1)+1]= init_state[0];
	p[key_num*(item_num+1)+2]= 0;
	//p[key_num*item_num+3]= 0;



}
void SVScene::SetupLisence()
{
	Int32 textMtlId ;
	int textId;
	if (!m_lisenceRT) {

		int rtid = rm->CreateRenderTarget(325, 100, XR_R8G8B8A8, XR_NONE, &m_lisenceRT);

		int m_lisenceNodeId = g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, rtid, &m_lisenceNode);
		int logoMtlId = m_lisenceNode->CreateUIMaterial(Material_UI_Spirit, XR_RES"lisence.dds");
		int logoLayerId = m_lisenceNode->CreateSpirit( -1, InsertFlag_Default, logoMtlId, 1.0, 10, 0, 0);

		textMtlId = m_lisenceNode->CreateUIFontMaterial(XR_RES"SEASANS.TTF", 0);
		textId = m_lisenceNode->CreateTextLayer(-1, InsertFlag_Default, textMtlId, 1.0, 100, 7, &text, 84,40);
		text->SetText("O-FLIM");
        text->SetFontSize(69);



		textMtlId = m_lisenceNode->CreateUIChineseFontMaterial(XR_RES"test6.dds", 0);
		textId = m_lisenceNode->CreateChineseTextLayer(-1, InsertFlag_Default, textMtlId, 1.0, 30, 0, &Chinesetext, 84);
		int index=0;
		Chinesetext->SetText(index);
        Chinesetext->SetFontSize(84);

		m_lisenceNode->SetClear(true,false);
		m_lisenceNode->SetClearColor(0.63,0.63,0.63,1.0);
		IMaterial* lisencemtl;
		int m_lisencemtlId = m_objectNode->CreateMaterial(Material_Glossy, &lisencemtl);
	    lisencemtl->SetDiffuseMap(m_lisenceRT->GetTextureId());
		lisencemtl->SetEnvironmentMap(CARENV);
		int lisenceMeshId = m_objectNode->CreateMesh(ModelType_Plane, 3.2, 0.8, 10, "lisence", &m_lisenceMesh);
		int modelId = m_objectNode->CreateModel(0, m_lisencemtlId, m_carId, InsertFlag_Child, -0, 50, 1667, 6, &m_lisence);
		m_lisence->SetMesh(lisenceMeshId);
		m_lisence->SetScale(80,100,100);
#ifdef CAR_MODEL
        modelId = m_objectNode->CreateModel(0, m_lisencemtlId, m_iSUVId, InsertFlag_Child, -0, 50, 1698, 0.6, &m_lisence);
        m_lisence->SetMesh(lisenceMeshId);
        m_lisence->SetScale(60,90,90);

        modelId = m_objectNode->CreateModel(0, m_lisencemtlId, m_iVanId, InsertFlag_Child, 0,-150, 1504, 1.0, &m_lisence);
        m_lisence->SetMesh(lisenceMeshId);
        m_lisence->SetScale(80,100,100);

        modelId = m_objectNode->CreateModel(0, m_lisencemtlId, m_iTruckId, InsertFlag_Child, -0, 50, 820, 1.0, &m_lisence);
        m_lisence->SetMesh(lisenceMeshId);
        m_lisence->SetScale(100,100,100);
#endif
        m_lisence->SetEnable(1);

	}

}
#define FRAME_BUFFER_TEXT_WIDTH 160
#define FRAME_BUFFER_TEXT_HEIGHT 160
#define SIDEMIRRORDEGREE 0.3

void SVScene::InitViewNode()
{
#define PlaneScaleX 16000.0
#define PlaneScaleY 17000.0
#define PlaneScaleY_NEG  -17000.0

#define ROTATE_ANGLE 30
#define ROTATE_LENGTH 3000
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
//#define	UIZ1  -1100.0f
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
    		    AVMData::GetInstance()->CalcUVTextureSV(&afVertices[index][slotId*8],&afVertices[index][slotId*8+3],2);



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
			afIndices[slotId+4] = (y+1)*m_meshWidth+x+1;
			afIndices[slotId+5] = (y+1)*m_meshWidth+x;

			slotId+=6;

		}
	}

	m_viewNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_viewNode);

	//m_viewNode->SetClear(FALSE, TRUE);


	m_viewNode->SetRenderROI(&FadeRightReg);
	m_viewNode->SetClearColor(1.0,0.0,0.0,1.0);
	int displayChannel = 2;


	cvdelegate = new RenderDelegateCV();

	// buffer file %s,line %d",__FILE__,__LINE__);
	cvdelegate->Init();
	cvdelegate->SetChannel(displayChannel);
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
    AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_3D_VERTEX_SHADER);
    AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_3D_FRAGMENT_SHADER);



	IRenderEffect* pIEffect;
	int CVMTL = m_viewNode->CreateMaterial(Material_Custom, &m_cvMtl);
	m_cvMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_cvMtl,rear_camera_index);
	pIEffect->InitShaderFromFile("Effect_SV", VertexName, FragShaderName,  sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
	pIEffect->SetRenderDelegate(cvdelegate);


	int meshid[3];
    for(int i =0;i<3;i++)
    {
    	meshid[i] = m_viewNode->CreateMesh(ModelType_Null, 0,0,0, "plane", &m_planeCrossMesh[i]);
    	m_planeCrossMesh[i]->LoadVertexFromArray(afVertices[i], XR_VERTEX_LAYOUT_PNT, m_meshWidth*m_meshHeight);
    	m_planeCrossMesh[i]->LoadIndexFromArray(afIndices, (m_meshWidth-1)*(m_meshHeight-1)*6*2);
    }
//#define VIEW_Z -4100
#define VIEW_Z 0

	//int mid = m_viewNode->CreateModel(0, -1, -1, InsertFlag_Default, 18000, 0, -4000, 1.0, &m_plane[0]);
	//m_plane[0]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X);


	int modelId = m_viewNode->CreateModel(0, CVMTL, -1, InsertFlag_Default, 0, 0, VIEW_Z, 1.0, &m_plane[1]);
	m_plane[1]->SetMesh(meshid[0]);
	m_plane[1]->SetName("C");
	//cvdelegate->ProcessModel(m_plane[1],"C");
	//m_plane[1]->SetScale(0,0,1);
	m_plane[1]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	modelId = m_viewNode->CreateModel(0, CVMTL, -1, InsertFlag_Default, 0, 0, VIEW_Z, 1.0, &m_plane[2]);
	m_plane[2]->SetMesh(meshid[1]);
	m_plane[2]->SetName("L");

	//cvdelegate->ProcessModel(m_plane[2],"L");
	m_plane[2]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y);
	modelId = m_viewNode->CreateModel(0, CVMTL, -1, InsertFlag_Default,0, 0, VIEW_Z, 1.0, &m_plane[3]);
	m_plane[3]->SetMesh(meshid[2]);
	m_plane[3]->SetName("R");

	//cvdelegate->ProcessModel(m_plane[3],"R");
	m_plane[3]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y);
//#endif

	/////////////////////////////cameraObject//////////////////
	//int cameraId = m_viewNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.f, 16000.0f, &m_viewCamera);
	int cameraId = m_viewNode->CreateCamera(151, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_viewCamera);

	//camera->SetOrientation(0, 0, 0);
	//m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
	//m_objectCamera->LookAt(0.0,0,-0.0);
	//camera->RotateAround(2,2);
	m_viewCamera->SetPosition(0,0,0);

	m_viewCamera->GetCAProperty(AP_RX, &rotX);

	m_viewCamera->GetCAProperty(AP_RY, &rotY);
	rotX->Set(0);
	rotY->Set(0);
	m_viewNode->SetCamera(cameraId);
	m_view_camera_id = cameraId;


}

//dota2_black: lock_data方法修改mesh后， GetVertexBuffer的值也变化了，为了保证dvr hmi不影响mesh
//使用临时数组保存lock_data修改前的值
//GetVertexBuffer 不使用

static GLfloat fVerticesSnapshot[4][28 * sizeof(GLfloat)];
void SVScene::InitSingleViewNode(GlSV2D *pSV2DData)
{

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
	m_2DSingleViewNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_2DSingleViewNode);

//   m_2DSingleViewNode->SetClear(TRUE, TRUE);
#ifdef ALIBABA_HMI
	m_2DSingleViewNode->SetRenderROI(&RightBottomSingleReg);
#else
	m_2DSingleViewNode->SetRenderROI(&RightReg);
#endif
#ifdef ALI
    m_2DSingleViewNode->SetRenderROI(&RightReg);
#else
    m_2DSingleViewNode->SetRenderROI(&RightReg);
#endif

	sv2Ddelegate = new RenderDelegateSV2D();
	sv2Ddelegate->Init();
	//step 1. prepare for Material ,different camera input image
	IRenderEffect* pIEffect;
	int SV2DMTL;
	SV2DMTL = m_2DSingleViewNode->CreateMaterial(Material_Custom, &m_SVSingleMtl);
	m_SVSingleMtl->CreateMaterialEffect(&pIEffect);

	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SVSingleMtl,front_camera_index);

	pIEffect->InitShaderFromFile("Effect_SV2D", VertexName, FragShaderName,  sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);
	pIEffect->SetRenderDelegate(sv2Ddelegate);

	//Load 2D Lookup table
	//SV2DData.Init();

    for(int i = eFrontSingle;i<=eRightSingle;i++)
    {
        //step 2 prepare mesh for 2D stiching
        IMesh* pMesh = NULL;
        pSV2DData->GetVertexBuffer(i,&pData,&BufferSize);
        meshid = m_2DSingleViewNode->CreateMesh(ModelType_Null, 1,0,0,MeshName[i-eFrontSingle], &pMesh);
        pMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
        pSV2DData->GetIndexBuffer(i,&pIndex,&BufferSize);
        pMesh->LoadIndexFromArray(pIndex ,2* BufferSize);
        m_singleviewMesh[i - eFrontSingle] = pMesh;
        memcpy(fVerticesSnapshot[i - eFrontSingle], pData, 28 * sizeof(GLfloat));
        //step 3 combine mesh and material(video texture) together.
        materialID = 5;






        modelId = m_2DSingleViewNode->CreateModel(0, SV2DMTL, -1, InsertFlag_Default, 1, 0, 0, 1, &m_SV2Dplane[i]);
        m_SV2Dplane[i]->SetMesh(meshid);
        m_SV2Dplane[i]->SetName(MeshName[i-eFrontSingle]);
        m_SV2Dplane[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
        m_SV2Dplane[i]->SetEnable(0);

    }
	m_SV2Dplane[eFrontSingle]->SetEnable(0);

    float front_cam_zone[4],rear_cam_zone[4];

	front_cam_zone[0] = AVMData::GetInstance()->GetFrontSingleViewRect(rect_left);
	front_cam_zone[1] = AVMData::GetInstance()->GetFrontSingleViewRect(rect_top);
	front_cam_zone[2] = AVMData::GetInstance()->GetFrontSingleViewRect(rect_right);
	front_cam_zone[3] = AVMData::GetInstance()->GetFrontSingleViewRect(rect_bottom);



	rear_cam_zone[0] = AVMData::GetInstance()->GetRearSingleViewRect(rect_left);
	rear_cam_zone[1] = AVMData::GetInstance()->GetRearSingleViewRect(rect_top);
	rear_cam_zone[2] = AVMData::GetInstance()->GetRearSingleViewRect(rect_right);
	rear_cam_zone[3] = AVMData::GetInstance()->GetRearSingleViewRect(rect_bottom);



	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

    InitOverlay(m_bev_config,m_2DSingleViewNode,&m_overlaymesh_2d_single,&m_overlay_2d_single,&m_overlay_data_2d_single,calib_2D_SINGLE,pos);
	m_overlay_data_2d_single.Set_Cam_Zone(2,front_cam_zone);
	m_overlay_data_2d_single.Set_Cam_Zone(3,rear_cam_zone);

	m_overlay_2d_single->SetEnable(1);
	m_overlay_2d_single->SetOpacity(1.0);

	InitRadarAlram(m_bev_config,m_2DSingleViewNode,&m_RadarAlarm_Mesh_single[0],&m_RadarAlarm_Node_single[0],m_radar_alarm_single,&m_RadarAlarm_Mtl_single[0],calib_2D_SINGLE);
    for(int i=0;i<8;i++)
    {
	    m_radar_alarm_single[i].Set_Cam_Zone(2,front_cam_zone);
		m_radar_alarm_single[i].Set_Cam_Zone(3,rear_cam_zone);
    }
	/////////////////////////////cameraObject//////////////////
	//int cameraId = m_viewNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.f, 16000.0f, &m_viewCamera);
#ifdef ALI
    int cameraId = m_2DSingleViewNode->CreateCamera(120, CAMERA_ASPECT, 10.0f, 16000.0f, &m_viewCamera);
#else
	int cameraId = m_2DSingleViewNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_viewCamera);
#endif
	m_2DSingleViewNode->SetCamera(cameraId);
    //m_2DSingleViewNode->SetEnable(1);
	m_viewCamera->Set2DCamera(1);
	m_viewCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	m_viewCamera->LookAt(0.0,0.0,-0.0);
	m_viewCamera->RotateAround(0,45);

}

void SVScene::InitAliControlViewNode(BEV_CONFIG_T bev_config)
{

	int meshid;
	int modelId,materialID;
	float *pData;
	unsigned short	 *pIndex;
	unsigned int BufferSize;
	IMesh *pMesh;
	INode *RenderNode;
	int groundId;
	int lisenceMeshId ;

	char *MeshName[]={"f","b","l","r"};

    float pos[3];

	// Interleaved vertex data
	m_AliCtrlViewNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_AliCtrlViewNode);

    m_AliCtrlViewNode->SetClear(TRUE,TRUE);
    //m_AliCtrlViewNode->SetClearColor(1.0,0.0,0.0,0.5);

#ifdef ALI
    m_AliCtrlViewNode->SetRenderROI(&UIControlReg);
#else
    m_AliCtrlViewNode->SetRenderROI(&RightReg);
#endif






	materialID = m_AliCtrlViewNode->CreateMaterial(Material_Rigid_Texture, &m_RemindMtl);
	m_RemindMtl->SetDiffuseMap(REMINDSAFE);







	//lisenceMeshId = m_AliCtrlViewNode->CreateMesh(ModelType_Plane,0.6,  0.06,0, "remind", &pMesh);

    //groundId = m_AliCtrlViewNode->CreateModel(0, materialID, -1, InsertFlag_Default,0.0,-0.86,0.0, 1.0, &RenderNode);
	//lisenceMeshId = m_AliCtrlViewNode->CreateMesh(ModelType_Plane,0.6,  0.3,0, "remind", &pMesh);
	//groundId = m_AliCtrlViewNode->CreateModel(0, materialID, -1, InsertFlag_Default,0.0,0.0,0.3, 1.0, &RenderNode);

	//RenderNode->SetMesh(lisenceMeshId);



	//step 1. prepare for Material ,different camera input image

	materialID = m_AliCtrlViewNode->CreateMaterial(Material_Rigid_Texture, &m_ControlMtl);
	m_ControlMtl->SetDiffuseMap(CONTROLPANELFRONT);







	lisenceMeshId = m_AliCtrlViewNode->CreateMesh(ModelType_Plane,1.0,  1.0,0, "ground", &pMesh);
	groundId = m_AliCtrlViewNode->CreateModel(0, materialID, -1, InsertFlag_Default,0.0,0.0,0.0, 1.0, &RenderNode);
	RenderNode->SetMesh(lisenceMeshId);

    //Reminder display






	/////////////////////////////cameraObject//////////////////
	//int cameraId = m_viewNode->CreateCamera(m_freeModeFOV, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.f, 16000.0f, &m_viewCamera);
#ifdef ALI
    int cameraId = m_AliCtrlViewNode->CreateCamera(120, CAMERA_ASPECT, 10.0f, 16000.0f, &m_controlCamera);
#else
	int cameraId = m_AliCtrlViewNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_controlCamera);
#endif
	m_AliCtrlViewNode->SetCamera(cameraId);
    //m_2DSingleViewNode->SetEnable(1);
	m_controlCamera->Set2DCamera(1);
	m_controlCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	m_controlCamera->LookAt(0.0,0.0,-0.0);
	m_controlCamera->RotateAround(0,45);

}

void SVScene::Init2DAVMNodeRTDraw(int cameraId)
{

	int meshid;
	int modelId,materialID;
	float *pData;
	unsigned short	 *pIndex;
	unsigned int BufferSize;
	IMaterial* tempcarmtl;
	Int32 tempmaterialid,modelid;
	IMesh *pStichMesh;
    INode *pStichNode,*pNode;
	char *MeshName[]={"f","b","l","r"};
    ICamera*pCamera;
	float pos[3];
    IMaterial* pMtl;
	IMesh *pMesh;
    float *pVertexData;
	XRVertexLayout  data_format;
	Int32 icount;
	int lisenceMeshId,groundId;
	float car_rect[4];
	// Interleaved vertex data

	m_2DAVMNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_2DAVMNodeStich);
	m_2DAVMNodeStich->SetRenderROI(&Stich2DReg);
	for(int i=0;i<4;i++)
	{
		AVMData::GetInstance()->m_2D_lut->GetCarRect(&car_rect[i],i);

	}


	//create material


//draw overlay

 	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

    InitOverlay(m_bev_config,m_2DAVMNodeStich,&m_overlaymesh_2d,&m_overlay_2d,&m_overlay_data_2d,calib_2D_STICH,pos);

	tempmaterialid = m_2DAVMNodeStich->CreateMaterial(Material_Rigid_Blend, &pMtl);
	//m_ground_mtl->SetDiffuseMap(m_lisenceRT->GetTextureId());
	pMtl->SetDiffuseMap(RADARALARMTEX[2]);

    lisenceMeshId = m_2DAVMNodeStich->CreateMesh(ModelType_Plane_Dynamic,2,	2,0, "ground", &pMesh);
#if 0
	m_SV2DData->GetVertexBuffer(eCarImageMesh,&pData,&BufferSize);
	meshid[i] = m_2DAVMNode->CreateMesh(ModelType_Null, 0,0,0,"CarImage", &pMesh);
	m_planeMesh->LoadVertexFromArray(pData, XR_VERTEX_LAYOUT_PTAK, BufferSize);
	m_planeMesh->SetName(Model[i]);
	m_SV2DData->GetIndexBuffer(i,&pIndex,&BufferSize);
	m_planeMesh->LoadIndexFromArray(pIndex ,2* BufferSize);
#endif

//	sv2D_param.PointTopLeft.Set(fCarView[0],fCarView[1]);
//	sv2D_param.PointBottomRight.Set(fCarView[7],fCarView[15]);


	//int lisenceMeshId = m_GroundNode->CreateMesh(ModelType_Plane,1,  1,0, "ground", &pGroundMesh);

	//int lisenceMeshId = m_GroundNode->CreateMesh(ModelType_Plane,1,  1,0, "ground", &pGroundMesh);
    groundId = m_2DAVMNodeStich->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0,0,0, 1.0, &pNode);

	pMesh->LockData(&pVertexData,&data_format,&icount);
	pVertexData[0]=car_rect[rect_left];
	pVertexData[1]=car_rect[rect_bottom];
	pVertexData[2]=0.0;
	pVertexData[8]=car_rect[rect_right];
	pVertexData[9]=car_rect[rect_bottom];
	pVertexData[10]=0.0;
	pVertexData[16]=car_rect[rect_left];
	pVertexData[17]=car_rect[rect_top];
	pVertexData[18]=0.0;
	pVertexData[24]=car_rect[rect_right];
	pVertexData[25]=car_rect[rect_top];
	pVertexData[26]=0.0;

	pMesh->UnLockData();

	pNode->SetMesh(groundId);


	tempmaterialid = m_2DAVMNodeStich->CreateMaterial(Material_Rigid_Texture, &tempcarmtl);
	tempcarmtl->SetDiffuseMap(m_lisenceRT->GetTextureId());


	lisenceMeshId = m_2DAVMNodeStich->CreateMesh(ModelType_Plane,1,  1,0, "ground", &pStichMesh);
	groundId = m_2DAVMNodeStich->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0,0,0, 1.0, &pStichNode);

	cameraId = m_2DAVMNodeStich->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &pCamera);
	pCamera->Set2DCamera(1);
	pCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
	pCamera->LookAt(0.0,0.0,-0.0);
	pCamera->RotateAround(0,45);
	m_2DAVMNodeStich->SetCamera(cameraId);

    pStichNode->SetMesh(lisenceMeshId);
	m_2DAVMNodeStich->SetCamera(cameraId);

}

void SVScene::InitRadarWaveMesh(float radius, int mesh_longi,int mesh_lati,int angle,float point_z,IMesh **pMesh,INode **pNode,float wavecolor[],char tex[],float speed)
{
#define PlaneScaleX 3000.0
#define PlaneScaleY 7000.0


	IMaterial*			temp_material;
	float  AlphaDegrade;
	// Interleaved vertex data
	GLfloat* afVertices = (GLfloat*)malloc(mesh_longi*(mesh_lati+1)*8*2*4);
	float radius_down,radius_up,theta_down,theta_up;
	// buffer file %s,line %d,",__FILE__,__LINE__);
	unsigned short* afIndices = (unsigned short*)malloc((mesh_longi)*(mesh_lati)*6*2);

	// buffer file %s,line %d,",__FILE__,__LINE__);
	int slotId=0, x, y,text;
#define	UIZ1  -5900.0f
//#define	UIZ1  -1100.0f


	for (y=0; y<mesh_longi; y++) {
        if(0==y)
        {
            radius_down = 0.01;
            radius_up=radius*((y+1)/(float)mesh_longi);
        }
        else
        {
            radius_down = radius*((y)/(float)mesh_longi);
            radius_up=radius*((y+1)/(float)mesh_longi);
        }
        if(y>mesh_longi/2)
        {
            AlphaDegrade=2.0*(1.0-y/(float)(mesh_longi-1.0));
        }
        else
        {
            AlphaDegrade=1.0;
        }
		for (x=0; x<=mesh_lati; x++) {
			theta_down= 3.14*(angle*x/mesh_lati)/180;


            afVertices[slotId*8] = radius_down*cos(theta_down);
            afVertices[slotId*8+1] = radius_down*sin(theta_down);
            afVertices[slotId*8+2] = point_z;
            afVertices[slotId*8+3] = radius_down*cos(theta_down);;
            afVertices[slotId*8+4] =  speed;
            afVertices[slotId*8+5] = AlphaDegrade;

            afVertices[slotId*8+6] = ((float)x)/(mesh_lati);
            afVertices[slotId*8+7] = 0.0;

            slotId+=1;
            afVertices[slotId*8] = radius_up*cos(theta_down);
            afVertices[slotId*8+1] = radius_up*sin(theta_down);
            afVertices[slotId*8+2] = point_z;
            afVertices[slotId*8+3] = radius_up*cos(theta_down);;
            afVertices[slotId*8+4] =  speed;
            afVertices[slotId*8+5] = AlphaDegrade;

            afVertices[slotId*8+6] = ((float)x)/(mesh_lati);
            afVertices[slotId*8+7] = 1.0;

            slotId+=1;

		}
	}

	slotId = 0;

	for (y=0; y<mesh_longi; y++) {
		for (x=0; x<mesh_lati; x++) {

			afIndices[slotId] = y*(mesh_lati+1)*2+x*2;
			afIndices[slotId+1] = y*(mesh_lati+1)*2+x*2+2;
			afIndices[slotId+2] = y*(mesh_lati+1)*2+x*2+1;
			afIndices[slotId+3] =  y*(mesh_lati+1)*2+x*2+2;
			afIndices[slotId+4] =  y*(mesh_lati+1)*2+x*2+3;
			afIndices[slotId+5] =  y*(mesh_lati+1)*2+x*2+1;

			slotId+=6;

		}
	}
	int tempmaterialid;
	tempmaterialid = m_objectNode->CreateMaterial(Material_Dynamic_Blend, &temp_material);
	temp_material->SetDiffuseMap(tex);
	temp_material->SetEnvironmentMap(BLUETEX);

	temp_material->SetAmbientColor(wavecolor[0],wavecolor[1],wavecolor[2]);

    FILE* FP = fopen(XR_RES"test.txt", "wb");
    fwrite(afVertices, mesh_longi*(mesh_lati+1)*8*2, 1, FP);
    fclose(FP);



	int meshid = m_objectNode->CreateMesh(ModelType_Null, 0,0,0, "fan", pMesh);
	(*pMesh)->LoadVertexFromArray(afVertices, XR_VERTEX_LAYOUT_PNT, mesh_longi*(mesh_lati+1)*2);
	(*pMesh)->LoadIndexFromArray(afIndices, (mesh_lati)*(mesh_longi)*6*2);

#define VIEW_Z 100


	int modelId = m_objectNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default, 100, 100, VIEW_Z, 1000.0, pNode);
	(*pNode)->SetMesh(meshid);
	(*pNode)->SetName("Ccc");


}

int SVScene::InitNode(BEV_CONFIG_T  pConfig,st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum)
{
    m_SwitchViewLogicAgain = false;
	///////////////////////////Scene Node///////////////////////////////
	m_mode = SceneMode_Free;
	m_topModeFOV = 160;
#ifdef ALI

	m_freeModeFOV =90;
#else
	m_freeModeFOV =35;
#endif
	m_camPos = CameraPosition_Free;
    m_zoomout=0;
	m_lastclickfreeflag = 1;
	float f_stich_ratio=0.3;
	IMaterial *pTempMtl;
	float f_vertical_radio = 0.5;
	float black_width = 80.0;//XrGetScreenHeight()*0.045;
	FadeLeftReg.Set(-XrGetScreenWidth()-FADE_BORDER, -FADE_BORDER, 0, XrGetScreenHeight());
	CenterReg.Set(0 + left_plane, XrGetScreenWidth(), 0 + black_plane, XrGetScreenHeight() - black_plane);
	FadeRightReg.Set(XrGetScreenWidth()+FADE_BORDER, 2*XrGetScreenWidth()+FADE_BORDER, 0, XrGetScreenHeight());
#ifdef ALI
    Stich2DReg.Set(XrGetScreenWidth()*f_stich_ratio,XrGetScreenWidth(),0,XrGetScreenHeight()* f_vertical_radio - CUT_LINE);
    RightReg.Set(0,XrGetScreenWidth(),0,XrGetScreenHeight());
    SingleViewReg.Set(0, XrGetScreenWidth(), 0, XrGetScreenHeight() * f_vertical_radio - CUT_LINE);
    UIControlReg.Set(0,XrGetScreenWidth()*(f_stich_ratio),0,XrGetScreenHeight() * f_vertical_radio-CUT_LINE);

#else

    f_stich_ratio=0.35;
    Stich2DReg.Set(0 + left_plane,left_plane + XrGetScreenWidth()*f_stich_ratio,0+black_width,XrGetScreenHeight()-black_width);
    RightReg.Set(XrGetScreenWidth()*f_stich_ratio+CUT_LINE + left_plane,XrGetScreenWidth(),0+black_width+XrGetScreenHeight()*0.0,XrGetScreenHeight()-black_width);


#endif
	RightTopFadeReg.Set(XrGetScreenWidth()*f_stich_ratio+CUT_LINE,XrGetScreenWidth(),XrGetScreenHeight(),XrGetScreenHeight()*2);
	RightBottomFadeReg.Set(XrGetScreenWidth()*f_stich_ratio+CUT_LINE,XrGetScreenWidth(),-XrGetScreenHeight(),0);
#ifdef ALIBABA_HMI
	Stich2DReg.Set(0,XrGetScreenWidth()*f_stich_ratio,0,XrGetScreenHeight()/2-CUT_LINE);
	RightReg.Set(0,XrGetScreenWidth(),XrGetScreenHeight()/2,XrGetScreenHeight());
	RightBottomSingleReg.Set(XrGetScreenWidth()*f_stich_ratio+CUT_LINE,XrGetScreenWidth(),0,XrGetScreenHeight()/2-CUT_LINE);
#endif
	m_turnlight_state = 0;

    m_veh_param.max_steering_wheel_angle = 588.0;
    m_veh_param.vehicle_axis_length = 2.700;
    m_veh_param.vehicle_length = pConfig.smc_hmi.VEHICLE_LENGTH/1000.0;
    m_veh_param.vehicle_rear_wheel_to_bumper = pConfig.smc_hmi.VEHICLE_REARWHEEL_TO_REAR_BUMPER/1000.0;
    m_veh_param.vehicle_front_wheel_to_bumper =  m_veh_param.vehicle_length- m_veh_param.vehicle_axis_length-m_veh_param.vehicle_rear_wheel_to_bumper;
    m_veh_param.vehicle_wheel_radius = 0.3;
    m_veh_param.vehicle_wheel_width = 0.2;
    m_veh_param.vehicle_width = 1.855;

	///////////////////////View Node/////////////////////////
    m_bev_config = pConfig;


	m_crossImage = new SVNodeCrossImage();
	m_crossImage->Init(&CenterReg);

	m_SV2DData = new GlSV2D;
	m_SV2DData->Init();

#ifdef EMIRROR
	RightReg.Set(0,XrGetScreenWidth(),0,XrGetScreenHeight());
    m_eMirror_node = new SVNodeEMirror();
    m_eMirror_node->Init(1,RightReg,0.1,XR_RES);
#else

	//InitAliControlViewNode(pConfig);
#ifndef ALI
    Init2DAVMNode();
#endif

	InitSceneNode(pConfig);

	InitObjectNode(pConfig);
	InitViewNode();

	//	InitSingleViewNode(m_SV2DData);

#ifndef ALI
    m_2DAVMNode->SetClear(TRUE,TRUE);
    m_2DAVMNode->SetClearColor(0.0,0.0,0.0,1.0);
	m_sceneNode->SetClear(FALSE,FALSE);
#endif
#ifdef CAR_TRANSPARENT
    Calc3DGroundTexture();

#endif
    m_pAdasHmi = new SVNodeAdasHMI;
	m_pAdasHmi->Init(pConfig,m_2DSingleViewNode,m_2DAVMNode,pAdasMdlHmiHandle,HmiMdlNum);
#if 1

	//m_pNodeSonar = new SVNodeSonar;
	//m_pNodeSonar->Init(&m_bev_config,m_2DAVMNode);
	
	
	
	AVM_Calib_2D_T result;
	
	
	result.center_x = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CX);
	result.center_y = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CY);
	result.ppmm_x= AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMX);
	result.ppmm_y= AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMY);
	
	
	
	m_APA_overlay = new GlSVOverlayAPA;
	m_APA_overlay->Init(m_2DAVMNode,XR_RES,result);
		   

	InitBevDisplayEffect();
    InitTourDisplayEffect();
	InitTourDisplaySecEffect();
	IAProperty* rotX=0, *rotY,*posZ,*rotZ=0;
	IAProperty* sldX=0, *sldY=0;

	am->CreateScrollingAnimation(&scrollX);
	am->CreateScrollingAnimation(&scrollY);
	am->CreateScrollingAnimation(&sliderX);


	scrollX->SetRange(-180, 180, 0);
	scrollY->SetRange(50, 90, 1);

	m_sceneCamera->GetCAProperty(AP_RX, &rotX);
	m_sceneCamera->GetCAProperty(AP_RY, &rotY);
	m_sceneCamera->GetCAProperty(AP_Z, &posZ);

	scrollX->BindTarget(rotX);
	scrollY->BindTarget(rotY);
	//sliderX->BindTarget(posZ);
	m_objectCamera->GetCAProperty(AP_RX, &rotX);
	m_objectCamera->GetCAProperty(AP_RY, &rotY);
	m_objectCamera->GetCAProperty(AP_Z, &posZ);
	scrollX->Bind2ndTarget(rotX, 0, 1);
	scrollY->Bind2ndTarget(rotY, 0, 1);
    //  sliderX->Bind2ndTarget(posZ,0,1);
	//m_mapplateCamera->GetCAProperty(AP_RX, &rotX);
    //m_mapplateCamera->GetCAProperty(AP_RY, &rotY);

	//scrollX->BindTarget(rotX);
	//scrollY->BindTarget(rotY);




	scrollY->DockToValue(30);

	scrollX->DockToValue(15);
	//sliderX->DockToValue(3000);


	//EnterCrossView(CameraPosition_Front);
	//m_objectNode->SetRenderROI(&FadeLeftReg);
    for (int i = 0 ;i < PRODUCT_AMOUNT;i++)
    {
        m_show_product_flag[i]=0;
    }
	m_position_active_product=0;
    // EnterTopView(3);
#endif
    m_door_state =0;
//EnterFreeView(CameraPosition_Free);
	m_luminance = new GlSVLuminance;

    // buffer file %s,line %d",__FILE__,__LINE__);
	int  temp =  m_luminance->Init();
	m_luminance->SetLuminance(&g_uiAverageIllum);
#endif
	return 0;
}

void SVScene::SetTopViewCrameraFov(Float32 fov) {
	m_topModeFOV = fov;
	float newScale = 3540.1/540.1/tan(Deg2Rad(fov
                                          )/2)*1.1;
	m_objectCamera->SetPosition(0, 0, 2000.0);
	m_objectCamera->LookAt(0.0,0,-0.0);

	m_sceneCamera->SetPosition(0, 0, 1);
	m_sceneCamera->LookAt(0, 0, -1);
	m_sceneCamera->SetFOV(fov);
    //m_sceneCamera->SetPerspective(150,4/3, 4.0f, 12000.0f);
	//m_objectCamera->SetFOV(fov);
    newScale = newScale*SCALE_CAR_MIDDLE;
	m_Car->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z*1.08);
    m_ground->SetScale(1.2,1.0,0.58);
#ifdef CAR_MODEL
    m_SUV->SetScale(SCALE_CAR_MIDDLE*1.05,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z*1.08);
    m_VAN->SetScale(SCALE_CAR_MIDDLE*1.05,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z*1.08);
    m_TRUCK->SetScale(SCALE_CAR_MIDDLE*1.05,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z*0.95);

#endif
}
void SVScene::SetProductVisible(unsigned char visibleflag) {
    if(1==visibleflag)
    {
    	m_bev[1]->SetOpacity(1);
    	m_bev[0]->SetOpacity(1);
    	m_bev[2]->SetOpacity(1);
    	m_bev[3]->SetOpacity(1);
    	m_bev[4]->SetOpacity(1);
    	m_radar[1]->SetOpacity(1);
    	m_ifv->SetOpacity(1);
    	//m_radar[2]->SetOpacity(1);
    	//m_radar[3]->SetOpacity(1);
    	//m_radar[4]->SetOpacity(1);
    	m_rsds[0]->SetOpacity(1);
    	m_rsds[1]->SetOpacity(1);
		m_radarwave[0]->SetOpacity(1);
		m_radarwave_bullet[0]->SetOpacity(1);
	    m_RadarWavePlane[3]->SetOpacity(1);

		m_RadarWavePlane[0]->SetOpacity(1);
		m_RadarWavePlane[1]->SetOpacity(1);
		m_RadarWavePlane[2]->SetOpacity(1);
		m_RadarWavePlane[4]->SetOpacity(1);
		m_ground->SetEnable(1);

	}
	else
	{
    	m_bev[1]->SetOpacity(0);
    	m_bev[0]->SetOpacity(0);
    	m_bev[2]->SetOpacity(0);
    	m_bev[3]->SetOpacity(0);
    	m_bev[4]->SetOpacity(0);
    	m_radar[1]->SetOpacity(0);
     	m_ifv->SetOpacity(0);
    	//m_radar[2]->SetOpacity(0);
    	//m_radar[3]->SetOpacity(0);
    	//m_radar[4]->SetOpacity(0);
    	m_rsds[0]->SetOpacity(0);
    	m_rsds[1]->SetOpacity(0);
		m_radarwave_bullet[0]->SetOpacity(0);
		m_radarwave[0]->SetOpacity(0);

		m_RadarWavePlane[0]->SetOpacity(0);
		m_RadarWavePlane[1]->SetOpacity(0);
		m_RadarWavePlane[2]->SetOpacity(0);
	    m_RadarWavePlane[3]->SetOpacity(0);
	    m_RadarWavePlane[4]->SetOpacity(0);
		//m_ground->SetEnable(0);


	}

}
void SVScene::SetCarEnable(Boolean flag)
{

    m_CarLight->SetEnable(flag);
    m_CarInternal->SetEnable(flag);
    m_CarDoor[0]->SetEnable(flag);
    m_Car->SetEnable(flag);
    m_CarDoor[1]->SetEnable(flag);

    m_CarDoor[2]->SetEnable(flag);
    m_CarDoor[3]->SetEnable(flag);
    m_Car_Window[4]->SetEnable(flag);
    for(int i =0;i<5;i++)
        m_Car_Window[i]->SetEnable(flag);


}
#define DELAY_TIME 5
void SVScene::ChangeCameraConfig(Int32 pos)
{
    static int pre_pos=0;
	static int change_delay = 0;
	if(pos == CameraPosition_BOSCH_Front )
	{
        if((pre_pos != pos)&&(change_delay < DELAY_TIME))
        {
            change_delay++;
        }
    	else
    	{
    	    if(change_delay >= DELAY_TIME)
    	    {
                // m_objectNode->SetEnable(0);
				m_Car->SetEnable(0);
				m_ground->SetEnable(0);
                //m_overlay->SetEnable(1);

				for(int i=0;i<4;i++)
				{
				    m_SkyNode[i]->SetEnable(0);
				}
				m_pPanaramaNode[0]->SetEnable(1);
				m_pPanaramaNode[1]->SetEnable(1);
                //m_sceneCamera->SetFOV(130);

                //	m_objectCamera->SetFOV(130);


    	    }
    		pre_pos = pos;
    	}

	}
	else
	{

        // m_objectNode->SetEnable(1);

        //m_Car->SetEnable(1);
		m_ground->SetEnable(1);
		//m_overlay->SetEnable(1);
		//m_sceneCamera->SetFOV(m_freeModeFOV);

		//m_objectCamera->SetFOV(m_freeModeFOV);
        for(int i=0;i<4;i++)
        {
            m_SkyNode[i]->SetEnable(1);
        }
        m_pPanaramaNode[0]->SetEnable(0);
        m_pPanaramaNode[1]->SetEnable(0);

		pre_pos = pos;
		change_delay=0;
	}

}
#define MAX_VIEW_TURN_ANGLE 35
void SVScene::FrontViewTurnwithSteering(Int32 pos,float steeringwheel_angle,float max_steering_wheel,float max_turn_angle)
{
    float view_turn_angle;
	static float pre_steering_wheel=0;

	IAProperty* rotX=0, *rotY,*objectRotX,*objectRotY=0;
    if((pre_steering_wheel != steeringwheel_angle)&&(pos == CameraPosition_BOSCH_Front))
    {
        view_turn_angle = steeringwheel_angle/max_steering_wheel*max_turn_angle;
		if(view_turn_angle<=MAX_VIEW_TURN_ANGLE && view_turn_angle >=(0-MAX_VIEW_TURN_ANGLE))
		{
            //if (scrollX) scrollX->DockToValue(view_turn_angle);
			m_sceneCamera->GetCAProperty(AP_RX, &rotX);
			m_sceneCamera->GetCAProperty(AP_RY, &rotY);

			m_objectCamera->GetCAProperty(AP_RX, &objectRotX);
			m_objectCamera->GetCAProperty(AP_RY, &objectRotY);

			rotX->Set(view_turn_angle);
			objectRotX->Set(view_turn_angle);



		}
    }
	pre_steering_wheel = steeringwheel_angle;

}
#define MIRROR_VIEW_FOV  60
void SVScene::EnterMirrorView(Int32 pos)
{
    //because mirror view not only change camera position but fov so
    //a sperate function is used.
    if(pos == LEFT_MIRROR_VIEW)
    {

#define AT_X -200.5
#define AT_Z -60
        //#define AT_Z -20
//	#define AT_Y 120

#define AT_Y -40
		m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
		//m_sceneCamera->LookAt(-335, 100, -230);

		m_sceneCamera->LookAt(-335, -60, -230);
		m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
		m_objectCamera->LookAt(-335, -60, -230);
		scrollX->DockToValue(0);
		scrollY->DockToValue(0);

        m_sceneCamera->SetFOV(MIRROR_VIEW_FOV);
        m_objectCamera->SetFOV(MIRROR_VIEW_FOV);


   	}
    else if(pos == RIGHT_MIRROR_VIEW)
   	{


#define AT_X 240.5
#define AT_Z -30
//#define AT_Z -20

//#define AT_Y 100
#define AT_Y -60

        m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_sceneCamera->LookAt(325, -60, -230);
        m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
        // m_objectCamera->LookAt(325, 100, -230);

        m_objectCamera->LookAt(325, -60, -230);
        scrollX->DockToValue(0);
        scrollY->DockToValue(6);

        m_sceneCamera->SetFOV(MIRROR_VIEW_FOV);
        m_objectCamera->SetFOV(MIRROR_VIEW_FOV);


   	}
    else
    {
        m_sceneCamera->SetFOV(m_freeModeFOV);
        m_objectCamera->SetFOV(m_freeModeFOV);
    }



}
#if 0
//ALI HMI
#define TURN_LIGHT_FRONT_ANGLE  25
#define TURN_LIGHT_ANGLE  25
#define SIDE_POS_WIDTH  600
#define SIDE_POS_FRONT  1500
#define SIDE_POS_REAR  1000
#endif

#define TURN_LIGHT_FRONT_ANGLE  25
#define TURN_LIGHT_ANGLE  40
#define SIDE_POS_WIDTH  400
#define SIDE_POS_FRONT  3000
#define SIDE_POS_REAR  1000

#define SIDE_POS_FRONT_HIGH_SPEED  3500

#define AT_Y  -100
void SVScene::EnterFreeView(Int32 pos)
{
	FadeInView(0);
	m_camPos = pos;
	if (pos == CameraPosition_Free) {
		//if(m_lastclickfreeflag == 0)
		//{
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
        m_zoomout = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(25);
        ResetStyleSetting();
		//}
#if 0
		else
		{
		    if(m_zoomout == 1)
		    {
        		m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        		m_sceneCamera->LookAt(0.0,0,-0.0);
        		m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        		m_objectCamera->LookAt(0.0,0,-0.0);
    			m_zoomout = 0;
		    }
			else
			{
        		m_sceneCamera->SetPosition(0, 0, CAMERA_ZOOMIN_DEFAULT_HEIGHT);
        		m_sceneCamera->LookAt(0.0,0,-0.0);
        		m_objectCamera->SetPosition(0, 0, CAMERA_ZOOMIN_DEFAULT_HEIGHT);
        		m_objectCamera->LookAt(0.0,0,-0.0);
    			m_zoomout = 1;
			}
		}
#endif
		m_lastclickfreeflag = 1;

	}
	else if (pos == CameraPosition_Back) {
#define AT_X 1900.0
#define AT_Z 1000
		m_sceneCamera->SetPosition(-AT_X, 0, AT_Z);
		m_sceneCamera->LookAt(000.0, 0, AT_Z);
		m_objectCamera->SetPosition(-AT_X, 0, AT_Z);
		m_objectCamera->LookAt(000.0, 0, AT_Z);
		m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(35);
		//text->SetText("AC-88888");
	}
	else if (pos == CameraPosition_Front) {

#define AT_X 1900.0
#define AT_Z -1000
        m_sceneCamera->SetPosition(-AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(000.0, 0, AT_Z);
        m_objectCamera->SetPosition(-AT_X, 0, AT_Z);
        m_objectCamera->LookAt(000.0, 0, AT_Z);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(35);

	}
	else if (pos == CameraPosition_Left) {
#define AT_X -SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
        //#define AT_X -800.0
        //#define AT_Z 1500
		m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
		m_sceneCamera->LookAt(AT_X, AT_Y, 0);
		m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
		m_objectCamera->LookAt(AT_X, AT_Y, 0);
        scrollX->DockToValue(0);
        scrollY->DockToValue(TURN_LIGHT_ANGLE);
		m_lastclickfreeflag = 0;
	}
	else if (pos == CameraPosition_Right) {
#if 0
#define AT_X 800.0
#define AT_Z 1500
		m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
		m_sceneCamera->LookAt(AT_X, 0, 0);
		m_objectCamera->SetPosition(AT_X, 0, AT_Z);
		m_objectCamera->LookAt(AT_X, 0, 0);
		m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(25);
#endif
#define AT_X SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(TURN_LIGHT_ANGLE);



	}
	else if (pos == CameraPosition_Left_Rear) {
#define AT_X -SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
		m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
		m_sceneCamera->LookAt(AT_X, 0, 0);
		m_objectCamera->SetPosition(AT_X, 0, AT_Z);
		m_objectCamera->LookAt(AT_X, 0, 0);
		m_lastclickfreeflag = 0;
        scrollX->DockToValue(180);
        scrollY->DockToValue(TURN_LIGHT_ANGLE);

	}
    else if (pos == CameraPosition_Right_Rear) {
#define AT_X SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(180);
        scrollY->DockToValue(TURN_LIGHT_ANGLE);

    }
    else if (pos == CameraPosition_Left_Front) {
#define AT_X -SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;
#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
        scrollX->DockToValue(0);
        scrollY->DockToValue(50);

    }
    else if (pos == CameraPosition_Right_Front) {
#define AT_X SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;
#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif

        scrollX->DockToValue(0);
        scrollY->DockToValue(50);

    }
    else if (pos == CameraPosition_Left_Rear_Light) {
#define AT_X -SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;

#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
        scrollX->DockToValue(180);
        scrollY->DockToValue(50);

    }
    else if (pos == CameraPosition_Right_Rear_Light) {
#define AT_X SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;

#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
        scrollX->DockToValue(180);
        scrollY->DockToValue(50);

    }
    else if(CameraPosition_Left_Front_Light == pos)
    {
#define AT_X SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT_HIGH_SPEED
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;

#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
        scrollX->DockToValue(180);
        scrollY->DockToValue(25);
    }
    else if(CameraPosition_Right_Front_Light == pos)
    {
#define AT_X -SIDE_POS_WIDTH
#define AT_Z SIDE_POS_FRONT_HIGH_SPEED
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, 0);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, 0);
        m_lastclickfreeflag = 0;

#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
        scrollX->DockToValue(180);
        scrollY->DockToValue(25);

    }
    else if (pos == CameraPosition_BOSCH_Front) {

#define AT_X 0.0
#define AT_Z -20
//				#define AT_Z -20
#define AT_Y -500
        m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_sceneCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_objectCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(0);

#if 0
#define AT_X 100
#define AT_Z -100
#if 1
        m_sceneCamera->SetPosition(AT_X, 0, AT_Z);
        m_sceneCamera->LookAt(AT_X, 0, AT_Z);
        m_objectCamera->SetPosition(AT_X, 0, AT_Z);
        m_objectCamera->LookAt(AT_X, 0, AT_Z);
        m_lastclickfreeflag = 0;

#else
        m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
        m_sceneCamera->LookAt(0.0,0,-0.0);
        m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
        m_objectCamera->LookAt(0.0,0,-0.0);
#endif
#endif
        //	scrollX->DockToValue(180);

        //scrollX->DockToValue(0);
        //	scrollY->DockToValue(0);

    }
    else if (pos == CameraPosition_BOSCH_Front_Top) {
#if 0
#define AT_X 0.0
#define AT_Y -560
#define AT_Z  400
#else
#define AT_X 0.0
#define AT_Z -520
#define AT_Y 800
#endif
        m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_sceneCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_objectCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(90);



    }
    else if (pos == CameraPosition_BOSCH_Rear_Top_REVERSE) {

#define AT_X 0.0
#define AT_Z 560
#define AT_Y 400
        m_sceneCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_sceneCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_objectCamera->SetPosition(AT_X, AT_Y, AT_Z);
        m_objectCamera->LookAt(0, AT_Y, 2*AT_Z);
        m_lastclickfreeflag = 0;
        scrollX->DockToValue(0);
        scrollY->DockToValue(90);


    }


	m_mode = SceneMode_Free;
	m_sceneCamera->SetFOV(m_freeModeFOV);

	m_objectCamera->SetFOV(m_freeModeFOV);
	//m_objectCamera->LookAt(0.0,0,-0.0);
	//m_objectCamera->SetFOV(m_freeModeFOV);
	m_Car->SetOpacity(1);
#ifdef CAR_MODEL
	m_SUV->SetOpacity(1);
	m_VAN->SetOpacity(1);
	m_TRUCK->SetOpacity(1);
#endif
	m_ground->SetOpacity(1);


	//m_Car->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE);
	//m_SUV->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z);
	//m_VAN->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z);
	//m_TRUCK->SetScale(SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE,SCALE_CAR_MIDDLE*SCALE_CAR_MIDDLE_SPECIAL_Z);

    //m_ground->SetScale(1.0,1.0,1.0);
    // SetProductVisible(1);


}

void SVScene::EnterTopView(Int32 pos)
{
	FadeInView(0);
	if(0!= bevdisplay[0])
	{
	    bevdisplay[0]->Stop();
        bevdisplay[1]->Stop();
	}
	bevSecTour[0]->Stop();
    bevSecTour[1]->Stop();
	m_lastclickfreeflag = 0;
	m_zoomout=0;
    m_mode = SceneMode_Top;
    scrollX->DockToValue(0);
	scrollY->DockToValue(90);
	m_sceneCamera->SetPosition(0, 0, CAMERA_ZOOMIN_DEFAULT_HEIGHT-3000);
	m_sceneCamera->LookAt(0.0,0,-0.0);
	m_objectCamera->SetPosition(0, 0, CAMERA_ZOOMIN_DEFAULT_HEIGHT-3100);
	m_objectCamera->LookAt(0.0,0,-0.0);
	//m_Car->SetEnable(1);
	//m_Car->SetOpacity(1);
	m_sceneCamera->SetFOV(m_freeModeFOV);
	m_Car->SetOpacity(1);
	SetCarEnable(1);
#ifdef CAR_MODEL
	m_SUV->SetOpacity(1);
	m_VAN->SetOpacity(1);
	m_TRUCK->SetOpacity(1);
#endif
	m_ground->SetOpacity(1);


}

void SVScene::EnterCrossView(Int32 pos)
{
	FadeInView(1);

    bevdisplay[0]->Stop();
    bevdisplay[1]->Stop();
	m_lastclickfreeflag = 0;

	m_zoomout=0;

	m_mode = SceneMode_Cross;
	int i=0;
	switch (pos) {
        case CameraPosition_Front:
            i=2;

            cvdelegate->SetChannel(i);
            break;
        case CameraPosition_Back:
            i=3;

            cvdelegate->SetChannel(i);
            break;
        case CameraPosition_Left:
            i=1;


            cvdelegate->SetChannel(i);
            break;
        case CameraPosition_Right:
            i=0;

            break;
        default:
            i=0;

            break;
	}

	cvdelegate->SetChannel(i);

}
void SVScene::UpdateLisceseText(String textupdate,unsigned int ChineseIndex)
{
	text->SetText(textupdate);
	if(ChineseIndex==NONE_CHINESE_WORD)
	{
        // Chinesetext->SetFontSize(0);
	}
	else
	{
	    // Chinesetext->SetFontSize(15);
	    Chinesetext->SetText(ChineseIndex);
	}

}

void SVScene::EnterPanorama(Int32 pos)
{
    IMaterial *pMaterilTemp;
	m_mode = SceneMode_Pano;

    m_lastclickfreeflag = 0;

    m_zoomout=0;
	int i=0;
#if 0
#if 0
	m_SV2Dplane[eSingleViewMesh]->GetMaterial(&pMaterilTemp);
	switch (pos) {
        case CameraPosition_Front:

            pMaterilTemp->SetDiffuseMap(ARROUNDVIEWFRONT);
            i=0;
            break;
        case CameraPosition_Back:

            pMaterilTemp->SetDiffuseMap(ARROUNDVIEWREAR);
            i=2;
            break;
        case CameraPosition_Left:

            pMaterilTemp->SetDiffuseMap(ARROUNDVIEWLEFT);
            i=3;
            break;
        case CameraPosition_Right:

            pMaterilTemp->SetDiffuseMap(ARROUNDVIEWRIGHT);
            i=1;
            break;
	}
#endif
	FadeInView(2);
#else
	scrollX->DockToValue(i*90);

	m_sceneCamera->SetPosition(0, -400, 0);
	m_sceneCamera->LookAt(0.0,-400,-0.1);
	m_sceneCamera->SetFOV(90);
	scrollX->DockToValue(i*90);
	m_objectCamera->SetPosition(0, -400, 0);
	m_objectCamera->LookAt(0.0,-400,-0.1);
	m_objectCamera->SetFOV(90);
	scrollY->DockToValue(0);

	FadeInView(0);
#endif
	m_Car->SetOpacity(0);
	SetCarEnable(0);
#ifdef CAR_MODEL
	m_VAN->SetOpacity(0);
	m_TRUCK->SetOpacity(0);
	m_SUV->SetOpacity(0);
#endif
	//SetProductVisible(0);

	//m_ground->SetOpacity(0);
	//m_Car->SetScale(0,0,0);
}

void SVScene::FadeInView(unsigned char  flag)
{
    static unsigned char pre_flag;
	if(flag != pre_flag)
	{
    	if (flag == 1) {

            m_sceneNode->SetRenderROI(&FadeLeftReg);
            m_objectNode->SetRenderROI(&FadeLeftReg);
            m_viewNode->SetRenderROI(&CenterReg);
            //m_2DAVMNode->SetRenderROI(&FadeLeftReg);

    	}
    	else if (flag == 2) {
    		m_sceneNode->SetRenderROI(&FadeLeftReg);
    		m_objectNode->SetRenderROI(&FadeLeftReg);
    		m_viewNode->SetRenderROI(&FadeLeftReg);
    		//m_2DAVMNode->SetRenderROI(&CenterReg);
    	}
    	else {
    		m_sceneNode->SetRenderROI(&CenterReg);
    		m_objectNode->SetRenderROI(&CenterReg);
    		m_viewNode->SetRenderROI(&FadeRightReg);
    		//m_2DAVMNode->SetRenderROI(&FadeRightReg);

    	}
	}
	pre_flag = flag;
}
void SVScene::SetSingleViewCamPos(unsigned char ucDir)
{

    for(int i = eFrontSingle;i<=eRightSingle;i++)
    {
        if(i==ucDir+eFrontSingle)
        {

			m_SV2Dplane[i]->SetEnable(1);
        }
		else
		{
			m_SV2Dplane[i]->SetEnable(0);

		}
    }

}

void SVScene::SwitchViewLogic(unsigned char  Input)
{
#ifndef ALI
    if(Input <= RIGHT_SINGLE_VIEW)
    {
#if 0
        m_sceneNode->SetRenderROI(&RightTopFadeReg);
        m_objectNode->SetRenderROI(&RightTopFadeReg);
        m_2DSingleViewNode->SetRenderROI(&RightBottomFadeReg);
#endif
        if(!m_SwitchViewLogicAgain)
        {
            m_SwitchViewLogicAgain = true;
            m_2DSingleViewNode->SetRenderROI(&RightReg);
        }
		//#ifdef ALI
	    //	m_sceneNode->SetEnable(1);
		//#else
        m_2DAVMNode->SetEnable(1);
        m_stich_node->SetEnable(1);
		m_pAdasHmi->SetEnable(0);
    	m_crossImage->SetEnable(0);
        m_sceneNode->SetEnable(0);
		//#endif
		m_objectNode->SetEnable(0);
        m_2DSingleViewNode->SetEnable(1);
		SetSingleViewCamPos(Input);
		//m_2DAVMNode->SetClear(TRUE,TRUE);
        int offset = 0;
        switch (Input)
        {
            case FRONT_SINGLE_VIEW:
                // m_SVSingleMtl->SetDiffuseMap(ARROUNDVIEWFRONT);
                //m_SV2Dplane[eFrontSingle]->SetEnable(0);
                sv2Ddelegate->SetChannel(front_camera_index);
                offset = 0;
                m_overlay_2d_single->SetEnable(1);
                break;
            case REAR_SINGLE_VIEW:
                //m_SVSingleMtl->SetDiffuseMap(ARROUNDVIEWREAR);
                sv2Ddelegate->SetChannel(rear_camera_index);
                offset = 1;
                m_overlay_2d_single->SetEnable(1);
                break;
            case LEFT_SINGLE_VIEW:
                // m_SVSingleMtl->SetDiffuseMap(ARROUNDVIEWLEFT);
                sv2Ddelegate->SetChannel(left_camera_index);
                m_overlay_2d_single->SetEnable(0);
                offset = 2;
                break;
            case RIGHT_SINGLE_VIEW:
                // m_SVSingleMtl->SetDiffuseMap(ARROUNDVIEWRIGHT);
                sv2Ddelegate->SetChannel(right_camera_index);
                m_overlay_2d_single->SetEnable(0);
                offset = 3;
                break;
        }
        XRVertexLayout data_format;
        float* pVertexData = NULL;
        Int32 iCount = 0;
        m_singleviewMesh[offset]->LockData(&pVertexData, &data_format, &iCount);
        memcpy(pVertexData, fVerticesSnapshot[offset], 28 * sizeof(GLfloat));
        m_singleviewMesh[offset]->UnLockData();
    }
	else if(Input == CROSS_IMAGE_VIEW)
	{
	  	m_sceneNode->SetEnable(0);
		m_objectNode->SetEnable(0);
        m_2DSingleViewNode->SetEnable(0);
	    m_2DAVMNode->SetEnable(0);

		m_pAdasHmi->SetEnable(0);
    	m_crossImage->SetEnable(1);
	}
	else
	{
#if 0
    	m_sceneNode->SetRenderROI(&RightReg);
    	m_objectNode->SetRenderROI(&RightReg);
    	m_2DSingleViewNode->SetRenderROI(&RightBottomFadeReg);
#endif
        
        m_2DAVMNode->SetEnable(1);

		m_pAdasHmi->SetEnable(0);
    	m_crossImage->SetEnable(0);
	    m_sceneNode->SetEnable(1);

		m_objectNode->SetEnable(1);
#ifdef ALIBABA_HMI
        m_2DSingleViewNode->SetEnable(0);

#else
        m_2DSingleViewNode->SetEnable(0);
#endif
#endif
#ifdef ALI
        SetCarEnable(1);
#else
		m_Car->SetEnable(1);
#endif
		//#ifdef ALI
       	//m_2DSingleViewNode->SetEnable(1);
		//#else
		//	m_2DSingleViewNode->SetEnable(0);
		//#endif
		switch (Input)
        {
            case FRONT_3D_VIEW:
			case TOUR_VIEW:
				m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
				m_sceneCamera->LookAt(0.0,-0,-0.0);
				m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
				m_objectCamera->LookAt(0.0,-0.0,-0.0);
				m_zoomout = 0;
				scrollX->DockToValue(0);
				scrollY->DockToValue(25);
				m_camPos = CameraPosition_Free;
                break;
            case REAR_3D_VIEW:
				m_sceneCamera->SetPosition(0, 0, SCENE_CAMERA_DEFAULT_HEIGHT);
				m_sceneCamera->LookAt(0.0,0,-0.0);
				m_objectCamera->SetPosition(0, 0, OBJ_CAMERA_DEFAULT_HEIGHT);
				m_objectCamera->LookAt(0.0,0,-0.0);
				m_zoomout = 0;
				scrollX->DockToValue(180);
				scrollY->DockToValue(25);

				m_camPos = CameraPosition_Free;
                break;
            case LEFT_FRONT_3D_VIEW:
                EnterFreeView(CameraPosition_Left);
                break;
            case RIGHT_FRONT_3D_VIEW:
	            EnterFreeView(CameraPosition_Right);
                break;
            case RIGHT_REAR_3D_VIEW:
				EnterFreeView(CameraPosition_Left_Rear);
                break;
            case LEFT_REAR_3D_VIEW:
	            EnterFreeView(CameraPosition_Right_Rear);
                break;
            case LEFT_TURN_SIGNAL_3D_VIEW:
                EnterFreeView(CameraPosition_Left_Front);
                break;
            case RIGHT_TURN_SIGNAL_3D_VIEW:
	            EnterFreeView(CameraPosition_Right_Front);
                break;
            case LEFT_REAR_TURN_SIGNAL_3D_VIEW:
				EnterFreeView(CameraPosition_Left_Rear_Light);
                break;
            case RIGHT_REAR_TURN_SIGNAL_3D_VIEW:
	            EnterFreeView(CameraPosition_Right_Rear_Light);
                break;
			case LEFT_HIGHT_SPEED_TURN_3D_VIEW:

				EnterFreeView(CameraPosition_Left_Front_Light);
                break;
			case RIGHT_HIGHT_SPEED_TURN_3D_VIEW:

				EnterFreeView(CameraPosition_Right_Front_Light);
                break;

			case BOSH_FRONT_VIEW:
	            EnterFreeView(CameraPosition_BOSCH_Front);
                break;
			case BOSH_FRONT_VIEW_TOP:
	            EnterFreeView(CameraPosition_BOSCH_Front_Top);
                break;
			case BOSH_REAR_VIEW_TOP:
	            EnterFreeView(CameraPosition_BOSCH_Rear_Top_REVERSE);
                break;
			default:
				m_camPos = CameraPosition_Free;
                break;

        }
		if(Input == REAR_3D_VIEW||Input == LEFT_HIGHT_SPEED_TURN_3D_VIEW||Input == RIGHT_HIGHT_SPEED_TURN_3D_VIEW
           |RIGHT_REAR_3D_VIEW == Input|LEFT_REAR_3D_VIEW == Input)
		{
		    svdelegate->SetMirrorFlipEnable(1);
		}
		else
		{
            svdelegate->SetMirrorFlipEnable(0);
		}

    	//EnterMirrorView(Input);

#ifndef ALI
	}
#endif

	//LightUpCtrlIndicate(Input);
	m_view_control = Input;

}
void SVScene::LightUpCtrlIndicate(unsigned char view_index)
{
	static unsigned char pre_view_index=0;
	if(pre_view_index != view_index)
	{
        switch(view_index)
        {

            case FRONT_SINGLE_VIEW:
            case FRONT_3D_VIEW:
            case TOUR_VIEW:
            case BOSH_FRONT_VIEW:
            case BOSH_FRONT_VIEW_TOP:
                m_ControlMtl->SetDiffuseMap(CONTROLPANELFRONT);
                break;
            case REAR_SINGLE_VIEW:
            case REAR_3D_VIEW:
            case BOSH_REAR_VIEW_TOP:
            case LEFT_MIRROR_VIEW:
            case RIGHT_MIRROR_VIEW:
                m_ControlMtl->SetDiffuseMap(CONTROLPANELREAR);
                break;
            case LEFT_SINGLE_VIEW:
            case LEFT_FRONT_3D_VIEW:
            case LEFT_REAR_3D_VIEW:
            case LEFT_TURN_SIGNAL_3D_VIEW:
            case LEFT_REAR_TURN_SIGNAL_3D_VIEW:
            case LEFT_HIGHT_SPEED_TURN_3D_VIEW:
                m_ControlMtl->SetDiffuseMap(CONTROLPANELLEFT);
                break;
            case RIGHT_SINGLE_VIEW:
            case RIGHT_FRONT_3D_VIEW:
            case RIGHT_REAR_3D_VIEW:
            case RIGHT_TURN_SIGNAL_3D_VIEW:
            case RIGHT_REAR_TURN_SIGNAL_3D_VIEW:
            case RIGHT_HIGHT_SPEED_TURN_3D_VIEW:
                m_ControlMtl->SetDiffuseMap(CONTROLPANELRIGHT);
                break;


        }
	}
    pre_view_index = view_index;

}
void SVScene::SwitchCameraPosition(Int32 pos)
{
	if(bevdisplay[0] != 0)
	{
        bevdisplay[0]->Stop();
        bevdisplay[1]->Stop();
        bevSecTour[0]->Stop();
        bevSecTour[1]->Stop();
	}
	switch (m_mode) {
        case SceneMode_Free:
            EnterFreeView(pos);


            break;
        case SceneMode_Top:
            EnterTopView(pos);


            break;
        case SceneMode_Cross:
            EnterCrossView(pos);


            break;
        case SceneMode_Pano:
            EnterPanorama(pos);

            break;
	}
}
#define ZOOM_MIN 1000
#define ZOOM_MAX 9000
void SVScene::ZoomFunction(Int32 pos)
{
	IAProperty* rotX=0, *rotY,*posZ=0;
    float temp=0;
	static int si_turn_flag = 0;
	static int si_wheel_product = 0;
	static int si_car_model = 0;
	static int si_car_color = 0;
    static unsigned char switch_view=0;

#define ZOOM_STEP 500
    if(SceneMode_Free == m_mode)
    {
        if(ZOOM_IN == pos)
        {
            m_sceneCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            // if(temp > ZOOM_MIN)
            // {
            posZ->Set(temp-ZOOM_STEP);
            m_objectCamera->SetPosition(0,0,temp-ZOOM_STEP);
            // }
            // m_sceneCamera->SetPosition(0.0,0.0,temp)
        }
        else if(ZOOM_OUT == pos)
        {
            m_sceneCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            if(temp < ZOOM_MAX)
            {
                posZ->Set(temp+ZOOM_STEP);
                m_objectCamera->SetPosition(0,0,temp+ZOOM_STEP);
            }
        }
        else if(ZOOM_TURN == pos)
        {
#if 0
            if(si_turn_flag == 0)
            {
                si_turn_flag = 1;
            }
            else
            {
                si_turn_flag = 0;
            }
            if(si_turn_flag == 1)
            {
                bevSecTour[0]->Start();
                bevSecTour[1]->Start();
                m_pre_view_control = m_view_control;

                SwitchViewLogic(TOUR_VIEW);

            }
            else
            {
                bevSecTour[0]->Stop();
                bevSecTour[1]->Stop();
                SwitchViewLogic(m_pre_view_control);

            }
#endif
            if(bevSecTour[0]->GetActiveState()==0)
            {
                bevSecTour[0]->Start();
                bevSecTour[1]->Start();
                m_pre_view_control = m_view_control;

                SwitchViewLogic(TOUR_VIEW);
            }


        }
        else if(ZOOM_TYRE == pos)
        {
            if (si_wheel_product == 0)
                si_wheel_product = 1;
            else
                si_wheel_product = 0;
            if(si_wheel_product == 1)
            {

                wheelRot->Start();

            }
            else
            {
                wheelRot->Stop();
                for (int i=0;i<4;i++) {
                    m_wheel[i]->RotateX(0);
                    m_wheel[i]->RotateY(0);
                }

            }

        }
        else if(ZOOM_MODEL == pos)
        {
            si_car_model++;
            if(si_car_model == 4)
            {
                si_car_model=0;
            }


            SwitchCarModel(si_car_model);

        }
        else if(ZOOM_COLOR == pos)
        {

            si_car_color++;
            if(si_car_color == 4)
            {
                si_car_color=0;
            }


            SwitchCarColor(si_car_color);


        }


    }
    else if(SceneMode_Top == m_mode)
    {
        if(ZOOM_IN == pos)
		{
            m_sceneCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            posZ->Set(temp+ZOOM_STEP);
            m_objectCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            posZ->Set(temp-ZOOM_STEP);
            // m_objectCamera->SetPosition(0,0,temp-ZOOM_STEP);
            // m_sceneCamera->SetPosition(0.0,0.0,temp)
		}
		else if(ZOOM_OUT == pos)
		{
            m_sceneCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            posZ->Set(temp-ZOOM_STEP);
            m_objectCamera->GetCAProperty(AP_Z,&posZ);
            temp=posZ->Get();
            posZ->Set(temp+ZOOM_STEP);
		}


    }


}

#define DOOR_ROATE_ANGLE 45
void SVScene::DoorAction(Int32 Pos)
{

	float rotate_angle;
    unsigned char ucSwitch;

	if(1==((m_door_state>>Pos)&0x01))
	{
	    ucSwitch=~(1<<Pos);
	    rotate_angle = 40-(Pos%2)*80;
	    m_CarDoor[Pos]->RotateDY(-rotate_angle);
		m_Car_Window[Pos]->RotateDY(-rotate_angle);
		m_door_state&=ucSwitch;
	}
	else
	{
	    //ucSwitch=~(1<<Pos);
	    rotate_angle = 40-(Pos%2)*80;
	    m_CarDoor[Pos]->RotateDY(rotate_angle);

		m_Car_Window[Pos]->RotateDY(rotate_angle);
		m_door_state|=(1<<Pos);
	}



}
void SVScene::TurnLightAction(Int32 Pos)
{

	float rotate_angle;
    unsigned char ucSwitch;
	static unsigned int flash_cnt=0;

	if(1==((m_turnlight_state>>Pos)&0x01))
	{
	    ucSwitch=~(1<<Pos);


		m_turnlight_state&=ucSwitch;
	}
	else
	{
	    //ucSwitch=~(1<<Pos);
		//m_carlightmtl->SetAmbientColor(1.0,1.0,1.0,0.0);
		m_turnlight_state|=(1<<Pos);
	}



}

void SVScene::ShowProduct(Int32 pos)
{
    if(pos >= PRODUCT_AMOUNT)
    {
        return;
    }




	unsigned char adjustactiveflag;
    for(int i =0;i< PRODUCT_AMOUNT;i++)
    {
        if(i!=pos)
        {
            m_show_product_flag[i]=0;
        }
    }
    if(m_show_product_flag[pos] ==0)
    {
        m_show_product_flag[pos] = 1;
    }
	else
	{
        m_show_product_flag[pos]=0;
	}

    if(m_show_product_flag[PRODUCT_IFV] == 1)
    {
        m_ifv->SetEnable(1);
		//m_bev[1]->SetEnable(1);
		bulletrun->Start();
		//m_radarwave[0]->SetEnable(1);
		//m_radarwave_bullet[0]->SetEnable(1);
	    m_RadarWavePlane[4]->SetEnable(1);
		m_position_active_product=m_ifv;
    }
	else
	{
	    m_ifv->SetEnable(0);
		m_radarwave[0]->SetEnable(0);

	    m_RadarWavePlane[4]->SetEnable(0);
		m_radarwave_bullet[0]->SetEnable(0);
		bulletrun->Stop();


	}


	if(m_show_product_flag[PRODUCT_ESR] == 1)
	{
		//m_radar[4]->SetEnable(1);
		m_radar[1]->SetEnable(1);
		//m_radar[2]->SetEnable(1);
		//m_radar[3]->SetEnable(1);
		m_RadarWavePlane[0]->SetEnable(1);
		m_position_active_product=m_radar[1];
	    m_RadarWavePlane[3]->SetEnable(1);
		//bevSecTour[0]->Start();
		//bevSecTour[1]->Start();


	}
	else
	{
		//m_radar[4]->SetEnable(0);
		m_radar[1]->SetEnable(0);
		//m_radar[2]->SetEnable(0);
		//m_radar[3]->SetEnable(0);
		m_RadarWavePlane[0]->SetEnable(0);
	    m_RadarWavePlane[3]->SetEnable(0);

		//bevSecTour[0]->Stop();
		//bevSecTour[1]->Stop();

	}

 	if(m_show_product_flag[PRODUCT_RSDS] == 1)
	{
		m_rsds[0]->SetEnable(1);
		m_rsds[1]->SetEnable(1);

		m_RadarWavePlane[1]->SetEnable(1);

		m_RadarWavePlane[2]->SetEnable(1);
		m_position_active_product=m_rsds[0];

	}
	else
	{
		m_rsds[0]->SetEnable(0);
		m_rsds[1]->SetEnable(0);

		m_RadarWavePlane[1]->SetEnable(0);

		m_RadarWavePlane[2]->SetEnable(0);

	}
    if(SceneMode_Free==m_mode)
    {
     	if(m_show_product_flag[PRODUCT_BEV] == 1)
    	{
    		m_bev[3]->SetEnable(1);
    		m_bev[2]->SetEnable(1);
    		m_bev[4]->SetEnable(1);
    		m_bev[1]->SetEnable(1);
    		m_bev[0]->SetEnable(0);
    		bevdisplay[0]->Start();
    		bevdisplay[1]->Start();

    		m_position_active_product=m_bev[1];


    	}
    	else
    	{
    		m_bev[3]->SetEnable(0);
    		bevdisplay[0]->Stop();
    		bevdisplay[1]->Stop();

    		m_bev[2]->SetEnable(0);
    		m_bev[4]->SetEnable(0);
    		m_bev[1]->SetEnable(0);
    		m_bev[0]->SetEnable(0);
    		//m_sceneCamera->SetPosition(0,0,SCENE_CAMERA_DEFAULT_HEIGHT);
    		//m_sceneCamera->LookAt(0,0,0);
    		//m_objectCamera->SetPosition(0,0,OBJ_CAMERA_DEFAULT_HEIGHT);
    		//m_objectCamera->LookAt(0,0,0);
    	}

		if(m_show_product_flag[PRODUCT_TOUR] == 1)
    	{
			bevSecTour[0]->Start();
			bevSecTour[1]->Start();

    	}
    	else
    	{
			bevSecTour[0]->Stop();
			bevSecTour[1]->Stop();
    	}
    }

	if(m_show_product_flag[PRODUCT_WHEEL] == 1)
	{

		wheelRot->Start();

	}
	else
	{
		wheelRot->Stop();
		for (int i=0;i<14;i++) {
			m_wheel[i]->RotateX(0);
			m_wheel[i]->RotateY(0);
		}

	}
    for(int i=0;i<PRODUCT_AMOUNT;i++)
    {
        adjustactiveflag|=m_show_product_flag[i];
    }
	if(0== adjustactiveflag)
	{
	    m_position_active_product=0;
	}

}
void SVScene::AdjustProductPosition(Int32 pos)
{
    float x,y,z,rotx,roty,rotz;
	static float temp=1;
    if(m_position_active_product==0)
		return;
	x=m_position_active_product->GetX();
    y=m_position_active_product->GetY();
    z=m_position_active_product->GetZ();
    switch(pos)
    {
        case POS_X_POS:
            m_position_active_product->SetDX(20);
            break;
        case POS_Y_POS:
            m_position_active_product->SetDY(20);
            break;
        case POS_Z_POS:
            m_position_active_product->SetDZ(20);
            break;
        case POS_X_NEG:
            m_position_active_product->SetDX(-20);
            break;
        case POS_Y_NEG:
            m_position_active_product->SetDY(-20);
            break;
        case POS_Z_NEG:
            m_position_active_product->SetDZ(-20);
            break;
		case POS_ROTX_POS:
            m_position_active_product->RotateDX(20);
            break;
        case POS_ROTY_POS:
            m_position_active_product->RotateDY(20);
            break;
        case POS_ROTZ_POS:
            m_position_active_product->RotateDZ(0.1);
            break;
        case POS_ROTX_NEG:
            m_position_active_product->RotateDX(-20);
            break;
        case POS_ROTY_NEG:
            m_position_active_product->RotateDY(-20);
            break;
        case POS_ROTZ_NEG:
            m_position_active_product->RotateDZ(-0.1);
            break;
    }

}

extern float g_MaterialColor[3];

void SVScene::SwitchCarColor(Int32 pos)
{

	switch (pos) {
        case RED_CAR:
            g_MaterialColor[0]=0.8;
            g_MaterialColor[1]=0.0;
            g_MaterialColor[2]=0.0;
            break;
        case GREEN_CAR:
            g_MaterialColor[0]=0.0;
            g_MaterialColor[1]=0.0;
            g_MaterialColor[2]=0.0;
            break;
        case WHITE_CAR:
            g_MaterialColor[0]=1.0;
            g_MaterialColor[1]=1.0;
            g_MaterialColor[2]=1.0;
            break;
        case GRAY_CAR:
            g_MaterialColor[0]=0.51;
            g_MaterialColor[1]=0.51;
            g_MaterialColor[2]=0.51;
            break;
		case PINK_CAR:
			g_MaterialColor[0]=0.9;
			g_MaterialColor[1]=0.78;
			g_MaterialColor[2]=0.12;

            break;
	}
}
void SVScene::ResetStyleSetting(void)
{


    SwitchCarColor(WHITE_CAR);

    SwitchCarModel(CAR_CAR);
	//UpdateLisceseText("DELPHI",NONE_CHINESE_WORD);

}
void SVScene::SwitchCarModel(Int32 pos)
{
#ifdef CAR_MODEL
	switch (pos) {
        case CAR_CAR:
            m_SUV->SetEnable(0);
            m_Car->SetEnable(1);
            m_VAN->SetEnable(0);
            m_TRUCK->SetEnable(0);
            SetCarEnable(1);

            break;
        case CAR_SUV:
            m_SUV->SetEnable(1);
            m_Car->SetEnable(0);
            m_VAN->SetEnable(0);
            m_TRUCK->SetEnable(0);

            SetCarEnable(0);
            break;
        case CAR_VAN:
            m_SUV->SetEnable(0);
            m_Car->SetEnable(0);
            m_VAN->SetEnable(1);
            m_TRUCK->SetEnable(0);

            SetCarEnable(0);
            break;
        case CAR_TRUCK:
            m_SUV->SetEnable(0);
            m_Car->SetEnable(0);
            m_VAN->SetEnable(0);
            m_TRUCK->SetEnable(1);

            SetCarEnable(0);
            break;
	}
#endif
}

#define HIGH_SPEED_GATE 30
#define SINGLE_VIEW_TO_3D_GATE  15
#define STEERING_WHEEL_GATE    90
#define STEERING_WHEEL_STILL_GATE    20
#define STEERING_WHEEL_TIME_GATE 150
#define CAMERA_DIR_FRONT  0
#define CAMERA_DIR_REAR  1
#define CAMERA_DIR_LEFT  2
#define CAMERA_DIR_RIGHT 3
#define CAMERA_DIR_REAR_LEFT  4
#define CAMERA_DIR_REAR_RIGHT 5

#define CAMERA_DIR_HIGH_SPEED_LEFT 10
#define CAMERA_DIR_HIGH_SPEED_RIGHT 11
void GenerateTextureIndex(float *fTextureIndex)
{
    static int cnt=0;
    cnt++;
	if(cnt ==600)
	{
        cnt=0;
	}

#if 0
    fTextureIndex[0]=0.0+cnt*0.01;
	fTextureIndex[1]=0.0+cnt*0.05;
	fTextureIndex[2]=0.4+cnt*0.01;
	fTextureIndex[3]=0.0+cnt*0.05;
	fTextureIndex[4]=0.0+cnt*0.01;
	fTextureIndex[5]=0.5+cnt*0.05;
	fTextureIndex[6]=0.4+cnt*0.01;
	fTextureIndex[7]=0.5+cnt*0.05;
#else
	fTextureIndex[0]=0.0;
	fTextureIndex[1]=0.0;
	fTextureIndex[2]=0.4;
	fTextureIndex[3]=0.5;
	fTextureIndex[4]=0.0;
	fTextureIndex[5]=0.5;
	fTextureIndex[6]=0.4;
	fTextureIndex[7]=1.0;
#endif

}
void SVScene::Calc3DGroundTexture()
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
    m_stich_node->CalcShadowTextureCoord(car_rect_image,car_rect_adjust,texture);
	m_ground->GetMesh(&groundmesh);
	m_groundmesh->LockData(&pVertexData,&data_format,&icount);
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



}

int SVScene::SwitchCrossView()
{
    m_2DAVMNode->SetEnable(0);
    m_pAdasHmi->SetEnable(0);
    m_sceneNode ->SetEnable(0);
    m_objectNode->SetEnable(0);
    m_2DSingleViewNode->SetEnable(0);
    m_stich_node->SetEnable(0);
    m_viewNode->SetEnable(0);
    m_crossImage->SetEnable(1);
    m_overlay_2d_single->SetEnable(0);
    for(int index = 0; index < 8; index++)
        m_RadarAlarm_Node_single[index]->SetEnable(0);


    XRVertexLayout  data_format;
    float* pVertexData = NULL;
    Int32 iCount = 0;
    //singleview cross 来回切换导致的lock_data读取的数据不是avm视图数据
    for(int index = 0; index < 4; index++)
    {
        m_singleviewMesh[index]->LockData(&pVertexData, &data_format, &iCount);
        memcpy(pVertexData, fVerticesSnapshot[index], 28 * sizeof(GLfloat));
        m_singleviewMesh[index]->UnLockData();
    }

    Region roi(XrGetScreenWidth()/4, 3 * XrGetScreenWidth()/4,
               XrGetScreenHeight()/4, 3 * XrGetScreenHeight()/4);
    m_2DSingleViewNode->SetRenderROI(&roi);
    m_last_view = 0x02; //保证切换到SVScene::Update时 ， 一定执行更新
    m_SwitchViewLogicAgain = false;
}

//dota2_black: 单视图全屏回放模式
static GLfloat fVerticesOriginFront[]={
	-1,  1, -1.0, 0, 0, 0,0.0,
     1,  1, -1.0, 1.0, 0, 0,0.0,
    -1, -1, -1.000000, 0, 1.0, 1.0,0.0,
     1, -1, -1.000000, 1.0, 1.0,1.0,0.0,
};

static GLfloat fVerticesOriginRear[] = {
	-1,  1, -1.000000, 0, 0, 0,0.0,
     1,  1, -1.000000, 1.0, 0,1.0,0.0,
    -1, -1, -1.000000, 0, 1.0,1.0,0.0,
     1, -1, -1.000000, 1.0, 1.0,1.0,0.0,
};

static GLfloat fVerticesOriginLeft[] = {
    -1,  1, -1.000000, 0, 0,   0,0.0,
     1,  1, -1.000000, 1.0, 0,   0,0.0,
    -1, -1, -1.000000, 0, 1.0, 1.0,0.0,
     1, -1, -1.000000, 1.0, 1.0, 1.0,0.0,
};

static GLfloat fVerticesOriginRight[] = {
    -1,  1, -1.000000, 0,   0,1.0,0.0,
     1,  1, -1.000000, 1.0, 0,1.0,0.0,
    -1, -1, -1.000000, 0,  1.0,1.0,0.0,
     1, -1, -1.000000, 1.0, 1.0,1.0,0.0,
};

int SVScene::SwitchSingleView(int view_control_flag)
{
    m_SwitchViewLogicAgain = false;
    if(m_last_view == view_control_flag)
    {
        return 0;
    }
    //第一步: 初始化所有node
    m_2DAVMNode->SetEnable(0);
    m_pAdasHmi->SetEnable(0);
    m_sceneNode->SetEnable(0);
    m_objectNode->SetEnable(0);
    m_2DSingleViewNode->SetEnable(1);
    m_stich_node->SetEnable(0);
    m_viewNode->SetEnable(0);
    m_crossImage->SetEnable(0);
    m_overlay_2d_single->SetEnable(0);

    for(int index = 0; index < 8; index++)
        m_RadarAlarm_Node_single[index]->SetEnable(0);

    m_last_view = view_control_flag; //保证切换到SVScene::Update时 ， 一定执行更新
    Region fullscreenROI(0 + left_plane, XrGetScreenWidth(), 0 + black_plane, XrGetScreenHeight() - black_plane);

    //第二步: 更改 fVerticesSingleView , 修改纹理mesh区域(不进行处理)
    Int32 offset = 0; float* viewmatrix = NULL;
    switch(view_control_flag)
    {
        case 0xf0:
            sv2Ddelegate->SetChannel(front_camera_index);
            SetSingleViewCamPos(FRONT_SINGLE_VIEW);
            m_2DSingleViewNode->SetRenderROI(&fullscreenROI);
            //修改前视图
            offset = 0; viewmatrix = fVerticesOriginFront;
            break;
        case 0xf1:
            sv2Ddelegate->SetChannel(rear_camera_index);
            SetSingleViewCamPos(REAR_SINGLE_VIEW);
            m_2DSingleViewNode->SetRenderROI(&fullscreenROI);
            //修改后视图
            offset = 1; viewmatrix = fVerticesOriginRear;
            break;
        case 0xf2:
            sv2Ddelegate->SetChannel(left_camera_index);
            SetSingleViewCamPos(LEFT_SINGLE_VIEW);
            m_2DSingleViewNode->SetRenderROI(&fullscreenROI);
            //修改左视图
            offset = 2; viewmatrix = fVerticesOriginLeft;
            break;
        case 0xf3:
            sv2Ddelegate->SetChannel(right_camera_index);
            SetSingleViewCamPos(RIGHT_SINGLE_VIEW);
            m_2DSingleViewNode->SetRenderROI(&fullscreenROI);
            //修改右视图
            offset = 3; viewmatrix = fVerticesOriginRight;
            break;
        default:
            return 0;
            break;
    }

    XRVertexLayout  data_format;
    float* pVertexData = NULL;
    Int32 iCount = 0;
    m_singleviewMesh[offset]->LockData(&pVertexData, &data_format, &iCount);
    memcpy(fVerticesSnapshot[offset], pVertexData, 28 * sizeof(GLfloat));
    memcpy(pVertexData, viewmatrix, 28 * sizeof(GLfloat));
    m_singleviewMesh[offset]->UnLockData();
}

int SVScene::Update(int view_control_flag, int param2)
{
    float steer_angle;
    unsigned char gear_state,temp;
    static int cnt = 0;
    unsigned char enter_top_flag=0;
    float fTextureIndex[8];
    static unsigned char pre_turn_light=0;
    unsigned char turn_light_state;
    float speed;
    float left_wheel_speed=0,right_wheel_speed=0;
    int time_now,time_interval = 0;
    static int time_pre=0;
    static unsigned char suc_init_flag =0;
    static unsigned int temptemp=0;
    temptemp ++;
    unsigned char driver_door_state = 0;
    unsigned char passenger_door_state = 0;
    unsigned char rear_right_door_state = 0;
    unsigned char rear_left_door_state = 0;
    float yaw_rate;
    AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);	
    AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
    AVMData::GetInstance()->m_p_can_data->Get_Turn_Signal(&turn_light_state);
    AVMData::GetInstance()->m_p_can_data->Get_Left_Wheel_Speed(&left_wheel_speed);
    AVMData::GetInstance()->m_p_can_data->Get_Right_Wheel_Speed(&right_wheel_speed);
		
    AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);
    AVMData::GetInstance()->m_p_can_data->Get_Door_State(&driver_door_state, &passenger_door_state, &rear_right_door_state, &rear_left_door_state);
    AVMData::GetInstance()->m_p_can_data->Get_Yaw_Rate(&yaw_rate);
#ifdef EMIRROR
    m_eMirror_node->Update(steer_angle,speed,turn_light_state,gear_state);

#else

    GenerateTextureIndex(fTextureIndex);

    m_pAdasHmi->Update();

    if(gear_state == GEAR_R)
    {
        temp= OLY_DIR_BACKWARD;
    }
    else
    {
        temp = OLY_DIR_FOWARD;
    }

    UpdateOverlayData(0.0-steer_angle,temp);
    enter_top_flag = UpdateRadarAlarm();
    //UpdateGoundTextureData(fTextureIndex);
    if(pre_turn_light != turn_light_state)
    {
        if(turn_light_state == TURN_LIGHT_LEFT)
        {

            ///m_CarDoor[0]->RotateDY(40);
        }
        else if(turn_light_state == TURN_LIGHT_OFF)
        {
            // m_CarDoor[0]->RotateDY(-40);
        }

        pre_turn_light = turn_light_state;
    }
    ChangeCameraConfig(m_camPos);
    FrontViewTurnwithSteering(m_camPos,0.0-steer_angle,588,46);

    ProcessDoorState(driver_door_state, passenger_door_state, rear_right_door_state, rear_left_door_state);
    ProcessViewRot();
#ifdef ALI
    ProcessTurnLight(m_turnlight_state);
#else
    ProcessTurnLight(turn_light_state);

#endif
		
    if(cnt > START_UP_TURN_TIME)
    {
        if(bevSecTour[0]->GetActiveState()==0)
        {

            SwitchView(enter_top_flag,view_control_flag);
            //SwitchView2DOnly(enter_top_flag);

        }
    }
    else
    {
        cnt++;
    }

    // m_luminance->Update();
    //AVMData::GetInstance()->m_lumin_para->SetLuminanceUnNormalizeRGB(g_uiAverageIllum);
    time_now = XrGetTime();
    if(suc_init_flag == 0)
    {
        suc_init_flag =1;
        time_interval = 0;

    }
    else
    {
        time_interval = time_now-time_pre;
    }
    time_interval=(int)(AVMData::GetInstance()->m_p_can_data->GetTimeStamp()/1000);
#ifdef CAR_TRANSPARENT
    static int keyframeupdate =0;
    keyframeupdate++;
#if 0
    speed=1;
    left_wheel_speed=1;
    right_wheel_speed=1;
#endif

    m_stich_node ->Update(steer_angle,speed,left_wheel_speed,right_wheel_speed,gear_state,time_interval,yaw_rate);
    m_pstich_Mtl->SetDiffuseMap(m_stich_node->GetStichFrameTextureId());

    m_3d_ground_Mtl->SetDiffuseMap(m_stich_node->GetGroundTextureId());
    m_stich_wheel->Update(steer_angle);

#endif
    float *pdist=	AVMData::GetInstance()->m_p_can_data->Get_Sonar_dist_list();
    m_pNodeSonar->Update(steer_angle, speed, left_wheel_speed, right_wheel_speed, gear_state, time_interval, yaw_rate, pdist);
    APAOverlayStruct pgs_result;


    m_APA_overlay->Update(g_APA_Result);
    time_pre = time_now;
#endif
    if(speed > SINGLE_VIEW_TO_3D_GATE-5)
    {
        m_overlay_2d_single->SetEnable(0);
		
        m_overlay_2d->SetEnable(0);
    }
    else
    {
	
        m_overlay_2d_single->SetEnable(1);
		
        m_overlay_2d->SetEnable(1);
    }
    //m_Car->SetEnable(0);
    //m_ground->SetEnable(0);
	return 0;
}
void SVScene::ProcessViewRot()
{
    //static unsigned char pre_view_state=0;
	static unsigned char pre_Rot_state=0;

    Boolean b_active_flag=0;

    b_active_flag = bevSecTour[0]->GetActiveState();
    if(b_active_flag == 1 && pre_Rot_state == 0)
    {
        //pre_view_state = m_view_control;

		pre_Rot_state = b_active_flag;
    }
    else if(b_active_flag == 0&& pre_Rot_state ==1)
    {
        SwitchViewLogic(m_pre_view_control);
		pre_Rot_state = b_active_flag;

    }


	return;

}
void SVScene::ProcessDoorState(unsigned char driver_door_state, unsigned char passenger_door_state, unsigned char rear_right_door_state, unsigned char rear_left_door_state)
{
	static unsigned char pre_driver_door_state = 100;
	static unsigned char pre_passenger_door_state = 100;
	static unsigned char pre_rear_right_door_state = 100;
	static unsigned char pre_rear_left_door_state = 100;
///	printf("\n=========Process door state !!!");
	if(pre_driver_door_state != driver_door_state)
	{
		if(DOOR_OPEN == driver_door_state)
			DoorActionSingle(DRIVER_DOOR_POS,DOOR_OPEN);
		else
			DoorActionSingle(DRIVER_DOOR_POS,DOOR_CLOSE);

		pre_driver_door_state = driver_door_state;
	}


	if(pre_passenger_door_state != passenger_door_state)
	{
		if(DOOR_OPEN == passenger_door_state)
			DoorActionSingle(PASSENGER_DOOR_POS,DOOR_OPEN * (-1));
		else
			DoorActionSingle(PASSENGER_DOOR_POS,DOOR_CLOSE);

		pre_passenger_door_state = passenger_door_state;
	}


	if(pre_rear_right_door_state != rear_right_door_state)
	{
		if(DOOR_OPEN == rear_right_door_state)
			DoorActionSingle(REAR_RIGHT_DOOR_POS,DOOR_OPEN * (-1));
		else
			DoorActionSingle(REAR_RIGHT_DOOR_POS,DOOR_CLOSE);

		pre_rear_right_door_state = rear_right_door_state;

	}


	if(pre_rear_left_door_state != rear_left_door_state)
	{
		if(DOOR_OPEN == rear_left_door_state)
			DoorActionSingle(REAR_LEFT_DOOR_POS,DOOR_OPEN);
		else
			DoorActionSingle(REAR_LEFT_DOOR_POS,DOOR_CLOSE);

		pre_rear_left_door_state = rear_left_door_state;
	}


}
void SVScene::DoorActionSingle(int pos,int state)
{
    float rotate_angle = 40;
   	m_CarDoor[pos]->RotateY(state*rotate_angle);
	m_Car_Window[pos]->RotateY(state*rotate_angle);
}

void SVScene::Calc3DGroundPos(float *pPose,float *pWidth,float*pHeight)
{
    float car_point[4];
	CvPoint2D32f car_rect[2];
    float car_adjust_point[4];
	CvPoint2D32f car_rect_world[2];
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

}

void SVScene::UpdateOverlayData(float steeringwheel,unsigned char driveing_direct)
{
    static float pre_steeringwheel=1000.0;
	unsigned  char pre_driving_direct = 0x0f;
    if(m_view_control == REAR_SINGLE_VIEW)
    {
        driveing_direct = OLY_DIR_BACKWARD;
    }
	if(m_view_control == FRONT_SINGLE_VIEW)
    {
        driveing_direct = OLY_DIR_FOWARD;
	}


	if((pre_steeringwheel - steeringwheel)>0.1||(pre_steeringwheel - steeringwheel)<-0.1
       ||driveing_direct!=pre_driving_direct)
	{
        //  m_overlay_data.Update(steeringwheel,driveing_direct);
        //m_overlaymesh->UnLockData();
#ifndef ALI
        m_overlay_data_2d.Update(steeringwheel,driveing_direct);
        m_overlaymesh_2d->UnLockData();



        m_overlay_data_2d_single.Update(steeringwheel,driveing_direct);
        m_overlaymesh_2d_single->UnLockData();
#endif
        pre_steeringwheel = steeringwheel;
        pre_driving_direct = driveing_direct;
	}


}
void SVScene::UpdateGoundTextureData(float *pTextureIndex)
{
    float *pVertexData;
	XRVertexLayout  data_format;
	Int32 icount;
	int i=0;
	IMaterial* pTempMtl;
	static int cnt=0;



	m_pMeshStichGround[m_render_to_AVM_index]->SetEnable(0);

	m_pMeshStichGround[1-m_render_to_AVM_index]->SetEnable(1);

	m_SV2Dplane[eCarImageMesh]->GetMaterial(&pTempMtl);
	pTempMtl->SetDiffuseMap(m_groundRT[m_render_to_AVM_index]->GetTextureId());
	m_3d_ground_Mtl->SetDiffuseMap(m_groundRT[m_render_to_AVM_index]->GetTextureId());

    m_pMeshStichGround[1-m_render_to_AVM_index]->LockData(&pVertexData,&data_format,&icount);

//	if(m_render_to_AVM_index == 1)
	m_ground_mtl[1-m_render_to_AVM_index]->SetDiffuseMap(m_lisenceRT->GetTextureId());
    // else
//	m_ground_mtl[1-m_render_to_AVM_index]->SetDiffuseMap(RADARALARMTEX[1-m_render_to_AVM_index]);

    for(i=0;i<icount;i++)
    {
        pVertexData[8*i+6]=pTextureIndex[2*i];
        pVertexData[8*i+7]=pTextureIndex[2*i+1];

    }

    m_pMeshStichGround[1-m_render_to_AVM_index]->UnLockData();
	cnt++;
	//if(cnt%20==1)

    m_render_to_AVM_index = 1-m_render_to_AVM_index;

}

int SVScene::UpdateRadarAlarm(void)
{
    unsigned char ucAlarm;
	int ret=0;
	int enter_top_flag=0;
	unsigned char switch_vew_flag=0;
    unsigned char drive_direct,temp;
    AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&drive_direct);
	for(int i=0;i<8;i++)
	{
#ifdef CHANGAN_HMI
	    if(i == 2||i==3)
	    {
	        continue;
	    }
#endif
		AVMData::GetInstance()->m_p_can_data->Get_PA_State(i/4,i%4,&ucAlarm);

		if (ucAlarm >= 4)
		{
		    continue;
		}
		
        if(i<4)
        {
            if((ucAlarm != 0)&&ucAlarm<=3)
            {
                enter_top_flag =1;
            }
        }

        if(i>=4)
        {
            if((ucAlarm != 0)&&ucAlarm<=4)
            {
                if((enter_top_flag == 1)||(enter_top_flag == 3))
                {
                    enter_top_flag =3;
                }
				else if((enter_top_flag == 2)||(enter_top_flag == 0))
				{
				    enter_top_flag =2;
				}
            }
        }

	    ret = m_radar_alram[i].Update(i,ucAlarm);
		if(ret == 0)
		{
		    m_RadarAlarm_Node[i]->SetEnable(0);
		}
		else
		{

		    m_RadarAlarm_Node[i]->SetEnable(1);
	        m_RadarAlarm_Mesh[i]->UnLockData();
			m_RadarAlarm_Mtl[i]->SetDiffuseMap(RADARALARMTEX[ucAlarm-1]);
		}

	}
#ifndef ALI

    for(int i=0;i<8;i++)
    {

#ifdef CHANGAN_HMI
    	if(i == 2||i==3)
	    {
	        continue;
	    }
#endif

		if (ucAlarm >= 4)
		{
		    continue;
		}
		
    	AVMData::GetInstance()->m_p_can_data->Get_PA_State(i/4,i%4,&ucAlarm);

    	ret = m_radar_alram_2d[i].Update(i,ucAlarm);
    	if(ret == 0)
    	{
    		m_RadarAlarm_Node_2d[i]->SetEnable(0);
    	}
    	else
    	{

    		m_RadarAlarm_Node_2d[i]->SetEnable(1);
    		m_RadarAlarm_Mesh_2d[i]->UnLockData();

			m_RadarAlarm_Mtl_2d[i]->SetDiffuseMap(RADARALARMTEX[ucAlarm-1]);
    	}
    }
    for(int i=0;i<8;i++)
    {

#ifdef CHANGAN_HMI
        if(i == 2||i==3)
	    {
	        continue;
	    }
#endif
		if (ucAlarm >= 4)
		{
		    continue;
		}

    	AVMData::GetInstance()->m_p_can_data->Get_PA_State(i/4,i%4,&ucAlarm);
        if(i<4)
        {
            if((ucAlarm != 0)&&ucAlarm<=4)
			{
                switch_vew_flag =1;
            }
        }

        if(i>=4)
        {
            if((ucAlarm != 0)&&ucAlarm<=4)
            {
                if((switch_vew_flag == 1)||(switch_vew_flag == 3))
                {
                    switch_vew_flag =3;
                }
				else if((switch_vew_flag == 2)||(switch_vew_flag == 0))
				{
				    switch_vew_flag =2;
				}
            }
        }
    	ret = m_radar_alarm_single[i].Update(i,ucAlarm);
    	if(ret == 0)
    	{
    		m_RadarAlarm_Node_single[i]->SetEnable(0);
    	}
    	else
    	{

    		m_RadarAlarm_Node_single[i]->SetEnable(1);
    		m_RadarAlarm_Mesh_single[i]->UnLockData();

			m_RadarAlarm_Mtl_single[i]->SetDiffuseMap(RADARALARMTEX[ucAlarm-1]);
    	}


    }
    if(sv2Ddelegate->GetChannel()==front_camera_index)
    {
        for(int i=4;i<8;i++)
        {
            m_RadarAlarm_Node_single[i]->SetEnable(0);
        }
    }
    else if(sv2Ddelegate->GetChannel()==rear_camera_index)
    {
        for(int i=0;i<4;i++)
        {
            m_RadarAlarm_Node_single[i]->SetEnable(0);
        }
    }
#endif
	return enter_top_flag;
}

void SVScene::UpdateExternCalibReslt(float *pos)
{

    svdelegate->UpdateExParamCalibRslt(pos);
	AVMData::GetInstance()->m_exParam->UpdateExParamCalibRslt(pos);

}
void SVScene::UpdateExternCalib2DReslt(GLfloat *pData,int data_size,GLushort *pIndex,int index_size)
{
    IMesh *pMeshTemp;
    // sv2Ddelegate->Update2DCalibRslt(pData,data_size,pIndex,index_size);
	AVMData::GetInstance()->m_2D_lut->UpdateLUT(pData,pIndex);

    m_2d_update_flag =1;
#ifdef CAR_TRANSPARENT
    m_stich_node->Update2DStichRslt();
	 
#endif
#if 0
	for(int i=0;i<8;i++)
	{

		m_SV2Dplane[i]->GetMesh(&pMeshTemp);
		pMeshTemp->UnLockData();

	}
#endif

}
void SVScene::UpdateStich2DReslt(unsigned char Seam_Update_Flag[],GLfloat *pData)
{
    IMesh *pMeshTemp;
   // sv2Ddelegate->Update2DCalibRslt(pData,data_size,pIndex,index_size);
   float *pTemp;
   unsigned int BufSize;
   unsigned int totalBufSize=0;
   for(int i=0;i<4;i++)
   {
   
       m_SV2DData->GetVertexBuffer(eFrontLeftMesh+i,&pTemp,&BufSize);
       if(1== Seam_Update_Flag[i])
       {
	       memcpy(pTemp,pData+7*totalBufSize,BufSize*7*sizeof(GLfloat));
   	
           m_stich_node->UpdateStich2DReslt(i);
       }
	   
	   totalBufSize+=BufSize;
   }

}
void SVScene::SaveOverlayData(void)
{

    m_overlay_data_2d.SaveVertexData();
	//m_overlaymesh->UnLockData();

}

void SVScene::ProcessWheelTurn(float steeringwheel)
{
    IAProperty *val;
    float wheel_angle = 0;
    wheel_angle = -(steeringwheel/600.0)*60.0*3.1415926/180.0;
#ifdef CAR_MODEL
    for (int i=0;i<14;i++)
#else
        for (int i=0;i<4;i++)
#endif
        {

            if (i%4<2) {
                m_wheel[i]->GetCAProperty(AP_RY, &val);
                val->Set(wheel_angle);
            }
        }

}
void SVScene::ProcessWheelRoll(unsigned char gear_state, float speed)
{
    static int vehicle_state = 1;
    static float vehicle_speed = 0.0;
    static float vehicle_last_speed = 0.0;

    if(vehicle_speed > 6.29 )
    {
        vehicle_speed = 0.0;
    }
    if(GEAR_R == gear_state)
    {
        vehicle_state = -1;
    }
    else
    {
        vehicle_state = 1;
    }

    vehicle_speed += (0.005 * speed) ;

    IAProperty* val=0;
#ifdef CAR_MODEL
    for (int i=0;i<14;i++)
#else
        for (int i=0;i<4;i++)
#endif
        {
            m_wheel[i]->GetCAProperty(AP_RX, &val);
            val->Set(vehicle_state * vehicle_speed);
        }

}

void SVScene::ProcessTurnLight(unsigned char turn_light)
{
	static unsigned int flash_cnt[2] = {0,};



    if(turn_light == TURN_LIGHT_OFF)
    {
        m_carlightmtl->SetAmbientColor(1.0,1.0,1.0,0.0);
		flash_cnt[0]=0;
		flash_cnt[1]=0;
    }
    else if(turn_light == TURN_LIGHT_LEFT)
    {

        flash_cnt[1]=0;

        if(flash_cnt[0]<LIGHT_ON_TIME)
        {
            m_carlightmtl->SetAmbientColor(TURN_LIGHT_COLOR_R,TURN_LIGHT_COLOR_G,TURN_LIGHT_COLOR_B,1.0);
        }
		else if(flash_cnt[0]<LGITH_FLASH_TIME)
		{
            m_carlightmtl->SetAmbientColor(1.0,1.0,1.0,0.0);
		}

		flash_cnt[0]++;
		if(flash_cnt[0] ==LGITH_FLASH_TIME)
		{
            flash_cnt[0] = 0;
		}
    }
    else if(turn_light == TURN_LIGHT_RIGHT)
    {
        flash_cnt[0]=0;
        if(flash_cnt[1] <LIGHT_ON_TIME)
        {
            m_carlightmtl->SetAmbientColor(TURN_LIGHT_COLOR_R,TURN_LIGHT_COLOR_G,TURN_LIGHT_COLOR_B,2.0);
        }
		else if(flash_cnt[1]<LGITH_FLASH_TIME)
		{
            m_carlightmtl->SetAmbientColor(1.0,1.0,0.0,0.0);
		}
		flash_cnt[1]++;
		if(flash_cnt[1] ==LGITH_FLASH_TIME)
		{
            flash_cnt[1] = 0;
		}
    }
	else
	{
        flash_cnt[1] = 0;
     	if(flash_cnt[0]<LIGHT_ON_TIME)
     	{
     		m_carlightmtl->SetAmbientColor(TURN_LIGHT_COLOR_R,TURN_LIGHT_COLOR_G,TURN_LIGHT_COLOR_B,3.0);
     	}
     	else if(flash_cnt[0]<LGITH_FLASH_TIME)
     	{
     		m_carlightmtl->SetAmbientColor(1.0,1.0,1.0,1.0);
     	}

     	flash_cnt[0]++;
     	if(flash_cnt[0] ==LGITH_FLASH_TIME)
     	{
     		flash_cnt[0] = 0;
     	}



	}
}


#define SPEED_CHANGE_TIME_GATE 40
void SVScene::SwitchView(unsigned char input_enter_top_flag,int view_control_flag)
{
    //UpdateTexture();
    float speed,steeringwheel;
	unsigned char gear_state,turn_light,temp,cam_dir;
	static int st_steer_turn_cnt=0;
	static unsigned int speed_high_cnt=0;
	static unsigned int  speed_low_cnt = 0;
	static unsigned int speed_second_high_cnt = 0;
	static unsigned char pre_speed_falg =0;//0---low_speed, 1--high_speed
	static unsigned char speed_flag=0;
	static unsigned char speed_high_flag = 0; //0---low_speed, 1--speed < 30, 2--speed >= 30
	static unsigned int exit_top_view_cnt = 0;
	static unsigned char pre_input_flag=0;
	static unsigned char pre_wheel_rot=0;
	unsigned char wheel_rot =0;
	unsigned char view_cmd = 0;
	unsigned char enter_top_flag;
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);
	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	AVMData::GetInstance()->m_p_can_data->Get_Turn_Signal(&turn_light);
	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steeringwheel);
#ifndef ALI
	ProcessWheelTurn(steeringwheel);
	ProcessWheelRoll(gear_state,speed);
#endif
    if(speed >0.1)
    {
        wheel_rot =1;
    }
	else
	{
	    wheel_rot = 0;
	}

    if((pre_input_flag != input_enter_top_flag)&&(input_enter_top_flag == 0))

    {
		if(exit_top_view_cnt >= 40)
		{
		    enter_top_flag = input_enter_top_flag;

		}
		else
		{
		    enter_top_flag = pre_input_flag;
			exit_top_view_cnt++;
		}

    }
	else
	{
	    enter_top_flag = input_enter_top_flag;
		exit_top_view_cnt=0;
	}



    if(speed >= SINGLE_VIEW_TO_3D_GATE)
    {
		speed_low_cnt=0;
    	if(speed >= HIGH_SPEED_GATE)
		{
			speed_second_high_cnt ++;
		}
		else
		{
			speed_second_high_cnt = 0;
		}

		if(speed_second_high_cnt >= SPEED_CHANGE_TIME_GATE)
		{
			speed_high_flag = 2;
		}
		else if(speed_high_cnt >= SPEED_CHANGE_TIME_GATE )
		{
			speed_high_flag = 1;
		}

		if(speed_high_cnt >= SPEED_CHANGE_TIME_GATE )
		{
            speed_flag=1;
		}
	    else
	    {
            speed_high_cnt++;
	    }
    }
	else
	{
        speed_high_cnt = 0;
        speed_second_high_cnt = 0;

		if(speed_low_cnt >= SPEED_CHANGE_TIME_GATE )
		{
            speed_flag=0;

			speed_high_flag = 0;
		}
	    else
	    {
            speed_low_cnt++;
	    }

	}

    if(speed_flag == 0)
    {
        JudgeCameraDir(&cam_dir,gear_state,turn_light,speed,speed_high_flag);
		if(cam_dir == CAMERA_DIR_FRONT)
        {
            // view_cmd = BOSH_FRONT_VIEW;

            view_cmd = FRONT_SINGLE_VIEW;
        }
        else if((cam_dir == CAMERA_DIR_REAR_LEFT)&&(steeringwheel <STEERING_WHEEL_STILL_GATE && steeringwheel >= -STEERING_WHEEL_STILL_GATE))
        {
            // view_cmd = LEFT_MIRROR_VIEW;
            view_cmd = FRONT_3D_VIEW+cam_dir;
        }

		else if((cam_dir == CAMERA_DIR_REAR_LEFT)&&(steeringwheel >=STEERING_WHEEL_STILL_GATE || steeringwheel <= -STEERING_WHEEL_STILL_GATE))
		{
		    view_cmd = FRONT_3D_VIEW+cam_dir;
		}
		else if(cam_dir == CAMERA_DIR_REAR_RIGHT&&(steeringwheel <STEERING_WHEEL_STILL_GATE && steeringwheel >= -STEERING_WHEEL_STILL_GATE))
        {
		    //view_cmd = RIGHT_MIRROR_VIEW;
			view_cmd = FRONT_3D_VIEW+cam_dir;
		}
		else if((cam_dir == CAMERA_DIR_REAR_RIGHT)&&(steeringwheel >=STEERING_WHEEL_STILL_GATE || steeringwheel <= -STEERING_WHEEL_STILL_GATE))
		{
		    view_cmd = FRONT_3D_VIEW+cam_dir;
		}
		else if((cam_dir == CAMERA_DIR_LEFT)||(cam_dir == CAMERA_DIR_RIGHT))
		{
		    view_cmd = FRONT_3D_VIEW+cam_dir;
		}
  		else if((cam_dir == CAMERA_DIR_REAR))
		{
		    view_cmd = REAR_SINGLE_VIEW;
		}



    }
	else
	{
	    if(turn_light == TURN_LIGHT_OFF)
	    {
            if(steeringwheel <STEERING_WHEEL_GATE && steeringwheel >= -STEERING_WHEEL_GATE)
            {
                st_steer_turn_cnt = 0;
    			JudgeCameraDir(&cam_dir,gear_state,turn_light,speed,speed_high_flag);
    			view_cmd = (FRONT_3D_VIEW+cam_dir);

            }
    		else if(steeringwheel > STEERING_WHEEL_GATE)
    		{

    			JudgeCameraDir(&cam_dir,gear_state,TURN_LIGHT_LEFT,speed,1);
    			view_cmd = (FRONT_3D_VIEW+cam_dir);
    			st_steer_turn_cnt++;

    		}
    		else
    		{

    			JudgeCameraDir(&cam_dir,gear_state,TURN_LIGHT_RIGHT,speed,1);
    			view_cmd = (FRONT_3D_VIEW+cam_dir);
    			st_steer_turn_cnt++;


    		}
			JudgeCameraDir(&cam_dir,gear_state,turn_light,speed,speed_high_flag);
			view_cmd = (FRONT_3D_VIEW+cam_dir);
			
	    }
		else
		{

			st_steer_turn_cnt = 0;
			JudgeCameraDir(&cam_dir,gear_state,turn_light,speed,speed_high_flag);
			view_cmd = (FRONT_3D_VIEW+cam_dir);
		}

	}
	if(((enter_top_flag == 1)||(enter_top_flag ==3 && gear_state != GEAR_R))
       &&(view_cmd == FRONT_3D_VIEW||view_cmd == BOSH_FRONT_VIEW||view_cmd==LEFT_FRONT_3D_VIEW
          ||view_cmd == RIGHT_FRONT_3D_VIEW||view_cmd == LEFT_TURN_SIGNAL_3D_VIEW||view_cmd == RIGHT_TURN_SIGNAL_3D_VIEW
          ||view_cmd ==FRONT_SINGLE_VIEW))
	{
	    view_cmd = BOSH_FRONT_VIEW_TOP;
	}

	if(((enter_top_flag == 2)||(enter_top_flag ==3 && gear_state == GEAR_R)))
		/*&&(view_cmd == REAR_3D_VIEW||view_cmd == BOSH_FRONT_VIEW||view_cmd==LEFT_REAR_3D_VIEW
          ||view_cmd == RIGHT_REAR_3D_VIEW||view_cmd == LEFT_REAR_TURN_SIGNAL_3D_VIEW||view_cmd == RIGHT_REAR_TURN_SIGNAL_3D_VIEW
          ||view_cmd ==REAR_SINGLE_VIEW||view_cmd ==LEFT_MIRROR_VIEW||view_cmd == RIGHT_MIRROR_VIEW))*/
	{
	    view_cmd = BOSH_REAR_VIEW_TOP;
	}


    if(view_cmd == FRONT_3D_VIEW||REAR_3D_VIEW == view_cmd)
    {
        view_cmd = FRONT_SINGLE_VIEW;
    }
	
    if(view_control_flag == 1)
    {
        view_cmd = REAR_SINGLE_VIEW;
    }
    else if (view_control_flag == 3)
    {
        view_cmd = RIGHT_SINGLE_VIEW;		
    }
    else if(view_control_flag == 2)
    {
        view_cmd = CROSS_IMAGE_VIEW;
    }

	if(m_touchedSelectViewState != m_lastSelectViewState && view_cmd != TOUR_VIEW)
	{
		SwitchViewLogic(m_touchedSelectViewState);
	}

	m_currentCanSetViewState = view_cmd;
    if(view_cmd != m_last_view)
    {		
        SwitchViewLogic(view_cmd);
    }

    if(pre_wheel_rot != wheel_rot)
    {
        if(wheel_rot == 0)
        {
            //wheelRot->Stop();
        }
		else
		{
            // wheelRot->Start();
		}
    }

    m_last_view = view_cmd;
	m_lastSelectViewState = m_touchedSelectViewState;

	pre_speed_falg = speed_flag;
	pre_input_flag = enter_top_flag;
	pre_wheel_rot = wheel_rot;

}
#define SPEED_CHANGE_TIME_GATE 40
void SVScene::SwitchView2DOnly(unsigned char input_enter_top_flag)
{
    //UpdateTexture();
    float speed,steeringwheel;
	unsigned char gear_state,turn_light,temp,cam_dir;
	static int st_steer_turn_cnt=0;
	static unsigned int speed_high_cnt=0;
	static unsigned int  speed_low_cnt = 0;
	static unsigned int speed_second_high_cnt = 0;
	static unsigned char pre_speed_falg =0;//0---low_speed, 1--high_speed
	static unsigned char speed_flag=0;
	static unsigned char speed_high_flag = 0; //0---low_speed, 1--speed < 30, 2--speed >= 30
	static unsigned int exit_top_view_cnt = 0;
	static unsigned char pre_input_flag=0;
	static unsigned char pre_wheel_rot=0;
	unsigned char wheel_rot =0;
	unsigned char view_cmd = 0;
	unsigned char enter_top_flag;
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);
	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	AVMData::GetInstance()->m_p_can_data->Get_Turn_Signal(&turn_light);
	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steeringwheel);
#ifndef ALI
	ProcessWheelTurn(steeringwheel);
	ProcessWheelRoll(gear_state,speed);
#endif
    if(speed >0.1)
    {
        wheel_rot =1;
    }
	else
	{
	    wheel_rot = 0;
	}

    if((pre_input_flag != input_enter_top_flag)&&(input_enter_top_flag == 0))

    {
		if(exit_top_view_cnt >= 40)
		{
		    enter_top_flag = input_enter_top_flag;

		}
		else
		{
		    enter_top_flag = pre_input_flag;
			exit_top_view_cnt++;
		}

    }
	else
	{
	    enter_top_flag = input_enter_top_flag;
		exit_top_view_cnt=0;
	}



    if(speed >= SINGLE_VIEW_TO_3D_GATE)
    {
		speed_low_cnt=0;
    	if(speed >= HIGH_SPEED_GATE)
		{
			speed_second_high_cnt ++;
		}
		else
		{
			speed_second_high_cnt = 0;
		}

		if(speed_second_high_cnt >= SPEED_CHANGE_TIME_GATE)
		{
			speed_high_flag = 2;
		}
		else if(speed_high_cnt >= SPEED_CHANGE_TIME_GATE )
		{
			speed_high_flag = 1;
		}

		if(speed_high_cnt >= SPEED_CHANGE_TIME_GATE )
		{
            speed_flag=1;
		}
	    else
	    {
            speed_high_cnt++;
	    }
    }
	else
	{
        speed_high_cnt = 0;
        speed_second_high_cnt = 0;

		if(speed_low_cnt >= SPEED_CHANGE_TIME_GATE )
		{
            speed_flag=0;

			speed_high_flag = 0;
		}
	    else
	    {
            speed_low_cnt++;
	    }

	}


    JudgeCameraDir(&cam_dir,gear_state,turn_light,speed,speed_high_flag);
    if(cam_dir == CAMERA_DIR_FRONT)
    {
        // view_cmd = BOSH_FRONT_VIEW;

        view_cmd = FRONT_SINGLE_VIEW;
    }
    else if((cam_dir == CAMERA_DIR_REAR_LEFT)||(cam_dir == CAMERA_DIR_LEFT))
    {
        view_cmd = LEFT_SINGLE_VIEW;

    }

    else if(cam_dir == CAMERA_DIR_REAR_RIGHT||(cam_dir == CAMERA_DIR_RIGHT))
    {
        //view_cmd = RIGHT_MIRROR_VIEW;
        view_cmd =RIGHT_SINGLE_VIEW;
    }

    else if((cam_dir == CAMERA_DIR_REAR))
    {
        view_cmd = REAR_SINGLE_VIEW;
    }





	if(((enter_top_flag == 1)||(enter_top_flag ==3 && gear_state != GEAR_R))
       &&(view_cmd == FRONT_3D_VIEW||view_cmd == BOSH_FRONT_VIEW||view_cmd==LEFT_FRONT_3D_VIEW
          ||view_cmd == RIGHT_FRONT_3D_VIEW||view_cmd == LEFT_TURN_SIGNAL_3D_VIEW||view_cmd == RIGHT_TURN_SIGNAL_3D_VIEW
          ||view_cmd ==FRONT_SINGLE_VIEW))
	{
	    view_cmd = BOSH_FRONT_VIEW_TOP;
	}

	if(((enter_top_flag == 2)||(enter_top_flag ==3 && gear_state == GEAR_R)))
		/*&&(view_cmd == REAR_3D_VIEW||view_cmd == BOSH_FRONT_VIEW||view_cmd==LEFT_REAR_3D_VIEW
          ||view_cmd == RIGHT_REAR_3D_VIEW||view_cmd == LEFT_REAR_TURN_SIGNAL_3D_VIEW||view_cmd == RIGHT_REAR_TURN_SIGNAL_3D_VIEW
          ||view_cmd ==REAR_SINGLE_VIEW||view_cmd ==LEFT_MIRROR_VIEW||view_cmd == RIGHT_MIRROR_VIEW))*/
	{
	    view_cmd = BOSH_REAR_VIEW_TOP;
	}

    if(view_cmd != m_last_view)
    {
		SwitchViewLogic(view_cmd);

    }
    if(pre_wheel_rot != wheel_rot)
    {
        if(wheel_rot == 0)
        {
            //wheelRot->Stop();
        }
		else
		{
            // wheelRot->Start();
		}
    }
    m_last_view = view_cmd;
	pre_speed_falg = speed_flag;
	pre_input_flag = enter_top_flag;
	pre_wheel_rot = wheel_rot;

}

void  SVScene::SwitchViewCtrlButton(unsigned char Ctrl_Direct)
{
    float speed;
	unsigned char view;
	unsigned char gear_state,temp;
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);

	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	if(bevSecTour[0]->GetActiveState()==0)
	{
        if(Ctrl_Direct == CTRL_BUTTON_FRONT)
        {
            if(speed < SINGLE_VIEW_TO_3D_GATE)
            {
                SwitchViewLogic(FRONT_SINGLE_VIEW);
            }
            else
            {
                SwitchViewLogic(FRONT_3D_VIEW);
            }
        }
        else if(Ctrl_Direct == CTRL_BUTTON_REAR)
        {
            if(speed < SINGLE_VIEW_TO_3D_GATE)
            {
                SwitchViewLogic(REAR_SINGLE_VIEW);
            }
            else
            {
                SwitchViewLogic(REAR_3D_VIEW);
            }
        }
        else if(Ctrl_Direct == CTRL_BUTTON_LEFT)
        {
            if(gear_state == GEAR_R)
            {
                SwitchViewLogic(LEFT_REAR_3D_VIEW);
            }
            else
            {
                SwitchViewLogic(LEFT_FRONT_3D_VIEW);
            }
        }
        else if(Ctrl_Direct == CTRL_BUTTON_RIGHT)
        {
   		    if(gear_state == GEAR_R)
            {
                SwitchViewLogic(RIGHT_REAR_3D_VIEW);
            }
            else
            {
                SwitchViewLogic(RIGHT_FRONT_3D_VIEW);
            }
        }
	}
    return;

}

void SVScene::JudgeCameraDir(unsigned char *output, unsigned char gear_state,unsigned char turn_light, float vehicle_speed, unsigned char vehicle_speed_flag)
{
	if(gear_state==GEAR_R)
	{
#ifdef ALI
		sv2Ddelegate->SetChannel(rear_camera_index);
#endif
		*output=CAMERA_DIR_REAR;

		if(turn_light == TURN_LIGHT_LEFT)
		{
			if(vehicle_speed >= HIGH_SPEED_GATE && 2 == vehicle_speed_flag)
				*output = CAMERA_DIR_HIGH_SPEED_LEFT;
			else
				*output = CAMERA_DIR_REAR_LEFT;
		}
		else if(turn_light == TURN_LIGHT_RIGHT)
		{
			if(vehicle_speed >= HIGH_SPEED_GATE && 2 == vehicle_speed_flag)
				*output = CAMERA_DIR_HIGH_SPEED_RIGHT;
			else
				*output = CAMERA_DIR_REAR_RIGHT;
		}
		else
		{
			*output = CAMERA_DIR_REAR;
		}
	}
	else
	{

#ifdef ALI
		//sv2Ddelegate->SetChannel(front_camera_index);
#endif

		if(turn_light == TURN_LIGHT_LEFT)
		{
			if(vehicle_speed >= HIGH_SPEED_GATE && 2 == vehicle_speed_flag)
				*output = CAMERA_DIR_HIGH_SPEED_LEFT;
			else
				*output =CAMERA_DIR_LEFT;
		}
		else if(turn_light == TURN_LIGHT_RIGHT)
		{
			if(vehicle_speed >= HIGH_SPEED_GATE && 2 == vehicle_speed_flag)
				*output = CAMERA_DIR_HIGH_SPEED_RIGHT;
			else
				*output = CAMERA_DIR_RIGHT;
		}
		else
		{

    		if(vehicle_speed >= HIGH_SPEED_GATE && 2 == vehicle_speed_flag)
    			*output = CAMERA_DIR_REAR;
            else
    			*output = CAMERA_DIR_FRONT;

		}
	}

}

static int dx, dy;
void SVScene::OnMouseDown(int x, int y)
{
	m_prevX = x;
	m_prevY = y;
	//if (m_mode == SceneMode_Top) {
	//	float interpolation = float(y)/XrGetScreenHeight();
	//	SetTopViewCrameraFov((1-interpolation)*m_freeModeFOV + interpolation*180);
	//}
}

void SVScene::OnMouseUp(int x, int y)
{
	IAProperty* rotX=0, *rotY,*posZ=0;
	float temp=0;

	if (XrGetTime()-m_lastTime > 200) {
		dy = 0;
		dx = 0;
	}
#ifdef EMIRROR
    //m_eMirror_node->CameraRollDelta(Float32(dx)/4,Float32(dx)/4);
#else
	if (m_mode == SceneMode_Free&&(bevSecTour[0]->GetActiveState()==0)) {

        m_sceneCamera->GetCAProperty(AP_RX, &rotX);
        m_sceneCamera->GetCAProperty(AP_RY, &rotY);

        temp = rotX->Get();


        if (m_camPos == CameraPosition_Free) {
            //if(abs((int)(temp+dx/4))%360<50||(abs(((int)(temp+dx/4)))%360>310&&(abs((int)(temp+dx/4))%360<360)))
            {
                if (scrollX) scrollX->Scroll(Float32(dx)/4);
                if (scrollY) scrollY->Scroll(Float32(dy)/4);


            }
		}
		else {
			scrollX->DockToValue(0);
			scrollY->DockToValue(20);
		}
	}
	else if (m_mode == SceneMode_Pano) {
		if (scrollX) scrollX->Scroll(Float32(dx)/4);
	}
#endif
	m_prevX = x;
	m_prevY = y;
}

void SVScene::OnMouseMove(int x, int y)
{
	IAProperty* rotX=0, *rotY,*posZ=0;
	float temp=0;

	dx = m_prevX - x;
	dy = m_prevY - y;

#ifdef EMIRROR
    m_eMirror_node->CameraRollDelta(Float32(dx)/4,Float32(dx)/4);
#else
    m_sceneCamera->GetCAProperty(AP_RX, &rotX);
	m_sceneCamera->GetCAProperty(AP_RY, &rotY);

	temp = rotX->Get();

	if (m_mode == SceneMode_Free&&(bevSecTour[0]->GetActiveState()==0)) {
		//if(abs((int)(temp+dx/4))%360<50||(abs(((int)(temp+dx/4)))%360>310&&(abs((int)(temp+dx/4))%360<360)))
		{

            if (scrollX) scrollX->DockToDeltaValue(Float32(dx)/4);
            if (scrollY) scrollY->DockToDeltaValue(Float32(dy)/4);


        }
	}
	else if (m_mode == SceneMode_Pano) {
		if (scrollX) scrollX->DockToDeltaValue(Float32(dx)/4);
	}
#endif
	m_prevX = x;
	m_prevY = y;
	m_lastTime = XrGetTime();
}

void SVScene::SetTouchSelectView(unsigned char view_index)
{
	m_touchedSelectViewState = view_index;
}
void SVScene::GetCurrentDisplayView(unsigned char &view_index)
{
	view_index = m_currentCanSetViewState;
}