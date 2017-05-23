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
#include "LayoutProcessBar.h"

IMPLEMENT_DYNAMIC(CLayoutProcessBar, CLayoutElement)

CLayoutProcessBar::CLayoutProcessBar()
    :CLayoutElement()
    ,CXrSlideBar(true)
{
    
}

void CLayoutProcessBar::InitElementSize(uint32_t pos_x, uint32_t pos_y,
                                        uint32_t element_width, uint32_t element_height,
                                        uint32_t opacity)
{
    processbar_x = pos_x;
    processbar_y = pos_y;
    processbar_width =  element_width;
    processbar_height = element_height;
    
    m_barWidth = element_width;
    m_barHeight = (element_height * 2 ) / 3 ;
}

void CLayoutProcessBar::InitElementTexture(const TextureName* array_texture)
{
    m_baseLayerTexture = array_texture[0];
    m_barBaseLayerTexture = array_texture[1];
    m_barFinishedLayerTexture = array_texture[2];
    m_slideLayerTexture = array_texture[3];
}

bool CLayoutProcessBar::CreateElement()
{
    const ILayoutNode* node = GetLayoutNode();
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
            100,
            600,
            1000,
            4,
            baseLayerMtl,
            &barROI,
            &sliderROI
            );
    }
    else
    {
        Log_Error("\n");
    }
    return true;
}

void CLayoutProcessBar::OnTouchEventDown()
{
    
}
void CLayoutProcessBar::OnTouchEventMove()
{
}
void CLayoutProcessBar::OnTouchEventUp()
{
    
}

Boolean CLayoutProcessBar::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
{
    switch(type)
    {
        case TouchEvent_Down: OnTouchEventDown(); break;
        case TouchEvent_Move: OnTouchEventMove(); break;
        case TouchEvent_Up:   OnTouchEventUp();   break;
        default: Log_Error(" unknown type: %d  from %s\n", type, __func__);
    }
    CXrSlideBar::OnTouchEvent(layerId, x, y, type);
}
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
