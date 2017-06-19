#ifndef _GPUELEMENTTEXT_H_ /* { */
#define _GPUELEMENTTEXT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementText.h
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
 * VERSION: 08 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrTextLabel.h"

namespace GUI
{
    /**
     * \brief CXrTextLable 对于text　label的区分不清(实现的是一个类似按钮的功能)
     *　　　　一个text label应该分为文本标签／文本编辑框(需要支持键盘等外设，不实现)／(富文本编辑框　不实现), 
     *　　　　因此重载CXrTextLable
     */
    class CGPUText : public IGUIElement
    {
    public:
        CGPUText();
        ~CGPUText();
        void SetTexture(const IGUITexture* effect, const long style);
        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetText(char* text);
    private:

        uint32_t m_layout_x, m_layout_y;
        uint32_t m_label_width, m_label_height;
        IGUITexture *m_base_texture,*m_font_texture;
        ITextLayer *m_pText;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUText, IGUIElement)
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTTEXT_H_ */
