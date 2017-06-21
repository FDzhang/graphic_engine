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
#include "Algo_Layout.h"

namespace GUI
{
    AlgoLayout* AlgoLayout::m_layout = NULL;
    AvmEventType   AlgoLayout::m_event_type = AvmEvent::Invalid_Event_Type;
    IAlgoLayout* AlgoLayout::GetLayout()
    {
        if(m_layout == NULL)
        {
            m_layout = new AlgoLayout;
        }
        return m_layout;
    }
    
    struct ILayout::ElementFuntionTable AlgoLayout::m_element_info[] =
    {
        {"CGPUButton" , "开关回放模式" , 1, 0, NULL, (PFCreateElement)(&AlgoLayout::InitAlgoExit) , (PFOnEvent)(&AlgoLayout::OnEventExit), NULL},
    };

    void AlgoLayout::Enable(bool flag)
    {
        ILayout::EnableLayout(flag);
    }
    
    AlgoLayout::AlgoLayout()
        :ILayout()
        ,IAlgoLayout()
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    AlgoLayout::~AlgoLayout()
    {
    }

    static IGUITexture exit_array_texture[] =
    {
        {XR_RES_DVR"BC64.dds", 1014, 620, 74, 74},
        {XR_RES_DVR"BC64.dds", 1014, 620, 74, 74},
    };
    
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
        Log_Error("--------------------%s------------", __func__);
        void* payload = NULL;
        AvmEvent* event = RequestEvent(&payload);
        Algo_Event_Payload_T* data = (Algo_Event_Payload_T*)(payload);
        //填充有效数据
        data->header.msg_id = ALGO_EXIT_BUTTON;
        data->body.onlyNotify = true;
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
