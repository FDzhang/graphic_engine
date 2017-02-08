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
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
/*------------------------------------------------------------------------------------------
 * Other Header Files
 *------------------------------------------------------------------------------------------*/
#include "avm/smc.h"
#include "avm/commondef.h"
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

//截自源文件: DataStruct.h
#define num_Channel 3
typedef struct CoefYUV
{	//the Coef for LB balance correction
	//front left
	float32_t K_FL[num_Channel];

	//front right
	float32_t K_FR[num_Channel];

	//right front
	float32_t K_RF[num_Channel];

	//right rear
	float32_t K_RB[num_Channel];

	//rear left
	float32_t K_BL[num_Channel];

	//rear right
	float32_t K_BR[num_Channel];

	//left front
	float32_t K_LF[num_Channel];

	//left rear
	float32_t K_LB[num_Channel];

}CoefYUV;

//截取自源文件:gpu_public_data_struct.h
enum
{
    front_left_door,
    front_right_door,
    rear_left_door,
    rear_right_door,
    door_max
};

typedef struct Overlay_APA_Y
{
    unsigned char stop_sign_flag;
	unsigned char end_parking_sign_flag;
    unsigned char parking_lot_detect_flag;
    unsigned char online_detect_flag;
	int drive_dirction_indicat;
	float scroll_rate;
	unsigned char park_lot_flag;
	float pParkLotPos[8];
	int vP_GearR_Text;
}APAOverlayStruct;

typedef struct GPU_MDL_POSE_T
{
    float front_pose[6];
	float rear_pose[6];
	float left_pose[6];
	float right_pose[6];

}GPU_MDL_POSE;

typedef struct CAN_DATA_T
{
    float vehicle_speed;
	float left_wheel_speed;
	float right_wheel_speed;
	float steering_wheel_angle;
	float yaw_rate;
	unsigned char door_state[door_max];
	unsigned char turn_light_status;
	unsigned char gear_state;
	unsigned char radar_alarm[8];
}CAN_DATA;

#define MAX_TEXT_BOX_LINE_NUM  10
//for text box
typedef struct st_text_box_data_Tag
{
    float pos[2];
	float width;
	float font_size;
	int line_num;
	bool show_flag;
	float text_color[3];
	char *text_content[MAX_TEXT_BOX_LINE_NUM];
	int text_box_id;
}st_text_box_data_T;

typedef struct st_static_icon_box_data_Tag
{
    float pos[2];
	float width;
	float height;
	int show_icon_num;
	bool show_flag;
	char *icon_file_name[MAX_TEXT_BOX_LINE_NUM];
}st_static_icon_box_data_T;

typedef struct st_scroll_box_data_Tag
{
    float pos[2];
	float width;
	float height;
	bool show_flag;
	float scroll_rate;
	bool  horizon;
	char *icon_file_name[2];   // 0 for background icon name, 1 fro scroll icon name
}st_scroll_box_data_T;

#define MAX_ALARM_STATE 3
typedef struct st_LDW_line_data_Tag
{
    float curv;
	float slope;
	float L_offset;
	float R_offset;

	bool show_flag;
    int alarm_state;

	char *icon_file_name[MAX_ALARM_STATE];   // 0 for background icon name, 1 fro scroll icon name
}st_LDW_line_data_T;


#define MAX_BSD_RECT 10
#define MAX_BSD_ALARM_STATE 3

enum
{
    single_view_rect_bottom_left,
    single_view_rect_bottom_right,
    single_view_rect_top_right,
    single_view_rect_top_left,
};

typedef struct st_singleview_rect_data_Tag
{
    float point[8]; //  顺序为左下，右下，右上，左上，
    int alarm_state;
	bool show_flag;
	bool rear_single_view_flag;
	char *icon_file_name[MAX_BSD_ALARM_STATE];
}st_singleview_rect_data_T;

#define MAX_MOVING_RECT_NUM 10
typedef struct st_BSD_radar_icon_data_Tag
{
    float pos[2];
	float width;
	float height;
	float target_width;
	float target_height;
    int alarm_state[MAX_MOVING_RECT_NUM];
	bool show_flag;
	int max_target_num;
	float moving_rect_pos[MAX_MOVING_RECT_NUM][2];
	bool  moving_rect_show_flag[MAX_MOVING_RECT_NUM];
	float moving_rect_alpharate[MAX_MOVING_RECT_NUM];
	char *icon_file_name[MAX_BSD_ALARM_STATE+1]; //0 ---for background picture , i+1 for alarm_state i moving rect texture
}st_BSD_radar_icon_data_T;

typedef struct st_ADAS_Mdl_HMI_Tag
{

    st_LDW_line_data_T *pLDWLine;
	int ldw_line_num;
	st_static_icon_box_data_T *pStaticIcon;
	int icon_num;
	st_text_box_data_T* pTextBox;
	int text_box_num;
	st_singleview_rect_data_T* pSingleviewRect;
	int single_view_rect_num;
	st_scroll_box_data_T* pScrollRect;
	int scroll_rect_num;
	st_BSD_radar_icon_data_T *pBSDRadar;
	int BSD_radar_num;
}st_ADAS_Mdl_HMI_T;
/*------------------------------------------------------------------------------------------
 * Exported Object Declarations
 *------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
 * Exported Function Prototypes
 *------------------------------------------------------------------------------------------*/
DLL_PUBLIC void InitADASMdlHMI(st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum);
DLL_PUBLIC void SetEglBaseParameter(EGLDisplay display,EGLContext context,EGLSurface surf);
DLL_PUBLIC int InitApp(int width,
                       int height,
                       Smc_Cal_T *pSmcCfgm,
                       str_avm_pose_t * pPose);
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

DLL_PUBLIC void UpdateAPAResult(APAOverlayStruct *pAPAReslt);

DLL_PUBLIC void setHMIAlgStatus(int alg_status_value);
DLL_PUBLIC void setHMIChainsStatus(int demo_status_value);
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





