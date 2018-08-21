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
#include "AVMData.h"
#include "fileloader.h"
#include "DataStruct.h"
#include "VideoSource/CImageCameraSourceRender.h"
#include "VideoSource/CVideoCameraSourceRender.h"
#include "VideoSource/CJ6CameraSourceRender.h"
#include "VideoSource/CVideoBufferCameraSourceRender.h"

#include "gpu_log.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/
#define SCALE_TEST 0.34447
	 // #define SCALE_TEST 0.245
 #define SCALE_3D_TO_2D_X   SCALE_TEST
 #define SCALE_3D_TO_2D_Y   SCALE_TEST
 #define SCALE_3D_TO_2D_Z   SCALE_TEST

#define LINEAR_MODE 0

 #define FRONT_LINEAR_CAMERA_HEIGHT 960
 #define FRONT_LINEAR_CAMERA_WIDTH  1280
 #define FRONT_LINEAR_CAMERA_HFOV   20
 #define FRONT_LINEAR_CAMERA_VFOV   15
/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/
extern "C" FLT_T Cam_Lut_Linear[];
/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/


/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

AVMData* AVMData::m_pAVMData;

void _CamRay2ViewRay(FLT_T ray[3], const Cam_Model *cam)
{
    FLT_T r[3];
    if(cam->_is_view_rotated)
    {
        r[0] = cam->_inv_view_R[0] * ray[0] + cam->_inv_view_R[1] * ray[1] + cam->_inv_view_R[2] * ray[2];
        r[1] = cam->_inv_view_R[3] * ray[0] + cam->_inv_view_R[4] * ray[1] + cam->_inv_view_R[5] * ray[2];
        r[2] = cam->_inv_view_R[6] * ray[0] + cam->_inv_view_R[7] * ray[1] + cam->_inv_view_R[8] * ray[2];
        ray[0] = r[0]; ray[1] = r[1]; ray[2] = r[2];
    }
}

void _ViewRay2CamRay(FLT_T ray[3], const Cam_Model *cam)
{
    FLT_T t[3];
    if(cam->_is_view_rotated)
    {
        t[0] = cam->_view_R[0] * ray[0] + cam->_view_R[1] * ray[1] + cam->_view_R[2] * ray[2];
        t[1] = cam->_view_R[3] * ray[0] + cam->_view_R[4] * ray[1] + cam->_view_R[5] * ray[2];
        t[2] = cam->_view_R[6] * ray[0] + cam->_view_R[7] * ray[1] + cam->_view_R[8] * ray[2];
        ray[0] = t[0]; ray[1] = t[1]; ray[2] = t[2];
    }
}

