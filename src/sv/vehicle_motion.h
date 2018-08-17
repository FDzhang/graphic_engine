#ifndef __VEHICLE_MOTION_H__
#define __VEHICLE_MOTION_H__
//#pragma once
typedef struct Gpu_Point2f_T
{
	float x;
	float y;
}Gpu_Point2f;

typedef struct COMMON_VEHICLE_DATA_SIMPLE_T
{
    float steering_angle; //StrWhAng -2048~2048   deg
    float vehicle_speed; //VehSpdAvgDrvn
         float yaw_rate; //VehDynYawRate -127~127 deg/sec
         float wheel_speed_fl; //
    float wheel_speed_fr; //
    float wheel_speed_rl; //WhlGrndVlctyLtNnDrvn  km/h
    float wheel_speed_rr; //WhlGrndVlctyRtNnDrvn  km/h
         int shift_pos; //VehMovState //0:parked; 0x1:Neutral; 0x2: Forward; 0x3 Rward; 0x4 Invalid
    bool door_sts_fl; // DDAjirSwAtv
         bool door_sts_fr; // PAjirSwAtv
         bool door_sts_rl; //RRDoorAjarSwAtct
         bool door_sts_rr; //RLDoorAjarSwAtct
    unsigned char left_turn_sig;  
    unsigned char right_turn_sig; 
         unsigned char brake_act_flag;
		 
         unsigned char reserved;
		 unsigned short wheel_pulse[4];
		 unsigned short pre_wheel_pulse[4];
}COMMON_VEHICLE_DATA_SIMPLE;

#include <math.h>

//#define CV_PI 3.1415926

//struct tag
//{
//	float t[9];
//}x,y;
#if 0
struct VEHICLE_MOTION
{
	double track_offset, track;
	//float t[9];

