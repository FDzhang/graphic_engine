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


/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

AVMData* AVMData::m_pAVMData;

AVMData::AVMData()
{
;

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
    m_pAVMData->m_exParam = new DataExPosParam(config.bev_conig.smc_hmi.SPACE_MODEL_Y_MIN,config.bev_conig.smc_hmi.SPACE_MODEL_SCALE_SIZE);
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

	m_pAVMData->m_calib_3d.model_bottom = config.bev_conig.smc_hmi.SPACE_MODEL_Y_MIN;
	m_pAVMData->m_calib_3d.model_scale= SCALE_3D_TO_2D_X;

	m_pAVMData->m_calib_3d.vehicle_length= config.bev_conig.smc_hmi.VEHICLE_LENGTH;

	m_pAVMData->m_calib_3d.vehicle_rear_axis_2_bumper= config.bev_conig.smc_hmi.VEHICLE_REARWHEEL_TO_REAR_BUMPER;
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
	    m_pAVMData->m_exParam->Init(config.pPose,config.bev_conig.smc_hmi.VEHICLE_LENGTH,config.bev_conig.smc_hmi.VEHICLE_REARWHEEL_TO_REAR_BUMPER,exAdjustfile);
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
	m_pAVMData->m_Veh_Data = config.vehicle_para;

}
void AVMData::CalcUVTextureSV(float *pWorld,float *texture,int chann)
{

	XRVec4 WorldCoord,InCamCoord;
	float pt3d[3];
    double image2D[2],world3D[3];
	float *temp_trans;
	XRMat4 *uvTransform;

	WorldCoord = XRVec4::XRVec4(pWorld[0],pWorld[1],pWorld[2],1.0);

	m_pAVMData->m_exParam->GetTransformMatrix(&uvTransform,chann);
	m_pAVMData->m_exParam->GetInnerModelTransform(&temp_trans,chann);
	InCamCoord = (*uvTransform)*(WorldCoord+XRVec4::XRVec4(temp_trans[0],temp_trans[1],temp_trans[2],0.0));

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

void AVMData::Get3dViewRegion(Region** pRegion)
{
	*pRegion = &m_3dViewRegion;
}
void AVMData::GetStitchViewRegion(Region** pRegion)
{
	*pRegion = &m_stitchViewRegion;
}
void AVMData::GetSingleViewRegion(Region** pRegion)
{
	*pRegion = &m_singleViewRegion;
}
void AVMData::GetObjectViewRegion(Region** pRegion)
{
	*pRegion = &m_objectViewRegion;
}
void AVMData::GetBevConfig(BEV_CONFIG_T* pConfig)
{
	pConfig = (BEV_CONFIG_T*)malloc(sizeof(BEV_CONFIG_T));
}
void AVMData::GetCarTransparentStatus(unsigned char& pCarTranspStatus)
{
	pCarTranspStatus = m_carTranspStatus;
}
void AVMData::SetCarTransparentStatus(unsigned char pCarTranspStatus)
{
	m_carTranspStatus = pCarTranspStatus;
}
void AVMData::Get3dViewCameraParams(SurroundViewCameraParamsT** pCameraParams)
{
	*pCameraParams = &m_3dViewCameraParams;
}
void AVMData::GetObjectViewCameraParams(SurroundViewCameraParamsT** pCameraParams)
{
	*pCameraParams = &m_objectViewCameraParams;
}
void AVMData::GetStitchViewCameraParams(SurroundViewCameraParamsT** pCameraParams)
{
	*pCameraParams = &m_stitchViewCameraParams;
}
void AVMData::GetSingleViewCameraParams(SurroundViewCameraParamsT** pCameraParams)
{
	*pCameraParams = &m_singleViewCameraParams;
}
void AVMData::Set3dViewRegion(Region* pRegion)
{
	if(pRegion != NULL)
	{
		m_3dViewRegion = *pRegion;
	}
}
void AVMData::SetStitchViewRegion(Region* pRegion)
{
	if(pRegion != NULL)
	{
		m_stitchViewRegion = *pRegion;
	}
}
void AVMData::SetSingleViewRegion(Region* pRegion)
{
	if(pRegion != NULL)
	{
		m_singleViewRegion = *pRegion;
	}
}
void AVMData::SetObjectViewRegion(Region* pRegion)
{
	if(pRegion != NULL)
	{
		m_objectViewRegion = *pRegion;
	}
}
void AVMData::SetObjectViewCameraParams(SurroundViewCameraParamsT* pCameraParams)
{
	if(pCameraParams != NULL)
	{
		m_objectViewCameraParams = *pCameraParams;
	}
}
void AVMData::SetStitchViewCameraParams(SurroundViewCameraParamsT* pCameraParams)
{
	if(pCameraParams != NULL)
	{
		m_stitchViewCameraParams = *pCameraParams;
	}
}
void AVMData::SetSingleViewCameraParams(SurroundViewCameraParamsT* pCameraParams)
{
	if(pCameraParams != NULL)
	{
		m_singleViewCameraParams = *pCameraParams;		
	}
}
void AVMData::Set3dViewCameraParams(SurroundViewCameraParamsT* pCameraParams)
{
	if(pCameraParams != NULL)
	{
		m_3dViewCameraParams = *pCameraParams;		
	}
}
void AVMData::SetAnimationManager(IAnimationManager* pAm)
{
	if(pAm != NULL)
	{
		m_am = pAm;
	}
}
	
void AVMData::GetAnimationManager(IAnimationManager** pAm)
{
	*pAm = m_am;
}
void AVMData::GetSv2dData(GlSV2D** pGlSv2d)
{	
	*pGlSv2d = m_sv2dData;
}

void AVMData::SetSv2dData(GlSV2D* pGlSv2d)
{
	if(pGlSv2d != NULL)
	{
		m_sv2dData = pGlSv2d;
	}
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
void AVMData::cvtSingleViewImagePoint2GpuPoint(float *out_gpu_Coord,float *in_image_coord,bool rear_single_view)
{
    float in_coord_normal[2];
	float camera_width,camera_height;
	m_pAVMData->m_camInstrinct->GetCameraWidth(&camera_width,0);
	m_pAVMData->m_camInstrinct->GetCameraHeight(&camera_height,0);

	in_coord_normal[0] = in_image_coord[0]/camera_width;
	in_coord_normal[1] = in_image_coord[1]/camera_height;

	if(rear_single_view == 1)
	{
		out_gpu_Coord[2] = 0.0;
		out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_rear_single_view_rect[rect_top])/(m_pAVMData->m_rear_single_view_rect[rect_bottom]-m_pAVMData->m_rear_single_view_rect[rect_top])/0.5+1;
		out_gpu_Coord[0] = (-in_coord_normal[0]+m_pAVMData->m_rear_single_view_rect[rect_left])/(m_pAVMData->m_rear_single_view_rect[rect_left]-m_pAVMData->m_rear_single_view_rect[rect_right])/0.5-1;
	}
	else
	{

    	out_gpu_Coord[2] = 0.0;
    	out_gpu_Coord[1] = -(in_coord_normal[1]-m_pAVMData->m_front_single_view_rect[rect_top])/(m_pAVMData->m_front_single_view_rect[rect_bottom]-m_pAVMData->m_front_single_view_rect[rect_top])/0.5+1;
    	out_gpu_Coord[0] = (in_coord_normal[0]-m_pAVMData->m_front_single_view_rect[rect_left])/(m_pAVMData->m_front_single_view_rect[rect_right]-m_pAVMData->m_front_single_view_rect[rect_left])/0.5-1;

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

void AVMData::SetStitchViewNodeStatus(unsigned char pStatus)
{
	m_stitchViewNodeStatus = pStatus;
}
void AVMData::GetStitchViewNodeStatus(unsigned char& pStatus)
{
	pStatus = m_stitchViewNodeStatus;
}
void AVMData::Set3dViewNodeStatus(unsigned char pStatus)
{
	m_avm3dViewNodeStatus = pStatus;
}
void AVMData::Get3dViewNodeStatus(unsigned char& pStatus)
{
	pStatus = m_avm3dViewNodeStatus;
}
void AVMData::SetSingleViewNodeStatus(unsigned char pStatus)
{
	m_singleViewNodeStatus = pStatus;
}
void AVMData::GetSingleViewNodeStatus(unsigned char& pStatus)
{
	pStatus = m_singleViewNodeStatus;
}
void AVMData::SetObjectViewNodeStatus(unsigned char pStatus)
{
	m_objViewNodeStatus = pStatus;
}
void AVMData::GetObjectViewNodeStatus(unsigned char& pStatus)
{
	pStatus = m_objViewNodeStatus;
}

void AVMData::Set3dViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avm3dVisibility[pFuncId] = pFlag;
}
void AVMData::Get3dViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avm3dVisibility[pFuncId];
}
void AVMData::SetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmStitchViewVisibility[pFuncId] = pFlag;
}
void AVMData::GetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmStitchViewVisibility[pFuncId];
}
void AVMData::SetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmSingleViewVisibility[pFuncId] = pFlag;
}
void AVMData::GetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmSingleViewVisibility[pFuncId];
}
void AVMData::SetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmObjViewVisibility[pFuncId] = pFlag;
}
void AVMData::GetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmObjViewVisibility[pFuncId];
}

