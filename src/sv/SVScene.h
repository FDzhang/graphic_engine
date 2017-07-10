#ifndef __SV_SCENE_H__
#define __SV_SCENE_H__

#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "GlSV2D.h"
#include "bev_config.h"
#include "GlSVOverlay.h"
#include "GlSVRadarAlarm.h"
#include "GlSVLuminance.h"

#define NONE_CHINESE_WORD 999
typedef enum SceneMode {
    SceneMode_Free				= 0x00000000,
    SceneMode_Top               = 0x00000001,
    SceneMode_Cross             = 0x00000002,
    SceneMode_Pano              = 0x00000003,
};

typedef enum ProductList {
    PRODUCT_BEV				= 0x00000000,
    PRODUCT_ESR             = 0x00000001,
     PRODUCT_IFV              = 0x00000002,
    PRODUCT_RSDS              = 0x00000003,    
    PRODUCT_WHEEL              = 0x00000004,
	PRODUCT_TOUR			  = 0x00000005,
    PRODUCT_AMOUNT
};
typedef enum ZoomList {
    ZOOM_IN				= 0x00000000,
    ZOOM_OUT             = 0x00000001,
	ZOOM_TURN			 = 0x00000002,	
	ZOOM_TYRE			 = 0x00000003,
    ZOOM_MODEL			 = 0x00000004,
	ZOOM_COLOR			 = 0x00000005,
	
    
};
typedef enum DirectCtrl {
    CTRL_BUTTON_FRONT			= 0x00000000,
    CTRL_BUTTON_REAR             = 0x00000001,
	CTRL_BUTTON_LEFT			 = 0x00000002,	
	CTRL_BUTTON_RIGHT			 = 0x00000003,
    
};

typedef enum ProductionPosAdjust {
    POS_X_POS,
	POS_Y_POS,
	POS_Z_POS,
    POS_ROTX_POS,
	POS_ROTY_POS,
	POS_ROTZ_POS,	
	POS_SAVE,
	POS_ZOOM_IN,
    POS_X_NEG,
	POS_Y_NEG,
	POS_Z_NEG,
    POS_ROTX_NEG,
	POS_ROTY_NEG,
	POS_ROTZ_NEG,
	POS_CANCLE,
	POS_ZOOM_OUT,
};

typedef enum CarColor {
    RED_CAR				= 0x00000000,
    GREEN_CAR               = 0x00000001,
    WHITE_CAR             = 0x00000002,
    GRAY_CAR              = 0x00000003,
    
    PINK_CAR              = 0x00000004,
};
typedef enum CarModel {
    CAR_CAR				= 0x00000000,
    CAR_SUV               = 0x00000001,
    CAR_VAN             = 0x00000002,
    CAR_TRUCK              = 0x00000003,
};

typedef enum CameraPosition {
	CameraPosition_Free			= 0x00000000,
	CameraPosition_Back			= 0x00000001,
    CameraPosition_Front		= 0x00000002,
	CameraPosition_Left			= 0x00000003,
	CameraPosition_Right		= 0x00000004,
	CameraPosition_Left_Rear	= 0x00000005,
	CameraPosition_Right_Rear	= 0x00000006,
	CameraPosition_Left_Front	= 0x00000007,
	CameraPosition_Right_Front	= 0x00000008,
	CameraPosition_Left_Rear_Light	= 0x00000009,
	CameraPosition_Right_Rear_Light	= 0x0000000a,		
	CameraPosition_BOSCH_Front	= 0x0000000b,	
	
	CameraPosition_BOSCH_Front_Top	= 0x000000c,	
	CameraPosition_BOSCH_Rear_Top_REVERSE	= 0x000000d,	
	CameraPosition_BOSCH_Rear_Top	= 0x000000e,
	
	CameraPosition_Left_Front_Light = 0x000000f,
	CameraPosition_Right_Front_Light = 0x0000010,
};
typedef enum RightViewType {
	FRONT_SINGLE_VIEW			= 0x00000000,
	REAR_SINGLE_VIEW			= 0x00000001,
    LEFT_SINGLE_VIEW		    = 0x00000002,
	RIGHT_SINGLE_VIEW			= 0x00000003,
	FRONT_3D_VIEW       		= 0x00000004,
	REAR_3D_VIEW				= 0x00000005,
	LEFT_FRONT_3D_VIEW                =0x0000006,
	RIGHT_FRONT_3D_VIEW				=0x0000007,	
	LEFT_REAR_3D_VIEW           =0x0008,
	RIGHT_REAR_3D_VIEW          = 0x00009,
	LEFT_TURN_SIGNAL_3D_VIEW,
	RIGHT_TURN_SIGNAL_3D_VIEW,
	LEFT_REAR_TURN_SIGNAL_3D_VIEW,
	RIGHT_REAR_TURN_SIGNAL_3D_VIEW,	
	LEFT_HIGHT_SPEED_TURN_3D_VIEW,
	RIGHT_HIGHT_SPEED_TURN_3D_VIEW,
	TOUR_VIEW,
	BOSH_FRONT_VIEW,
	BOSH_FRONT_VIEW_TOP,	
	BOSH_REAR_VIEW_TOP,
	LEFT_MIRROR_VIEW,
	RIGHT_MIRROR_VIEW,	
	CROSS_IMAGE_VIEW,			
	TOTAL_VIEW_NUM,
};


