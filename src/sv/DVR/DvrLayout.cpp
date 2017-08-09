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
    CGPUButton* DvrLayout::m_media_play= NULL;
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
        { "CGPUEventListener", "全屏单视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaFullscreenview), (PFOnEvent)(&DvrLayout::OnFullscreenviewEvent), NULL},
        { "CGPUEventListener", "前视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaTopleftview), (PFOnEvent)(&DvrLayout::OnTopleftviewEvent), NULL},
        { "CGPUEventListener", "后视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaToprightview), (PFOnEvent)(&DvrLayout::OnToprightviewEvent), NULL},
        { "CGPUEventListener", "左视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaButtomleftview), (PFOnEvent)(&DvrLayout::OnButtomleftviewEvent), NULL},
        { "CGPUEventListener", "右视图监听控件", 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaButtomrightview), (PFOnEvent)(&DvrLayout::OnButtomrightviewEvent), NULL},
        { "CGPUPanel"      , "多媒体栏"   , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPanel)       , NULL, NULL},
        { "CGPUButton"     , "退出"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaExit)        , (PFOnEvent)(&DvrLayout::OnExitEvent), NULL},
        { "CGPUButton"     , "设置"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaSetting)     , (PFOnEvent)(&DvrLayout::OnSettingEvent), NULL},
        { "CGPUButton"     , "停止"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaStop), (PFOnEvent)(&DvrLayout::OnStopEvent), NULL},
        { "CGPUButton"     , "下一曲"     , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPrev)        , (PFOnEvent)(&DvrLayout::OnPrevEvent), NULL},
        { "CGPUButton"     , "上一曲"     , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaNext)        , (PFOnEvent)(&DvrLayout::OnNextEvent), NULL},
        { "CGPUButton"     , "快进"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaForward)     , (PFOnEvent)(&DvrLayout::OnForwardEvent), NULL},
        { "CGPUButton"     , "视图切换"       , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaView)      , (PFOnEvent)(&DvrLayout::OnViewEvent), NULL},
        { "CGPUButton"    , "播放列表按钮", 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewPop),(PFOnEvent)(&DvrLayout::OnListviewPop), NULL},
        { "CGPUProcessbar" , "进度条"     , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaBar)         , (PFOnEvent)(&DvrLayout::OnBarEvent), NULL},
        { "CGPUButton"     , "播放按钮"   , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaPlay)        , (PFOnEvent)(&DvrLayout::OnPlayEvent), NULL},
        { "CGPUListView"   , "播放列表"   , 1, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListview),(PFOnEvent)(&DvrLayout::OnListviewEvent), NULL},
        //{ "CGPUImageStream", "播放列表缩略图", 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewThumbnail), NULL, NULL},
        { "CGPUButton", "播放列表itemNext" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewPrev), (PFOnEvent)(&DvrLayout::OnListviewPrevEvent), NULL},
        { "CGPUButton", "播放列表itemPrev" , 2, 0, NULL, (PFCreateElement)(&DvrLayout::InitMediaListviewNext), (PFOnEvent)(&DvrLayout::OnListviewNextEvent), NULL},
    };

    DvrLayout::DvrLayout()
        :ILayout(DVRHMI_EVENT_NAME)
        ,m_element_size(sizeof(m_element_info) / sizeof(struct ElementFuntionTable))
        ,m_bar(NULL), m_listview_pop(NULL), m_bar_text(NULL), m_listview(NULL), m_listview_thumbnail(NULL), m_topleftView_button(NULL), m_toprightView_button(NULL), m_buttomleftView_button(NULL), m_buttomrightView_button(NULL), m_fullscreenView_button(NULL)
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
        if(m_bar)
        {
            m_bar->SetValue(whole_time, cur_time);

            whole_time /= 1000;
            cur_time   /= 1000;
            char time_text[32];
            sprintf(time_text, "%u-%u-%u / %u-%u-%u",
                    cur_time / 3600, (cur_time / 60) % 60, cur_time % 60,
                    whole_time / 3600,(whole_time / 60) % 60, whole_time % 60
                );

            //m_bar_text->SetText(time_text);
        }
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
        if(m_listview)
        {
            m_listview->Reset();
            for(int index = 0; index < table.itemNum; index++)
            {
                m_listview->SetItemText(table.item[index].itemName, index);
            }
            m_listview->Sync();
        }
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
        {XR_RES_DVR"media_playback_panel.dds", 0, 80, 100, 560},
    };
    static IGUITexture exit_array_texture[] = {
        {XR_RES_HMI"BC64.dds",  0, 0, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 0, 100, 70}
    };
    static IGUITexture setting_array_texture[] =  {
        {XR_RES_HMI"BC64.dds", 0, 70, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 70, 100, 70},
    };
    static IGUITexture stop_array_texture[] =  {
        {XR_RES_HMI"BC64.dds", 0, 140, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 140, 100, 70},
    };
    static IGUITexture next_array_texture[] = {
        {XR_RES_HMI"BC64.dds", 0, 210, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 210, 100, 70}
    };
    static IGUITexture prev_array_texture[] =  {
        {XR_RES_HMI"BC64.dds", 0, 280, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 280, 100, 70},
    };
    static IGUITexture forward_array_texture[] = {
        {XR_RES_HMI"BC64.dds", 0, 350, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 350, 100, 70}
    };
    static IGUITexture view_array_texture[] = {
        {XR_RES_HMI"BC64.dds", 0, 420, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 420, 100, 70}
    };
    static IGUITexture listviewpop_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds",   0, 490, 100, 70},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 490, 100, 70}
    };

    static IGUITexture listview_array_texture[] = {
        {XR_RES_DVR"media_playback_listview_bg.dds", 80, 368, 300, 267},
        {XR_RES_HMI"BC64.dds", 13, 24, 240, 33},
        {XR_RES_DVR"media_playback_listview_itemSelected.dds",13, 24, 280, 33},
        {XR_RES_HMI"consola.ttf", 0, 0, 0, 0}
    };
    static IGUITexture listview_itemPrev_texture[] =
    {
        {XR_RES_DVR"media_playback_listview_itemPrev.dds", 125, 8, 42, 14},
        {XR_RES_HMI"BC64.dds", 125, 8, 42, 14},
    };
    static IGUITexture listview_itemNext_texture[] =
    {
        {XR_RES_DVR"media_playback_listview_itemNext.dds", 125, 238, 42, 14},
        {XR_RES_HMI"BC64.dds", 125, 238, 42, 14},
    };
    static IGUITexture listviewThumbnail_array_texture[] = {
        {XR_RES_DVR"media_listview_thumbnail.dds", 329, 0, 273, 348},
    };
    
    static IGUITexture play_array_texture[] =  {
        {XR_RES_DVR"media_playback_pause.dds", 660, 330, 60, 60},
        {XR_RES_DVR"media_playback_play.dds", 660, 330, 60, 60}
    };
    
    static IGUITexture bar_array_texture[] = {
        {XR_RES_HMI"BC64.dds", 284, 581, 813, 46},
        {XR_RES_DVR"media_playback_barBase.dds", 0, 10, 812, 10},
        {XR_RES_DVR"media_playback_barSlide.dds", 0, 0, 31, 35},
        {XR_RES_DVR"media_playback_barFinished.dds", 0, 10, 812, 10},
    };

    static IGUITexture topleftview_texture[] = {
        {NULL, 100, 80, 590, 280},
    };
    static IGUITexture toprightview_texture[] = {
        {NULL, 690, 80, 590, 280},
    };
    static IGUITexture buttomleftview_texture[] = {
        {NULL, 100, 360, 590, 280},
    };
    static IGUITexture buttomrightview_texture[] = {
        {NULL, 690, 360, 590, 280},
    };
    static IGUITexture fullscreenview_texture[] = {
        {NULL, 100, 80, 1180, 560},
    };
    //panel按钮
    void DvrLayout::InitMediaPanel(IGUIElement* media_panel, const GUI_HANDLE_T parentId)
    {
        media_panel->Attach(m_node, parentId);
        media_panel->SetTexture(panel_array_texture, 0);
        media_panel->Create(panel_array_texture[0].pos_x,
                            panel_array_texture[0].pos_y,
                            panel_array_texture[0].element_width,
                            panel_array_texture[0].element_height);
    }
    //退出按钮/切换到系统home界面
    void DvrLayout::InitMediaExit(IGUIElement* media_exit, const GUI_HANDLE_T parentId)
    {
        media_exit->Attach(m_node, parentId);
        media_exit->SetTexture(exit_array_texture, GUI_BUTTON_EFFECT_LOCK);
        media_exit->Create(exit_array_texture[0].pos_x,
                           exit_array_texture[0].pos_y,
                           exit_array_texture[0].element_width,
                           exit_array_texture[0].element_height);
    }
    void DvrLayout::OnExitEvent(IGUIElement* exit_button)
    {
        //reset dvr layout的状态
        //bug! 由于退出按钮在down之后，退出界面，无法响应对应的up消息．导致再次进入状态异常
        exit_button->Reset();
        m_media_play->Reset();
        //m_listview_pop->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_EXIT_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    //系统设置按钮
    void DvrLayout::InitMediaSetting(IGUIElement* media_setting, const GUI_HANDLE_T parentId)
    {
        media_setting->Attach(m_node, parentId);
        media_setting->SetTexture(setting_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_setting->Create(setting_array_texture[0].pos_x,
                              setting_array_texture[0].pos_y,
                              setting_array_texture[0].element_width,
                              setting_array_texture[0].element_height);
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
    //停止按钮
    void DvrLayout::InitMediaStop(IGUIElement* media_stop, const GUI_HANDLE_T parentId)
    {
        media_stop->Attach(m_node, parentId);
        media_stop->SetTexture(stop_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_stop->Create(stop_array_texture[0].pos_x,
                           stop_array_texture[0].pos_y,
                           stop_array_texture[0].element_width,
                           stop_array_texture[0].element_height);
    }
    void DvrLayout::OnStopEvent(IGUIElement* setting_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_SETTING_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    //下一曲按钮
    void DvrLayout::InitMediaNext(IGUIElement* media_next, const GUI_HANDLE_T parentId)
    {
        media_next->Attach(m_node, parentId);
        media_next->SetTexture(next_array_texture, 0);
        media_next->Create(next_array_texture[0].pos_x,
                           next_array_texture[0].pos_y,
                           next_array_texture[0].element_width,
                           next_array_texture[0].element_height);
    }
    void DvrLayout::OnNextEvent(IGUIElement* next_button)
    {
        m_media_play->Reset();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_NEXT_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    //上一曲按钮
    void DvrLayout::InitMediaPrev(IGUIElement* media_prev_button, const GUI_HANDLE_T parentId)
    {
        media_prev_button->Attach(m_node, parentId);
        media_prev_button->SetTexture(prev_array_texture, 0);
        media_prev_button->Create(prev_array_texture[0].pos_x,
                                  prev_array_texture[0].pos_y,
                                  prev_array_texture[0].element_width,
                                  prev_array_texture[0].element_height);
    }
    void DvrLayout::OnPrevEvent(IGUIElement* prev_button)
    {
        m_media_play->Reset();
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_PREVE_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
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
    void DvrLayout::OnPlayEvent(IGUIElement* play_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_PLAY_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    //倍速播放按钮
    void DvrLayout::InitMediaForward(IGUIElement* media_forward, const GUI_HANDLE_T parentId)
    {

        media_forward->Attach(m_node, parentId);
        media_forward->SetTexture(forward_array_texture, 0);
        media_forward->Create(forward_array_texture[0].pos_x,
                              forward_array_texture[0].pos_y,
                              forward_array_texture[0].element_width,
                              forward_array_texture[0].element_height);
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
    //切换视图按钮
    void DvrLayout::InitMediaView(IGUIElement* media_view, const GUI_HANDLE_T parentId)
    {

        media_view->Attach(m_node, parentId);
        media_view->SetTexture(view_array_texture, 0);
        media_view->Create(view_array_texture[0].pos_x,
                           view_array_texture[0].pos_y,
                           view_array_texture[0].element_width,
                           view_array_texture[0].element_height);
    }
    void DvrLayout::OnViewEvent(IGUIElement* view_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = DVR_MEDIA_VIEW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void DvrLayout::InitMediaListviewPop(IGUIElement* media_listview_pop_button, const GUI_HANDLE_T parentId)
    {
        media_listview_pop_button->Attach(m_node, parentId);
        media_listview_pop_button->SetTexture(listviewpop_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        media_listview_pop_button->Create(listviewpop_array_texture[0].pos_x,
                                          listviewpop_array_texture[0].pos_y,
                                          listviewpop_array_texture[0].element_width,
                                          listviewpop_array_texture[0].element_height);
        m_listview_pop = dynamic_cast<CGPUButton*>(media_listview_pop_button);
    }
    void DvrLayout::OnListviewPop(IGUIElement* listviewpop_button)
    {
        static bool flag = true;
        m_listview->Enable(flag);
        flag = !flag;
    }


    //列表框
    void DvrLayout::InitMediaListview(IGUIElement* media_listview, const GUI_HANDLE_T parentId)
    {
        media_listview->Attach(m_node, parentId);
        media_listview->SetTexture(listview_array_texture, 0);
        media_listview->Create(listview_array_texture[0].pos_x,
                               listview_array_texture[0].pos_y,
                               listview_array_texture[0].element_width,
                               listview_array_texture[0].element_height);
        media_listview->Enable(false);
        m_listview = dynamic_cast<CGPUListView*>(media_listview);
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
        listviewPrev_button->SetTexture(listview_itemPrev_texture, 0);
        listviewPrev_button->Create(listview_itemPrev_texture[0].pos_x,
                                    listview_itemPrev_texture[0].pos_y,
                                    listview_itemPrev_texture[0].element_width,
                                    listview_itemPrev_texture[0].element_height);
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
    void DvrLayout::InitMediaListviewNext(IGUIElement* listviewNext_button, const GUI_HANDLE_T parentId)
    {
        listviewNext_button->Attach(m_node, parentId);
        listviewNext_button->SetTexture(listview_itemNext_texture, 0);
        listviewNext_button->Create(listview_itemNext_texture[0].pos_x,
                                    listview_itemNext_texture[0].pos_y,
                                    listview_itemNext_texture[0].element_width,
                                    listview_itemNext_texture[0].element_height);
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


    //进度条
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
