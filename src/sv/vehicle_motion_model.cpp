//#include "../../source/utility/common/reuse.h"
//#include "..\utility\common\commondef.h"
#include "vehicle_motion_model.h"
#include <math.h>
#include <stdlib.h>
#include<stdio.h>
void VehicleMotion::SteerWheel2Radius(
	float32_t str_whl_angle,
	int shft_pos,
	float32_t &radius
	)
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

void VehicleMotion::Motion2KframePredictVCS(
	COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
	int32_t time_offset,
	float32_t &track,
	float32_t t[9],
	float32_t m[9],
	int32_t &flag,
	float32_t thresh_dist_kframe
	)
{

	int shft_pos = vhcl_can_data.shift_pos;
	float32_t str_whl_angle = vhcl_can_data.steering_angle;
	float32_t radius = 0;
	float32_t track_offset = 0;
	//SteerWheel2Radius(str_whl_angle, shft_pos, radius);
	steeringwheel_radius(str_whl_angle,shft_pos,radius);
	radius=radius;


	if (track>=thresh_dist_kframe)
	{
		flag = 1;
		track = 0.0f;
		m[0] = 1.0f;
		m[1] = 0.0f;
		m[2] = 0.0f;
		m[3] = 0.0f;
		m[4] = 1.0f;
		m[5] = 0.0f;
		m[6] = 0.0f;
		m[7] = 0.0f;
	    m[8] = 1.0f;
	}
	else
	{
		flag = 0;
	}

	if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				float speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				float theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
				t[1] = sin(theta_offset);
				t[2] = -radius*sin(theta_offset);
				t[3] = -sin(theta_offset);
				t[4] = cos(theta_offset);
				t[5] = radius*(1-cos(theta_offset));
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
				//pointOut.x = pointIn.x*cos(abs(theta_offset))+pointIn.y*sin(abs(theta_offset))-radius*sin(abs(theta_offset));
				//pointOut.y = -pointIn.x*sin(abs(theta_offset))+pointIn.y*cos(abs(theta_offset))+radius*(1-cos(abs(theta_offset)));
			}
			else
			{
				float speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				float theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
				t[1] = -sin(theta_offset);
				t[2] = -radius*sin(theta_offset);
				t[3] = sin(theta_offset);
				t[4] = cos(theta_offset);
				t[5] = -radius*(1-cos(theta_offset));
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;

				//pointOut.x = pointIn.x*cos(abs(theta_offset))-pointIn.y*sin(abs(theta_offset))-radius*sin(abs(theta_offset));
				//pointOut.y = pointIn.x*sin(abs(theta_offset))+pointIn.y*cos(abs(theta_offset))-radius*(1-cos(abs(theta_offset)));
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				float speed = vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				float theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
				t[1] = -sin(theta_offset);
				t[2] = radius*sin(theta_offset);
				t[3] = sin(theta_offset);
				t[4] = cos(theta_offset);
				t[5] = radius*(1-cos(theta_offset));
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;

				//pointOut.x = pointIn.x*cos(abs(theta_offset))-pointIn.y*sin(abs(theta_offset))+radius*sin(abs(theta_offset));
				//pointOut.y = pointIn.x*sin(abs(theta_offset))+pointIn.y*cos(abs(theta_offset))+radius*(1-cos(abs(theta_offset)));
			}
			else
			{
				float speed = vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				float theta_offset = track_offset/radius;

				t[0] = cos(theta_offset);
				t[1] = sin(theta_offset);
				t[2] = radius*sin(theta_offset);
				t[3] = -sin(theta_offset);
				t[4] = cos(theta_offset);
				t[5] = -radius*(1-cos(theta_offset));
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;

				//pointOut.x = pointIn.x*cos(abs(theta_offset))+pointIn.y*sin(abs(theta_offset))+radius*sin(abs(theta_offset));
				//pointOut.y = -pointIn.x*sin(abs(theta_offset))+pointIn.y*cos(abs(theta_offset))-radius*(1-cos(abs(theta_offset)));
			}
		}

	Mat_Mul_3by3(m, t, m);
}

