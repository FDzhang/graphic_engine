#ifndef __GL_SV_OVERLAY_H__
#define __GL_SV_OVERLAY_H__

#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "GlSVOverlayBase.h"


typedef struct Dynamic_Overlay_Para_T
{

    float Vehicle_Min_Radius_Gear_R_Left_Turn_Rear_Axis_Cent;
	float Vehicle_Min_Radius_Gear_R_Right_Turn_Rear_Axis_Cent;
	float Vehicle_Min_Radius_Gear_D_Left_Turn_Rear_Axis_Cent;
	float Vehicle_Min_Radius_Gear_D_Right_Turn_Rear_Axis_Cent;
    float Vehicle_Max_Deg_Steering_Wheel_Left_Turn;
	float Vehicle_Max_Deg_Steering_Wheel_Right_Turn;
	

	float overlay_length;

	
}Dynamic_Overlay_Para;

#define OLY_DIR_FOWARD  0
#define OLY_DIR_BACKWARD 1
#define OLY_SINGLE_BACKWARD 2
#define OLY_VERTICAL_PARKING 3
#define OLY_PARRAEL_PARKING 4

#define MY_PI 3.1415926




class GlSVOverlay:public GlSVOverlayBase
{
public:
	GlSVOverlay();

	int InitPrivate(Dynamic_Overlay_Para pConfig);
	
	int Update(float steeringwheel,int drive_indicate);
    void CaculateCenter(float *centerX, float *centerY,float radius[],float *theta,float fSteeringwheel,int Direct);
	void GenerateArcPlane(float centerX, float centerY,float radius[],float length,float startangle[],	unsigned int number,int element_perpixel,float*pVertex);
	void Cal_Steeringwheel_2_Radius(float *radius,float steerAngle,int gear_state);

private:


	
	


    Dynamic_Overlay_Para m_config_private;
	//void *m_pdata;
	//unsigned int m_data_size;
    //unsigned int m_element_num;
	//unsigned char m_calib_mode;


};

#endif //#ifndef __GL_SV_DEMO_H__
