#ifndef _DVR_LAYOUT_H_ /* { */
#define _DVR_LAYOUT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: DVR_Layout.h
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
 * VERSION: 31 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "Layout.h"
#include "IF_Dvr.h"

namespace GUI
{
    /** class DVR_Layout
     * \brief AVM DVR 播放layout类，　实现了DVR HMI的显示以及相应控件的切换逻辑与特效逻辑
     */
    class DVR_Layout : public ILayout , public IDVR
    {
    public:
        DVR_Layout();
        ~DVR_Layout();

    public: /*IDVR要求的提供外部调用的接口实现*/
        //Layout初始化面板接口
        void Init();
        //Layout使能接口
        void Enable(bool flag);
        //进度条控件操作接口
        void SetProcessbarValue(uint32_t whole_time, uint32_t cur_time);
        void InsertProcessbarKeyFrame(void* frame);
        //文本播放列表控件操作接口
        void SetPlaylist(const char* playlist);
        void AppendPlaylist(const char* playlist);
        //媒体播放按钮控制
        void StartPlay();
        void PausePlay();
        void NextPlay();
        void PrevPlay();
        void FastForwardPlay();
        void RewindPlay();
    private:
        //暂停播放按钮
        void InitMediaPlay(const IGUIElement*, uint32_t parentId);
        //下一曲按钮
        void InitMediaNext(const IGUIElement*, uint32_t parentId);
        //上一部按钮
        void InitMediaPrev(const IGUIElement*, uint32_t parentId);
        //前进按钮
        void InitMediaForward(const IGUIElement*, uint32_t parentId);
        //后退按钮
        void InitMediaRewind(const IGUIElement*, uint32_t parentId);
        //截图按钮
        void InitMediaScreenShot(const IGUIElement*, uint32_t parentId);
        //设置按钮
        void InitMediaSetting(const IGUIElement*, uint32_t parentId);
        //视图切换按钮
        void InitMediaSwitch(const IGUIElement*, uint32_t parentId);
        //进度条按钮
        void InitMediaBar(const IGUIElement*, uint32_t parentI);
        //文件列表
        void InitMediaFileListView(const IGUIElement*, uint32_t parentId);
        //状态图标
        void InitMediaStateIcon(const IGUIElement*, uint32_t parentId);
        //panel
        void InitMediaPanel(const IGUIElement*, uint32_t parentId);
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];

        static uint32_t m_media_panel_start_x, m_media_panel_start_y, m_media_panel_width, m_media_panel_height;
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _DVR_LAYOUT_H_ */
