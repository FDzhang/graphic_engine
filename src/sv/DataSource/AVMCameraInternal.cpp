/*===========================================================================*\
 * FILE: template.c
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
#include "AVMCameraInternal.h"
#include "../fileloader.h"
#include "../DataStruct.h"
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

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/
int AVMCameraInternal::get_camera_config(CAMERA_CFG *cam_model, BEV_CONFIG_T pconfig)
{


   	cam_model[right_camera_index].CAM_TYPE = 0;
	cam_model[right_camera_index].CAM_INT_W = (pconfig.smc.RIGHT_CAMERA_SENSOR_WIDTH);
	cam_model[right_camera_index].CAM_INT_H = (pconfig.smc.RIGHT_CAMERA_SENSOR_HEIGHT);
	cam_model[right_camera_index].CAM_INT_CX = (pconfig.smc.RIGHT_CAMERA_SENSOR_CENTER_X);
	cam_model[right_camera_index].CAM_INT_CY = (pconfig.smc.RIGHT_CAMERA_SENSOR_CENTER_Y);
	cam_model[right_camera_index].CAM_SKEW_C = (pconfig.smc.RIGHT_CAMERA_SKEW_C);
	cam_model[right_camera_index].CAM_SKEW_D = (pconfig.smc.RIGHT_CAMERA_SKEW_D);
	cam_model[right_camera_index].CAM_LEN_ORIGIN_HFOV = (pconfig.smc.RIGHT_CAMERA_H_FOV);
	cam_model[right_camera_index].CAM_LEN_ORIGIN_VFOV = (pconfig.smc.RIGHT_CAMERA_V_FOV);
	cam_model[right_camera_index].CAM_LEN_CX = (int)(pconfig.smc.RIGHT_CAMERA_IMAGE_CENTER_X);
	cam_model[right_camera_index].CAM_LEN_CY = (int)(pconfig.smc.RIGHT_CAMERA_IMAGE_CENTER_Y);
	cam_model[right_camera_index].CAM_SKEW_E = (pconfig.smc.RIGHT_CAMERA_SKEW_E);
	cam_model[right_camera_index].CAM_LEN_TOP_CUT = (int)(pconfig.smc.RIGHT_CAMERA_IMAGE_TOP_CUT);
	sprintf(cam_model[right_camera_index].CAM_LEN_DIST_LUT,"%s%s",XR_RES,pconfig.smc.RIGHT_CAMERA_LUT_FILE_NAME);


   	cam_model[left_camera_index].CAM_TYPE = 0;
	cam_model[left_camera_index].CAM_INT_W = (pconfig.smc.LEFT_CAMERA_SENSOR_WIDTH);
	cam_model[left_camera_index].CAM_INT_H = (pconfig.smc.LEFT_CAMERA_SENSOR_HEIGHT);
	cam_model[left_camera_index].CAM_INT_CX = (pconfig.smc.LEFT_CAMERA_SENSOR_CENTER_X);
	cam_model[left_camera_index].CAM_INT_CY = (pconfig.smc.LEFT_CAMERA_SENSOR_CENTER_Y);
	cam_model[left_camera_index].CAM_SKEW_C = (pconfig.smc.LEFT_CAMERA_SKEW_C);
	cam_model[left_camera_index].CAM_SKEW_D = (pconfig.smc.LEFT_CAMERA_SKEW_D);
	cam_model[left_camera_index].CAM_LEN_ORIGIN_HFOV = (pconfig.smc.LEFT_CAMERA_H_FOV);
	cam_model[left_camera_index].CAM_LEN_ORIGIN_VFOV = (pconfig.smc.LEFT_CAMERA_V_FOV);
	cam_model[left_camera_index].CAM_LEN_CX = (int)(pconfig.smc.LEFT_CAMERA_IMAGE_CENTER_X);
	cam_model[left_camera_index].CAM_LEN_CY = (int)(pconfig.smc.LEFT_CAMERA_IMAGE_CENTER_Y);
	cam_model[left_camera_index].CAM_SKEW_E = (pconfig.smc.LEFT_CAMERA_SKEW_E);
	cam_model[left_camera_index].CAM_LEN_TOP_CUT = (int)(pconfig.smc.LEFT_CAMERA_IMAGE_TOP_CUT);
	sprintf(cam_model[left_camera_index].CAM_LEN_DIST_LUT,"%s%s",XR_RES,pconfig.smc.LEFT_CAMERA_LUT_FILE_NAME);


   	cam_model[front_camera_index].CAM_TYPE = 0;
	cam_model[front_camera_index].CAM_INT_W = (pconfig.smc.FRONT_CAMERA_SENSOR_WIDTH);
	cam_model[front_camera_index].CAM_INT_H = (pconfig.smc.FRONT_CAMERA_SENSOR_HEIGHT);
	cam_model[front_camera_index].CAM_INT_CX = (pconfig.smc.FRONT_CAMERA_SENSOR_CENTER_X);
	cam_model[front_camera_index].CAM_INT_CY = (pconfig.smc.FRONT_CAMERA_SENSOR_CENTER_Y);
	cam_model[front_camera_index].CAM_SKEW_C = (pconfig.smc.FRONT_CAMERA_SKEW_C);
	cam_model[front_camera_index].CAM_SKEW_D = (pconfig.smc.FRONT_CAMERA_SKEW_D);
	cam_model[front_camera_index].CAM_LEN_ORIGIN_HFOV = (pconfig.smc.FRONT_CAMERA_H_FOV);
	cam_model[front_camera_index].CAM_LEN_ORIGIN_VFOV = (pconfig.smc.FRONT_CAMERA_V_FOV);
	cam_model[front_camera_index].CAM_LEN_CX = (pconfig.smc.FRONT_CAMERA_IMAGE_CENTER_X);
	cam_model[front_camera_index].CAM_LEN_CY = (pconfig.smc.FRONT_CAMERA_IMAGE_CENTER_Y);
	cam_model[front_camera_index].CAM_SKEW_E = (pconfig.smc.FRONT_CAMERA_SKEW_E);
	cam_model[front_camera_index].CAM_LEN_TOP_CUT = (int)(pconfig.smc.FRONT_CAMERA_IMAGE_TOP_CUT);

	sprintf(cam_model[front_camera_index].CAM_LEN_DIST_LUT,"%s%s",XR_RES,pconfig.smc.FRONT_CAMERA_LUT_FILE_NAME);


   	cam_model[rear_camera_index].CAM_TYPE = 0;
	cam_model[rear_camera_index].CAM_INT_W = (pconfig.smc.REAR_CAMERA_SENSOR_WIDTH);
	cam_model[rear_camera_index].CAM_INT_H = (pconfig.smc.REAR_CAMERA_SENSOR_HEIGHT);
	cam_model[rear_camera_index].CAM_INT_CX = (pconfig.smc.REAR_CAMERA_SENSOR_CENTER_X);
	cam_model[rear_camera_index].CAM_INT_CY = (pconfig.smc.REAR_CAMERA_SENSOR_CENTER_Y);
	cam_model[rear_camera_index].CAM_SKEW_C = (pconfig.smc.REAR_CAMERA_SKEW_C);
	cam_model[rear_camera_index].CAM_SKEW_D = (pconfig.smc.REAR_CAMERA_SKEW_D);
	cam_model[rear_camera_index].CAM_LEN_ORIGIN_HFOV = (pconfig.smc.REAR_CAMERA_H_FOV);
	cam_model[rear_camera_index].CAM_LEN_ORIGIN_VFOV = (pconfig.smc.REAR_CAMERA_V_FOV);
	cam_model[rear_camera_index].CAM_LEN_CX = (int)(pconfig.smc.REAR_CAMERA_IMAGE_CENTER_X);
	cam_model[rear_camera_index].CAM_LEN_CY = (int)(pconfig.smc.REAR_CAMERA_IMAGE_CENTER_Y);
	cam_model[rear_camera_index].CAM_SKEW_E = (pconfig.smc.REAR_CAMERA_SKEW_E);
	cam_model[rear_camera_index].CAM_LEN_TOP_CUT = (int)(pconfig.smc.REAR_CAMERA_IMAGE_TOP_CUT);

	sprintf(cam_model[rear_camera_index].CAM_LEN_DIST_LUT,"%s%s",XR_RES,pconfig.smc.REAR_CAMERA_LUT_FILE_NAME);



	return 0;
}


/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

AVMCameraInternal::AVMCameraInternal()
{
	mp_full_cam_model[0] = NULL;
	mp_full_cam_model[1] = NULL;
	mp_full_cam_model[2] = NULL;
	mp_full_cam_model[3] = NULL;

	m_camera_lut[0] = NULL;
	m_camera_lut[1] = NULL;
	m_camera_lut[2] = NULL;
	m_camera_lut[3] = NULL;

	mp_undist_linear_mdl[0] = NULL;
	mp_undist_linear_mdl[1] = NULL;
	mp_undist_linear_mdl[2] = NULL;
	mp_undist_linear_mdl[3] = NULL;

	mp_undist_Cyli_mdel[0] = NULL;
	mp_undist_Cyli_mdel[1] = NULL;
	mp_undist_Cyli_mdel[2] = NULL;
	mp_undist_Cyli_mdel[3] = NULL;
	
}
AVMCameraInternal::~AVMCameraInternal()
{
    for(int i=0;i<4;i++)
    {
        delete [] m_camera_lut[i];
    }



}

void AVMCameraInternal::InitParamFromSysConfig(CAMERA_CFG *cam_model,Camera_Param_T *p_sys_config,Smc_Cal_T *pSMC)
{
	Camera_Param_Cam_Int_T sys_cam_mdl;
    int j=0;
    for(int i =0;i<4;i++)
    {
        if(i == right_camera_index)
        {
            j=3;
        }
		else if (i == left_camera_index)
		{
		    j=2;
		}
		else if (i == front_camera_index)
		{
		    j=0;
		}
		else
		{
		    j=1;
		}
        sys_cam_mdl = p_sys_config[j].cam_int;

		cam_model[i].CAM_TYPE = 0;
		cam_model[i].CAM_INT_W = p_sys_config->cam_int.cam_int_w;
		cam_model[i].CAM_INT_H = sys_cam_mdl.cam_int_h;
		cam_model[i].CAM_INT_CX = sys_cam_mdl.cam_int_cu;
		cam_model[i].CAM_INT_CY = sys_cam_mdl.cam_int_cv;
		cam_model[i].CAM_SKEW_C = sys_cam_mdl.cam_int_skew_c;
		cam_model[i].CAM_SKEW_D = sys_cam_mdl.cam_int_skew_d;
		cam_model[i].CAM_LEN_ORIGIN_HFOV = sys_cam_mdl.cam_int_fu_or_hfov_at_cu;
		cam_model[i].CAM_LEN_ORIGIN_VFOV = sys_cam_mdl.cam_int_fv_or_vfov_at_cv;
		cam_model[i].CAM_SKEW_E = sys_cam_mdl.cam_int_skew_e;
		cam_model[i].CAM_LEN_TOP_CUT = sys_cam_mdl.cam_int_use_fov;
		printf("before cam_lut_index = %d ",sys_cam_mdl.cam_int_lut);

	    m_camera_lut[i] = pSMC->lut_table[sys_cam_mdl.cam_int_lut];
		printf("cam_lut_index =0x%x", m_camera_lut[i]);
    }

}

void AVMCameraInternal::InitLutMemory(void)
{
    for(int i=0;i<4;i++)
    {
        m_camera_lut[i] = new float [LUT_ROW_NUM];
    }


}

/*Init from pose file ,file sotre camera pose index as front right rear left*/
void AVMCameraInternal::Init( BEV_CONFIG_T pconfig)
{
     int i=0;



	get_camera_config(m_cam_cfg_fisheye,pconfig);
	InitLutMemory();

	for(i=0;i<4;i++)
	{

		ReadFloatSpaceTxtFile(m_cam_cfg_fisheye[i].CAM_LEN_DIST_LUT,m_camera_lut[i],LUT_ROW_NUM);
		Cam_InitIntrinsic(
			&m_cam_fisheye_instrict[i],m_cam_cfg_fisheye[i].CAM_INT_W,
			m_cam_cfg_fisheye[i].CAM_INT_H,
			m_cam_cfg_fisheye[i].CAM_INT_CX,
			m_cam_cfg_fisheye[i].CAM_INT_CY,
			m_cam_cfg_fisheye[i].CAM_SKEW_C,
			m_cam_cfg_fisheye[i].CAM_SKEW_D,
			m_cam_cfg_fisheye[i].CAM_SKEW_E,
			m_camera_lut[i],
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_HFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_VFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_TOP_CUT
			);
	}


}

