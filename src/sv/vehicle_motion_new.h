#ifndef __VEHICLE_MOTION_NEW_H__
#define __VEHICLE_MOTION_NEW_H__

#include "reuse.h"
#include "bev_data_type.h"

#include <math.h>

#include "commondef.h"


#ifndef CV_PI
#define CV_PI 3.14159265358979323846264338327950288
#endif

#ifndef FLT_MIN
#define FLT_MIN 1e-30
#endif

#include <opencv_adapter.h>

class Vehicle_Motion_New
{
public:
    Vehicle_Motion_New(){
    }

    ~Vehicle_Motion_New(){
    }

    int8_t init(float32_t H, float32_t W, float32_t a[4], float32_t b[4]);
    
    void steeringwheel_wheelangle(const COMMON_VEHICLE_DATA& vhcl_can_data,
        float32_t &whl_angle_a, //inner tire
        float32_t &whl_angle_b  //outer tier
        );

    void traject_predict_world(const COMMON_VEHICLE_DATA vhcl_can_data, int32_t time_offset);

    void traject_predict_car(Point2f point_src, const COMMON_VEHICLE_DATA& vhcl_can_data, Point2f &point_dst, float32_t time_offset);

    void get_motion_transform(float32_t cx, float32_t cy, float32_t ppmmx, float32_t ppmmy, float32_t *t );

    void steeringwheel_radius(float32_t str_whl_angle, int8_t shft_pos, float32_t &radius);

    void pos_predict_car(
        Point2f point_src,
        Point2f &point_dst,
        float32_t radius,
        float32_t angle,
        int8_t shift_pos,
        int8_t turning_status
        );

    void radius_steeringwheel(
        float32_t &str_whl_angle,
        float32_t radius,
        int8_t shift_pos,
        int8_t turning_status
        );

    float32_t get_distance_from_pulse();

    enum{VEH_SHIFT_P=0, VEH_SHIFT_N, VEH_SHIFT_D, VEH_SHIFT_R, VEH_SHIFT_INVALID};
    enum{VEH_TURNING_RIGHT=0, VEH_TURNING_LEFT};
                        
    float32_t track; //distance from origin to the current position
    float32_t theta; //heading degree of vehicle
    Point2f pos; //position of vehicle in world coordinate

private:


    enum{_Forward_R = 0, _Forward_L, _Backward_R, _Backward_L};
    float32_t H, W;
    float32_t _a[4], _b[4];
    int16_t pulse_pre[2], pulse_cur[2], pulse_delta[2];
};

#endif
