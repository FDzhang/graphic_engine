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
        ,CXrBaseView()
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

        const IUINode* node = GetLayoutNode();
        if(node)
        {
            /** 第一步: 创建进度条的base Layer*/
            InsertFlag flag = InsertFlag_Child;
            int32_t parent = GetParent();
            if(parent < 0)
            {
                //控件不存在父节点id
                parent = -1;
                flag = InsertFlag_Default;
            }
#if 0
            Int32 RTMtlId = node->CreateUIMaterial(Material_UI_Spirit, m_baseLayerTexture);
            Int32 baseLayerId = node->CreateSpirit(parent, flag, RTMtlId, 1.0, processbar_x, processbar_y, 0, processbar_width, processbar_height);
            m_root = node->GetLayer(baseLayerId);
            m_root->SetEventResponder(this);
            Int32 scrollPanelId = node->CreateScrollPanel(baseLayerId, InsertFlag_Child, processbar_x, processbar_y, 100, 100, ScrollMode_X, 120);
#endif
            SetElementId(32);
        }
        else
        {
            Log_Error("\n");
        }
        return true;
    }
    void CGPUProcessbar::SetEnable(bool enable)
    {
        SetEnable(enable);
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
        m_cmdTarget->DispatchEvent(layerId, type);
        //OnTouchEvent(layerId, x, y, type);
    }

    void CGPUProcessbar::SetValue(uint32_t whole_time, uint32_t current_time)
    {
        float percent = (float)current_time / (float)whole_time;
        DEBUG("whole_time %d current_time %d percent %f\n", whole_time, current_time, percent);
        //CXrSlideBar::SetValue(percent);
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