void AVMCameraInternal::Init(Camera_Param_T *p_Int_Cam,Smc_Cal_T* pIntParam)
{
    int i=0;

    InitParamFromSysConfig(&m_cam_cfg_fisheye[0],p_Int_Cam,pIntParam);

	for(i=0;i<4;i++)
	{
		Cam_InitIntrinsic(
			&m_cam_fisheye_instrict[i],m_cam_cfg_fisheye[i].CAM_INT_W,
			m_cam_cfg_fisheye[i].CAM_INT_H,
			m_cam_cfg_fisheye[i].CAM_INT_CX,
			m_cam_cfg_fisheye[i].CAM_INT_CY,
			m_cam_cfg_fisheye[i].CAM_SKEW_C,
			m_cam_cfg_fisheye[i].CAM_SKEW_D,
			m_cam_cfg_fisheye[i].CAM_SKEW_E,
			m_camera_lut[i],
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_HFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_VFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_TOP_CUT
            );
	}


}

void AVMCameraInternal::Init(Smc_Cal_T *pIntParam)
{
     int i=0;

	 InitParamFromSysConfig(m_cam_cfg_fisheye, pIntParam->camera_param, pIntParam);


	for(i=0;i<4;i++)
	{

		Cam_InitIntrinsic(
			&m_cam_fisheye_instrict[i],m_cam_cfg_fisheye[i].CAM_INT_W,
			m_cam_cfg_fisheye[i].CAM_INT_H,
			m_cam_cfg_fisheye[i].CAM_INT_CX,
			m_cam_cfg_fisheye[i].CAM_INT_CY,
			m_cam_cfg_fisheye[i].CAM_SKEW_C,
			m_cam_cfg_fisheye[i].CAM_SKEW_D,
			m_cam_cfg_fisheye[i].CAM_SKEW_E,
			m_camera_lut[i],
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_HFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_ORIGIN_VFOV,
			m_cam_cfg_fisheye[i].CAM_LEN_TOP_CUT
			);
	}


}


