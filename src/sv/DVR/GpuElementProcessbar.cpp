/*------------------------------------------------------------------------------------------
 * FILE: LayoutProcessBar.cpp
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
 * VERSION: 16 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementProcessbar.h"

namespace GUI
{
    CGPUProcessbar::CGPUProcessbar()
        :IGUIElement()
        ,CXrSlideBar(true)
    {
    
    }

    CGPUProcessbar::~CGPUProcessbar()
    {
        
    }
    bool CGPUProcessbar::Create(const uint32_t pos_x, const uint32_t pos_y,
                                const uint32_t element_width, const uint32_t element_height)
    {
        processbar_x = pos_x;
        processbar_y = pos_y;
        processbar_width =  element_width;
        processbar_height = element_height;
    
        m_barWidth =  8;
        m_barHeight = 16;

        
        //m_barBaseLayerTexture = array_texture[1];
        //m_barFinishedLayerTexture = array_texture[2];
        //m_slideLayerTexture = array_texture[3];

        const IUINode* node = GetLayoutNode();
        if(node)
        {
            /** 第一步: 创建进度条的base Layer*/
            Int32 baseLayerMtl = node->CreateUIMaterial(Material_UI_Spirit, m_baseLayerTexture);
            Rect barROI(0, 1000, 0, 12);
            Rect sliderROI(0, 1000, 0, 12);
            CXrSlideBar::Add(
                node,
                -1,
                InsertFlag_Default,
                processbar_x,
                processbar_y,
                processbar_width,
                processbar_height,
                baseLayerMtl,
                &barROI,
                &sliderROI
                );
            SetElementId(m_baseLayerId);
        }
        else
        {
            Log_Error("\n");
        }
        return true;
    }
    void CGPUProcessbar::SetEnable(bool enable)
    {
        CXrSlideBar::SetEnable(enable);
    }
    void CGPUProcessbar::SetElementEffect(void* effect, long style)
    {
        switch(style)
        {
        case GPU_GUI_EFFECT_TEXTURE:
            
            m_baseLayerTexture = ((IGUITexture*)effect)[0];
            break;
        default:
            break;
        }
    }
    Boolean CGPUProcessbar::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        DEBUG("%d %d %d\n", m_baseLayerId, layerId, type);
        m_cmdTarget->DispatchEvent(layerId, type);
        CXrSlideBar::OnTouchEvent(layerId, x, y, type);
    }

    void CGPUProcessbar::SetValue(uint32_t whole_time, uint32_t current_time)
    {
        float percent = (float)current_time / (float)whole_time;
        DEBUG("whole_time %d current_time %d percent %f\n", whole_time, current_time, percent);
        CXrSlideBar::SetValue(percent);
    }
    
    IMPLEMENT_DYNAMIC_CLASS(CGPUProcessbar)
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