AVMData::AVMData()
{
	m_2dParamUpdateFlag = 0;
	m_3dParamUpdateFlag = 0;
	m_seamDataChangeFlag = 0;

	m_exParam = NULL;
	m_camInstrinct = NULL;
	m_lumin_para = NULL;
	m_2D_lut = NULL;
	m_usc_data = NULL;
	m_p_can_data = NULL;
	m_cam_source = NULL;
	m_process_info = NULL;

}
AVMData* AVMData::GetInstance()
{
    if(m_pAVMData == NULL)
    {
        m_pAVMData = new AVMData;
    }

	return m_pAVMData;
}
void AVMData::InitConfig(SV_DATA_CONFIG_T config)
{
    char exfilename[MAX_NAME_LENGTH];
	char exAdjustfile[MAX_NAME_LENGTH];

	char LuminParafile[MAX_NAME_LENGTH];
	char configfile[MAX_NAME_LENGTH];
	char datafile[MAX_NAME_LENGTH];
	char indexfile[MAX_NAME_LENGTH];
	char carposefile[MAX_NAME_LENGTH];
	char carposeadjustfile[MAX_NAME_LENGTH];
	char calibfile[MAX_NAME_LENGTH];

	CImageCameraSourceRender *pCamSource;
    m_pAVMData->m_exParam = new DataExPosParam(config.pSmc->bev_3d_param.model_param.model_bottom,config.pSmc->bev_3d_param.model_param.model_scale);
    m_pAVMData->m_camInstrinct=new AVMCameraInternal;
	m_pAVMData->m_lumin_para = new AVMLuminanceData;
	m_pAVMData->m_2D_lut = new AVM2DLUT;
	m_pAVMData->m_p_can_data = new AVMCANData;
	m_pAVMData->m_process_info = new AVMProcessingInfo;	
	m_pAVMData->m_usc_data= new AVMUSCData;
	
    if(config.platform_config == PLATFORM_PC_IMAGE)
    {
        pCamSource = new CImageCameraSourceRender;
        m_pAVMData->m_cam_source = pCamSource;
	}
	else if(config.platform_config == PLATFORM_PC_VIDEO)
	{
     //   pCamSource = new CVideoCameraSourceRender;
        m_pAVMData->m_cam_source = new CVideoCameraSourceRender;


	}
	else if(config.platform_config == PLATFORM_J6)
	{
     //   pCamSource = new CVideoCameraSourceRender;
        m_pAVMData->m_cam_source = new CJ6CameraSourceRender;;

	}
	else if(config.platform_config == PLATFORM_PC_VIDEO_LIVE)
	{
     //   pCamSource = new CVideoCameraSourceRender;
        m_pAVMData->m_cam_source = new CVideoBufferCameraSourceRender;

	}

    m_pAVMData->m_calib_3d.model_bottom = config.pSmc->bev_3d_param.model_param.model_bottom;
    m_pAVMData->m_calib_3d.model_scale = SCALE_3D_TO_2D_X;
       
    m_pAVMData->m_calib_3d.vehicle_length= config.pSmc->veh_param.veh_length;
       
    m_pAVMData->m_calib_3d.vehicle_rear_axis_2_bumper= config.pSmc->veh_param.veh_rwheel2tail;
	
	sprintf(exfilename,"%s%s",config.file_path,config.exparam_file_name);
	sprintf(exAdjustfile,"%s%s",config.file_path,config.exparam_adjust_file_name);
	sprintf(LuminParafile,"%s%s",config.file_path,config.lumin_pos_file_name);
	sprintf(indexfile,"%s%s",config.file_path,config.lut_index_file_name);
	sprintf(datafile,"%s%s",config.file_path,config.lut_data_file_name);
	sprintf(calibfile,"%s%s",config.file_path,config.car_calib_name);
	sprintf(configfile,"%s%s",config.file_path,config.lut_config_file_name);
	sprintf(carposefile,"%s%s",config.file_path,config.car_pose_file_name);
	sprintf(carposeadjustfile,"%s%s",config.file_path,config.car_pose_adjust_file_name);
	if(config.config_file_source == CFG_FROM_FILE)
	{
	    m_pAVMData->m_exParam->Init(exfilename,config.bev_conig.smc_hmi.VEHICLE_LENGTH,config.bev_conig.smc_hmi.VEHICLE_REARWHEEL_TO_REAR_BUMPER,exAdjustfile);
        m_pAVMData->m_camInstrinct->Init(config.bev_conig);
	}
	else if(config.config_file_source == CFG_FROM_SYS)
	{
		m_pAVMData->m_exParam->Init(config.pPose,config.pSmc->veh_param.veh_length,config.pSmc->veh_param.veh_rwheel2tail);
        //m_pAVMData->m_camInstrinct->Init(config.pSmc);
        m_pAVMData->m_camInstrinct->Init(config.pCamParam,config.pSmc);
	}

	m_pAVMData->m_lumin_para->Init(LuminParafile);
	//m_pAVMData->m_2D_lut->Init(configfile,indexfile,datafile,carposefile,carposeadjustfile,calibfile);
	if(config.pSticherResult != NULL)
	{
	    m_pAVMData->m_2D_lut->Init(configfile,indexfile,datafile,0,config.pSticherResult);
		fprintf(stdout,"\r\n load config calibresult");
    }
	m_pAVMData->m_cam_source->Init(config.file_path);
	m_pAVMData->m_p_can_data->Init();
	m_pAVMData->m_usc_data->Init(config.pSmc->bev_decoder_param, config.pSmc->bev_display_param, config.pSmc->bev_3d_param, config.pSmc->bev_ui_param);

	memcpy(m_pAVMData->m_front_single_view_rect,config.front_single_view_rect,4*sizeof(float));
	memcpy(m_pAVMData->m_rear_single_view_rect,config.rear_single_view_rect,4*sizeof(float));
	memcpy(m_pAVMData->m_left_single_view_rect,config.left_single_view_rect,4*sizeof(float));
	memcpy(m_pAVMData->m_right_single_view_rect,config.right_single_view_rect,4*sizeof(float));

	m_pAVMData->m_Veh_Data = config.vehicle_para;
    m_pAVMData->m_vehParam = config.pSmc->veh_param;
    m_pAVMData->m_smc = config.pSmc;
    if(LINEAR_MODE)
    {
        InitLinearCameraModel(front_camera_index);
		InitLinearCameraModel(rear_camera_index);

		InitLinearCameraModel(left_camera_index);

		InitLinearCameraModel(right_camera_index);
    }
}
void AVMData::InitLinearCameraModel(int camera_index)
{
    Cam_Model *pRealCam;
    float prsource[3];
	float ptsource[3];
	
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);
    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);
    AVMData::GetInstance()->m_pFishCam[camera_index] = pRealCam;
    
	AVMData::GetInstance()->m_pLinearCam[camera_index] = new Cam_Model;
 	Cam_Init(AVMData::GetInstance()->m_pLinearCam[camera_index], 
		FRONT_LINEAR_CAMERA_WIDTH,FRONT_LINEAR_CAMERA_HEIGHT,
		FRONT_LINEAR_CAMERA_WIDTH/2.0, FRONT_LINEAR_CAMERA_HEIGHT/2.0, 
		1, 0, 0, 
		Cam_Lut_Linear,
		FRONT_LINEAR_CAMERA_HFOV*deg2rad, 
		FRONT_LINEAR_CAMERA_VFOV*deg2rad, 
		true, 
		prsource, 
		ptsource
		);
	float a[3];
    a[0] = -0.5; a[1] = 0.0; a[2] = -0.0;
	Cam_UpdateViewRotation(AVMData::GetInstance()->m_pLinearCam[camera_index], a);

	return ;
}
void AVMData::CvtFishEyeCoord2LinearCoord(float in_fish_coord[2],float out_linear_coord[2],int camera_index)
{
	FLT_T ray[3];
    Cam_Model_Intrinsic *pFishCam;
	
	AVMData::GetInstance()->m_camInstrinct->GetCameraInstrinct(&pFishCam,camera_index);
	Cam_MapImagePoint2CamRay(ray,in_fish_coord,pFishCam);
	_CamRay2ViewRay(ray, AVMData::GetInstance()->m_pFishCam[camera_index]);
	_ViewRay2CamRay(ray, AVMData::GetInstance()->m_pLinearCam[camera_index]);
	Cam_MapCamRay2ImagePoint(out_linear_coord,ray,&(AVMData::GetInstance()->m_pLinearCam[camera_index]->cam_int));
	
    return;
}

