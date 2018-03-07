#ifndef __DATA_STRUCT_H__
#define __DATA_STRUCT_H__


/*===========================================================================*\
 * FILE: data_struct.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION: This file is all the data struct for 3D AVM useage
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

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
//#include "reuse.h"
#include "bev_config.h"
#include "DataStruct_IF.h"
#include "gpu_public_data_struct.h"
#include "smc.h"
#include "commondef.h"
#include "Database.h"
#include "cta_embed_interface.h"
#include "tp_embed_interface.h"
#include "apa_modules_if.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/
#define MAX_NAME_LENGTH 100

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/
typedef enum GpuErrorCodeTag
{
	LINEAR_VIEW_NODE_NORMAL = 0,
	LINEAR_VIEW_NODE_INIT_FAILED,
	LEFT_RIGHT_VIEW_NORMAL,
	LEFT_RIGHT_VIEW_NODE_INIT_FAILED,
	LARGE_3D_VIEW_NORMAL,
	LARGE_3D_VIEW_NODE_INIT_FAILED,
	CHANGAN_MAIN_HMI_NORMAL,
	CHANGAN_SWITCH_VIEW_HMI_NORMAL,
	S302_MAIN_HMI_NORMAL,
	EP21_MAIN_HMI_NORMAL,
	DEMO_HMI_NORMAL,
	DEMO_LKA_HMI_NORMAL,
	DEMO_SP_HMI_NORMAL,
	TRAINED_PARKING_HMI_NORMAL,
	DEMO_EOL_HMI_NORMAL,
	HMI_ELEMENT_NULL,
	GPU_ERROR_CODE_NUMS,
}
GpuErrorCodeT;

enum
{
    front_camera_index=0,
	rear_camera_index,
	left_camera_index,
	right_camera_index,
	four_camera_index,
	left_right_camera_index,
};
#define TURN_LIGHT_OFF  0
#define TURN_LIGHT_LEFT 1
#define TURN_LIGHT_RIGHT 2

#define DOOR_OPEN 1
#define DOOR_CLOSE 0
#define DRIVER_DOOR_POS 0
#define PASSENGER_DOOR_POS 1
#define REAR_LEFT_DOOR_POS  2
#define REAR_RIGHT_DOOR_POS  3

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

        CameraPosition_BMW_Rear = 0x0000011,
        CameraPosition_BMW_Left = 0x0000012,
        CameraPosition_BMW_Right = 0x0000013,
        CameraPosition_BMW_Left_Front = 0x0000014,
        CameraPosition_BMW_Right_Front = 0x0000015,
        CameraPosition_BMW_Left_Rear = 0x0000016,
        CameraPosition_BMW_Right_Rear = 0x0000017,
        CameraPosition_BMW_3D_Rear = 0x0000018,
};

/*enum
{
LINEAR_FRONT_180_DEGREE_VIEW = 36,
    LINEAR_REAR_180_DEGREE_VIEW,
    LEFT_RIGHT_LINEAR_VIEW,
    TOUR_LARGE_3D_VIEW,
};*/
	/*
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
	BMW_REAR_VIEW,
	BMW_LEFT_VIEW,
	BMW_RIGHT_VIEW,
	BMW_LEFT_FRONT_VIEW,
	BMW_RIGHT_FRONT_VIEW,
	BMW_LEFT_REAR_VIEW,
	BMW_RIGHT_REAR_VIEW,
    BMW_REAR_3D_VIEW,	
	FRONT_LARGE_SINGLE_VIEW,
	REAR_LARGE_SINGLE_VIEW,
	LEFT_LARGE_SINGLE_VIEW,
	RIGHT_LARGE_SINGLE_VIEW,
	CROSS_IMAGE_VIEW,	
	MATTS_VIEW,
	TOTAL_VIEW_NUM,
};*/

typedef enum View_Region_Postion_Tag
{
	REGION_POS_TOP = 0,
	REGION_POS_BOTTOM = 1,
	REGION_POS_LEFT = 2,
	REGION_POS_RIGHT = 3,
}
View_Region_Postion_T;


enum EConfigContent{
eConfigNum,eFrontVertexNum,eFrontIndexNum,eRearVertexNum,eRearIndexNum,eLeftVertexNum,eLeftIndexNum,eRightVertexNum,eRightIndexNum,eConfigEnd};// Shader uniforms

enum MeshIndex{
eFrontMesh,eRearMesh,eLeftMesh,eRightMesh,eFrontLeftMesh,eFrontRightMesh,eRearLeftMesh,eRearRightMesh,eCarImageMesh,eFrontSingle,eRearSingle,eLeftSingle,eRightSingle,eMeshIndexMax,eRightBottomMesh,
};

enum{
	front_lut_index=0,
	rear_lut_index,
	left_lut_index,
	right_lut_index,
	front_left_lut_index,
	front_right_lut_index,
	rear_left_lut_index,
	rear_right_lut_index,
	bc_front_left_lut_index,
	bc_front_right_lut_index,
	bc_rear_left_lut_index,
	bc_rear_right_lut_index,
	bc_left_front_lut_index,
	bc_right_front_lut_index,
	bc_left_rear_lut_index,
	bc_right_rear_lut_index,
};

enum{

   rect_left,
   rect_top,
   rect_right,
   rect_bottom,
};

enum{
    left_turn_max=0,
	right_turn_max,

};
enum{
    left_turn_foward_radius=0,
	right_turn_foward_radius,
	left_turn_backward_radius,
	right_turn_backward_radius,

};