	void steeringwheel_radius(float str_whl_angle, 
						  int shft_pos,
						  float &radius)
	{
		if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				radius = 3.314f/tan(0.07225*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)-0.3655f;
			}
			else
			{
				radius = 4.967f/tan(0.115*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.8558f;
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				radius = 4.048f/tan(0.09341*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.2907f;
			}
			else
			{
				radius = 4.593f/tan(0.10941*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.8289f;
			}
		}
	}

	void steeringwheel_wheelangle(COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
		                       
								 float &whl_angle_a, 
								 float &whl_angle_b)
	{
		int shft_pos = vhcl_can_data.shift_pos;
		float str_whl_angle = vhcl_can_data.steering_angle;
		float radius = 0;

		if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				radius = 3.314f/tan(0.07225*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)-0.3655f;
				whl_angle_a = -atan(2.749f/(radius+1.838f/2));
				whl_angle_b = -atan(2.749f/(radius-1.838f/2));
			}
			else
			{
				radius = 4.967f/tan(0.115*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.8558f;
				whl_angle_b = atan(2.749f/(radius+1.838f/2));
				whl_angle_a = atan(2.749f/(radius-1.838f/2));
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				radius = 4.048f/tan(0.09341*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.2907f;
				whl_angle_a = -atan(2.749f/(radius+1.838f/2));
				whl_angle_b = -atan(2.749f/(radius-1.838f/2));
			}
			else
			{
				radius = 4.593f/tan(0.10941*(fabs(str_whl_angle)+0.00000001f)*CV_PI/180)+0.8289f;
				whl_angle_b = atan(2.749f/(radius+1.838f/2));
				whl_angle_a = atan(2.749f/(radius-1.838f/2));
			}
		}
	}


	void traject_predict_world(Point2f point_src,
		                       COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
					           Point2f &point_dst,
					           float time_offset,
							   float theta_src,
							   float &theta_dst
							   )
	{
		int shft_pos = vhcl_can_data.shift_pos;
		float str_whl_angle = vhcl_can_data.steering_angle;
		float radius = 0;
		steeringwheel_radius(str_whl_angle, shft_pos, radius);
		float speed = 0;
		//float track_offset = 0;
		//float track;
		float theta_offset;
		//float theta;

		float x_offset, y_offset;


		if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;

				theta_offset = track_offset/radius;

				x_offset = radius*(1-cos(abs(theta_offset)));
                y_offset = radius*sin(abs(theta_offset));

				point_dst.x = point_src.x+cos(abs(theta_src))*x_offset+sin(abs(theta_src))*y_offset;
				point_dst.y = point_src.y-sin(abs(theta_src))*x_offset+cos(abs(theta_src))*y_offset;

				theta_dst = theta_src+theta_offset;
			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed*0.97f;

				theta_offset = -track_offset/radius;

				x_offset = -radius*(1-cos(abs(theta_offset)));
                y_offset = radius*sin(abs(theta_offset));

				//point_dst.x = point_src.x+cos(abs(theta_src))*x_offset+sin(abs(theta_src))*y_offset;
				//point_dst.y = point_src.y-sin(abs(theta_src))*x_offset+cos(abs(theta_src))*y_offset;

				point_dst.x = point_src.x+cos(abs(theta_src))*x_offset-sin(abs(theta_src))*y_offset;
				point_dst.y = point_src.y+sin(abs(theta_src))*x_offset+cos(abs(theta_src))*y_offset;

				theta_dst = theta_src+theta_offset;
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				
				theta_offset = -track_offset/radius;

				x_offset = radius*(1-cos(abs(theta_offset)));
                y_offset = -radius*sin(abs(theta_offset));

				point_dst.x = point_src.x+cos(abs(theta_src))*x_offset+sin(abs(theta_src))*y_offset;
				point_dst.y = point_src.y-sin(abs(theta_src))*x_offset+cos(abs(theta_src))*y_offset;

				theta_dst = theta_src+theta_offset;

			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed*0.97f;

				theta_offset = track_offset/radius;

				x_offset = -radius*(1-cos(abs(theta_offset)));
                y_offset = -radius*sin(abs(theta_offset));

				point_dst.x = point_src.x+cos(abs(theta_src))*x_offset+sin(abs(theta_src))*y_offset;
				point_dst.y = point_src.y-sin(abs(theta_src))*x_offset+cos(abs(theta_src))*y_offset;

				theta_dst = theta_src+theta_offset;
			}
		}

		
	}
	
	void traject_predict_car(Point2f point_src,
		                     COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
							 Point2f &point_dst,
							 float time_offset)
	{
		int shft_pos = vhcl_can_data.shift_pos;
		float str_whl_angle = vhcl_can_data.steering_angle;
		float radius = 0;
		steeringwheel_radius(str_whl_angle, shft_pos, radius);
		float speed = 0;

		float track_offset = 0;
		//float track;
		float theta_offset;
		//float theta;

		if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;

				theta_offset = track_offset/radius;

				point_dst.x = point_src.x*cos(abs(theta_offset))+point_src.y*sin(abs(theta_offset))-radius*sin(abs(theta_offset));
				point_dst.y = -point_src.x*sin(abs(theta_offset))+point_src.y*cos(abs(theta_offset))+radius*(1-cos(abs(theta_offset)));
			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;

				theta_offset = track_offset/radius;

				point_dst.x = point_src.x*cos(abs(theta_offset))-point_src.y*sin(abs(theta_offset))-radius*sin(abs(theta_offset));
				point_dst.y = point_src.x*sin(abs(theta_offset))+point_src.y*cos(abs(theta_offset))-radius*(1-cos(abs(theta_offset)));
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;

				theta_offset = track_offset/radius;

				point_dst.x = point_src.x*cos(abs(theta_offset))-point_src.y*sin(abs(theta_offset))+radius*sin(abs(theta_offset));
				point_dst.y = point_src.x*sin(abs(theta_offset))+point_src.y*cos(abs(theta_offset))+radius*(1-cos(abs(theta_offset)));
			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;

				theta_offset = track_offset/radius;

				point_dst.x = point_src.x*cos(abs(theta_offset))-point_src.y*sin(abs(theta_offset))+radius*sin(abs(theta_offset));
				point_dst.y = -point_src.x*sin(abs(theta_offset))+point_src.y*cos(abs(theta_offset))-radius*(1-cos(abs(theta_offset)));
			}
		}
	}

	
	float *get_motion_transform(COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
							 int time_offset,
							 float cx, float cy,
							 float ppmmx, float ppmmy,
							 float *t)
	{
		//Mat T;
		int shft_pos = vhcl_can_data.shift_pos;
		float str_whl_angle = vhcl_can_data.steering_angle;
		float radius=0;
		steeringwheel_radius(str_whl_angle, shft_pos, radius);
		float speed=0;

		//float track_offset = 0;
		//float track;
		double theta_offset;
		//float theta;
		//float *t;
		//t = new float [9];
	
		

		if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;//
				//speed = vhcl_can_data.vehicle_speed/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
			    t[1] = ppmmx/ppmmy*sin(theta_offset);
                t[2] = cy*(1-cos(theta_offset))-cx*ppmmx/ppmmy*sin(theta_offset)+radius/ppmmy*(1-cos(theta_offset));  
                t[3] = -ppmmy/ppmmx*sin(theta_offset);  
                t[4] = cos(theta_offset);  
                t[5] = cx*(1-cos(theta_offset))+cy*ppmmy/ppmmx*sin(theta_offset)+radius/ppmmx*sin(theta_offset); 
			    t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed*0.97f;
				track += track_offset;
				theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
			    t[1] = -ppmmx/ppmmy*sin(theta_offset);
                t[2] = cy*(1-cos(theta_offset))+cx*ppmmx/ppmmy*sin(theta_offset)-radius/ppmmy*(1-cos(theta_offset));  
                t[3] = ppmmy/ppmmx*sin(theta_offset);  
                t[4] = cos(theta_offset);  
                t[5] = cx*(1-cos(theta_offset))-cy*ppmmy/ppmmx*sin(theta_offset)+radius/ppmmx*sin(theta_offset); 
			    t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				theta_offset = track_offset/radius;

		        t[0] = cos(theta_offset);
			    t[1] = -ppmmx/ppmmy*sin(theta_offset);
                t[2] = cy*(1-cos(theta_offset))+cx*ppmmx/ppmmy*sin(theta_offset)+radius/ppmmy*(1-cos(theta_offset));  
                t[3] = ppmmy/ppmmx*sin(theta_offset);  
                t[4] = cos(theta_offset);  
                t[5] = cx*(1-cos(theta_offset))-cy*ppmmy/ppmmx*sin(theta_offset)-radius/ppmmx*sin(theta_offset); 
			    t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
			else
			{
				speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed*0.97f;
				track += track_offset;
				theta_offset = track_offset/radius;

			    t[0] = cos(theta_offset);
			    t[1] = ppmmx/ppmmy*sin(theta_offset);
                t[2] = cy*(1-cos(theta_offset))-cx*ppmmx/ppmmy*sin(theta_offset)-radius/ppmmy*(1-cos(theta_offset));  
                t[3] = -ppmmy/ppmmx*sin(theta_offset);  
                t[4] = cos(theta_offset);  
                t[5] = cx*(1-cos(theta_offset))+cy*ppmmy/ppmmx*sin(theta_offset)-radius/ppmmx*sin(theta_offset); 
			    t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
		}

		return t;
		
	}
							 




};
#endif

#endif