void AVMData::CvtLinearCoord2FishEyeCoord(float in_linear_coord[2],float out_fish_coord[2],int camera_index)
{
	FLT_T ray[3];
    Cam_Model_Intrinsic *pFishCam;
	
	AVMData::GetInstance()->m_camInstrinct->GetCameraInstrinct(&pFishCam,camera_index);
	Cam_MapImagePoint2CamRay(ray,in_linear_coord,&(AVMData::GetInstance()->m_pLinearCam[camera_index]->cam_int));
	_CamRay2ViewRay(ray, AVMData::GetInstance()->m_pLinearCam[camera_index]);
	_ViewRay2CamRay(ray, AVMData::GetInstance()->m_pFishCam[camera_index]);
	Cam_MapCamRay2ImagePoint(out_fish_coord,ray,pFishCam);
	
    return;
}
void AVMData::CalcUVTextureSV(float *pWorldin,float *texture,int chann)
{
#if 1 - LINEAR_MODE
	XRVec4 WorldCoord,InCamCoord;
	float pt3d[3];
    double image2D[2],world3D[3];
	float *temp_trans;
	XRMat4 *uvTransform;
	float pWorld[3];

#if 1
	pWorld[0] = (0.004613610149942*pWorldin[2] * pWorldin[2] / 1000 / 1000 + 1.666666666666667)*pWorldin[0];
	  // pWorld[0]=pWorldin[0]*kp;
	pWorld[1]=pWorldin[1];
	pWorld[2]=pWorldin[2];
#else
	float kp;
	int turn_point = 250;
	   if(chann == rear_camera_index|| chann == left_camera_index)
	   {
		   if (pWorldin[2] > turn_point)
		   {
			  kp = (1.0 + 0.3*(pWorldin[2] - turn_point) / (850 - turn_point));

		   }
		   else if (pWorldin[2] < -turn_point)
		   {
			  // kp = (2 - (pWorldin[2] + 850)*1 / (850 - turn_point));

		   }
		   else
		   {

		   }
		   //front
		   //kp = (1.0 + (pWorldin[2] + 250)*0.3 / (850 + 250));
		   //rear
		   kp = (1.3 - (pWorldin[2] + 850)*0.3 / (850 +250));
	   }
	   else if (chann == front_camera_index|| chann == right_camera_index)
	   {
		   if (pWorldin[2] > turn_point)
		   {
			 //  kp = (1.0 + (pWorldin[2] - turn_point)*1 / (850 - turn_point));
		   }
		   else if (pWorldin[2] < -turn_point)
		   {
			   kp = (1.3 - 0.3*(pWorldin[2] + 850)*1 / (850 + turn_point));
		   }
		   else
		   {

		   }
		   //front
		   //kp = (1.3 - (pWorldin[2] + 850)*0.3 / (850 +250));
		   //rear
		   kp = (1.0 + (pWorldin[2] + 250)*0.3 / (850 + 250));
	   }

	pWorld[0]=pWorldin[0]*kp;
	   pWorld[1]=pWorldin[1];
	   pWorld[2]=pWorldin[2];
#endif	   
	WorldCoord = XRVec4(pWorld[0],pWorld[1],pWorld[2],1.0);

	m_pAVMData->m_exParam->GetTransformMatrix(&uvTransform,chann);
	m_pAVMData->m_exParam->GetInnerModelTransform(&temp_trans,chann);
	InCamCoord = (*uvTransform)*(WorldCoord+XRVec4(temp_trans[0],temp_trans[1],temp_trans[2],0.0));

	pt3d[0] = InCamCoord.x;
	pt3d[1] = InCamCoord.y;
	pt3d[2] = InCamCoord.z;

   m_pAVMData->m_camInstrinct->MapCamRay2ImagePointGpu(pt3d,texture,chann);
#else
  	XRVec4 WorldCoord,InCamCoord;
	float pt3d[3];
    double image2D[2],world3D[3];
	float *temp_trans;
	XRMat4 *uvTransform;

    float current_vanish_point=230.f/720.f;
    float expect_vanish_point =280.f/720.f;
    float border_row = 350.f/720.f;
    float linear_border_row = 442.f; //590 //432  //442
	float linear_border_column = 442.0f;
    float linear_expect_vanish_pt = 380.f; //380   //300 //210 //372 //380
    float linear_current_vanish_pt = 163.f; //163
    float texture_border[2];
    float scale;
    float temp;
    float fish_coord_point[2];
    float linear_coord_point[2];
    float linear_coord_border[2];
    float camera_width,camera_height;
    float temp_texture[2];
    float pWorld[3];
    float max_scale =0.5;
    float height =200;
    float portion;

    pWorld[0]=pWorldin[0];
    pWorld[1]=pWorldin[1];
    pWorld[2]=pWorldin[2];
    if(LINEAR_MODE)
    {
        if(chann == front_camera_index &&(pWorld[1]>-560))
        {
            //pWorld[1] = pWorld[1] + 1.05* (pWorld[1] + 560);
        }    
		if(chann == front_camera_index &&(pWorldin[0]<0))
		{
		   //pWorldin[0] = pWorldin[0] + 0.9* (pWorldin[0]);
		} 
		else if(chann == front_camera_index &&(pWorldin[0]>0))
		{
			//pWorldin[0] = pWorldin[0] - 0.6* (pWorldin[0]);
		}
    }
	WorldCoord = XRVec4::XRVec4(pWorld[0],pWorld[1],pWorld[2],1.0);

	m_pAVMData->m_exParam->GetTransformMatrix(&uvTransform,chann);
	m_pAVMData->m_exParam->GetInnerModelTransform(&temp_trans,chann);
	InCamCoord = (*uvTransform)*(WorldCoord+XRVec4::XRVec4(temp_trans[0],temp_trans[1],temp_trans[2],0.0));

	pt3d[0] = InCamCoord.x;
	pt3d[1] = InCamCoord.y;
	pt3d[2] = InCamCoord.z;

   m_pAVMData->m_camInstrinct->MapCamRay2ImagePointGpu(pt3d,texture,chann);

    if(LINEAR_MODE)
    {
        if(chann == front_camera_index)   //front_camera_index
        {
            AVMData::GetInstance()->m_camInstrinct->GetCameraWidth(&camera_width,front_camera_index);	
            AVMData::GetInstance()->m_camInstrinct->GetCameraHeight(&camera_height,front_camera_index);
            fish_coord_point[0]= texture[0]*camera_width; 
            fish_coord_point[1]= texture[1]*camera_height;
            CvtFishEyeCoord2LinearCoord(fish_coord_point,linear_coord_point,chann);

#if 1
            linear_border_row = 880;  //600
			linear_border_column = 880;  //600
			if((chann == front_camera_index 
				||rear_camera_index == chann)
				&&(linear_coord_point[1]>-540))
			{
				//linear_coord_point[0] = (1.0-0.7*((linear_coord_point[1]+540)/(500+540)))*linear_coord_point[0];// + 0.85* (pWorld[1] + 540);
				//linear_coord_point[1] = -540 + 0.9*(linear_coord_point[1] + 540);
				//linear_coord_point[1] = linear_coord_point[1] + 0.2 * linear_coord_point[1];
			}
            if(linear_coord_point[1]<linear_border_row)
            {
                scale = 1.0 - (linear_border_row - linear_coord_point[1]) * 0.002;
                if(scale < 0.85) scale = 0.85;
                scale = 0.85;  //0.2857
                linear_coord_point[1]=linear_border_row-scale*(linear_border_row - linear_coord_point[1]);

				scale = 1.0 - (linear_border_column - linear_coord_point[0]) * 0.002;
                if(scale < 0.45) scale = 0.45;
                scale = 0.45;  //0.2857
                //linear_coord_point[0]=linear_border_column-scale*(linear_border_column - linear_coord_point[0]);
    

                CvtLinearCoord2FishEyeCoord(linear_coord_point, fish_coord_point,chann);
                texture[0] = fish_coord_point[0] / camera_width;
                texture[1] = fish_coord_point[1] / camera_height;
				//texture[0] = 0;
				/*if(texture[0] < 0.5)
                {
					texture[0] = texture[0] + 0.01;
				}
				else
				{
					texture[0] = texture[0] + 0.03;
				}*/
           }
		}	
            
#endif
		if(chann == left_camera_index)   //front_camera_index
        {
            AVMData::GetInstance()->m_camInstrinct->GetCameraWidth(&camera_width,chann);	
            AVMData::GetInstance()->m_camInstrinct->GetCameraHeight(&camera_height,chann);
            fish_coord_point[0]= texture[0]*camera_width; 
            fish_coord_point[1]= texture[1]*camera_height;
            CvtFishEyeCoord2LinearCoord(fish_coord_point,linear_coord_point,chann);

#if 1
            linear_border_row = 880;  //600
			linear_border_column = 880;  //600
            if(linear_coord_point[1]<linear_border_row)
            {
                scale = 1.0 - (linear_border_row - linear_coord_point[1]) * 0.002;
  				float rate_raw = 0.95;
                if(scale < rate_raw) scale = rate_raw;
                scale = rate_raw;  //0.2857
                linear_coord_point[1]=linear_border_row-scale*(linear_border_row - linear_coord_point[1]);

				scale = 1.0 - (linear_border_column - linear_coord_point[0]) * 0.002;
                if(scale < 0.45) scale = 0.45;
                scale = 0.45;  //0.2857
                //linear_coord_point[0]=linear_border_column-scale*(linear_border_column - linear_coord_point[0]);
    

                CvtLinearCoord2FishEyeCoord(linear_coord_point, fish_coord_point,chann);
                texture[0] = fish_coord_point[0] / camera_width;
                texture[1] = fish_coord_point[1] / camera_height;
				//texture[0] = 0;
				/*if(texture[0] < 0.5)
                {
					texture[0] = texture[0] + 0.01;
				}
				else
				{
					texture[0] = texture[0] + 0.03;
				}*/
           }
			
		}   
#endif
		if(chann == right_camera_index)   //front_camera_index
        {
            AVMData::GetInstance()->m_camInstrinct->GetCameraWidth(&camera_width,chann);	
            AVMData::GetInstance()->m_camInstrinct->GetCameraHeight(&camera_height,chann);
            fish_coord_point[0]= texture[0]*camera_width; 
            fish_coord_point[1]= texture[1]*camera_height;
            CvtFishEyeCoord2LinearCoord(fish_coord_point,linear_coord_point,chann);

#if 1
            linear_border_row = 880;  //600
			linear_border_column = 880;  //600
            if(linear_coord_point[1]<linear_border_row)
            {
                scale = 1.0 - (linear_border_row - linear_coord_point[1]) * 0.002;
  				float rate_raw = 0.95;
                if(scale < rate_raw) scale = rate_raw;
                scale = rate_raw;  //0.2857
                linear_coord_point[1]=linear_border_row-scale*(linear_border_row - linear_coord_point[1]);

				scale = 1.0 - (linear_border_column - linear_coord_point[0]) * 0.002;
                if(scale < 0.45) scale = 0.45;
                scale = 0.45;  //0.2857
                //linear_coord_point[0]=linear_border_column-scale*(linear_border_column - linear_coord_point[0]);
    

                CvtLinearCoord2FishEyeCoord(linear_coord_point, fish_coord_point,chann);
                texture[0] = fish_coord_point[0] / camera_width;
                texture[1] = fish_coord_point[1] / camera_height;
				//texture[0] = 0;
				/*if(texture[0] < 0.5)
                {
					texture[0] = texture[0] + 0.01;
				}
				else
				{
					texture[0] = texture[0] + 0.03;
				}*/
           }
			
            
#endif
        }
		if(chann == rear_camera_index)   //front_camera_index
        {
            AVMData::GetInstance()->m_camInstrinct->GetCameraWidth(&camera_width,chann);	
            AVMData::GetInstance()->m_camInstrinct->GetCameraHeight(&camera_height,chann);
            fish_coord_point[0]= texture[0]*camera_width; 
            fish_coord_point[1]= texture[1]*camera_height;
            CvtFishEyeCoord2LinearCoord(fish_coord_point,linear_coord_point,chann);

#if 1
            linear_border_row = 880;  //600
			linear_border_column = 880;  //600
				
			scale = 1.0 - (linear_border_column - linear_coord_point[0]) * 0.002;
			float rate_raw = 0.95;
			if(scale < rate_raw) scale = rate_raw;
			scale = rate_raw;  //0.2857
            linear_coord_point[0]=linear_border_column-scale*(linear_border_column - linear_coord_point[0]);

            if(linear_coord_point[1]<linear_border_row)
            {
                scale = 1.0 - (linear_border_row - linear_coord_point[1]) * 0.002;
                float rate_raw = 0.95;
                if(scale < rate_raw) scale = rate_raw;
                scale = rate_raw;  //0.2857
                linear_coord_point[1]=linear_border_row-scale*(linear_border_row - linear_coord_point[1]);

                CvtLinearCoord2FishEyeCoord(linear_coord_point, fish_coord_point,chann);
                texture[0] = fish_coord_point[0] / camera_width;
                texture[1] = fish_coord_point[1] / camera_height;
				//texture[0] = 0;
				/*if(texture[0] < 0.5)
                {
					texture[0] = texture[0] + 0.01;
				}
				else
				{
					texture[0] = texture[0] + 0.03;
				}*/
           }
			
            
#endif
        }
    }
#endif


}
void AVMData::CalcUVTextureCV(float *pWorld,float *texture,int chann)
{

  XRVec4 WorldCoord,InCamCoord;
  float pt3d[3];
    double image2D[2],world3D[3];
  float *temp_trans;
  XRMat4 *uvTransform;

  WorldCoord = XRVec4(-pWorld[2],pWorld[0],-pWorld[1],1.0);

  //m_pAVMData->m_exParam->GetTransformMatrix(&uvTransform,chann);
  //m_pAVMData->m_exParam->GetInnerModelTransform(&temp_trans,chann);
  InCamCoord = XRMat4::RotationZ(3.1415926*(-0.03))*XRMat4::RotationY(3.1415926*(0.5))*XRMat4::RotationX(3.1415926*(0.5))*WorldCoord;//(*uvTransform)*(WorldCoord+XRVec4::XRVec4(temp_trans[0],temp_trans[1],temp_trans[2],0.0));
   //InCamCoord = (WorldCoord+XRVec4::XRVec4(temp_trans[0],temp_trans[1],temp_trans[2],0.0));

  pt3d[0] = InCamCoord.x;
  pt3d[1] = InCamCoord.y;
  pt3d[2] = InCamCoord.z;

   m_pAVMData->m_camInstrinct->MapCamRay2ImagePointGpu(pt3d,texture,chann);
}
float AVMData::GetFrontSingleViewRect(int index)
{

	return m_pAVMData->m_front_single_view_rect[index];
}
float AVMData::GetRearSingleViewRect(int index)
{

	return m_pAVMData->m_rear_single_view_rect[index];
}
float AVMData::GetLeftSingleViewRect(int index)
{

	return m_pAVMData->m_left_single_view_rect[index];
}
float AVMData::GetRightSingleViewRect(int index)
{

	return m_pAVMData->m_right_single_view_rect[index];
}



