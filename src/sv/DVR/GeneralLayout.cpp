/*------------------------------------------------------------------------------------------
 * FILE: GeneralLayout.cpp
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
#include "GeneralLayout.h"
namespace GUI
{
    GeneralLayout* GeneralLayout::m_layout = NULL;

    IGeneralLayout* GeneralLayout::GetLayout()
    {
        if(m_layout == NULL)
        {
            m_layout = new GeneralLayout;
        }
        return m_layout;
    }

    struct ILayout::ElementFuntionTable GeneralLayout::m_element_info[] =
    {
        {"CGPUIcon" , "鼠标光标" , 1, 0, NULL, (PFCreateElement)(&GeneralLayout::InitMouseCursor) , NULL, NULL},
    };

    void GeneralLayout::Enable(bool flag)
    {
        ILayout::EnableLayout(flag);
    }

    GeneralLayout::GeneralLayout()
        :ILayout("GeneralLayout")
        ,IGeneralLayout()
        ,m_element_size(sizeof(m_element_info) / sizeof( struct ElementFuntionTable))
    {
        InitElementTable(m_element_info, m_element_size);
    }

    GeneralLayout::~GeneralLayout()
    {
    }

    static IGUITexture cursor_array_texture[] =
    {
        {XR_RES_GENERAL"cursor.dds", 0, 0, 64, 64},
    };

    void GeneralLayout::InitMouseCursor(IGUIElement* cursor, const GUI_HANDLE_T parentId)
    {
        cursor->Attach(m_node, parentId);
        cursor->SetTexture(cursor_array_texture, GUI::GUI_ICON_MOVEABLE);
        cursor->Create(0,
                       0,
                       1280,
                       720);
        m_cursor = dynamic_cast<CGPUIcon*>(cursor);
    }

    void GeneralLayout::OnMouseMove(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Move);
        }
    }
    void GeneralLayout::OnMouseUp(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Up);
        }
    }
    void GeneralLayout::OnMouseDown(int x, int y)
    {
        if(m_cursor)
        {
            m_cursor->OnTouchEvent(m_cursor->GetHwnd(), x, y, TouchEvent_Down);
        }
    }

    void GeneralLayout::EnableCursor(bool flag)
    {
        if(m_cursor)
        {
            m_cursor->Enable(flag);
        }
    }
};

/**
 * 接口函数，操作GeneralLayout
 */
extern "C" DLL_PUBLIC IGeneralLayout* NewGeneralLayout()
{
    return(GUI::GeneralLayout::GetLayout());
}

extern "C" DLL_PUBLIC void DeleteGeneralLayout(IGeneralLayout* layout)
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
