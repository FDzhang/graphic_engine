#include <iostream>
#include "commondef.h"
#include <string.h>

#include "SVTimeStitcher.h"
#include "AVMData.h"
#include "gpu_log.h"

using namespace std;

bool SVTimeStitcher::init()
{
	Smc_Cal_T *_avm_mc;
	AVMData::GetInstance()->GetSmc(&_avm_mc);

    float32_t bevW =(float32_t)( _avm_mc->bev_stitch_param.view_param[2].view_range
        + _avm_mc->bev_stitch_param.view_param[3].view_range
        + _avm_mc->veh_param.veh_width);

    //world width in bev image
    float32_t bevH = (float32_t)(_avm_mc->bev_stitch_param.view_param[0].view_range
        + _avm_mc->bev_stitch_param.view_param[1].view_range
        + _avm_mc->veh_param.veh_length);

    int32_t   imgW = _avm_mc->bev_stitch_param.bev_stitch_img_width;  //bev image width
    int32_t   imgH = _avm_mc->bev_stitch_param.bev_stitch_img_height; //bev image height  
    float32_t vehH = (float32_t)(_avm_mc->veh_param.veh_length);
    float32_t vehW = (float32_t)(_avm_mc->veh_param.veh_width);
    float32_t rear2Bumper = (float32_t)(_avm_mc->veh_param.veh_rwheel2tail) ;
    float32_t blind_front = (float32_t)(_avm_mc->bev_stitch_param.view_param[0].blind_range);
    float32_t blind_rear  = (float32_t)(_avm_mc->bev_stitch_param.view_param[1].blind_range);
    float32_t blind_left = (float32_t)(_avm_mc->bev_stitch_param.view_param[2].blind_range);
    float32_t blind_right = (float32_t)(_avm_mc->bev_stitch_param.view_param[3].blind_range);
    
    ppmmx = bevH / imgH; 
    ppmmy = bevW / imgW;
    int32_t   carW = int32_t(vehW / ppmmy);
    int32_t   carH = int32_t(vehH / ppmmx);
    
    carRealRect = cvRect(int32_t(imgW/2-carW/2),int32_t( imgH/2-carH/2), int32_t(carW), int32_t(carH));   
    carRect = cvRect(int32_t(imgW/2-carW/2-blind_left/ppmmy),int32_t( imgH/2-carH/2-blind_front/ppmmx), int32_t(carW+(blind_left+blind_right)/ppmmy), int32_t(carH+(blind_front+blind_rear)/ppmmx));
  
    cx = int32_t((imgH + carRealRect.height)/2-(rear2Bumper)/ppmmx);
    cy = int32_t(imgW/2);
    
//    cx = _cx;
//    cy = _cy;
    
    ppmmx = ppmmx / 1000;
    ppmmy = ppmmy / 1000;
//    carRect = _carRect;
//    carRealRect = _carRealRect;
    //iH = _iH * (VIEW_RANGE * 2 + _avm_mc->veh_param.veh_length) / (_avm_mc->bev_stitch_param.view_param[0].view_range + _avm_mc->bev_stitch_param.view_param[1].view_range + _avm_mc->veh_param.veh_length);
    //iW = _iW * (VIEW_RANGE * 2 + _avm_mc->veh_param.veh_width) / (_avm_mc->bev_stitch_param.view_param[2].view_range + _avm_mc->bev_stitch_param.view_param[3].view_range + _avm_mc->veh_param.veh_width);
    iH = imgH;
    iW = imgW;
    vhcl_motion.track = 0;
    threshold_ts_u = (int32_t)floor(THRESHOLD_TS_Y / ppmmy);
    threshold_ts_v_front = (int32_t)floor(THRESHOLD_TS_X_FRONT / ppmmx);
    threshold_ts_v_rear = (int32_t)floor(THRESHOLD_TS_X_REAR / ppmmx);

    float32_t H = _avm_mc->veh_param.veh_axis_length;
    float32_t W = vehW;
    float32_t a[4], b[4];
    a[0] = (float32_t)COEFF_LINEAR_FR;
    a[1] = (float32_t)COEFF_LINEAR_FL;
    a[2] = (float32_t)COEFF_LINEAR_RR;
    a[3] = (float32_t)COEFF_LINEAR_RL;

    b[0] = (float32_t)COEFF_CONST_FR;
    b[1] = (float32_t)COEFF_CONST_FL;
    b[2] = (float32_t)COEFF_CONST_RR;
    b[3] = (float32_t)COEFF_CONST_RL;

    vhcl_motion.init(H, W, a, b);

    
    threshold_ts_x_front = THRESHOLD_TS_X_FRONT;
    threshold_ts_x_rear = THRESHOLD_TS_X_REAR;
    threshold_ts_y = THRESHOLD_TS_Y;
    m_bEnabled = true;
    m_last_shift_pos = Parking;
    m_last_lowBmAct = Closed;
    //boundary of carRect
    bottom_row = carRect.y + carRect.height - 1;
    right_col = carRect.x + carRect.width - 1;
    if (carRect.x - threshold_ts_u > 0 && carRect.y - threshold_ts_v_front > 0)
    {
        roi_ts = tsRect(carRect.x - threshold_ts_u, carRect.y - threshold_ts_v_front, carRect.width + 2 * threshold_ts_u, carRect.height + threshold_ts_v_front + threshold_ts_v_rear);
    }
    else
    {
        roi_ts = carRect;
    }
    m_pix_num_ratio_D = PIX_NUM_RATIO_D;
    m_pix_num_ratio_R = PIX_NUM_RATIO_R;
    m_iFrame = -1;

	//dense LUT initialization
	m_dense_lut.w = carRect.width;
	m_dense_lut.h = carRect.height;
	m_dense_lut.car_list = (TabCar*)malloc(m_dense_lut.w * m_dense_lut.h * sizeof(TabCar));
	if (NULL == m_dense_lut.car_list)
	{
		return 0;
	}
	memset(m_dense_lut.car_list, 0, m_dense_lut.w * m_dense_lut.h * sizeof(TabCar));
	/*float *pDstPt = m_dense_lut.car_list->dstPt;
	float recipX = (float)2 / (m_dense_lut.w - 1);
	float recipY = (float)2 / (m_dense_lut.h - 1);
	float yCoord = 1.0f;
	int step = sizeof(TabCar) / sizeof(float);
	for (int i = 0; i < m_dense_lut.h; i++)
	{
		float xCoord = -1.0f;
		for (int j = 0; j < m_dense_lut.w; j++)
		{
			*pDstPt = xCoord;
			*(pDstPt + 1) = yCoord;
			xCoord += recipX;
			pDstPt += step;
		}
		yCoord -= recipY;
	}*/
	m_dense_lut.timeStamp = 0;
	m_dense_lut.new_img_flag = true;
	m_dense_lut.reset_flag = false;

	//GPU LUT initialization
	m_gpu_lut.w = GPU_LUT_W;
	m_gpu_lut.h = GPU_LUT_H;
	m_gpu_lut.car_list = (TabCar*)malloc(m_gpu_lut.w * m_gpu_lut.h * sizeof(TabCar));
	if (NULL == m_gpu_lut.car_list)
	{
		return 0;
	}
	memset(m_gpu_lut.car_list, 0, m_gpu_lut.w * m_gpu_lut.h * sizeof(TabCar));
	float *pDstPt = m_gpu_lut.car_list->dstPt;
	float recipX = (float)2 / (m_gpu_lut.w - 1);
	float recipY = (float)2 / (m_gpu_lut.h - 1);
	float yCoord = 1.0f;
	int step = sizeof(TabCar) / sizeof(float);
	for (int i = 0; i < m_gpu_lut.h; i++)
	{
		float xCoord = -1.0f;
		for (int j = 0; j < m_gpu_lut.w; j++)
		{
			*pDstPt = xCoord;
			*(pDstPt + 1) = yCoord;
			xCoord += recipX;
			pDstPt += step;
		}
		yCoord -= recipY;
	}
	m_gpu_lut.timeStamp = 0;
	m_gpu_lut.new_img_flag = true;
	m_gpu_lut.reset_flag = false;

	//mCoordX and mCoordY initialization
	float ratioX = (float)(m_dense_lut.w - 1) / (m_gpu_lut.w - 1);
	for (int i = 0; i < m_gpu_lut.w; i++)
	{
		int coordX = (int)round(ratioX*i);
		if (m_gpu_lut.w - 1 == i)
		{
			coordX = m_dense_lut.w - 1;
		}
		mCoordX[i] = coordX;
	}
	float ratioY = (float)(m_dense_lut.h - 1) / (m_gpu_lut.h - 1);
	for (int i = 0; i < m_gpu_lut.h; i++)
	{
		int coordY = (int)round(ratioY*i);
		if (m_gpu_lut.h - 1 == i)
		{
			coordY = m_dense_lut.h - 1;
		}
		mCoordY[i] = coordY;
	}

	//GPU LUT index initialization
	m_pIndex = (unsigned short *)malloc((m_gpu_lut.h - 1) * (m_gpu_lut.w - 1) * 6 * sizeof(unsigned short));
	unsigned short *pTempIndex = m_pIndex;
	for (int y = 0; y < m_gpu_lut.h - 1; y++)
	{
		unsigned short usIndex = y * m_gpu_lut.w;
		for (int x = 0; x < m_gpu_lut.w - 1; x++)
		{
			*pTempIndex++ = usIndex;
			*pTempIndex++ = usIndex + 1;
			*pTempIndex++ = usIndex + m_gpu_lut.w;
			*pTempIndex++ = usIndex + 1;
			*pTempIndex++ = usIndex + m_gpu_lut.w + 1;
			*pTempIndex++ = usIndex + m_gpu_lut.w;
			usIndex++;
		}
	}

    return true;
}


