#ifndef _GPUELEMENTLISTVIEW_H_ /* { */
#define _GPUELEMENTLISTVIEW_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementListView.h
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
 * VERSION: 01 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "IGUIElement.h"
#include "XrCore/XrSrc/XrUILibrary/CXrSelector.h"

namespace GUI
{
    class CGPUListView : public IGUIElement , private CXrBaseView
    {
    public:
        CGPUListView();
        ~CGPUListView();

        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetTexture(const IGUITexture* effect, const long style);
        //! 使能列表框(overwirte IGUIElement)
        void Enable(bool enable);
        //! 清空文件列表内容
        void Reset();
        //! 获取当前选中的item
        uint32_t GetCurrentIndex()  const { return m_current_item->index;}
        //! 删除当前选中的item,触发删除与更新列表操作
        uint32_t DeleteCurrentItem() {}
        //! 更新列表(更新列表文本的同时，更新itemNum)
        void SetText(const char* text[], uint32_t itemNum);
        //! 修改列表框对应index的文本(不更新itemNum)
        void SetItemText(const char* text, int32_t index);

        //! 列表框向上移动，false表示越界, 选中框不移动
        bool PrevItem();
        //! 列表框向下移动，false表示越界, 选中框不移动
        bool NextItem();
        //! 同步列表框hmi status
        void Sync();
    protected:
        void OnItemSelected(EventResponder* responder, Int32 x, Int32 y, Int32 type);
    private:
        //重载事件响应
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type);

    private:
        uint32_t m_itemNum;
        uint32_t m_pos_x, m_pos_y;
        uint32_t m_element_width, m_element_height;
        
        IGUITexture* m_base_texture                 ;
        IGUITexture* m_listview_item_texture        ;
        IGUITexture* m_listview_itemSelected_texture;
        IGUITexture* m_listview_itemOk_texture;
        IGUITexture* m_listview_font_texture        ;

        //目前暂定为固定数目的列表
        struct ListViewItem
        {
            Int32 m_itemSpirtId;
            ILayer* m_itemLayer;
            ITextLayer* m_itemText; //文字绘制层
            
            uint32_t indexFile;     //对应的文件索引号
            uint32_t index;         //item 序列号
            bool valid;
            EventResponder* responder;
        }*m_listview_item, *m_current_item;

        //列表框下方的上/下翻页 上/下选择layer
        ILayer* m_itemOkLayer, *m_itemSelectedLayer;
        ITextLayer* m_itemOkTextLayer;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUListView, IGUIElement)
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTLISTVIEW_H_ */
