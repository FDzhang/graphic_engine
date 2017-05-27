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

namespace GUI
{
    int32_t IGUIElement::m_focus_id = 0;
    void GPU_SetElementTexture(IGUIElement* element, const IGUITexture* array_texture, uint32_t array_size)
    {
        
    }

    void GPU_SetElementOpacity(IGUIElement* element, const uint32_t opacity)
    {
        
    }

    void GPU_SetElementEventEffect(IGUIElement* element, const uint32_t style)
    {
        
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
