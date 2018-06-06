#ifndef __GPU_MODULE_INTERFACE__
#define __GPU_MODULE_INTERFACE__
/*------------------------------------------------------------------------------------------*\
 * FILE: GPU_Module_Interface.h
 *==========================================================================================
 * Copyright 2016   O-Film Technologies, Inc., All Rights Reserved.
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
 * VERSION: 27 9月 2016 dota2_black
 *------------------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------
 * Standard Header Files
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>
/*------------------------------------------------------------------------------------------
 * Other Header Files
 *------------------------------------------------------------------------------------------*/
#include "avm/smc.h"
#include "commondef.h"
#include "gpu_public_data_struct.h"
#include "TS_config.h"
#include "Gpu_Dvr_Interface.h"
/*------------------------------------------------------------------------------------------
 * Exported Preprocessor #define Constants
 *------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
 * Exported Preprocessor #define MACROS
 *------------------------------------------------------------------------------------------*/
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
/*------------------------------------------------------------------------------------------
 * Exported Type Declarations
 *------------------------------------------------------------------------------------------*/

//重定义, 省去包含egl等头文件
typedef unsigned int GLuint;
typedef void* EGLSurface;
typedef void* EGLContext;
typedef void* EGLDisplay;
    
#include "luminb_result.h"
/*------------------------------------------------------------------------------------------
 * Exported Object Declarations
 *------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
 * Exported Function Prototypes
 *------------------------------------------------------------------------------------------*/

typedef enum RenderInterfaceErrorCodeTag
{
	RENDER_INTERFACE_NO_ERROR = 0,
	RENDER_INTERFACE_INPUT_DATA_NULL,
	RENDER_INTERFACE_RET_NULL,
	RENDER_INTERFACE_ERROR_NUM,
}
RenderInterfaceErrorCodeT;

/*
typedef enum Changan_Track_Cam_Region_Index_Tag
{
    CCAG_TRACK_CAMERA_REGION_FRONT = 0,
    CCAG_TRACK_CAMERA_REGION_REAR,
    CCAG_TRACK_CAMERA_REGION_LEFT,
    CCAG_TRACK_CAMERA_REGION_RIGHT,
    CCAG_TRACK_CAMERA_REGION_FRONT_LEFT,
    CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT,
    CCAG_TRACK_CAMERA_REGION_REAR_LEFT,
    CCAG_TRACK_CAMERA_REGION_REAR_RIGHT,    
    CCAG_TRACK_CAMERA_REGION_NUMS
} Changan_Track_Cam_Region_Index_T;
 
 
 typedef enum Changan_Cam_Region_Index_Tag
 {
    CCAG_CAMERA_REGION_FRONT = 9,
    CCAG_CAMERA_REGION_REAR,
    CCAG_CAMERA_REGION_LEFT,
    CCAG_CAMERA_REGION_RIGHT
 
 } Changan_Cam_Region_Index_T;
 */
