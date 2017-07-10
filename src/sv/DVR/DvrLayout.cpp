/*------------------------------------------------------------------------------------------
 * FILE: DvrLayout.cpp
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
#include "DvrLayout.h"
#include "IGUIElement.h"
#include "GPU_Module_Interface.h"

namespace GUI
{
    DvrLayout* DvrLayout::m_layout = NULL;
    IDvrLayout* DvrLayout::GetLayout()
    {
        //! 线程安全性不保证
        if(m_layout == NULL)
        {
            m_layout = new DvrLayout;
        }
        return m_layout;
    }

    /**
     * \beief gpu控件元素信息表, 记录控件消息事件响应操作
     */
    struct DvrLayout::ElementFuntionTable DvrLayout::m_element_info[] =
    {
        { "CGPUEventListener", "前视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaTopleftview), (PFOnEvent)(&DvrLayout::OnTopleftviewEvent), NULL},
        { "CGPUEventListener", "后视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaToprightview), (PFOnEvent)(&DvrLayout::OnToprightviewEvent), NULL},
        { "CGPUEventListener", "左视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaButtomleftview), (PFOnEvent)(&DvrLayout::OnButtomleftviewEvent), NULL},
        { "CGPUEventListener", "右视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaButtomrightview), (PFOnEvent)(&DvrLayout::OnButtomrightviewEvent), NULL},
        { "CGPUEventListener", "全屏单视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaFullscreenview), (PFOnEvent)(&DvrLayout::OnFullscreenviewEvent), NULL},
        { "CGPUPanel"      , "多媒体栏"   , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPanel)       , NULL, NULL},
        { "CGPUButton"     , "播放按钮"   , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPlay)        , (PFOnEvent)(&DvrLayout::OnPlayEvent), NULL},
        { "CGPUButton"     , "上一曲"     , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaNext)        , (PFOnEvent)(&DvrLayout::OnNextEvent), NULL},
        { "CGPUButton"     , "下一曲"     , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPrev)        , (PFOnEvent)(&DvrLayout::OnPrevEvent), NULL},
        { "CGPUButton"     , "快进"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaForward)     , (PFOnEvent)(&DvrLayout::OnForwardEvent), NULL},
        { "CGPUButton"     , "快退"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaRewind)      , (PFOnEvent)(&DvrLayout::OnRewindEvent), NULL},
        { "CGPUText"       , "进度条时间" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaText)        , NULL, NULL},
        { "CGPUButton"     , "退出"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaExit)        , (PFOnEvent)(&DvrLayout::OnExitEvent), NULL},
        { "CGPUButton"     , "截图"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaScreenShot)  , (PFOnEvent)(&DvrLayout::OnScreenShotEvent), NULL},
        { "CGPUButton"     , "设置"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaSetting)     , (PFOnEvent)(&DvrLayout::OnSettingEvent), NULL},
        { "CGPUButton"    , "播放列表按钮", 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewPop),(PFOnEvent)(&DvrLayout::OnListviewPop), NULL},
        { "CGPUProcessbar" , "进度条"     , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaBar)         , (PFOnEvent)(&DvrLayout::OnBarEvent), NULL},
        { "CGPUListView"   , "播放列表"   , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListview),(PFOnEvent)(&DvrLayout::OnListviewEvent), NULL},
        //{ "CGPUImageStream", "播放列表缩略图", 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewThumbnail), NULL, NULL},
        { "CGPUButton", "播放列表下翻" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewPrev), (PFOnEvent)(&DvrLayout::OnListviewPrevEvent), NULL},
        { "CGPUButton", "播放列表上翻" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewNext), (PFOnEvent)(&DvrLayout::OnListviewNextEvent), NULL},
        { "CGPUButton", "播放列表确定" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewOk), (PFOnEvent)(&DvrLayout::OnListviewOkEvent), NULL},
        //{ "CGPUIcon"       , "指示灯"     , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaStateIcon), NULL, NULL},
    };

    DvrLayout::DvrLayout()
        :ILayout(DVRHMI_EVENT_NAME)
        ,m_element_size(sizeof(m_element_info) / sizeof(struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    DvrLayout::~DvrLayout()
    {
    }

    void DvrLayout::Enable(bool flag)
    {
        ILayout::EnableLayout(flag);
    }
    void DvrLayout::SetProcessbarValue(uint32_t whole_time, uint32_t cur_time)
    {
        m_bar->SetValue(whole_time, cur_time);

        whole_time /= 1000;
        cur_time   /= 1000;
        char time_text[32];
        sprintf(time_text, "%u-%u-%u / %u-%u-%u",
                cur_time / 3600, (cur_time / 60) % 60, cur_time % 60,
                whole_time / 3600,(whole_time / 60) % 60, whole_time % 60
            );

        m_bar_text->SetText(time_text);
    }
    void DvrLayout::InsertProcessbarKeyFrame(void* frame)
    {

    }
    PlaylistItemTable_T* DvrLayout::GetPlaylistItemTable()
    {
        return &table;
    }
    void DvrLayout::SyncPlaylist()
    {
        m_listview->Reset();
        for(int index = 0; index < table.itemNum; index++)
        {
            m_listview->SetItemText(table.item[index].itemName, index);
        }
        m_listview->Sync();
    }
    void DvrLayout::AppendPlaylist(const char* playlist)
    {

    }
    void DvrLayout::NextItemInPlaylist()
    {
        static bool down = true;
        if(down)
        {
            OnMouseSingleDown(210, 589);
            down =false;
        }
        else
        {
            OnMouseSingleUp(210, 589);
            down = true;
        }
    }
    void DvrLayout::PrevItemInPlaylist()
    {
        static bool down = true;
        if(down)
        {
            OnMouseSingleDown(20, 589);
            down =false;
        }
        else
        {
            OnMouseSingleUp(20, 589);
            down = true;
        }
    }
    /**
     * \brief 内部测试专用接口,  实际采用触摸屏左边进行Layout的坐标响应操作
     */
    void DvrLayout::StartPlay()
    {
        OnMouseSingleDown(640, 670);
    }
    void DvrLayout::PausePlay()
    {
        OnMouseSingleDown(640, 670);
    }
    void DvrLayout::NextPlay()
    {
        OnMouseSingleDown(690, 670);
    }
    void DvrLayout::PrevPlay()
    {
        OnMouseSingleDown(526, 670);
    }
    void DvrLayout::FastForwardPlay()
    {
        OnMouseSingleDown(456, 670);
    }
    void DvrLayout::RewindPlay()
    {
        OnMouseSingleDown(760, 670);
    }
    void DvrLayout::SetPlaylist()
    {
        static bool down = true;
        if(down)
        {
            OnMouseSingleDown(126, 589);
            down =false;
        }
        else
        {
            OnMouseSingleUp(126, 589);
            down = true;
        }
    }
    /**
     * \brief DVR 控件元素操作接口实现，　目前为手动添加并实现，后期可通过UI设计并自动代码生成并添加
     *　　　　主要涉及的是UI的绘制代码，private 不对外暴露实现细节
     */
    static IGUITexture panel_array_texture[] = {
        {XR_RES_DVR"panel.dds", 0, 600, 1280, 120},
    };
    static IGUITexture prev_array_texture[] =  {
        {XR_RES_DVR"media_prev.dds", 526, 46, 64, 48},
        {XR_RES_DVR"media_prev_rewind_hit.dds", 526, 46, 64, 48},
    };
    static IGUITexture play_array_texture[] =  {
        {XR_RES_DVR"media_pause.dds", 590, 20, 100, 100},
        {XR_RES_DVR"media_play.dds", 590, 20, 100, 100}
    };
    static IGUITexture next_array_texture[] = {
        {XR_RES_DVR"media_next.dds", 690, 46, 64, 48},
        {XR_RES_DVR"media_next_forward_hit.dds", 690, 46, 64, 48}
    };
    static IGUITexture forward_array_texture[] = {
        {XR_RES_DVR"media_forward.dds", 824, 46, 64, 48},
        {XR_RES_DVR"media_next_forward_hit.dds", 824, 46, 64, 48}
    };
    static IGUITexture rewind_array_texture[] = {
        {XR_RES_DVR"media_rewind.dds", 760, 46, 64, 48},
        {XR_RES_DVR"media_prev_rewind_hit.dds", 760, 46, 64, 48}
    };
    static IGUITexture bar_array_texture[] = {
        {XR_RES_DVR"barBase.dds", 0, 0, 1280, 18},
        {XR_RES_DVR"barSlide.dds", 0, 0, 1280, 18}
    };
    static IGUITexture exit_array_texture[] = {
        {XR_RES_DVR"media_on.dds",  1200, 33, 74, 74},
        {XR_RES_DVR"media_off.dds", 1200, 33, 74, 74}
    };
    static IGUITexture text_array_texture[] = {
        {XR_RES_DVR"BC64.dds", 240, 50, 80, 40},
        {XR_RES"text_box.ttf", 1200, 30, 80, 80}
    };
    static IGUITexture listviewpop_array_texture[] =
    {
        {XR_RES_DVR"media_listview_pop.dds",   24, 45, 48, 50},
        {XR_RES_DVR"media_listview_poped.dds", 24, 45, 48, 50}
    };
    static IGUITexture listview_array_texture[] = {
        {XR_RES_DVR"media_listview_bg.dds", 0, 200, 602, 350},
        {XR_RES_DVR"media_listview_itemPlay.dds",0, 33, 329, 35},
        {XR_RES_DVR"media_listview_item.dds", 0, 68, 329, 35},
        {XR_RES_DVR"media_listview_itemSelected.dds",0, 68, 329, 35},
        {XR_RES"text_box.ttf", 0, 0, 0, 0}
    };
    static IGUITexture listview_pageprev_texture[] =
    {
        {XR_RES_DVR"media_listview_itemPrev.dds", 25, 0, 33, 33},
        {XR_RES_DVR"BC64.dds", 25, 0, 33, 33},
    };
    static IGUITexture listview_itemok_texture[] =
    {
        {XR_RES_DVR"media_listview_itemOk.dds", 147, 0, 33, 33},
        {XR_RES_DVR"BC64.dds", 147, 0, 33, 33},
    };
    static IGUITexture listview_pagenext_texture[] =
    {
        {XR_RES_DVR"media_listview_itemNext.dds", 270, 0, 33, 33},
        {XR_RES_DVR"BC64.dds", 270, 0, 33, 33},
    };
    static IGUITexture listviewThumbnail_array_texture[] = {
        {XR_RES_DVR"media_listview_thumbnail.dds", 329, 0, 273, 348},
    };
    static IGUITexture topleftview_texture[] = {
        {NULL, 0, 0, 640, 360},
    };
    static IGUITexture toprightview_texture[] = {
        {NULL, 640, 0, 640, 360},
    };
    static IGUITexture buttomleftview_texture[] = {
        {NULL, 0, 360, 640, 360},
    };
    static IGUITexture buttomrightview_texture[] = {
        {NULL, 640, 360, 640, 360},
    };
    static IGUITexture fullscreenview_texture[] = {
        {NULL, 0, 0, 1280, 720},
    };
    void DvrLayout::InitMediaPanel(IGUIElement* media_panel, const GUI_HANDLE_T parentId)
    {
        media_panel->Attach(m_node, parentId);
        media_panel->SetTexture(panel_array_texture, 0);
        media_panel->Create(panel_array_texture[0].pos_x,
                            panel_array_texture[0].pos_y,
                            panel_array_texture[0].element_width,
                            panel_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaPrev(IGUIElement* media_prev_button, const GUI_HANDLE_T parentId)
    {
        media_prev_button->Attach(m_node, parentId);
        media_prev_button->SetTexture(prev_array_texture, 0);
        media_prev_button->Create(prev_array_texture[0].pos_x,
                                  prev_array_texture[0].pos_y,
                                  prev_array_texture[0].element_width,
                                  prev_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaPlay(IGUIElement* media_play_button, const GUI_HANDLE_T parentId)
    {
        media_play_button->Attach(m_node, parentId);
        media_play_button->SetTexture(play_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_play_button->Create(play_array_texture[0].pos_x,
                                  play_array_texture[0].pos_y,
                                  play_array_texture[0].element_width,
                                  play_array_texture[0].element_height);
        IGUIElement* button = media_play_button;
        m_media_play = dynamic_cast<CGPUButton*>(button);
    }
    void DvrLayout::InitMediaNext(IGUIElement* media_next_button, const GUI_HANDLE_T parentId)
    {
        media_next_button->Attach(m_node, parentId);
        media_next_button->SetTexture(next_array_texture, 0);
        media_next_button->Create(next_array_texture[0].pos_x,
                                  next_array_texture[0].pos_y,
                                  next_array_texture[0].element_width,
                                  next_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaForward(IGUIElement* media_forward_button, const GUI_HANDLE_T parentId)
    {

        media_forward_button->Attach(m_node, parentId);
        media_forward_button->SetTexture(forward_array_texture, 0);
        media_forward_button->Create(forward_array_texture[0].pos_x,
                                     forward_array_texture[0].pos_y,
                                     forward_array_texture[0].element_width,
                                     forward_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaRewind(IGUIElement* media_rewind_button, const GUI_HANDLE_T parentId)
    {

        media_rewind_button->Attach(m_node, parentId);
        media_rewind_button->SetTexture(rewind_array_texture, 0);
        media_rewind_button->Create(rewind_array_texture[0].pos_x,
                                    rewind_array_texture[0].pos_y,
                                    rewind_array_texture[0].element_width,
                                    rewind_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaBar(IGUIElement* media_bar, const GUI_HANDLE_T parentId)
    {
        media_bar->Attach(m_node, parentId);
        media_bar->SetTexture(bar_array_texture, 0);
        media_bar->Create(bar_array_texture[0].pos_x,
                          bar_array_texture[0].pos_y,
                          bar_array_texture[0].element_width,
                          bar_array_texture[0].element_height);
        m_bar = dynamic_cast<CGPUProcessbar*>(media_bar);
    }
    void DvrLayout::InitMediaText(IGUIElement* media_text, const GUI_HANDLE_T parentId)
    {
        media_text->Attach(m_node, parentId);
        media_text->SetTexture(text_array_texture, 0);
        media_text->Create(text_array_texture[0].pos_x,
                           text_array_texture[0].pos_y,
                           text_array_texture[0].element_width,
                           text_array_texture[0].element_height);
        media_text -> SetText("/");
        m_bar_text = dynamic_cast<CGPUText*>(media_text);
    }

    void DvrLayout::InitMediaListview(IGUIElement* media_listview, const GUI_HANDLE_T parentId)
    {
        media_listview->Attach(m_node, parentId);
        media_listview->SetTexture(listview_array_texture, 0);
        media_listview->Create(listview_array_texture[0].pos_x,
                               listview_array_texture[0].pos_y,
                               listview_array_texture[0].element_width,
                               listview_array_texture[0].element_height);

        m_listview = dynamic_cast<CGPUListView*>(media_listview);
    }
    void DvrLayout::InitMediaStateIcon(IGUIElement*, const GUI_HANDLE_T parentId)
    {

    }
    void DvrLayout::InitMediaSetting(IGUIElement* media_setting, const GUI_HANDLE_T parentId)
    {

    }
    void DvrLayout::InitMediaScreenShot(IGUIElement* media_screenshot, const GUI_HANDLE_T parentId)
    {

    }
    void DvrLayout::InitMediaExit(IGUIElement* media_exit, const GUI_HANDLE_T parentId)
    {

        media_exit->Attach(m_node, parentId);
        media_exit->SetTexture(exit_array_texture, 0);
        media_exit->Create(exit_array_texture[0].pos_x,
                           exit_array_texture[0].pos_y,
                           exit_array_texture[0].element_width,
                           exit_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaListviewPop(IGUIElement* media_listview_pop_button, const GUI_HANDLE_T parentId)
    {
        media_listview_pop_button->Attach(m_node, parentId);
        media_listview_pop_button->SetTexture(listviewpop_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_listview_pop_button->Create(listviewpop_array_texture[0].pos_x,
                                          listviewpop_array_texture[0].pos_y,
                                          listviewpop_array_texture[0].element_width,
                                          listviewpop_array_texture[0].element_height);
    }
    void DvrLayout::InitMediaListviewThumbnail(IGUIElement* media_thumbnail, const GUI_HANDLE_T parentId)
    {
        media_thumbnail->Attach(m_node, parentId);
        media_thumbnail->SetTexture(listviewThumbnail_array_texture, 0);
        media_thumbnail->Create(listviewThumbnail_array_texture[0].pos_x,
                                listviewThumbnail_array_texture[0].pos_y,
                                listviewThumbnail_array_texture[0].element_width,
                                listviewThumbnail_array_texture[0].element_height);
        m_listview_thumbnail = dynamic_cast<CGPUImageStream*>(media_thumbnail);
        //初始化缩略图地址
        for( int index = 0; index < table.itemNum; index ++)
        {
            table.item[index].addr.itemThumbnailAddr =
                m_listview_thumbnail->GetImageRawData(&table.item[index].thumbnail_width,
                                                      &table.item[index].thumbnail_height);
        }
    }
    void DvrLayout::InitMediaListviewPrev(IGUIElement* listviewPrev_button, const GUI_HANDLE_T parentId)
    {
        listviewPrev_button->Attach(m_node, parentId);
        listviewPrev_button->SetTexture(listview_pageprev_texture, 0);
        listviewPrev_button->Create(listview_pageprev_texture[0].pos_x,
                                    listview_pageprev_texture[0].pos_y,
                                    listview_pageprev_texture[0].element_width,
                                    listview_pageprev_texture[0].element_height);
    }
    void DvrLayout::InitMediaListviewNext(IGUIElement* listviewNext_button, const GUI_HANDLE_T parentId)
    {
        listviewNext_button->Attach(m_node, parentId);
        listviewNext_button->SetTexture(listview_pagenext_texture, 0);
        listviewNext_button->Create(listview_pagenext_texture[0].pos_x,
                                    listview_pagenext_texture[0].pos_y,
                                    listview_pagenext_texture[0].element_width,
                                    listview_pagenext_texture[0].element_height);
    }
    void DvrLayout::InitMediaListviewOk(IGUIElement* listviewOk_button, const GUI_HANDLE_T parentId)
    {
        listviewOk_button->Attach(m_node, parentId);
        listviewOk_button->SetTexture(listview_itemok_texture, 0);
        listviewOk_button->Create(listview_itemok_texture[0].pos_x,
                                  listview_itemok_texture[0].pos_y,
                                  listview_itemok_texture[0].element_width,
                                  listview_itemok_texture[0].element_height);
    }
    void DvrLayout::InitMediaTopleftview(IGUIElement* topleftView_button, const GUI_HANDLE_T parentId)
    {
        topleftView_button->Attach(m_node, parentId);
        topleftView_button->SetTexture(topleftview_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        topleftView_button->Create(topleftview_texture[0].pos_x,
                                   topleftview_texture[0].pos_y,
                                   topleftview_texture[0].element_width,
                                   topleftview_texture[0].element_height);
        m_topleftView_button = dynamic_cast<CGPUEventListener*>(topleftView_button);
    }
    void DvrLayout::InitMediaToprightview(IGUIElement* toprightView_button, const GUI_HANDLE_T parentId)
    {
        toprightView_button->Attach(m_node, parentId);
        toprightView_button->SetTexture(toprightview_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        toprightView_button->Create(toprightview_texture[0].pos_x,
                                    toprightview_texture[0].pos_y,
                                    toprightview_texture[0].element_width,
                                    toprightview_texture[0].element_height);
        m_toprightView_button = dynamic_cast<CGPUEventListener*>(toprightView_button);
    }
    void DvrLayout::InitMediaButtomleftview(IGUIElement* buttomleftView_button, const GUI_HANDLE_T parentId)
    {
        buttomleftView_button->Attach(m_node, parentId);
        buttomleftView_button->SetTexture(buttomleftview_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        buttomleftView_button->Create(buttomleftview_texture[0].pos_x,
                                      buttomleftview_texture[0].pos_y,
                                      buttomleftview_texture[0].element_width,
                                      buttomleftview_texture[0].element_height);
        m_buttomleftView_button = dynamic_cast<CGPUEventListener*>(buttomleftView_button);
    }
    void DvrLayout::InitMediaButtomrightview(IGUIElement* buttomrightView_button, const GUI_HANDLE_T parentId)
    {
        buttomrightView_button->Attach(m_node, parentId);
        buttomrightView_button->SetTexture(buttomrightview_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        buttomrightView_button->Create(buttomrightview_texture[0].pos_x,
                                       buttomrightview_texture[0].pos_y,
                                       buttomrightview_texture[0].element_width,
                                       buttomrightview_texture[0].element_height);
        m_buttomrightView_button = dynamic_cast<CGPUEventListener*>(buttomrightView_button);
    }
    void DvrLayout::InitMediaFullscreenview(IGUIElement* fullscreenview_button, const GUI_HANDLE_T parentId)
    {
        fullscreenview_button->Attach(m_node, parentId);
        fullscreenview_button->SetTexture(fullscreenview_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        fullscreenview_button->Create(fullscreenview_texture[0].pos_x,
                                      fullscreenview_texture[0].pos_y,
                                      fullscreenview_texture[0].element_width,
                                      fullscreenview_texture[0].element_height);
        //fullscreenview_button->Enable(false);
        m_fullscreenView_button = dynamic_cast<CGPUEventListener*>(fullscreenview_button);
    }
    /**
     *  \brief DVR 控件元素事件响应
     */
    void DvrLayout::OnPlayEvent(IGUIElement* play_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_PLAY_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnNextEvent(IGUIElement* next_button)
    {
        m_media_play->Reset();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        if(m_listview->NextItem())
        {
            //填充有效数据
            payload->header.msg_id = DVR_MEDIA_NEXT_BUTTON;
            payload->body.onlyNotify = true;
        }
        else
        {
            //!列表框下移越界，触发向下翻页命令
            payload->header.msg_id = DVR_MEDIA_LIST_VIEW;
            payload->body.dvr_body.listview_file.operation = 0x06;
            payload->body.dvr_body.listview_file.method.file_play = m_listview->GetCurrentIndex();
        }
        PostEvent(event);
    }
    void DvrLayout::OnPrevEvent(IGUIElement* prev_button)
    {
        m_media_play->Reset();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        if(m_listview->PrevItem())
        {
            //填充有效数据
            payload->header.msg_id = DVR_MEDIA_PREVE_BUTTON;
            payload->body.onlyNotify = true;
        }
        else
        {
            //!列表框上移越界，触发向上翻页命令
            payload->header.msg_id = DVR_MEDIA_LIST_VIEW;
            payload->body.dvr_body.listview_file.operation = 0x05;
            payload->body.dvr_body.listview_file.method.file_play = m_listview->GetCurrentIndex();
        }
        PostEvent(event);
    }
    void DvrLayout::OnForwardEvent(IGUIElement* forward_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_FORWARD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnRewindEvent(IGUIElement* rewind_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_REWIND_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnScreenShotEvent(IGUIElement* screenshot_button)
    {
        void* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        Layout_Event_Payload_T* data = (Layout_Event_Payload_T*)(payload);
        //填充有效数据
        data->header.msg_id = DVR_MEDIA_SCREEN_SHOT_BUTTON;
        data->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnSettingEvent(IGUIElement* setting_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_SETTING_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnBarEvent(IGUIElement* bar_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_BAR;
        payload->body.dvr_body.bar.operation = 0x01;
        payload->body.dvr_body.bar.method.jump_time = dynamic_cast<CGPUProcessbar*>(bar_button)->GetPos();
        PostEvent(event);
    }
    void DvrLayout::OnExitEvent(IGUIElement* exit_button)
    {
        m_media_play->Reset();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_EXIT_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnListviewEvent(IGUIElement* list_view)
    {
        //更新缩略图
        //m_listview_thumbnail->UpdateImage();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_LIST_VIEW;
        payload->body.dvr_body.listview_file.operation = 0x04;
        payload->body.dvr_body.listview_file.method.file_play = dynamic_cast<CGPUListView*>(list_view)->GetCurrentIndex();
        PostEvent(event);
    }
    void DvrLayout::OnListviewPrevEvent(IGUIElement* listviewPrev_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_LIST_VIEW;
        payload->body.dvr_body.listview_file.operation = 0x05;
        payload->body.dvr_body.listview_file.method.file_play = m_listview->GetCurrentIndex();
        PostEvent(event);
    }
    void DvrLayout::OnListviewNextEvent(IGUIElement* listviewNext_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_LIST_VIEW;
        payload->body.dvr_body.listview_file.operation = 0x06;
        payload->body.dvr_body.listview_file.method.file_play = m_listview->GetCurrentIndex();
        PostEvent(event);
    }
    void DvrLayout::OnListviewOkEvent(IGUIElement* listviewOk_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_BAR;
        payload->body.dvr_body.listview_file.operation = 0x05;
        payload->body.dvr_body.listview_file.method.file_play = m_listview->GetCurrentIndex();
        PostEvent(event);
    }
    void DvrLayout::OnListviewPop(IGUIElement* listviewpop_button)
    {
        static bool flag = false;
        m_listview->Enable(flag);
        flag = !flag;
    }
    void DvrLayout::OnTopleftviewEvent(IGUIElement* topleftview_button)
    {
        m_topleftView_button->Enable(false);
        m_toprightView_button->Enable(false);
        m_buttomleftView_button->Enable(false);
        m_buttomrightView_button->Enable(false);
        m_fullscreenView_button->Enable(true);

        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_TOPLEFTVIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnToprightviewEvent(IGUIElement* toprightview_button)
    {
        m_topleftView_button->Enable(false);
        m_toprightView_button->Enable(false);
        m_buttomleftView_button->Enable(false);
        m_buttomrightView_button->Enable(false);
        m_fullscreenView_button->Enable(true);
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_TOPRIGHTVIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnButtomleftviewEvent(IGUIElement* buttomleftview_button)
    {
        m_topleftView_button->Enable(false);
        m_toprightView_button->Enable(false);
        m_buttomleftView_button->Enable(false);
        m_buttomrightView_button->Enable(false);
        m_fullscreenView_button->Enable(true);
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_BUTTOMLEFTVIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnButtomrightviewEvent(IGUIElement* buttomrightView_button)
    {
        buttomrightView_button->Enable(false);
        m_topleftView_button->Enable(false);
        m_toprightView_button->Enable(false);
        m_buttomleftView_button->Enable(false);
        m_buttomrightView_button->Enable(false);
        m_fullscreenView_button->Enable(true);
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_BUTTOMRIGHTVIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::OnFullscreenviewEvent(IGUIElement* fullscreenview_button)
    {
        m_topleftView_button->Enable(true);
        m_toprightView_button->Enable(true);
        m_buttomleftView_button->Enable(true);
        m_buttomrightView_button->Enable(true);
        m_fullscreenView_button->Enable(false);
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_SINGLEVIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
};

/**
 * 接口函数，操作Dvr_Layout
 */
extern "C" DLL_PUBLIC IDvrLayout* NewDvrLayout()
{
    return(GUI::DvrLayout::GetLayout());
}

extern "C" DLL_PUBLIC void DeleteDvrLayout(IDvrLayout* dvr)
{
    if(dvr)
    {
        delete dvr;
    }
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
