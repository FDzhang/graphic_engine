#ifndef _LAYOUTPROCESSBAR_H_ /* { */
#define _LAYOUTPROCESSBAR_H_
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
#include "LayoutElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrSlideBar.h"

class CLayoutProcessBar : public CLayoutElement ,private CXrSlideBar
{
    DECLARE_DYNAMIC(CLayoutProcessBar)
public:
    CLayoutProcessBar();
    virtual ~CLayoutProcessBar(){}
    void InitElementSize(uint32_t pos_x, uint32_t pos_y,
                         uint32_t element_width, uint32_t element_height,
                         uint32_t opacity);
    void InitElementTexture(const TextureName* array_texture);
    bool CreateElement();
protected:
    virtual void OnTouchEventDown();
    virtual void OnTouchEventMove();
    virtual void OnTouchEventUp();
private:
    /** 重写OnTouchEvent, 添加事件自定义处理功能*/
    Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y,Int32 type);

private:
    TextureName m_baseLayerTexture, m_barBaseLayerTexture, m_barFinishedLayerTexture, m_slideLayerTexture;
    uint32_t processbar_x, processbar_y;
    uint32_t processbar_width, processbar_height;
    ILayer   *m_pbaseLayer, *m_pbarBaseLayer, *m_pbarFinshedLayer, *m_pSliderLayer;
    uint32_t m_barWidth, m_barHeight;
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _LAYOUTPROCESSBAR_H_ */
