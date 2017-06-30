/*------------------------------------------------------------------------------------------
 * FILE: GpuElementListView.cpp
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
 * VERSION: 14 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "GpuElementListView.h"
#include "Layout.h"
#include "XrCore/XrSrc/External/IXrCore.h"

namespace GUI
{
    CGPUListView::CGPUListView()
        :IGUIElement("CGPUListView")
        ,CXrBaseView()
        ,m_itemNum(8)
        ,m_pos_x(0), m_pos_y(0)
        ,m_element_width(0), m_element_height(0)
        ,m_listview_item(NULL)
        ,m_current_item(NULL)
    {
        m_listview_item = new struct ListViewItem[m_itemNum];
    }
    CGPUListView::~CGPUListView()
    {
        for(int index = 0; index < m_itemNum; index++)
        {
            delete m_listview_item[index].responder;
            m_listview_item[index].responder = NULL;
        }
        delete[] m_listview_item;
    }
    bool CGPUListView::Create(const uint32_t pos_x, const uint32_t pos_y,
                              const uint32_t element_width, const uint32_t element_height)
    {
        m_pos_x = pos_x; m_pos_y = pos_y;
        m_element_width = element_width;
        m_element_height = element_height;
        IGUINode* node = GetLayoutNode();
        if(node)
        {
            InsertFlag flag = InsertFlag_Child;
            int32_t parent = GetParent();
            if(parent < 0)
            {
                //控件不存在父节点id
                parent = -1;
                flag = InsertFlag_Default;
            }
            //列表框背景
            Int32 bgId= node->CreateUIMaterial(Material_UI_Spirit, const_cast<char*>(m_base_texture->texName));
            //列表框文本项
            Int32 textItemId = node->CreateUIMaterial(Material_UI_Spirit,
                                                      const_cast<char*>(m_listview_item_texture->texName));
            Int32 textSelectedItemId = node->CreateUIMaterial(Material_UI_Spirit,
                                                              const_cast<char*>(m_listview_itemSelected_texture->texName));
            Int32 textOkItemId = node->CreateUIMaterial(Material_UI_Spirit,
                                                        const_cast<char*>(m_listview_itemOk_texture->texName));
            Int32 fontId = node->CreateUIFontMaterial(const_cast<char*>(m_listview_font_texture->texName), 0);
            
            Int32 rootId = node->CreateSpirit(parent, flag, bgId, 1.0,
                                              m_pos_x, m_pos_y,
                                              0,
                                              m_element_width, m_element_height);
            for(int index = 0; index < m_itemNum; index++)
            {
                //按要求创建指定数目的listview item子控件
                m_listview_item[index].m_itemSpirtId =
                    node->CreateSpirit(rootId, InsertFlag_Child, textItemId, 1.0,
                                       m_listview_item_texture->pos_x,
                                       m_listview_item_texture->pos_y + m_listview_item_texture->element_height* index,
                                       0,
                                       m_listview_item_texture->element_width,
                                       m_listview_item_texture->element_height);
                m_listview_item[index].index = index;
                //为每个子控件注册触摸事件
                m_listview_item[index].m_itemLayer = node->GetLayer(m_listview_item[index].m_itemSpirtId);
                m_listview_item[index].responder = new EventResponder(this, (Responder)(&CGPUListView::OnItemSelected));
                (m_listview_item[index].responder)->SetPrivateData(&(m_listview_item[index]));
                (m_listview_item[index].m_itemLayer)->SetEventResponder(m_listview_item[index].responder);
            }

            for(int index = 0; index < m_itemNum; index++)
            {
                //为每个控件添加text layer
                node->CreateTextLayer(m_listview_item[index].m_itemSpirtId, InsertFlag_Child, fontId, 1,
                                             0.1 * m_listview_item_texture->element_width,
                                             0.1 * m_listview_item_texture->element_height,
                                             &(m_listview_item[index].m_itemText),
                                             m_listview_item_texture->element_width * 0.8 ,
                                             m_listview_item_texture->element_height * 0.8);
                m_listview_item[index].m_itemText->SetOpacity(1.0);
                m_listview_item[index].m_itemText->SetFontSize(20);
                m_listview_item[index].m_itemText->SetColor(1.0, 1.0, 1.0);
                m_listview_item[index].valid = false;
            }
            //选择框, 单击选择框表示选中进行播放
            Int32 itemSelectedId = node->CreateSpirit(rootId, InsertFlag_Child,
                                                      textSelectedItemId, 1.0,
                                                      m_listview_itemSelected_texture->pos_x,
                                                      m_listview_itemSelected_texture->pos_y,
                                                      0,
                                                      m_listview_itemSelected_texture->element_width,
                                                      m_listview_itemSelected_texture->element_height);
            m_itemSelectedLayer = node->GetLayer(itemSelectedId);
            m_itemSelectedLayer -> SetEventResponder(this);

            //当前播放文件项
            Int32 itemOkId = node->CreateSpirit(rootId, InsertFlag_Child,
                                                textOkItemId, 1.0,
                                                m_listview_itemOk_texture->pos_x,
                                                m_listview_itemOk_texture->pos_y,
                                                0,
                                                m_listview_itemOk_texture->element_width,
                                                m_listview_itemOk_texture->element_height);
            m_itemOkLayer = node->GetLayer(itemOkId);
            node->CreateTextLayer(itemOkId, InsertFlag_Child, fontId, 1,
                                  0.1*m_listview_itemOk_texture->element_width,
                                  0.1*m_listview_itemOk_texture->element_height,
                                  &m_itemOkTextLayer,
                                  m_listview_itemOk_texture->element_width ,
                                  m_listview_itemOk_texture->element_height);
            m_itemOkTextLayer->SetOpacity(1.0);
            m_itemOkTextLayer->SetFontSize(20);
            m_itemOkTextLayer->SetColor(1.0, 1.0, 0); //当前正在播放的文件为红色
            
            //初始化当前选中框
            m_current_item = &(m_listview_item[0]);
            IGUIElement::SetHwnd((GUI_HANDLE_T)rootId);
        }
    }
    
    void CGPUListView::SetTexture(const IGUITexture* effect, const long style)
    {
        m_base_texture                  = &(((IGUITexture*)effect)[0]);
         m_listview_itemOk_texture       = &(((IGUITexture*)effect)[1]);
        m_listview_item_texture         = &(((IGUITexture*)effect)[2]);
        m_listview_itemSelected_texture = &(((IGUITexture*)effect)[3]);
        m_listview_font_texture         = &(((IGUITexture*)effect)[4]);
    }
    void CGPUListView::Enable(bool enable)
    {
        IGUINode* node = GetLayoutNode();
        if(node)
        {
            ILayer* layer = node->GetLayer(GetHwnd());
            layer->SetEnable(enable);
        }
    }
    /*清空文件列表内容*/
    void CGPUListView::Reset()
    {
        for(int index = 0; index < m_itemNum; index++)
        {
            m_listview_item[index].m_itemText->SetText("");
            m_listview_item[index].m_itemLayer->SetEnable(false);
            m_listview_item[index].valid = false;
        }
    }
    void CGPUListView::OnItemSelected(EventResponder* responder, Int32 x, Int32 y, Int32 type)
    {
        switch(type)
        {
            case TouchEvent_Down:
            {
                struct ListViewItem* item =  (struct ListViewItem*)(responder->GetPrivateData());
                m_itemSelectedLayer->SetY((item->m_itemLayer)->GetY());
                //更新current指针
                m_current_item = item;
                break;
            }
            default:
                break;
        }
        return TRUE;
    }
    /*文件列表框选择下一个item*/
    bool CGPUListView::PrevItem()
    {
        struct ListViewItem* item = &(m_listview_item[(m_itemNum + m_current_item->index - 1) % m_itemNum]);
        //判断是否越界
        if(m_current_item->index == 0)
        {
            //m_current_item = item;
            return false;
        }
        m_current_item = item;
        m_itemOkTextLayer->SetText(const_cast<char*>((m_current_item->m_itemText)->GetText()));
        m_itemSelectedLayer->SetY(m_listview_item_texture->pos_y +
                                  m_current_item->index * m_listview_item_texture->element_height);
        return true;
    }
    /**文件列表框选择上一个item*/
    bool CGPUListView::NextItem()
    {
        //! 第一步， 选中栏循环跳转
        struct ListViewItem* item = &(m_listview_item[(m_current_item->index + 1) % m_itemNum]);
        //判断是否越界,或者到了文件列表末尾
        if(m_current_item->index == (m_itemNum - 1) || !(item->valid))
        {
            //m_current_item = item;
            return false;
        }
        m_current_item = item;
        m_itemOkTextLayer->SetText(const_cast<char*>((m_current_item->m_itemText)->GetText()));
        m_itemSelectedLayer->SetY(m_listview_item_texture->pos_y +
                                  m_current_item->index * m_listview_item_texture->element_height);
        return true;
    }

    void CGPUListView::SetText(const char* text[], uint32_t itemNum)
    {
        for(int index = 0; index < itemNum; index++)
        {
            //使能对应item
            m_listview_item[index].m_itemLayer->SetEnable(true);
            //更新列表框文字
            m_listview_item[index].m_itemText->SetText(const_cast<char*>(text[index]));
        }
    }
    void CGPUListView::SetItemText(const char* text, int index)
    {
        m_listview_item[index].m_itemLayer->SetEnable(true);
        m_listview_item[index].m_itemText->SetText(const_cast<char*>(text));
        m_listview_item[index].valid = true;
    }

    Boolean CGPUListView::OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type)
    {
        switch(type)
        {
        case TouchEvent_Down:
            m_itemOkTextLayer->SetText(const_cast<char*>((m_current_item->m_itemText)->GetText()));
            IGUIElement::DispatchEvent(IGUIElement::EventId(), type);
            break;
        case TouchEvent_Up:
            break;
        default:
            break;
        }
        return TRUE;
    }
    void CGPUListView::Sync()
    {
        m_current_item = &(m_listview_item[0]);

        
        /*临时添加的在第一次sync列表框时，默认播放第一个文件*/
        static bool first = true;
        if(first)
        {
            m_itemOkTextLayer->SetText(const_cast<char*>((m_current_item->m_itemText)->GetText()));
            first = false;
        }
        
        //同步选中框状态，若itemSelected位置没有及时更新，则重新更新状态
        m_itemSelectedLayer->SetY(m_current_item->m_itemLayer->GetY());
    }
    IMPLEMENT_DYNAMIC_CLASS(CGPUListView)
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *==========================================================================================
 *
 * Date             SCR                      user                              Description
 *==========================================================================================
 *------------------------------------------------------------------------------------------*/
