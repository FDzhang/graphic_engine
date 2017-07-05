#ifndef _GPUDATEBASE_H_ /* { */
#define _GPUDATEBASE_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: GpuDateBase.h
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
 * VERSION: 23 6月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include <stdint.h>

//! Gpu DataBase ,用于更新数据
typedef struct
{
    //!进度条设置
    //! 列表框视图数据表
    struct dvr_listview_item
    {
        const uint32_t   dvr_listview_item_num;
        uint32_t*  dvr_listview_item;
    }
    //! 媒体播放数据
    uint32_t   dvr_media_status;

}GPU_DATABASE_T;
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUDATEBASE_H_ */
