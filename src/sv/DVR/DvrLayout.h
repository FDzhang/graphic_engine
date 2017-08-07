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
#include "GpuElementEventListener.h"
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
        //panel
        void InitMediaPanel(IGUIElement*, const GUI_HANDLE_T parentId);
        //退出按钮
        void InitMediaExit(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnExitEvent(IGUIElement*);
        //设置按钮
        void InitMediaSetting(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnSettingEvent(IGUIElement*);
        //停止按钮
        void InitMediaStop(IGUIElement*, const GUI_HANDLE_T);
        void OnStopEvent(IGUIElement*);
        //下一曲按钮
        void InitMediaNext(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnNextEvent(IGUIElement*);
        //上一部按钮
        void InitMediaPrev(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnPrevEvent(IGUIElement*);
        //前进按钮
        void InitMediaForward(IGUIElement*,const  GUI_HANDLE_T parentId);
        void OnForwardEvent(IGUIElement*);
        //视图切换
        void InitMediaView(IGUIElement*, const GUI_HANDLE_T);
        void OnViewEvent(IGUIElement*);
        //文件列表弹出
        void InitMediaListviewPop(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewPop(IGUIElement*);

        //文件列表
        void InitMediaListview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewEvent(IGUIElement*);

        void InitMediaListviewThumbnail(IGUIElement*, const GUI_HANDLE_T parentId);
        void InitMediaListviewPrev(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewPrevEvent(IGUIElement*);
        void InitMediaListviewNext(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewNextEvent(IGUIElement*);
        void InitMediaListviewOk(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnListviewOkEvent(IGUIElement*);
        
        //播放按钮
        void InitMediaPlay(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnPlayEvent(IGUIElement*);
        
        //进度条
        void InitMediaBar(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnBarEvent(IGUIElement*);

        //视图切换
        void InitMediaTopleftview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnTopleftviewEvent(IGUIElement*);
        void InitMediaToprightview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnToprightviewEvent(IGUIElement*);
        void InitMediaButtomleftview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnButtomleftviewEvent(IGUIElement*);
        void InitMediaButtomrightview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnButtomrightviewEvent(IGUIElement*);
        void InitMediaFullscreenview(IGUIElement*, const GUI_HANDLE_T parentId);
        void OnFullscreenviewEvent(IGUIElement*);
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
        CGPUProcessbar* m_bar;
        CGPUButton*     m_media_play, *m_listview_pop;
        CGPUText*       m_bar_text;
        CGPUListView*   m_listview;
        CGPUImageStream* m_listview_thumbnail;
        AvmEventType    m_event_type;
        CGPUEventListener*     m_topleftView_button;
        CGPUEventListener*     m_toprightView_button;
        CGPUEventListener*     m_buttomleftView_button;
        CGPUEventListener*     m_buttomrightView_button;
        CGPUEventListener*     m_fullscreenView_button;
        
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
