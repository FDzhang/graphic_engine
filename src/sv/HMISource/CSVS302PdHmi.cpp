/*===========================================================================*\
 * FILE: CSVS302PdHmi.h
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
#include "CSVS302PdHmi.h"
#include "gpu_log.h"


CSVS302PdHmi::CSVS302PdHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_trigger, NULL, S302_PD_ELEM_NUMS * sizeof(IActionTrigger*));
    memset(m_buttonVisibility, 0, S302_PD_ELEM_NUMS * sizeof(unsigned char));
    memset(m_buttonImage, 0, S302_PD_ELEM_NUMS * sizeof(unsigned char));
}

CSVS302PdHmi::~CSVS302PdHmi()
{
    for(int i = 0; i < S302_PD_ELEM_NUMS; i++)
    {
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
        SAFE_DELETE(m_trigger[i]);
        SAFE_DELETE(m_baseButton[i]);
    }
}

int CSVS302PdHmi::SetHmiParams()
{
    for(int i=0;i<S302_PD_ELEM_NUMS;i++)
    {
        m_baseButtonData[i].icon_type = STATIC_ICON;
        m_baseButtonData[i].show_flag = 0;
        m_baseButtonData[i].show_icon_num = 0;
    }

    m_baseButtonData[S302_PD_FRONT_WARNING].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_PD_FRONT_WARNING].icon_file_name[0],"%sCar/s302_mod_warning.dds",XR_RES);

    m_baseButtonData[S302_PD_REAR_WARNING].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_PD_REAR_WARNING].icon_file_name[0],"%sCar/s302_mod_warning.dds",XR_RES);

    m_baseButtonData[S302_PD_LEFT_WARNING].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_PD_LEFT_WARNING].icon_file_name[0],"%sCar/s302_mod_warning.dds",XR_RES);

    m_baseButtonData[S302_PD_RIGHT_WARNING].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_PD_RIGHT_WARNING].icon_file_name[0],"%sCar/s302_mod_warning.dds",XR_RES);

    for(int i = 0; i < S302_PD_ELEM_NUMS; i++)
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

    return S302_PD_HMI_NORMAL;
}

int CSVS302PdHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    float stitchRegionWidth = window_width * (480.0/1520.0);

    float iconWidth = 72;
    float iconHeight = 64;

    float frontIconStartX = (stitchRegionWidth - iconWidth)*0.5;
    float frontIconStartY = 16;

    float rearIconStartX = (stitchRegionWidth - iconWidth)*0.5;
    float rearIconStartY = m_screenHeight - iconHeight - 16;

    float leftIconStartX = 8;
    float leftIconStartY = (m_screenHeight - iconHeight)*0.5;

    float rightIconStartX = stitchRegionWidth - iconWidth - 8;
    float rightIconStartY = (m_screenHeight - iconHeight)*0.5;

    SetHmiElementProperty(S302_PD_FRONT_WARNING, frontIconStartX, frontIconStartY, iconWidth, iconHeight);
    SetHmiElementProperty(S302_PD_REAR_WARNING, rearIconStartX, rearIconStartY, iconWidth, iconHeight);
    SetHmiElementProperty(S302_PD_LEFT_WARNING, leftIconStartX, leftIconStartY, iconWidth, iconHeight);
    SetHmiElementProperty(S302_PD_RIGHT_WARNING, rightIconStartX, rightIconStartY, iconWidth, iconHeight);

    SetHmiParams();

    return S302_PD_HMI_NORMAL;
}
int CSVS302PdHmi::Update(Hmi_Message_T& hmiMsg)
{
    PdResultT pdResult;
    memset(&pdResult, 0, sizeof(PdResultT));
    CAvmRenderDataBase::GetInstance()->GetPdResult(&pdResult);

    if(1 == pdResult.pdStatus)
    {
        m_buttonVisibility[S302_PD_FRONT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_FRONT];
        m_buttonVisibility[S302_PD_REAR_WARNING] = pdResult.warningStatus[PD_WARNING_REG_REAR];
        m_buttonVisibility[S302_PD_LEFT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_LEFT];
        m_buttonVisibility[S302_PD_RIGHT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_RIGHT];
    }

    RefreshHmi();

    return S302_PD_HMI_NORMAL;
}
int CSVS302PdHmi::RefreshHmi()
{
    for(int i = 0; i < S302_PD_ELEM_NUMS; i++)
    {
        m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
        m_baseButton[i]->SetShowIconNum(m_buttonImage[i]);
        m_baseButton[i]->Update();
    }
    return S302_PD_HMI_NORMAL;
}

int CSVS302PdHmi::SetElementsVisibility(unsigned char pFlag)
{
    for(int i = 0; i < S302_PD_ELEM_NUMS; i++)
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
    return S302_PD_HMI_NORMAL;
}

int CSVS302PdHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return S302_PD_HMI_NORMAL;
}
int CSVS302PdHmi::DestroyHmiElems()
{
    return S302_PD_HMI_NORMAL;
}

void CSVS302PdHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
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
 *  2/24/18   Jensen Wang   Create the CSVS302PdHmi class.
\*===========================================================================*/
