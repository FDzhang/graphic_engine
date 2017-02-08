
#include "GlSVRadarAlarm.h"
#include <math.h>
#include "DataStruct.h"


/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/








/****************************************

----------referenced functions-------------------


*************************************************/
#define FIRST_ZONE_FRONT_FRONT_2_VEHICLE -500.0
#define FIRST_ZONE_LEFT_FRONT_2_VEHICLE_CENTER -1100.0
#define SECOND_ZONE_FRONT_FRONT_2_VEHICLE 100.0
#define SECOND_ZONE_LEFT_FRONT_2_VEHICLE_CENTER -560.0
#define THIRD_ZONE_FRONT_FRONT_2_VEHICLE 200.0
#define THIRD_ZONE_LEFT_FRONT_2_VEHICLE_CENTER 0
#define FOURTH_ZONE_FRONT_FRONT_2_VEHICLE 100.0
#define FOURTH_ZONE_LEFT_FRONT_2_VEHICLE_CENTER 560.0
#define FIFTH_ZONE_FRONT_FRONT_2_VEHICLE -500.0
#define FIFTH_ZONE_LEFT_FRONT_2_VEHICLE_CENTER 1100.0


#define FIRST_RADAR_POS_X   -660 
#define FIRST_RADAR_POS_Y   -200
#define FIRST_RADAR_START_ANGLE 180.0
#define FIRST_RADAR_END_ANGLE 50.0
#define SECOND_RADAR_POS_X   -260 
#define SECOND_RADAR_POS_Y   0
#define SECOND_RADAR_START_ANGLE 135.0
#define SECOND_RADAR_END_ANGLE 45.0


#define CENTER_POS_X 0
#define CENTER_POS_Y_REAR -3767
#define RADAR_LINE_LEFT  160
#define RADAR_ANGLE_STEP  35

#define RADIUS_2D_STEP  150
#ifdef CHANGAN_HMI
#define RADIUS_FRONT_FIRST 3800
#define RADIUS_REAR_FIRST 1300
#define CENTER_POS_Y -3000

#define RADIUS_STEP       300

#else
#define RADIUS_FRONT_FIRST 1300
#define RADIUS_REAR_FIRST 1300
#define CENTER_POS_Y -900

#define RADIUS_STEP       300
#endif

/************************************************

---------functions---------------

/************************************************/
//SEA coordinate 
float gf_Radar_Zone_Corrd[]=
{ FIRST_ZONE_FRONT_FRONT_2_VEHICLE,FIRST_ZONE_FRONT_FRONT_2_VEHICLE,SECOND_ZONE_FRONT_FRONT_2_VEHICLE,SECOND_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,
  SECOND_ZONE_FRONT_FRONT_2_VEHICLE,SECOND_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,THIRD_ZONE_FRONT_FRONT_2_VEHICLE,THIRD_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,
  THIRD_ZONE_FRONT_FRONT_2_VEHICLE,THIRD_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,FOURTH_ZONE_FRONT_FRONT_2_VEHICLE,FOURTH_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,
  FOURTH_ZONE_FRONT_FRONT_2_VEHICLE,FOURTH_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,FIFTH_ZONE_FRONT_FRONT_2_VEHICLE,FIFTH_ZONE_LEFT_FRONT_2_VEHICLE_CENTER,
};


#if 0
float gf_Radar_Zone_ARC[]=
{
	FIRST_RADAR_POS_X,FIRST_RADAR_POS_Y,FIRST_RADAR_START_ANGLE,FIRST_RADAR_END_ANGLE,
	SECOND_RADAR_POS_X,SECOND_RADAR_POS_Y,SECOND_RADAR_START_ANGLE,SECOND_RADAR_END_ANGLE,
	-SECOND_RADAR_POS_X,SECOND_RADAR_POS_Y,SECOND_RADAR_START_ANGLE,SECOND_RADAR_END_ANGLE,
 	-FIRST_RADAR_POS_X,FIRST_RADAR_POS_Y,180-FIRST_RADAR_END_ANGLE,180-FIRST_RADAR_START_ANGLE,
   

};
float gf_radar_dist_level[]={500,700,900,1100};

#endif
#if 0
float gf_Radar_Zone_ARC[]=
{
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP,
 	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP,RADAR_LINE_LEFT-4*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y_REAR,-RADAR_LINE_LEFT,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-4*RADAR_ANGLE_STEP),
   

};
#endif
#ifdef CHANGAN_HMI
float gf_Radar_Zone_ARC[]=
{
 	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP-35,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-4*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-RADAR_LINE_LEFT,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),
   

};



