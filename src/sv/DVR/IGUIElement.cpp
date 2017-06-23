/*------------------------------------------------------------------------------------------
 * FILE: LayoutElement.cpp
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
 * VERSION: 13 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "Layout.h"

namespace GUI
{
    int32_t IGUIElement::m_focus_id = 0;
    IGUIElement::IGUIElement(const char* name)
        :m_id(-1), m_parent(0)
        ,m_eventId(0), m_cmdTarget(NULL)
        ,m_node(NULL)
        ,m_elementName(name)
    {
    }
    IGUIElement::~IGUIElement()
    {
    }

    void IGUIElement::DispatchEvent(const EVENT_HANDLE_T eventId, const uint32_t type)
    {
        //if(m_cmdTarget) /*不做判断处理, 用户控件必须做事件处理*/
        {
            m_cmdTarget->Dispatch(eventId, type);
        }
    }
    IMPLEMENT_DYNAMIC_BASE(IGUIElement)
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
