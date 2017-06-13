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
     * \brief 设置播放器列表控件内容(接口调用将清空播放列表并更新传入的列表内容)
     * \param [IN] playlist　播放列表文件名(protocol+filename) 控件只显示文件名
     */
    virtual void SetPlaylist(const char* playlist) = 0;
    /**
     * \brief 往播放器列表控件添加播放文件
     * \param [IN] playlist 播放器列表文件名(protocol+filename) 控件只显示添加的文件名
     */
    virtual void AppendPlaylist(const char* playlist) = 0;

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
