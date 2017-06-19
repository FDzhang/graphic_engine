#ifndef _IGUIELEMENT_H_ /* { */
#define _IGUIELEMENT_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: IGUIElement.h
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
 * VERSION: 13 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "RuntimeClass.h"

#ifndef OFILM_VIEW_ENGINE
#include "XrCore/XrSrc/External/IUINode.h"
#include "XrCore/XrSrc/External/IEventResponder.h"
#endif

namespace GUI
{
    //typedef 封装数据类型, 提供统一的通用数据类型
    typedef int32_t GUI_HANDLE_T;   //GUI控件句柄
    typedef int32_t EVENT_HANDLE_T; //事件句柄
    //typedef char*   IGUITexture; /**纹理类型 默认纹理即文件纹理, 暂不实现纹理的绑定操作方法,待代码重构*/
    struct IGUITexture
    {
        const char*    texName;
        const uint32_t pos_x, pos_y;
        const uint32_t element_width, element_height;
    };
            
    typedef IUINode IGUINode; /**node的创建,关系到整个绘制引擎, 待架构优化实现*/

    /** 
     *  \brief IGUIElement是所有GUI绘制元素的基类, 提供统一的GUI绘制元素对外操作接口
     *         IGUIElement的接口抽象关系到GUI 绘制的灵活性:
     *             1.脚本实现对GUI布局以及GUI element逻辑关系
     *             2.良好的控件组合以及可扩展能力
     */
    class ILayout;
    class IGUIElement
    {
    public:
        IGUIElement(const char* name);
        virtual ~IGUIElement();
        void Attach(const IGUINode* node, const GUI_HANDLE_T parent = 0) {m_node = node; m_parent = parent;}
        /**
         *  \brief 创建GUI Element, 接口函数
         *  \param [IN] pos_x , pos_y  元素绘制位置(相对于parent的位置)
         *  \param [IN] element_width, element_height 元素size
         *  \param [IN] style  GUI元素特性
         */
        virtual bool Create(const uint32_t pos_x, const uint32_t pos_y,
                            const uint32_t element_width, const uint32_t element_height) = 0;
        /**
         *  \brief 设置焦点, 默认的情况下,所有的GUI Element的事件皆由GUI引擎通知调度
         */
        virtual void SetFocus() { m_focus_id = m_id;}
        //! 设置控件元素纹理以及控件特效
        virtual void SetTexture(const IGUITexture* effect, long style) = 0;
        //! 设置控件元素透明度
        virtual void SetOpacity(uint32_t opacity) {};
        //! 设置控件元素文本内容
        virtual void SetText(char* text){};
        
        /* 
         * \brief 获取当前用于绘制的当前窗口安全句柄
         *　　　　 note: 暂未实现对句柄安全的保证, 后期会重写GUI_HANDLE_T,实现句柄的安全
         */
        const GUI_HANDLE_T GetHwnd() const { return m_id;}
        //! 设置Element的Event ID
        void EventId(const EVENT_HANDLE_T eventId) { m_eventId = eventId;}
        //! 获取Element的Event ID
        const EVENT_HANDLE_T EventId() const { return m_eventId;}

        /**********************************************************************************
         * \brief 控件元素通用操作
         */
        //使能控件元素
        virtual void Enable(bool enable){};
        //重置控件元素
        virtual void Reset() {};
        //注册消息分发函数
        void RegisterDispatch(ILayout* cmdTarget) {m_cmdTarget = cmdTarget;};
    protected:
        //! 获取layout Id
        IUINode* GetLayoutNode() const { return m_node;}
        //! 获取父类控件Id
        const GUI_HANDLE_T GetParent()  const { return m_parent;}
        //! 设置控件句柄(由子类创建后设置)
        void  SetHwnd(const GUI_HANDLE_T id)      { m_id = id;}
        //! 通知事件对象处理
        void DispatchEvent(const EVENT_HANDLE_T eventId, const uint32_t type);
    private:
        //! 唯一身份标志, 目前保存的是XrCore引擎库设置的身份标志
        GUI_HANDLE_T m_id;
        //! 父类控件id
        GUI_HANDLE_T m_parent;
        //! 事件id
        EVENT_HANDLE_T m_eventId;
        //! 控件事件对象
        ILayout* m_cmdTarget;
        //Gpu绘制layout node
        IUINode* m_node;
        //控件类型名
        const char* m_elementName;

    private:
        static int32_t m_focus_id; //通过Element的ID 做焦点标志
        /**实现依据类名动态创建类对象的功能,声明动态基类特性*/
    private:
        DECLEAR_DYNAMIC_BASE(IGUIElement)
    };

    typedef void  (IGUIElement::*Responder)(Int32 layerId, Int32 x, Int32 y, Int32 type);
    
    class EventResponder : public IEventResponder
    {
    public:
        EventResponder(IGUIElement* element, Responder event)
            :IEventResponder()
            ,m_responder(event)
            ,m_element(element)
        {
        }
        ~EventResponder() { if(m_responder) m_responder = NULL;}
    private:
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
        {
            (m_element->*m_responder)(layerId, x, y, type);
        }
        String GetName(){} 
        Void SetName(String name){}; 
        Void* GetRealType() {}; 
    private:
        Responder m_responder;
        IGUIElement* m_element;
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IGUIELEMENT_H_ */
