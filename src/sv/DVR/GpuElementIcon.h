#ifndef _GPUELEMENTICON_H_ /* { */
#define _GPUELEMENTICON_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementIcon.h
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
 * VERSION: 01 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include "XrCore/XrSrc/XrUILibrary/CXrBaseView.h"
#include "IGUIElement.h"

namespace GUI
{
    enum
    {
        GUI_ICON_DEFAULT,
        GUI_ICON_MOVEABLE,
    };

    class CGPUIcon : public IGUIElement, private CXrBaseView
    {
    public:
        CGPUIcon();
        virtual ~CGPUIcon();
        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetTexture(const IGUITexture* effect, const long style);
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type);
    private:
        IGUITexture* m_iconTexture;
        ILayer*      m_iconLayer;
        long         m_iconStyle;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUIcon, IGUIElement)
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTICON_H_ */
