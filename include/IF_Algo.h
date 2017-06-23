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

#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))

//! 事件
#define ALGOHMI_EVENT_NAME "algo_hmi"

//! copy from TcpProtocol.h, please careful the same between these files
typedef struct Algo_Event_Header
{
    const uint32_t  magic;
    uint16_t  msg_id;
    //major.minor = 1.0
    const uint8_t   revision_lsb;
    const uint8_t   revision_msb;
    uint16_t  payload_len;
}
Algo_Event_Header_T;


typedef struct Algo_Event_Payload
{
    Algo_Event_Header_T header;
    union
    {
        bool onlyNotify; //true　notify, 接收方不需要更多参数
    }body;
}Algo_Event_Payload_T;

typedef enum
{
    ALGO_EXIT_BUTTON, /*算法退出按钮*/
    ALGO_LDW_BUTTON,
    ALGO_BSD_BUTTON,
    ALGO_ONLINE_BUTTON,
    ALGO_APA_BUTTON,
    ALGO_RECORD_BUTTON,
    ALGO_WIFI_BUTTON,
}ALGO_EVENT_ELEMENT_ID_T;

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
     * \brief 更新进度条位置
     */
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