//if failure, restart time stitcher
void SVTimeStitcher::reset()
{
    m_bEnabled = false;
    if (!prev_T.empty())
        prev_T.clear();

	vhcl_motion.track = 0.0;
	m_iFrame = -1;
	m_dense_lut.reset_flag = true;
}

//low beam lights detection
bool SVTimeStitcher::lowBmAct()
{
    if (m_last_lowBmAct != m_pvadat->LowBmAct)
    {
        if (Closed == m_pvadat->LowBmAct)
        {
            threshold_ts_x_front = 1.0;
        }
        else
        {
            threshold_ts_x_front = 3.0;
        }

        threshold_ts_v_front = (int32_t)floor(threshold_ts_x_front / ppmmx);
        m_last_lowBmAct = m_pvadat->LowBmAct;

        if (carRect.x - threshold_ts_u > 0 && carRect.y - threshold_ts_v_front > 0)
        {
            roi_ts = tsRect(carRect.x - threshold_ts_u, carRect.y - threshold_ts_v_front, carRect.width + 2 * threshold_ts_u, carRect.height + threshold_ts_v_front + threshold_ts_v_rear);
        }
        else
        {
            roi_ts = carRect;
        }

        return true;
    }

    return false;
}

//dual-threshold for function failure judgment
bool SVTimeStitcher::judge_work_speed()
{
    float speed;
    AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&speed);
    if (speed > MAX_VEHICLE_SPEED)
    {
        return true;
    }

    if (!m_bEnabled)
    {
        if (speed > MAX_VEHICLE_SPEED * SPEED_RATIO)
        {
            return true;
        }
        else
        {
            m_bEnabled = !m_bEnabled;
        }
    }

    return false;
}

