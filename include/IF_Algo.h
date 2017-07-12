#ifndef _IF_ALGO_H_ /* { */
#define _IF_ALGO_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: IF_Algo.h
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
 * VERSION: 21 6月 2017 dota2_black
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "GpuAvmEvent.h"

//! 事件
#define ALGOHMI_EVENT_NAME "algo_hmi"

/**
 * \brief IDVR 暴露操作DVR Layout的接口
 */
class IAlgoLayout
{
public:
    /**
     * \brief 初始化DVR Layout (目前不执行操作，由于目前GPU内部初始化序列混乱，待整改)
     */
    virtual void Init() = 0;
    /**
     * \brief 使能DVR Layout的显示，DVR Layout控制DVR控件的内部更新逻辑，外部操作不涉及控件的更新逻辑
     * \param [IN] flag true则Layout显示
     */
    virtual void Enable(bool flag) = 0;
    /**
     * \brief 更新Algo Apa
     */
    virtual void EnableApaDemoPicture(int flag) = 0; 
    
};

//! 接口函数
extern "C" DLL_PUBLIC IAlgoLayout* NewAlgoLayout(void);
extern "C" DLL_PUBLIC void  DeleteAlgoLayout(IAlgoLayout* algo);
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _IF_ALGO_H_ */
