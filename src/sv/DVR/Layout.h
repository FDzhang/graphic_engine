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
#include "IGUIElement.h"
#include "event/RawAvmEvent.h"
#include "event/AvmEvent.h"

namespace GUI
{
    class ILayout
    {
    protected:
        typedef void  (ILayout::*PFCreateElement)(IGUIElement*, const GUI_HANDLE_T parentId);
        typedef void  (ILayout::*PFOnEvent)(IGUIElement*);
        typedef void  (ILayout::*PFDeCreateElement)(const IGUIElement*);
        struct ElementFuntionTable
        {
            const char*         className;       //element 的类名
            const char*         elementName;    //element 元素名
            int32_t             elementLevel;   //控件等级
            uint32_t            layerId;         //element 身份标识ID
            IGUIElement*        element;         //控件对象
            PFCreateElement     CreateElement;   //控件初始化方法
            PFOnEvent           OnEvent;         //控件事件响应方法 (默认不实现，除非存在自定义事件响应)
            PFDeCreateElement   DeCreateElement; //控件释放方法(默认不实现，除非存在自定义资源需要释放)
        };
    public:
        ILayout();
        virtual ~ILayout();
        //! 控件事件分发， 静态表索引，抛出特定消息
        void Dispatch(const EVENT_HANDLE_T eventId, const uint32_t type);
        //! 使能layout(控制layout的绘制与否)
        void EnableLayout(int flag);
        //! AttachEvent 注册SystemEvent消息
        static AvmEventType AttachEvent(const char* name, uint32_t payload_size);
    protected:
        //! 初始化控件元素表
        void InitElementTable(struct ElementFuntionTable* table, const uint32_t elementNum);
        /* 
         * \brief 请求event创建payload用于填充raw data
         * [OUT] payload raw date pointer
         * [return] AvmEvent* event数据对象，调用者无需关心
         */
        AvmEvent* RequestEvent(void** payload);
        static bool PostEvent(AvmEvent* avm_event);
        //! 获取AvmEvent 默认是无效event type
        virtual AvmEventType GetAttachEventType() {return AvmEvent::Invalid_Event_Type;}

    protected:
        //Layout node (布局在Layout上的控件元素，都应该在此基础上进行绘制)
        IGUINode* m_node;
        int      m_node_id;
    private:
        //! 保存的原始控件表
        struct ElementFuntionTable* m_origin_element_info;
        uint32_t m_origin_table_size;
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
