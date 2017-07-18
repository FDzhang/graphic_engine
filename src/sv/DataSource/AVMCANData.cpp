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
#include "AVMCANData.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/

extern unsigned int Get_Frame_TimeStamp(void);
/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/
void AVMCANData::Init( void)
{
	m_drive_distance=0;


}
void AVMCANData::UpdateCANData(CAN_DATA in_can_data)
{
    m_CAN_Data = in_can_data;
	
}
void AVMCANData::Get_Vehicle_Speed(float * Vehicle_Speed)
{
   * Vehicle_Speed = m_CAN_Data.vehicle_speed;
}

void AVMCANData::Get_Left_Wheel_Speed(float * Vehicle_Speed)
{
    *Vehicle_Speed =m_CAN_Data.left_wheel_speed;

}
void AVMCANData::Get_Right_Wheel_Speed(float * Vehicle_Speed)
{
    *Vehicle_Speed = m_CAN_Data.right_wheel_speed;
}

void AVMCANData::Get_Door_State( unsigned char * Driver_Door_State, unsigned char * Passenger_Door_State,  unsigned char * Rear_Right_Door_State, unsigned char * Rear_Left_Door_State)
{
    *Driver_Door_State = m_CAN_Data.door_state[front_left_door];
	*Passenger_Door_State = m_CAN_Data.door_state[front_right_door];
	*Rear_Left_Door_State = m_CAN_Data.door_state[rear_left_door];
	*Rear_Right_Door_State = m_CAN_Data.door_state[rear_right_door];

}
void AVMCANData::Get_Steer_Angle(float *Steer_Angle)
{
   *Steer_Angle = m_CAN_Data.steering_wheel_angle;

}
    void AVMCANData::Get_Yaw_Rate(float *yaw_rate)
	{
		*yaw_rate=m_CAN_Data.yaw_rate;
	}
void AVMCANData::Get_Gear_State(unsigned char *Vehicle_Movement_State)
{
    *Vehicle_Movement_State = m_CAN_Data.gear_state;

}
void AVMCANData::Get_Turn_Signal(unsigned char* Turn_Signal)
{
    *Turn_Signal = m_CAN_Data.turn_light_status;
}
void AVMCANData::Get_PA_State(unsigned char pos,unsigned char Dist,unsigned char* objstate)
{

    *objstate = m_CAN_Data.radar_alarm[2*pos+Dist];

}
	
float * AVMCANData::Get_Sonar_dist_list(void)
{

	return m_CAN_Data.radar_dist;

}
		
float AVMCANData::Get_Drive_Dist(void)
{
	return m_drive_distance;
}
void AVMCANData::CalcDriveDist(void)
{
   float speed = (m_CAN_Data.left_wheel_speed+m_CAN_Data.right_wheel_speed)/2.0;
   float delta_distance = speed/3600.0*Get_Frame_TimeStamp();
   if(GEAR_R == m_CAN_Data.gear_state)
   {
      m_drive_distance -= delta_distance;  
   }
   else
   {
      m_drive_distance += delta_distance;
   }
}
void AVMCANData::ResetDriveDist(void)
{
    m_drive_distance=0;
}

unsigned int AVMCANData::GetTimeStamp(void)
{
   return m_CAN_Data.frame_time;
}

void AVMCANData::Get_Wheel_Pulse(unsigned short *pwheelpulse)
{
    for(int i =0;i<4;i++)
    {
        pwheelpulse[i]=m_CAN_Data.wheel_pls[i];
    }

}
CAN_DATA AVMCANData::GetCANData(void)
{
   return m_CAN_Data;
}


/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