//gear shifting detection
bool SVTimeStitcher::judge_shift_pos()
{
    unsigned char gear_state;
    AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
    if (gear_state != m_last_shift_pos && Neutral != gear_state && Parking != gear_state)
    {
        m_last_shift_pos = gear_state;
        return true;
    }

    return false;
}

//threshold_ts_x and threshold_ts_y out of range protection
bool SVTimeStitcher::judge_blind_area()
{
    return (threshold_ts_x_front < 0 || threshold_ts_x_front > 3
        || threshold_ts_x_rear < 0 || threshold_ts_x_rear > 3
        || threshold_ts_y < 0 || threshold_ts_y > 3);
}

//add new bev_img and T to deque
void SVTimeStitcher::add_new_image()
{
    //image caching number limit protection
    if (prev_T.size() >= IMG_NUM_LIMIT)
    {
        prev_T.pop_back();
    }

    RT initialRT{ { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 } };
    prev_T.push_front(initialRT);

    if (m_iFrame < IMG_NUM_LIMIT - 1)
    {
        m_iFrame++;
    }
    else
    {
        m_iFrame = 0;
    }

    vhcl_motion.track = 0.0;
}

bool SVTimeStitcher::update_LUT(int pic, float *prevRT, int *pSIndex, int *pEIndex, int &pix_num, bool bCount, int &roi_pix_num, bool order_flag/* = true */)
{
    pic = (m_iFrame - pic + IMG_NUM_LIMIT) % IMG_NUM_LIMIT;

    float t[6];
    //matrix inversion
    float D = prevRT[0] * prevRT[4] - prevRT[1] * prevRT[3];
    D = D != 0 ? 1.0f / D : 0.0f;
    float A11 = prevRT[4] * D, A22 = prevRT[0] * D;
    t[0] = A11;
    t[1] = -D * prevRT[1];
    t[3] = -D * prevRT[3];
    t[4] = A22;
    float b1 = -t[0] * prevRT[2] - t[1] * prevRT[5];
    float b2 = -t[3] * prevRT[2] - t[4] * prevRT[5];
    t[2] = b1;
    t[5] = b2;

    bool bIsNeedInpaint = false;
    int roi_rBorder = roi_ts.x + roi_ts.width;
    int roi_dBorder = roi_ts.y + roi_ts.height;
    float recipX = (float)1 / (iW - 1);
    float recipY = (float)1 / (iH - 1);
    int step = carRect.width * sizeof(TabCar) / sizeof(float);

    //if this is the first bev_img, then count pixel number in threshold_ts_x area
    if (bCount)
    {
        roi_pix_num = pixels_in_threshold_ts_v(t, order_flag);
    }

	int offset = pic == IMG_NUM_LIMIT - 1 ? -10 : 5;
	if (order_flag)
	{
		for (int x = carRect.x; x <= right_col; x++)
		{
			int overlapRow = 0;
			float x0_f = t[0] * x + t[1] * (*pSIndex) + t[2];
			float y0_f = t[3] * x + t[4] * (*pSIndex) + t[5];
			float *pSrcPt = ((m_dense_lut.car_list + x - carRect.x + carRect.width * (*pSIndex - carRect.y))->srcPt + pic)->coord;
			float recipW = 1.0;

            //update wPt of gpu_lut.car_list
            for (int y = *pSIndex; y < *pEIndex; y++)
            {
                int x0 = (int)round(x0_f);
                int y0 = (int)round(y0_f);

                if ((x0 >= 0 && x0 < iW && y0 >= 0 && y0 < iH)
                    && (y0 < roi_ts.y || y0 >= roi_dBorder || x0 < roi_ts.x || x0 >= roi_rBorder))
                {
                    if (0 == overlapRow)
                    {
                        overlapRow = y;
                        recipW = (float)1 / (*pEIndex - overlapRow);
                    }

                    *pSrcPt = x0 * recipX;
                    *(pSrcPt + 1) = 1.0f - y0 * recipY;
                    *(pSrcPt + 2) = (y - overlapRow) * recipW;
                    *(pSrcPt + offset) = 1 - *(pSrcPt + 2);
                }

                x0_f += t[1];
                y0_f += t[4];
                pSrcPt += step;
            }


            //update srcPt of gpu_lut.car_list
            for (int y = *pEIndex; y <= bottom_row; y++)
            {
                int x0 = (int)round(x0_f);
                int y0 = (int)round(y0_f);

                if ((x0 >= 0 && x0 < iW && y0 >= 0 && y0 < iH)
                    && (y0 < roi_ts.y || y0 >= roi_dBorder || x0 < roi_ts.x || x0 >= roi_rBorder))
                {
                    if (0 == overlapRow)
                    {
                        overlapRow = y;
                        if (y > *pEIndex)
                        {
                            bIsNeedInpaint = true;
                        }
                    }

                    *pSrcPt = x0 * recipX;
                    *(pSrcPt + 1) = 1.0f - y0 * recipY;
                    *(pSrcPt + 2) = 1.0f;

                    pix_num++;
                }
                else if (overlapRow != 0)
                {
                    *pSIndex = *pEIndex;
                    *pEIndex = y;
                    break;
                }

                if (bottom_row == y && overlapRow != 0)
                {
                    *pSIndex = *pEIndex;
                    *pEIndex = y + 1;
                    break;
                }

                x0_f += t[1];
                y0_f += t[4];
                pSrcPt += step;
            }

			pSIndex++;
			pEIndex++;
		}
	}
	else
	{
		for (int x = carRect.x; x <= right_col; x++)
		{
			int overlapRow = 0;
			float x0_f = t[0] * x + t[1] * (*pSIndex) + t[2];
			float y0_f = t[3] * x + t[4] * (*pSIndex) + t[5];
			float *pSrcPt = ((m_dense_lut.car_list + x - carRect.x + carRect.width * (*pSIndex - carRect.y))->srcPt + pic)->coord;
			float recipW = 1.0;

            //update wPt of gpu_lut.car_list
            for (int y = *pSIndex; y > *pEIndex; y--)
            {
                int x0 = (int)round(x0_f);
                int y0 = (int)round(y0_f);

                if ((x0 >= 0 && x0 < iW && y0 >= 0 && y0 < iH)
                    && (y0 < roi_ts.y || y0 >= roi_dBorder || x0 < roi_ts.x || x0 >= roi_rBorder))
                {
                    if (0 == overlapRow)
                    {
                        overlapRow = y;
                        recipW = (float)1 / (*pEIndex - overlapRow);
                    }

                    *pSrcPt = x0 * recipX;
                    *(pSrcPt + 1) = 1.0f - y0 * recipY;
                    *(pSrcPt + 2) = (y - overlapRow) * recipW;
                    *(pSrcPt + offset) = 1.0f - *(pSrcPt + 2);
                }

                x0_f -= t[1];
                y0_f -= t[4];
                pSrcPt -= step;
            }

            //update srcPt of gpu_lut.car_list
            for (int y = *pEIndex; y >= carRect.y; y--)
            {
                int x0 = (int)round(x0_f);
                int y0 = (int)round(y0_f);

                if ((x0 >= 0 && x0 < iW && y0 >= 0 && y0 < iH)
                    && (y0 < roi_ts.y || y0 >= roi_dBorder || x0 < roi_ts.x || x0 >= roi_rBorder))
                {
                    if (0 == overlapRow)
                    {
                        overlapRow = y;
                        if (y < *pEIndex)
                        {
                            bIsNeedInpaint = true;
                        }
                    }

                    *pSrcPt = x0 * recipX;
                    *(pSrcPt + 1) = 1.0f - y0 * recipY;
                    *(pSrcPt + 2) = 1.0f;

                    pix_num++;
                }
                else if (overlapRow != 0)
                {
                    *pSIndex = *pEIndex;
                    *pEIndex = y;
                    break;
                }

                if (carRect.y == y && overlapRow != 0)
                {
                    *pSIndex = *pEIndex;
                    *pEIndex = y - 1;
                    break;
                }

                x0_f -= t[1];
                y0_f -= t[4];
                pSrcPt -= step;
            }

            pSIndex++;
            pEIndex++;
        }
    }

    return bIsNeedInpaint;
}

