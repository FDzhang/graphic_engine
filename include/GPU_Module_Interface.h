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
    TOUR_LARGE_3D_VIEW,
    CAMERA_DEBUG_FRONT_SINGLE_VIEW,  
    CAMERA_DEBUG_REAR_SINGLE_VIEW,
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
	unsigned char iconStatus[MAIN_MENU_ELEM_NUM];
	unsigned char menuVisibility;
}
MainMenuDataT;

typedef struct CtaResultTag
{
	unsigned char ctaStatus;
	void* ctaResult;
}
CtaResultT;	

typedef enum RenderDataTypeTag
{
	RENDER_DATA_CAN = 1,
	RENDER_DATA_MAIN_MENU,
	RENDER_DATA_VIEW_CMD,
	RENDER_DATA_CALIB_RESULT,
	RENDER_DATA_LUMB_RESULT,
	RENDER_DATA_STITCH_ANGLE,
	RENDER_DATA_APA_RESULT,
	RENDER_DATA_CTA_RESULT,
	RENDER_DATA_LKA_LC_RESULT,
	RENDER_DATA_TP_RESULT,
	RENDER_DATA_ALGO_STATUS,
	RENDER_DATA_SONAR_PLD_RESULT,
	RENDER_DATA_SHUT_DOWN_DISPLAY,
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
DLL_PUBLIC int UpdateRenderData(unsigned short dataTypeId, void* renderData, unsigned int dataLength);

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





