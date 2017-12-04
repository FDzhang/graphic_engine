#ifndef __AVM_CAMERA_EXPARAM_H__
#define __AVM_CAMERA_EXPARAM_H__

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
class DataExPosParam
{
public:
	
	DataExPosParam(float space_y_min,float space_scale);
	void Init(char *filename,float vehicle_length,float vehicle_rear_wheel_to_bumper,char *filenameAdjust=NULL);
	void GetCameraPos(float *pos,int camera_index);
	void GetCameraPos(float *pos);
	void GetCameraAngle(float *pos,int camera_index);
	void InitModleTransformMatrix(XRMat4 *pModelTransform);
	void Calc3DAVMTransform(XRMat4 *modle,float *Rot, float *intrans,XRVec4 offset,float *scale);
	int ConvertCameraIndex(int input2DIndex);
	void ImprotCalibResultFromBuffer(float *inputpos, float *rot, float *trans);
	void GetTransformMatrix(XRMat4 **matrix,int camera_index);
	void GetInnerModelTransform(float **pTrans,int camera_index);
	void GetModelTransform(XRMat4 **pMatrix,int camera_index);
	void UpdateExParamCalibRslt(float *pose);	
	
	void ImprotCalibResultFromConfigFile(str_avm_pose_t *pPose, float *rot, float *trans);
	void Init(str_avm_pose_t *pPose,float vehicle_length,float vehicle_rear_wheel_to_bumper,char *filenameAdjust);
private:
    void Cvt_Angles_To_Rotation(float R[9], const float angles[3]);	
	float m_pos_angle[12];
	float m_pos_trans[12];
	float m_scale[3];
	XRMat4		m_ModelTransform[4];
	XRVec4 m_offsetIner2Global;
	float m_trans_inner_model[12];
	
	XRMat4		m_uvTransform[4];
	
	float m_adjust_exparam[24];
	float m_space_y_min;
	float m_space_scale;
    unsigned char m_update_flag[4];

};
#if 0
class DataSingleViewCfg
{

public:
    GetSingleviewRatio(float *pos,int camera_index);
	GetViewMatrix();
	GetCameraAngle();
private:

};

class DataCameraInstrict
{

public:
    GetCameraConfig(float *pos,int camera_index);
	GetCameraInstrict();
	GetCameraLUT();
private:

};
#endif
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
