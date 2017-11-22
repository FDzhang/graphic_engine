/*===========================================================================*\
 * FILE: AVMUSCData.c
 *===========================================================================
 * Copyright 2008 O-Film Technologies, Inc., All Rights Reserved.
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
#include "AVMUSCData.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/


/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

AVMUSCData::AVMUSCData()
{

}
AVMUSCData::~AVMUSCData()
{
    
}
	
bool AVMUSCData::Init(Bev_Decoder_Param_T decoder_param, Bev_DISPLAY_Param_T display_param, 
            Bev_3D_Param_T bev_3d_param, Bev_UI_Param_T ui_param)
{    
    m_decoder_param = decoder_param;


    m_display_param = display_param;

    m_bev_3d_param = bev_3d_param;

    m_ui_param = ui_param;	

   return true; 
}
bool AVMUSCData::GetDecoderParam(Bev_Decoder_Param_T** decoder_param)
{
    *decoder_param = &m_decoder_param;
    
    return true;
}
bool AVMUSCData::GetDisplayParam(Bev_DISPLAY_Param_T** display_param)
{
    *display_param = &m_display_param;
    return true;
}
bool AVMUSCData::GetBev3DParam(Bev_3D_Param_T** bev_3d_param)
{
    *bev_3d_param = &m_bev_3d_param;
    return true;
}
bool AVMUSCData::GetUiParam(Bev_UI_Param_T** ui_param)
{
    *ui_param = &m_ui_param;
    return true;
}

bool AVMUSCData::GetSingleViewRoi(Bev_DISPLAY_Param_Bev_Single_View_Roi_T** single_view_roi)
{
    *single_view_roi = &m_display_param.bev_single_view_roi;
    return true;
}

bool AVMUSCData::SetSingleViewRoi(Bev_DISPLAY_Param_Bev_Single_View_Roi_T* single_view_roi)
{
    if(single_view_roi == NULL)
    {
        return false;
    }
    m_display_param.bev_single_view_roi = *single_view_roi;
    return true;
}

bool AVMUSCData::GetFrontSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y)
{
    *top_left_x = m_display_param.bev_single_view_roi.front_single_view_roi_topleft_x;
    *top_left_y = m_display_param.bev_single_view_roi.front_single_view_roi_topleft_y;
    *bottom_right_x = m_display_param.bev_single_view_roi.front_single_view_roi_bottom_right_x;
    *bottom_right_y = m_display_param.bev_single_view_roi.front_single_view_roi_bottom_right_y;
    return true;
}
bool AVMUSCData::SetFrontSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)
{
    m_display_param.bev_single_view_roi.front_single_view_roi_topleft_x = top_left_x;
    m_display_param.bev_single_view_roi.front_single_view_roi_topleft_y = top_left_y;
    m_display_param.bev_single_view_roi.front_single_view_roi_bottom_right_x = bottom_right_x ;
    m_display_param.bev_single_view_roi.front_single_view_roi_bottom_right_y = bottom_right_y;

    return true;
}

bool AVMUSCData::GetRearSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y)
{
    *top_left_x = m_display_param.bev_single_view_roi.rear_single_view_roi_topleft_x;
    *top_left_y = m_display_param.bev_single_view_roi.rear_single_view_roi_topleft_y;
    *bottom_right_x = m_display_param.bev_single_view_roi.rear_single_view_roi_bottom_right_x;
    *bottom_right_y = m_display_param.bev_single_view_roi.rear_single_view_roi_bottom_right_y;

    return true;
}
bool AVMUSCData::SetRearSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)
{    
    m_display_param.bev_single_view_roi.rear_single_view_roi_topleft_x = top_left_x;
    m_display_param.bev_single_view_roi.rear_single_view_roi_topleft_y = top_left_y;
    m_display_param.bev_single_view_roi.rear_single_view_roi_bottom_right_x = bottom_right_x ;
    m_display_param.bev_single_view_roi.rear_single_view_roi_bottom_right_y = bottom_right_y;
    return true;
}

bool AVMUSCData::GetLeftSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y)
{
    *top_left_x = m_display_param.bev_single_view_roi.left_single_view_roi_topleft_x;
    *top_left_y = m_display_param.bev_single_view_roi.left_single_view_roi_topleft_y;
    *bottom_right_x = m_display_param.bev_single_view_roi.left_single_view_roi_bottom_right_x;
    *bottom_right_y = m_display_param.bev_single_view_roi.left_single_view_roi_bottom_right_y;

    return true;
}

bool AVMUSCData::SetLeftSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)
{
    m_display_param.bev_single_view_roi.left_single_view_roi_topleft_x = top_left_x;
    m_display_param.bev_single_view_roi.left_single_view_roi_topleft_y = top_left_y;
    m_display_param.bev_single_view_roi.left_single_view_roi_bottom_right_x = bottom_right_x ;
    m_display_param.bev_single_view_roi.left_single_view_roi_bottom_right_y = bottom_right_y;


    return true;
}

bool AVMUSCData::GetRightSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y)
{
    *top_left_x = m_display_param.bev_single_view_roi.right_single_view_roi_topleft_x;
    *top_left_y = m_display_param.bev_single_view_roi.right_single_view_roi_topleft_y;
    *bottom_right_x = m_display_param.bev_single_view_roi.right_single_view_roi_bottom_x;
    *bottom_right_y = m_display_param.bev_single_view_roi.right_single_view_roi_bottom_right_y;


    return true;
}

bool AVMUSCData::SetRightSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y)
{
    m_display_param.bev_single_view_roi.right_single_view_roi_topleft_x = top_left_x;
    m_display_param.bev_single_view_roi.right_single_view_roi_topleft_y = top_left_y;
    m_display_param.bev_single_view_roi.right_single_view_roi_bottom_x = bottom_right_x ;
    m_display_param.bev_single_view_roi.right_single_view_roi_bottom_right_y = bottom_right_y;


    return true;
}



/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

