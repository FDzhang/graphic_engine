#ifndef _LAYOUT_H_ /* { */
#define _LAYOUT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: Layout.h
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
 * VERSION: 25 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementButton.h"
#include "GpuElementProcessbar.h"
#include "GpuElementPanel.h"

#define DECLEAR_ELEMENT_EVENT

namespace GUI
{
    typedef void (* PFCreateElement)(const IGUIElement*);
    typedef void  (*PFOnEvent)(const IGUIElement*, const uint32_t type);
    class Layout : public CCmdTarget
    {
        struct ElementFuntionTable
        {
            const char*  classname;    //element 的类名
            const char*  element_name; //element 元素名
            uint32_t     layerId;      //element 身份标识ID
            IGUIElement* element;
            //void  (*CreateElement)(const IGUIElement*);  //初始化element的函数指针
            //void  (*OnEvent)(const IGUIElement*, const uint32_t type); //element 消息响应函数
            PFCreateElement CreateElement;
            PFOnEvent OnEvent;
        };
    public:
        Layout();
        ~Layout();
        void DispatchEvent(uint32_t layerId, uint32_t type);
    protected:
        virtual void InitLayout();
        seta();
    private:
        static IUINode* m_node;
        static struct ElementFuntionTable element_info[];
        //控件消息响应内部接口
        static void InitMediaPlay(const IGUIElement*);
        static void OnMediaPlayEvent(const IGUIElement*, const uint32_t);
        static void InitMediaNext(const IGUIElement*);
        static void OnMediaNextEvent(const IGUIElement*, const uint32_t);
        static void InitMediaPrev(const IGUIElement*);
        static void OnMediaPrevEvent(const IGUIElement*, const uint32_t);
        static void InitMediaBar(const IGUIElement*);
        static void OnMediaBarEvent(const IGUIElement*, const uint32_t);
        static void OnDefault(const IGUIElement*, const uint32_t);
    private:
        struct ElementFuntionTable* m_element_table;
        uint32_t m_element_table_size;

        uint32_t a;
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _LAYOUT_H_ */