void AVMCameraInternal::Init(Cam_Model_Intrinsic *pCamIntMdl)
{

    int j=0;

    for(int i =0;i<4;i++)
    {
        if(i == right_camera_index)
        {
            j=3;
        }
		else if (i == left_camera_index)
		{
		    j=2;
		}
		else if (i == front_camera_index)
		{
		    j=0;
		}
		else
		{
		    j=1;
		}

		m_cam_fisheye_instrict[i]=pCamIntMdl[j];

	}


}


void AVMCameraInternal::GetCameraWidth(float *width,int camera_index)
{
   *width = m_cam_cfg_fisheye[camera_index].CAM_INT_W;
   return;

}
void AVMCameraInternal::GetCameraHeight(float *height,int camera_index)
{
   *height = m_cam_cfg_fisheye[camera_index].CAM_INT_H;
   return;

}

void AVMCameraInternal::GetCameraInstrinct(Cam_Model_Intrinsic **matrix,int camera_index)
{
    	*matrix=&(m_cam_fisheye_instrict[camera_index]);
}

Cam_Model * AVMCameraInternal::GetFullCameraModel(int camera_index,float *pCameraR,float *pCam_T)
{
	 int i=0;
	if(mp_full_cam_model[camera_index]!= NULL)
	{
	    return mp_full_cam_model[camera_index];
	}
	
	
	mp_full_cam_model[camera_index] = new Cam_Model;

	Cam_Init(mp_full_cam_model[camera_index], 
		m_cam_cfg_fisheye[camera_index].CAM_INT_W, 
		m_cam_cfg_fisheye[camera_index].CAM_INT_H, 
		m_cam_cfg_fisheye[camera_index].CAM_INT_CX,  
		m_cam_cfg_fisheye[camera_index].CAM_INT_CY, 
		m_cam_cfg_fisheye[camera_index].CAM_SKEW_C,
		m_cam_cfg_fisheye[camera_index].CAM_SKEW_D, 
		m_cam_cfg_fisheye[camera_index].CAM_SKEW_E, 
		m_camera_lut[camera_index], 
		m_cam_cfg_fisheye[camera_index].CAM_LEN_ORIGIN_HFOV,
		m_cam_cfg_fisheye[camera_index].CAM_LEN_ORIGIN_VFOV,
		m_cam_cfg_fisheye[camera_index].CAM_LEN_TOP_CUT, 
		pCameraR, 
		pCam_T
		);

	return mp_full_cam_model[camera_index];
}

