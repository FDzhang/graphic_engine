#ifndef _TS_CONFIG_H
#define _TS_CONFIG_H

#define IMG_NUM_LIMIT 5
#define VIEW_RANGE 4
#define THRESHOLD_TS_X_FRONT 1.0f
#define THRESHOLD_TS_X_REAR  2.0f
#define THRESHOLD_TS_Y       2.0f
#define PIX_NUM_RATIO_D      0.6f
#define PIX_NUM_RATIO_R      0.9f
#define GPU_LUT_W            21
#define GPU_LUT_H            41

typedef struct Pt_T
{
	float coord[2];
	float weight;
}Pt;

typedef struct TabCar_T
{
	float dstPt[3];
	Pt srcPt[IMG_NUM_LIMIT];
}TabCar;

typedef struct LUT_Car_T
{
	bool reset_flag;
	bool new_img_flag;
	unsigned int timeStamp;
	int w, h;
	TabCar *car_list;
}LUT_Car;

#endif //_TS_CONFIG_H