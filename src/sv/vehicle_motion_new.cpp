#include <string.h>
#include "vehicle_motion_new.h"
#include "AVMData.h"
#include "gpu_log.h"
#include "bev_data_type.h"


int8_t Vehicle_Motion_New::init(
                    float32_t H, //vehicle wheel base, mm
                    float32_t W, //vehicle width, mm
                    float32_t a[4], //coefficient
                    float32_t b[4] //coefficient
                    )
    {
        this->H = H/1000;
        this->W = W/1000;
        memcpy(_a, a, sizeof(float32_t)*4);
        memcpy(_b, b, sizeof(float32_t)*4);
        theta = track = 0;
        memset(pulse_cur, 0, 2 * sizeof(pulse_cur));
        memset(pulse_pre, 0, 2 * sizeof(pulse_pre));
        memset(pulse_delta, 0, 2 * sizeof(pulse_delta));
        return true;
    }

void Vehicle_Motion_New::steeringwheel_radius(
                          float32_t str_whl_angle, 
                          int8_t shft_pos,
                          float32_t &radius
                          )//convert from steering wheel angle to steering radius
    {
        if(shft_pos == 2)
        {
            if(str_whl_angle<0) // steering wheel turns clockwisely
            {
                //radius = H/tan(ABS(_a[_Forward_R]*(-str_whl_angle)+FLT_MIN+_b[_Forward_R])*CV_PI/180)-W/2;
                radius = 2.750 / tan((3.269*(1.0e-8)*(-str_whl_angle) *(-str_whl_angle) *(-str_whl_angle) - 2.488*(1.0e-5)*(-str_whl_angle) *(-str_whl_angle)
                    + 0.06131 * (-str_whl_angle) + 0.004912)*CV_PI / 180) - 0.9195;        
            }
            else
            {
                //radius = H/tan(ABS(_a[_Forward_L]*str_whl_angle+FLT_MIN+_b[_Forward_L])*CV_PI/180)-W/2;
                radius = 2.750 / tan((3.466*(1.0e-8)*(str_whl_angle)*(str_whl_angle)*(str_whl_angle)+2.798*(1.0e-5)*(str_whl_angle)*(str_whl_angle)
                    +0.05994 * (str_whl_angle)+0.0446)*CV_PI / 180) + 0.9195;

            }
        }
        else
        {
            if(str_whl_angle<0) // steering wheel turns anti-clockwisely
            {
                //radius = H/tan(ABS(_a[_Backward_R]*(-str_whl_angle)+FLT_MIN+_b[_Backward_R])*CV_PI/180)-W/2;
                radius = 2.750 / tan((6.667*(1.0e-8)*(-str_whl_angle) *(-str_whl_angle) *(-str_whl_angle) - 5.163*(1.0e-5)*(-str_whl_angle) *(-str_whl_angle)
                    + 0.06626 * (-str_whl_angle) + 0.007778)*CV_PI / 180) - 0.9195;

            }
            else
            {
                //radius = H/tan(ABS(_a[_Backward_L]*str_whl_angle+FLT_MIN+_b[_Backward_L])*CV_PI/180)-W/2;
                radius = 2.750 / tan((8.628*(1.0e-8)*(str_whl_angle)*(str_whl_angle)*(str_whl_angle)-1.086*(1.0e-5)*(str_whl_angle)*(str_whl_angle)
                    +0.06691 * (str_whl_angle)+0.005639)*CV_PI / 180) + 0.9195;

            }
        }
    }