typedef enum AvmViewTypeTag
{
    FRONT_SINGLE_VIEW = 0x00000000, // chang an 前单
    REAR_SINGLE_VIEW,// chang an 后单
    LEFT_SINGLE_VIEW,// chang an 左单
    RIGHT_SINGLE_VIEW,// chang an 右单
    FRONT_3D_VIEW,
    REAR_3D_VIEW,
    LEFT_FRONT_3D_VIEW,
    RIGHT_FRONT_3D_VIEW,
    LEFT_REAR_3D_VIEW,
    RIGHT_REAR_3D_VIEW,
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
    BMW_LEFT_VIEW,// chang an 左3D
    BMW_RIGHT_VIEW,// chang an 右3D
    BMW_LEFT_FRONT_VIEW,// chang an 左前3D
    BMW_RIGHT_FRONT_VIEW,// chang an 右前3D
    BMW_LEFT_REAR_VIEW,// chang an 左后3D
    BMW_RIGHT_REAR_VIEW,// chang an 右后3D
    BMW_REAR_3D_VIEW,// chang an 前3D
    FRONT_LARGE_SINGLE_VIEW,
    REAR_LARGE_SINGLE_VIEW,
    LEFT_LARGE_SINGLE_VIEW,
    RIGHT_LARGE_SINGLE_VIEW,
    CROSS_IMAGE_VIEW,
    MATTS_VIEW,
    LINEAR_FRONT_180_DEGREE_VIEW,
    LINEAR_REAR_180_DEGREE_VIEW,
    LEFT_RIGHT_LINEAR_VIEW,
    SIDE_BY_SIDE_SINGLE_VIEW,
    TOUR_LARGE_3D_VIEW,
    CAMERA_DEBUG_FRONT_SINGLE_VIEW,  
    CAMERA_DEBUG_REAR_SINGLE_VIEW,
    DVR_FRONT_SINGLE_VIEW,
    DVR_REAR_SINGLE_VIEW,
    DVR_LEFT_SINGLE_VIEW,
    DVR_RIGHT_SINGLE_VIEW,
    TOTAL_VIEW_NUM,
}
AvmViewTypeT;

typedef struct GpuCalibResultTag
{
	unsigned int** outConfigStore;
	float*		   dataBuffer;
	unsigned short* guiIndexBuffer;
	GPU_MDL_POSE	pose;
}
GpuCalibResultT;

typedef struct StitchResultTag
{
	unsigned char* seamChangeFlag;
	StitcherResult* sticherResult;

}
StitchResultT;

typedef enum LkaLcFuncModeTag
{
	LDW_MODE = 0,
	LKA_MODE,
	LC_MODE,
	LKA_LC_MODE,
	LKA_LC_MODE_NUM,
}
LkaLcFuncModeT;

typedef enum LkaControlStatusTag
{
	LKA_CTRL_UNRELIABLE = 0,
	LKA_CTRL_WARNING,
	LKA_CTRL_CONTROL,
	LKA_CTRL_STATUS_NUM,
}
LkaControlStatusT;

typedef enum LkaAlgoControlModeTag
{
	LKA_ALGO_CTRL_FAIL = 0,
	LKA_ALGO_CTRL_OFF,
	LKA_ALGO_CTRL_STANDBY,
	LKA_ALGO_CTRL_ENABLE,
	LKA_ALGO_CTRL_LKA_STAGE1_LEFT,
	LKA_ALGO_CTRL_LKA_STAGE1_RIGHT,
	LKA_ALGO_CTRL_LKA_STAGE2_LEFT,
	LKA_ALGO_CTRL_LKA_STAGE2_RIGHT,
	LKA_ALGO_CTRL_TRANSITION,
	LKA_ALGO_CTRL_TURN_SIGNAL,
	LKA_ALGO_CTRL_LC_LEFT_LANE_CHANGE,
	LKA_ALGO_CTRL_LC_RIGHT_LANE_CHANGE,
	LKA_ALGO_CTRL_MODE_NUM,
}
LkaAlgoControlModeT;
 
typedef struct LkaLcResultTag
{
	unsigned char funcMode;
	unsigned char funcStatus;
	unsigned char lkaFlag;
	unsigned char workFlag;
	unsigned char ltConfi;
	unsigned char rtConfi;
	unsigned char lkaAlgoMode;
	unsigned char chimeFlag;
	unsigned char errorFlag;
	
}
LkaLcResultT;

/********************************/
/*S302 pd algo gui interface    */
/********************************/
typedef enum PdWarningRegTag
{
	PD_WARNING_REG_FRONT = 0,
	PD_WARNING_REG_REAR,
	PD_WARNING_REG_LEFT,
	PD_WARNING_REG_RIGHT,
	PD_WARNING_REG_MAX_NUMS,
}
PdWarningRegT;

