#ifndef __AVM_CAN_DATA_H__
#define __AVM_CAN_DATA_H__
/*===========================================================================*\
 * FILE: AVMCANData.h
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
class AVMCANData
{
public:

    AVMCANData(){};
    ~AVMCANData();
    /*Init from pose file ,file sotre camera pose index as front right rear left*/	
    void Init( void);
    void UpdateCANData(CAN_DATA in_can_data);
	void Get_Vehicle_Speed(float * Vehicle_Speed);
	
	void Get_Left_Wheel_Speed(float * Vehicle_Speed);
	void Get_Right_Wheel_Speed(float * Vehicle_Speed);
	
	void Get_Door_State( unsigned char * Driver_Door_State, unsigned char * Passenger_Door_State,  unsigned char * Rear_Right_Door_State, unsigned char * Rear_Left_Door_State);
	
	void Get_Steer_Angle(float *Steer_Angle);
	void Get_Gear_State(unsigned char *Vehicle_Movement_State);
	void Get_Turn_Signal(unsigned char* Turn_Signal);
	
	void Get_PA_State(unsigned char pos,unsigned char Dist,unsigned char* objstate);

    void Get_Yaw_Rate(float *yaw_rate);
	
    void Get_Wheel_Pulse(unsigned short *pwheelpulse);
	
	float * Get_Sonar_dist_list(void);
	float Get_Drive_Dist(void);
	unsigned char Get_Eps_Status();
	unsigned char Get_Lcc_Enable();
	
	void CalcDriveDist(void);
	
	void ResetDriveDist(void);
	unsigned int GetTimeStamp(void);
	CAN_DATA GetCANData(void);

	CAN_DATA m_CAN_Data;
	float m_drive_distance;
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