void AVMData::SetDisplayViewCmd(unsigned char pCmd)
{
	m_displayViewCmd = pCmd;
}
void AVMData::GetDisplayViewCmd(unsigned char& pCmd)
{
	pCmd = m_displayViewCmd;
}

void AVMData::SetSingleViewChannel(unsigned char pChannelId)
{
	m_singleViewChannel = pChannelId;
}
void AVMData::GetSingleViewChannel(unsigned char& pChannelId)
{
	pChannelId = m_singleViewChannel;
}

void AVMData::Set3dViewIndex(unsigned char pIndex)
{
	m_avm3dViewIndex = pIndex;
}
void AVMData::Get3dViewIndex(unsigned char& pIndex)
{
	pIndex = m_avm3dViewIndex;
}

void AVMData::SetSingleViewNode(class ISceneNode* pSingleViewNode)
{
	m_singleViewNode = pSingleViewNode;
}
void AVMData::GetSingleViewNode(class ISceneNode** pSingleViewNode)
{
	*pSingleViewNode = m_singleViewNode;
}

void AVMData::SetSingleViewMesh(class IMesh* pSingleViewMesh[])
{
	m_singleViewMesh[0] = pSingleViewMesh[0];
	m_singleViewMesh[1] = pSingleViewMesh[1];
	m_singleViewMesh[2] = pSingleViewMesh[2];
	m_singleViewMesh[3] = pSingleViewMesh[3];
}
void AVMData::GetSingleViewMesh(class IMesh* pSingleViewMesh[])
{
	pSingleViewMesh[0] = m_singleViewMesh[0];
	pSingleViewMesh[1] = m_singleViewMesh[1];
	pSingleViewMesh[2] = m_singleViewMesh[2];
	pSingleViewMesh[3] = m_singleViewMesh[3];
}

