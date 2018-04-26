/*===========================================================================*\
 * FILE: CSVS302GuidelineHmi.cpp
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
#include "CSVS302GuidelineHmi.h"
#include "gpu_log.h"

CSVS302GuidelineHmi::CSVS302GuidelineHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_guideLine, NULL, S302_GUIDELINE_NUM * sizeof(HMIGuideLine*));
}

CSVS302GuidelineHmi::~CSVS302GuidelineHmi()
{
    for(int i = 0; i < S302_GUIDELINE_NUM; i++)
    {
        SAFE_DELETE(m_guideLine[i]);
    }
}

int CSVS302GuidelineHmi::Init(int window_width, int window_height)
{
    SetHmiGuideline();

    return S302_GUIDELINE_NORMAL;
}

void CSVS302GuidelineHmi::SetHmiGuideline()
{
    int i = 0;

    ISceneNode* m_avmViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&m_avmViewNode);
    ISceneNode* m_singleViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1;
    m_guideLineData[i].guideLineLength = 800.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 200.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_red.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL1;
    m_guideLineData[i].guideLineLength = 800.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 200.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_red.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL2;
    m_guideLineData[i].guideLineLength = 1000.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 1000.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_yellow.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL2;
    m_guideLineData[i].guideLineLength = 1000.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 1000.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_yellow.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL3;
    m_guideLineData[i].guideLineLength = 1000.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 2000.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_green.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL3;
    m_guideLineData[i].guideLineLength = 1000.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 100.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 2000.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_green.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL1;
    m_guideLineData[i].guideLineLength = 80.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 240.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 920.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_red.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL1;
    m_guideLineData[i].guideLineLength = 80.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 240.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 920.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_red.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL2;
    m_guideLineData[i].guideLineLength = 80.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 280.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 1920.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_yellow.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL2;
    m_guideLineData[i].guideLineLength = 80.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 280.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 1920.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_yellow.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL3;
    m_guideLineData[i].guideLineLength = 200.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 360.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 2800.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_green.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);

    i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3;
    m_guideLineData[i].guideLineLength = 200.0;
    m_guideLineData[i].guideLineName = "S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_STATIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 360.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 100.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 2800.0;
    m_guideLineData[i].guideLinePointNum = 2;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/static_overlay_green.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);
    m_guideLine[i]->SetVisibility(1);
}

int CSVS302GuidelineHmi::Update(Hmi_Message_T& hmiMsg)
{
    RefreshHmiGuideline();

    return S302_GUIDELINE_NORMAL;
}

void CSVS302GuidelineHmi::RefreshHmiGuideline()
{
    float steer_angle = 0.0;
    unsigned char gear_state = 0;
    unsigned char m_displayViewCmd = 0;

    AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);
    AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(m_displayViewCmd);

//    static int m_cnt = 0;
//    steer_angle = 320;
//    gear_state = GEAR_R;
//    m_displayViewCmd = REAR_SINGLE_VIEW;
//
//    steer_angle = m_cnt *4.8;
//
//    if(m_cnt < 250) steer_angle = steer_angle - 600;
//    else steer_angle = steer_angle - 1800;
//
//    if(m_cnt < 250) gear_state = GEAR_P;
//    else gear_state = GEAR_R;
//
//    if(m_cnt < 250) m_displayViewCmd = FRONT_SINGLE_VIEW;
//    else if(m_cnt <= 500) m_displayViewCmd = REAR_SINGLE_VIEW;
//
//    CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(m_displayViewCmd);
//
//    m_cnt ++;
//    if(m_cnt == 500) m_cnt = 0;

    if(m_displayViewCmd == FRONT_SINGLE_VIEW)
    {
        for (int i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1; i <= S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3; i++)
        {
            m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_FORWARD);
            m_guideLine[i]->SetVisibility(1);
        }
    }
    else if(m_displayViewCmd == REAR_SINGLE_VIEW)
    {
        for (int i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1; i <= S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3; i++)
        {
            m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_BACKWARD);
            m_guideLine[i]->SetVisibility(1);
        }
    }
    else
    {
        for (int i = S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1; i <= S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3; i++)
        {
            m_guideLine[i]->SetVisibility(0);
        }
    }
}

int CSVS302GuidelineHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return S302_GUIDELINE_NORMAL;
}
int CSVS302GuidelineHmi::DestroyHmiElems()
{
    return S302_GUIDELINE_NORMAL;
}

int CSVS302GuidelineHmi::SetElementsVisibility(unsigned char pFlag)
{
    return S302_GUIDELINE_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/24/18   Chunh Huang   Create the CSVS302GuidelineHmi class.
\*===========================================================================*/