void AVMData::GetFrontSingleViewRect(float *pData)
{
	memcpy(pData,m_pAVMData->m_front_single_view_rect,4*sizeof(float));

}
void AVMData::GetRearSingleViewRect(float *pData)
{

	memcpy(pData,m_pAVMData->m_rear_single_view_rect,4*sizeof(float));
}
void AVMData::GetVehicleParam(SV_VEHICLE_PARAM_T **pVehicleData)
{

	*pVehicleData = &m_pAVMData->m_Veh_Data;
}

void AVMData::GetVehicleParam(Veh_Param_T **pVehicleData)
{
    *pVehicleData = &m_pAVMData->m_vehParam;
}

void AVMData::GetBevConfig(BEV_CONFIG_T* pConfig)
{
	*pConfig = m_bevConfig;
}
void AVMData::SetBevConfig(BEV_CONFIG_T pConfig)
{
	m_bevConfig = pConfig;
}
	
void AVMData::Calc3DGroundPos(float *pPose,float *pWidth,float*pHeight)
{
    float car_point[4];
	GpuCvPoint2D32f car_rect[2];
	GpuCvPoint2D32f car_rect_world[2];
	float pModelPoint[6];
	float pWorldPint[6];
	
    int i=0;

	for(i=0;i<4;i++)
	{
	    m_2D_lut->GetCarRect(&car_point[i],i);
		
	}

	car_rect[0].x = car_point[rect_left];
	car_rect[0].y = car_point[rect_top];
	car_rect[1].x = car_point[rect_right];
	car_rect[1].y = car_point[rect_bottom];
	
    for(i = 0;i<2;i++)
    {
	    m_2D_lut->CvtPointImage2Wolrd(car_rect[i],&car_rect_world[i]);

		pWorldPint[3*i] = car_rect_world[i].x;
	    pWorldPint[3*i+1] = car_rect_world[i].y;
        pWorldPint[3*i+2] = 0;
		
        cvtWorldPoint2ModelPoint3D(&pModelPoint[3*i],&pWorldPint[3*i]);
    }

	*pWidth = pModelPoint[3]-pModelPoint[0];
	*pHeight = pModelPoint[2]-pModelPoint[5];
	pPose[0] = (pModelPoint[3]+pModelPoint[0])/2.0;
	pPose[1] = pModelPoint[1];
	pPose[2] = (pModelPoint[2]+pModelPoint[5])/2.0;
}

