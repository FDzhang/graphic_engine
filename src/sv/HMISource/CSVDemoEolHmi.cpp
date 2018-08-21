/*===========================================================================*\
 * FILE: CSVDemoEolHmi.cpp
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
#include "CSVDemoEolHmi.h"
#include "gpu_log.h"

CSVDemoEolHmi::CSVDemoEolHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_trigger, 0, DEMO_EOL_ICON_NUMS * sizeof(IActionTrigger*));

    memset(m_buttonVisibility, 0, DEMO_EOL_ICON_NUMS * sizeof(unsigned char));

    memset(m_buttonImage, 0, DEMO_EOL_ICON_NUMS * sizeof(unsigned char));

}

CSVDemoEolHmi::~CSVDemoEolHmi()
{
    for(int i = DEMO_EOL_STATUS_REMIND_TEXT; i < DEMO_EOL_ICON_NUMS; i++)
    {
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);

        SAFE_DELETE(m_trigger[i]);

        SAFE_DELETE(m_baseButton[i]);
    }

}

int CSVDemoEolHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    float remindTextWidth = 384;
    float remindTextHeight = 384;

    float remindTextPointX = m_screenWidth/2 - remindTextWidth/2;
    float remindTextPointY = m_screenHeight/2 - remindTextHeight/2;

    SetHmiElementProperty(DEMO_EOL_STATUS_REMIND_TEXT, remindTextPointX, remindTextPointY, remindTextWidth, remindTextHeight);

    SetHmiParams();

    return DEMO_EOL_HMI_NORMAL;
}

int CSVDemoEolHmi::SetHmiParams()
{
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].show_flag = 0;
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].show_icon_num = 0;
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_PROCESS] = new char [50];
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_SUCCEEDED] = new char [50];
    m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_FAILED] = new char [50];
    sprintf(m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_PROCESS],"%sCar/EOL/calibration_process.dds",XR_RES);
    sprintf(m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_SUCCEEDED],"%sCar/EOL/calibration_succeeded.dds",XR_RES);
    sprintf(m_baseButtonData[DEMO_EOL_STATUS_REMIND_TEXT].icon_file_name[DEMO_EOL_CALIBRATION_FAILED],"%sCar/EOL/calibration_failed.dds",XR_RES);
    m_buttonVisibility[DEMO_EOL_STATUS_REMIND_TEXT] = 0;
    m_buttonImage[DEMO_EOL_STATUS_REMIND_TEXT] = 0;

    for(int i = DEMO_EOL_STATUS_REMIND_TEXT; i < DEMO_EOL_ICON_NUMS; i++)
    {
        m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
        m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
        m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
        m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
        m_baseButtonData[i].delegate_func = NULL;
        m_baseButtonData[i].trigger = m_trigger[i];

        m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
        m_baseButton[i]->SetVisibility(0);
    }

    return DEMO_EOL_HMI_NORMAL;
}

int CSVDemoEolHmi::Update(Hmi_Message_T& hmiMsg)
{
    //Log_Error("---------CSVDemoEolHmi::Update------");
    EolResultT eolResult;
    memset(&eolResult, 0, sizeof(EolResultT));

    //debug code;need delete;
    /*static unsigned int tmp_cnt = 0;
    if(tmp_cnt < 1500)
    {
        eolResult.eolStatus = EOL_CALIBRATION_PROCESS;
    }
    else
    {
        eolResult.eolStatus = EOL_CALIBRATION_FAILED;
    }
    tmp_cnt++;
    CAvmRenderDataBase::GetInstance()->SetEolResult(&eolResult);*/

    CAvmRenderDataBase::GetInstance()->GetEolResult(&eolResult);

    if(eolResult.eolStatus == EOL_CALIBRATION_STANDBY)
    {
        m_buttonVisibility[DEMO_EOL_STATUS_REMIND_TEXT] = 0;
        m_buttonImage[DEMO_EOL_STATUS_REMIND_TEXT] = 0;
    }
    else if(eolResult.eolStatus == EOL_CALIBRATION_PROCESS)
    {
        m_buttonVisibility[DEMO_EOL_STATUS_REMIND_TEXT] = 1;
        m_buttonImage[DEMO_EOL_STATUS_REMIND_TEXT] = DEMO_EOL_CALIBRATION_PROCESS;
    }
    else if(eolResult.eolStatus == EOL_CALIBRATION_SUCCEEDED)
    {
        m_buttonVisibility[DEMO_EOL_STATUS_REMIND_TEXT] = 1;
        m_buttonImage[DEMO_EOL_STATUS_REMIND_TEXT] = DEMO_EOL_CALIBRATION_SUCCEEDED;
    }
    else if(eolResult.eolStatus == EOL_CALIBRATION_FAILED)
    {
        m_buttonVisibility[DEMO_EOL_STATUS_REMIND_TEXT] = 1;
        m_buttonImage[DEMO_EOL_STATUS_REMIND_TEXT] = DEMO_EOL_CALIBRATION_FAILED;
    }

    RefreshHmi();

    return DEMO_EOL_HMI_NORMAL;
}

int CSVDemoEolHmi::RefreshHmi()
{
    for(int i = DEMO_EOL_STATUS_REMIND_TEXT; i < DEMO_EOL_ICON_NUMS; i++)
    {
        m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
        m_baseButton[i]->SetShowIconNum(m_buttonImage[i]);
        m_baseButton[i]->Update();
    }

    return DEMO_EOL_HMI_NORMAL;
}

int CSVDemoEolHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return DEMO_EOL_HMI_NORMAL;
}
int CSVDemoEolHmi::DestroyHmiElems()
{
    return DEMO_EOL_HMI_NORMAL;
}

int CSVDemoEolHmi::SetElementsVisibility(unsigned char pFlag)
{
    for(int i = DEMO_EOL_STATUS_REMIND_TEXT; i < DEMO_EOL_ICON_NUMS; i++)
    {
        if(pFlag == 0)
        {
            m_baseButton[i]->SetVisibility(0);
        }
        else
        {
            m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
        }
    }

    return DEMO_EOL_HMI_NORMAL;
}

void CSVDemoEolHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
{
    m_buttonSize[pIconIndex][BUTTON_SIZE_WIDTH] = pIconWidth;
    m_buttonSize[pIconIndex][BUTTON_SIZE_HEIGHT] = pIconHeight;
    m_buttonPos[pIconIndex][BUTTON_POS_X] = pIconPosX;
    m_buttonPos[pIconIndex][BUTTON_POS_Y] = pIconPosY;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  3/5/18     Chunh Huang   Create the CSVDemoEolHmi class.
\*===========================================================================*/
