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