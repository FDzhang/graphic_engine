#ifndef __SV_TIME_STITCHER_H__
#define __SV_TIME_STITCHER_H__

#define MAX_VEHICLE_SPEED        30
#define SPEED_RATIO              0.8
#define TRACK_LIMIT              5
#define EPSINON                  0.000001
#define IMG_NUM_LIMIT            5

#include "vehicle_motion_new.h"
#include "camera_model.h"
#include "reuse.h"
#include "commondef.h"
#include <math.h>
#include "config_vehicle_motion.h"
#include "TS_config.h"

//using namespace cv;
#include <deque>

typedef struct RT_T
{
    float t[6];
}RT;

typedef struct tsRect_T
{
    int x;
    int y;
    int width;
    int height;

    tsRect_T(int _x = 0, int _y = 0, int w = 0, int h = 0) : x(_x), y(_y), width(w), height(h) {}
    tsRect_T(const CvRect& r) : x(r.x), y(r.y), width(r.width), height(r.height) {}
}tsRect;

class SVTimeStitcher
{
public:
    SVTimeStitcher(){}
    ~SVTimeStitcher(){}

    bool init();
    
    void update();
    
    //if failure, restart time stitcher
    void reset();
    //low beam lights detection
    bool lowBmAct();
    //dual-threshold for function failure judgment
    bool judge_work_speed();
    //gear shifting detection
    bool judge_shift_pos();
    //threshold_ts_x and threshold_ts_y out of range protection
    bool judge_blind_area();

	//add new bev_img and T to deque
	void add_new_image();
	
	//update the dense LUT
	bool update_LUT(int pic, float *prevRT, int *pSIndex, int *pEIndex, int &pix_num, bool bCount, int &roi_pix_num, bool order_flag = true);
	//count pixels in front or rear blind area
	int pixels_in_threshold_ts_v(float *t, bool order_flag);
	//empty the dense LUT every time
	void empty_LUT();
	//fill up the LUT if need
	void inpaint_LUT();
	//calculate relative vehicle motion model
	void update_RT(RT &prevRT, float *currRT);
	//update the LUT for GPU in the end of the main function
	void update_GPU_LUT();
	//align mAdaptCoordY with mCoordY at the begin of every turn
	void update_CoordY();

    void GetVertexBuffer(float **pVertex, unsigned int &bufSize);

    void GetIndexBuffer(unsigned short **pIndex, unsigned int &bufSize);

    bool GetNewImgFlag();

    bool GetResetFlag();
    
    LUT_Car m_gpu_lut;
    unsigned short *m_pIndex;
    
//    LUT_Car* get_LUT(){return &m_gpu_lut;}		
//	unsigned short* get_pIndex(){return m_pIndex;}

private:
    std::deque<RT> prev_T;

    float32_t ppmmx, ppmmy;
    float32_t cx, cy;
    int32_t iH, iW;
    tsRect carRect;
    tsRect carRealRect;
    COMMON_VEHICLE_DATA* m_pvadat;
    int32_t threshold_ts_u, threshold_ts_v_rear, threshold_ts_v_front;
    tsRect roi_ts;
    Vehicle_Motion_New vhcl_motion;

	bool m_bEnabled;
	
	float32_t threshold_ts_x_front;
	float32_t threshold_ts_x_rear;
	float32_t threshold_ts_y;
	int32_t bottom_row;
	int32_t right_col;
	int16_t m_last_shift_pos;
	int16_t m_last_lowBmAct;
	float m_pix_num_ratio_D;
	float m_pix_num_ratio_R;
	int m_iFrame;
	//int m_gpu_step_W;
	//int m_gpu_step_H;
	LUT_Car m_dense_lut;
	int mCoordX[GPU_LUT_W];
	int mCoordY[GPU_LUT_H];
};

enum ShiftPos
{
    Parking = 0,
    Neutral = 1,
    Driving = 2,
    Reverse = 3,
    Exception = 4
};

enum LowBeamAct
{
    Closed = 0,
    LowBmAct = 1,
    HighBmAct = 2
};
#endif//__TIMR_STITCHER_H__