#ifndef __AVM_USC_DATA_H__
#define __AVM_USC_DATA_H__
/*===========================================================================*\
 * FILE: AVMUSCData.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *    This file is used for all the input data for all AVM moudules, including
 *    calib data,CAN data ,and so on.
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
#include "../DataStruct.h"
#include "../../XrCore/XrSrc/External/XrHeaders.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/




/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
class AVMUSCData
{
public:

    AVMUSCData();
    ~AVMUSCData();
    	
    bool Init(Bev_Decoder_Param_T decoder_param, Bev_DISPLAY_Param_T display_param, 
                Bev_3D_Param_T bev_3d_param, Bev_UI_Param_T ui_param);
    bool GetDecoderParam(Bev_Decoder_Param_T** decoder_param);
    bool GetDisplayParam(Bev_DISPLAY_Param_T** display_param);
    bool GetBev3DParam(Bev_3D_Param_T** bev_3d_param);
    bool GetUiParam(Bev_UI_Param_T** ui_param);

    bool GetSingleViewRoi(Bev_DISPLAY_Param_Bev_Single_View_Roi_T** single_view_roi);
    bool SetSingleViewRoi(Bev_DISPLAY_Param_Bev_Single_View_Roi_T* single_view_roi);

    bool GetFrontSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y);
    bool SetFrontSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y);

    bool GetRearSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y);
    bool SetRearSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y);

    bool GetLeftSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y);
    bool SetLeftSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y);

    bool GetRightSingleViewRoi(float* top_left_x, float* top_left_y, float* bottom_right_x, float* bottom_right_y);
    bool SetRightSingleViewRoi(float top_left_x, float top_left_y, float bottom_right_x, float bottom_right_y);
	
private:
    Bev_Decoder_Param_T    m_decoder_param;
    Bev_DISPLAY_Param_T m_display_param;
    Bev_3D_Param_T          m_bev_3d_param;
    Bev_UI_Param_T             m_ui_param;	
};
/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/


#endif //#ifndef __GL_SV_DEMO_H__
