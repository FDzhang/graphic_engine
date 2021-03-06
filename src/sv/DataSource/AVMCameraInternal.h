#ifndef __AVM_CAMERA_INSTRINCT_H__
#define __AVM_CAMERA_INSTRINCT_H__

/*===========================================================================*\
 * FILE: example.h
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
#include "camera_model.h"
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
enum
{
    roi_start_x_index = 0,
	roi_end_x_index,
    roi_start_y_index,
	roi_end_y_index,

};

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
class AVMCameraInternal
{
public:

	AVMCameraInternal();
	~AVMCameraInternal();


	/*Init from pose file ,file sotre camera pose index as front right rear left*/
	void Init( BEV_CONFIG_T pconfig);
	void GetCameraWidth(float *width,int camera_index);
	void GetCameraHeight(float *height,int camera_index);
	void GetCameraInstrinct(Cam_Model_Intrinsic **matrix,int camera_index);
	void MapCamRay2ImagePointGpu(float *pWld,float *pTex,int camera_index);

	void InitParamFromSysConfig(CAMERA_CFG *cam_model, Camera_Param_T *p_sys_config, Smc_Cal_T *pSMC);

	void Init(Camera_Param_T *p_Int_Cam,Smc_Cal_T* pIntParam);
	void Init(Smc_Cal_T *pIntParam);
	void Init(Cam_Model_Intrinsic *pCamIntMdl);

	Cam_Model * GetFullCameraModel(int camera_index,float *pCameraR,float *pCam_T);
    void SetUndistLinearCameraModel(int camera_index,Cam_Model* pLinearMdl);
    
    
    void SetUndistCyliCameraModel(int camera_index,Cam_Model_Cyli* pCyliMdl);
    
    Cam_Model *GetUndistLinearCameraModel(int camera_index);
    
    
    Cam_Model_Cyli *GetUndistCyliCameraModel(int camera_index);
	void MapImgPtFish2Cylic(int camera_index,float *pSrc,float *pDst);
	void MapImgPtFish2Linear(int camera_index,float *pSrc, float *pDst);
    void SetUndistCamROI(int camera_index,int start_x,int start_y,int end_x,int end_y);
	void SetLinearCamROI(int camera_index,int start_x,int start_y,int end_x,int end_y);

private:
	void InitLutMemory(void);
	int get_camera_config(CAMERA_CFG *cam_model, BEV_CONFIG_T pconfig);


    Cam_Model_Intrinsic m_cam_fisheye_instrict[4];
	//Cam_Model m_cam_fisheye_instrict[4];
    CAMERA_CFG m_cam_cfg_fisheye[4];
	float *m_camera_lut[4];

	Cam_Model *mp_full_cam_model[4];

	Cam_Model *mp_undist_linear_mdl[4];
	Cam_Model_Cyli *mp_undist_Cyli_mdel[4];
	
    int m_undist_cam_roi[4][4];
	int m_linear_cam_roi[4][4];

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
