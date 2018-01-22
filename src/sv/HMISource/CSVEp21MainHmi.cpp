/*===========================================================================*\
 * FILE: CSVEp21MainHmi.cpp
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
#include "CSVEp21MainHmi.h"
#include "gpu_log.h"

REGISTER_HMI_CLASS(CSVEp21MainHmi)

CSVEp21MainHmi::CSVEp21MainHmi()
{

}

CSVEp21MainHmi::~CSVEp21MainHmi()
{

}

int CSVEp21MainHmi::SetHmiParams()
{


    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

	m_viewIndexCodeData.imageWidth = 128;
	m_viewIndexCodeData.imageHeight = 1;

	m_viewIndexCodeData.iconPosX = 128.0;
	m_viewIndexCodeData.iconPosY = 0.0;
	m_viewIndexCodeData.iconWidth = m_viewIndexCodeData.imageWidth;
	m_viewIndexCodeData.iconHeight = m_viewIndexCodeData.imageHeight;

	m_viewIndexCodeData.insertFlag = InsertFlag_Default;
	m_viewIndexCodeData.trigger = NULL;

	char* pData2 = new char[m_viewIndexCodeData.imageWidth * m_viewIndexCodeData.imageHeight * 3];
	memset(pData2, 255, sizeof(char)*m_viewIndexCodeData.imageWidth * m_viewIndexCodeData.imageHeight*3);

	m_viewIndexCodeData.imageData = pData2;
    m_viewIndexCodeData.renderUiNode = m_uiNode;

    m_viewIndexCode = new HMIRawDataImageIcon(&m_viewIndexCodeData);

    SetHmiParams();

    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::Update(Hmi_Message_T& hmiMsg)
{
 	//char* pData = new char[m_viewIndexCodeData.imageWidth * m_viewIndexCodeData.imageHeight * 3];
	//memset(pData, 255, sizeof(char)*m_viewIndexCodeData.imageWidth * m_viewIndexCodeData.imageHeight*3);

    //m_viewIndexCode->SetVisibility(1);
    //m_viewIndexCode->Update(pData, 1);

    //delete pData;

    RefreshHmi();

    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::RefreshHmi()
{

    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::SetElementsVisibility(unsigned char pFlag)
{
    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return EP21_MAIN_HMI_NORMAL;
}

int CSVEp21MainHmi::DestroyHmiElems()
{
    return EP21_MAIN_HMI_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  01/18/18   Chunh Huang   Create the CSVEp21MainHmi class.
\*===========================================================================*/
