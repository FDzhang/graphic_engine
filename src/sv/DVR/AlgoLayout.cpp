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
        {"CGPUButton" , "APA_IN" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaIn) , (PFOnEvent)(&AlgoLayout::OnEventApaIn), NULL},
        {"CGPUButton" , "APA_OUT" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaOut) , (PFOnEvent)(&AlgoLayout::OnEventApaOut), NULL},
        //{"CGPUButton" , "fcw" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoFCW) , (PFOnEvent)(&AlgoLayout::OnEventFCW), NULL},
        {"CGPUButton" , "oc" , 2, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoOC) , (PFOnEvent)(&AlgoLayout::OnEventOC), NULL},
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
        ,m_oc_button(NULL), m_apa_button(NULL), m_media_panel(NULL)
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    AlgoLayout::~AlgoLayout()
    {
    }
    static IGUITexture panel_array_texture[] = {
        {XR_RES_ALGO"algo_panel.dds", 0, 80, 100, 560},
    };
    static IGUITexture ldw_array_texture[] =
    {
        {XR_RES_ALGO"algo_ldw.dds", 0, 140, 100, 70},
        {XR_RES_ALGO"algo_ldw_clicked.dds", 0, 140, 100, 70},
    };
    static IGUITexture bsd_array_texture[] =
    {
        {XR_RES_ALGO"algo_bsd.dds", 0, 210, 100, 70},
        {XR_RES_ALGO"algo_bsd_clicked.dds", 0, 210, 100, 70},
    };
    static IGUITexture oc_array_texture[] =
    {
        {XR_RES_ALGO"algo_fcw.dds", 0, 420, 100, 70},
        {XR_RES_ALGO"algo_fcw_clicked.dds", 0, 420, 100, 70},
    };
    static IGUITexture fcw_array_texture[] =
    {
        {XR_RES_ALGO"algo_fcw.dds", 0, 420, 100, 70},
        {XR_RES_ALGO"algo_fcw_clicked.dds", 0, 420, 100, 70},
    };
    
    static IGUITexture mediaBtn_array_texture[] =
    {
        {XR_RES_ALGO"algo_media_btn.dds", 0, 490, 100, 70},
        {XR_RES_ALGO"algo_media_btn_clicked.dds", 0, 490, 100, 70},
    };
    static IGUITexture mediaPanel_array_texture[] = {
        {XR_RES_ALGO"algo_media_panel.dds", 76, 524, 175, 113},
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
    static IGUITexture apaIn_array_texture[] =
    {
        {XR_RES_ALGO"algo_apaIn.dds", 0, 280, 100, 70},
        {XR_RES_ALGO"algo_apaIn_clicked.dds", 0, 280, 100, 70},
    };
    static IGUITexture apaOut_array_texture[] =
    {
        {XR_RES_ALGO"algo_apaOut.dds", 0, 350, 100, 70},
        {XR_RES_ALGO"algo_apaOut_clicked.dds", 0, 350, 100, 70},
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
        m_fcw_button->Reset();
        m_apaIn_button->Reset();
        m_apaOut_button->Reset();
        
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
        m_fcw_button->Reset();
        m_apaIn_button->Reset();
        m_apaOut_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_BSD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    
    void AlgoLayout::InitAlgoOC(IGUIElement* oc_button, const GUI_HANDLE_T parentId)
    {        
        oc_button->Attach(m_node, parentId);
        oc_button->SetTexture(oc_array_texture, GUI_BUTTON_EFFECT_LOCK);
        oc_button->Create(oc_array_texture[0].pos_x,
                           oc_array_texture[0].pos_y,
                           oc_array_texture[0].element_width,
                           oc_array_texture[0].element_height
            );
        m_oc_button = dynamic_cast<CGPUButton*>(oc_button);
    }
    
    void AlgoLayout::OnEventOC(IGUIElement* oc_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_OC_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    
    void AlgoLayout::InitAlgoFCW(IGUIElement* fcw_button, const GUI_HANDLE_T parentId)
    {        
        fcw_button->Attach(m_node, parentId);
        fcw_button->SetTexture(fcw_array_texture, GUI_BUTTON_EFFECT_LOCK);
        fcw_button->Create(fcw_array_texture[0].pos_x,
                           fcw_array_texture[0].pos_y,
                           fcw_array_texture[0].element_width,
                           fcw_array_texture[0].element_height
            );
        m_fcw_button = dynamic_cast<CGPUButton*>(fcw_button);
    }
    
    void AlgoLayout::OnEventFCW(IGUIElement*)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_CTA_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    
    void AlgoLayout::InitAlgoMedia(IGUIElement* media_button, const GUI_HANDLE_T parentId)
    {
        media_button->Attach(m_node, parentId);
        media_button->SetTexture(mediaBtn_array_texture, GUI_BUTTON_EFFECT_LOCK);
        media_button->Create(mediaBtn_array_texture[0].pos_x,
                             mediaBtn_array_texture[0].pos_y,
                             mediaBtn_array_texture[0].element_width,
                             mediaBtn_array_texture[0].element_height
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
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_fcw_button->Reset();
        OnEventMedia(m_media_panel);
        m_apaIn_button->Reset();
        m_apaOut_button->Reset();
        
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
        static bool is_record = true;
        is_record = !is_record;
        //处理按钮逻辑
        m_ldw_button->Enable(is_record);
        m_bsd_button->Enable(is_record);
        m_fcw_button->Enable(is_record);
        m_apaIn_button->Enable(is_record);
        m_apaOut_button->Enable(is_record);
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_fcw_button->Reset();
        m_playback_button->Reset();
        m_apaIn_button->Reset();
        m_apaOut_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_RECORD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }

    void AlgoLayout::InitAlgoApaIn(IGUIElement* apaIn_button, const GUI_HANDLE_T parentId)
    {
        apaIn_button->Attach(m_node, parentId);
        apaIn_button->SetTexture(apaIn_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        apaIn_button->Create(apaIn_array_texture[0].pos_x,
                             apaIn_array_texture[0].pos_y,
                             apaIn_array_texture[0].element_width,
                             apaIn_array_texture[0].element_height
            );
        m_apaIn_button = dynamic_cast<CGPUButton*>(apaIn_button);
    }

    void AlgoLayout::OnEventApaIn(IGUIElement* apaIn_button)
    {
        //处理按钮逻辑
        m_record_button->Reset();
        m_playback_button->Reset();
        m_media_button->Reset();
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_fcw_button->Reset();
        m_apaOut_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_APA_IN_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }

    void AlgoLayout::InitAlgoApaOut(IGUIElement* apaOut_button, const GUI_HANDLE_T parentId)
    {
        apaOut_button->Attach(m_node, parentId);
        apaOut_button->SetTexture(apaOut_array_texture, GUI::GUI_BUTTON_EFFECT_LOCK);
        apaOut_button->Create(apaOut_array_texture[0].pos_x,
                              apaOut_array_texture[0].pos_y,
                              apaOut_array_texture[0].element_width,
                              apaOut_array_texture[0].element_height
            );
        m_apaOut_button = dynamic_cast<CGPUButton*>(apaOut_button);
    }
    void AlgoLayout::OnEventApaOut(IGUIElement* apaOut_button)
    {
        //处理按键逻辑
        m_record_button->Reset();
        m_playback_button->Reset();
        m_media_button->Reset();
        m_ldw_button->Reset();
        m_bsd_button->Reset();
        m_fcw_button->Reset();
        m_apaIn_button->Reset();
        
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_APA_OUT_BUTTON;
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
