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
#include "GpuElementButton.h"
#include "GpuElementProcessbar.h"
#include "GpuElementPanel.h"
#include "GpuElementText.h"
#include "GpuElementListView.h"
#include "GpuElementImageStream.h"

namespace GUI
{
    /** class DVR_Layout
     * \brief AVM DVR 播放layout类，　实现了DVR HMI的显示以及相应控件的切换逻辑与特效逻辑
     */
    class DvrLayout : public ILayout , public IDvrLayout
    {
        DvrLayout();
        ~DvrLayout();
    public:
        static IDvrLayout* GetLayout();
    public: /*IDVR要求的提供外部调用的接口实现*/
        //Layout初始化面板接口
        void Init() {};
        //Layout使能接口
        void Enable(bool flag);
        //进度条控件操作接口
        void SetProcessbarValue(uint32_t whole_time, uint32_t cur_time);
        void InsertProcessbarKeyFrame(void* frame);
        //文本播放列表控件操作接口
        PlaylistItemTable_T* GetPlaylistItemTable();
        void SyncPlaylist();
        void AppendPlaylist(const char* playlist);
        void NextItemInPlaylist();
        void PrevItemInPlaylist();
        //媒体播放按钮控制
        void StartPlay();
        void PausePlay();
        void NextPlay();
        void PrevPlay();
        void FastForwardPlay();
        void RewindPlay();
        void SetPlaylist();
    protected:
        AvmEventType GetAttachEventType() {return m_event_type; }
    private:
        //暂停播放按钮
        void InitMediaPlay(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnPlayEvent(IGUIElement*);
        //下一曲按钮
        void InitMediaNext(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnNextEvent(IGUIElement*);
        //上一部按钮
        void InitMediaPrev(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnPrevEvent(IGUIElement*);
        //前进按钮
        void InitMediaForward(IGUIElement*,const  GUI_HANDLE_T parentId);
        void OnForwardEvent(IGUIElement*);
        //后退按钮
        void InitMediaRewind(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnRewindEvent(IGUIElement*);
        //截图按钮
        void InitMediaScreenShot(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnScreenShotEvent(IGUIElement*);
        //设置按钮
        void InitMediaSetting(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnSettingEvent(IGUIElement*);
        //进度条按钮
        void InitMediaBar(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnBarEvent(IGUIElement*);
        //时间文本控件
        void InitMediaText(IGUIElement*, const GUI_HANDLE_T parentId);

        //状态图标
        void InitMediaStateIcon(IGUIElement*, const GUI_HANDLE_T parentId);
        //panel
        void InitMediaPanel(IGUIElement*, const GUI_HANDLE_T parentId);
        //media_exit
        void InitMediaExit(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnExitEvent(IGUIElement*);

        //文件列表
        void InitMediaListview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewEvent(IGUIElement*);
        void InitMediaListviewPop(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewPop(IGUIElement*);
        void InitMediaListviewThumbnail(IGUIElement*, const GUI_HANDLE_T parentId);
        void InitMediaListviewPrev(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewPrevEvent(IGUIElement*);
        void InitMediaListviewNext(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewNextEvent(IGUIElement*);
        void InitMediaListviewOk(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewOkEvent(IGUIElement*);
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
        CGPUProcessbar* m_bar;
        CGPUButton*     m_media_play;
        CGPUText*       m_bar_text;
        CGPUListView*   m_listview;
        CGPUImageStream* m_listview_thumbnail;
        AvmEventType    m_event_type;

        PlaylistItemTable_T table;
    private:
        static DvrLayout* m_layout;
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
