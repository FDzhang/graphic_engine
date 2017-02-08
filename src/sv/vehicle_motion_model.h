#ifndef __VEHICLE_MOTION_MODEL_H_
#define __VEHICLE_MOTION_MODEL_H_

//#include "../../source/utility/common/reuse.h"
//#include "..\utility\common\commondef.h"
#include "math_common.h"
#include "vehicle_motion.h"
#include "reuse_gpu.h"

#include "DataStruct.h"
#define CV_PI 3.1416926


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
private:


	

};

#endif
