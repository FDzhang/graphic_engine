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
#include "event/AvmEvent.h"
#include "XrCore/XrSrc/External/IXrCore.h"

namespace GUI
{
    ILayout::ILayout()
        :m_node(NULL), m_node_id(0)
        ,m_origin_element_info(NULL)
        ,m_origin_table_size(0)
    {
    }

    ILayout::~ILayout()
    {
        //控件元素在ILayout中创建， ILayout有责任释放
        if(m_origin_element_info)
        {
            for(int index =0 ; index < m_origin_table_size - 1; index++)
            {
                delete m_origin_element_info[index].element;
            }
        }
    }

    void ILayout::Dispatch(const EVENT_HANDLE_T eventId, const uint32_t type)
    {
        //if(m_index_element_table) //不需进行检查, m_index_element_table 为NULL,即代表内存分配失败
        {
            PFOnEvent event = m_origin_element_info[eventId].OnEvent;
            if(event != NULL)
            {
               (this->*event)(m_origin_element_info[eventId].element);
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
    
    void ILayout::InitElementTable(struct ElementFuntionTable* table, const uint32_t elementNum)
    {
        if(table != NULL && elementNum > 0)
        {
            m_origin_table_size = elementNum;
            m_origin_element_info = table;
        }
        DEBUG("Layout origin size is %d\n", m_origin_table_size);
        
        if(m_node != NULL)
        {
            INFO("Layout has created , don't create it again\n");
            return;
        }
        //! 第一步，获取控件最大深度
        int maxId = 0;
        for( int index = 0; index <m_origin_table_size ; index++)
        {
            int element_id = m_origin_element_info[index].elementLevel;
            if(maxId < element_id)
            {
                maxId = element_id;
            }
        }
        uint32_t* rootId = new uint32_t[maxId];
        //root id 默认为-1
        rootId[0] = -1;

        //! 第二步　在Layout Node上创建元素对象
        IXrCore* core = GetXrCoreInterface();
        m_node_id = core->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_node);
        if(m_node == NULL)
        {
            ERROR("failed to create ui node\n");
            return;
        }
            
        for( int index = 0; index <m_origin_table_size; index++)
        {
            DEBUG("%s:create %s element\n", __func__, m_origin_element_info[index].className);
            //依据类名动态创建类对象
            m_origin_element_info[index].element = IGUIElement::Create(m_origin_element_info[index].className);
            //回调注册的对象初始化函数
            (this->*(m_origin_element_info[index].CreateElement))(m_origin_element_info[index].element,
                                                                  rootId[m_origin_element_info[index].elementLevel - 1]);
            //设置控件元素事件Id
            m_origin_element_info[index].element->EventId((EVENT_HANDLE_T)index);
            m_origin_element_info[index].element->RegisterDispatch(this);
            //获取layout id
            const int element_id = m_origin_element_info[index].element ->GetHwnd();
            m_origin_element_info[index].layerId = element_id;
            //更新子控件的rootId
            rootId[m_origin_element_info[index].elementLevel] = element_id;
            DEBUG("current element rootId is %d, child element rootId is %d eventId is %d\n",
                  rootId[m_origin_element_info[index].elementLevel - 1],
                  rootId[m_origin_element_info[index].elementLevel],
                  m_origin_element_info[index].element->EventId()
                );
        }
        delete[] rootId; //释放rootId动态数组

    }

    AvmEventType ILayout::AttachEvent( const char* name, uint32_t payload_size)
    {
        if( name == NULL || payload_size == 0)
        {
            return AvmEvent::Invalid_Event_Type;
        }
        return( AvmRegisterEvent(name, payload_size));
    }

    AvmEvent* ILayout::RequestEvent(void** payload)
    {
        AvmEventType m_event_type = GetAttachEventType();
        if( m_event_type == AvmEvent::Invalid_Event_Type)
        {
            ERROR("not a right avm event type id");
            return NULL;
        }
        AvmEvent* avm_event = AvmRequestEvent(m_event_type);
        RawAvmEvent* raw_event = avm_event->GetRawEvent();
        *payload = raw_event->payload;
        return avm_event;
    }
    
    bool ILayout::PostEvent(AvmEvent* avm_event)
    {
        if(avm_event != NULL)
        {
            AvmPostEvent(*avm_event, NULL);
            AvmEventReleaseAndTrace(*avm_event);
            return true;
        }
        else
        {
            ERROR("please make sure the avm_event is valid\n");
            return false;
        }
    }
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
