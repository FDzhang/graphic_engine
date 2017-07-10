#ifndef _GPUELEMENTEVENTLISTENER_H_ /* { */
#define _GPUELEMENTEVENTLISTENER_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementContainer.h
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
 * VERSION: 10 7月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrBaseView.h"

namespace GUI
{
    class CGPUEventListener: public IGUIElement , private CXrBaseView
    {
    public:
        CGPUEventListener();
        ~CGPUEventListener();

        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetTexture(const IGUITexture* effect, const long style) {}
        void Enable(bool enable);
    private:
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type);
        
    private:
        ILayer* m_eventLayer;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUEventListener, IGUIElement)
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTEVENTLISTENER_H_ */