void VehicleMotion::revMotion2KframePredictVCS(
	COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
	int32_t time_offset,
	float32_t &track,
	float32_t t[9],
	float32_t m[9],
	int32_t &flag,
	float32_t thresh_dist_kframe
	)
{

	int shft_pos = vhcl_can_data.shift_pos;
	float32_t str_whl_angle = vhcl_can_data.steering_angle;
	float32_t radius = 0;
	float32_t track_offset = 0;
	float dist_temp=0;
	//SteerWheel2Radius(str_whl_angle, shft_pos, radius);
	
    //fprintf(stdout,"\r\noldradius%f",radius);
	steeringwheel_radius(str_whl_angle,shft_pos,radius);
	
    //fprintf(stdout,"\r\nnew radius%f",radius);
	float theta_offset;
	
	int turn_sign = get_turn_dir(&vhcl_can_data);
	radius = radius/1000.0;
	
	dist_temp = -get_distance_from_pulse(&vhcl_can_data);
    theta_offset = dist_temp/radius;
	//if(theta_offset !=0)
    //fprintf(stdout,"\r\nold theta %f,dist %f",theta_offset,dist_temp);
	
	//theta_offset= -fabs(get_theta_from_multi_pulse(&vhcl_can_data,radius*1000,turn_sign));
    //fprintf(stdout,"\r\nnew theta %f,dist %f",theta_offset,dist_temp);
	float f_time_offset = time_offset;
	//theta_offset = -get_theta_from_distance(&vhcl_can_data, radius*1000, turn_sign, f_time_offset);
	if (fabs(track)>=thresh_dist_kframe)
	{
		flag = 1;
		track = 0.0f;
		m[0] = 1.0f;
		m[1] = 0.0f;
		m[2] = 0.0f;
		m[3] = 0.0f;
		m[4] = 1.0f;
		m[5] = 0.0f;
		m[6] = 0.0f;
		m[7] = 0.0f;
	    m[8] = 1.0f;
	}
	else
	{
		flag = 0;
	}

	if(shft_pos == 2)
		{
			if(str_whl_angle<0)
			{
				float speed = -vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				theta_offset = track_offset/radius;
				//if(theta_offset!=0)
				//fprintf(stdout,"\r\n 1 old theta %f",theta_offset);
				float cosValue = cos(theta_offset);
				float sinValue = sin(theta_offset);
				t[0] = cosValue;
				t[1] = sinValue;
				t[2] = -radius*sinValue;
				t[3] = -sinValue;
				t[4] = cosValue;
				t[5] = radius*(1-cosValue);
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
			else
			{
				float speed = -vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				
				theta_offset = track_offset/radius;
				//if(theta_offset!=0)
				//fprintf(stdout,"\r\n 2 old theta %f",theta_offset);
				float cosValue = cos(theta_offset);
				float sinValue = sin(theta_offset);

				t[0] = cosValue;
				t[1] = -sinValue;
				t[2] = -radius*sinValue;
				t[3] = sinValue;
				t[4] = cosValue;
				t[5] = -radius*(1-cosValue);
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				float speed = -vhcl_can_data.wheel_speed_rr/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				theta_offset = track_offset/radius;
				//if(theta_offset!=0)
				//fprintf(stdout,"\r\n 3 old theta %f",theta_offset);
				float cosValue = cos(theta_offset);
				float sinValue = sin(theta_offset);

				t[0] = cosValue;
				t[1] = -sinValue;
				t[2] = radius*sinValue;
				t[3] = sinValue;
				t[4] = cosValue;
				t[5] = radius*(1-cosValue);
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
			else
			{
				float speed = -vhcl_can_data.wheel_speed_rl/3.6f;
				track_offset = time_offset/1000000.0f*speed;
				track += track_offset;
				theta_offset = track_offset/radius;
				//if(theta_offset!=0)
				//fprintf(stdout,"\r\n 4 old theta %f",theta_offset);
				float cosValue = cos(theta_offset);
				float sinValue = sin(theta_offset);

				t[0] = cosValue;
				t[1] = sinValue;
				t[2] = radius*sinValue;
				t[3] = -sinValue;
				t[4] = cosValue;
				t[5] = -radius*(1-cosValue);
				t[6] = 0.0f;
			    t[7] = 0.0f;
			    t[8] = 1.0f;
			}
		}

	Mat_Mul_3by3(m, t, m);
}


void VehicleMotion::getPos2Kframe(
	GpuCvPoint2D32f pointIn,
	float32_t m[9],
	GpuCvPoint2D32f &pointOut
	)
{
	pointOut.x = m[0]*pointIn.x+m[1]*pointIn.y+m[2];
	pointOut.y = m[3]*pointIn.x+m[4]*pointIn.y+m[5];
}
int VehicleMotion::get_driving_dir(COMMON_VEHICLE_DATA_SIMPLE * v_data)
{
	return (v_data->shift_pos == 0x03 ? -1 : 1);
}
int VehicleMotion::get_turn_dir(COMMON_VEHICLE_DATA_SIMPLE * v_data)
{
	int dir = get_driving_dir(v_data);
	int sign = 1;
	if (dir > 0)//forward,
	{
		if (v_data->steering_angle > 0) //left-turn
			sign = -1;
		else
			sign = 1;
	}
	else//backward
	{
		if (v_data->steering_angle > 0)//
			sign = 1;
		else
			sign = -1;
	}
	return sign;

}



void VehicleMotion::steeringwheel_radius(
	float str_whl_angle,
	int shft_pos,
	float &radius
	)//convert from steering wheel angle to steering radius
{
	enum{ _Forward_R = 0, _Forward_L, _Backward_R, _Backward_L };
	float32_t H = 2.756f * 1000;
	float32_t W = 1.839f * 1000;
	float32_t _a[4], _b[4];
	#if 0
#define COEFF_LINEAR_FR 0.056620
#define COEFF_LINEAR_FL 0.056248
#define COEFF_LINEAR_RR 0.047870
#define COEFF_LINEAR_RL 0.065278

#define COEFF_CONST_FR -0.029849
#define COEFF_CONST_FL -0.023264
#define COEFF_CONST_RR  2.981121
#define COEFF_CONST_RL -3.054503
#else


#define COEFF_LINEAR_FR 0.0643
#define COEFF_LINEAR_FL 0.1098
#define COEFF_LINEAR_RR 0.08407
#define COEFF_LINEAR_RL 0.10503
	
#define COEFF_CONST_FR 0.0
#define COEFF_CONST_FL 0.0
#define COEFF_CONST_RR  0.0
#define COEFF_CONST_RL -0.0
#endif


#if 1
if (shft_pos == 2)
{
	if (str_whl_angle < 0) // steering wheel turns clockwisely
	{
		radius = 2700.0 / tan((6.18785419533*(1.0e-8)*(-str_whl_angle) *(-str_whl_angle) *(-str_whl_angle) - 5.56846210504*(1.0e-6)*(-str_whl_angle) *(-str_whl_angle)
			+ 0.0648694036246 * (-str_whl_angle) + 0.0431498050907)*CV_PI / 180.0);
	}
	else
	{
		radius = 2700.0 / tan((4.08146348191*(1.0e-8)*(str_whl_angle) *(str_whl_angle) *(str_whl_angle) + 1.74925456061*(1.0e-5)*(str_whl_angle) *(str_whl_angle)
			+ 0.0577312396722 * (str_whl_angle) + 0.0180829501563)*CV_PI / 180.0);

		//radius = 2756 / tan(ABS(0.06501 * str_whl_angle + FLT_MIN + _b[_Forward_L])*CV_PI / 180) + 919.5;
	}
}
else
{
	if (str_whl_angle < 0) // steering wheel turns anti-clockwisely
	{
		radius = 2700.0 / tan((6.61732367641*(1.0e-8)*(-str_whl_angle) *(-str_whl_angle) *(-str_whl_angle) - 1.87272938306*(1.0e-5)*(-str_whl_angle) *(-str_whl_angle)
			+ 0.0685588855819 * (-str_whl_angle) + 0.0423157328512)*CV_PI / 180.0);
	}
	else
	{
		radius = 2700.0 / tan((2.19221033599*(1.0e-8)*(str_whl_angle) *(str_whl_angle) *(str_whl_angle) + 2.2210856422*(1.0e-5)*(str_whl_angle) *(str_whl_angle)
			+ 0.0580515777155 * (str_whl_angle) + 0.0186827689377)*CV_PI / 180.0);
	}
}

#endif

static float pre_steering_wheel=0;
   if(pre_steering_wheel != str_whl_angle)
   {
      // fprintf(stdout,"\r\n gear[%d],steer[%f],radius[%f]",shft_pos,str_whl_angle,radius);
       pre_steering_wheel = str_whl_angle;
    }
   
}

float VehicleMotion::get_yawrate_from_curvature(COMMON_VEHICLE_DATA_SIMPLE * v_data)
{
	unsigned char gear_state = v_data->shift_pos;
	float steerAngle = v_data->steering_angle;
	float Radius = 0;
	steeringwheel_radius(steerAngle, gear_state, Radius);
	Radius = fabs(Radius);

	int shft_pos = v_data->shift_pos;
	float str_whl_angle = v_data->steering_angle;
	float speed;


	
	speed =1000.0* (v_data->wheel_speed_rr + v_data->wheel_speed_rl) / 2.0f / 3.6f;
    //if(steerAngle<0)
	//speed =1000.0* ( v_data->wheel_speed_rl)  / 3.6f;

   // else
	//	speed =1000.0* (v_data->wheel_speed_rr ) / 3.6f;


	return fabs(speed) / Radius;
}

float VehicleMotion::get_distance_from_pulse(COMMON_VEHICLE_DATA_SIMPLE * v_data)
{
    int16_t pulse_curent[2];
	int16_t pulse_pre[2];
	int16_t pulse_delta[2];

 	float pulse_distance = 0.027289235;
	float max_pulse = 255;

	pulse_curent[0]=v_data->wheel_pulse[rear_left_whl];
	pulse_pre[0]=v_data->pre_wheel_pulse[rear_left_whl];
	pulse_curent[1]=v_data->wheel_pulse[rear_right_whl];
	pulse_pre[1]=v_data->pre_wheel_pulse[rear_right_whl];
	
    for(int i=0;i<2;i++)
    {
	    if(pulse_curent[i]<pulse_pre[i])
	    {
	        pulse_delta[i] = -pulse_pre[i]+max_pulse+pulse_curent[i];
	    }
		else
		{
	        pulse_delta[i] = -pulse_pre[i]+pulse_curent[i];
		
		}
    }

    return((pulse_delta[0] +pulse_delta[1] )*pulse_distance/2.0f);
	
}
float VehicleMotion::get_theta_from_multi_pulse(COMMON_VEHICLE_DATA_SIMPLE * v_data,float radius,int turn_sign)
{
    // unit  mm

	float radius_real[4];
    int16_t pulse_curent[2];
	int16_t pulse_pre[2];
	int16_t pulse_delta[4];
    float half_wheel_width=793;
	float axis_length = 2750;
    float theta_offset[4];
	float theta_offset_total;
	theta_offset_total=0;
	float effective_num=0;
    if(v_data->steering_angle<0)//(turn_right)
    {
	    radius_real[front_left_whl] = sqrt((radius+half_wheel_width)*(radius+half_wheel_width)+axis_length*axis_length);
	    radius_real[front_right_whl] = sqrt((radius-half_wheel_width)*(radius-half_wheel_width)+axis_length*axis_length);
	    radius_real[rear_left_whl] = radius+half_wheel_width;
	    radius_real[rear_right_whl] = radius-half_wheel_width;
		
    }
	else
	{
	    radius_real[front_right_whl] = sqrt((radius+half_wheel_width)*(radius+half_wheel_width)+axis_length*axis_length);
	    radius_real[front_left_whl] = sqrt((radius-half_wheel_width)*(radius-half_wheel_width)+axis_length*axis_length);
	    radius_real[rear_right_whl] = radius+half_wheel_width;
	    radius_real[rear_left_whl] = radius-half_wheel_width;
	    
	}
	pulse_curent[0]=v_data->wheel_pulse[rear_left_whl];
	pulse_pre[0]=v_data->pre_wheel_pulse[rear_left_whl];
	pulse_curent[1]=v_data->wheel_pulse[rear_right_whl];
	pulse_pre[1]=v_data->pre_wheel_pulse[rear_right_whl];

    for(int i=0;i<4;i++)
    {
	    if(v_data->wheel_pulse[i]<v_data->pre_wheel_pulse[i])
	    {
	        pulse_delta[i] = -v_data->pre_wheel_pulse[i]+1024+v_data->wheel_pulse[i];
	    }
		else
		{
	        pulse_delta[i] = -v_data->pre_wheel_pulse[i]+v_data->wheel_pulse[i];
		
		}
        if(pulse_delta[i]==0)
        {
            continue;
        }
		effective_num=effective_num+1.0;
		theta_offset[i] = (1000*turn_sign*pulse_delta[i]*0.046)/radius_real[i];
		theta_offset_total += theta_offset[i];	
    }
	if(effective_num == 0)
	{
	    theta_offset_total=0;
	}
	else
	{
	    theta_offset_total=theta_offset_total/effective_num;
	}
	//fprintf(stdout,"\r\nradius[%f,%f,%f,%f], radius_axis[%f]",radius_real[0],radius_real[1],radius_real[2],radius_real[3],radius);
	//fprintf(stdout,"\r\ndelta pulse[%d,%d,%d,%d]",pulse_delta[0],pulse_delta[1],pulse_delta[2],pulse_delta[3]);

    return theta_offset_total;
	
}

void VehicleMotion::get_new_point_from_Vhichle_data(Gpu_Point2f pts[MAXPOINTNUM], COMMON_VEHICLE_DATA_SIMPLE * v_data, float g_PLD_time_Offset_in)
{
	int dri_sign = get_driving_dir(v_data);
	int turn_sign = get_turn_dir(v_data);
	float radius;
	float theta_offset;
	steeringwheel_radius(v_data->steering_angle, v_data->shift_pos, radius);
	//float theta_offset = turn_sign*get_yawrate_from_curvature(v_data)*g_PLD_time_Offset_in;
    
	//fprintf(stdout,"\r\n theta_offset wheel speed=%f",theta_offset);
     theta_offset= (1000*turn_sign*get_distance_from_pulse(v_data))/radius;
	//fprintf(stdout,"\r\n theta_offset pulse speed=%f",theta_offset);
	//theta_offset= get_theta_from_multi_pulse(v_data,radius,turn_sign);
	//fprintf(stdout,"\r\n theta_offset multi pulse speed=%f",theta_offset);


	int shft_pos = v_data->shift_pos;
	float str_whl_angle = v_data->steering_angle;
	//theta_offset = get_theta_from_distance(v_data, radius, turn_sign,  g_PLD_time_Offset_in);

	for (int i = 0; i < MAXPOINTNUM; i++)
	{
		Gpu_Point2f point_src, point_dst;
		point_src = pts[i];
		if (shft_pos == 2)
		{
			if (str_whl_angle < 0)
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) + point_src.y*sin(ABS(theta_offset)) - radius*sin(ABS(theta_offset));
				point_dst.y = -point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) + radius*(1 - cos(ABS(theta_offset)));
			}
			else
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) - point_src.y*sin(ABS(theta_offset)) - radius*sin(ABS(theta_offset));
				point_dst.y = point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) - radius*(1 - cos(ABS(theta_offset)));
			}
		}
		else
		{
			if (str_whl_angle < 0)
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) - point_src.y*sin(ABS(theta_offset)) + radius*sin(ABS(theta_offset));
				point_dst.y = point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) + radius*(1 - cos(ABS(theta_offset)));
			}
			else
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) + point_src.y*sin(ABS(theta_offset)) + radius*sin(ABS(theta_offset));
				point_dst.y = -point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) - radius*(1 - cos(ABS(theta_offset)));
			}
		}
		pts[i] = point_dst;
	}



}
float VehicleMotion::get_theta_from_distance(COMMON_VEHICLE_DATA_SIMPLE * v_data,float radius,int turn_sign, float g_PLD_time_Offset_in)
{
    // unit  mm
   // Static int fffff=0;
     
       int16_t pulse_delta[2];
    float half_wheel_width=794;
       //float axis_length = 2750;
    float theta_offset;
       

	int flag=1; 
	int n1=0;
	int n2=0;
	float speed_down=1;//�����ٶȣ�km/h
	float speed_up=4;//�����ٶȣ�km/h
	float ratio=45.81;//�������


    if(v_data->steering_angle<0)//(turn_right)
    {
           flag=-1;
           
    }
       else
       {
           flag=1;
           
       }
      

    for(int i=0;i<2;i++)
    {
           if(v_data->wheel_pulse[i]<v_data->pre_wheel_pulse[i])
          {
               pulse_delta[i] = -v_data->pre_wheel_pulse[i]+1024+v_data->wheel_pulse[i];
           }
              else
              {
               pulse_delta[i] = -v_data->pre_wheel_pulse[i]+v_data->wheel_pulse[i];
              
              }
	}
	if (v_data->wheel_speed_rl<speed_up && v_data->wheel_speed_rl>speed_down)
	{
		n1=1;
	}
	else
	{
		n1=0;
	}
	if (v_data->wheel_speed_rr<speed_up && v_data->wheel_speed_rr>speed_down)
	{
		n2=1;
	}
	else
	{
		n2=0;
	}
	if (n1==0 && n2==0)
	{
		theta_offset=( pulse_delta[0]+ pulse_delta[1])*ratio/2.0/radius;
	}
	else
	{
		theta_offset = (n1* v_data->wheel_speed_rl / (radius + flag* half_wheel_width) + n2* v_data->wheel_speed_rr / (radius - flag* half_wheel_width))* g_PLD_time_Offset_in / (n1*1.0 + n2*1.0) * 1000 / 3.6;
	}
     
    return theta_offset;
       
}

