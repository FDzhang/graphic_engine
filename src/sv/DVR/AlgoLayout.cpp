/*------------------------------------------------------------------------------------------
 * FILE: Algo_Layout.cpp
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
 * VERSION: 21 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include "AlgoLayout.h"

namespace GUI
{
    AlgoLayout* AlgoLayout::m_layout = NULL;
    IAlgoLayout* AlgoLayout::GetLayout()
    {
        if(m_layout == NULL)
        {
            m_layout = new AlgoLayout;
        }
        return m_layout;
    }

    struct AlgoLayout::ElementFuntionTable AlgoLayout::m_element_info[] =
    {
        {"CGPUPanel", "algo_panel", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoPanel), NULL, NULL},
        {"CGPUButton" , "ldw" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoLdw) , (PFOnEvent)(&AlgoLayout::OnEventLdw), NULL},
        {"CGPUButton" , "bsd" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoBsd) , (PFOnEvent)(&AlgoLayout::OnEventBsd), NULL},
        {"CGPUButton" , "online" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoOnline) , (PFOnEvent)(&AlgoLayout::OnEventOnline), NULL},
        {"CGPUButton" , "apa" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApa) , (PFOnEvent)(&AlgoLayout::OnEventApa), NULL},
        {"CGPUButton" , "行车记录仪" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoMedia) , (PFOnEvent)(&AlgoLayout::OnEventMedia), NULL},
        {"CGPUPanel" , "algo_media_panel" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoMediaPanel) , NULL, NULL},
        {"CGPUButton" , "playback" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoMediaPlayback) , (PFOnEvent)(&AlgoLayout::OnEventMediaPlayback), NULL},
        {"CGPUButton" , "record" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoMediaRecord) , (PFOnEvent)(&AlgoLayout::OnEventMediaRecord), NULL},
    };

    void AlgoLayout::Enable(bool flag)
    {
        EnableLayout(flag);
    }
    
    AlgoLayout::AlgoLayout()
        :ILayout(ALGOHMI_EVENT_NAME)
        ,IAlgoLayout()
        ,m_record_button(NULL), m_playback_button(NULL)
        ,m_ldw_button(NULL), m_bsd_button(NULL)
        ,m_online_button(NULL), m_apa_button(NULL), m_media_panel(NULL)
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    AlgoLayout::~AlgoLayout()
    {
    }
    static IGUITexture panel_array_texture[] = {
        {XR_RES_ALGO"algo_panel.dds", 0, 0, 115, 720},
    };
    static IGUITexture ldw_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds", 0, 180, 100, 90},
        {XR_RES_ALGO"algo_btn_clicked.dds", 0, 180, 100, 90},
    };
    static IGUITexture bsd_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds", 0, 270, 100, 90},
        {XR_RES_ALGO"algo_btn_clicked.dds", 0, 270, 100, 90},
    };
    static IGUITexture online_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds", 0, 360, 100, 90},
        {XR_RES_ALGO"algo_btn_clicked.dds", 0, 360, 100, 90},
    };
    static IGUITexture apa_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds", 0, 450, 100, 90},
        {XR_RES_ALGO"algo_btn_clicked.dds", 0, 450, 100, 90},
    };
    static IGUITexture media_array_texture[] =
    {
        {XR_RES_HMI"BC64.dds", 0, 630, 100, 90},
        {XR_RES_HMI"media_btn_clicked.dds", 0, 630, 100, 90},
    };
    static IGUITexture mediaPanel_array_texture[] = {
        {XR_RES_ALGO"algo_media_panel.dds", 76, 604, 175, 113},
    };
    static IGUITexture record_array_texture[] =
    {
        {XR_RES_ALGO"algo_media_record.dds", 19, 5, 154, 49},
        {XR_RES_ALGO"algo_media_record_clicked.dds", 19, 5, 154, 49},
    };
    static IGUITexture playback_array_texture[] =
    {
        {XR_RES_ALGO"algo_media_playback.dds", 19, 47, 154, 49},
        {XR_RES_ALGO"algo_media_playback_clicked.dds", 19, 47, 154, 49},
    };


    void AlgoLayout::InitAlgoPanel(IGUIElement* algo_panel, const GUI_HANDLE_T parentId)
    {
        algo_panel->Attach(m_node, parentId);
        algo_panel->SetTexture(panel_array_texture, 0);
        algo_panel->Create(panel_array_texture[0].pos_x,
                           panel_array_texture[0].pos_y,
                           panel_array_texture[0].element_width,
                           panel_array_texture[0].element_height
            );
    }
    void AlgoLayout::InitAlgoLdw(IGUIElement* ldw_button, const GUI_HANDLE_T parentId)
    {
        ldw_button->Attach(m_node, parentId);
        ldw_button->SetTexture(ldw_array_texture, GUI_BUTTON_EFFECT_LOCK);
        ldw_button->Create(ldw_array_texture[0].pos_x,
                           ldw_array_texture[0].pos_y,
                           ldw_array_texture[0].element_width,
                           ldw_array_texture[0].element_height
            );        
        m_ldw_button = dynamic_cast<CGPUButton*>(ldw_button);
    }
    void AlgoLayout::OnEventLdw(IGUIElement* ldw_button)
    {
        //处理按钮逻辑
        m_online_button->Reset();
        m_apa_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_LDW_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoBsd(IGUIElement* bsd_button, const GUI_HANDLE_T parentId)
    {
        bsd_button->Attach(m_node, parentId);
        bsd_button->SetTexture(bsd_array_texture, GUI_BUTTON_EFFECT_LOCK);
        bsd_button->Create(bsd_array_texture[0].pos_x,
                           bsd_array_texture[0].pos_y,
                           bsd_array_texture[0].element_width,
                           bsd_array_texture[0].element_height
            );

        m_bsd_button = dynamic_cast<CGPUButton*>(bsd_button);
    }
    void AlgoLayout::OnEventBsd(IGUIElement* bsd_button)
    {
        //处理按钮逻辑关系
        m_online_button->Reset();
        m_apa_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_BSD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoOnline(IGUIElement* online_button, const GUI_HANDLE_T parentId)
    {
        online_button->Attach(m_node, parentId);
        online_button->SetTexture(online_array_texture, GUI_BUTTON_EFFECT_LOCK);
        online_button->Create(online_array_texture[0].pos_x,
                              online_array_texture[0].pos_y,
                              online_array_texture[0].element_width,
                              online_array_texture[0].element_height
            );
        m_online_button = dynamic_cast<CGPUButton*>(online_button);
    }
    void AlgoLayout::OnEventOnline(IGUIElement* play_button)
    {
        //处理按钮逻辑关系
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_apa_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_ONLINE_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoApa(IGUIElement* apa_button, const GUI_HANDLE_T parentId)
    {
        apa_button->Attach(m_node, parentId);
        apa_button->SetTexture(apa_array_texture, GUI_BUTTON_EFFECT_LOCK);
        apa_button->Create(apa_array_texture[0].pos_x,
                           apa_array_texture[0].pos_y,
                           apa_array_texture[0].element_width,
                           apa_array_texture[0].element_height
            );

        m_apa_button = dynamic_cast<CGPUButton*>(apa_button);
    }
    void AlgoLayout::OnEventApa(IGUIElement* play_button)
    {
        //处理按钮逻辑
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_online_button->Reset();
                
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_APA_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoMedia(IGUIElement* media_button, const GUI_HANDLE_T parentId)
    {
        media_button->Attach(m_node, parentId);
        media_button->SetTexture(media_array_texture, GUI_BUTTON_EFFECT_LOCK);
        media_button->Create(media_array_texture[0].pos_x,
                             media_array_texture[0].pos_y,
                             media_array_texture[0].element_width,
                             media_array_texture[0].element_height
            );

        m_media_button = dynamic_cast<CGPUButton*>(media_button);
    }
    void AlgoLayout::OnEventMedia(IGUIElement* media_button)
    {
        //使能子菜单判断模式 record/playback
        static bool flag = true;
        m_media_panel->Enable(flag);
        flag = !flag;
    }
    void AlgoLayout::InitAlgoMediaPanel(IGUIElement* media_panel, const GUI_HANDLE_T parentId)
    {
        media_panel->Attach(m_node, parentId);
        media_panel->SetTexture(mediaPanel_array_texture, GUI_BUTTON_EFFECT_LOCK);
        media_panel->Create(mediaPanel_array_texture[0].pos_x,
                            mediaPanel_array_texture[0].pos_y,
                            mediaPanel_array_texture[0].element_width,
                            mediaPanel_array_texture[0].element_height
            );
        media_panel->Enable(false);
        m_media_panel = dynamic_cast<CGPUPanel*>(media_panel);
    }
    
    void AlgoLayout::InitAlgoMediaPlayback(IGUIElement* playback_button, const GUI_HANDLE_T parentId)
    {
        playback_button->Attach(m_node, parentId);
        playback_button->SetTexture(playback_array_texture, 0);
        playback_button->Create(playback_array_texture[0].pos_x,
                                playback_array_texture[0].pos_y,
                                playback_array_texture[0].element_width,
                                playback_array_texture[0].element_height
            );
        m_playback_button = dynamic_cast<CGPUButton*>(playback_button);
    }
    void AlgoLayout::OnEventMediaPlayback(IGUIElement* playback_button)
    {
        //处理按钮逻辑
        m_record_button->Reset();
        m_playback_button->Reset();
        m_media_button->Reset();
        OnEventMedia(m_media_panel);
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_EXIT_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoMediaRecord(IGUIElement* record_button, const GUI_HANDLE_T parentId)
    {        
        record_button->Attach(m_node, parentId);
        record_button->SetTexture(record_array_texture, GUI_BUTTON_EFFECT_LOCK);
        record_button->Create(record_array_texture[0].pos_x,
                              record_array_texture[0].pos_y,
                              record_array_texture[0].element_width,
                              record_array_texture[0].element_height
            );
        m_record_button = dynamic_cast<CGPUButton*>(record_button);
    }
    void AlgoLayout::OnEventMediaRecord(IGUIElement*)
    {
        //处理按钮逻辑
        m_ldw_button->Enable(false);
        m_bsd_button->Enable(false);
        m_online_button->Enable(false);
        m_apa_button->Enable(false);
        m_playback_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_RECORD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
};

/**
 * 接口函数，操作AlgoLayout
 */
extern "C" DLL_PUBLIC IAlgoLayout* NewAlgoLayout()
{
    return(GUI::AlgoLayout::GetLayout());
}

extern "C" DLL_PUBLIC void DeleteAlgoLayout(IAlgoLayout* layout)
{
    if(layout)
    {
        delete layout;
    }
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