//input world unit is meter,
void AVMData::cvtWorldPoint2ModelPoint3D(float *out_Model_Coord,float *in_world_coord)
{
    out_Model_Coord[2] = -m_pAVMData->m_calib_3d.model_scale*(in_world_coord[0]*1000-((m_pAVMData->m_calib_3d.vehicle_length/2)-m_pAVMData->m_calib_3d.vehicle_rear_axis_2_bumper));
    out_Model_Coord[1] = -m_pAVMData->m_calib_3d.model_bottom*3.5-m_pAVMData->m_calib_3d.model_scale*in_world_coord[2]*1000;
    out_Model_Coord[0] = m_pAVMData->m_calib_3d.model_scale*(in_world_coord[1]*1000);

}
void AVMData::cvtWorldPoint2Stich2DPoint(float *out_stich_Coord,float *in_world_coord,unsigned char unitmm)
{
	GpuCvPoint2D32f inPoint;
	GpuCvPoint2D32f outPoint;
	inPoint.x = in_world_coord[0];
    inPoint.y = in_world_coord[1];
    if(unitmm == 1)
    {
	    m_pAVMData->m_2D_lut->CvtPointWorld2ImageUnitmm(inPoint,&outPoint);
        
    }
	else
	{
    m_pAVMData->m_2D_lut->CvtPointWorld2Image(inPoint,&outPoint);
	}
    out_stich_Coord[0] = outPoint.x;
	out_stich_Coord[1] = outPoint.y;
	out_stich_Coord[2] = 0.1;
}
void AVMData::cvtSingleViewImagePoint2GpuPoint(float *out_gpu_Coord,float *in_image_coord,unsigned char single_view_index)
{
    float in_coord_normal[2];
	float camera_width,camera_height;
	m_pAVMData->m_camInstrinct->GetCameraWidth(&camera_width,0);
	m_pAVMData->m_camInstrinct->GetCameraHeight(&camera_height,0);

	in_coord_normal[0] = in_image_coord[0]/camera_width;
	in_coord_normal[1] = in_image_coord[1]/camera_height;

	if(single_view_index == rear_camera_index)
	{
		out_gpu_Coord[2] = 0.0;
		out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_rear_single_view_rect[rect_top])/(m_pAVMData->m_rear_single_view_rect[rect_bottom]-m_pAVMData->m_rear_single_view_rect[rect_top])/0.5+1;
		out_gpu_Coord[0] = (-in_coord_normal[0]+m_pAVMData->m_rear_single_view_rect[rect_left])/(m_pAVMData->m_rear_single_view_rect[rect_left]-m_pAVMData->m_rear_single_view_rect[rect_right])/0.5-1;
	}
	else if(single_view_index == front_camera_index)
	{
	
    	out_gpu_Coord[2] = 0.0;
    	out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_front_single_view_rect[rect_top])/(m_pAVMData->m_front_single_view_rect[rect_bottom]-m_pAVMData->m_front_single_view_rect[rect_top])/0.5+1;
    	out_gpu_Coord[0] = (in_coord_normal[0]-m_pAVMData->m_front_single_view_rect[rect_left])/(m_pAVMData->m_front_single_view_rect[rect_right]-m_pAVMData->m_front_single_view_rect[rect_left])/0.5-1;
	
	}
	else if(single_view_index == left_camera_index)
	{
    	out_gpu_Coord[2] = 0.0;
    	out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_left_single_view_rect[rect_top])/(m_pAVMData->m_left_single_view_rect[rect_bottom]-m_pAVMData->m_left_single_view_rect[rect_top])/0.5+1;
    	out_gpu_Coord[0] = (in_coord_normal[0]-m_pAVMData->m_left_single_view_rect[rect_left])/(m_pAVMData->m_left_single_view_rect[rect_right]-m_pAVMData->m_left_single_view_rect[rect_left])/0.5-1;

	}
	else if(single_view_index == right_camera_index)
	{
		out_gpu_Coord[2] = 0.0;
    	out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_right_single_view_rect[rect_bottom])/(m_pAVMData->m_right_single_view_rect[rect_top]-m_pAVMData->m_right_single_view_rect[rect_bottom])/0.5+1;
    	out_gpu_Coord[0] = (in_coord_normal[0]-m_pAVMData->m_right_single_view_rect[rect_right])/(m_pAVMData->m_right_single_view_rect[rect_left]-m_pAVMData->m_right_single_view_rect[rect_right])/0.5-1;

	}
}

