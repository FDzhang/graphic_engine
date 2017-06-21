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
        :IGUIElement("CGPUProcessbar")
        ,CXrBaseView()
        ,m_processbar_x(0) , m_processbar_y(0)
        ,m_processbar_width(0), m_processbar_height(0)
        ,m_pos(0)
    {
    
    }

    CGPUProcessbar::~CGPUProcessbar()
    {
        
    }

    bool CGPUProcessbar::Create(const uint32_t pos_x, const uint32_t pos_y,
                                const uint32_t element_width, const uint32_t element_height)
    {
        m_processbar_x = pos_x;
        m_processbar_y = pos_y;
        m_processbar_width =  element_width;
        m_processbar_height = element_height;

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
            
            Int32 RTMtlId = node->CreateUIMaterial(Material_UI_Spirit, m_barBaseTexture->texName);
            Int32 barBaseId = node->CreateSpirit(parent, flag, RTMtlId, 1.0, m_processbar_x, m_processbar_y, 0, m_processbar_width, m_processbar_height);
            m_pbarBase = node->GetLayer(barBaseId);
            m_pbarBase->SetEventResponder(this);
            RTMtlId = node->CreateUIMaterial(Material_UI_Spirit, m_barSlideTexture->texName);
            Int32 barSlideId = node->CreateSpirit(barBaseId, InsertFlag_Child, RTMtlId, 1.0, 0, 0, 0, m_processbar_width, m_processbar_height);
            m_pbarSlide = node->GetLayer(barSlideId);
            IGUIElement::SetHwnd((GUI_HANDLE_T)barBaseId);
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
    void CGPUProcessbar::SetTexture(const IGUITexture* effect, const long style)
    {
        m_barBaseTexture = &(((IGUITexture*)effect)[0]);
        m_barSlideTexture = &(((IGUITexture*)effect)[1]);
    }
    Boolean CGPUProcessbar::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        switch(type)
        {
        case TouchEvent_Down:
            //设置焦点在进度条上
            m_status = true;
        case TouchEvent_Move:
            //判断焦点是否被释放
            if(m_status)
            {
                Int32 PosX = x<0?0:x;
                PosX = PosX>m_processbar_width?m_processbar_width:PosX;
                m_pbarSlide->SetX(PosX);
                m_pos = PosX;
            }
            break;
        case TouchEvent_Up:
            //释放焦点
            IGUIElement::DispatchEvent(IGUIElement::EventId(), type);
            m_status = false;
        default:
            Log_Error("attention: a unknown touch event is sent");
        }
    }

    void CGPUProcessbar::SetValue(uint32_t whole_time, uint32_t current_time)
    {
        current_time = current_time > whole_time? whole_time:current_time;
        float value = (float)current_time / (float)whole_time;
        DEBUG("whole_time %d current_time %d percent %f\n", whole_time, current_time, value);
        m_pbarSlide->SetX(m_processbar_width*value);
        m_pos = current_time;
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
