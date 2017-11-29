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
#include "log/LogHelper.hpp"
#include "global/config.h"
#include "GpuAvmEvent.h"

//前置申明
class AvmEvent;

namespace GUI
{
    /*
     * \brief CGUILayout 集成了Gpu构建hmi的基础功能
     */
    class ILayout : public LogHelper
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
        ILayout(const char* className);
        virtual ~ILayout();
        //! 控件事件分发， 静态表索引，抛出特定消息
        void Dispatch(const EVENT_HANDLE_T eventId, const uint32_t type);
        //! 使能layout(控制layout的绘制与否)
        void EnableLayout(int flag);

    protected:
        //! 初始化控件元素表
        void InitElementTable(struct ElementFuntionTable* table, const uint32_t elementNum);

        /*
         * \brief 绑定AvmEvent
         */
        bool AttachAvmEvent(const char* eventName);
        /*
         * \brief 请求AvmEvent,分配event 对象，用于数据填充
         */
        AvmEvent* RequestEvent(Layout_Event_Payload_T** payload);
        /*
         * \brief 请求post 指定数据
         */
        bool  PostEvent(AvmEvent* avm_event);
    protected:
        //Layout node (布局在Layout上的控件元素，都应该在此基础上进行绘制)
        IGUINode* m_node;
        int       m_node_id;
    private:
        //! 保存的原始控件表
        struct ElementFuntionTable* m_origin_element_info;
        uint32_t m_origin_table_size;
        AvmEventType m_eventType; //AvmEvent事件类型id
        const char* m_className;  //Layout className
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
