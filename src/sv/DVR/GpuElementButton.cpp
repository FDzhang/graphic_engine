/*------------------------------------------------------------------------------------------
 * FILE: LayoutButton.cpp
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
#include "GpuElementButton.h"
#include "Layout.h"

namespace GUI
{
    CGPUButton::CGPUButton()
        :IGUIElement("button")
        ,CXrButton(-1)
        ,m_button_opacity(1)
        ,m_button_property(0)
        ,m_baseOpacity(1)
        ,m_hitOpacity(0)
    {
    }

    CGPUButton::~CGPUButton()
    {
    }

    bool CGPUButton::Create(const uint32_t pos_x, const uint32_t pos_y,
                            const uint32_t element_width, const uint32_t element_height)
    {
        //检查pos在layout中的有效范围
        m_layout_x = pos_x; //! pos_x + m_node->pos_x
        m_layout_y = pos_y; //! pos_x + m_node->pos_x
        //检查size是否在layout的有效范围
        m_button_width = element_width;
        m_button_height = element_height;
    
        const IGUINode* node = GetLayoutNode();
        if(node)
        {
            InsertFlag flag = InsertFlag_Child;
            int32_t parent = GetParent();
            if(parent < 0)
            {
                //控件不存在父节点id
                parent = -1;
                flag = InsertFlag_Default;
            }
            /** 调用XrCore的CXrButton,添加button node*/
            CXrButton::Add(node,
                           parent,
                           flag,
                           m_layout_x,
                           m_layout_y,
                           m_button_width,
                           m_button_height,
                           m_button_opacity,
                           m_base_texture->texName,
                           m_hit_texture->texName);
            IGUIElement::SetHwnd((GUI_HANDLE_T)CXrButton::GetRootId());
        }
        else
        {
            ERROR("plese point a layout node for it\n");
        }
        return true;
    }

    void CGPUButton::SetTexture(const IGUITexture* effect, const long style)
    {
        //目前CXrButton 只支持两种纹理(底层纹理, 点击后的纹理), 检查纹理文件是否存在
        m_base_texture = &(((IGUITexture*)effect)[0]);
        m_hit_texture =  &(((IGUITexture*)effect)[1]);
        m_button_property = style;
    }
    void CGPUButton::SetEnable(bool enable)
    {
        CXrButton::SetEnable(enable);
    }
    void CGPUButton::Reset()
    {
        m_baseOpacity = 1;
        m_hitOpacity = 0;
        m_base.SetOpacity(m_baseOpacity);
        m_hit.SetOpacity(m_hitOpacity);
    }
    Boolean CGPUButton::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        switch(m_button_property)
        {
        case GUI_BUTTON_EFFECT_LOCK:
            if( type == TouchEvent_Down)
            {
                IGUIElement::DispatchEvent(IGUIElement::EventId(), type);
                m_baseOpacity = ~m_baseOpacity;
                m_hitOpacity = ~m_hitOpacity;
                m_hit.SetOpacity(m_hitOpacity);
                m_base.SetOpacity(m_baseOpacity);
            }
            break;
        case GUI_BUTTON_EFFECT_DEFAULT:
            switch(type)
            {
            case TouchEvent_Down:
                IGUIElement::DispatchEvent(IGUIElement::EventId(), type);
                m_hit.SetOpacity(m_button_opacity);
                m_base.SetOpacity(0);
                break;
            case TouchEvent_Up:
                
                m_hit.SetOpacity(0.0);
                m_base.SetOpacity(m_button_opacity);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        return TRUE;
    }
    IMPLEMENT_DYNAMIC_CLASS(CGPUButton)
};


/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
