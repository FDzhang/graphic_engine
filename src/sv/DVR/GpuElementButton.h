#ifndef _GPU_ELEMENT_BUTTON_H_ /* { */
#define _GPU_ELEMENT_BUTTON_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuElementButton.h
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
#include "XrCore/XrSrc/XrUILibrary/IActionTrigger.h"
#include "XrCore/XrSrc/XrUILibrary/CXrButton.h"
#include "IGUIElement.h"

namespace GUI
{
    /**按钮属性设置*/
    enum
    {
        GUI_BUTTON_EFFECT_DEFAULT,         /**默认按钮属性*/
        GUI_BUTTON_EFFECT_TEXT,            /**设置按钮为文本式开关*/
        GUI_BUTTON_EFFECT_LOCK,            /**设置按钮为自锁式开关*/
    };


    
    /**
     * \Author: dota2_black
     * \brief: CXrButton的事件机制(通过IActionTrigger注册操作方法进入CXrButton),将设置button属性和设置button的操作方法分离
     *         重写为合并的方法(创建不同videobutton的开发者需要同时负责button的属性以及功能, private IActionTrigger为适配
     *         CXrButton的绘制
     * \param[in] name button text naXme
     * 
     */
    class CGPUButton : public IGUIElement,  private CXrButton
    {
    public:
        /** cornerSize默认值设为-1, 表征不对纹理文件做特殊处理,直接使用调用者的纹理文件*/
        CGPUButton();
        virtual ~CGPUButton();
    
        bool Create(const uint32_t pos_x, const uint32_t pos_y,
                    const uint32_t element_width, const uint32_t element_height);
        void SetTexture(const IGUITexture* effect, const long style);
        void SetEnable(bool enable);
        void Reset() ;
    private:
        Boolean OnTouchEvent(Int32 layerId, Int32 x, Int32 y, Int32 type);
    private:
        uint32_t m_layout_x, m_layout_y;
        uint32_t m_button_width, m_button_height; 
        IGUITexture* m_base_texture;
        IGUITexture* m_hit_texture;

        uint32_t m_button_opacity;
        uint32_t m_button_property;
        uint32_t m_baseOpacity;
        uint32_t m_hitOpacity;
    private:
        DECLEAR_DYNAMIC_CLASS(CGPUButton, IGUIElement)
    };
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPU_ELEMENT_BUTTON_H_ */