int SVTimeStitcher::pixels_in_threshold_ts_v(float *t, bool order_flag)
{
    int roi_rBorder = roi_ts.x + roi_ts.width;
    int roi_dBorder = roi_ts.y + roi_ts.height;
    int startRow = 0, endRow = 0;
    int roi_pix_num = 0;

    if (order_flag)
    {
        startRow = roi_ts.y;
        endRow = carRect.y;
    }
    else
    {
        startRow = carRect.y + carRect.height;
        endRow = roi_ts.y + roi_ts.height;
    }

    for (int x = carRect.x; x <= right_col; x++)
    {
        float x0_f = t[0] * x + t[1] * startRow + t[2];
        float y0_f = t[3] * x + t[4] * startRow + t[5];
        bool col_flag = false;
        for (int y = startRow; y < endRow; y++)
        {
            int x0 = (int)round(x0_f);
            int y0 = (int)round(y0_f);

            if ((x0 >= 0 && x0 < iW && y0 >= 0 && y0 < iH)
                && (y0 < roi_ts.y || y0 >= roi_dBorder || x0 < roi_ts.x || x0 >= roi_rBorder))
            {
                roi_pix_num++;

                if (!col_flag)
                {
                    col_flag = true;
                }
            }
            else if (col_flag)
            {
                break;
            }

            x0_f += t[1];
            y0_f += t[4];
        }
    }

    return roi_pix_num;
}

