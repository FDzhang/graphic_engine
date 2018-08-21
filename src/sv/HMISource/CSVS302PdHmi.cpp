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
    memset(m_trigger, 0, S302_PD_ELEM_NUMS * sizeof(IActionTrigger*));
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
        if(i >= S302_PD_SINGLE_TOP_SIDE) m_baseButtonData[i].icon_type = DYNAMIC_ICON;
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

    for(int i = S302_PD_SINGLE_TOP_SIDE; i < S302_PD_ELEM_NUMS;i++)
    {
       m_baseButtonData[i].icon_file_name[0] = new char [50];
       sprintf(m_baseButtonData[i].icon_file_name[0],"%sCar/s302_mod_single_warning.dds",XR_RES);
    }

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
    
    SetHmiElementProperty(S302_PD_SINGLE_TOP_SIDE, 0, 0, 0, 0);
    SetHmiElementProperty(S302_PD_SINGLE_BOTTOM_SIDE, 0, 0, 0, 0);
    SetHmiElementProperty(S302_PD_SINGLE_LEFT_SIDE, 0, 0, 0, 0);
    SetHmiElementProperty(S302_PD_SINGLE_RIGHT_SIDE, 0, 0, 0, 0);

    SetHmiParams();

    return S302_PD_HMI_NORMAL;
}
int CSVS302PdHmi::Update(Hmi_Message_T& hmiMsg)
{
    PdResultT pdResult;
    memset(&pdResult, 0, sizeof(PdResultT));
    CAvmRenderDataBase::GetInstance()->GetPdResult(&pdResult);
        
    //Log_Error("GPU:---%d, ---%d, ---%d, ---%d", pdResult.warningStatus[0], pdResult.warningStatus[1], pdResult.warningStatus[2], pdResult.warningStatus[3]);
     unsigned char currentViewStatus = 0;  
    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(currentViewStatus);
	
    if(currentViewStatus != LINEAR_FRONT_180_DEGREE_VIEW
        && currentViewStatus != LINEAR_REAR_180_DEGREE_VIEW
        && 2 == pdResult.pdStatus)
    {
        m_buttonVisibility[S302_PD_FRONT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_FRONT];
        m_buttonVisibility[S302_PD_REAR_WARNING] = pdResult.warningStatus[PD_WARNING_REG_REAR];
        m_buttonVisibility[S302_PD_LEFT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_LEFT];
        m_buttonVisibility[S302_PD_RIGHT_WARNING] = pdResult.warningStatus[PD_WARNING_REG_RIGHT];
    }
    else
    {
        m_buttonVisibility[S302_PD_FRONT_WARNING] = 0;
        m_buttonVisibility[S302_PD_REAR_WARNING] = 0;
        m_buttonVisibility[S302_PD_LEFT_WARNING] = 0;
        m_buttonVisibility[S302_PD_RIGHT_WARNING] = 0;      
    }

    if(currentViewStatus != FRONT_SINGLE_VIEW && currentViewStatus != REAR_SINGLE_VIEW)
    {
        for(int i = S302_PD_SINGLE_TOP_SIDE; i <= S302_PD_SINGLE_RIGHT_SIDE;i++)
        {
            m_buttonVisibility[i] = 0;            
        }
    }
    else if(currentViewStatus == FRONT_SINGLE_VIEW)
    {
        unsigned char gear_state = 255;
        AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
        if(gear_state == GEAR_R)
        {
            for(int i = S302_PD_SINGLE_TOP_SIDE; i <= S302_PD_SINGLE_RIGHT_SIDE; i++)
            {
                m_buttonVisibility[i] = 0;            
            }             
        }
        else
        {
            for(int i = S302_PD_SINGLE_TOP_SIDE; i <= S302_PD_SINGLE_RIGHT_SIDE; i++)
            {
                m_buttonVisibility[i] = 1;            
            }            
        }
    }
    else
    {
        for(int i = S302_PD_SINGLE_TOP_SIDE; i <= S302_PD_SINGLE_RIGHT_SIDE; i++)
        {
            m_buttonVisibility[i] = 1;            
        }        
    }

    SetSingleViewModWarning(pdResult.objInfo, currentViewStatus);
    
    RefreshHmi();

    return S302_PD_HMI_NORMAL;
}
int CSVS302PdHmi::RefreshHmi()
{
    for(int i = S302_PD_SINGLE_TOP_SIDE; i <= S302_PD_SINGLE_RIGHT_SIDE; i++)
    {
        m_baseButton[i]->SetX(m_buttonPos[i][0]);
        m_baseButton[i]->SetY(m_buttonPos[i][1]);
        m_baseButton[i]->SetWidth(m_buttonSize[i][0]);
        m_baseButton[i]->SetHeight(m_buttonSize[i][1]);
    }
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

int CSVS302PdHmi::SetSingleViewModWarning(PdObjInfoT PdCoord, unsigned char viewIndex)
{
    if(m_buttonVisibility[S302_PD_SINGLE_TOP_SIDE] == 0) return 0;
    
    if(viewIndex > 3) return 0;
    
    float leftTopCoord[2];
    float rightTopCoord[2];
    float leftBottomCoord[2];
    float rightBottomCoord[2];

    if(viewIndex == 0)
    {
        if(TransImgCoord2ScreenCoord(PdCoord.al32VertexLeftTop, leftTopCoord, viewIndex) == 0) return 0;
        TransImgCoord2ScreenCoord(PdCoord.al32VertexRightTop, rightTopCoord, viewIndex);
        TransImgCoord2ScreenCoord(PdCoord.al32VertexLeftBtm, leftBottomCoord, viewIndex);
        TransImgCoord2ScreenCoord(PdCoord.al32VertexRightBtm, rightBottomCoord, viewIndex);        
    }
    else if(viewIndex == 1)
    {
        if(TransImgCoord2ScreenCoord(PdCoord.al32VertexLeftTop, rightTopCoord, viewIndex) == 0) return 0;
        TransImgCoord2ScreenCoord(PdCoord.al32VertexRightTop, leftTopCoord, viewIndex);
        TransImgCoord2ScreenCoord(PdCoord.al32VertexLeftBtm, rightBottomCoord, viewIndex);
        TransImgCoord2ScreenCoord(PdCoord.al32VertexRightBtm, leftBottomCoord, viewIndex);        
    }
    else
    {
        return 0;
    }

    float coordTop = (leftTopCoord[1] < rightTopCoord[1])?leftTopCoord[1]:rightTopCoord[1];
    float coordBottom = (leftBottomCoord[1] > rightBottomCoord[1])?leftBottomCoord[1]:rightBottomCoord[1];
    float coordLeft = (leftTopCoord[0] < leftBottomCoord[0])?leftTopCoord[0]:leftBottomCoord[0];
    float coordRight = (rightTopCoord[0] > rightBottomCoord[0])?rightTopCoord[0]:rightBottomCoord[0];

    Region* singleViewRegion = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewRegion(&singleViewRegion);
    float singleLeft = singleViewRegion->left;
    float singleRight = singleViewRegion->right;
    float singleTop = singleViewRegion->top;
    float singleBottom = singleViewRegion->bottom;

    if(coordLeft < singleLeft)
    {
        m_buttonVisibility[S302_PD_SINGLE_LEFT_SIDE] = 0;
        coordLeft = singleLeft;
    }
    if(coordLeft > singleRight)
    {
        m_buttonVisibility[S302_PD_SINGLE_LEFT_SIDE] = 0;
        coordLeft = singleRight;
    }
    if(coordRight > singleRight)
    {
        m_buttonVisibility[S302_PD_SINGLE_RIGHT_SIDE] = 0;
        coordRight = singleRight;
    }
    if(coordRight < singleLeft)
    {
        m_buttonVisibility[S302_PD_SINGLE_RIGHT_SIDE] = 0;
        coordRight = singleLeft;
    }
    if(coordTop < singleTop)
    {
        m_buttonVisibility[S302_PD_SINGLE_TOP_SIDE] = 0;
        coordTop = singleTop;
    }
    if(coordBottom > singleBottom)
    {
        m_buttonVisibility[S302_PD_SINGLE_BOTTOM_SIDE] = 0;
        coordBottom = singleBottom;
    }

    m_buttonPos[S302_PD_SINGLE_TOP_SIDE][0] = coordLeft; //leftTopCoord[0];
    m_buttonPos[S302_PD_SINGLE_TOP_SIDE][1] = coordTop; //leftTopCoord[1];
    m_buttonSize[S302_PD_SINGLE_TOP_SIDE][0] = coordRight - coordLeft; //rightTopCoord[0] - leftTopCoord[0];
    m_buttonSize[S302_PD_SINGLE_TOP_SIDE][1] = 4;

    m_buttonPos[S302_PD_SINGLE_BOTTOM_SIDE][0] = coordLeft; //leftBottomCoord[0];
    m_buttonPos[S302_PD_SINGLE_BOTTOM_SIDE][1] = coordBottom - 4; //leftBottomCoord[1] - 4;
    m_buttonSize[S302_PD_SINGLE_BOTTOM_SIDE][0] = coordRight - coordLeft; //rightBottomCoord[0] - leftBottomCoord[0];
    m_buttonSize[S302_PD_SINGLE_BOTTOM_SIDE][1] = 4;

    m_buttonPos[S302_PD_SINGLE_LEFT_SIDE][0] = coordLeft; //leftTopCoord[0];
    m_buttonPos[S302_PD_SINGLE_LEFT_SIDE][1] = coordTop; //leftTopCoord[1];
    m_buttonSize[S302_PD_SINGLE_LEFT_SIDE][0] = 4;
    m_buttonSize[S302_PD_SINGLE_LEFT_SIDE][1] = coordBottom - coordTop;  //leftBottomCoord[1] - leftTopCoord[1];

    m_buttonPos[S302_PD_SINGLE_RIGHT_SIDE][0] = coordRight - 4; //rightTopCoord[0] - 4;
    m_buttonPos[S302_PD_SINGLE_RIGHT_SIDE][1] = coordTop; //rightTopCoord[1];
    m_buttonSize[S302_PD_SINGLE_RIGHT_SIDE][0] = 4;
    m_buttonSize[S302_PD_SINGLE_RIGHT_SIDE][1] = coordBottom - coordTop;  //rightBottomCoord[1] - rightTopCoord[1];

    return S302_PD_HMI_NORMAL;    
}

int CSVS302PdHmi::TransImgCoord2ScreenCoord(Int32 *pImgCoord, float *pScreenCoord, unsigned char viewIndex)
{
    if(viewIndex > 3) return 0;
    if(pImgCoord[0] > 1280 || pImgCoord[1] > 720)
    {   
        return 0;
    }
    
    float* vertexData;
    CAvmRenderDataBase::GetInstance()->GetSingleViewRoi(&vertexData, viewIndex);
    float imgLeft = vertexData[3] * 1280;
    float imgTop = vertexData[4] * 720;
    float imgRight = vertexData[3 + 21] * 1280;
    float imgBottom = vertexData[4 + 21] * 720;
    
    Region* singleViewRegion = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewRegion(&singleViewRegion);
    float singleLeft = singleViewRegion->left;
    float singleRight = singleViewRegion->right;
    float singleTop = singleViewRegion->top;
    float singleBottom = singleViewRegion->bottom;
    
    float imgcoordX = pImgCoord[0];
    float imgcoordY = pImgCoord[1];
    
    pScreenCoord[0] = (imgcoordX - imgLeft) / (imgRight - imgLeft) * (singleRight - singleLeft) + singleLeft; 
    pScreenCoord[1] = (imgcoordY - imgTop) / (imgBottom - imgTop) * (singleBottom - singleTop) + singleTop; 
    
    return S302_PD_HMI_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  2/24/18   Jensen Wang   Create the CSVS302PdHmi class.
\*===========================================================================*/
