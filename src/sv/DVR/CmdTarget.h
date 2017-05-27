#ifndef _CMD_TARGET_H_ /* { */
#define _CMD_TARGET_H_
/*------------------------------------------------------------------------------------------*\
 * FILE: CmdTarget.h
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
 * VERSION: 26 5月 2017 dota2_black 
 *------------------------------------------------------------------------------------------*/
#include "reuse.h"

class CCmdTarget
{
public:
    virtual void DispatchEvent(uint32_t layerId, uint32_t type) = 0; //消息分发接口
};
/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _CMD_TARGET_H_ */
