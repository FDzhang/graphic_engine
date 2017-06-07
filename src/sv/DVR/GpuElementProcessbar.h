#ifndef _GPU_ELEMENT_PROCESSBAR_H_ /* { */
#define _GPU_ELEMENT_PROCESSBAR_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: LayoutProcessBar.h
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
 * VERSION: 15 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrSlider.h"

namespace GUI
{
    class CGPUProcessbar : public IGUIElement, private CXrBaseView
    {
    public:
        CGPUProcessbar();
        virtual ~CGPUProcessbar();
        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetElementEffect(void* effect, long style);
        void SetValue(uint32_t whole_time, uint32_t current_time);
        void SetEnable(bool enable);
    private:
        /** 重写OnTouchEvent, 添加事件自定义处理功能*/
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y,Int32 type);

    private:
        IGUITexture m_baseLayerTexture, m_slideLayerTexture;
        uint32_t processbar_x, processbar_y;
        uint32_t processbar_width, processbar_height;
        ILayer   *m_pbaseLayer;
        uint32_t m_barWidth, m_barHeight;

    private:
        DECLEAR_DYNAMIC_CLASS(CGPUProcessbar, IGUIElement)
    };
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPU_ELEMENT_PROCESSBAR_H_ */