typedef struct PdObjInfoTag
{
    int32_t l32ObjID; //目标ID
    int32_t al32VertexLeftTop[2]; //鱼眼图像上检测目标框左上角点坐标 x,y
    int32_t al32VertexRightTop[2]; //鱼眼图像上检测目标框右上角点坐标 x,y
    int32_t al32VertexRightBtm[2]; //鱼眼图像上检测目标框右下角点坐标 x,y
    int32_t al32VertexLeftBtm[2]; //鱼眼图像上检测目标框左下角点坐标 x,y
} 
PdObjInfoT;

typedef struct PdResultTag
{
	unsigned char pdStatus; //0: stanby, 1:detecting

	unsigned char warningStatus[PD_WARNING_REG_MAX_NUMS]; //0: No objects, 1: warning

	int32_t       objNum;
	PdObjInfoT    objInfo;
}
PdResultT;

typedef enum EolStatusTag
{
    EOL_CALIBRATION_STANDBY = 0,
	EOL_CALIBRATION_ENTER_EOL,	
    EOL_CALIBRATION_PROCESS,
    EOL_CALIBRATION_SUCCEEDED,
    EOL_CALIBRATION_FAILED,
    EOL_STATUS_NUM,
}
EolStatusT;

typedef struct EolResultTag
{
    EolStatusT eolStatus;
}
EolResultT;

typedef enum SystemTouchActionTag
{
	TOUCH_ACTION_NONE = 0,
	TOUCH_ACTION_PRESS,
	TOUCH_ACTION_RELEASE,
	TOUCH_ACTION_MOVE,
	TOUCH_ACTION_NUM,
}
SystemTouchActionT;

typedef struct SystemTouchDataTag
{
	int x;
	int y;
	SystemTouchActionT touchAction;
}
SystemTouchDataT;

typedef struct MouseDataTag
{
	unsigned char visibility;
	SystemTouchDataT touchData;
}
MouseDataT;


typedef enum MainMenuElementIdTag
{
	MAIN_MENU_SETTING = 0,
	MAIN_MENU_LDW,
	MAIN_MENU_LKA,
	MAIN_MENU_LC,
	MAIN_MENU_BSD,
	MAIN_MENU_PARKING_IN,
	MAIN_MENU_PARKING_OUT,
	MAIN_MENU_TRAINED_PARKING,
	MAIN_MENU_CTA,
	MAIN_MENU_PD,
	MAIN_MENU_DVR,
	MAIN_MENU_ONLINE,
	MAIN_MENU_EOL,
	MAIN_MENU_GUIDELINE,
	MAIN_MENU_SEA,
	MAIN_MENU_MOD,

	MAIN_MENU_RADAR_CTRL_AVM,
	MAIN_MENU_TURNLIGHT_CTRL_AVM,
	MAIN_MENU_ELEM_NUM,
}
MainMenuElementIdT;

typedef enum IconStatusTag
{
	ICON_NORMAL = 0,
	ICON_HIGHLIGHT,
	ICON_FAILED,
	ICON_STATUS_NUM,
}
IconStatusT;

typedef struct MainMenuDataTag
{
	IconStatusT iconStatus[MAIN_MENU_ELEM_NUM]; 
	unsigned char menuVisibility;
}
MainMenuDataT;

typedef struct CtaResultTag
{
	unsigned char ctaStatus;
	void* ctaResult;
}
CtaResultT;	

typedef enum VehWheelHubStyleTag
{
	WHEEL_HUB_STYEL_NORMAL = 0,
	WHEEL_HUB_STYEL_MAX_NUMS,
}
VehWheelHubTypeStyleT;

typedef enum VehBodyStyleTag
{
	BODY_STYLE_NORMAL = 0,
	BODY_STYLE_MAX_NUMS,
}
VehWheelHubBodyStyleT;