#define LGITH_FLASH_TIME 20
#define LIGHT_ON_TIME 18
#define TURN_LIGHT_COLOR_R 0.97
#define TURN_LIGHT_COLOR_G  0.4
#define TURN_LIGHT_COLOR_B  0.01

#define DOOR_OPEN 1
#define DOOR_CLOSE 0
#define  DRIVER_DOOR_POS 0
#define  PASSENGER_DOOR_POS 1
#define REAR_LEFT_DOOR_POS  2
#define REAR_RIGHT_DOOR_POS  3

#define GEAR_P  0
#define GEAR_R  3
#define GEAR_N  1
#define GEAR_D  2

//#define EMIRROR



#define START_UP_TURN_TIME 200
#define CAMERA_ASPECT  1.333
class SVScene
{
	// The program object containing the 2 shader objects

public:
	SVScene() 
	{
		m_lisenceRT = 0;
	}
	int InitNode(BEV_CONFIG_T  pConfig,st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum);
	void InitSceneNode(BEV_CONFIG_T  pConfig);
	void InitObjectNode(BEV_CONFIG_T  pConfig);
	void InitViewNode();
	void ProcessDoorState(unsigned char driver_door_state, unsigned char passenger_door_state, unsigned char rear_right_door_state, unsigned char rear_left_door_state);
	int UpdateAnimation();
	int Update(int view_control_flag, int param2);
    int SwitchCrossView();
    int SwitchSingleView(int view_control_flag);
    void ShowProduct(Int32 pos);
    void AdjustProductPosition(Int32 pos);	
	void EnterTopView(Int32 pos);
	void EnterCrossView(Int32 pos);
	void EnterFreeView(Int32 pos);
	void EnterPanorama(Int32 pos);
	void SwitchCameraPosition(Int32 pos);
	void SetTopViewCrameraFov(Float32 fov);
	void Draw();
	void OnMouseDown(int x, int y);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);
	void FadeInView(unsigned char flag);
	void SwitchCarColor(Int32 pos);
	void SwitchCarModel(Int32 pos);
	void SetupLisence();
	void UpdateLisence(char* backgroundTex,char* text);
	void GenerateRadarWaveAnimateKey(float **fKey,float time_period,float *dist_state,float *init_state,int item_num,int key_num);
    void SetProductVisible(unsigned char visibleflag);	
	void InitBevDisplayEffect();
	void UpdateLisceseText(String textupdate,unsigned int ChineseIndex);	
	void InitTourDisplaySecEffect();
	void InitTourDisplayEffect();
	void ResetStyleSetting(void);	
	void InitSingleViewNode(GlSV2D *pSV2DData);
	void JudgeCameraDir(unsigned char *output, unsigned char gear_state,unsigned char turn_light, float vehicle_speed, unsigned char vehicle_speed_flag);
	void SwitchView(unsigned char input_enter_top_flag,int view_control_flag);
	void DoorActionSingle(int pos,int state);	
	void ChangeCameraConfig(Int32 pos);
	void SwitchViewLogic(unsigned char  Input);
	void Init2DAVMNode();
	void ZoomFunction(Int32 pos);
	void InitProductModel(void);
	void ProcessWheelTurn(float steeringwheel);
	void FrontViewTurnwithSteering(Int32 pos,float steeringwheel_angle,float max_steering_wheel,float max_turn_angle);
    void LightUpCtrlIndicate(unsigned char view_index)	;
	void InitRadarWaveMesh(float radius, int mesh_longi,int mesh_lati,int angle,float point_z,IMesh **pMesh,INode **pNode,float wavecolor[],char tex[],float speed=1.0);
	void SetSingleViewCamPos(unsigned char ucDir);
	void InitOverlay(BEV_CONFIG_T pConfig , ISceneNode *pNode,IMesh **pMesh,INode **OverlayNode,GlSVOverlay *pOverlayData,unsigned char calib_mode,float *pos);
	void UpdateOverlayData(float steeringwheel,unsigned char driveing_direct);
	
	void SaveOverlayData(void);
	
	void InitMirrorNode(BEV_CONFIG_T pConfig , ISceneNode *pNode,float *pPose,float *scale);
	
	void UpdateExternCalibReslt(float *pos);
	void UpdateExternCalib2DReslt(GLfloat *pData,int data_size,GLushort *pIndex,int index_size);
	void EnterMirrorView(Int32 pos);
	
	void Init2DAVMNodeRT();
	
	void Init2DAVMNodeRTDraw(int cameraId);
	void InitRadarAlram(BEV_CONFIG_T  pConfig,ISceneNode* p_render_node,IMesh *pMesh[],INode *OverlayNode[],GlSVRadarAlarm radar_alarm[],IMaterial* material[],unsigned char calib_mode);
    int UpdateRadarAlarm(void);
	void ProcessWheelRoll(unsigned char gear_state, float speed);
	
	void Init2DGroundNodeRT(int j);
	
	void UpdateGoundTextureData(float *pTextureIndex);
	
	void InitAliControlViewNode(BEV_CONFIG_T bev_config);
	
	void  SwitchViewCtrlButton(unsigned char Ctrl_Direct);
	void ProcessViewRot();
	void DoorAction(Int32 Pos);
	void SetCarEnable(Boolean flag);
	
	void ProcessTurnLight(unsigned char turn_light);
	
	void TurnLightAction(Int32 Pos);
	
	void SwitchView2DOnly(unsigned char input_enter_top_flag);
	
	void Calc3DGroundPos(float *pPose,float *pWidth,float*pHeight);
	void Init2DStichAVMNode();
	void Calc3DGroundTexture();