void SVTimeStitcher::empty_LUT()
{
	TabCar* temp_list = m_dense_lut.car_list;
	for (int y = 0; y < m_dense_lut.h; y++)
	{
		for (int x = 0; x < m_dense_lut.w; x++)
		{
			for (int i = 0; i < IMG_NUM_LIMIT; i++)
			{
				temp_list->srcPt[i].weight = 0.0;
			}

            temp_list++;
        }
    }

	m_dense_lut.new_img_flag = false;
	m_dense_lut.reset_flag = false;
}

void SVTimeStitcher::update_GPU_LUT()
{
	TabCar *pGpuTabCar = m_gpu_lut.car_list;
	for (int y = 0; y < m_gpu_lut.h; y++)
	{
		TabCar *pDenseTabCar = m_dense_lut.car_list + mCoordY[y]*m_dense_lut.w;
		for (int x = 0; x < m_gpu_lut.w; x++)
		{
			memcpy(pGpuTabCar->srcPt, (pDenseTabCar + mCoordX[x])->srcPt, sizeof(Pt)*IMG_NUM_LIMIT);
			pGpuTabCar++;
		}
	}
	m_gpu_lut.new_img_flag = m_dense_lut.new_img_flag;
	m_gpu_lut.reset_flag = m_dense_lut.reset_flag;
    //Log_Error("=================new_img_flag = %d", m_gpu_lut.new_img_flag);
}