static const unsigned char VEH_LICENSENUM_MAX_NUMS = 9;
typedef enum VehLicenseNumTag
{
	LICENSE_NUM_INVALID = 0x0,
	LICENSE_NUM_A = 0x1,
	LICENSE_NUM_B = 0x2,
	LICENSE_NUM_C = 0x3,
	LICENSE_NUM_D = 0x4,
	LICENSE_NUM_E = 0x5,
	LICENSE_NUM_F = 0x6,
	LICENSE_NUM_G = 0x7,
	LICENSE_NUM_H = 0x8,
	LICENSE_NUM_I = 0x9,
	LICENSE_NUM_J = 0xA,
	LICENSE_NUM_K = 0xB,
	LICENSE_NUM_L = 0xC,
	LICENSE_NUM_M = 0xD,
	LICENSE_NUM_N = 0xE,
	LICENSE_NUM_O = 0xF,
	LICENSE_NUM_P = 0x10,
	LICENSE_NUM_Q = 0x11,
	LICENSE_NUM_R = 0x12,
	LICENSE_NUM_S = 0x13,
	LICENSE_NUM_T = 0x14,
	LICENSE_NUM_U = 0x15,
	LICENSE_NUM_V = 0x16,
	LICENSE_NUM_W = 0x17,
	LICENSE_NUM_X = 0x18,
	LICENSE_NUM_Y = 0x19,
	LICENSE_NUM_Z = 0x1A,
	LICENSE_NUM_POINT = 0x1B,
	LICENSE_NUM_LINE = 0x1C,
	LICENSE_NUM_0 = 0x1D,
	LICENSE_NUM_1 = 0x1E,
	LICENSE_NUM_2 = 0x1F,
	LICENSE_NUM_3 = 0x20,
	LICENSE_NUM_4 = 0x21,
	LICENSE_NUM_5 = 0x22,
	LICENSE_NUM_6 = 0x23,
	LICENSE_NUM_7 = 0x24,
	LICENSE_NUM_8 = 0x25,
	LICENSE_NUM_9 = 0x26,
	LICENSE_NUM_BJ = 0x27,
	LICENSE_NUM_TJ = 0x28,
	LICENSE_NUM_HEBEI = 0x29,
	LICENSE_NUM_SHANXI = 0x2A,
	LICENSE_NUM_NEIMENG = 0x2B,
	LICENSE_NUM_LIAONING = 0x2C,
	LICENSE_NUM_JILIN = 0x2D,
	LICENSE_NUM_HEILONGJIANG = 0x2E,
	LICENSE_NUM_SHANGHAI = 0x2F,
	LICENSE_NUM_SUZHOU = 0x30,
	LICENSE_NUM_ZHEJIANG = 0x31,
	LICENSE_NUM_ANHUI = 0x32,
	LICENSE_NUM_FUJIAN = 0x33,
	LICENSE_NUM_JIANGXI = 0x34,
	LICENSE_NUM_SHANDONG = 0x35,
	LICENSE_NUM_HENAN = 0x36,
	LICENSE_NUM_XUE = 0x4C,
	LICENSE_NUM_MAX,

}
VehLicenseNumT;


typedef struct VehInfoTag
{
	VehWheelHubBodyStyleT bodyStyle;
	VehWheelHubTypeStyleT wheelHubStyle;
	VehLicenseNumT        licenseNum[VEH_LICENSENUM_MAX_NUMS];
}
VehInfoT;

typedef struct CarTransparentResultTag
{
	unsigned char carTransptStatus;
	void* reverse;
}
CarTransparentResultT;

typedef enum GuideLineCmdTag
{
	GUIDE_LINE_CMD_NOT_ACTIVE = 0x0,
	GUIDE_LINE_CMD_OPEN = 0x1,
	GUIDE_LINE_CMD_CLOSE = 0x2,
	
}GuideLineCmdT;

