/*------------------------------------------------------------------------------------------
 * FILE: GpuElementText.cpp
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
 * VERSION: 08 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementText.h"
#include "XrCore/XrSrc/XrNode/Scene/CUINode.h"

namespace GUI
{
    CGPUText::CGPUText()
        :IGUIElement("CGPUText")
        ,m_layout_x(0), m_layout_y(0)
        ,m_label_width(0), m_label_height(0)
        ,m_pText(NULL)
    {
    }

    CGPUText::~CGPUText()
    {

    }

    void CGPUText::SetTexture(const IGUITexture* effect, const long style)
    {
        m_base_texture = ((IGUITexture*)effect)[0];
        m_font_texture = ((IGUITexture*)effect)[1];
    }
    
    bool CGPUText::Create(const uint32_t pos_x, const uint32_t pos_y,
                          const uint32_t element_width, const uint32_t element_height)
    {
        //检查pos在layout中的有效范围
        m_layout_x = pos_x; //! pos_x + m_node->pos_x
        m_layout_y = pos_y; //! pos_x + m_node->pos_x
        //检查size是否在layout的有效范围
        m_label_width = element_width;
        m_label_height = element_height;
    
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
            Int32 rootId = node->CreateSpirit(parent, flag, -1, 1.0, m_layout_x, m_layout_y, 0 , m_label_width, m_label_height);
            ILayer* m_root = node->GetLayer(rootId);
            
            Int32 m_back_mtl_id= node->CreateUIMaterial(Material_UI_Spirit, XR_RES"BC64.dds"); 
            
            int logoLayerId = node->CreateSpirit( rootId,
                                                  InsertFlag_Child,
                                                  m_back_mtl_id,
                                                  1.0,
                                                  0,
                                                  0,
                                                  0,
                                                  m_label_width,
                                                  m_label_height);
            float m_textSize = 0.6;
            Int32 m_font_mtl_id = node->CreateUIFontMaterial(XR_RES"text_box.ttf", 0);
            node->CreateTextLayer(rootId,
                                  InsertFlag_Child,
                                  m_font_mtl_id,
                                  1,
                                  0,
                                  0,
                                  &m_pText,
                                  m_label_width,
                                  m_label_height);

            m_pText->SetOpacity(1.0);
            m_pText->SetFontSize(20);
            m_pText->SetColor(0.88, 0.35, 0.71);
            IGUIElement::SetElementId(logoLayerId);
        }
        else
        {
            ERROR("plese point a layout node for it\n");
        }
        return true;
    }

    void CGPUText::SetText(char* text)
    {
        m_pText->SetText(text);
    }

    IMPLEMENT_DYNAMIC_CLASS(CGPUText)
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
