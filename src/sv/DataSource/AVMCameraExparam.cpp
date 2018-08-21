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
#include "../AVMData.h"
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
 void DataExPosParam::Cvt_Angles_To_Rotation(float R[9], const float angles[3])
 {
	 float cx = cos(angles[0]), cy = cos(angles[1]), cz = cos(angles[2]);
	 float sx = sin(angles[0]), sy = sin(angles[1]), sz = sin(angles[2]);
	 R[0] = cy*cz;	 R[1] = -cx*sz+sx*sy*cz; R[2] = sx*sz+cx*sy*cz;
	 R[3] = cy*sz;	 R[4] = cx*cz+sx*sy*sz;  R[5] = -sx*cz+cx*sy*sz;
	 R[6] = -sy;	 R[7] = sx*cy;			 R[8] = cx*cy;
 }

/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

DataExPosParam::DataExPosParam(float space_y_min,float space_scale)
{
    m_space_scale = space_scale;
	m_space_y_min = space_y_min;

}

/*Init from pose file ,file sotre camera pose index as front right rear left*/	
void DataExPosParam::Init(char *filename,float vehicle_length,float vehicle_rear_wheel_to_bumper,char *filenameAdjust)
{
	float input[24];
	int i,j,k =0;
	m_offsetIner2Global  = XRVec4(0,m_space_scale*m_space_y_min,
		-(vehicle_length/2-vehicle_rear_wheel_to_bumper)*SCALE_3D_TO_2D_Y,0.0);
		m_scale[0]= SCALE_3D_TO_2D_X;
		m_scale[1]= SCALE_3D_TO_2D_Y;
		m_scale[2]= SCALE_3D_TO_2D_Z;

        

	ReadFloatSpaceTxtFile(filename,input,24);
	if(filenameAdjust == NULL)
	{
	    memset(m_adjust_exparam,0,24*sizeof(float));
	}
	else
	{	    
		ReadFloatSpaceTxtFile(filenameAdjust,m_adjust_exparam,24);
	}	
	ImprotCalibResultFromBuffer(input,m_pos_angle,m_pos_trans);
	InitModleTransformMatrix(m_ModelTransform);
	Calc3DAVMTransform(m_ModelTransform,m_pos_angle,m_pos_trans,m_offsetIner2Global,m_scale);	 


}

void DataExPosParam::Init(str_avm_pose_t *pPose,float vehicle_length,float vehicle_rear_wheel_to_bumper,char *filenameAdjust)
{

    int i,j,k =0;
    m_offsetIner2Global  =XRVec4(0,m_space_scale*m_space_y_min,
    	-(vehicle_length/2-vehicle_rear_wheel_to_bumper)*SCALE_3D_TO_2D_Y,0.0);
    	m_scale[0]= SCALE_3D_TO_2D_X;
    	m_scale[1]= SCALE_3D_TO_2D_Y;
    	m_scale[2]= SCALE_3D_TO_2D_Z;
    
    
    ImprotCalibResultFromConfigFile(pPose,m_pos_angle,m_pos_trans);
    
    if(filenameAdjust == NULL)
    {
    	memset(m_adjust_exparam,0,24*sizeof(float));
    }
    else
    {		
    	ReadFloatSpaceTxtFile(filenameAdjust,m_adjust_exparam,24);
    }	
    
    	
    InitModleTransformMatrix(m_ModelTransform);
    Calc3DAVMTransform(m_ModelTransform,m_pos_angle,m_pos_trans,m_offsetIner2Global,m_scale);	 


}
void DataExPosParam::Init(str_avm_pose_t *pPose,float vehicle_length,float vehicle_rear_wheel_to_bumper)
{

    int i,j,k =0;
    m_offsetIner2Global = XRVec4(0,m_space_scale*m_space_y_min,
    	-(vehicle_length/2-vehicle_rear_wheel_to_bumper)*SCALE_3D_TO_2D_Y,0.0);
    	m_scale[0]= SCALE_3D_TO_2D_X;
    	m_scale[1]= SCALE_3D_TO_2D_Y;
    	m_scale[2]= SCALE_3D_TO_2D_Z;
    
    if(pPose != NULL)
    {
        ImprotCalibResultFromConfigFile(pPose,m_pos_angle,m_pos_trans);
    }
      	
    InitModleTransformMatrix(m_ModelTransform);
    Calc3DAVMTransform(m_ModelTransform,m_pos_angle,m_pos_trans,m_offsetIner2Global,m_scale);	 


}

void DataExPosParam::GetCameraPos(float *pos,int camera_index)
{
    
    memcpy(pos,&(m_pos_trans[3*camera_index]),3*sizeof(float));

}
void DataExPosParam::GetCameraAngle(float *pos,int camera_index)
{
    
    memcpy(pos,&(m_pos_angle[3*camera_index]),3*sizeof(float));

}

void DataExPosParam::GetTransformMatrix(XRMat4 **matrix,int camera_index)
{
    
    *matrix=&(m_uvTransform[camera_index]);

}

void DataExPosParam::GetCameraPos(float *pos)
{
    memcpy(pos,m_pos_trans,12*sizeof(float));

}
void DataExPosParam::GetModelTransform(XRMat4 **pMatrix,int camera_index)
{
    *pMatrix=&(m_ModelTransform[camera_index]);
}

void DataExPosParam::GetInnerModelTransform(float **pTrans,int camera_index)
{
	*pTrans = &(m_trans_inner_model[3*camera_index]);
}

