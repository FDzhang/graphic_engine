/*------------------------------------------------------------------------------------------
 * FILE: GpuElementIcon.cpp
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
 * VERSION: 19 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementIcon.h"

namespace GUI
{
    CGPUIcon::CGPUIcon()
        :IGUIElement("CGPUIcon")
        ,CXrBaseView()
        ,m_cursor_texture(NULL),m_cursor_layer(NULL)
    {
    }
    CGPUIcon::~CGPUIcon()
    {
    }
        bool CGPUIcon::Create(const uint32_t pos_x, const uint32_t pos_y,
                          const uint32_t element_width, const uint32_t element_height)
    {
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
            Int32 m_baseLayerId = node->CreateSpirit(parent, flag, -1, 1.0, pos_x, pos_y, 0, element_width, element_height);
            ILayer* layer = node->GetLayer(m_baseLayerId);
            layer->SetEventResponder(this);
            
            Int32 cursorId = node->CreateUIMaterial(Material_UI_Spirit, m_cursor_texture->texName);
            Int32 cursorSpiritId = node->CreateSpirit(m_baseLayerId, InsertFlag_Child,
                                                      cursorId, 1.0,
                                                      m_cursor_texture->pos_x,
                                                      m_cursor_texture->pos_y, 0,
                                                      m_cursor_texture->element_width,
                                                      m_cursor_texture->element_height);
            m_cursor_layer = node->GetLayer(cursorSpiritId);
            IGUIElement::SetHwnd((GUI_HANDLE_T)m_baseLayerId);
        }
    }
    void CGPUIcon::SetTexture(const IGUITexture* effect, const long style)
    {
        m_cursor_texture = &(((IGUITexture*)effect)[0]);
    }

    Boolean CGPUIcon::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        Log_Error("x: %d y:%d", x, y);
        m_cursor_layer->SetX(x);
        m_cursor_layer->SetY(y);
    }
    IMPLEMENT_DYNAMIC_CLASS(CGPUIcon)
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
