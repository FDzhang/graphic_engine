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
#include "CmdTarget.h"

#ifndef OFILM_VIEW_ENGINE
#include "XrCore/XrSrc/External/IUINode.h"
#endif

namespace GUI
{
//typedef 封装数据类型, 提供统一的通用数据类型
    typedef char*   IGUITexture; /**纹理类型 默认纹理即文件纹理, 暂不实现纹理的绑定操作方法,待代码重构*/
    typedef IUINode IGUINode; /**node的创建,关系到整个绘制引擎, 待架构优化实现*/

    /**GUI特效设置*/

    /** GPU通用特效设置*/
    enum
    {
        GPU_GUI_EFFECT_TEXTURE,
        GPU_GUI_EFFECT_UNKNOWN = 0xf,
    };
    /** GUI通用特效设置*/
    enum
    {
        GUI_EFFECT_OPACITY = 0xf1,
        GUI_EFFECT_BUTTON_PROPERTY,
        GUI_EFFECT_PANEL_PROPERTY,
        GUI_EFFECT_PROCESSBAR_PROPERTY,
        GUI_EFFECT_UNKNOWN = 0xff,
    };
    /** 
     *  \brief IGUIElement是所有GUI绘制元素的基类, 提供统一的GUI绘制元素对外操作接口
     *         IGUIElement的接口抽象关系到GUI 绘制的灵活性:
     *             1.脚本实现对GUI布局以及GUI element逻辑关系
     *             2.良好的控件组合以及可扩展能力
     */
    class IGUIElement
    {
    public:
        IGUIElement(const char* name = "GUIElement")
            :m_node(NULL)
            ,m_id(-1)
            ,m_parent(0)
            ,m_elementName(name)
        {
        }
        virtual ~IGUIElement(){};
        void Attach(IGUINode* node, uint32_t parent = 0) {m_node = node; m_parent = parent;}
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
        /**
         * \brief GUI Element特效设置接口
         */
        virtual void SetElementEffect(void* effect, long style) = 0;
        /**
         * \brief 获取Element ID, 目前该id由XrCore创建, 用于消息区分
         */
        const uint32_t GetElementId() const { return m_id;}
        virtual void SetEnable(bool enable) = 0;
        virtual void Reset() {};
        // 临时注册消息分发函数
        void RegisterDispatch(CCmdTarget* cmdTarget) {m_cmdTarget = cmdTarget;};
    protected:
        const IGUINode* GetLayoutNode() const { return m_node;}
        const int32_t GetParent() const { return m_parent;}
        void SetElementId(uint32_t id) { m_id = id;}
        CCmdTarget* m_cmdTarget;
    private:
        uint32_t m_id;     //唯一身份标志, 目前保存的是XrCore引擎库设置的身份标志
        uint32_t m_parent;
        IGUINode* m_node;
        const char* m_elementName;
    private:
        static int32_t m_focus_id; //通过Element的ID 做焦点标志
        /**实现依据类名动态创建类对象的功能,声明动态基类特性*/
        DECLEAR_DYNAMIC_BASE(IGUIElement)
    };

    //针对GPU 绘制GUI 特效提供的接口, 为GUI 控件提供纹理特效,实现 GUI控件与绘制平台解耦
    void GPU_SetElementTexture(IGUIElement* element, const IGUITexture* array_texture, uint32_t array_size);
    void GPU_SetElementOpacity(IGUIElement* element, const uint32_t opacity);
    void GPU_SetElementEventEffect(IGUIElement* element, const uint32_t style);
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IGUIELEMENT_H_ */
