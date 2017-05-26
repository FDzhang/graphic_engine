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

extern IXrCore* g_pIXrCore;
namespace GUI
{
    /**
     * \beief gpu控件元素信息表, 记录控件消息事件响应操作 
     * 对外操作接口的实现, 任何通过控件触发的消息都将从此处静态注册并返回需要的结果到system manager
     */
    struct Layout::ElementFuntionTable Layout::element_info[] =
    {
        { "CGPUButton", "Media_Play", 0, NULL, (PFCreateElement)(&Layout::InitMediaPlay), (PFOnEvent)&Layout::OnMediaPlayEvent},
        { "CGPUButton", "Media_Next", 0, NULL, (PFCreateElement)(&Layout::InitMediaNext), (PFOnEvent)&Layout::OnMediaNextEvent},
        { "CGPUButton", "Media_Prev", 0, NULL, (PFCreateElement)(&Layout::InitMediaPrev), (PFOnEvent)&Layout::OnMediaPrevEvent},
        { "CGPUProcessbar", "Media_Bar", 0, NULL, (PFCreateElement)(&Layout::InitMediaBar), (PFOnEvent)&Layout::OnMediaBarEvent},
        { "NULL", "NULL", 0, NULL, NULL, (PFOnEvent)&Layout::OnDefault},
    };

    
    IUINode* Layout::m_node = NULL;
    Layout::Layout()
        :m_element_table(NULL)
    {
        if(m_node == NULL)
        {
            g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_node);
            if(m_node == NULL)
            {
                ERROR("failed to create ui node\n");
            }
        }
        InitLayout(); //初始化DVR Layout 的控件元素(布局/事件注册)
    }

    Layout::~Layout()
    {
        for(int i =0 ; i < m_element_table_size; i++)
        {
            delete m_element_table[element_info[i].layerId].element;
        }
        delete[] m_element_table;
    }

    void Layout::DispatchEvent(uint32_t layerId, uint32_t type)
    {
        PFOnEvent event = m_element_table[layerId].OnEvent;
        if(event != NULL)
        {
            event(m_element_table[layerId].element, type);
        }
    }
    void Layout::InitLayout()
    {
        int maxId = 0 , element_id = 0;
        /**第一步: 动态创建控件元素对象*/
        m_element_table_size = sizeof( element_info) / sizeof( struct ElementFuntionTable) - 1;
        for( int i = 0; i < m_element_table_size; i++)
        {
            element_info[i].element = IGUIElement::Create(element_info[i].classname); //依据类名动态创建类对象
            element_info[i].CreateElement(element_info[i].element); //回调注册的对象初始化函数
            element_info[i].element->RegisterDispatch(this);
            int element_id =element_info[i].element ->GetElementId(); //获取layout id
            if(maxId < element_id) maxId = element_id; //获取layout中id的最大值
        }
        DEBUG(" max layerId is %d\n", maxId);
        /**第二步: 分配最大layout id的数组存储控件元素,对element_info重排序*/
        m_element_table = new ElementFuntionTable[maxId];
        for( int i = 0; i < m_element_table_size; i++)
        {
            memcpy(&m_element_table[element_info[i].layerId], &(element_info[i]), sizeof(ElementFuntionTable));
        }
    }

    /*--------------------------------------------------------------------------------
     * \brief DVR MEDIA PLAY BUTTON REFRENCE
     */
    void Layout::InitMediaPlay(const IGUIElement* media_play_button)
    {
        IGUITexture play_array_texture[] = { XR_RES_DVR"media_play.dds", XR_RES_DVR"media_pause.dds"};
        media_play_button->Attach(m_node);
        media_play_button->SetElementEffect(play_array_texture, GUI::GPU_GUI_EFFECT_TEXTURE);
        uint32_t property = GUI::GUI_BUTTON_EFFECT_LOCK;
        media_play_button->SetElementEffect(&property, GUI::GUI_EFFECT_BUTTON_PROPERTY);
        media_play_button->Create(155, 600, 50,50);
    }
    void Layout::OnMediaPlayEvent(const IGUIElement* element, const uint32_t type)
    {
        DEBUG("%s\n", __func__);
    }
    /*--------------------------------------------------------------------------------
     * \brief DVR MEDIA NEXT BUTTON REFRENCE
     */
    void Layout::InitMediaNext(const IGUIElement* media_next_button)
    {
        IGUITexture next_array_texture[] = { XR_RES_DVR"media_next.dds", XR_RES_DVR"BC64.dds"};
        media_next_button->Attach(m_node);
        media_next_button->SetElementEffect(next_array_texture, GUI::GPU_GUI_EFFECT_TEXTURE);
        media_next_button->Create(100, 600, 50,50);
    }
    void Layout::OnMediaNextEvent(const IGUIElement* element, const uint32_t type)
    {
        DEBUG("%s\n", __func__);
    }
    /*--------------------------------------------------------------------------------
     * \brief DVR MEDIA PREV BUTTON REFRENCE
     */
    void Layout::InitMediaPrev(const IGUIElement* media_prev_button)
    {
         IGUITexture prev_array_texture[] = { XR_RES_DVR"media_prev.dds", XR_RES_DVR"BC64.dds"};
         media_prev_button->Attach(m_node);
         media_prev_button->SetElementEffect(prev_array_texture, GUI::GPU_GUI_EFFECT_TEXTURE);
         media_prev_button->Create(210, 600, 50,50);
    }
    void Layout::OnMediaPrevEvent(const IGUIElement* element, const uint32_t type)
    {
        DEBUG("%s\n", __func__);
    }
    /*--------------------------------------------------------------------------------
     * \brief DVR MEDIA PROCESSBAR REFRENCE
     */
    void Layout::InitMediaBar(const IGUIElement* media_bar)
    {
        IGUITexture array_texture_bar[] = { XR_RES_DVR"barBase.dds"};
        media_bar->Attach(m_node);
        media_bar->SetElementEffect(array_texture_bar, GUI::GPU_GUI_EFFECT_TEXTURE);
        media_bar->Create(270, 615, 800, 4);
    }
    void Layout::OnMediaBarEvent(const IGUIElement* element, const uint32_t type)
    {
        DEBUG("%s\n", __func__);
    }

    void Layout::OnDefault(const IGUIElement* element, const uint32_t type)
    {
        DEBUG("%s\n", __func__);
    }
};

/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================

 *------------------------------------------------------------------------------------------*/
