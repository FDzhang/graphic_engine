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
#include "DataSource/AVMUSCData.h"

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
	
	void GetBevConfig(BEV_CONFIG_T* pConfig);
	void SetBevConfig(BEV_CONFIG_T pConfig);
	void GetCarTransparentStatus(unsigned char& pCarTranspStatus);
	void SetCarTransparentStatus(unsigned char pCarTranspStatus);


	void Get3dViewRegion(Region** pRegion);
	void GetStitchViewRegion(Region** pRegion);
	void GetSingleViewRegion(Region** pRegion);
	void GetObjectViewRegion(Region** pRegion);	
	void GetLinearViewRegion(Region** pRegion);
	void GetObjectViewCameraParams(SurroundViewCameraParamsT** pCameraParams);
	void GetStitchViewCameraParams(SurroundViewCameraParamsT** pCameraParams);
	void GetSingleViewCameraParams(SurroundViewCameraParamsT** pCameraParams);
	void Get3dViewCameraParams(SurroundViewCameraParamsT** pCameraParams);
	void GetLinearViewCameraParams(SurroundViewCameraParamsT** pCameraParams);

	void Set3dViewRegion(Region* pRegion);
	void SetStitchViewRegion(Region* pRegion);
	void SetSingleViewRegion(Region* pRegion);
	void SetObjectViewRegion(Region* pRegion);	
	void SetLinearViewRegion(Region* pRegion);
	void GetLeftRightViewRegion(Region** pLeftRightViewReg, unsigned char viewIndex);
	void SetLeftRightViewRegion(Region* pLeftRightViewReg, unsigned char viewIndex);

	void SetObjectViewCameraParams(SurroundViewCameraParamsT* pCameraParams);
	void SetStitchViewCameraParams(SurroundViewCameraParamsT* pCameraParams);
	void SetSingleViewCameraParams(SurroundViewCameraParamsT* pCameraParams);
	void Set3dViewCameraParams(SurroundViewCameraParamsT* pCameraParams);
	void SetLinearViewCameraParams(SurroundViewCameraParamsT* pCameraParams);

	void SetAnimationManager(class IAnimationManager* pAm);
	void GetAnimationManager(class IAnimationManager** pAm);
	void GetSv2dData(class GlSV2D** pGlSv2d);
	void SetSv2dData(class GlSV2D* pGlSv2d);
	void SetStitchViewNodeStatus(unsigned char pStatus);
	void GetStitchViewNodeStatus(unsigned char& pStatus);
	void Set3dViewNodeStatus(unsigned char pStatus);
	void Get3dViewNodeStatus(unsigned char& pStatus);
	void SetSingleViewNodeStatus(unsigned char pStatus);
	void GetSingleViewNodeStatus(unsigned char& pStatus);
	void SetObjectViewNodeStatus(unsigned char pStatus);
	void GetObjectViewNodeStatus(unsigned char& pStatus);

	void Set3dViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void Get3dViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void Set180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void Get180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);


	void SetDisplayViewCmd(unsigned char pCmd);
	void GetDisplayViewCmd(unsigned char& pCmd);

	void SetSingleViewChannel(unsigned char pChannelId);
	void GetSingleViewChannel(unsigned char& pChannelId);

	void Set3dViewIndex(unsigned char pIndex);
	void Get3dViewIndex(unsigned char& pIndex);
	void SetSingleViewNode(class ISceneNode* pSingleViewNode);
	void GetSingleViewNode(class ISceneNode** pSingleViewNode);
	void SetStitchViewNode(class ISceneNode* pStitchViewNode);
	void GetStitchViewNode(class ISceneNode** pStitchViewNode);
	void Set3dViewNode(class ISceneNode* p3dViewNode);
	void Get3dViewNode(class ISceneNode** p3dViewNode);
	void SetObjectViewNode(class ISceneNode* pObjViewNode);
	void GetObjectViewNode(class ISceneNode** pObjViewNode);

	void SetSingleViewMesh(class IMesh* pSingleViewMesh[]);
	void GetSingleViewMesh(class IMesh* pSingleViewMesh[]);

	void SetSingleViewVertex(float* pSingleViewVertex[]);
	void GetSingleViewVertex(float* pSingleViewVertex[]);

	void SetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[]);
	void GetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[]);

	void SetSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex);
	void GetSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex);
	void SetLargeSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex);
	void GetLargeSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex);

	void GetTimeStitcherNode(class SVNode2DStich**	pTimeStitchNode);
	void SetTimeStitcherNode(class SVNode2DStich*	pTimeStitchNode);
	
	void GetApaOverlayResult(APAOverlayStruct* pAPAReslt);
	void SetApaOverlayResult(APAOverlayStruct pAPAReslt);

	
	void SetStitchAngle(unsigned char pSeamChangedFlag, unsigned char* pSeamChangeFlag,GLfloat* pVertex);
	void GetStitchAngle(unsigned char& pSeamChangedFlag, unsigned char** pSeamChangeFlag,GLfloat** pVertex);

	void Set2DParam(unsigned char pUpdateFlag, GLfloat *pData,GLushort *pIndex);
	void Set3DParam(unsigned char pUpdateFlag, float *pos);

	void Get2DParam(unsigned char& pUpdateFlag, GLfloat **pData,GLushort **pIndex);
	void Get3DParam(unsigned char& pUpdateFlag, float **pos);
	
	void Calc3DGroundPos(float *pPose,float *pWidth,float*pHeight);

	void cvtWorldPoint2Stich2DPoint(float *out_stich_Coord,float *in_world_coord,unsigned char unitmm=0);
	
	void cvtWorldPoint2ModelPoint3D(float *out_Model_Coord,float *in_world_coord);
	
	void cvtSingleViewImagePoint2GpuPoint(float *out_gpu_Coord,float *in_image_coord,bool rear_single_view);
		DataExPosParam *m_exParam;
		AVMCameraInternal *m_camInstrinct;
		AVMLuminanceData *m_lumin_para;
		AVM2DLUT *m_2D_lut;
		AVMUSCData *m_usc_data;
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
    
	Region m_singleViewRegion;
	Region m_3dViewRegion;
	Region m_stitchViewRegion;
	Region m_objectViewRegion;
	Region m_fadeRegion;
	Region m_linearViewRegion;
	Region m_leftViewRegion;
	Region m_rightViewRegion;

	SurroundViewCameraParamsT m_stitchViewCameraParams;
	SurroundViewCameraParamsT m_objectViewCameraParams;
	SurroundViewCameraParamsT m_3dViewCameraParams;
	SurroundViewCameraParamsT m_singleViewCameraParams;	
	SurroundViewCameraParamsT m_linearViewCameraParams;

	class GlSV2D* m_sv2dData;
	class IAnimationManager* m_am;
	class ISceneNode* m_singleViewNode;
	class ISceneNode* m_3dViewNode;
	class ISceneNode* m_objectViewNode;
	class IMesh*	  m_singleViewMesh[4];
	class INode*	  m_singleViewPlaneNode[4];
	float*			  m_singleViewVertex[4];
	float*			  m_singleViewRoi[4];
	float*			  m_largeSingleViewRoi[4];

	APAOverlayStruct       m_apaReslt;

	unsigned char m_avm3dVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmSingleViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmStitchViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmObjViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avm180DegreeViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmLeftRightViewVisibility[PROCESS_FUNC_NUMS];
	
	unsigned char m_stitchViewNodeStatus;
	unsigned char m_singleViewNodeStatus;
	unsigned char m_avm3dViewNodeStatus;
	unsigned char m_objViewNodeStatus;

	unsigned char m_displayViewCmd;
	unsigned char m_singleViewChannel;
	unsigned char m_avm3dViewIndex;

	unsigned char m_carTranspStatus;
	class ISceneNode* m_stitchViewNode;

	BEV_CONFIG_T		   m_bevConfig;

	class SVNode2DStich*	m_timeStitchNode;
	unsigned char*			m_seamUpdateFlag;
	GLfloat*				m_seamUpdateData;
	unsigned char 			m_seamDataChangeFlag;

	unsigned char 			m_2dParamUpdateFlag;
	GLfloat*				m_2dParamData;
	GLushort*				m_2dParamIndex;

	unsigned char			m_3dParamUpdateFlag;
	float*					m_3dParamPos;
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
