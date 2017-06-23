/*------------------------------------------------------------------------------------------
 * FILE: GpuElementPanel.cpp
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
 * VERSION: 23 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementPanel.h"
#include "Layout.h"

namespace GUI
{
    CGPUPanel::CGPUPanel()
        :IGUIElement("CGPUPanel")
    {
        m_panel = new CXrPanel(-1);
    }

    bool CGPUPanel::Create(const uint32_t pos_x, const uint32_t pos_y,
                const uint32_t element_width, const uint32_t element_height)
    {
        m_layout_x = pos_x;
        m_layout_y = pos_y;
        m_panel_width = element_width;
        m_panel_height = element_height;

        const IUINode* node = GetLayoutNode();
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
            m_panel->Add(node, parent, flag, pos_x, pos_y, element_width, element_height, 1, const_cast<char*>(m_baseLayerTexture->texName));
            IGUIElement::SetHwnd((GUI_HANDLE_T)m_panel->GetRootId());
            DEBUG("get the right layout node\n");
        }
        else
        {
            ERROR("plese point a layout node for it\n");
        }
        return true;
    }

    void CGPUPanel::SetTexture(const IGUITexture* effect, const long style)
    {
        m_baseLayerTexture = &(((IGUITexture*)effect)[0]);
    }
    CGPUPanel::~CGPUPanel()
    {
    
    }
    IMPLEMENT_DYNAMIC_CLASS(CGPUPanel)
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