void SVTimeStitcher::inpaint_LUT()
{
	float *pW = (m_dense_lut.car_list + m_dense_lut.h*m_dense_lut.w - 1)->srcPt->coord;
	int step = sizeof(TabCar) / sizeof(float);
	for (int y = 0; y < m_dense_lut.h; y++)
	{
		for (int x = 0; x < m_dense_lut.w; x++)
		{
			bool flag = true;
			for (int i = 0; i < IMG_NUM_LIMIT; i++)
			{
				if (*(pW + 2 + i * 3) > EPSINON)
				{
					flag = !flag;
					break;
				}
			}

			if (flag)
			{
				if (y > 0)
				{
					memcpy(pW, pW + m_dense_lut.w*step, sizeof(float) * IMG_NUM_LIMIT * 3);
				}
				else if (x > 0)
				{
					memcpy(pW, pW - step, sizeof(float) * IMG_NUM_LIMIT * 3);
				}
			}

            pW -= step;
        }
    }
}

void SVTimeStitcher::update_RT(RT &prevRT, float *currRT)
{
    //matrix multiplication
    float t[6];
    t[0] = currRT[0] * prevRT.t[0] + currRT[1] * prevRT.t[3];
    t[1] = currRT[0] * prevRT.t[1] + currRT[1] * prevRT.t[4];
    t[2] = currRT[0] * prevRT.t[2] + currRT[1] * prevRT.t[5] + currRT[2];
    t[3] = currRT[3] * prevRT.t[0] + currRT[4] * prevRT.t[3];
    t[4] = currRT[3] * prevRT.t[1] + currRT[4] * prevRT.t[4];
    t[5] = currRT[3] * prevRT.t[2] + currRT[4] * prevRT.t[5] + currRT[5];

    memcpy(prevRT.t, t, sizeof(float) * 6);
}

