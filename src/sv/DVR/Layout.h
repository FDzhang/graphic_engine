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
#include "GpuElementText.h"

namespace GUI
{
    class ILayout : public CCmdTarget
    {
    protected:
        typedef void  (ILayout::*PFCreateElement)(const IGUIElement*, uint32_t parentId);
        typedef void  (ILayout::*PFOnEvent)(const IGUIElement*, const uint32_t type);
        typedef void  (ILayout::*PFDeCreateElement)(const IGUIElement*);
        struct ElementFuntionTable
        {
            const char*         classname;       //element 的类名
            const char*         element_name;    //element 元素名
            int32_t             element_level;   //控件等级
            uint32_t            layerId;         //element 身份标识ID
            IGUIElement*        element;         //控件对象
            PFCreateElement     CreateElement;   //控件初始化方法
            PFOnEvent           OnEvent;         //控件事件响应方法 (默认不实现，除非存在自定义事件响应)
            PFDeCreateElement   DeCreateElement; //控件释放方法(默认不实现，除非存在自定义资源需要释放)
        };
    public:
        ILayout(struct ElementFuntionTable* table, const uint32_t elementNum);
        ~ILayout();
        //! 控件事件分发， 静态表索引，抛出特定消息
        void DispatchEvent(uint32_t layerId, uint32_t type);
        //! 使能layout(控制layout的绘制与否)
        void EnableLayout(int flag);
    protected:
        //! Layout的元素事件响应(将所有Layout 上的控件消息集中管理并发送)
        void OnEvent(const IGUIElement*, uint32_t type);
    private:
        //! 初始化控件布局
        void InitLayout();
    protected:
        IUINode* m_node;  //Layout node (布局在Layout上的控件元素，都应该在此基础上进行绘制)
        int      m_node_id;
    private:
        //! 控件事件索引表
        struct ElementFuntionTable* m_index_element_table;
        uint32_t m_index_table_size;
        
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
