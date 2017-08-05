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
#include "GpuAvmEvent.h"

//! 事件
#define DVRHMI_EVENT_NAME "dvr_hmi"

typedef struct
{
    //暂时固定itemNum, 后期可调
    const uint32_t maxItemNum = 6;
    uint32_t itemNum = maxItemNum;
    struct
    {
        //设置字符串名字地址
        char* itemName = "";
        uint32_t thumbnail_width;
        uint32_t thumbnail_height;
        union
        {
            char*    itemThumbnailAddr; //GraphicEngine申请的绑定纹理的buf
            uint32_t surfaceTexId; //GpuTask绑定的surface texture
        }addr;
    }item[8];
}PlaylistItemTable_T;
/**
 * \brief IDVR 暴露操作DVR Layout的接口
 */
class IDvrLayout
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
};

//! 接口函数
extern "C" DLL_PUBLIC IDvrLayout* NewDvrLayout(void);
extern "C" DLL_PUBLIC void  DeleteDvrLayout(IDvrLayout* dvr);
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IF_DVR_H_ */