float32_t Vehicle_Motion_New::get_distance_from_pulse()
{
    unsigned short wheel_pulse[4];
    
    AVMData::GetInstance()->m_p_can_data->Get_Wheel_Pulse(wheel_pulse);
    // if(wheel_pulse[rear_left_whl] == 0 && wheel_pulse[rear_right_whl] == 0)
    // {
    //     wheel_pulse[rear_left_whl] = pulse_cur[0];
    //     wheel_pulse[rear_right_whl] = pulse_cur[1];
    // }
    if (pulse_cur[0] == 0 && pulse_cur[1] == 0)
    { 
//        pulse_cur[0] = vhcl_can_data.WRSLNDWhlDistPCntr;
//        
//        pulse_cur[1] = vhcl_can_data.WRSRNDWhlDistPCntr;
        pulse_cur[0] = wheel_pulse[rear_left_whl];
        pulse_cur[1] = wheel_pulse[rear_right_whl];

        pulse_pre[0] = pulse_cur[0];
        pulse_pre[1] = pulse_cur[1];
        return 0;
    }
    else
    { 
//        pulse_cur[0] = vhcl_can_data.WRSLNDWhlDistPCntr;
//        
//        pulse_cur[1] = vhcl_can_data.WRSRNDWhlDistPCntr;

        pulse_cur[0] = wheel_pulse[rear_left_whl];
        pulse_cur[1] = wheel_pulse[rear_right_whl];    

        for (int i = 0; i<2; i++)
        {
            if (pulse_cur[i]<pulse_pre[i])
            {
                pulse_delta[i] = -pulse_pre[i] + 1024 + pulse_cur[i];
            }
            else
            {
                pulse_delta[i] = -pulse_pre[i] + pulse_cur[i];

            }
        }
        pulse_pre[0] = pulse_cur[0];
        pulse_pre[1] = pulse_cur[1];

        return((pulse_delta[0] + pulse_delta[1])*0.023);//??m
    }
    

}

void Vehicle_Motion_New::steeringwheel_wheelangle(
                                 const COMMON_VEHICLE_DATA& vhcl_can_data,
                                 float32_t &whl_angle_a, //inner tire
                                 float32_t &whl_angle_b  //outer tier
                                 )// convert from steering wheel angle to wheel turning angle
    {
        int8_t shft_pos = vhcl_can_data.shift_pos;
        float32_t str_whl_angle = vhcl_can_data.steering_angle;
        float32_t radius = 0;

        if(shft_pos == 2)
        {
            if(str_whl_angle<0)
            {
                radius = H/tan(ABS(_a[_Forward_R]*(-str_whl_angle)+FLT_MIN+_b[_Forward_R])*CV_PI/180)-W/2;
                whl_angle_b = -atan(H/(radius+W/2));
                whl_angle_a = -atan(H/(radius-W/2));
            }
            else
            {
                radius = H/tan(ABS(_a[_Forward_L]*str_whl_angle+FLT_MIN+_b[_Forward_L])*CV_PI/180)-W/2;
                whl_angle_a = atan(H/(radius+W/2));
                whl_angle_b = atan(H/(radius-W/2));
            }
        }
        else
        {
            if(str_whl_angle<0)
            {
                radius = H/tan(ABS(_a[_Backward_R]*(-str_whl_angle)+FLT_MIN+_b[_Backward_R])*CV_PI/180)-W/2;
                whl_angle_b = -atan(H/(radius+W/2));
                whl_angle_a = -atan(H/(radius-W/2));
            }
            else
            {
                radius = H/tan(ABS(_a[_Backward_L]*str_whl_angle+FLT_MIN+_b[_Backward_L])*CV_PI/180)-W/2;
                whl_angle_a = atan(H/(radius+W/2));
                whl_angle_b = atan(H/(radius-W/2));
            }
        }
    }

void Vehicle_Motion_New::traject_predict_world(
                               COMMON_VEHICLE_DATA vhcl_can_data,
                               int32_t time_offset //current timestamp-previous timestamp, us
                               ) //vehicle trajectory depict in world coordinate
    {
        float32_t radius = 0;
        int8_t shft_pos = vhcl_can_data.shift_pos;
        float32_t str_whl_angle = vhcl_can_data.steering_angle;
        steeringwheel_radius(str_whl_angle, shft_pos, radius);
        float32_t speed = (vhcl_can_data.wheel_speed_rl + vhcl_can_data.wheel_speed_rr)/2/3.6f;
        //float32_t track_offset = time_offset/1000000.0f*speed;
        float32_t track_offset = get_distance_from_pulse();

        float32_t x_offset, y_offset;


        if(shft_pos == 2)
        {
            if(str_whl_angle<0)
            {
                float32_t theta_offset = track_offset/radius;

                x_offset = radius*(1-cos(ABS(theta_offset)));
                y_offset = radius*sin(ABS(theta_offset));

                pos.x = pos.x+cos(theta)*x_offset+sin(theta)*y_offset;
                pos.y = pos.y-sin(theta)*x_offset+cos(theta)*y_offset;

                theta += theta_offset;
            }
            else
            {
                float32_t theta_offset = -track_offset/radius;

                x_offset = -radius*(1-cos(ABS(theta_offset)));
                y_offset = radius*sin(ABS(theta_offset));
            
                pos.x = pos.x+cos(theta)*x_offset+sin(theta)*y_offset;
                pos.y = pos.y-sin(theta)*x_offset+cos(theta)*y_offset;

                theta += theta_offset;
            }
        }
        else
        {
            if(str_whl_angle<0)
            {
                float32_t theta_offset = -track_offset/radius;

                x_offset = radius*(1-cos(ABS(theta_offset)));
                y_offset = -radius*sin(ABS(theta_offset));

                pos.x = pos.x+cos(theta)*x_offset+sin(theta)*y_offset;
                pos.y = pos.y-sin(theta)*x_offset+cos(theta)*y_offset;

                theta += theta_offset;

            }
            else
            {
                float32_t theta_offset = track_offset/radius;

                x_offset = -radius*(1-cos(ABS(theta_offset)));
                y_offset = -radius*sin(ABS(theta_offset));

                pos.x = pos.x+cos(theta)*x_offset+sin(theta)*y_offset;
                pos.y = pos.y-sin(theta)*x_offset+cos(theta)*y_offset;

                theta += theta_offset;

            }
        }

        
    }