void AVMCameraInternal::MapCamRay2ImagePointGpu(float *pWld,float *pTex,int camera_index)
{

    Cam_MapCamRay2ImagePoint(
       pTex, 				   /* the output image point */
       pWld,			   /* the input normalized or not 3d ray in camera coordinate system */
       &m_cam_fisheye_instrict[camera_index]
       );
    pTex[0]/=m_cam_cfg_fisheye[camera_index].CAM_INT_W;
    pTex[1]/=m_cam_cfg_fisheye[camera_index].CAM_INT_H;


}
void AVMCameraInternal::SetUndistLinearCameraModel(int camera_index,Cam_Model* pLinearMdl)
{
    mp_undist_linear_mdl[camera_index] = pLinearMdl;

}

void AVMCameraInternal::SetUndistCyliCameraModel(int camera_index,Cam_Model_Cyli* pCyliMdl)
{
    mp_undist_Cyli_mdel[camera_index] = pCyliMdl;

}
Cam_Model *AVMCameraInternal::GetUndistLinearCameraModel(int camera_index)
{
    return mp_undist_linear_mdl[camera_index];
}

Cam_Model_Cyli *AVMCameraInternal::GetUndistCyliCameraModel(int camera_index)
{
    return mp_undist_Cyli_mdel[camera_index];
}
void AVMCameraInternal::SetUndistCamROI(int camera_index,int start_x,int start_y,int end_x,int end_y)
{
    m_undist_cam_roi[camera_index][roi_start_x_index]=start_x;
    m_undist_cam_roi[camera_index][roi_end_x_index]=end_x;
    m_undist_cam_roi[camera_index][roi_start_y_index]=start_y;
    m_undist_cam_roi[camera_index][roi_end_y_index]=end_y;

}
void AVMCameraInternal::SetLinearCamROI(int camera_index,int start_x,int start_y,int end_x,int end_y)
{
	m_linear_cam_roi[camera_index][roi_start_x_index]=start_x;
    m_linear_cam_roi[camera_index][roi_end_x_index]=end_x;
    m_linear_cam_roi[camera_index][roi_start_y_index]=start_y;
    m_linear_cam_roi[camera_index][roi_end_y_index]=end_y;
}
void AVMCameraInternal::MapImgPtFish2Linear(int camera_index,float *pSrc, float *pDst)
{
	if(pSrc == NULL)
	{
		return ;
	}

	float pSrcImage[2],pDistImage[2];

	//convert texture coordinate 2 image coord
    pSrcImage[0]=(pSrc[0])*mp_full_cam_model[camera_index]->cam_int.w;
	pSrcImage[1]=(pSrc[1])*mp_full_cam_model[camera_index]->cam_int.h;
	Cam_MapImagePoints_Fish2Linear(pDistImage,pSrcImage,1,mp_full_cam_model[camera_index],mp_undist_linear_mdl[camera_index]);

	float img_width  = m_linear_cam_roi[camera_index][roi_end_x_index] - m_linear_cam_roi[camera_index][roi_start_x_index];
	float img_height = m_linear_cam_roi[camera_index][roi_end_y_index] - m_linear_cam_roi[camera_index][roi_start_y_index];
	float img_start_pos_x = m_linear_cam_roi[camera_index][roi_start_x_index];
	float img_start_pos_y = m_linear_cam_roi[camera_index][roi_start_y_index];

	pDst[0] = -1.0+2.0*(pDistImage[0]-img_start_pos_x)/img_width;
	pDst[1] = 1.0-2.0*(pDistImage[1]-img_start_pos_y)/img_height;
}
void AVMCameraInternal::MapImgPtFish2Cylic(int camera_index,float *pSrc,float *pDst)
{
    float pSrcImage[2],pDistImage[2];
	float w,h;
	float x0,y0;
	//convert texture coordinate 2 image coord
    pSrcImage[0]=(pSrc[0])*mp_full_cam_model[camera_index]->cam_int.w;
	pSrcImage[1]=(pSrc[1])*mp_full_cam_model[camera_index]->cam_int.h;
	Cam_MapImagePoints_Fish2Cyli(pDistImage,pSrcImage,1,mp_full_cam_model[camera_index],mp_undist_Cyli_mdel[camera_index]);
    w= m_undist_cam_roi[camera_index][roi_end_x_index]- m_undist_cam_roi[camera_index][roi_start_x_index];
	h= m_undist_cam_roi[camera_index][roi_end_y_index]- m_undist_cam_roi[camera_index][roi_start_y_index];
    x0= m_undist_cam_roi[camera_index][roi_start_x_index];
	y0=m_undist_cam_roi[camera_index][roi_start_y_index];

	//according to ROI convert image coord 2 texture coord

	pDst[0] = -1.0+2.0*(pDistImage[0]-x0)/w;
	pDst[1] = 1.0-2.0*(pDistImage[1]-y0)/h;

    if(camera_index == rear_camera_index)
    {

	   pDst[0]=-pDst[0];
    }
	
}


/*===========================================================================*\
 * External Function Definitions
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/

