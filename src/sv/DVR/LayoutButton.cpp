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
#include "LayoutButton.h"

IMPLEMENT_DYNAMIC(CLayoutButton, CLayoutElement)
void CLayoutButton::InitElementSize(uint32_t pos_x, uint32_t pos_y,
                                   uint32_t element_width, uint32_t element_height,
                                   uint32_t opacity)
{
    //检查pos在layout中的有效范围
    layout_x = pos_x; //! pos_x + m_node->pos_x
    layout_y = pos_y; //! pos_x + m_node->pos_x
    //检查size是否在layout的有效范围
    button_width = element_width;
    button_height = element_height;
    button_opacity = opacity;
}

void CLayoutButton::InitElementTexture(const TextureName* array_texture)
{
    //目前CXrButton 只支持两种纹理(底层纹理, 点击后的纹理), 检查纹理文件是否存在
    base_texture = array_texture[0];
    hit_texture = array_texture[1];
}

bool CLayoutButton::CreateElement()
{
    const ILayoutNode* node = GetLayoutNode();
    if(node)
    {
        /** 调用XrCore的CXrButton,添加button node*/
        button->Add(node,
                    -1,
                    InsertFlag_Default,
                    layout_x,
                    layout_y,
                    button_width,
                    button_height,
                    button_opacity,
                    base_texture,
                    hit_texture);
        button->SetActionDelegate(this);
        DEBUG("get the right layout node\n");
    }
    else
    {
        ERROR("plese point a layout node for it\n");
    }
    return true;
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
