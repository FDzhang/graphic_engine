#ifndef _IF_DVR_H_ /* { */
#define _IF_DVR_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: IF_Dvr.h
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
 * VERSION: 04 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>

#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))

//! 事件
#define DVRHMI_EVENT_NAME "dvr_hmi"

//! copy from TcpProtocol.h, please careful the same between these files
typedef struct DVR_Event_Header
{
    const uint32_t  magic;
    uint16_t  msg_id;
    //major.minor = 1.0
    const uint8_t   revision_lsb;
    const uint8_t   revision_msb;
    uint16_t  payload_len;
}
DVR_Event_Header_T;


typedef struct DVR_Event_Payload
{
    DVR_Event_Header_T header;
    union
    {
        bool onlyNotify; //true　notify, 接收方不需要更多参数
        struct
        {
            bool status; //当前状态(play or pause)
        }btn_play;

        struct //!　文件列表操作
        {
            uint8_t operation;
            uint8_t __res[3];
            union
            {
                uint8_t fileList;     //获取指定类型的文件列表
                uint32_t file_delete; //删除指定文件号的文件(file_delete 为file索引号)
                uint32_t file_sync;   //同步播放列表
                uint32_t file_play;   //播放指定文件号的文件
                uint32_t file_pageUp; //向上翻页(基于当前选中行为末行进行更新)
                uint32_t file_pageDown;//向下翻页(基于当前选中行为首行进行更行)
            }method;
        }listview_file; //暂定，需要文件列表访问方法

        struct //!　进度条操作
        {
            uint8_t operation;
            uint8_t __res[3];
            union
            {
                uint32_t jump_time;
            }method;
        }bar;
    }body;
}DVR_Event_Payload_T;



typedef enum
{
    DVR_MEDIA_PLAY_BUTTON,        /*播放*/
    DVR_MEDIA_PREVE_BUTTON,       /*上一个*/
    DVR_MEDIA_NEXT_BUTTON,        /*下一个*/
    DVR_MEDIA_FORWARD_BUTTON,     /*快进*/
    DVR_MEDIA_REWIND_BUTTON,      /*快退*/
    //DVR_MEDIA_TEXT_LABEL,       /*进度条时间*/
    DVR_MEDIA_EXIT_BUTTON,        /*退出*/
    DVR_MEDIA_SCREEN_SHOT_BUTTON, /*截图*/
    DVR_MEDIA_SETTING_BUTTON,     /*设置*/
    DVR_MEDIA_BAR,                /*进度条 */
    DVR_MEDIA_LIST_VIEW,          /*文件列表*/
    //DVR_MEDIA_STATE_ICON,       /*状态图标*/
    //DVR_MEDIA_PANEL,
    //DVR_DEBUG_PANEL,             /*dvr 调试板*/
    DVR_MEDIA_MAX_NUM = 0xFFFFFFFF
}EVENT_ELEMENT_ID_T;

typedef struct
{
    //暂时固定itemNum, 后期可调
    const uint32_t maxItemNum = 9;
    uint32_t itemNum = maxItemNum;
    struct
    {
        char* itemName = "";
        union
        {
            char*    itemThumbnailAddr; //GraphicEngine申请的绑定纹理的buf
            uint32_t surfaceTexId; //GpuTask绑定的surface texture
        }addr;
    }item[9];
}PlaylistItemTable_T;

/**
 * \brief IDVR 暴露操作DVR Layout的接口
 */
class IDVR
{
public:
    /**
     * \brief 初始化DVR Layout (目前不执行操作，由于目前GPU内部初始化序列混乱，待整改)
     */
    virtual void Init() = 0;
    /**
     * \brief 使能DVR Layout的显示，DVR Layout控制DVR控件的内部更新逻辑，外部操作不涉及控件的更新逻辑
     * \param [IN] flag true则Layout显示
     */
    virtual void Enable(bool flag) = 0;
    /**
     * \brief 更新进度条位置
     */
    virtual void SetProcessbarValue(uint32_t whole_time, uint32_t cur_time) = 0;
    /**
     * \brief 在当前进度条的位置显示一帧图像
     */
    virtual void InsertProcessbarKeyFrame(void* frame) = 0;

    /**
     * \brief 获取播放列表itemTable
     * 
     */
    virtual PlaylistItemTable_T* GetPlaylistItemTable() = 0;
   /**
     * \brief 同步播放器列表控件内容(接口调用将清空列表控件的item并更新itemTable至列表中)
     * 
     */
    virtual void SyncPlaylist() = 0;
    /**
     * \brief 往播放器列表控件添加播放文件
     * \param [IN] playlist 播放器列表文件名(protocol+filename) 控件只显示添加的文件名
     */
    //virtual void AppendPlaylist(const char* playlist) = 0;
    //virtual void NextItemInPlaylist() = 0;
    //virtual void PrevItemInPlaylist() = 0;
    
    /**
     * \brief　媒体播放控制，　播放/暂停/上一部/下一部/快进/快退　播放 (debug调试使用)
     *         正常情况是不需要此操作接口(由触摸产生的坐标触发按钮事件响应完成状态更新并更新事件逻辑)
     *         本接口通过模拟产生触摸事件仿真控制
     */
    virtual void StartPlay() = 0;
    virtual void PausePlay() = 0;
    virtual void NextPlay() = 0;
    virtual void PrevPlay() = 0;
    virtual void FastForwardPlay() = 0;
    virtual void RewindPlay() = 0;
    virtual void SetPlaylist() = 0;
};

//! 接口函数
extern "C" DLL_PUBLIC IDVR* NewDvrLayout(void);
extern "C" DLL_PUBLIC void  DeleteDvrLayout(IDVR* dvr);
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IF_DVR_H_ */
