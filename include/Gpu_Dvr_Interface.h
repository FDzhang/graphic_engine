/*******************************************************************************
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
\*********************************************************************************/
#ifndef _GPU_DVR_INTERFACE_H_
#define _GPU_DVR_INTERFACE_H_

#define NUM_THUMBNAIL_PER_PAGE_EXT	8

typedef struct
{
	char filename[128];
	unsigned char *pPreviewBuf;
	unsigned int ulPreviewHeight;
	unsigned int ulPreviewWidth;
	int color_format;	//0:PREVIEW_RGB565, 1:PREVIEW_RGB888, 2:PREVIEW_RGB32, 3:PREVIEW_YUV420, 4:PREVIEW_YUV422
	unsigned char bValid;
}GUI_OBJ_THUMB_ITEM_EXT;

typedef struct
{
	GUI_OBJ_THUMB_ITEM_EXT item[NUM_THUMBNAIL_PER_PAGE_EXT];
}GUI_OBJ_THUMB_FRAME_INST_EXT;

typedef struct
{
    unsigned char nCurPage;
    unsigned char nTotalPage;
}GUI_OBJ_THUMB_PAGENUM_INST_EXT;

typedef struct
{
	unsigned char check_box[NUM_THUMBNAIL_PER_PAGE_EXT]; //1:select, 0:not select
}GUI_OBJ_THUMB_EDIT_INST_EXT;


typedef struct
{
	char filename[128];
}GUI_OBJ_PLAY_FILENAME_INST_EXT;

typedef struct
{
	unsigned int duration; //in ms
	unsigned int position;
}GUI_OBJ_PLAY_TIME_INST_EXT;

typedef struct
{
    unsigned short 	TimeYear;
    unsigned short 	TimeMon;
    unsigned short 	TimeDay;
    unsigned short 	TimeHour;	
    unsigned short 	TimeMin;
    unsigned short 	TimeSec;	
    unsigned int 	GpsLongitude;
    unsigned int 	GpsLatitude;
    unsigned short 	VehicleSpeed;
    unsigned char 	GearShiftPositon;
    unsigned char 	BrakePedalStatus;
    unsigned char 	DriverBuckleSwitchStatus;
    unsigned char 	LeftTurnLampStatus;
    unsigned char 	RightTurnLampStatus;
    unsigned char   AccePedalPosition;
    unsigned char   EngineThrottlePosition;
}GUI_OBJ_VEHICLE_DATA_INST_EXT;


typedef enum
{
	GUI_VIEW_INDEX_FRONT_EXT,
	GUI_VIEW_INDEX_REAR_EXT,
	GUI_VIEW_INDEX_LEFT_EXT,
	GUI_VIEW_INDEX_RIGHT_EXT,
	GUI_VIEW_INDEX_MATTS_EXT,
	GUI_VIEW_INDEX_NUM_EXT
}GUI_VIEW_INDEX_EXT;

typedef enum
{
	/*general*/
	GUI_OBJ_ID_MAIN_MENU_TAB_EXT = 0,
	GUI_OBJ_ID_WARNING_EXT,
	GUI_OBJ_ID_CARD_STATE_EXT,

	/*record mode*/
	GUI_OBJ_ID_REC_SWITCH_EXT,
	GUI_OBJ_ID_REC_STATE_EXT,
	GUI_OBJ_ID_REC_EVENT_RECORD_STATE_EXT,
	GUI_OBJ_ID_REC_VIEW_INDEX_EXT,
    GUI_OBJ_ID_REC_VEHICLE_DATA_EXT,

	/*thumbnail mode*/
	GUI_OBJ_ID_THUMB_TAB_EXT,
	GUI_OBJ_ID_THUMB_EDIT_EXT,
	GUI_OBJ_ID_THUMB_EDIT_SEL_CHECKBOX_EXT,
	GUI_OBJ_ID_THUMB_FRAME_EXT,
	GUI_OBJ_ID_THUMB_CAPACITY_EXT,
    GUI_OBJ_ID_THUMB_PAGE_NUM_EXT,

	/*playback mode*/
	GUI_OBJ_ID_PB_PLAY_STATE_EXT,
	GUI_OBJ_ID_PB_PLAY_TIMER_EXT,
	GUI_OBJ_ID_PB_PLAY_SPEED_EXT,
	GUI_OBJ_ID_PB_FILENAME_EXT,
	GUI_OBJ_ID_PB_VIEW_INDEX_EXT,
	GUI_OBJ_ID_PB_DC_SWITCH_EXT,
    GUI_OBJ_ID_PB_MODE_EXT,
    GUI_OBJ_ID_PB_VEHICLE_DATA_EXT,

	/*setup*/
	GUI_OBJ_ID_SETUP_SPLIT_TIME_EXT,
	GUI_OBJ_ID_SETUP_VIDEO_QUALITY_EXT,
	GUI_OBJ_ID_SETUP_PHOTO_QUALITY_EXT,
	GUI_OBJ_ID_SETUP_FORMAT_CARD_EXT,

	/*quick menu*/
	GUI_OBJ_ID_DIALOG_EXT, /*dialog*/
    GUI_OBJ_ID_SIDEBAR_EXT,

	GUI_OBJ_ID_NUM_EXT
}GUI_OBJ_ID_EXT;

typedef enum
{
	GUI_OBJ_STATUS_TYPE_U32_EXT,
	GUI_OBJ_STATUS_TYPE_POINTER_EXT,
	GUI_OBJ_STATUS_TYPE_NUM_EXT
}GUI_OBJ_STATUS_TYPE_EXT;

typedef struct
{
	GUI_OBJ_ID_EXT Id;
	char Name[64];
	unsigned char bEnable;
	unsigned char bShow;
	GUI_OBJ_STATUS_TYPE_EXT status_type;
	union
	{
		unsigned int ObjVal;
		void *ptr;
	}uStatus;

}DVR_GRAPHIC_UIOBJ_EXT;

typedef enum
{
	GUI_LAYOUT_RECORD_EXT = 0,
	GUI_LAYOUT_THUMB_EXT,
	GUI_LAYOUT_PLAYBACK_VIDEO_EXT,
	GUI_LAYOUT_PLAYBACK_IMAGE_EXT,
	GUI_LAYOUT_SETUP_EXT,
	GUI_LAYOUT_NUM_EXT
}DVR_GUI_LAYOUT_TYPE_EXT;

typedef struct
{
	DVR_GUI_LAYOUT_TYPE_EXT curLayout;
	DVR_GRAPHIC_UIOBJ_EXT *pTable;
	int ObjNum;
}DVR_GUI_LAYOUT_INST_EXT;


/*
* DVR Example: UpdateRenderDvrData((DVR_GUI_LAYOUT_INST_EXT*)RenderData, sizeof(DVR_GUI_LAYOUT_INST_EXT));
*
*/
#ifdef __cplusplus
extern "C"
{
#endif

	int UpdateRenderDvrData(void* renderData, unsigned int dataLength);
#ifdef __cplusplus
}
#endif


#endif // _GPU_DVR_INTERFACE_H_