#if 0
void VehicleMotion::get_new_point_from_Vhichle_data(Point2f pts[MAXPOINTNUM], COMMON_VEHICLE_DATA_SIMPLE * v_data, float g_PLD_time_Offset_in)
{
	int dri_sign = get_driving_dir(v_data);
	int turn_sign = get_turn_dir(v_data);
	float radius;
	steeringwheel_radius(v_data->steering_angle, v_data->shift_pos, radius);
	float theta_offset = turn_sign*get_yawrate_from_curvature(v_data)*g_PLD_time_Offset_in;
	v_data->wheel_pulse[rear_left_whl]
	v_data->pre_wheel_pulse[rear_left_whl]

	int shft_pos = v_data->shift_pos;
	float str_whl_angle = v_data->steering_angle;

	for (int i = 0; i < MAXPOINTNUM; i++)
	{
		Point2f point_src, point_dst;
		point_src = pts[i];
		if (shft_pos == 2)
		{
			if (str_whl_angle < 0)
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) + point_src.y*sin(ABS(theta_offset)) - radius*sin(ABS(theta_offset));
				point_dst.y = -point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) + radius*(1 - cos(ABS(theta_offset)));
			}
			else
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) - point_src.y*sin(ABS(theta_offset)) - radius*sin(ABS(theta_offset));
				point_dst.y = point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) - radius*(1 - cos(ABS(theta_offset)));
			}
		}
		else
		{
			if (str_whl_angle < 0)
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) - point_src.y*sin(ABS(theta_offset)) + radius*sin(ABS(theta_offset));
				point_dst.y = point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) + radius*(1 - cos(ABS(theta_offset)));
			}
			else
			{
				point_dst.x = point_src.x*cos(ABS(theta_offset)) + point_src.y*sin(ABS(theta_offset)) + radius*sin(ABS(theta_offset));
				point_dst.y = -point_src.x*sin(ABS(theta_offset)) + point_src.y*cos(ABS(theta_offset)) - radius*(1 - cos(ABS(theta_offset)));
			}
		}
		pts[i] = point_dst;
	}



}


#endif
