#ifndef _IF_GENERAL_H_ /* { */
#define _IF_GENERAL_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: IF_General.h
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
 * VERSION: 19 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "GpuAvmEvent.h"

class IGeneralLayout
{
public:
    /**
     * \brief 初始化General Layout (目前不执行操作，由于目前GPU内部初始化序列混乱，待整改)
     */
    virtual void Init() = 0;
    /**
     * \brief 使能General Layout的显示，Front Layout控制Front控件的内部更新逻辑，外部操作不涉及控件的更新逻辑
     * \param [IN] flag true则Layout显示
     */
    virtual void Enable(bool flag) = 0;

    /*光标作为一个始终拥有焦点的控件，在目前架构中，需要特殊处理*/
    virtual void OnMouseMove(int x, int y) = 0;
    //virtual void OnMouseUp(int x, int y) = 0;
    //virtual void OnMouseDown(int x, int y) = 0;

    virtual void EnableCursor(bool flag) = 0;
};

//! 接口函数
extern "C" DLL_PUBLIC IGeneralLayout* NewGeneralLayout(void);
extern "C" DLL_PUBLIC void  DeleteGeneralLayout(IGeneralLayout* layout);
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IF_GENERAL_H_ */