private:
	ISceneNode*			m_sceneNode;
	Int32				m_scenenodeId;
 	ISceneNode*			m_objectNode;
	Int32				m_objectnodeId;
	ISceneNode*			m_viewNode;
	Int32				m_viewNodeId;
	ISceneNode*			m_2DAVMNode;
	Int32				m_2DAVMNodeId;
	Int32				m_GroundNodeId;	
	ISceneNode*			m_2DSingleViewNode;
	Int32				m_2DSingleViewNodeId;	
	ISceneNode*			m_AliCtrlViewNode;
	Int32				m_AliCtrlViewNodeId;		
	IUINode*			m_lisenceNode;
	Int32				m_lisenceNodeId;
	IRenderTarget*		m_lisenceRT;
	IRenderTarget*		m_LuminanceTextureRT;
	IRenderTarget*		m_LuminanceValueRT;
	
	Int32				m_LuminanceTextureNodeId;
	Int32				m_LuminanceValueNodeId;
	
	ISceneNode*			m_LuminanceTextureNode;
	ISceneNode*			m_LuminanceValueNode;
	ISceneNode*			m_2DAVMNodeStich;
	Int32				m_2DAVMNodeStichId;

	ICamera*			m_sceneCamera;
	ICamera*			m_objectCamera;
	ICamera*			m_viewCamera;
	
	ICamera*			m_controlCamera;
	IMesh *m_overlaymesh;
	
	IMesh *m_overlaymesh_2d;
	IMesh *m_overlaymesh_2d_single;
	
	ICamera*			m_2dviewCamera;
	ITextLayer* text;
    ITextLayer *Chinesetext;
	IMesh*				m_planeCrossMesh[3];
	class SVNodeCrossImage *m_crossImage;

	IMesh*				m_planeMesh;
	IMesh*				m_lisenceMesh;
	IMesh*				m_wheelMesh;
	IMesh*				m_arrowMesh;
	IMesh*				m_RadarWaveMesh;
    IMesh*              m_pMeshStichGround[2];
	IRenderTarget*		m_groundRT[2];	
	ISceneNode*			m_GroundNode[2];
    IMaterial*          m_ground_mtl[2];	
    unsigned char       m_render_to_AVM_index;
	INode*				m_Car;
	INode*              m_Car_Window[5];
	
	INode*				m_CarLight;
	INode*				m_CarInternal;
	
	INode*				m_CarDoor[4];
	INode*				m_SUV;
	INode*				m_lisence;	
	INode*				m_ifv;
	INode*				m_radarwave[5];	
	INode*				m_radarwave_bullet[5]; 
	INode*				m_VAN;	
	INode*				m_TRUCK;		
	INode*				m_wheel[16];
	INode*				m_plane[8];
	INode*				m_RadarWavePlane[8];
	INode*				m_SV2Dplane[eMeshIndexMax];
	IMesh*              m_RadarAlarm_Mesh[8];
	INode*              m_RadarAlarm_Node[8];
	IMesh*              m_RadarAlarm_Mesh_2d[8];
	INode*              m_RadarAlarm_Node_2d[8];
		IMesh*          m_RadarAlarm_Mesh_single[8];
	INode*              m_RadarAlarm_Node_single[8];
	IMaterial*          m_RadarAlarm_Mtl[8];
	IMaterial*          m_RadarAlarm_Mtl_2d[8];
	
	IMaterial*          m_RadarAlarm_Mtl_single[8];
	INode*				m_arrow[16];
	IMaterial*			arrowmtl[2];
	INode*				m_radar[5];
	INode*              m_bev[5];
	INode*              m_rsds[5];
	INode*              m_ufo[5];
	INode*              m_line[5];
	INode **m_active_shape_node;
	INode*				m_mapplate;
	INode*				m_position_active_product;
	INode *m_ground;
	INode *m_overlay;
	INode *m_overlay_2d;
	
	INode *m_overlay_2d_single;
	INode*              m_mirror[2];
	GlSV2D  *m_SV2DData;
	unsigned char m_view_control;
	unsigned char m_pre_view_control;
    IMesh *m_groundmesh;
	IMaterial*			m_cvMtl;
	
	IMaterial*			m_SV2DMtl;
	
	IMaterial*			m_3d_ground_Mtl;
	IMaterial*			m_SVSingleMtl;
	
	IMaterial*			m_ControlMtl;
	IMaterial *m_carlightmtl;
	
	IMaterial*			m_RemindMtl;
	Int32 m_iSUVId;
	Int32 m_iVanId;
	Int32 m_iTruckId;
    Int32 m_iRadarId;
	Int32				m_carmtlId;
	Int32				m_carId;
	class RenderDelegateSV*	svdelegate;
	class RenderDelegateCV*	cvdelegate;
	class RenderDelegateSV2D*	sv2Ddelegate;
	class RenderDelegateSV2DImage*	sv2DImagedelegate;
	class SVNode2DStich* m_stich_node;
    class SVNodeEMirror* m_eMirror_node;
	class GlSVOverlayAPA* m_APA_overlay;
	class GlSVOverlayStichWheel *m_stich_wheel;
	IScrollingAnimation*	scrollX;
	IScrollingAnimation*	scrollY;
	IScrollingAnimation*	sliderX;
	IScrollingAnimation*	sliderY;
    BEV_CONFIG_T        m_bev_config;
	Float32				m_freeModeFOV;
	Float32				m_topModeFOV;
	SceneMode			m_mode;
	Int32				m_camPos;
    Int32               m_zoomout;
	Int32               m_lastclickfreeflag;
	unsigned char m_2d_update_flag;
	int m_prevX;
	int m_prevY;
	int m_lastTime;
	int m_view_camera_id;
	unsigned char   m_show_product_flag[PRODUCT_AMOUNT];
	GlSVOverlay m_overlay_data;
	
	GlSVOverlay m_overlay_data_2d;
	
	GlSVOverlay m_overlay_data_2d_single;
	GlSVRadarAlarm m_radar_alram[8];
	GlSVRadarAlarm m_radar_alram_2d[8];
	GlSVRadarAlarm m_radar_alarm_single[8];
	
	INode *m_pPanaramaNode[2];
	INode *m_SkyNode[4];
	unsigned char m_last_view;
    unsigned char m_door_state;
	
    unsigned char m_turnlight_state;
    IMaterial* m_pstich_Mtl;
	class SVNodeSonar *m_pNodeSonar;
    class SVNodeAdasHMI *m_pAdasHmi;
	GlSVLuminance  *m_luminance;
	//for test
	vehicle_param m_veh_param;
    //IMaterial* m_ground_mtl;
};


#endif __SV_SCENE_H__
