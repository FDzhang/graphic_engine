#ifndef _GPUAVMEVENT_H_ /* { */
#define _GPUAVMEVENT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuAvmEvent.h
 *==========================================================================================
 * Copyright 2017   O-Film Technologies, Inc., All Rights Reserved.
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
 * VERSION: 22 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>

#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))

#define SURROUND_VIEW_EVENT_NAME "surround_view_event"
#define TPHMI_EVENT_NAME "tp_hmi"

/*********************************************************************************
 * \brief Gpu event payload data结构体
 *　　　  msg header使用的是Tcp传输控制头，目的在提供手机通过SystemManager透传的可能性
 */
typedef struct Gpu_Event_Header
{
    const uint32_t magic;       //magic number
    uint16_t       msg_id;
    const uint8_t  revision_lsb;//版本号
    const uint8_t  revision_msb;
    uint16_t       payload_len; //body len
}
    Gpu_Event_Header_T;

typedef struct
{
    Gpu_Event_Header_T header;
    union
    {
        bool onlyNotify; //只是发送notify通知，不要求对Event msg解析
        unsigned char viewIndex;
        union  //! 通用AvmEvent消息
        {
            struct
            {
                uint8_t operation;
                uint8_t __res[3];
                union
                {
                    uint8_t debug_target;
                    uint8_t debug_level;
                    uint8_t debug_status;
                }method;
                uint8_t debug_resolve[7];
            }debug_panel;
        }general_body;
        //struct //! 算法layout的AvmEvent消息
        //{
        //}algo_body;
		struct
		{
			uint8_t tp_status;
			uint8_t capture_image_status;
			uint8_t navigating_status;
			uint8_t control_status;
			uint8_t parking_status;
		}tp_body;

        //! DVR Layout Event 消息
        union
        {
            struct
            {
                bool status; //当前状态(play or pause), 用于纠正媒体播放状态
            }btn_play;

            struct //!　文件列表操作
            {
                uint8_t operation;
                uint8_t __res[3];
                union
                {
                    //接口有待讨论
                    uint32_t fileList;     //文件类型过滤
                    uint32_t file_delete;  //删除指定文件号的文件
                    uint32_t file_sync;    //同步播放列表
                    uint32_t file_play;    //播放指定index的文件
                    uint32_t file_pageUp;  //向上翻页(基于当前选中行为末行进行更新)
                    uint32_t file_pageDown;//向下翻页(基于当前选中行为首行进行更行)
                }method;
            }listview_file; //暂定，需要文件列表访问方法

            struct //!　进度条操作
            {
                uint8_t operation;
                uint8_t processBarMode; //进度条模式(0. 单纯时间跳转模式／1. 关键帧跳转模式)
                uint8_t __res[2];
                union
                {
                    uint32_t jump_time; //进度条调节后up事件触发当前需要跳转的事件/us
                }method;
            }bar;
        }dvr_body;
    }body;
}Layout_Event_Payload_T;

/*********************************************************************************
 * \brief AvmEvent payload的msgid
 */
typedef enum
{
    GENERAL_EVENT_ELEMENT_LAYOUT = 0x0,
    DEBUG_PANEL,
}GENERAL_EVENT_ELEMENT_ID_T;

typedef enum
{
    ALGO_EVENT_ELEMENT_LAYOUT = 0x10, //ALGO_EVENT_ELEMENT_ID_T起始索引id
    ALGO_EXIT_BUTTON,
    ALGO_LDW_BUTTON,
    ALGO_BSD_BUTTON,
    ALGO_OC_BUTTON,
    ALGO_APA_BUTTON,
    ALGO_APA_IN_BUTTON,
    ALGO_APA_OUT_BUTTON,
    ALGO_RECORD_BUTTON,
    ALGO_WIFI_BUTTON,
    ALGO_CTA_BUTTON,
    ALGO_TP_BUTTON,
    ALGO_LKA_BUTTON,
    ALGO_LC_BUTTON,
    ALGO_PD_BUTTON,
    ALGO_EOL_BUTTON,
    CMD_2D_VIEW_MODE,
    CMD_3D_VIEW_MODE,
    CMD_LARGE_SINGLE_VIEW_MODE,
    CMD_LARGE_180_VIEW_MODE,
    CMD_SETTING_PAGE,
    CMD_GUIDE_LINE_BUTTON,
    CMD_TURN_LIGHT_CONTRL_AVM,
    CMD_RADAR_CONTRL_AVM, 
    CMD_EXIT_AVM,
    CMD_VIEW_INDEX,
    FULL_SCREEN_3D_TOUCHED = 0x50,
}HMI_EVENT_ELEMENT_ID_T;

typedef enum
{
    DVR_EVENT_ELEMENT_LAYOUT = 0x20,
    DVR_MEDIA_PLAY_BUTTON,        /*播放*/
    DVR_MEDIA_PREVE_BUTTON,       /*上一个*/
    DVR_MEDIA_NEXT_BUTTON,        /*下一个*/
    DVR_MEDIA_FORWARD_BUTTON,     /*快进*/
    DVR_MEDIA_REWIND_BUTTON,      /*快退*/
    DVR_MEDIA_EXIT_BUTTON,        /*退出*/
    //DVR_MEDIA_SCREEN_SHOT_BUTTON, /*截图*/
    DVR_MEDIA_SETTING_BUTTON,     /*设置*/
    DVR_MEDIA_BAR,                /*进度条 */
    DVR_MEDIA_LIST_VIEW,          /*文件列表*/
    //DVR_MEDIA_STATE_ICON,       /*状态图标*/
    DVR_MEDIA_TOPLEFTVIEW_BUTTON, /*田字格左上视图按钮*/
    DVR_MEDIA_TOPRIGHTVIEW_BUTTON, /*田字格右上视图按钮*/
    DVR_MEDIA_BUTTOMLEFTVIEW_BUTTON, /*田字格左下视图按钮*/
    DVR_MEDIA_BUTTOMRIGHTVIEW_BUTTON, /*田字格右下试图按钮*/
    DVR_MEDIA_SINGLEVIEW_BUTTON, /*单视图状态按钮*/
    DVR_MEDIA_VIEW_BUTTON, /*回放展现的view形式*/
    DVR_MEDIA_MAX_NUM = 0xFFFFFFFF
}DVR_EVENT_ELEMENT_ID_T;

typedef enum
{
	SURROUND_VIEW_3D_FULL_SCREEN= 0x40,
}
SURROUND_VIEW_EVENT_ELEMENT_ID_T;

typedef enum
{
	ALGO_TP_CAPTURE_IMAGE_ICON = 0x30,
	ALGO_TP_NAVIGATING_ICON,
	ALGO_TP_CONTROL_ICON,
	ALGO_TP_PARKING_ICON,
}
ALGO_TP_EVENT_ELEMENT_ID_T;


/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUAVMEVENT_H_ */