void Vehicle_Motion_New::traject_predict_car(Point2f point_src,
                             const COMMON_VEHICLE_DATA& vhcl_can_data,
                             Point2f &point_dst,
                             float32_t time_offset)
{
    int8_t shft_pos = vhcl_can_data.shift_pos;
    float32_t str_whl_angle = vhcl_can_data.steering_angle;
    float32_t radius=0;
    steeringwheel_radius(str_whl_angle, shft_pos, radius);
    float32_t speed = (vhcl_can_data.wheel_speed_rl + vhcl_can_data.wheel_speed_rr)/2/3.6f;
    //float32_t track_offset = time_offset/1000000.0f*speed;
    float32_t track_offset = get_distance_from_pulse();
    float32_t theta_offset = track_offset/radius;

    if(shft_pos == 2)
        {
            if(str_whl_angle<0)
            {
                point_dst.x = point_src.x*cos(ABS(theta_offset))+point_src.y*sin(ABS(theta_offset))-radius*sin(ABS(theta_offset));
                point_dst.y = -point_src.x*sin(ABS(theta_offset))+point_src.y*cos(ABS(theta_offset))+radius*(1-cos(ABS(theta_offset)));
            }
            else
            {
                point_dst.x = point_src.x*cos(ABS(theta_offset))-point_src.y*sin(ABS(theta_offset))-radius*sin(ABS(theta_offset));
                point_dst.y = point_src.x*sin(ABS(theta_offset))+point_src.y*cos(ABS(theta_offset))-radius*(1-cos(ABS(theta_offset)));
            }
        }
        else
        {
            if(str_whl_angle<0)
            {
                point_dst.x = point_src.x*cos(ABS(theta_offset))-point_src.y*sin(ABS(theta_offset))+radius*sin(ABS(theta_offset));
                point_dst.y = point_src.x*sin(ABS(theta_offset))+point_src.y*cos(ABS(theta_offset))+radius*(1-cos(ABS(theta_offset)));
            }
            else
            {
                point_dst.x = point_src.x*cos(ABS(theta_offset))+point_src.y*sin(ABS(theta_offset))+radius*sin(ABS(theta_offset));
                point_dst.y = -point_src.x*sin(ABS(theta_offset))+point_src.y*cos(ABS(theta_offset))-radius*(1-cos(ABS(theta_offset)));
            }
        }
}


void Vehicle_Motion_New::get_motion_transform(float32_t cx, float32_t cy,float32_t ppmmx, float32_t ppmmy, float32_t* t)
    {
        float steer_angle;
        unsigned char gear_state;
        float left_wheel_speed=0,right_wheel_speed=0;
        float rear_left_wheel_speed=0,rear_right_wheel_speed=0;

        float yawRate = 0.0;
        AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);		
    	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
    	AVMData::GetInstance()->m_p_can_data->Get_Wheel_Speed(&right_wheel_speed, &left_wheel_speed, &rear_right_wheel_speed, &rear_left_wheel_speed);	