#else
float gf_Radar_Zone_ARC[]=
{
 	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP,RADAR_LINE_LEFT-4*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y,RADAR_LINE_LEFT,RADAR_LINE_LEFT-RADAR_ANGLE_STEP,
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-4*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-3*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),-(RADAR_LINE_LEFT-2*RADAR_ANGLE_STEP),
	CENTER_POS_X,CENTER_POS_Y_REAR,-RADAR_LINE_LEFT,-(RADAR_LINE_LEFT-RADAR_ANGLE_STEP),
   

};
#endif

float gf_radar_dist_level[]={RADIUS_FRONT_FIRST,RADIUS_FRONT_FIRST+RADIUS_STEP,RADIUS_FRONT_FIRST+2*RADIUS_STEP,RADIUS_FRONT_FIRST+3*RADIUS_STEP,
	                         RADIUS_REAR_FIRST,RADIUS_REAR_FIRST+RADIUS_STEP,RADIUS_REAR_FIRST+2*RADIUS_STEP,RADIUS_REAR_FIRST+3*RADIUS_STEP};





GlSVRadarAlarm::GlSVRadarAlarm()
{

	
}

int GlSVRadarAlarm::InitPrivate(RADAR_ALARM_CONFIG pConfig,unsigned char zone,unsigned char dist_level)
{
    m_config_private = pConfig;
	m_zone = zone;
	m_DistLevel = dist_level;
	return 0;
}


int GlSVRadarAlarm::Update(unsigned char zone,unsigned char dist_level)
{
    float worldcoord[2];
	float worldcoord2[2];
	float worldcoord3[2];
	float worldcoord4[2];
    if(zone == m_zone)//&&(dist_level == m_DistLevel))
    {
        if(dist_level != 0)
        {
            m_DistLevel = dist_level-1;
			if((m_calib_mode == calib_3D)||(m_calib_mode == calib_2D_SINGLE))
           {
                CaculateWorldCoordinate(worldcoord,worldcoord2);
        
            	GenerateArcPlane(worldcoord,worldcoord2,(float *)m_pdata);
            }
			else
			{
			    CaculateWorldCoordinate2DRadar(worldcoord,worldcoord2,worldcoord3,worldcoord4);
			    GenerateArcPlane2D(worldcoord,worldcoord2,worldcoord3,worldcoord4,(float *)m_pdata);
			}
            return 1;
        }
		else
		{
		    return 0;
		}
    }
	else
	{
	    return 0;
	}
}

void GlSVRadarAlarm::CaculateWorldCoordinate(float *coord_first, float *coord_sec)
{
    float offset_y=0;
#if 0

	coord_first[0] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4]+m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	coord_first[1] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+1]+m_config.vehicle_width/2.0;

	coord_sec[0] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+2]+m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	coord_sec[1] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+3]+m_config.vehicle_width/2.0;
#endif
    offset_y=m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)],gf_Radar_Zone_ARC[4*m_zone+2],coord_first);
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)],gf_Radar_Zone_ARC[4*m_zone+3],coord_sec);

    //real world to image coordinate. use gpu internal process method.
      
}
void GlSVRadarAlarm::CaculateWorldCoordinate2DRadar(float *coord_first, float *coord_sec,float *coord_third,float *coord_fourth)
{
    float offset_y=0;
#if 0

	coord_first[0] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4]+m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	coord_first[1] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+1]+m_config.vehicle_width/2.0;

	coord_sec[0] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+2]+m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	coord_sec[1] = gf_Radar_Zone_Corrd[(4*m_zone+m_DistLevel)*4+3]+m_config.vehicle_width/2.0;
#endif
    offset_y=m_config.vehicle_axis_length+m_config.vehicle_front_wheel2bumper_length;
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)],gf_Radar_Zone_ARC[4*m_zone+2],coord_first);
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)],gf_Radar_Zone_ARC[4*m_zone+3],coord_sec);
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)]+RADIUS_2D_STEP,gf_Radar_Zone_ARC[4*m_zone+2],coord_third);
	CaculatePointFromAngle(gf_Radar_Zone_ARC[4*m_zone],gf_Radar_Zone_ARC[4*m_zone+1]+offset_y,gf_radar_dist_level[m_DistLevel+4*(m_zone/4)]+RADIUS_2D_STEP,gf_Radar_Zone_ARC[4*m_zone+3],coord_fourth);

    //real world to image coordinate. use gpu internal process method.
      
}

