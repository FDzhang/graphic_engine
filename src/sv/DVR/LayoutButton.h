#ifndef _LAYOUTBUTTON_H_ /* { */
#define _LAYOUTBUTTON_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: LayoutButton.h
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
#include "LayoutElement.h"

/**
 * \Author: dota2_black
 * \brief: CXrButton的事件机制(通过IActionTrigger注册操作方法进入CXrButton),将设置button属性和设置button的操作方法分离
 *         重写为合并的方法(创建不同videobutton的开发者需要同时负责button的属性以及功能, private IActionTrigger为适配
 *         CXrButton的绘制
 * \param[in] name button text name
 * 
 */
class CLayoutButton : private IActionTrigger ,public CLayoutElement
{
    DECLARE_DYNAMIC(CLayoutButton)
public:
    /** cornerSize默认值设为-1, 表征不对纹理文件做特殊处理,直接使用调用者的纹理文件*/
    CLayoutButton(uint32_t cornerSize = -1) :IActionTrigger(), CLayoutElement()
    {
        button = new CXrButton(cornerSize);
    }
    virtual ~CLayoutButton() { if(button) { delete button; button = NULL;}}
    
    void InitElementSize(uint32_t pos_x, uint32_t pos_y,
                         uint32_t element_width, uint32_t element_height,
                         uint32_t opacity);

    void InitElementTexture(const TextureName* array_texture);

    bool CreateElement();
protected:
    /**
     * button 接口， 每个按钮都应该实现对应的事件响应功能(按键按下)
     */
    virtual Void OnPress(Int32 id) { Log_Debug("button id is %d\n",id);}
    /**
     * button 接口， 每个按钮都应该实现对应的事件响应功能(按键释放)
     */
    virtual Void OnRelease(Int32 id, Boolean isIn) { Log_Debug("button id is %d\n",id);} 
private:
    uint32_t layout_x, layout_y;
    uint32_t button_width, button_height;
    uint32_t button_opacity;
    TextureName base_texture;
    TextureName hit_texture;
    CXrButton* button;
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _LAYOUTBUTTON_H_ */