void AVMProcessingInfo::UpdateFps(float fps)
{
	m_Processing_Data.sgxfps = fps;
}

void AVMProcessingInfo::UpdateFrameLatency(float avg_in_ms, float max_in_ms)
{
	m_Processing_Data.srcToSgxAvgLatency = avg_in_ms;
	m_Processing_Data.srcToSgxMaxLatency = max_in_ms;
}

void AVMProcessingInfo::UpdateAlgCost(float avg_in_ms, float max_in_ms)
{
	m_Processing_Data.algAvgCost_ms = avg_in_ms;
	m_Processing_Data.algMaxCost_ms = max_in_ms;
}

void AVMProcessingInfo::GetProcessInfo(ProcessInfoData *pInfo)
{
	if(pInfo)
	{
		memcpy(pInfo, &m_Processing_Data, sizeof(ProcessInfoData));
	}
}



void AVMData::SetStitchAngle(unsigned char pSeamChangedFlag, unsigned char* pSeamChangeFlag,GLfloat* pVertex)
{
	m_seamDataChangeFlag = pSeamChangedFlag;

	m_seamUpdateFlag = pSeamChangeFlag;
	m_seamUpdateData = pVertex;
}
void AVMData::GetStitchAngle(unsigned char& pSeamChangedFlag, unsigned char** pSeamChangeFlag,GLfloat** pVertex)
{
	pSeamChangedFlag = m_seamDataChangeFlag;

	*pSeamChangeFlag = m_seamUpdateFlag;
	*pVertex = m_seamUpdateData;
}
void AVMData::Set2DParam(unsigned char pUpdateFlag, GLfloat *pData,GLushort *pIndex)
{
	m_2dParamUpdateFlag = pUpdateFlag;
	m_2dParamData = pData;
	m_2dParamIndex = pIndex;
}
void AVMData::Set3DParam(unsigned char pUpdateFlag, float *pos)
{
	m_3dParamUpdateFlag = pUpdateFlag;
	m_3dParamPos = pos;
}
void AVMData::Get2DParam(unsigned char& pUpdateFlag, GLfloat **pData,GLushort **pIndex)
{
	pUpdateFlag = m_2dParamUpdateFlag;
	*pData = m_2dParamData;
	*pIndex = m_2dParamIndex;
}
void AVMData::Get3DParam(unsigned char& pUpdateFlag, float **pos)
{
	pUpdateFlag = m_3dParamUpdateFlag;
	*pos  = m_3dParamPos;
}
void AVMData::GetSmc(Smc_Cal_T **pSmc)
{
	*pSmc = m_pAVMData->m_smc;
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

