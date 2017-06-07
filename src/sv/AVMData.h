#ifndef __AVM_DATA_H__
#define __AVM_DATA_H__

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
#include "DataStruct.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "DataSource/AVMCameraExparam.h"
#include "DataSource/AVMCameraInternal.h"
#include "DataSource/AVMLuminanceData.h"
#include "DataSource/AVM2DLUT.h"
#include "DataSource/AVMCANData.h"
#include "ICameraSourceRender.h"

#include "bev_config.h"
#include "smc.h"
//#include "VideoSource/CImageCameraSourceRender.h"

typedef struct Calib_3D_Para_T
{
    float model_scale;
	float model_bottom;
	float vehicle_length;
	float vehicle_axis_length;
	float vehicle_rear_axis_2_bumper;

}Calib_3D_Para;

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
typedef struct
{
	float sgxfps;
	float srcToSgxAvgLatency;
	float srcToSgxMaxLatency;
	float algAvgCost_ms;
	float algMaxCost_ms;
}ProcessInfoData;

class AVMProcessingInfo
{
public:
	AVMProcessingInfo()
	{
		m_Processing_Data.sgxfps = 0.0f;
		m_Processing_Data.srcToSgxAvgLatency = 0.0f;
		m_Processing_Data.srcToSgxMaxLatency = 0.0f;
		m_Processing_Data.algAvgCost_ms = 0.0f;
		m_Processing_Data.algMaxCost_ms = 0.0f;
	};
	~AVMProcessingInfo();
	void UpdateFps(float fps);
	void UpdateFrameLatency(float avg_in_ms, float max_in_ms);
	void UpdateAlgCost(float avg_in_ms, float max_in_ms);
	void GetProcessInfo(ProcessInfoData *pInfo);
	
private:
	ProcessInfoData m_Processing_Data;
};

class AVMData
{
public:
	
    static AVMData* GetInstance();
	static void InitConfig(SV_DATA_CONFIG_T config);
	
	static void CalcUVTextureSV(float *pWorld,float *texture,int chann);
	float GetFrontSingleViewRect(int index);
	float GetRearSingleViewRect(int index);
	
	void GetFrontSingleViewRect(float *pData);
	void GetRearSingleViewRect(float *pData);
	void GetVehicleParam(SV_VEHICLE_PARAM_T **pVehicleData);

	void cvtWorldPoint2Stich2DPoint(float *out_stich_Coord,float *in_world_coord,unsigned char unitmm=0);
	
	void cvtWorldPoint2ModelPoint3D(float *out_Model_Coord,float *in_world_coord);
	
	void cvtSingleViewImagePoint2GpuPoint(float *out_gpu_Coord,float *in_image_coord,bool rear_single_view);
		DataExPosParam *m_exParam;
		AVMCameraInternal *m_camInstrinct;
		AVMLuminanceData *m_lumin_para;
		AVM2DLUT *m_2D_lut;
		AVMCANData *m_p_can_data;
		ICameraSourceRender *m_cam_source;
		AVMProcessingInfo *m_process_info;

private:
    AVMData();

    static AVMData* m_pAVMData;
	//static CImageCameraSourceRender *m_pCamSourceIMG;
	SV_VEHICLE_PARAM_T m_Veh_Data;
	float m_front_single_view_rect[4];
	float m_rear_single_view_rect[4];
	Calib_3D_Para m_calib_3d;
    

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
