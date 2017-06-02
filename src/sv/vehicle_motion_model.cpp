//#include "../../source/utility/common/reuse.h"
//#include "..\utility\common\commondef.h"
#include "vehicle_motion_model.h"
#include <math.h>
#include <stdlib.h>
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
	SteerWheel2Radius(str_whl_angle, shft_pos, radius);


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
	SteerWheel2Radius(str_whl_angle, shft_pos, radius);

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
			}
			else
			{
				float speed = -vhcl_can_data.wheel_speed_rl/3.6f;
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
			}
		}
		else
		{
			if(str_whl_angle<0)
			{
				float speed = -vhcl_can_data.wheel_speed_rr/3.6f;
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
			}
			else
			{
				float speed = -vhcl_can_data.wheel_speed_rl/3.6f;
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
			}
		}

	Mat_Mul_3by3(m, t, m);
}


void VehicleMotion::getPos2Kframe(
	CvPoint2D32f pointIn,
	float32_t m[9],
	CvPoint2D32f &pointOut
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
	#if 1
#define COEFF_LINEAR_FR 0.056620
#define COEFF_LINEAR_FL 0.056248
#define COEFF_LINEAR_RR 0.047870
#define COEFF_LINEAR_RL 0.065278

#define COEFF_CONST_FR -0.029849
#define COEFF_CONST_FL -0.023264
#define COEFF_CONST_RR  2.981121
#define COEFF_CONST_RL -3.054503
#else


#define COEFF_LINEAR_FR 0.06215
#define COEFF_LINEAR_FL 0.06011
#define COEFF_LINEAR_RR 0.06042
#define COEFF_LINEAR_RL 0.06263
	
#define COEFF_CONST_FR 0.172
#define COEFF_CONST_FL 0.4169
#define COEFF_CONST_RR  0.3349
#define COEFF_CONST_RL -0.1307
#endif
	_a[0] = COEFF_LINEAR_FR;
	_a[1] = COEFF_LINEAR_FL;
	_a[2] = COEFF_LINEAR_RR;
	_a[3] = COEFF_LINEAR_RL;

	_b[0] = COEFF_CONST_FR;
	_b[1] = COEFF_CONST_FL;
	_b[2] = COEFF_CONST_RR;
	_b[3] = COEFF_CONST_RL;
	if (shft_pos == 2)
	{
		if (str_whl_angle < 0) // steering wheel turns clockwisely
		{
			radius = H / tan(ABS(_a[_Forward_R] * (-str_whl_angle) + FLT_MIN + _b[_Forward_R])*CV_PI / 180) - W / 2;
		}
		else
		{
			radius = H / tan(ABS(_a[_Forward_L] * str_whl_angle + FLT_MIN + _b[_Forward_L])*CV_PI / 180) - W / 2;
		}
	}
	else
	{
		if (str_whl_angle < 0) // steering wheel turns anti-clockwisely
		{
			radius = H / tan(ABS(_a[_Backward_R] * (-str_whl_angle) + FLT_MIN + _b[_Backward_R])*CV_PI / 180) - W / 2;
		}
		else
		{
			radius = H / tan(ABS(_a[_Backward_L] * str_whl_angle + FLT_MIN + _b[_Backward_L])*CV_PI / 180) - W / 2;
		}
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



	return fabs(speed) / Radius;
}

float VehicleMotion::get_distance_from_pulse(COMMON_VEHICLE_DATA_SIMPLE * v_data)
{
    int16_t pulse_curent[2];
	int16_t pulse_pre[2];
	int16_t pulse_delta[2];
    
	pulse_curent[0]=v_data->wheel_pulse[rear_left_whl];
	pulse_pre[0]=v_data->pre_wheel_pulse[rear_left_whl];
	pulse_curent[1]=v_data->wheel_pulse[rear_right_whl];
	pulse_pre[1]=v_data->pre_wheel_pulse[rear_right_whl];

    for(int i=0;i<2;i++)
    {
	    if(pulse_curent[i]<pulse_pre[i])
	    {
	        pulse_delta[i] = -pulse_pre[i]+1024+pulse_curent[i];
	    }
		else
		{
	        pulse_delta[i] = -pulse_pre[i]+pulse_curent[i];
		
		}
    }
    return((pulse_delta[0] +pulse_delta[1] )*0.023);
	
}

void VehicleMotion::get_new_point_from_Vhichle_data(Point2f pts[MAXPOINTNUM], COMMON_VEHICLE_DATA_SIMPLE * v_data, float g_PLD_time_Offset_in)
{
	int dri_sign = get_driving_dir(v_data);
	int turn_sign = get_turn_dir(v_data);
	float radius;
	steeringwheel_radius(v_data->steering_angle, v_data->shift_pos, radius);
	float theta_offset = turn_sign*get_yawrate_from_curvature(v_data)*g_PLD_time_Offset_in;

    //theta_offset = turn_sign*get_distance_from_pulse(v_data)/radius;
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
