
#include "GlSVOverlay.h"
#include "AVMData.h"
#include <math.h>



/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/








/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


GlSVOverlay::GlSVOverlay()
{

	
}

int GlSVOverlay::InitPrivate(Dynamic_Overlay_Para pConfig)
{
    m_config_private = pConfig;
	
	return 0;
}


int GlSVOverlay::Update(float steeringwheel,int drive_indicate)
{
    float center[2];
	float radius[2];
	float theta[2];
	float  length = 0;
	if(steeringwheel<0.1&&steeringwheel>-0.1)
	{
		steeringwheel=0.1;
	}
    CaculateCenter(&center[0],&center[1],radius,theta,steeringwheel,drive_indicate);
	if(drive_indicate == OLY_DIR_BACKWARD)
	{
		length = m_config_private.overlay_length;
		Set_Cam_Pos(rear_camera_index,m_config.m_rear_cam_pos_wld);
	}
	else
	{
		length = -m_config_private.overlay_length;
		Set_Cam_Pos(front_camera_index,m_config.m_front_cam_pos_wld);
	}
	GenerateArcPlane(center[0],center[1],radius,length,theta,m_data_size,m_element_num,(float *)m_pdata);


	return 0;
}

void GlSVOverlay::CaculateCenter(float *centerX, float *centerY,float radius[],float *theta,float fSteeringwheel,int Direct)
{
	float fTurnRadius;
    float fBackWheel2Tail = m_config.vehicle_rear_wheel2bumper_length;
	float fVehicleWidth = m_config.vehicle_width;
	float fFrontWheel2Bumper = m_config.vehicle_front_wheel2bumper_length;
	float fAxisLength = m_config.vehicle_axis_length+fFrontWheel2Bumper;
	Cal_Steeringwheel_2_Radius(&fTurnRadius,fSteeringwheel,Direct);
	 
	 *centerY = 0.0;
    if(OLY_DIR_BACKWARD == Direct)
    {
        if(fTurnRadius <0)	
        {
		   radius[0] = sqrt(fTurnRadius*fTurnRadius+fBackWheel2Tail*fBackWheel2Tail);
		   radius[1] = sqrt((-fTurnRadius+fVehicleWidth)*(-fTurnRadius+fVehicleWidth)+fBackWheel2Tail*fBackWheel2Tail);
		   theta[0]=atan(fBackWheel2Tail/fTurnRadius);
		   theta[1]=atan(fBackWheel2Tail/(fTurnRadius-fVehicleWidth));
		   
		   *centerX = fTurnRadius- fVehicleWidth/2;

		}
		else
		{
			radius[1] = sqrt(fTurnRadius*fTurnRadius+fBackWheel2Tail*fBackWheel2Tail);
			radius[0] = sqrt((fTurnRadius+fVehicleWidth)*(fTurnRadius+fVehicleWidth)+fBackWheel2Tail*fBackWheel2Tail);
			theta[1]=atan(fBackWheel2Tail/fTurnRadius);
			theta[0]=atan(fBackWheel2Tail/(fTurnRadius+fVehicleWidth));
			 *centerX = fTurnRadius+fVehicleWidth/2;
		    
		}
    }
    else if(OLY_DIR_FOWARD == Direct)  //foward using rear wheel inside and front head outside
    {
    #if 0
         if(fTurnRadius <0)	
        {
		   radius[0] = -fTurnRadius;
		   radius[1] = sqrt((-fTurnRadius+fVehicleWidth)*(-fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
		   theta[0]=0;
		   theta[1]=-atan(fFrontWheel2Bumper/(fTurnRadius-fVehicleWidth));
		   
		   *centerX = fTurnRadius- fVehicleWidth/2;

		}
		else
		{
			radius[1] = fTurnRadius;
			radius[0] = sqrt((fTurnRadius+fVehicleWidth)*(fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
			theta[1]=0;
			theta[0]=-atan(fFrontWheel2Bumper/(fTurnRadius+fVehicleWidth));
			 *centerX = fTurnRadius+fVehicleWidth/2;
		    
		} 
		#endif
         if(fTurnRadius <0)	
        {
		   radius[0] = sqrt((-fTurnRadius)*(-fTurnRadius)+fAxisLength*fAxisLength);
		   radius[1] = sqrt((-fTurnRadius+fVehicleWidth)*(-fTurnRadius+fVehicleWidth)+fAxisLength*fAxisLength);
		   theta[0]=-atan(fAxisLength/(fTurnRadius));
		   theta[1]=-atan(fAxisLength/(fTurnRadius-fVehicleWidth));
		   
		   *centerX = fTurnRadius- fVehicleWidth/2;

		}
		else
		{
			radius[1] = sqrt((fTurnRadius)*(fTurnRadius)+fAxisLength*fAxisLength);
			radius[0] = sqrt((fTurnRadius+fVehicleWidth)*(fTurnRadius+fVehicleWidth)+fAxisLength*fAxisLength);
			theta[1]=-atan(fAxisLength/(fTurnRadius));
			theta[0]=-atan(fAxisLength/(fTurnRadius+fVehicleWidth));
			 *centerX = fTurnRadius+fVehicleWidth/2;
		    
		}

		
    }
	else if (OLY_SINGLE_BACKWARD ==Direct)
	{
        if(fTurnRadius <0)	
        {

		   radius[0] = sqrt((-fTurnRadius+fVehicleWidth)*(-fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
		   radius[1] =radius[0];


		   theta[0]=-atan(fFrontWheel2Bumper/(fTurnRadius-fVehicleWidth));
		   theta[1]=theta[0];		   
		   *centerX = fTurnRadius- fVehicleWidth/2;

		}
		else
		{
			radius[0] = sqrt((fTurnRadius+fVehicleWidth)*(fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
			radius[1] =radius[0];
			theta[0]=-atan(fFrontWheel2Bumper/(fTurnRadius+fVehicleWidth));
			theta[1]=theta[0];		 

			 *centerX = fTurnRadius+fVehicleWidth/2; 
		}  	    
	}
	#if 0
	else  if (OLY_VERTICAL_PARKING  == Direct)
    {
         if(fTurnRadius <0)	
        {
		   radius[0] = sqrt((fTurnRadius+OVL_VERTICAL_TOL)*(fTurnRadius+OVL_VERTICAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
		   radius[1] = sqrt((-fTurnRadius+VHICLE_WIDTH+OVL_VERTICAL_TOL)*(-fTurnRadius+VHICLE_WIDTH+OVL_VERTICAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
		   theta[0]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius+OVL_VERTICAL_TOL))-MY_PI/20;
		   theta[1]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius-(VHICLE_WIDTH+OVL_VERTICAL_TOL)))-MY_PI/20;
		   
		   *centerX = fTurnRadius- (VHICLE_WIDTH)/2;

		}
		else
		{
			radius[1] = sqrt((fTurnRadius-OVL_VERTICAL_TOL)*(fTurnRadius-OVL_VERTICAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
			radius[0] = sqrt((fTurnRadius+VHICLE_WIDTH+OVL_VERTICAL_TOL)*(fTurnRadius+VHICLE_WIDTH+OVL_VERTICAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
			theta[1]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius-OVL_VERTICAL_TOL))+MY_PI/20;
			theta[0]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius+VHICLE_WIDTH+OVL_VERTICAL_TOL))+MY_PI/20;
			 *centerX = fTurnRadius+(VHICLE_WIDTH)/2;
		    
		}
    }
    else  if (OLY_PARRAEL_PARKING == Direct)
    {
        if(fTurnRadius <0)	
        {
		   radius[1] = sqrt((-fTurnRadius+VHICLE_WIDTH+OVL_PARRAL_TOL)*(-fTurnRadius+VHICLE_WIDTH+OVL_PARRAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
		   radius[0] =  radius[1];

		   theta[1]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius-VHICLE_WIDTH-OVL_PARRAL_TOL))-MY_PI/18;		   
		   theta[0]=theta[1];
		   
		   *centerX = fTurnRadius- (VHICLE_WIDTH)/2;

		}
		else
		{
			radius[0] = sqrt((fTurnRadius+VHICLE_WIDTH+OVL_PARRAL_TOL)*(fTurnRadius+VHICLE_WIDTH+OVL_PARRAL_TOL)+VHI_BACKWHEEL_2_TAIL*VHI_BACKWHEEL_2_TAIL);
			radius[1] = radius[0];
			theta[0]=atan(VHI_BACKWHEEL_2_TAIL/(fTurnRadius+VHICLE_WIDTH+OVL_PARRAL_TOL))+MY_PI/18;
			theta[1]=theta[0];
			
			 *centerX = fTurnRadius+(VHICLE_WIDTH)/2;
		    
		}
    }	
	#endif
	else //foward using rear wheel inside and front head outside
    {
         if(fTurnRadius <0)	
        {
		   radius[0] = sqrt(fTurnRadius*fTurnRadius+fFrontWheel2Bumper*fFrontWheel2Bumper);
		   radius[1] = sqrt((-fTurnRadius+fVehicleWidth)*(-fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
		   theta[0]=-atan(fFrontWheel2Bumper/fTurnRadius);
		   theta[1]=-atan(fFrontWheel2Bumper/(fTurnRadius-fVehicleWidth));
		   
		   *centerX = fTurnRadius- fVehicleWidth/2;

		}
		else
		{
			radius[1] = sqrt(fTurnRadius*fTurnRadius+fFrontWheel2Bumper*fFrontWheel2Bumper);
			radius[0] = sqrt((fTurnRadius+fVehicleWidth)*(fTurnRadius+fVehicleWidth)+fFrontWheel2Bumper*fFrontWheel2Bumper);
			theta[1]=-atan(fFrontWheel2Bumper/fTurnRadius);
			theta[0]=-atan(fFrontWheel2Bumper/(fTurnRadius+fVehicleWidth));
			 *centerX = fTurnRadius+fVehicleWidth/2;
		    
		}       
    }
	
    //real world to image coordinate. use gpu internal process method.
      
}
#define SKY_CLINDER_RADIUS 3500

void GlSVOverlay::GenerateArcPlane(float centerX, float centerY,float radius[],float length,float startangle[],	unsigned int number,int element_perpixel,float*pVertex)
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
		float output[3];
	float tempCam[3];
	//number = (unsigned int)(length/0.1);
	for(int j=0;j<2;j++)
	{
	
	    totalangle = length/radius[j];
    	if(centerX <0)//leftasi
    	{
    		step = -totalangle/number;  //could be optimized.
    		Anglestart[j] =startangle[j];
    	}
    	else
    	{
    		step = totalangle/number;
    		Anglestart[j] =-MY_PI+startangle[j];
    	}
	}
    	for(Loop = 0;Loop <number*2;Loop++)
    	{
            index = Loop%2;
    		xLeft= centerX+(radius[index])*cos(Anglestart[index]+Loop*step);
    		yLeft= centerY+(radius[index])*sin(Anglestart[index]+Loop*step);
			//xRight= centerX+(radius[1])*cos(Anglestart[1]+Loop*step);
    		//yRight= centerY+(radius[1])*sin(Anglestart[1]+Loop*step);
            world_coord[0]=xLeft;
			world_coord[1]=yLeft;


    	    Cal_World_2_Model_Coordinate(model_coord,world_coord);
    	    // left side 
    		//pVertex[index+0] = xLeft*1000;
    		//pVertex[index+1] = yLeft*1000;

			pVertex[slotid+0]= model_coord[0];
			pVertex[slotid+1] = m_config.m_model_bottom;
			pVertex[slotid+2] = model_coord[1];
			if(m_calib_mode == calib_2D_SINGLE)
			{
			       Cal_World_2_Model_Coordinate_3d(output,&pVertex[slotid]); 
        			pVertex[slotid+0]= output[0];
        			pVertex[slotid+1] =output[1];
        			pVertex[slotid+2] = output[1];				   
			}
			else if(m_calib_mode == calib_2D_STICH)
			{
			    pVertex[slotid+1]=pVertex[slotid+2];
			}

            if(m_calib_mode == calib_3D)
            {
                #if 0
				ConvertGroundToClinder(&pVertex[slotid],output,SKY_CLINDER_RADIUS,2,0);
                pVertex[slotid+0]= output[0];
			    pVertex[slotid+1] = output[1];
			    pVertex[slotid+2] = output[2];
				#endif
            }
			
			
			slotid+=8;
    
    	}
	


}

void GlSVOverlay::Cal_Steeringwheel_2_Radius(float *radius,float steerAngle,int gear_state)
{
   //get value from config-file
    float steerCountAtLock = 0;//pVhiclePara->fSteeringWheelAtlock; // steering wheel sensor
    float turnRadiusAtLock = 0;// pVhiclePara->fRmin; // meters minimum truning radius
    float curvatureAtLock = 0; // radians = 1/radius
    float VEHICLE_WHEELBASE = m_config.vehicle_axis_length; //2.85f
    //float steerAngle = Get_Vehicle_Real_Steer_Angle();
    float vehCurv = 0;
    float temp = vehCurv;
	float c_in =vehCurv;
	float max_beta = 0; 
	float beta = 0;
	float c = 0;
   if(gear_state == OLY_DIR_BACKWARD)
   {
	   if(steerAngle>0)
	   {
		   steerCountAtLock = m_config_private.Vehicle_Max_Deg_Steering_Wheel_Left_Turn;
		   turnRadiusAtLock = m_config_private.Vehicle_Min_Radius_Gear_R_Left_Turn_Rear_Axis_Cent;//pVhiclePara->afRminArray[REAR_LEFT_RADIUS];
	   }
	   else
	   {
		   steerCountAtLock = m_config_private.Vehicle_Max_Deg_Steering_Wheel_Right_Turn;//pVhiclePara->afSteeringWheelAtlock[REAR_RIGHT_RADIUS];
		   turnRadiusAtLock = m_config_private.Vehicle_Min_Radius_Gear_R_Right_Turn_Rear_Axis_Cent;//pVhiclePara->afRminArray[REAR_RIGHT_RADIUS];
	   }
   }
   else
   {
	   if(steerAngle>0)
	   {
		   steerCountAtLock = m_config_private.Vehicle_Max_Deg_Steering_Wheel_Left_Turn;
		   turnRadiusAtLock = m_config_private.Vehicle_Min_Radius_Gear_D_Left_Turn_Rear_Axis_Cent;
	   }
	   else
	   {
		   steerCountAtLock = m_config_private.Vehicle_Max_Deg_Steering_Wheel_Right_Turn;;
		   turnRadiusAtLock = m_config_private.Vehicle_Min_Radius_Gear_D_Right_Turn_Rear_Axis_Cent;
	   }	   
   }
   
   curvatureAtLock = 1.0f/turnRadiusAtLock; // radians = 1/radius
   VEHICLE_WHEELBASE = m_config.vehicle_axis_length; //2.85f
   vehCurv = ((float)steerAngle / steerCountAtLock) * curvatureAtLock;
   temp = vehCurv;
	c_in =vehCurv;
	//float VEHICLE_WHEELBASE = 2.7f; //2.85f
	max_beta = atan(VEHICLE_WHEELBASE / turnRadiusAtLock); 
	beta = max_beta * c_in / curvatureAtLock;
	c = tan(beta) / VEHICLE_WHEELBASE;

	vehCurv = c ;

	temp =	(vehCurv>curvatureAtLock? curvatureAtLock:(vehCurv<-curvatureAtLock ? -curvatureAtLock:vehCurv));
	*radius=1/temp;

}


