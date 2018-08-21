/*===========================================================================*\
 * FILE: CSVEp21MainHmi.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
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
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/


#ifndef _CSV_EP21_MAIN_HMI_H_
#define _CSV_EP21_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"


class CSVEp21MainHmi : public ISVHmi
{
public:

    CSVEp21MainHmi();
    ~CSVEp21MainHmi();
    HMI_BASE_INHERITANCE_FUNC()

    int SetElementsVisibility(unsigned char pFlag);

private:
    int SetHmiParams();
    int RefreshHmi();

private:
	HMIRawDataImageIcon* m_viewIndexCode;
	HMIRawDataImageIconDataT m_viewIndexCodeData;

    int m_screenWidth;
    int m_screenHeight;
public:

};

#endif //_CSV_EP21_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  01/18/18   Chunh Huang   Create the CSVEp21MainHmi class.
\*===========================================================================*/