typedef struct {
  float vehicle_length;
  float vehicle_width;
  float vehicle_rear_wheel_to_bumper;
  float vehicle_axis_length;
  float vehicle_front_wheel_to_bumper;
  float vehicle_tyre_radius;
  float vehicle_tyre_width;
  float vehicle_max_steering_wheel[2];
  float vehicle_min_radius[4];

} SV_VEHICLE_PARAM_T;

typedef enum{

   PLATFORM_PC_IMAGE,
   PLATFORM_J5,
   PLATFORM_J6,
   PLATFORM_PC_VIDEO,
   PLATFORM_PC_VIDEO_LIVE,
}PLATFORM_CONFIG;
typedef enum{

   CFG_FROM_SYS,
   CFG_FROM_FILE,
}CFG_SOURCE;


typedef enum{

   SV_3D_VERTEX_SHADER,
   SV_3D_FRAGMENT_SHADER,
   SV_2D_VERTEX_SHADER,
   SV_2D_FRAGMENT_SHADER,
   SV_MIRROR_VERTEX_SHADER,
   SV_MIRROR_FRAGMENT_SHADER,
}SHADER_NAME_INDEX;
// x y SAE coordinate system
enum CALIB_INDEX
{
    POS_CALIB_CX,
	POS_CALIB_CY,
	POS_CALIB_PPMMX,   //pixel per mili-meter x
	POS_CALIB_PPMMY,
};

typedef struct GpuCvPoint2D32f
{
	float x;
	float y;


	GpuCvPoint2D32f(float _x = 0, float _y = 0): x(_x), y(_y) {}

}
GpuCvPoint2D32f;
typedef struct Vehicle_Param_T
{
    float vehicle_length;      //unit mm
	float vehicle_width;
	float vehicle_axis_length;
	float vehicle_rear_wheel_to_bumper;

    float vehicle_front_wheel_to_bumper;
	float vehicle_wheel_radius;
	float vehicle_wheel_width;
	float max_steering_wheel_angle;

}vehicle_param;


typedef struct {
	char file_path[MAX_NAME_LENGTH];
	char exparam_file_name[MAX_NAME_LENGTH];
	char exparam_adjust_file_name[MAX_NAME_LENGTH];
	char lumin_pos_file_name[MAX_NAME_LENGTH];
    char lut_data_file_name[MAX_NAME_LENGTH];
	char lut_index_file_name[MAX_NAME_LENGTH];
	char lut_config_file_name[MAX_NAME_LENGTH];
	char car_pose_file_name[MAX_NAME_LENGTH];
	char car_pose_adjust_file_name[MAX_NAME_LENGTH];
	char car_calib_name[MAX_NAME_LENGTH];
	float front_single_view_rect[4];
	float rear_single_view_rect[4];
	float left_single_view_rect[4];
	float right_single_view_rect[4];
	CFG_SOURCE config_file_source;
	PLATFORM_CONFIG platform_config;
	BEV_CONFIG_T bev_conig;
	SV_VEHICLE_PARAM_T vehicle_para;
	Smc_Cal_T *pSmc;
	Camera_Param_T *pCamParam;
	str_avm_pose_t * pPose;
	StitcherResult *pSticherResult;
} SV_DATA_CONFIG_T;

//world coordinate system x y
typedef struct {
   float center_x;
   float center_y;
   float ppmm_x;
   float ppmm_y;
} AVM_Calib_2D_T;


typedef struct
{
	int CAM_TYPE;

	float CAM_INT_W;
	float CAM_INT_H;
	float CAM_INT_CX;
	float CAM_INT_CY;

	float CAM_SKEW_C;
	float CAM_SKEW_D;

	float CAM_LEN_ORIGIN_HFOV;
	float CAM_LEN_ORIGIN_VFOV;
	int   CAM_LEN_CX;
	int   CAM_LEN_CY;
	float	CAM_SKEW_E;
	int   CAM_LEN_TOP_CUT;

	char CAM_LEN_DIST_LUT[MAX_NAME_LENGTH];

} CAMERA_CFG;

 typedef struct Luminance_balance_tag
{
  int flag;
  float K_FL[3];
  float K_FR[3];
  float K_BL[3];
  float K_BR[3];
  float K_LF[3];
  float K_RF[3];
  float K_LB[3];
  float K_RB[3];
  float Lumin_point_TL[3];
  float Lumin_point_TR[3];
  float Lumin_point_RB[3];
  float Lumin_point_RT[3];
}Lumin_para;

 typedef struct Luminance_balance_value
{
  float Lumin_FL[3];
  float Lumin_FR[3];
  float Lumin_BL[3];
  float Lumin_BR[3];
  float Lumin_LF[3];
  float Lumin_RF[3];
  float Lumin_LB[3];
  float Lumin_RB[3];
}Lumin_value;

enum eCofIlluminace{
 eLeftRear,eRightRear, eRearLeft,eRearRight,eLeftFront,eRightFront,eFrontLeft, eFrontRight,
};

typedef struct SurroundViewCameraParamsTag
{
	float fovx; 
	float aspect; 
	float znear; 
	float zfar;
}
SurroundViewCameraParamsT;

typedef enum VisibilityIndexTag
{	
	PROCESS_TURNLIGHT_FUNC,
	PROCESS_MATTS_FUNC,
	PROCESS_LARGE_SINGLVIEW_FUNC,
	PROCESS_LARGE_3DVIEW_FUNC,
	PROCESS_VIEW_DISPLAY_FUNC,
	PROCESS_GET_STATUS_FUNC,
	PROCESS_FUNC_NUMS,
}
VisibilityIndexT;
/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/


#endif //#ifndef __GL_SV_DEMO_H__