void AVMData::SetSingleViewVertex(float* pSingleViewVertex[])
{
	m_singleViewVertex[0] = pSingleViewVertex[0];
	m_singleViewVertex[1] = pSingleViewVertex[1];
	m_singleViewVertex[2] = pSingleViewVertex[2];
	m_singleViewVertex[3] = pSingleViewVertex[3];
}
void AVMData::GetSingleViewVertex(float* pSingleViewVertex[])
{
	pSingleViewVertex[0] = m_singleViewVertex[0];
	pSingleViewVertex[1] = m_singleViewVertex[1];
	pSingleViewVertex[2] = m_singleViewVertex[2];
	pSingleViewVertex[3] = m_singleViewVertex[3];
}

void AVMData::SetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[])
{
	m_singleViewPlaneNode[0] = pSingleViewPlaneNode[eFrontSingle];
	m_singleViewPlaneNode[1] = pSingleViewPlaneNode[eRearSingle];
	m_singleViewPlaneNode[2] = pSingleViewPlaneNode[eLeftSingle];
	m_singleViewPlaneNode[3] = pSingleViewPlaneNode[eRightSingle];
}
void AVMData::GetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[])
{
	pSingleViewPlaneNode[0] = m_singleViewPlaneNode[0];
	pSingleViewPlaneNode[1] = m_singleViewPlaneNode[1];
	pSingleViewPlaneNode[2] = m_singleViewPlaneNode[2];
	pSingleViewPlaneNode[3] = m_singleViewPlaneNode[3];
}

void AVMData::SetSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;

	static unsigned initFlag[4] = {0};
	if(initFlag[pViewIndex] == 0)
	{
		m_singleViewRoi[pViewIndex] = new float[28];
		initFlag[pViewIndex] = 1;
	}
	
	memcpy(m_singleViewRoi[pViewIndex], pSingleViewRoi, sizeof(float)*28);
}
void AVMData::GetSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;
	*pSingleViewRoi = m_singleViewRoi[pViewIndex];
}

void AVMData::SetLargeSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;

	static unsigned initFlag[4] = {0};
	if(initFlag[pViewIndex] == 0)
	{
		m_largeSingleViewRoi[pViewIndex] = new float[4];
		initFlag[pViewIndex] = 1;
	}
	
	memcpy(m_largeSingleViewRoi[pViewIndex], pSingleViewRoi, sizeof(float)*4);
}
void AVMData::GetLargeSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;
	*pSingleViewRoi = m_largeSingleViewRoi[pViewIndex];
}
void AVMData::GetTimeStitcherNode(class SVNode2DStich**	pTimeStitchNode)
{
	*pTimeStitchNode = m_timeStitchNode;
}
void AVMData::SetTimeStitcherNode(class SVNode2DStich*	pTimeStitchNode)
{
	m_timeStitchNode = pTimeStitchNode;
}
void AVMData::GetApaOverlayResult(APAOverlayStruct* pAPAReslt)
{
	*pAPAReslt = m_apaReslt;
}
void AVMData::SetApaOverlayResult(APAOverlayStruct pAPAReslt)
{
	m_apaReslt = pAPAReslt;
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