typedef enum RenderDataTypeTag
{
	RENDER_DATA_CAN = 1,
	RENDER_DATA_MAIN_MENU,
	RENDER_DATA_DVR, //Data struct: DVR_GUI_LAYOUT_INST_EXT
	RENDER_DATA_VIEW_CMD,
	RENDER_DATA_VEHICAL_INFO,
	RENDER_DATA_CAR_TRANSPARENT_RESULT,
	RENDER_DATA_CALIB_RESULT,
	RENDER_DATA_LUMB_RESULT,
	RENDER_DATA_STITCH_ANGLE,
	RENDER_DATA_APA_RESULT,
	RENDER_DATA_CTA_RESULT,
	RENDER_DATA_LKA_LC_RESULT,
	RENDER_DATA_TP_RESULT,
	RENDER_DATA_SEA_RESULT,
	RENDER_DATA_PD_RESULT,
	RENDER_DATA_MOD_RESULT,
	RENDER_DATA_EOL_RESULT,
	RENDER_DATA_ALGO_STATUS,
	RENDER_DATA_SONAR_PLD_RESULT,
	RENDER_DATA_SONAR_RESULT,
	RENDER_DATA_SHUT_DOWN_DISPLAY,
	RENDER_DATA_MOUSE_ICON,
	RENDER_DATA_GUIDE_LINE_CMD,
	RENDER_DATA_CLEAR_BUFFER,
	RENDER_DATA_TIME_STAMP,
	RENDER_DATA_TYPE_NUM,
}
RenderDataTypeT;

typedef struct RenderDataHeaderTag
{
	unsigned short dataTypeId;
	unsigned int   dataLength;
}
RenderDataHeaderT;

typedef struct RenderDataTag
{
	RenderDataHeaderT dataHeader;
	void*             data;
}
RenderDataT;


DLL_PUBLIC int SetRenderData(RenderDataT* pRenderData);	

DLL_PUBLIC int UpdateRenderData(RenderDataTypeT dataTypeId, void* renderData = 0, unsigned int dataLength = 0);

DLL_PUBLIC void InitADASMdlHMI(st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum);
DLL_PUBLIC void SetEglBaseParameter(EGLDisplay display,EGLContext context,EGLSurface surf);
DLL_PUBLIC int InitAppNew(int width, int height, st_GPU_Init_Config_T* gpu_init);
DLL_PUBLIC int UpdateApp(unsigned int view_control_flag,GLuint texYuv[]);
DLL_PUBLIC int OnMouseSingleUp(int x,int y);
DLL_PUBLIC int OnMouseSingleDown(int x,int y);
DLL_PUBLIC int OnMouseSingleMove(int x,int y);

DLL_PUBLIC void UpdateGpuMdlCalibRslt(unsigned int ** out_config_store,
                                      float* data_buffer,
                                      unsigned short* gui_index_buffer,
                                      GPU_MDL_POSE pose);

DLL_PUBLIC void UpdateGpuLuminanceBalanceCof(CoefYUV *lb_result);
DLL_PUBLIC void UpdateGPUMdlCANData(CAN_DATA in_CAN_data);

DLL_PUBLIC void UpdateCustomHMIData();
DLL_PUBLIC void UpdateStichAngle(unsigned char seam_change_flag[],StitcherResult* sticher_result);

DLL_PUBLIC void UpdateAPAResult(APAOverlayStruct *pAPAReslt);

DLL_PUBLIC void UpdateCtaResult(unsigned char pCtaStatus, void* pCtaResult);
DLL_PUBLIC void UpdateTpResult(unsigned char pTpStatus, void* pTpResult);

DLL_PUBLIC void setHMIAlgStatus(int alg_status_value);
DLL_PUBLIC void setHMIChainsStatus(int demo_status_value);
    
DLL_PUBLIC void GetSonarPLDRslt(Radar_PLD_Result *pReslt);

DLL_PUBLIC void SetShutdownDisplay();

/*
param key_mode: 
    0, next_view change mode.
    1, view_index change mode.
*/
DLL_PUBLIC void MockTouchEvent(unsigned char key_value, unsigned char key_mode = 0);

/*------------------------------------------------------------------------------------------
 * Exported Inline Function Definitions and #define Function-Like Macros
 *------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } GPU_Module_Interface_H */





