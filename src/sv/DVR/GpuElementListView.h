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

class GpuElementListView : private CXrSelector
{
public:
    GpuElementListView();
    ~GpuElementListView();

    bool Create(const uint32_t pos_x, const uint32_t pos_y,
                const uint32_t element_width, element_height);
    void SetElementEffect(void* effect, long style);
private:
    DECLEAR_DYNAMIC_CLASS(GpuElementListView, IGUIElement)
};

/*------------------------------------------------------------------------------------------
 * File Revision History (top to bottom: first revision to last revision)
 *------------------------------------------------------------------------------------------
 *
 * Date             SCR                   userid                   Description
 * -----------------------------------------------------------------------------------------

 *------------------------------------------------------------------------------------------*/
#endif /* } _GPUELEMENTLISTVIEW_H_ */
