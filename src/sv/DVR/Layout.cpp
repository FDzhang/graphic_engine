/*------------------------------------------------------------------------------------------
 * FILE: Layout.cpp
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
 * VERSION: 25 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "Layout.h"

namespace GUI
{
    ILayout::ILayout(struct ElementFuntionTable* table, const uint32_t elementNum)
        :m_origin_element_info(table)
        ,m_origin_table_size(elementNum)
        ,m_index_element_table(NULL)
        ,m_index_table_size(0)
        ,m_node(NULL)
    {
        DEBUG("Layout origin size is %d\n", m_origin_table_size);
        if(m_node == NULL)
        {
            IXrCore* core = GetXrCoreInterface();
            m_node_id = core->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_node);
            if(m_node == NULL)
            {
                ERROR("failed to create ui node\n");
            }
        }
        InitLayout(); //初始化DVR Layout 的控件元素(布局/事件注册)
    }

    ILayout::~ILayout()
    {
        if(m_index_element_table)
        {
            for(int i =0 ; i < m_origin_table_size - 1; i++)
            {
                delete m_index_element_table[m_origin_element_info[i].layerId].element;
            }
            delete[] m_index_element_table;
        }
    }

    void ILayout::DispatchEvent(uint32_t layerId, uint32_t type)
    {
        //if(m_index_element_table) //不需进行检查, m_index_element_table 为NULL,即代表内存分配失败
        {
            PFOnEvent event = m_index_element_table[layerId].OnEvent;
            if(event != NULL)
            {
                (this->*event)(m_index_element_table[layerId].element, type);
            }
        }
    }

    void ILayout::EnableLayout(int flag)
    {
        if(m_node)
        {
            m_node->SetEnable(flag);
        }
        else
        {
            DEBUG("Please InitLayout First\n");
        }
    }
    
    void ILayout::InitLayout()
    {
        int maxId = 0;
        //第一步，获取控件最大深度
        for( int i = 0; i <m_origin_table_size - 1; i++)
        {
            int element_id = m_origin_element_info[i].element_level;
            if(maxId < element_id)
            {
                maxId = element_id;
            }
        }
        uint32_t* rootId = new uint32_t[maxId]; rootId[0] = -1;
        if(rootId)
        {
            /**第二步: 动态创建控件元素对象*/
            for( int i = 0; i <m_origin_table_size - 1; i++)
            {
                DEBUG("%s:create %s element\n", __func__, m_origin_element_info[i].classname);
                //依据类名动态创建类对象
                m_origin_element_info[i].element = IGUIElement::Create(m_origin_element_info[i].classname); 
                //回调注册的对象初始化函数
                (this->*(m_origin_element_info[i].CreateElement))(m_origin_element_info[i].element,
                                                                  rootId[m_origin_element_info[i].element_level - 1]);
                m_origin_element_info[i].element->RegisterDispatch(this);
                //获取layout id
                int element_id =m_origin_element_info[i].element ->GetElementId();
                m_origin_element_info[i].layerId = element_id;
                //更新子控件的rootId
                rootId[m_origin_element_info[i].element_level] = element_id;
                DEBUG("current element rootId is %d, child element rootId is %d\n",
                      rootId[m_origin_element_info[i].element_level - 1],
                      rootId[m_origin_element_info[i].element_level]);
                if(maxId < element_id) maxId = element_id; //获取layout中id的最大值
            }
            delete[] rootId;
            DEBUG("element max layerId is %d\n", maxId);
            /**第三步: 分配最大layout id的数组存储控件元素,对element_info重排序*/
            m_index_element_table = new struct ElementFuntionTable[maxId + 1];
            for( int i = 0; i < m_origin_table_size - 1; i++)
            {
                memcpy(&m_index_element_table[m_origin_element_info[i].layerId],
                       &(m_origin_element_info[i]),
                       sizeof(struct ElementFuntionTable));
                DEBUG("m_origin_element_info[%d].layerId is %d, %p copy to %p\n",
                      i,
                      m_origin_element_info[i].layerId,
                      &(m_origin_element_info[i]),
                      &(m_index_element_table[m_origin_element_info[i].layerId]));
            }
        }
    }

    void ILayout::OnEvent(const IGUIElement* element, uint32_t type)
    {
        
    }
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