void GlSVRadarAlarm::CaculatePointFromAngle(float centerx, float centery,float radius,float start_angle,float *CoordOutput)
{
    float rad;
	rad = start_angle*3.1415926/180.0;
    CoordOutput[0]=centerx+radius*cos(rad);
    CoordOutput[1]=centery+radius*sin(rad);

	
    //real world to image coordinate. use gpu internal process method.
      
}

void GlSVRadarAlarm::GenerateArcPlane(float *coord_first, float *coord_sec,float *pVertex)
{

	float Anglestart[2];
	float AngleEnd;
	float xLeft;
	float yLeft;
	float xRight;
	float yRight;
	float xNormal;
	float yNormal;
	float zNormal;
	float temp =0.0;
	float step;
	float tempx;
	float tempy;
	unsigned int Loop;
	unsigned int index=0,slotid=0;;
	float flastx=0,flasty=0; 
	float totalangle;
	
	float world_coord[2];
	float model_coord[2];
	//number = (unsigned int)(length/0.1);

	float *pCoord[2];
	float output[3];
	float tempCam[3];
	pCoord[0]=coord_first;
	pCoord[1]=coord_sec;

     tempCam[0] = 0.0;
	 tempCam[1] = 0.0;
	 tempCam[2] = -100.0;
    if(m_zone<4)
    {
        m_cam_pos =front_camera_index;
    }
	else
	{
        m_cam_pos = rear_camera_index;
    }
	
	    for(Loop = 0;Loop <4;Loop++)
    	{
            index = Loop%2;

            world_coord[0]=*(pCoord[index]);
			world_coord[1]=*(pCoord[index]+1);
    	    Cal_World_2_Model_Coordinate(model_coord,world_coord);


			if(m_calib_mode == calib_2D_STICH)
			{
    			pVertex[slotid+0]= model_coord[0]+(Loop/2)*0.1;
    			pVertex[slotid+1]= model_coord[1]+(Loop/2)*0.1;			
    			pVertex[slotid+2] =0.0 ;				
			}
			else if(m_calib_mode == calib_3D)
			{
    			pVertex[slotid+0]= model_coord[0];
    			pVertex[slotid+1]=  m_config.m_model_bottom+(Loop/2)*(m_config_private.obstacle_height);			
    			pVertex[slotid+2] = model_coord[1];	
				#if 0
				ConvertGroundToClinder(&pVertex[slotid],output,SKY_CLINDER_RADIUS,2,0);
    			pVertex[slotid+0]= output[0];
    			pVertex[slotid+1]=  output[1];			
    			pVertex[slotid+2] = output[2];	
				#endif				
			}
			else
			{
			 
    			pVertex[slotid+0]= model_coord[0];
    			pVertex[slotid+1]=  m_config.m_model_bottom+(Loop/2)*(m_config_private.obstacle_height);			
    			pVertex[slotid+2] = model_coord[1];	
				Cal_World_2_Model_Coordinate_3d(output,&pVertex[slotid]); 
				
				//ConvertGroundToClinder(&pVertex[slotid],output,SKY_CLINDER_RADIUS,2,0);
    			pVertex[slotid+0]= output[0];
    			pVertex[slotid+1]=  output[1];			
    			pVertex[slotid+2] = output[1];			
			}
			
			slotid+=8;
    
    	}
	


}
void GlSVRadarAlarm::GenerateArcPlane2D(float *coord_first, float *coord_sec,float *coord_third,float *coord_fourth,float *pVertex)
{

	float Anglestart[2];
	float AngleEnd;
	float xLeft;
	float yLeft;
	float xRight;
	float yRight;
	float xNormal;
	float yNormal;
	float zNormal;
	float temp =0.0;
	float step;
	float tempx;
	float tempy;
	unsigned int Loop;
	unsigned int index=0,slotid=0;;
	float flastx=0,flasty=0; 
	float totalangle;
	
	float world_coord[2];
	float model_coord[2];
	//number = (unsigned int)(length/0.1);

	float *pCoord[4];
	pCoord[0]=coord_first;
	pCoord[1]=coord_sec;
	pCoord[2]=coord_third;
	pCoord[3]=coord_fourth;


    
    	for(Loop = 0;Loop <4;Loop++)
    	{
            index = Loop%2;

            world_coord[0]=*(pCoord[Loop]);
			world_coord[1]=*(pCoord[Loop]+1);
    	    Cal_World_2_Model_Coordinate(model_coord,world_coord);


    			pVertex[slotid+0]= model_coord[0];
    			pVertex[slotid+1]= model_coord[1];			
    			pVertex[slotid+2] =0.0 ;				
			
    		
			slotid+=8;
    
    	}
	


}