void DataExPosParam::InitModleTransformMatrix(XRMat4 *pModelTransform)
{
	int Index;
	for(Index = 0;Index<4;Index++)
	{
		switch(Index)
		{
			case front_camera_index:
			case right_camera_index:
				pModelTransform[Index] = XRMat4::RotationY(3.1415926*(0));
			break;
			case rear_camera_index:
			case left_camera_index: 			
				pModelTransform[Index] = XRMat4::RotationY(3.1415926*(1));
			break;		
		}	
	}


}

void DataExPosParam::Calc3DAVMTransform(XRMat4 *modle,float *Rot, float *intrans,XRVec4 offset,float *scale)
{
	XRVec4 offsetIner2Global  =XRVec4(offset.x,offset.y, offset.z,0.0);
	
	//convert matrix from input2D coorinate system to 3D coordinate system
	XRMat4 InputCam2InnerCam= XRMat4(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0);
	//convert matrix from input2D coorinate system to 3D coordinate system		
	XRMat4 InnerGlobal2InputGlobal = XRMat4(0.0,1.0,0.0,0.0,0.0,0.0,-1.0,0.0,-1.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0);
	XRMat4 InnerR=	XRMat4::Scale(1.0, 1.0, 1.0);
	XRVec4 InnerT= XRVec4(0,0,0,0);
	XRMat4 ScaleInner2Global = XRMat4::Scale(1.0/scale[0],1.0/scale[1],1.0/scale[2]);

	int i;
	for (i=0; i<4; i++) 
	{
		m_uvTransform[i] = XRMat4::Scale(1.0, 1.0, 1.0);
		
		float r[9],a[3],trans[3];
		for(int j = 0; j < 3; j++)
		{
			a[j] = Rot[3*i+j];//*deg2rad;
			trans[j] = intrans[3*i+j];
		}
		
		Cvt_Angles_To_Rotation(r,a);	

		//step1: InnerR
		XRMat4 InputR = XRMat4(r[0],r[1],r[2],0.0,r[3],r[4],r[5],0.0,r[6],r[7],r[8],0,0.0,0.0,0.0,1.0);
		InnerR = InputCam2InnerCam*InputR*InnerGlobal2InputGlobal*ScaleInner2Global*(modle[i].inverse());
		
		//step2: InnerT
		InnerT = InnerR.inverse()*(InputCam2InnerCam*InputR*InnerGlobal2InputGlobal*ScaleInner2Global*offsetIner2Global-InputCam2InnerCam*InputR*XRVec4(trans[0], trans[1], trans[2], 0));
					
		 m_uvTransform[i] = InnerR;
		m_trans_inner_model[3*i] = InnerT.x;			 
		m_trans_inner_model[3*i+1] = InnerT.y;	
		m_trans_inner_model[3*i+2] = InnerT.z;	
		m_uvTransform[i] = XRMat4::RotationX(m_adjust_exparam[i*6])* m_uvTransform[i];
		m_uvTransform[i] = XRMat4::RotationY(m_adjust_exparam[i*6+1])* m_uvTransform[i];
		m_uvTransform[i] = XRMat4::RotationZ(m_adjust_exparam[i*6+2])* m_uvTransform[i];
		m_trans_inner_model[3*i] +=m_adjust_exparam[i*6+3];
		m_trans_inner_model[3*i+1] +=m_adjust_exparam[i*6+4];
		m_trans_inner_model[3*i+2] +=m_adjust_exparam[i*6+5];

    }


}
	
void DataExPosParam::UpdateExParamCalibRslt(float *pose)
{
	float PoseAngle[12],PoseTrans[12];
	ImprotCalibResultFromBuffer(pose,PoseAngle,PoseTrans);
	Calc3DAVMTransform(m_ModelTransform,PoseAngle,PoseTrans,m_offsetIner2Global,m_scale);
}


	//this function is for index changing 
int DataExPosParam::ConvertCameraIndex(int input2DIndex)
{
	int output3DIndex;
	switch(input2DIndex)
	{
		case 0:
			output3DIndex=front_camera_index;
		break;
		case 1:
			output3DIndex=right_camera_index;
		break;
		case 2:
			output3DIndex = rear_camera_index;
		break;
		case 3:
			output3DIndex=left_camera_index;
		break;		
	}
	return output3DIndex;

}
	
void DataExPosParam::ImprotCalibResultFromBuffer(float *inputpos, float *rot, float *trans)
{

  
	int i,j,k =0;

	for(j=0;j<4;j++)
	{
		k=ConvertCameraIndex(j);
		
		for(i=0;i<3;i++)
		{
			rot[k*3+i] = inputpos[j*6+i];
			trans[k*3+i] = inputpos[j*6+3+i];		
		}
		
	}

}
void DataExPosParam::ImprotCalibResultFromConfigFile(str_avm_pose_t *pPose, float *rot, float *trans)
{


	int i,j,k =0;



	for(j=0;j<3;j++)
	{
	
	    rot[3*front_camera_index+j]=pPose->_pose_front[j];
		trans[3*front_camera_index+j]=pPose->_pose_front[3+j];
	    rot[3*rear_camera_index+j]=pPose->_pose_rear[j];
		trans[3*rear_camera_index+j]=pPose->_pose_rear[3+j];
	    rot[3*left_camera_index+j]=pPose->_pose_left[j];
		trans[3*left_camera_index+j]=pPose->_pose_left[3+j];
	    rot[3*right_camera_index+j]=pPose->_pose_right[j];
		trans[3*right_camera_index+j]=pPose->_pose_right[3+j];

		
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

