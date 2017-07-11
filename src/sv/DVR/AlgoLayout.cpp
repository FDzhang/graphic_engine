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
        {"CGPUButton" , "ldw" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoLdw) , (PFOnEvent)(&AlgoLayout::OnEventLdw), NULL},
        {"CGPUButton" , "bsd" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoBsd) , (PFOnEvent)(&AlgoLayout::OnEventBsd), NULL},
        {"CGPUButton" , "online" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoOnline) , (PFOnEvent)(&AlgoLayout::OnEventOnline), NULL},
        {"CGPUButton" , "apa" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApa) , (PFOnEvent)(&AlgoLayout::OnEventApa), NULL},
        {"CGPUButton" , "playback" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoExit) , (PFOnEvent)(&AlgoLayout::OnEventExit), NULL},
        {"CGPUButton" , "record" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoRecord) , (PFOnEvent)(&AlgoLayout::OnEventRecord), NULL},
        {"CGPUButton" , "wifi" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoWifi) , (PFOnEvent)(&AlgoLayout::OnEventWifi), NULL},
    };

    void AlgoLayout::Enable(bool flag)
    {
        EnableLayout(flag);
    }

    AlgoLayout::AlgoLayout()
        :ILayout(ALGOHMI_EVENT_NAME)
        ,IAlgoLayout()
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    AlgoLayout::~AlgoLayout()
    {
    }

    static IGUITexture ldw_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 702, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 702, 620, 78, 78},
    };
    static IGUITexture bsd_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 780, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 780, 620, 78, 78},
    };
    static IGUITexture online_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 858, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 858, 620, 78, 78},
    };
    static IGUITexture apa_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 936, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 936, 620, 78, 78},
    };
    static IGUITexture exit_array_texture[] =
    {
        {XR_RES"playback_unable.dds", 1014, 620, 78, 78},
        {XR_RES"playback_enable.dds", 1014, 620, 78, 78},
    };
    static IGUITexture record_array_texture[] =
    {
        {XR_RES"record_unable.dds", 1092, 620, 78, 78},
        {XR_RES"record_enable.dds", 1092, 620, 78, 78},
    };
    static IGUITexture wifi_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 1170, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 1170, 620, 78, 78},
    };
    void AlgoLayout::InitAlgoLdw(IGUIElement* ldw_button, const GUI_HANDLE_T parentId)
    {
        ldw_button->Attach(m_node, parentId);
        ldw_button->SetTexture(ldw_array_texture, 0);
        ldw_button->Create(ldw_array_texture[0].pos_x,
                           ldw_array_texture[0].pos_y,
                           ldw_array_texture[0].element_width,
                           ldw_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventLdw(IGUIElement* ldw_button)
    {
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
        bsd_button->SetTexture(bsd_array_texture, 0);
        bsd_button->Create(bsd_array_texture[0].pos_x,
                           bsd_array_texture[0].pos_y,
                           bsd_array_texture[0].element_width,
                           bsd_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventBsd(IGUIElement* bsd_button)
    {
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
        online_button->SetTexture(online_array_texture, 0);
        online_button->Create(online_array_texture[0].pos_x,
                              online_array_texture[0].pos_y,
                              online_array_texture[0].element_width,
                              online_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventOnline(IGUIElement* play_button)
    {
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
        apa_button->SetTexture(apa_array_texture, 0);
        apa_button->Create(apa_array_texture[0].pos_x,
                           apa_array_texture[0].pos_y,
                           apa_array_texture[0].element_width,
                           apa_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventApa(IGUIElement* play_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_APA_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }

    void AlgoLayout::InitAlgoExit(IGUIElement* exit_button, const GUI_HANDLE_T parentId)
    {
        exit_button->Attach(m_node, parentId);
        exit_button->SetTexture(exit_array_texture, 0);
        exit_button->Create(exit_array_texture[0].pos_x,
                            exit_array_texture[0].pos_y,
                            exit_array_texture[0].element_width,
                            exit_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventExit(IGUIElement* play_button)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_EXIT_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoRecord(IGUIElement* record_button, const GUI_HANDLE_T parentId)
    {
        record_button->Attach(m_node, parentId);
        record_button->SetTexture(record_array_texture, GUI_BUTTON_EFFECT_LOCK);
        record_button->Create(record_array_texture[0].pos_x,
                              record_array_texture[0].pos_y,
                              record_array_texture[0].element_width,
                              record_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventRecord(IGUIElement*)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_RECORD_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
    void AlgoLayout::InitAlgoWifi(IGUIElement* wifi_button, const GUI_HANDLE_T parentId)
    {
        wifi_button->Attach(m_node, parentId);
        wifi_button->SetTexture(wifi_array_texture, 0);
        wifi_button->Create(wifi_array_texture[0].pos_x,
                            wifi_array_texture[0].pos_y,
                            wifi_array_texture[0].element_width,
                            wifi_array_texture[0].element_height
            );
    }
    void AlgoLayout::OnEventWifi(IGUIElement*, const GUI_HANDLE_T)
    {
        Layout_Event_Payload_T* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        //填充有效数据
        payload->header.msg_id = ALGO_WIFI_BUTTON;
        payload->body.onlyNotify = true;
        PostEvent(event);
    }
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
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
