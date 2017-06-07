/* -*- C++ -*-


   $Id: bev_config.cpp,v 1.2 2015/08/31 13:37:02 cvsroot Exp $

   Copyright 2003 by Delphi Corporation. All Rights Reserved.
   This file contains Delphi Delco Electonics Proprietary information.
   It may not be reproduced or distributed without permission.
   Contact:   
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>   // for toupper
#include <assert.h>


#include "bev_config.h"
#include "iv_options.h"


//#define BEV_OPT_INT32( NAME, ADDRESS ) { #NAME, MoosOptInt, &load_config_data.NAME }
#define BEV_OPT_INT32(NAME,ADDRESS) { #NAME, MoosOptInt, ADDRESS.NAME }
#define BEV_OPT_FLOAT( NAME, ADDRESS ) { #NAME, MoosOptFloat, ADDRESS.NAME }
#define BEV_OPT_BOOL( NAME, ADDRESS ) { #NAME, MoosOptBool, ADDRESS.NAME }
#define BEV_OPT_STRING( NAME, ADDRESS ,LEGNTH) { #NAME, MoosOptStr, ADDRESS.NAME,LEGNTH }

#define BEV_OPT_END { NULL, MoosOptEnd }

 
BEV_CONFIG_T load_config_data;




static Options smc_list[] = 
{
	
	BEV_OPT_INT32( SMC_MAJOR_VERSION , &load_config_data.smc ),
    
	BEV_OPT_INT32( SMC_MINOR_VERSION, &load_config_data.smc ),

	// camera distortion model
	// 
	BEV_OPT_INT32( DISTORTION_MODEL , &load_config_data.smc ),
	
	// front camera parameter
	
	BEV_OPT_FLOAT( FRONT_CAMERA_SENSOR_WIDTH , &load_config_data.smc ),	
	BEV_OPT_FLOAT( FRONT_CAMERA_SENSOR_HEIGHT , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( FRONT_CAMERA_SENSOR_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_SENSOR_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_SKEW_C , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_SKEW_D , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_H_FOV , &load_config_data.smc ),	
	BEV_OPT_FLOAT( FRONT_CAMERA_V_FOV , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( FRONT_CAMERA_IMAGE_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_IMAGE_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_SKEW_E , &load_config_data.smc ),
	BEV_OPT_FLOAT( FRONT_CAMERA_IMAGE_TOP_CUT , &load_config_data.smc ),	
	

	BEV_OPT_STRING( FRONT_CAMERA_LUT_FILE_NAME , &load_config_data.smc,MAX_NAME_LENGTH ),

	// rear camera parameter
	
	BEV_OPT_FLOAT( REAR_CAMERA_SENSOR_WIDTH , &load_config_data.smc ),	
	BEV_OPT_FLOAT( REAR_CAMERA_SENSOR_HEIGHT , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( REAR_CAMERA_SENSOR_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_SENSOR_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_SKEW_C , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_SKEW_D , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_H_FOV , &load_config_data.smc ),	
	BEV_OPT_FLOAT( REAR_CAMERA_V_FOV , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( REAR_CAMERA_IMAGE_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_IMAGE_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_SKEW_E , &load_config_data.smc ),
	BEV_OPT_FLOAT( REAR_CAMERA_IMAGE_TOP_CUT , &load_config_data.smc ),	
	
	BEV_OPT_STRING( REAR_CAMERA_LUT_FILE_NAME , &load_config_data.smc,MAX_NAME_LENGTH ),


	// left camera parameter
	
	BEV_OPT_FLOAT( LEFT_CAMERA_SENSOR_WIDTH , &load_config_data.smc ),	
	BEV_OPT_FLOAT( LEFT_CAMERA_SENSOR_HEIGHT , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( LEFT_CAMERA_SENSOR_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_SENSOR_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_SKEW_C , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_SKEW_D , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_H_FOV , &load_config_data.smc ),	
	BEV_OPT_FLOAT( LEFT_CAMERA_V_FOV , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( LEFT_CAMERA_IMAGE_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_IMAGE_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_SKEW_E , &load_config_data.smc ),
	BEV_OPT_FLOAT( LEFT_CAMERA_IMAGE_TOP_CUT , &load_config_data.smc ),	
	
	//BEV_OPT_INT32( LEFT_CAMERA_LUT_FILE_NAME , &load_config_data.smc. ),	
	BEV_OPT_STRING( LEFT_CAMERA_LUT_FILE_NAME , &load_config_data.smc,MAX_NAME_LENGTH ),

	// right camera parameter
	BEV_OPT_FLOAT( RIGHT_CAMERA_SENSOR_WIDTH , &load_config_data.smc ),	
	BEV_OPT_FLOAT( RIGHT_CAMERA_SENSOR_HEIGHT , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( RIGHT_CAMERA_SENSOR_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_SENSOR_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_SKEW_C , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_SKEW_D , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_H_FOV , &load_config_data.smc ),	
	BEV_OPT_FLOAT( RIGHT_CAMERA_V_FOV , &load_config_data.smc ),		 
	BEV_OPT_FLOAT( RIGHT_CAMERA_IMAGE_CENTER_X , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_IMAGE_CENTER_Y , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_SKEW_E , &load_config_data.smc ),
	BEV_OPT_FLOAT( RIGHT_CAMERA_IMAGE_TOP_CUT , &load_config_data.smc ),	
	
	//BEV_OPT_INT32( RIGHT_CAMERA_LUT_FILE_NAME , &load_config_data.smc. ),	
    BEV_OPT_STRING( RIGHT_CAMERA_LUT_FILE_NAME , &load_config_data.smc,MAX_NAME_LENGTH ),

			   

	BEV_OPT_END
};

static Options smc_hmi_list[] = 
{
	
	BEV_OPT_INT32( SMC_MAJOR_VERSION , &load_config_data.smc_hmi ),
	BEV_OPT_INT32( SMC_MINOR_VERSION , &load_config_data.smc_hmi ),


	BEV_OPT_FLOAT( SPACE_MODEL_SCALE_SIZE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( SPACE_MODEL_Y_MIN , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( VEHICLE_LENGTH , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( VEHICLE_REARWHEEL_TO_REAR_BUMPER , &load_config_data.smc_hmi ),


	// VEHICLE model position and size
	// 
	BEV_OPT_FLOAT( CAR_MODEL_POSITION_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( CAR_MODEL_POSITION_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( CAR_MODEL_POSITION_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( CAR_MODEL_SCALE_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( CAR_MODEL_SCALE_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( CAR_MODEL_SCALE_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( WHEEL_MODEL_SCALE , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( WHEEL_MODEL_OFFSET_FRONT , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( WHEEL_MODEL_OFFSET_REAR , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( WHEEL_MODEL_OFFSET_WIDTH , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( WHEEL_MODEL_OFFSET_UP , &load_config_data.smc_hmi ),

			 

	//ground model position and size
	BEV_OPT_FLOAT( GROUND_MODEL_WIDTH , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( GROUND_MODEL_HEIGHT , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( GROUND_MODEL_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( GROUND_MODEL_POS_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( GROUND_MODEL_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_INT32( GROUND_MODEL_ENABLE , &load_config_data.smc_hmi),


	//ui layout
	BEV_OPT_FLOAT( LEFT_PANEL_POSITION_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( LEFT_PANEL_POSITION_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( LEFT_PANEL_WIDTH , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( LEFT_PANEL_HEIGHT , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( BOTTOM_PANEL_POSITION_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( BOTTOM_PANEL_POSITION_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( BOTTOM_PANEL_WIDTH , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( BOTTOM_PANEL_HEIGHT , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( RIGHT_PANEL_POSITION_X , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( RIGHT_PANEL_POSITION_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( RIGHT_PANEL_WIDTH , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( RIGHT_PANEL_HEIGHT , &load_config_data.smc_hmi ),
		//sonar position
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_POS_X , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_POS_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_ANGLE , &load_config_data.smc_hmi ),	
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_POS_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_POS_X , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_POS_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_POS_X , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_POS_Y , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_POS_X , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_ANGLE , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_POS_X , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_POS_Y , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_POS_Z , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_ANGLE , &load_config_data.smc_hmi ),




	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_CONOR_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_LEFT_MIDDLE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_LEFT_SIDE_SONAR_COLOR_B , &load_config_data.smc_hmi),

	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_MIDDLE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_CONOR_SONAR_COLOR_B , &load_config_data.smc_hmi ),

	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( REAR_RIGHT_SIDE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_LEFT_SIDE_SONAR_COLOR_B , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_CONOR_SONAR_COLOR_B , &load_config_data.smc_hmi ),

	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_LEFT_MIDDLE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_MIDDLE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_COLOR_G , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_CONOR_SONAR_COLOR_B , &load_config_data.smc_hmi),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_COLOR_R , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_COLOR_G , &load_config_data.smc_hmi ),
	BEV_OPT_FLOAT( FRONT_RIGHT_SIDE_SONAR_COLOR_B , &load_config_data.smc_hmi ),
	BEV_OPT_END
};


int bev_Load_Configure( BEV_CONFIG_T * pData, char* SMC, char* AMC, char* USC )
{
	int ret = -1;
	int smc_list_count;
	int amc_list_count;
	int smc_hmi_list_count;
	int usc_list_count;
	int count;

	initOptions();

	while ( 1 )
	{

		smc_list_count = addOptions( smc_list );
		if ( (smc_list_count + 1) < (sizeof( smc_list ) / sizeof(Options)) ) // Full push
		{
			break;
		}
		smc_hmi_list_count = addOptions( smc_hmi_list );
		if ( (smc_hmi_list_count + 1) < (sizeof( smc_hmi_list ) / sizeof(Options)) ) // Full push
		{
			break;
		}
#if 0
		amc_list_count = addOptions( amc_list );
		if ( ( amc_list_count + 1) < (sizeof( amc_list ) / sizeof(Options) )) // Full push
		{
			break;
		}
		usc_list_count = addOptions( usc_list );
		if ( ( usc_list_count + 1) < (sizeof( usc_list ) / sizeof(Options)) ) // Full push
		{
			break;
		}
#endif

		count = 0;
		ret =  MOptionsRead( SMC ,&count, 1 );
		if ( ret < 0 ) break;
		if ( count < smc_list_count ) // Full Extract
		{
			break;
		}

		count = 0;
		
		ret =  MOptionsRead( AMC ,&count, 1 );
		if ( ret < 0 ) break;
		if ( count < smc_hmi_list_count ) // Full Extract
		{
			break;
		}
		
		#if 0
		ret =  MOptionsRead( AMC ,&count, 1 );
		if ( ret < 0 ) break;
		if ( count < amc_list_count ) // Full Extract
		{
			break;
		}

		count = 0;
		ret =  MOptionsRead( USC , &count, 1 ); // Full Extract
		if ( ret < 0 ) break;
		if ( count < usc_list_count ) 
		{
			break;
		}
		#endif

		break;
	}

	if ( ret >= 0 )
	{
		// Fill Smc_Cal_T
		memcpy( pData, &load_config_data, sizeof(load_config_data) );
		ret = 0;
	}

	return ret;
}

