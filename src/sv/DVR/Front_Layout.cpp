/*------------------------------------------------------------------------------------------
 * FILE: Front_Layout.cpp
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
 * VERSION: 19 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "Front_Layout.h"

namespace GUI
{
    Front_Layout* Front_Layout::m_layout = NULL;
    
    IFrontLayout* Front_Layout::GetLayout()
    {
        if(m_layout == NULL)
        {
            m_layout = new Front_Layout;
        }
        return m_layout;
    }
    
    struct ILayout::ElementFuntionTable Front_Layout::m_element_info[] =
    {
        {"CGPUIcon" , "鼠标光标" , 1, 0, NULL, (PFCreateElement)(&Front_Layout::InitMouseCursor) , NULL, NULL},
    };

    void Front_Layout::Enable(bool flag)
    {
        ILayout::EnableLayout(flag);
    }
    
    Front_Layout::Front_Layout()
        :ILayout()
        ,IFrontLayout()
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    Front_Layout::~Front_Layout()
    {
    }

    static IGUITexture cursor_array_texture[] =
    {
        {XR_RES_FRONT"cursor.dds", 0, 0, 64, 64}
    };
    
    void Front_Layout::InitMouseCursor(IGUIElement* cursor, const GUI_HANDLE_T parentId)
    {
        cursor->Attach(m_node, parentId);
        cursor->SetTexture(cursor_array_texture, 0);
        cursor->Create(0,
                       0,
                       1280,
                       720);
        m_cursor = dynamic_cast<CGPUIcon*>(cursor);
    }
    void Front_Layout::OnMouseMove(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Move);
        }
    }
    void Front_Layout::OnMouseUp(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Up);
        }
    }
    void Front_Layout::OnMouseDown(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Down);
        }
    }
};

/**
 * 接口函数，操作Front_Layout
 */
extern "C" DLL_PUBLIC IFrontLayout* NewFrontLayout()
{
    return(GUI::Front_Layout::GetLayout());
}

extern "C" DLL_PUBLIC void DeleteFrontLayout(IFrontLayout* layout)
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
