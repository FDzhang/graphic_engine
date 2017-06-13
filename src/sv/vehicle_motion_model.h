#ifndef __VEHICLE_MOTION_MODEL_H_
#define __VEHICLE_MOTION_MODEL_H_

//#include "../../source/utility/common/reuse.h"
//#include "..\utility\common\commondef.h"
#include "math_common.h"
#include "vehicle_motion.h"
#include "reuse_gpu.h"

#include "DataStruct.h"
#define CV_PI 3.1416926

#define  MAXPOINTNUM 1
#define FLT_MIN 1.1e-30f

#ifndef ABS
#define ABS(x) ((x) >= 0 ? (x):-(x))
#endif

#ifndef MAX
#define MAX(x, y) ((x) >= (y)? (x):(y))
#define MIN(x, y) ((x) > (y)?(y):(x))
#endif
/* constructs CvPoint2D32f structure. */
inline  CvPoint2D32f  cvPoint2D32f(float32_t x, float32_t y)
{
	CvPoint2D32f p;

	p.x = (float)x;
	p.y = (float)y;

	return p;
}


class VehicleMotion
{
public:
	VehicleMotion(){
	}

	~VehicleMotion(){
	}

	//void pos_predict_
	void SteerWheel2Radius(
		float32_t str_whl_angle,
		int shft_pos,
		float32_t &radius
		);

	void revMotion2KframePredictVCS(
		COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data, //CAN information
		int32_t time_offset, //
		float32_t &track, //
		float32_t t[9],
		float32_t m[9],
		int32_t &flag,  //flag of key frame updating
		float32_t thresh_dist_kframe
		);
void Motion2KframePredictVCS(
	COMMON_VEHICLE_DATA_SIMPLE vhcl_can_data,
	int32_t time_offset,
	float32_t &track,
	float32_t t[9],
	float32_t m[9],
	int32_t &flag,
	float32_t thresh_dist_kframe
	);
	void getPos2Kframe(
		CvPoint2D32f pointIn,
		float32_t m[9],
		CvPoint2D32f &pointOut
		);
	
	float get_distance_from_pulse(COMMON_VEHICLE_DATA_SIMPLE * v_data);
	void get_new_point_from_Vhichle_data(Point2f pts[MAXPOINTNUM], COMMON_VEHICLE_DATA_SIMPLE * v_data, float g_PLD_time_Offset_in);
private:
	int get_driving_dir(COMMON_VEHICLE_DATA_SIMPLE * v_data);
	int get_turn_dir(COMMON_VEHICLE_DATA_SIMPLE * v_data);
		void steeringwheel_radius(
			float str_whl_angle,
			int shft_pos,
			float &radius
			);//convert from steering wheel angle to steering radius

	float get_yawrate_from_curvature(COMMON_VEHICLE_DATA_SIMPLE * v_data);
	float get_theta_from_multi_pulse(COMMON_VEHICLE_DATA_SIMPLE * v_data,float radius,int turn_sign);

	

};

#endif
