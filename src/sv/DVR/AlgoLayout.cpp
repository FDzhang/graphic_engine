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
        {"CGPUIcon", "ApaImage0", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage0), NULL},
        {"CGPUIcon", "ApaImage1", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage1), NULL},
        {"CGPUIcon", "ApaImage2", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage2), NULL},
        {"CGPUIcon", "ApaImage3", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage3), NULL},
        {"CGPUIcon", "ApaImage4", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage4), NULL},
        {"CGPUIcon", "ApaImage5", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage5), NULL},
        {"CGPUIcon", "ApaImage6", 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoApaImage6), NULL},
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
        ,m_algoApaImage0(NULL), m_algoApaImage1(NULL),m_algoApaImage2(NULL),m_algoApaImage3(NULL),m_algoApaImage4(NULL),m_algoApaImage5(NULL),m_algoApaImage6(NULL)
         
    {
        InitElementTable(m_element_info, m_element_size);
    }

    AlgoLayout::~AlgoLayout()
    {
    }
    void AlgoLayout::EnableApaDemoPicture(int flag)
    {
        //临时添加 ， 调用者确保调用阶段已经初始化
        m_algoApaImage0->Enable(false);
        m_algoApaImage1->Enable(false);
        m_algoApaImage2->Enable(false);
        m_algoApaImage3->Enable(false);
        m_algoApaImage4->Enable(false);
        m_algoApaImage5->Enable(false);
        m_algoApaImage6->Enable(false);
        
        switch(flag)
        {
            case 0: m_algoApaImage0->Enable(true); break;
            case 1: m_algoApaImage1->Enable(true); break;
            case 2: m_algoApaImage2->Enable(true); break;
            case 3: m_algoApaImage3->Enable(true); break;
            case 4: m_algoApaImage4->Enable(true); break;
            case 5: m_algoApaImage5->Enable(true); break;
            case 6: m_algoApaImage6->Enable(true); break;
            default:
                break;
        }
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
        {XR_RES_DVR"BC64.dds", 1014, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 1014, 620, 78, 78},
    };
    static IGUITexture record_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 1092, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 1092, 620, 78, 78},
    };
    static IGUITexture wifi_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 1170, 620, 78, 78},
        {XR_RES_DVR"BC64.dds", 1170, 620, 78, 78},
    };
    static IGUITexture apaImage0_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_0.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage1_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_1.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage2_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_2.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage3_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_3.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage4_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_4.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage5_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_5.dds", 456, 0, 824, 720},
    };
    static IGUITexture apaImage6_array_texture[] = {
        {XR_RES_ALGO"APA_SINGLE_VIEW_ID_6.dds", 456, 0, 824, 720},
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
        record_button->SetTexture(record_array_texture, 0);
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
    void AlgoLayout::InitAlgoApaImage0(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage0_array_texture, 0);
        algoApa_image->Create(apaImage0_array_texture[0].pos_x,
                              apaImage0_array_texture[0].pos_y,
                              apaImage0_array_texture[0].element_width,
                              apaImage0_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage0 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage1(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage1_array_texture, 0);
        algoApa_image->Create(apaImage1_array_texture[0].pos_x,
                              apaImage1_array_texture[0].pos_y,
                              apaImage1_array_texture[0].element_width,
                              apaImage1_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage1 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage2(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage2_array_texture, 0);
        algoApa_image->Create(apaImage2_array_texture[0].pos_x,
                              apaImage2_array_texture[0].pos_y,
                              apaImage2_array_texture[0].element_width,
                              apaImage2_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage2 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage3(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage3_array_texture, 0);
        algoApa_image->Create(apaImage3_array_texture[0].pos_x,
                              apaImage3_array_texture[0].pos_y,
                              apaImage3_array_texture[0].element_width,
                              apaImage3_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage3 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage4(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage4_array_texture, 0);
        algoApa_image->Create(apaImage4_array_texture[0].pos_x,
                              apaImage4_array_texture[0].pos_y,
                              apaImage4_array_texture[0].element_width,
                              apaImage4_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage4 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage5(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage5_array_texture, 0);
        algoApa_image->Create(apaImage5_array_texture[0].pos_x,
                              apaImage5_array_texture[0].pos_y,
                              apaImage5_array_texture[0].element_width,
                              apaImage5_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage5 = dynamic_cast<CGPUIcon*>(algoApa_image);
    }
    void AlgoLayout::InitAlgoApaImage6(IGUIElement* algoApa_image, const GUI_HANDLE_T parentId)
    {
        algoApa_image->Attach(m_node, parentId);
        algoApa_image->SetTexture(apaImage6_array_texture, 0);
        algoApa_image->Create(apaImage6_array_texture[0].pos_x,
                              apaImage6_array_texture[0].pos_y,
                              apaImage6_array_texture[0].element_width,
                              apaImage6_array_texture[0].element_height);
        algoApa_image->Enable(false);
        m_algoApaImage6 = dynamic_cast<CGPUIcon*>(algoApa_image);
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
