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
	BEV_OPT_END
};


#if 0
int32_t Convert_Configure_to_SMC( Smc_Cal_T * pSMC_Data, BEV_CONFIG_T *pConfig_data )
{
	int i ;

	pSMC_Data->k_smc_major_ver = pConfig_data->smc.SMC_MAJOR_VERSION;
	pSMC_Data->k_smc_minor_ver = pConfig_data->smc.SMC_MINOR_VERSION;
//// VEHICLE PHYSICAL INFORMATION
//// UNIT: METER -> mm	
	pSMC_Data->veh_param.veh_length			= 1000*pConfig_data->smc.VEHICLE_LENGTH;
	pSMC_Data->veh_param.veh_width			= 1000*pConfig_data->smc.VEHICLE_WIDTH;	
	pSMC_Data->veh_param.veh_fwheel2head	= 1000*pConfig_data->smc.VEHICLE_FRONT_SUSPENSION_LENGTH;
	pSMC_Data->veh_param.veh_axis_length	= 1000*pConfig_data->smc.VEHICLE_WHEELBASE; 
	pSMC_Data->veh_param.veh_rwheel2tail	= 1000*pConfig_data->smc.VEHICLE_REAR_SUSPENSION_LENGTH + 0.5; 
	pSMC_Data->veh_param.veh_tier_R			= 1000*pConfig_data->smc.VEHICLE_TIRE_RADIUS;
//// VEHICLE TURNING RADIUS
//// UNIT: METER -> mm

	pSMC_Data->veh_param.LeftFrontMinTurningRadius		= 1000*pConfig_data->smc.VEHICLE_MIN_RADIUS_FORWARD_LEFTTURN_REAR_WHEEL_CENTER;
	pSMC_Data->veh_param.RightFrontMinTurningRadius		= 1000*pConfig_data->smc.VEHICLE_MIN_RADIUS_FORWARD_RIGHTTURN_REAR_WHEEL_CENTER;
	pSMC_Data->veh_param.LeftBackMinTurningRadius		= 1000*pConfig_data->smc.VEHICLE_MIN_RADIUS_REVERSE_LEFTTURN_REAR_WHEEL_CENTER;
	pSMC_Data->veh_param.RightBackMinTurningRadius		= 1000*pConfig_data->smc.VEHICLE_MIN_RADIUS_REVERSE_RIGHTTURN_REAR_WHEEL_CENTER;
//// VEHICLE STEERING DEGREE
	pSMC_Data->veh_param.LeftMaxSteeringWheelAngle		= pConfig_data->smc.VEHICLE_MAX_STEERING_WHEEL_ANGLE_LEFTTURN;
	pSMC_Data->veh_param.RightMaxSteeringWheelAngle		= pConfig_data->smc.VEHICLE_MAX_STEERING_WHEEL_ANGLE_RIGHTTURN;
////// BEV CALIBRATION PARAMETER
	pSMC_Data->camera_param[0].cam_ext.tx = pConfig_data->smc.FRONT_CAMERA_TRANS_X;
	pSMC_Data->camera_param[0].cam_ext.ty = pConfig_data->smc.FRONT_CAMERA_TRANS_Y;
	pSMC_Data->camera_param[0].cam_ext.tz = pConfig_data->smc.FRONT_CAMERA_TRANS_Z;
	pSMC_Data->camera_param[0].cam_ext.rx = pConfig_data->smc.FRONT_CAMERA_ROT_X;
	pSMC_Data->camera_param[0].cam_ext.ry = pConfig_data->smc.FRONT_CAMERA_ROT_Y;
	pSMC_Data->camera_param[0].cam_ext.rz = pConfig_data->smc.FRONT_CAMERA_ROT_Z;
	pSMC_Data->camera_param[1].cam_ext.tx = pConfig_data->smc.REAR_CAMERA_TRANS_X;
	pSMC_Data->camera_param[1].cam_ext.ty = pConfig_data->smc.REAR_CAMERA_TRANS_Y;
	pSMC_Data->camera_param[1].cam_ext.tz = pConfig_data->smc.REAR_CAMERA_TRANS_Z;
	pSMC_Data->camera_param[1].cam_ext.rx = pConfig_data->smc.REAR_CAMERA_ROT_X;
	pSMC_Data->camera_param[1].cam_ext.ry = pConfig_data->smc.REAR_CAMERA_ROT_Y;
	pSMC_Data->camera_param[1].cam_ext.rz = pConfig_data->smc.REAR_CAMERA_ROT_Z;
	pSMC_Data->camera_param[2].cam_ext.tx = pConfig_data->smc.LEFT_CAMERA_TRANS_X;
	pSMC_Data->camera_param[2].cam_ext.ty = pConfig_data->smc.LEFT_CAMERA_TRANS_Y;
	pSMC_Data->camera_param[2].cam_ext.tz = pConfig_data->smc.LEFT_CAMERA_TRANS_Z;
	pSMC_Data->camera_param[2].cam_ext.rx = pConfig_data->smc.LEFT_CAMERA_ROT_X;
	pSMC_Data->camera_param[2].cam_ext.ry = pConfig_data->smc.LEFT_CAMERA_ROT_Y;
	pSMC_Data->camera_param[2].cam_ext.rz = pConfig_data->smc.LEFT_CAMERA_ROT_Z;
	pSMC_Data->camera_param[3].cam_ext.tx = pConfig_data->smc.RIGHT_CAMERA_TRANS_X;
	pSMC_Data->camera_param[3].cam_ext.ty = pConfig_data->smc.RIGHT_CAMERA_TRANS_Y;
	pSMC_Data->camera_param[3].cam_ext.tz = pConfig_data->smc.RIGHT_CAMERA_TRANS_Z;
	pSMC_Data->camera_param[3].cam_ext.rx = pConfig_data->smc.RIGHT_CAMERA_ROT_X;
	pSMC_Data->camera_param[3].cam_ext.ry = pConfig_data->smc.RIGHT_CAMERA_ROT_Y;
	pSMC_Data->camera_param[3].cam_ext.rz = pConfig_data->smc.RIGHT_CAMERA_ROT_Z;

//
//// AMC
//
	pSMC_Data->k_amc_major_ver = pConfig_data->amc.AMC_MAJOR_VERSION;
	pSMC_Data->k_amc_minor_ver = pConfig_data->amc.AMC_MINOR_VERSION;
//// BEV Stitch related parameters
	pSMC_Data->bev_stitch_param.fl_angle_front_edge			= pConfig_data->amc.ANGLE_FRONT_EDGE_TOP_LEFT;
	pSMC_Data->bev_stitch_param.fl_angle_left_edge 			= pConfig_data->amc.ANGLE_LEFT_EDGE_TOP_LEFT;
	pSMC_Data->bev_stitch_param.fr_angle_front_edge			= pConfig_data->amc.ANGLE_FRONT_EDGE_TOP_RIGHT;
	pSMC_Data->bev_stitch_param.fr_angle_right_edge			= pConfig_data->amc.ANGLE_RIGHT_EDGE_TOP_RIGHT;
	pSMC_Data->bev_stitch_param.bl_angle_back_edge	 		= pConfig_data->amc.ANGLE_BACK_EDGE_BOTTOM_LEFT;
	pSMC_Data->bev_stitch_param.bl_angle_left_edge	 		= pConfig_data->amc.ANGLE_LEFT_EDGE_BOTTOM_LEFT;
	pSMC_Data->bev_stitch_param.br_angle_back_edge	 		= pConfig_data->amc.ANGLE_BACK_EDGE_BOTTOM_RIGHT;
	pSMC_Data->bev_stitch_param.br_angle_right_edge			= pConfig_data->amc.ANGLE_RIGHT_EDGE_BOTTOM_RIGHT;
	pSMC_Data->bev_stitch_param.view_param[0].view_range	= 1000*pConfig_data->amc.BEV_VIEW_RANGE_FRONT;
	pSMC_Data->bev_stitch_param.view_param[0].blind_range	= 1000*pConfig_data->amc.BEV_BLIND_RANGE_FRONT;
	pSMC_Data->bev_stitch_param.view_param[1].view_range	= 1000*pConfig_data->amc.BEV_VIEW_RANGE_REAR;
	pSMC_Data->bev_stitch_param.view_param[1].blind_range	= 1000*pConfig_data->amc.BEV_BLIND_RANGE_REAR;
	pSMC_Data->bev_stitch_param.view_param[2].view_range	= 1000*pConfig_data->amc.BEV_VIEW_RANGE_LEFT;
	pSMC_Data->bev_stitch_param.view_param[2].blind_range	= 1000*pConfig_data->amc.BEV_BLIND_RANGE_LEFT;
	pSMC_Data->bev_stitch_param.view_param[3].view_range	= 1000*pConfig_data->amc.BEV_VIEW_RANGE_RIGHT;
	pSMC_Data->bev_stitch_param.view_param[3].blind_range	= 1000*pConfig_data->amc.BEV_BLIND_RANGE_RIGHT;
	pSMC_Data->bev_stitch_param.bev_stitch_img_width		= pConfig_data->amc.BEV_STITCH_IMG_WIDTH			;
	pSMC_Data->bev_stitch_param.bev_stitch_img_height		= pConfig_data->amc.BEV_STITCH_IMG_HEIGHT			;

	//// Single View related parameters
	pSMC_Data->bev_single_param.single_view_width						=	pConfig_data->amc.SINGLE_VIEW_WIDTH				;
	pSMC_Data->bev_single_param.single_view_height						=	pConfig_data->amc.SINGLE_VIEW_HEIGHT			;
	pSMC_Data->bev_single_param.sv_undist_percent[0]					=	pConfig_data->amc.FRONT_SV_UNDIST_PERCENT			     ;
	pSMC_Data->bev_single_param.sv_undist_percent[1]					=	pConfig_data->amc.REAR_SV_UNDIST_PERCENT			     ;
	pSMC_Data->bev_single_param.sv_undist_percent[2]					=	pConfig_data->amc.LEFT_SV_UNDIST_PERCENT			     ;
	pSMC_Data->bev_single_param.sv_undist_percent[3]					=	pConfig_data->amc.RIGHT_SV_UNDIST_PERCENT			     ;
	pSMC_Data->bev_single_param.hfov_start								=	pConfig_data->amc.HFOV_START							 ;
	pSMC_Data->bev_single_param.hfov_end								=	pConfig_data->amc.HFOV_END								 ;
	pSMC_Data->bev_single_param.vfov_start								=	pConfig_data->amc.VFOV_START							 ;
	pSMC_Data->bev_single_param.vfov_end								=	pConfig_data->amc.VFOV_END								 ;
	pSMC_Data->bev_single_param.upper_shield_in_pix						=	pConfig_data->amc.UPPER_SHIELD_IN_PIX					 ;
	pSMC_Data->bev_single_param.downer_shield_in_pix					=	pConfig_data->amc.DOWNER_SHIELD_IN_PIX					 ;
	pSMC_Data->bev_single_param.front_single_view_roi_topleft_x			=	pConfig_data->amc.FRONT_SINGLE_VIEW_ROI_TOPLEFT_X		 ;
	pSMC_Data->bev_single_param.front_single_view_roi_topleft_y			=	pConfig_data->amc.FRONT_SINGLE_VIEW_ROI_TOPLEFT_Y		 ;
	pSMC_Data->bev_single_param.front_single_view_roi_bottom_right_x	=	pConfig_data->amc.FRONT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_X	 ;
	pSMC_Data->bev_single_param.front_single_view_roi_bottom_right_y	=	pConfig_data->amc.FRONT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_Y	 ;
	pSMC_Data->bev_single_param.rear_single_view_roi_topleft_x			=	pConfig_data->amc.REAR_SINGLE_VIEW_ROI_TOPLEFT_X		 ;
	pSMC_Data->bev_single_param.rear_single_view_roi_topleft_y			=	pConfig_data->amc.REAR_SINGLE_VIEW_ROI_TOPLEFT_Y		 ;
	pSMC_Data->bev_single_param.rear_single_view_roi_bottom_right_x		=	pConfig_data->amc.REAR_SINGLE_VIEW_ROI_BOTTOM_RIGHT_X	 ;
	pSMC_Data->bev_single_param.rear_single_view_roi_bottom_right_y		=	pConfig_data->amc.REAR_SINGLE_VIEW_ROI_BOTTOM_RIGHT_Y	 ;
	pSMC_Data->bev_single_param.left_single_view_roi_topleft_x			=	pConfig_data->amc.LEFT_SINGLE_VIEW_ROI_TOPLEFT_X		 ;
	pSMC_Data->bev_single_param.left_single_view_roi_topleft_y			=	pConfig_data->amc.LEFT_SINGLE_VIEW_ROI_TOPLEFT_Y		 ;
	pSMC_Data->bev_single_param.left_single_view_roi_bottom_right_x		=	pConfig_data->amc.LEFT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_X	 ;
	pSMC_Data->bev_single_param.left_single_view_roi_bottom_right_y		=	pConfig_data->amc.LEFT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_Y	 ;
	pSMC_Data->bev_single_param.right_single_view_roi_topleft_x			=	pConfig_data->amc.RIGHT_SINGLE_VIEW_ROI_TOPLEFT_X		 ;
	pSMC_Data->bev_single_param.right_single_view_roi_topleft_y			=	pConfig_data->amc.RIGHT_SINGLE_VIEW_ROI_TOPLEFT_Y		 ;
	pSMC_Data->bev_single_param.right_single_view_roi_bottom_right_x	=	pConfig_data->amc.RIGHT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_X	 ;
	pSMC_Data->bev_single_param.right_single_view_roi_bottom_right_y	=	pConfig_data->amc.RIGHT_SINGLE_VIEW_ROI_BOTTOM_RIGHT_Y	 ;



////
////// EOL PARAMETER
	pSMC_Data->bev_eol_param.board_width					= 1000*pConfig_data->amc.CALIB_BOARD_WIDTH;
	pSMC_Data->bev_eol_param.board_length					= 1000*pConfig_data->amc.CALIB_BOARD_LENGTH;
	pSMC_Data->bev_eol_param.board_veh_flboard2fwheel		= 1000*pConfig_data->amc.FRONT_LEFT_CALIB_BOARD_TO_VEH_FRONT_WHEEL_DIST;
	pSMC_Data->bev_eol_param.board_veh_flboard2centralaxis	= 1000*pConfig_data->amc.FRONT_LEFT_CALIB_BOARD_TO_VEH_CENTRAL_AXIS_DIST;
	pSMC_Data->bev_eol_param.board_flboard2frboard			= 1000*pConfig_data->amc.FRONT_LEFT_CALIB_BOARD_TO_FRONT_RIGHT_CALIB_BOARD_DIST;
	pSMC_Data->bev_eol_param.board_flboard2rlboard			= 1000*pConfig_data->amc.FRONT_LEFT_CALIB_BOARD_TO_REAR_LEFT_CALIB_BOARD_DIST;
////
//////SVS
	pSMC_Data->bev_svs_param.board_size = 1000*pConfig_data->amc.CALIBRATION_BOARD_SIZE_SVS;
	pSMC_Data->bev_svs_param.veh_tire_arrow_wid_fl = 1000*pConfig_data->amc.CALIBRATION_TOOL_Distance;
	pSMC_Data->bev_svs_param.veh_tire_arrow_wid_fr = 1000*pConfig_data->amc.CALIBRATION_TOOL_Distance;
	pSMC_Data->bev_svs_param.veh_tire_arrow_wid_bl = 1000*pConfig_data->amc.CALIBRATION_TOOL_Distance;
	pSMC_Data->bev_svs_param.veh_tire_arrow_wid_br = 1000*pConfig_data->amc.CALIBRATION_TOOL_Distance;
////
////// PGS Parameters
	pSMC_Data->bev_pgs_param.steering_wheel_range_veh_curv					= pConfig_data->amc.STEERING_WHEEL_RANGE_VEH_CURV					;
	pSMC_Data->bev_pgs_param.steering_wheel_meet_tol_veh_curv				= pConfig_data->amc.STEERING_WHEEL_MEET_TOL_VEH_CURV				;
	pSMC_Data->bev_pgs_param.enter_parking_vehicle_speed_gate				= pConfig_data->amc.ENTER_PARKING_VEHICLE_SPEED_GATE				;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_vert_first_fwd_opt		= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_VERT_FIRST_FWD_OPT			;	
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_vert_first_fwd			= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_VERT_FIRST_FWD				;	
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_verl_sec_back				= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_VERL_SEC_BACK				;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_paral_first_fwd			= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_PARAL_FIRST_FWD			;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_paral_first_bwd			= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_PARAL_FIRST_BWD			;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_paral_sec_bwd				= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_PARAL_SEC_BWD				;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_turn_dir_all				= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_TURN_DIR_ALL				;
	pSMC_Data->bev_pgs_param.drv_dist_abnor_range_sel_lot_all				= pConfig_data->amc.DRV_DIST_ABNOR_RANGE_SEL_LOT_ALL				;
	pSMC_Data->bev_pgs_param.paral_first_foward_dist_tolerance				= pConfig_data->amc.PARAL_FIRST_FOWARD_DIST_TOLERANCE				;
	pSMC_Data->bev_pgs_param.vert_first_foward_dist_tolerance				= pConfig_data->amc.VERT_FIRST_FOWARD_DIST_TOLERANCE				;
	pSMC_Data->bev_pgs_param.state_last_time_between_parkings				= pConfig_data->amc.STATE_LAST_TIME_BETWEEN_PARKINGS				;
	pSMC_Data->bev_pgs_param.vertical_parking_final_state_auto_exit_time	= pConfig_data->amc.VERTICAL_PARKING_FINAL_STATE_AUTO_EXIT_TIME		;	
	pSMC_Data->bev_pgs_param.parallel_parking_final_state_auto_exit_time	= pConfig_data->amc.PARALLEL_PARKING_FINAL_STATE_AUTO_EXIT_TIME		;	
	pSMC_Data->bev_pgs_param.state_last_time_parking_lot_select				= pConfig_data->amc.STATE_LAST_TIME_PARKING_LOT_SELECT				;
	pSMC_Data->bev_pgs_param.state_last_time_vertical_first_foward_optional	= pConfig_data->amc.STATE_LAST_TIME_VERTICAL_FIRST_FOWARD_OPTIONAL	;
	pSMC_Data->bev_pgs_param.state_last_time_vertical_first_turn			= pConfig_data->amc.STATE_LAST_TIME_VERTICAL_FIRST_TURN				;	
	pSMC_Data->bev_pgs_param.state_last_time_vertical_first_foward			= pConfig_data->amc.STATE_LAST_TIME_VERTICAL_FIRST_FOWARD			;
	pSMC_Data->bev_pgs_param.state_last_time_vertical_second_turn			= pConfig_data->amc.STATE_LAST_TIME_VERTICAL_SECOND_TURN			;
	pSMC_Data->bev_pgs_param.state_last_time_vertical_second_backward		= pConfig_data->amc.STATE_LAST_TIME_VERTICAL_SECOND_BACKWARD		;
	pSMC_Data->bev_pgs_param.state_last_time_parallel_first_foward			= pConfig_data->amc.STATE_LAST_TIME_PARALLEL_FIRST_FOWARD			;
	pSMC_Data->bev_pgs_param.state_last_time_parallel_first_turn			= pConfig_data->amc.STATE_LAST_TIME_PARALLEL_FIRST_TURN				;	
	pSMC_Data->bev_pgs_param.state_last_time_parallel_first_backward		= pConfig_data->amc.STATE_LAST_TIME_PARALLEL_FIRST_BACKWARD			;	
	pSMC_Data->bev_pgs_param.state_last_time_parallel_second_turn			= pConfig_data->amc.STATE_LAST_TIME_PARALLEL_SECOND_TURN			;
	pSMC_Data->bev_pgs_param.state_last_time_parallel_second_backward		= pConfig_data->amc.STATE_LAST_TIME_PARALLEL_SECOND_BACKWARD		;
	pSMC_Data->bev_pgs_param.default_parking_lot_lateral_distance			= pConfig_data->amc.DEFAULT_PARKING_LOT_LATERAL_DISTANCE			;
	pSMC_Data->bev_pgs_param.parallel_parking_curb_lot_length 				= pConfig_data->amc.PARALLEL_PARKING_CURB_LOT_LENGTH 				;
	pSMC_Data->bev_pgs_param.parallel_parking_curb_lot_width 				= pConfig_data->amc.PARALLEL_PARKING_CURB_LOT_WIDTH 				;
	pSMC_Data->bev_pgs_param.parallel_parking_wall_lot_length 				= pConfig_data->amc.PARALLEL_PARKING_WALL_LOT_LENGTH 				;
	pSMC_Data->bev_pgs_param.parallel_parking_wall_lot_width				= pConfig_data->amc.PARALLEL_PARKING_WALL_LOT_WIDTH					;	
	pSMC_Data->bev_pgs_param.vertical_parking_lot_length					= pConfig_data->amc.VERTICAL_PARKING_LOT_LENGTH						;	
	pSMC_Data->bev_pgs_param.vertical_parking_lot_width						= pConfig_data->amc.VERTICAL_PARKING_LOT_WIDTH						;
	pSMC_Data->bev_pgs_param.vertical_parking_final_stop_positionoffset		= pConfig_data->amc.VERTICAL_PARKING_FINAL_STOP_POSITIONOFFSET		;

////
////// HMI Parameters
	/// BEV HMI
	pSMC_Data->bev_hmi_param.bev.bev_img_pos_x				=			pConfig_data->amc.BEV_IMG_POS_X					;
	pSMC_Data->bev_hmi_param.bev.bev_img_pos_y				=			pConfig_data->amc.BEV_IMG_POS_Y					;
	pSMC_Data->bev_hmi_param.bev.single_view_img_pos_x		=			pConfig_data->amc.SINGLE_VIEW_IMG_POS_X			;
	pSMC_Data->bev_hmi_param.bev.single_view_img_pos_y		=			pConfig_data->amc.SINGLE_VIEW_IMG_POS_Y			;
	pSMC_Data->bev_hmi_param.bev.parking_lot_adjust_step	=			pConfig_data->amc.PARKING_LOT_ADJUST_STEP		;
	pSMC_Data->bev_hmi_param.bev.parking_button_pos_x		=			pConfig_data->amc.PARKING_BUTTON_POS_X			;
	pSMC_Data->bev_hmi_param.bev.parking_button_pos_y		=			pConfig_data->amc.PARKING_BUTTON_POS_Y			;
	pSMC_Data->bev_hmi_param.bev.parking_button_width		=			pConfig_data->amc.PARKING_BUTTON_WIDTH			;
	pSMC_Data->bev_hmi_param.bev.parking_button_height		=			pConfig_data->amc.PARKING_BUTTON_HEIGHT			;
	pSMC_Data->bev_hmi_param.bev.view_switch_button_pos_x	=			pConfig_data->amc.VIEW_SWITCH_BUTTON_POS_X		;
	pSMC_Data->bev_hmi_param.bev.view_switch_button_pos_y	=			pConfig_data->amc.VIEW_SWITCH_BUTTON_POS_Y		;
	pSMC_Data->bev_hmi_param.bev.view_switch_button_width	=			pConfig_data->amc.VIEW_SWITCH_BUTTON_WIDTH		;
	pSMC_Data->bev_hmi_param.bev.view_switch_button_height	=			pConfig_data->amc.VIEW_SWITCH_BUTTON_HEIGHT		;

	/// Singleview HMI
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlay_margin2vehicle						=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAY_MARGIN2VEHICLE				   ;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlay_near_line_distance2vehicle			=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAY_NEAR_LINE_DISTANCE2VEHICLE	   ;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlay_middel_line_distance2vehicle			=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAY_MIDDEL_LINE_DISTANCE2VEHICLE	;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlay_far_line_distance2vehicle			=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAY_FAR_LINE_DISTANCE2VEHICLE	   ;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlayr_line_type							=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAYR_LINE_TYPE					   ;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlayr_line_width							=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAYR_LINE_WIDTH					;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlay_thickness_in_phy						=			pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAY_THICKNESS_IN_PHY				;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlayr_near_line_color						=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAYR_NEAR_LINE_COLOR				;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlayr_middle_line_color					=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAYR_MIDDLE_LINE_COLOR			   ;
	pSMC_Data->bev_hmi_param.sv.single_view_static_overlayr_far_line_color						=    		pConfig_data->amc.SINGLE_VIEW_STATIC_OVERLAYR_FAR_LINE_COLOR				;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_start_from_bumper_f					=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_START_FROM_BUMPER_F			;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_start_from_bumper_r					=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_START_FROM_BUMPER_R			;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_length								=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_LENGTH						;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_segment_num							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_SEGMENT_NUM					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlayr_line_type							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAYR_LINE_TYPE					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlayr_line_width							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAYR_LINE_WIDTH					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_thickness_in_phy					=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_THICKNESS_IN_PHY			   ;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_color_seg_0							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_COLOR_SEG_0					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_color_seg_1							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_COLOR_SEG_1					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_color_seg_2							=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_COLOR_SEG_2					;
	pSMC_Data->bev_hmi_param.sv.single_view_dynamic_overlay_margin								=    		pConfig_data->amc.SINGLE_VIEW_DYNAMIC_OVERLAY_MARGIN						;



////
////// PGS HMI
	pSMC_Data->bev_hmi_param.pgs.gear_icon_d_x									=			pConfig_data->amc.GEAR_ICON_D_X									;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_d_y									=			pConfig_data->amc.GEAR_ICON_D_Y									;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_d_width								=			pConfig_data->amc.GEAR_ICON_D_WIDTH								;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_d_height								=			pConfig_data->amc.GEAR_ICON_D_HEIGHT							;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_r_x									=			pConfig_data->amc.GEAR_ICON_R_X									;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_r_y									=			pConfig_data->amc.GEAR_ICON_R_Y									;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_r_width								=			pConfig_data->amc.GEAR_ICON_R_WIDTH								;
	pSMC_Data->bev_hmi_param.pgs.gear_icon_r_height								=			pConfig_data->amc.GEAR_ICON_R_HEIGHT							;
	pSMC_Data->bev_hmi_param.pgs.gear_indicate_icon_twinkle_time_total			=			pConfig_data->amc.GEAR_INDICATE_ICON_TWINKLE_TIME_TOTAL			;
	pSMC_Data->bev_hmi_param.pgs.gear_indicate_icon_twinkle_apeear_time			=			pConfig_data->amc.GEAR_INDICATE_ICON_TWINKLE_APEEAR_TIME		;
	pSMC_Data->bev_hmi_param.pgs.gear_indicate_icon_altha_weight				=			pConfig_data->amc.GEAR_INDICATE_ICON_ALTHA_WEIGHT				;
	pSMC_Data->bev_hmi_param.pgs.steering_wheel_y_to_image_center				=			pConfig_data->amc.STEERING_WHEEL_Y_TO_IMAGE_CENTER				;
	pSMC_Data->bev_hmi_param.pgs.dynamic_overlay_apeear_threshold				=			pConfig_data->amc.DYNAMIC_OVERLAY_APEEAR_THRESHOLD				;
	pSMC_Data->bev_hmi_param.pgs.front_dynamic_overlay_length					=			pConfig_data->amc.FRONT_DYNAMIC_OVERLAY_LENGTH					;
	pSMC_Data->bev_hmi_param.pgs.front_dynamic_overlay_line_width				=			pConfig_data->amc.FRONT_DYNAMIC_OVERLAY_LINE_WIDTH				;
	pSMC_Data->bev_hmi_param.pgs.front_dynamic_overlay_color					=			pConfig_data->amc.FRONT_DYNAMIC_OVERLAY_COLOR					;
	pSMC_Data->bev_hmi_param.pgs.front_dynamic_overlay_alpha_weight_max			=			pConfig_data->amc.FRONT_DYNAMIC_OVERLAY_ALPHA_WEIGHT_MAX		;
	pSMC_Data->bev_hmi_param.pgs.front_dynamic_overlay_alpha_weight_min			=			pConfig_data->amc.FRONT_DYNAMIC_OVERLAY_ALPHA_WEIGHT_MIN		;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_overlay_length					=			pConfig_data->amc.REAR_DYNAMIC_OVERLAY_LENGTH					;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_overlay_line_width				=			pConfig_data->amc.REAR_DYNAMIC_OVERLAY_LINE_WIDTH				;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_overlay_color						=			pConfig_data->amc.REAR_DYNAMIC_OVERLAY_COLOR					;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_overlay_alpha_weight_max			=			pConfig_data->amc.REAR_DYNAMIC_OVERLAY_ALPHA_WEIGHT_MAX			;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_overlay_alpha_weight_min			=			pConfig_data->amc.REAR_DYNAMIC_OVERLAY_ALPHA_WEIGHT_MIN			;
	pSMC_Data->bev_hmi_param.pgs.rear_dynamic_side_overlay_length				=			pConfig_data->amc.REAR_DYNAMIC_SIDE_OVERLAY_LENGTH				;
	pSMC_Data->bev_hmi_param.pgs.parallel_vertical_step_one_line_length			=			pConfig_data->amc.PARALLEL_VERTICAL_STEP_ONE_LINE_LENGTH		;
	pSMC_Data->bev_hmi_param.pgs.parallel_vertical_step_one_line_width			=			pConfig_data->amc.PARALLEL_VERTICAL_STEP_ONE_LINE_WIDTH			;
	pSMC_Data->bev_hmi_param.pgs.parallel_vertical_step_one_line_color			=			pConfig_data->amc.PARALLEL_VERTICAL_STEP_ONE_LINE_COLOR			;
	pSMC_Data->bev_hmi_param.pgs.parallel_vertical_step_one_line_alpha_weight	=			pConfig_data->amc.PARALLEL_VERTICAL_STEP_ONE_LINE_ALPHA_WEIGHT	;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_two_line_width					=			pConfig_data->amc.PARALLEL_STEP_TWO_LINE_WIDTH					;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_two_line_length					=			pConfig_data->amc.PARALLEL_STEP_TWO_LINE_LENGTH					;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_two_line_color					=			pConfig_data->amc.PARALLEL_STEP_TWO_LINE_COLOR					;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_two_line_alpha_weight			=			pConfig_data->amc.PARALLEL_STEP_TWO_LINE_ALPHA_WEIGHT			;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_three_line_width					=			pConfig_data->amc.PARALLEL_STEP_THREE_LINE_WIDTH				;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_three_line_length				=			pConfig_data->amc.PARALLEL_STEP_THREE_LINE_LENGTH				;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_three_line_color					=			pConfig_data->amc.PARALLEL_STEP_THREE_LINE_COLOR				;
	pSMC_Data->bev_hmi_param.pgs.parallel_step_three_line_alpha_weight			=			pConfig_data->amc.PARALLEL_STEP_THREE_LINE_ALPHA_WEIGHT			;
	pSMC_Data->bev_hmi_param.pgs.vertical_step_two_line_dist_to_vehicle			=			pConfig_data->amc.VERTICAL_STEP_TWO_LINE_DIST_TO_VEHICLE		;
	pSMC_Data->bev_hmi_param.pgs.vertical_step_two_line_length					=			pConfig_data->amc.VERTICAL_STEP_TWO_LINE_LENGTH					;
	pSMC_Data->bev_hmi_param.pgs.vertical_step_two_line_width					=			pConfig_data->amc.VERTICAL_STEP_TWO_LINE_WIDTH					;
	pSMC_Data->bev_hmi_param.pgs.vertical_step_two_line_color					=			pConfig_data->amc.VERTICAL_STEP_TWO_LINE_COLOR					;
	pSMC_Data->bev_hmi_param.pgs.vertical_step_two_alpha_weight					=			pConfig_data->amc.VERTICAL_STEP_TWO_ALPHA_WEIGHT				;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_ruler_line_width					=			pConfig_data->amc.PARKING_LOT_RULER_LINE_WIDTH					;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_ruler_color						=			pConfig_data->amc.PARKING_LOT_RULER_COLOR						;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_ruler_alpha_weight					=			pConfig_data->amc.PARKING_LOT_RULER_ALPHA_WEIGHT				;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_line_length						=			pConfig_data->amc.PARKING_LOT_LINE_LENGTH						;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_line_width							=			pConfig_data->amc.PARKING_LOT_LINE_WIDTH						;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_color								=			pConfig_data->amc.PARKING_LOT_COLOR								;
	pSMC_Data->bev_hmi_param.pgs.parking_lot_alpha_weight						=			pConfig_data->amc.PARKING_LOT_ALPHA_WEIGHT						;
	
////
////
////// USC
	pSMC_Data->k_usc_major_ver = pConfig_data->usc.USC_MAJOR_VERSION;
	pSMC_Data->k_usc_minor_ver = pConfig_data->usc.USC_MINOR_VERSION;
////
////// CAMERA PARAMETER
		
	pSMC_Data->bev_decoder_param.camera_decode_formate		=  pConfig_data->usc.CAMERA_DECODE_FORMATE;
	pSMC_Data->bev_decoder_param.capture_offset_x[0]		=  pConfig_data->usc.CAPTURE_OFFSET_X_FRONT;	
	pSMC_Data->bev_decoder_param.capture_offset_y[0]		=  pConfig_data->usc.CAPTURE_OFFSET_Y_FRONT;
	pSMC_Data->bev_decoder_param.capture_offset_x[1]		=  pConfig_data->usc.CAPTURE_OFFSET_X_REAR;	
	pSMC_Data->bev_decoder_param.capture_offset_y[1]		=  pConfig_data->usc.CAPTURE_OFFSET_Y_REAR;	
	pSMC_Data->bev_decoder_param.capture_offset_x[2]		=  pConfig_data->usc.CAPTURE_OFFSET_X_LEFT;	
	pSMC_Data->bev_decoder_param.capture_offset_y[2]		=  pConfig_data->usc.CAPTURE_OFFSET_Y_LEFT;	
	pSMC_Data->bev_decoder_param.capture_offset_x[3]		=  pConfig_data->usc.CAPTURE_OFFSET_X_RIGHT;	
	pSMC_Data->bev_decoder_param.capture_offset_y[3]		=  pConfig_data->usc.CAPTURE_OFFSET_Y_RIGHT;	

	pSMC_Data->bev_decoder_param.brightness[0]		=  pConfig_data->usc.BRIGHTNESS_FRONT;
	pSMC_Data->bev_decoder_param.brightness[1]		=  pConfig_data->usc.BRIGHTNESS_REAR;
	pSMC_Data->bev_decoder_param.brightness[2]		=  pConfig_data->usc.BRIGHTNESS_LEFT;
	pSMC_Data->bev_decoder_param.brightness[3]		=  pConfig_data->usc.BRIGHTNESS_RIGHT;

	pSMC_Data->bev_decoder_param.contrast[0]		=  pConfig_data->usc.CONTRAST_FRONT;
	pSMC_Data->bev_decoder_param.contrast[1]		=  pConfig_data->usc.CONTRAST_REAR;
	pSMC_Data->bev_decoder_param.contrast[2]		=  pConfig_data->usc.CONTRAST_LEFT;
	pSMC_Data->bev_decoder_param.contrast[3]		=  pConfig_data->usc.CONTRAST_RIGHT;

	pSMC_Data->bev_decoder_param.chroma_u[0]		=  pConfig_data->usc.CHROMA_U_FRONT;
	pSMC_Data->bev_decoder_param.chroma_u[1]		=  pConfig_data->usc.CHROMA_U_REAR;
	pSMC_Data->bev_decoder_param.chroma_u[2]		=  pConfig_data->usc.CHROMA_U_LEFT;
	pSMC_Data->bev_decoder_param.chroma_u[3]		=  pConfig_data->usc.CHROMA_U_RIGHT;

	pSMC_Data->bev_decoder_param.chroma_v[0]		=  pConfig_data->usc.CHROMA_V_FRONT;
	pSMC_Data->bev_decoder_param.chroma_v[1]		=  pConfig_data->usc.CHROMA_V_REAR;
	pSMC_Data->bev_decoder_param.chroma_v[2]		=  pConfig_data->usc.CHROMA_V_LEFT;
	pSMC_Data->bev_decoder_param.chroma_v[3]		=  pConfig_data->usc.CHROMA_V_RIGHT;

	pSMC_Data->bev_decoder_param.hue[0]		=  pConfig_data->usc.HUE_FRONT;
	pSMC_Data->bev_decoder_param.hue[1]		=  pConfig_data->usc.HUE_REAR;
	pSMC_Data->bev_decoder_param.hue[2]		=  pConfig_data->usc.HUE_LEFT;
	pSMC_Data->bev_decoder_param.hue[3]		=  pConfig_data->usc.HUE_RIGHT;

	pSMC_Data->camera_param[0].cam_sensor.camera_output_center_x = pConfig_data->usc.CAMERA_OUTPUT_CENTER_X_FRONT;
	pSMC_Data->camera_param[0].cam_sensor.camera_output_center_y = pConfig_data->usc.CAMERA_OUTPUT_CENTER_Y_FRONT;
	pSMC_Data->camera_param[1].cam_sensor.camera_output_center_x = pConfig_data->usc.CAMERA_OUTPUT_CENTER_X_REAR;
	pSMC_Data->camera_param[1].cam_sensor.camera_output_center_y = pConfig_data->usc.CAMERA_OUTPUT_CENTER_Y_REAR;
	pSMC_Data->camera_param[2].cam_sensor.camera_output_center_x = pConfig_data->usc.CAMERA_OUTPUT_CENTER_X_LEFT;
	pSMC_Data->camera_param[2].cam_sensor.camera_output_center_y = pConfig_data->usc.CAMERA_OUTPUT_CENTER_Y_LEFT;
	pSMC_Data->camera_param[3].cam_sensor.camera_output_center_x = pConfig_data->usc.CAMERA_OUTPUT_CENTER_X_RIGHT;
	pSMC_Data->camera_param[3].cam_sensor.camera_output_center_y = pConfig_data->usc.CAMERA_OUTPUT_CENTER_Y_RIGHT;
	
	for ( i = 0; i < 4; i ++ )
	{
		pSMC_Data->camera_param[i].cam_sensor.camera_output_width			= pConfig_data->usc.CAMERA_OUTPUT_WIDTH;
		pSMC_Data->camera_param[i].cam_sensor.camera_output_height			= pConfig_data->usc.CAMERA_OUTPUT_HEIGHT;
		pSMC_Data->camera_param[i].cam_lens.camera_fisheye_model			= pConfig_data->usc.CAMERA_FISHEYE_MODEL;  // 1: F*(ANGLE)
		pSMC_Data->camera_param[i].cam_lens.hfov							= pConfig_data->usc.CAMERA_HFOV;
		pSMC_Data->camera_param[i].cam_lens.vfov							= pConfig_data->usc.CAMERA_VFOV;
		pSMC_Data->camera_param[i].cam_input.input_image_width				= pConfig_data->usc.INPUT_IMAGE_WIDTH;
		pSMC_Data->camera_param[i].cam_input.input_image_height				= pConfig_data->usc.INPUT_IMAGE_HEIGHT;
		pSMC_Data->camera_param[i].cam_input.input_image_width_active		= pConfig_data->usc.INPUT_IMAGE_WIDTH_ACTIVE;
		pSMC_Data->camera_param[i].cam_input.input_image_height_active		= pConfig_data->usc.INPUT_IMAGE_HEIGHT_ACTIVE;
		pSMC_Data->camera_param[i].cam_input.input_image_active_offset_x	= pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_X;
		pSMC_Data->camera_param[i].cam_input.input_image_active_offset_y	= pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_Y;
		pSMC_Data->camera_param[i].cam_normal.width = 640;
		pSMC_Data->camera_param[i].cam_normal.height = 480;
		pSMC_Data->camera_param[i].cam_normal.centx = 320;
		pSMC_Data->camera_param[i].cam_normal.centy = 240;
		pSMC_Data->camera_param[i].cam_normal.hfov = 120;
		pSMC_Data->camera_param[i].cam_normal.vfov = 90;
	}

	pSMC_Data->camera_param[0].cam_input.input_image_center_x		= pSMC_Data->camera_param[0].cam_sensor.camera_output_center_x - pConfig_data->usc.CAPTURE_OFFSET_X_FRONT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_X;
	pSMC_Data->camera_param[0].cam_input.input_image_center_y		= pSMC_Data->camera_param[0].cam_sensor.camera_output_center_y - pConfig_data->usc.CAPTURE_OFFSET_Y_FRONT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_Y;
	pSMC_Data->camera_param[1].cam_input.input_image_center_x		= pSMC_Data->camera_param[1].cam_sensor.camera_output_center_x - pConfig_data->usc.CAPTURE_OFFSET_X_REAR + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_X;
	pSMC_Data->camera_param[1].cam_input.input_image_center_y		= pSMC_Data->camera_param[1].cam_sensor.camera_output_center_y - pConfig_data->usc.CAPTURE_OFFSET_Y_REAR + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_Y;
	pSMC_Data->camera_param[2].cam_input.input_image_center_x		= pSMC_Data->camera_param[2].cam_sensor.camera_output_center_x - pConfig_data->usc.CAPTURE_OFFSET_X_LEFT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_X;
	pSMC_Data->camera_param[2].cam_input.input_image_center_y		= pSMC_Data->camera_param[2].cam_sensor.camera_output_center_y - pConfig_data->usc.CAPTURE_OFFSET_Y_LEFT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_Y;
	pSMC_Data->camera_param[3].cam_input.input_image_center_x		= pSMC_Data->camera_param[3].cam_sensor.camera_output_center_x - pConfig_data->usc.CAPTURE_OFFSET_X_RIGHT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_X;
	pSMC_Data->camera_param[3].cam_input.input_image_center_y		= pSMC_Data->camera_param[3].cam_sensor.camera_output_center_y - pConfig_data->usc.CAPTURE_OFFSET_Y_RIGHT + pConfig_data->usc.INPUT_IMAGE_ACTIVE_OFFSET_Y;


////
////// DISPLAY PARAMETER
////
	// Output
	pSMC_Data->bev_display_param.output_image_width				=  pConfig_data->usc.OUTPUT_IMAGE_WIDTH;
	pSMC_Data->bev_display_param.output_image_height			=  pConfig_data->usc.OUTPUT_IMAGE_HEIGHT;
	pSMC_Data->bev_display_param.output_image_width_active		=  pConfig_data->usc.OUTPUT_IMAGE_WIDTH_ACTIVE;
	pSMC_Data->bev_display_param.output_image_height_active		=  pConfig_data->usc.OUTPUT_IMAGE_HEIGHT_ACTIVE;
	pSMC_Data->bev_display_param.output_image_active_offset_x	=  pConfig_data->usc.OUTPUT_IMAGE_ACTIVE_OFFSET_X;
	pSMC_Data->bev_display_param.output_image_active_offset_y	=  pConfig_data->usc.OUTPUT_IMAGE_ACTIVE_OFFSET_Y;

	pSMC_Data->bev_display_param.display_scale_x				= pConfig_data->usc.DISPLAY_SCALE_X;
	pSMC_Data->bev_display_param.display_scale_y				= pConfig_data->usc.DISPLAY_SCALE_Y;
	pSMC_Data->bev_display_param.display_offset_x				= pConfig_data->usc.DISPLAY_OFFSET_X;
	pSMC_Data->bev_display_param.display_offset_y				= pConfig_data->usc.DISPLAY_OFFSET_Y;
////
////// ENCODE PARAMETER
	pSMC_Data->bev_display_param.output_encoder_format			= pConfig_data->usc.OUTPUT_ENCODER_FORMAT; 	// 1 "PAL", 2: "NTSC"

	return -1;
}
#endif
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

