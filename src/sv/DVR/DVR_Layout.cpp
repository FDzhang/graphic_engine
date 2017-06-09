/*------------------------------------------------------------------------------------------
 * FILE: DVR_Layout.cpp
 *==========================================================================================
 * Copyright 2017  O-Film Technologies, Inc., All Rights Reserved.
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
#include "DVR_Layout.h"
#include "IGUIElement.h"
#include "GPU_Module_Interface.h"

namespace GUI
{
    /**
     * \beief gpu控件元素信息表, 记录控件消息事件响应操作 
     *        对外操作接口的实现, 任何通过控件触发的消息都将从此处静态注册并返回需要的结果到system manager
     */
    struct ILayout::ElementFuntionTable DVR_Layout::m_element_info[] =
    { 
        { "CGPUPanel"      , "多媒体栏"   , 1, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaPanel)       , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUButton"     , "播放按钮"   , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaPlay)        , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUButton"     , "上一曲"     , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaNext)        , (PFOnEvent)(&DVR_Layout::OnPlayEvent), NULL},
        { "CGPUButton"     , "下一曲"     , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaPrev)        , (PFOnEvent)(&DVR_Layout::OnPlayEvent), NULL},
        { "CGPUButton"     , "快进"       , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaForward)     , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUButton"     , "快退"       , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaRewind)      , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUText"       , "进度条时间" , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaText)        , NULL, NULL},
        { "CGPUButton"     , "退出"       , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaExit)        , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUButton"     , "截图"       , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaScreenShot)  , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUButton"     , "设置"       , 2, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaSetting)     , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "CGPUProcessbar" , "进度条"     , 1, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaBar)         , (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        //{ "CGPUListView"   , "播放列表"   , 1, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaFileListView),(PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        //{ "CGPUIcon"       , "指示灯"     , 1, 0, NULL, (PFCreateElement)(&DVR_Layout::InitMediaStateIcon),   (PFOnEvent)(&DVR_Layout::OnEvent), NULL},
        { "NULL", "NULL", 1, 0, NULL, NULL, NULL, NULL}
    };

    uint32_t DVR_Layout::m_media_panel_start_x = 0;
    uint32_t DVR_Layout::m_media_panel_start_y = 620;
    uint32_t DVR_Layout::m_media_panel_width = 1280;
    uint32_t DVR_Layout::m_media_panel_height = 100;
    
    DVR_Layout::DVR_Layout()
        :ILayout(m_element_info, sizeof(m_element_info) / sizeof(struct ElementFuntionTable))
        ,m_element_size(sizeof(m_element_info) / sizeof(struct ElementFuntionTable))
    {
    }

    DVR_Layout::~DVR_Layout()
    {
        
    }
    
    void DVR_Layout::Enable(bool flag)
    {
        ILayout::EnableLayout(flag);
    }
    void DVR_Layout::SetProcessbarValue(uint32_t whole_time, uint32_t cur_time)
    {
        m_bar->SetValue(whole_time, cur_time);
        char time_text[24];
        sprintf(time_text, "%u/%u", whole_time, cur_time);
        m_bar_text->SetText(time_text);
    }
    void DVR_Layout::InsertProcessbarKeyFrame(void* frame)
    {
        
    }
    void DVR_Layout::SetPlaylist(const char* playlist)
    {
        
    }
    void DVR_Layout::AppendPlaylist(const char* playlist)
    {
        
    }
    
    /**
     * \brief 内部测试专用接口,  实际采用触摸屏左边进行Layout的坐标响应操作
     */
    void DVR_Layout::StartPlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }
    void DVR_Layout::PausePlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }
    void DVR_Layout::NextPlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2 + 50,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }
    void DVR_Layout::PrevPlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2 - 114,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }
    void DVR_Layout::FastForwardPlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2 + 184,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }
    void DVR_Layout::RewindPlay()
    {
        OnMouseSingleDown(m_media_panel_start_x + m_media_panel_width / 2 + 120,
                          m_media_panel_start_y + m_media_panel_height / 2);
    }


    /**
     * \brief DVR 控件元素操作接口实现，　目前为手动添加并实现，后期可通过UI设计并自动代码生成并添加
     *　　　　主要涉及的是UI的绘制代码，private 不对外暴露实现细节
     */
    void DVR_Layout::InitMediaPanel(const IGUIElement* media_panel, uint32_t parentId)
    {
        IGUITexture array_texture_panel[] = { XR_RES_DVR"panel.dds"};
        media_panel->Attach(m_node, parentId);
        media_panel->SetTexture(array_texture_panel, 0);
        media_panel->Create(m_media_panel_start_x, m_media_panel_start_y, m_media_panel_width, m_media_panel_height);
    }
    void DVR_Layout::InitMediaPrev(const GUI::IGUIElement* media_prev_button, uint32_t parentId)
    {
        IGUITexture prev_array_texture[] = { XR_RES_DVR"media_prev.dds", XR_RES_DVR"media_prev_rewind_hit.dds"};
        media_prev_button->Attach(m_node, parentId);
        media_prev_button->SetTexture(prev_array_texture, 0);
        media_prev_button->Create(m_media_panel_width / 2 - 114,
                                  m_media_panel_height / 2 - 24,
                                  64,
                                  48);
    }
    void DVR_Layout::InitMediaPlay(const GUI::IGUIElement* media_play_button, uint32_t parentId)
    {
        IGUITexture play_array_texture[] = { XR_RES_DVR"media_pause.dds", XR_RES_DVR"media_play.dds"};
        media_play_button->Attach(m_node, parentId);
        media_play_button->SetTexture(play_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_play_button->Create(m_media_panel_width / 2 - 50,
                                  m_media_panel_height / 2 - 50,
                                  100,
                                  100);
        IGUIElement* button = media_play_button;
        m_media_play = dynamic_cast<CGPUButton*>(button);
    }
    void DVR_Layout::InitMediaNext(const GUI::IGUIElement* media_next_button, uint32_t parentId)
    {
        IGUITexture next_array_texture[] = { XR_RES_DVR"media_next.dds", XR_RES_DVR"media_next_forward_hit.dds"};
        media_next_button->Attach(m_node, parentId);
        media_next_button->SetTexture(next_array_texture, 0);
        media_next_button->Create(m_media_panel_width / 2 + 50,
                                  m_media_panel_height / 2  - 24,
                                  64,
                                  48);
    }
    void DVR_Layout::InitMediaForward(const GUI::IGUIElement* media_forward_button, uint32_t parentId)
    {
        IGUITexture prev_array_texture[] = { XR_RES_DVR"media_forward.dds", XR_RES_DVR"media_next_forward_hit.dds"};
        media_forward_button->Attach(m_node, parentId);
        media_forward_button->SetTexture(prev_array_texture, 0);
        media_forward_button->Create(m_media_panel_width / 2 + 184,
                                     m_media_panel_height / 2 - 24,
                                     64,
                                     48);
    }
    void DVR_Layout::InitMediaRewind(const GUI::IGUIElement* media_rewind_button, uint32_t parentId)
    {
        IGUITexture prev_array_texture[] = { XR_RES_DVR"media_rewind.dds", XR_RES_DVR"media_prev_rewind_hit.dds"};
        media_rewind_button->Attach(m_node, parentId);
        media_rewind_button->SetTexture(prev_array_texture, 0);
        media_rewind_button->Create(m_media_panel_width / 2 + 120,
                                    m_media_panel_height / 2 - 24,
                                    64,
                                    48);
    }
    void DVR_Layout::InitMediaBar(const GUI::IGUIElement* media_bar, uint32_t parentId)
    {
        IGUITexture array_texture_bar[] = { XR_RES_DVR"barBase.dds", XR_RES_DVR"barSlide.dds"};
        media_bar->Attach(m_node, parentId);
        media_bar->SetTexture(array_texture_bar, 0);
        media_bar->Create(m_media_panel_start_x, m_media_panel_start_y - 18, 1280, 20);
        IGUIElement* bar = media_bar;
        m_bar = dynamic_cast<CGPUProcessbar*>(bar);
    }
    void DVR_Layout::InitMediaText(const IGUIElement* media_text, uint32_t parentId)
    {
        IGUITexture array_texture_bar[] = {XR_RES_DVR"BC64.dds", XR_RES"text_box.ttf"};
        media_text->Attach(m_node, parentId);
        media_text->SetTexture(array_texture_bar, 0);
        media_text->Create( m_media_panel_width / 2 - 400, m_media_panel_height / 2 - 20, 80, 40);
        media_text -> SetText("/");
        IGUIElement* element = media_text;
        m_bar_text = dynamic_cast<CGPUText*>(element);
    }
    
    void DVR_Layout::InitMediaFileListView(const IGUIElement*, uint32_t parentId)
    {
        
    }
    void DVR_Layout::InitMediaStateIcon(const IGUIElement*, uint32_t parentId)
    {
        
    }
    void DVR_Layout::InitMediaSetting(const IGUIElement* media_setting, uint32_t parentId)
    {
        
    }
    void DVR_Layout::InitMediaScreenShot(const IGUIElement* media_screenshot, uint32_t parentId)
    {
        
    }
    void DVR_Layout::InitMediaExit(const IGUIElement* media_exit, uint32_t parentId)
    {
        IGUITexture exit_array_texture[] = { XR_RES_DVR"media_on.dds", XR_RES_DVR"media_off.dds"};
        media_exit->Attach(m_node, parentId);
        media_exit->SetTexture(exit_array_texture, 0);
        media_exit->Create(m_media_panel_width - 64,
                                     m_media_panel_height / 2 - 24,
                                     64,
                                     64);
    }
    //临时添加(由于没有反馈事件传递机制)
    void DVR_Layout::OnPlayEvent(const  IGUIElement* element, const uint32_t type)
    {
        if(type == TouchEvent_Down)
        {
            m_media_play->Reset();
        }
    }
};

/**
 * 接口函数，操作Dvr_Layout
 */
extern "C" DLL_PUBLIC IDVR* NewDvrLayout()
{
    GUI::DVR_Layout* layout = new GUI::DVR_Layout;
    if(layout)
    {
        return layout;
    }
    else
        return NULL;
}

extern "C" DLL_PUBLIC void DeleteDvrLayout(IDVR* dvr)
{
    if(dvr)
    {
        delete dvr;
        dvr = NULL;
    }
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
