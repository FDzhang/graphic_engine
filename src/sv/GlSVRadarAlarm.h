#ifndef __GL_SV_RADARALARM_H__
#define __GL_SV_RADARALARM_H__

#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "GlSVOverlayBase.h"

//#define CHANGAN_HMI


typedef struct RADAR_ALARM_CONFIG_T
{

	float vehicle_radar_2_front_bumper;

	float obstacle_height;

	
	
}RADAR_ALARM_CONFIG;

#if 0
typedef struct RADAR_ALARM_CONFIG_T
{
    float vehicle_length;
	float vehicle_width;
	float vehicle_axis_length;
	float vehicle_front_wheel2bumper_length;
	float vehicle_rear_wheel2bumper_length;
	float vehicle_radar_2_front_bumper;
	float m_model_bottom;
	unsigned char dynamic_overlay_point_num;
	float model_scale;
	float obstacle_height;
	float m_calib_center_x;   //x means imaage x direction
	float m_calib_center_y;
	float m_calib_mmpp_x;
	float m_calib_mmpp_y;
	
	
}RADAR_ALARM_CONFIG;
#endif

typedef struct RADAR_ALARM_STRUCT_T
{
    unsigned char ZoneNum;  // 0---3 means front,4---7 means rear
	unsigned char DistLevel;
	float ObstacleHeight;
    float WorldCoordinate[4]; //obstacle coordinate 2 points

}RADAR_ALARM_STRUCT;




class GlSVRadarAlarm :public GlSVOverlayBase
{
public:
	GlSVRadarAlarm();

	int InitPrivate(RADAR_ALARM_CONFIG pConfig,unsigned char zone,unsigned char dist_level);
	
	int Update(unsigned char zone,unsigned char dist_level);
	void CaculateWorldCoordinate(float *coord_first, float *coord_sec);
	void GenerateArcPlane(float *coord_first, float *coord_sec,float *pVertex);

	void CaculatePointFromAngle(float centerx, float centery,float radius,float start_angle,float *CoordOutput);
    void CaculateWorldCoordinate2DRadar(float *coord_first, float *coord_sec,float *coord_third,float *coord_fourth);
	void GenerateArcPlane2D(float *coord_first, float *coord_sec,float *coord_third,float *coord_fourth,float *pVertex);

private:


	



	
	


    RADAR_ALARM_CONFIG m_config_private;

	unsigned char m_zone;
	unsigned char m_DistLevel;


};

#endif //#ifndef __GL_SV_DEMO_H__