void SVTimeStitcher::update()
{    
    empty_LUT();
    //lowBmAct();
    bool ret = judge_work_speed();
    ret |= judge_shift_pos();
    ret |= judge_blind_area();

	if (ret || vhcl_motion.track > TRACK_LIMIT)
	{
		reset();
		update_GPU_LUT();
		return;
	}

	//if there is no image or matrix in deque
	if (/*prev_bev_img.empty() ||*/ prev_T.empty())
	{
		m_dense_lut.new_img_flag = true;
		add_new_image();
		update_GPU_LUT();
		return;
	}

    float t[9];
    vhcl_motion.get_motion_transform(cx, cy, ppmmx, ppmmy, t);

    //pix_num is used to record how many pixels have been painted in carRect
    int pix_num = 0;

    //pixel_num_limit is used to judge whether a new bev_img is needed 
    float scale_limit = 0;
    int pixel_num_limit = 0;

    //image blending area definition
    int *start_index = new int[carRect.width];
    int *end_index = new int[carRect.width];

    bool order_flag;
    
    float vehicle_speed;
    AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&vehicle_speed);

	Smc_Cal_T *m_avm_mc;
	AVMData::GetInstance()->GetSmc(&m_avm_mc);
 //   Log_Error("=================vehicle_speed = %f", vehicle_speed);
    if (Driving == m_last_shift_pos)
    {
        scale_limit =
            ((m_avm_mc->bev_stitch_param.view_param[0].view_range - m_avm_mc->bev_stitch_param.view_param[0].blind_range) / 1000 - threshold_ts_x_front - vehicle_speed / 3.6f * 0.12f)
            / ((m_avm_mc->veh_param.veh_length + m_avm_mc->bev_stitch_param.view_param[0].blind_range) / 1000 + threshold_ts_x_front);
        if (scale_limit > 0 && scale_limit < 1)
        {
            pixel_num_limit = (int)floor(scale_limit * (carRect.height + threshold_ts_v_front) * carRect.width * m_pix_num_ratio_D);
        }

        int *pSIndex = start_index;
        int *pEIndex = end_index;
        for (int i = 0; i < carRect.width; ++i)
        {
            *pSIndex = carRect.y;
            *pEIndex = carRect.y;
            ++pSIndex;
            ++pEIndex;
        }

        order_flag = true;
    }
    else
    {
        scale_limit =
            ((m_avm_mc->bev_stitch_param.view_param[1].view_range - m_avm_mc->bev_stitch_param.view_param[1].blind_range) / 1000 - threshold_ts_x_rear - vehicle_speed / 3.6 * 0.12)
            / ((m_avm_mc->veh_param.veh_length + m_avm_mc->bev_stitch_param.view_param[1].blind_range) / 1000 + threshold_ts_x_rear);
        if (scale_limit > 0)
        {
            pixel_num_limit = (int)floor(scale_limit * (carRect.height + threshold_ts_v_rear)  * carRect.width * m_pix_num_ratio_R);
        }

        int *pSIndex = start_index;
        int *pEIndex = end_index;
        for (int i = 0; i < carRect.width; i++)
        {
            *pSIndex = bottom_row;
            *pEIndex = bottom_row;
            ++pSIndex;
            ++pEIndex;
        }

        order_flag = false;
    }

    bool bIsNeedInpaint = false;
    deque<RT>::iterator iter_T = prev_T.begin();
    for (int i = 0; i < prev_T.size(); i++)
    {
        update_RT(*iter_T, t);

		int roi_pix_num = 0;
		if (0 == i  && !m_dense_lut.new_img_flag)
		{
			 bIsNeedInpaint |= update_LUT(i, iter_T->t, start_index, end_index, pix_num, true, roi_pix_num, order_flag);

			if ((pix_num + roi_pix_num) >= pixel_num_limit)
			{
				m_dense_lut.new_img_flag = true;
			}
		}
		else
		{
			bIsNeedInpaint |= update_LUT(i, iter_T->t, start_index, end_index, pix_num, false, roi_pix_num, order_flag);
		}

        iter_T++;
    }

    delete[] start_index;
    delete[] end_index;

    if (pix_num < carRect.width*carRect.height
        && (prev_T.size() >= IMG_NUM_LIMIT || carRect.width*carRect.height - pix_num < 1200 || bIsNeedInpaint))
    {
        inpaint_LUT();
    }
        
	if (m_dense_lut.new_img_flag)
	{
		add_new_image();
	}

	update_GPU_LUT();
}

void SVTimeStitcher::GetVertexBuffer(float **pVertex, unsigned int &bufSize)
{
	bufSize = m_gpu_lut.h * m_gpu_lut.w;
	*pVertex = (float *)m_gpu_lut.car_list;
}

void SVTimeStitcher::GetIndexBuffer(unsigned short **pIndex, unsigned int &bufSize)
{
	bufSize = (m_gpu_lut.h - 1) * (m_gpu_lut.w - 1) * 6;
	*pIndex = m_pIndex;
}

bool SVTimeStitcher::GetNewImgFlag()
{
	return m_gpu_lut.new_img_flag;
}

bool SVTimeStitcher::GetResetFlag()
{
	return m_gpu_lut.reset_flag;
}



