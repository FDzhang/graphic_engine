#ifndef _FRONT_LAYOUT_H_ /* { */
#define _FRONT_LAYOUT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: Front_Layout.h
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
 * VERSION: 19 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "Layout.h"
#include "GpuElementIcon.h"
#include "IF_Front.h"

namespace GUI
{
    class Front_Layout : public ILayout , public IFrontLayout
    {
    public:
        Front_Layout();
        ~Front_Layout();
        static IFrontLayout* GetLayout();
        void Init() {};
        void Enable(bool flag) ;

        /*光标作为一个始终拥有焦点的控件，在目前架构中，需要特殊处理*/
        void OnMouseMove(int x, int y);
        void OnMouseUp(int x, int y);
        void OnMouseDown(int x, int y);
    private:
        uint32_t m_element_size;
        static struct ElementFuntionTable m_element_info[];
    private:
        void InitMouseCursor(IGUIElement* , const GUI_HANDLE_T);
    private:
        CGPUIcon* m_cursor;
        static Front_Layout* m_layout;
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _FRONT_LAYOUT_H_ */
