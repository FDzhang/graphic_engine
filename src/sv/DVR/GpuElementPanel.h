#ifndef _GPU_ELEMENT_PANNEL_H_ /* { */
#define _GPU_ELEMENT_PANNEL_H_
/*------------------------------------------------------------------------------------------*\
 * FILE:GpuElementPannel.h
 *==========================================================================================
 * Copyright 2017   O-Film Technologies, Inc., All Rights Reserved.
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
 * VERSION: 23 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrPanel.h"

namespace GUI
{
    class CGPUPanel : public IGUIElement
    {
    
    public:
        CGPUPanel();
        ~CGPUPanel();
        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetElementEffect(void* effect, long style);
    private:
        CXrPanel* m_panel;
        uint32_t m_layout_x, m_layout_y;
        uint32_t m_panel_width, m_panel_height;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUPanel, IGUIElement)
    };
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPU_ELEMENT_PANEL_H_ */