//        Log_Error("=================steer_angle = %f", steer_angle);
//        Log_Error("=================gear_state = %d", gear_state);
//        Log_Error("=================rear_wheel_speed = %f, %f", rear_right_wheel_speed,rear_left_wheel_speed);
//    	AVMData::GetInstance()->m_p_can_data->Get_Yaw_Rate(&yawRate);
    
//        int8_t shft_pos = vhcl_can_data.shift_pos;
//        float32_t str_whl_angle = vhcl_can_data.steering_angle;
//        float32_t radius=0;
//        steeringwheel_radius(str_whl_angle, shft_pos, radius);
//        float32_t speed = (vhcl_can_data.wheel_speed_rl + vhcl_can_data.wheel_speed_rr)/2/3.6f;
//        //float32_t track_offset = time_offset/1000000.0f*speed;
//        float32_t track_offset = get_distance_from_pulse(vhcl_can_data);
//        track += track_offset;
//        float32_t theta_offset = track_offset/radius;


        
        int8_t shft_pos = gear_state;
        float32_t str_whl_angle = steer_angle;
        float32_t radius=0;
        steeringwheel_radius(str_whl_angle, shft_pos, radius);
        float32_t speed = (rear_left_wheel_speed + rear_right_wheel_speed)/2/3.6f;
        //float32_t track_offset = time_offset/1000000.0f*speed;
        float32_t track_offset = get_distance_from_pulse();
        track += track_offset;
        float32_t theta_offset = track_offset/radius;

        if(shft_pos == 2)
        {
            if(str_whl_angle<0)
            {
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
        
    }

void Vehicle_Motion_New::pos_predict_car(
                         Point2f point_src,
                         Point2f &point_dst,
                         float32_t radius,
                         float32_t angle,
                         int8_t shift_pos,
                         int8_t turning_status
                         )
{
    if(shift_pos == VEH_SHIFT_D)
        {
            if(turning_status == VEH_TURNING_RIGHT)
            {
                point_dst.x = point_src.x*cosf(ABS(angle))+point_src.y*sin(ABS(angle))-radius*sin(ABS(angle));
                point_dst.y = -point_src.x*sin(ABS(angle))+point_src.y*cos(ABS(angle))+radius*(1-cos(ABS(angle)));
            }
            else
            {
                point_dst.x = point_src.x*cos(ABS(angle))-point_src.y*sin(ABS(angle))-radius*sin(ABS(angle));
                point_dst.y = point_src.x*sin(ABS(angle))+point_src.y*cos(ABS(angle))-radius*(1-cos(ABS(angle)));
            }
        }
        else
        {
            if(turning_status == VEH_TURNING_RIGHT)
            {
                point_dst.x = point_src.x*cos(ABS(angle))-point_src.y*sin(ABS(angle))+radius*sin(ABS(angle));
                point_dst.y = point_src.x*sin(ABS(angle))+point_src.y*cos(ABS(angle))+radius*(1-cos(ABS(angle)));
            }
            else
            {
                point_dst.x = point_src.x*cos(ABS(angle))+point_src.y*sin(ABS(angle))+radius*sin(ABS(angle));
                point_dst.y = -point_src.x*sin(ABS(angle))+point_src.y*cos(ABS(angle))-radius*(1-cos(ABS(angle)));
            }
        }
}

void Vehicle_Motion_New::radius_steeringwheel(
                            float32_t &str_whl_angle,
                            float32_t radius,
                            int8_t shift_pos,
                            int8_t turning_status
                            )
{
    if(shift_pos == VEH_SHIFT_D)
        {
            if(turning_status == VEH_TURNING_RIGHT)
            {
                str_whl_angle = -ABS(atan(H/(radius+W/2))*180/CV_PI-FLT_MIN-_b[_Forward_R])/_a[_Forward_R];
            }
            else
            {
                str_whl_angle = ABS(atan(H/(radius+W/2))*180/CV_PI-FLT_MIN-_b[_Forward_L])/_a[_Forward_L];
            }
        }
        else
        {
            if(turning_status == VEH_TURNING_RIGHT)
            {
                str_whl_angle = -ABS(atan(H/(radius+W/2))*180/CV_PI-FLT_MIN-_b[_Backward_R])/_a[_Backward_R];
            }
            else
            {
                str_whl_angle = ABS(atan(H/(radius+W/2))*180/CV_PI-FLT_MIN-_b[_Backward_L])/_a[_Backward_L];
            }
        }
}
