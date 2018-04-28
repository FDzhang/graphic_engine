
#include <stdio.h>
//#include "GlSVDemo.h"
#include <GLES2/gl2.h>
#include "DataStruct.h"

#include "SurroundView.h"
#include "AVMData.h"
#include "HMISource/HMITest.h"
#include "GPU_Module_Interface.h"
//GlSVDemo* demo;
XRSV app;
//#define STATIC_TEXTURE_USE
APAOverlayStruct g_APA_Result;
const char Indicatefile[256] = "/opt/svres/apa/R2D.dds";
st_ADAS_Mdl_HMI_T g_APA_HMI_data;
st_static_icon_box_data_T g_GearRText;
st_text_box_data_T tempText[3];
st_static_icon_box_data_T tempIcon[4];
st_scroll_box_data_T tempScroll[2];
st_LDW_line_data_T tempLDWData[4];
st_singleview_rect_data_T tempBSDRectData[8];
st_ADAS_Mdl_HMI_T BSD_Mdel_HMI;
st_ADAS_Mdl_HMI_T LDW_MDEL_HMI;
st_ADAS_Mdl_HMI_T *pHMIArray[2];
Radar_PLD_Result g_radar_pld_reslt;
SVNodeTestHMI test_hmi;
st_ADAS_Mdl_HMI_T* pTestHMI[1];
static int chains_status = 0;
static int next_chains_status = 0;

extern char CAR2DICON[];
extern char CARLIGHTON[];
extern char CARLIGHTTEX[];
extern char CARTEX[];
extern void UpdateJ6VideoTexture(GLuint input[]);
#ifdef __cplusplus
extern "C" {
#endif
  
void InitADASMdlHMI(st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum)
{
	int window_width = 1280;
	int window_height = 720;
	test_hmi.InitHMI(window_width, window_height);
	test_hmi.SetHMIParams();

	pAdasMdlHmiHandle[HmiMdlNum] = test_hmi.GetHMI();
	HmiMdlNum += 1;

	g_GearRText.show_flag = 0;
	g_GearRText.height = 155;
	g_GearRText.width = 636;
	g_GearRText.show_icon_num = 0;
	g_GearRText.icon_file_name[0] = Indicatefile;
	g_GearRText.pos[0]= 20;
	g_GearRText.pos[1] = 150;
	g_APA_HMI_data.pStaticIcon = &g_GearRText;
	g_APA_HMI_data.icon_num = 1;
	pAdasMdlHmiHandle[HmiMdlNum++] = &g_APA_HMI_data;
	app.initAdasMdlHmi(pAdasMdlHmiHandle,HmiMdlNum);
}
//void GpuLogctrl_End(void){return};

   
void UpdateCustomHMIData()
{
	float steer_angle;
	float vehicle_speed;
	float yaw_rate_value;
	ProcessInfoData InfoData;
	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);
	AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&vehicle_speed);
	AVMData::GetInstance()->m_p_can_data->Get_Yaw_Rate(&yaw_rate_value);
	AVMData::GetInstance()->m_process_info->GetProcessInfo(&InfoData);

	test_hmi.UpdateHMIChainStatus(chains_status);
	test_hmi.UpdateHMINextChainsStatus(next_chains_status);
	test_hmi.UpdateHMIData(steer_angle, vehicle_speed, yaw_rate_value);
	test_hmi.setIconStatus();
	test_hmi.UpdateHMIChainProcessingStatus(InfoData.sgxfps,
		InfoData.srcToSgxAvgLatency,
		InfoData.srcToSgxMaxLatency,
		InfoData.algAvgCost_ms,
		InfoData.algMaxCost_ms);
}

void setHMIAlgStatus(int alg_status_value)
{
	test_hmi.alg_status= alg_status_value;

	app.SetCurrentAlgoStatus(alg_status_value);
	
}

void setHMIChainsStatus(int demo_status_value)
{
	test_hmi.demo_status= demo_status_value;
}

void SetCustomeHMIChainStatus(int pchain_status)
{
	chains_status = pchain_status;
}
void SetCustomeHMINextChainStatus(int pchain_status)
{
	next_chains_status = pchain_status;

}

void InitVehcleParam()
{
    SV_VEHICLE_PARAM_T veh_param;
	veh_param.vehicle_axis_length =  2700;
	veh_param.vehicle_front_wheel_to_bumper = 956;
	veh_param.vehicle_length =  4545;
	veh_param.vehicle_rear_wheel_to_bumper = 889;
	veh_param.vehicle_width = 1855;
	veh_param.vehicle_max_steering_wheel[left_turn_max] = 588;
	veh_param.vehicle_max_steering_wheel[right_turn_max] = 588;
	veh_param.vehicle_min_radius[left_turn_foward_radius] = 4680;
	veh_param.vehicle_min_radius[left_turn_backward_radius] = 4680;
	veh_param.vehicle_min_radius[right_turn_foward_radius] = 4680;
	veh_param.vehicle_min_radius[right_turn_backward_radius] = 4680;

	veh_param.vehicle_tyre_radius=500;
	veh_param.vehicle_tyre_radius=300;
    app.initVehicleParam(veh_param);

		//TestAdasHMI();
}

//{ add start by ke.zhonghua 2017/05/08
int InitAppNew(int width, int height, st_GPU_Init_Config_T* gpu_init)
{
    if(gpu_init != NULL)
    {
        InitVehcleParam();
        if(app.init(width, height, *gpu_init))
        {
            g_radar_pld_reslt.iParkLotBitFlag=0;
			g_radar_pld_reslt.iParkLotNum=0;
            return 0;
        }
        return -1;
    }
    return -22;//参数错误
}
//} add end ke.zhonghua
void GetSonarPLDRslt(Radar_PLD_Result *pReslt)
{
     pReslt->iParkLotBitFlag = g_radar_pld_reslt.iParkLotBitFlag;
	 pReslt->iParkLotNum = g_radar_pld_reslt.iParkLotNum;
	 for(int i=0;i<4;i++)
	 {
	     pReslt->sFrontMarginGround_Points[i] = g_radar_pld_reslt.sFrontMarginGround_Points[i];
         pReslt->sGround_Points[i].x = g_radar_pld_reslt.sGround_Points[i].x/1000.0;
		 
         pReslt->sGround_Points[i].y = g_radar_pld_reslt.sGround_Points[i].y/1000.0;
	     pReslt->sTruePLD_Points[i] = g_radar_pld_reslt.sTruePLD_Points[i];
         pReslt->sRearMarginGround_Points[i] = g_radar_pld_reslt.sRearMarginGround_Points[i];

	 }
	 pReslt->sGround_Points[0].x = g_radar_pld_reslt.sGround_Points[2].x/1000.0;
	 
	 pReslt->sGround_Points[0].y = g_radar_pld_reslt.sGround_Points[2].y/1000.0;

pReslt->sGround_Points[1].x = g_radar_pld_reslt.sGround_Points[0].x/1000.0;

pReslt->sGround_Points[1].y = g_radar_pld_reslt.sGround_Points[0].y/1000.0;
pReslt->sGround_Points[2].x = g_radar_pld_reslt.sGround_Points[1].x/1000.0;

pReslt->sGround_Points[2].y = g_radar_pld_reslt.sGround_Points[1].y/1000.0;

	 
}
Radar_PLD_Result* GetSonarPLDDataPointer(void)
{
    return &g_radar_pld_reslt;

}

int UpdateApp(unsigned int view_control_flag,GLuint texYuv[])
{
	#ifndef STATIC_TEXTURE_USE
	//UpdateJ6VideoTexture(texYuv);
	for(int i =0;i<4;i++)
	{
	    AVMData::GetInstance()->m_cam_source->UpdateCameraSource(i,texYuv[i]);
	}
	#endif
	//TestAdasHMIUpdate();
	app.update(view_control_flag);
    return 0;
}

void SetShutdownDisplay()
{
    app.MockTouchEvent(1,0);
    app.DisableCar();
}

int OnMouseSingleUp(int x,int y)
{
    app.SingleTouchUp(x, y);
	printf("\r\nSingle touch up, [%d,%d]",x,y);
    return 0;
}

int OnMouseSingleDown(int x,int y)
{
    app.SingleTouchDown( x, y);

	//Log_Message("\r\nSingle touch down, [%d,%d]",x,y);
    return 0;
}

int OnMouseSingleMove(int x,int y)
{
    app.SingleTouchMove( x, y);

	printf("\r\nSingle touch move, [%d,%d]",x,y);
    return 0;
}

void UpdateGPUMdlCANData(CAN_DATA in_CAN_data)
{
    in_CAN_data.radar_alarm[0]=0;
	in_CAN_data.radar_alarm[3]=0;
	in_CAN_data.radar_alarm[5]=0;
	in_CAN_data.radar_alarm[6]=0;
    AVMData::GetInstance()->m_p_can_data->UpdateCANData(in_CAN_data);
}

void UpdateGpuChainSgxFps(float fps)
{
	if(AVMData::GetInstance()->m_process_info != NULL)
	{
		AVMData::GetInstance()->m_process_info->UpdateFps(fps);
	}
}
void UpdateStichAngle(unsigned char seam_change_flag[],StitcherResult* sticher_result)
{
    float *pData;
	int   unstitch_point_num = sticher_result->gpu_2dlut_param->gpu_lut_config[1]
	  +sticher_result->gpu_2dlut_param->gpu_lut_config[3]
	  +sticher_result->gpu_2dlut_param->gpu_lut_config[5]
	  +sticher_result->gpu_2dlut_param->gpu_lut_config[7];

	pData = sticher_result->gpu_2dlut_param->gpu_lut_data+unstitch_point_num*7;

	
    app.UpdateStichAngle(seam_change_flag,pData);
}

void UpdateGpuChainSrcToSgxLatency(float avg_in_ms, float max_in_ms)
{
	if(AVMData::GetInstance()->m_process_info != NULL)
	{
		AVMData::GetInstance()->m_process_info->UpdateFrameLatency(avg_in_ms, max_in_ms);
	}
}

void UpdateGpuChainAlgCost(float avg_in_ms, float max_in_ms)
{
	if(AVMData::GetInstance()->m_process_info != NULL)
	{
		AVMData::GetInstance()->m_process_info->UpdateAlgCost(avg_in_ms, max_in_ms);
	}
}

void UpdateGpuMdlCalibRslt(unsigned int ** out_config_store, float* data_buffer, unsigned short* gui_index_buffer, GPU_MDL_POSE pose)
{

	float gpu_format_pose[24];


	  //  log_message("LUT changed, GPU will update its internal data...");
		for(int i =0;i<6;i++)
		{
			gpu_format_pose[i] = pose.front_pose[i];
		}
		for(int i =0;i<6;i++)
		{
			gpu_format_pose[6*1+i] = pose.right_pose[i];
		}
		for(int i =0;i<6;i++)
		{
			gpu_format_pose[6*2+i] = pose.rear_pose[i];
		}
		for(int i =0;i<6;i++)
		{
			gpu_format_pose[6*3+i] = pose.left_pose[i];
		}

		app.Update3DParam(gpu_format_pose);
		app.Update2DParam((void *)data_buffer,(void *)gui_index_buffer);



}
void UpdateAPAResult(APAOverlayStruct *pAPAReslt)
{
	if(pAPAReslt == NULL)
		return;
	
    g_APA_Result.drive_dirction_indicat = pAPAReslt->drive_dirction_indicat;
	g_APA_Result.end_parking_sign_flag = pAPAReslt->end_parking_sign_flag;
	g_APA_Result.online_detect_flag = pAPAReslt->online_detect_flag;
	g_APA_Result.parking_lot_detect_flag = pAPAReslt->parking_lot_detect_flag;
	g_APA_Result.park_lot_flag = pAPAReslt->park_lot_flag;
	for(int i = 0;i<8;i++)
	{
	    g_APA_Result.pParkLotPos[i] = pAPAReslt->pParkLotPos[i];
	}
	g_APA_Result.parking_lot_type = pAPAReslt->parking_lot_type;
	g_APA_Result.scroll_rate = pAPAReslt->scroll_rate;
	g_APA_Result.stop_sign_flag = pAPAReslt->stop_sign_flag;
	g_APA_Result.vP_GearR_Text = pAPAReslt->vP_GearR_Text;
	// udpate Gear_R indicate text when vertical parking first turn
	g_GearRText.show_flag = 0;//pAPAReslt->vP_GearR_Text;
	g_GearRText.height = 155;
	g_GearRText.width = 636;
	g_GearRText.show_icon_num = 0;
	g_GearRText.icon_file_name[0] = Indicatefile;
	g_GearRText.pos[0]= 20;
	g_GearRText.pos[1] = 150;
}

void UpdateCtaResult(unsigned char pCtaStatus, void* pCtaResult)
{
	app.UpdateCtaResult(pCtaStatus, pCtaResult);
}

void UpdateTpResult(unsigned char pTpStatus, void* pTpResult)
{
}

void UpdateGpuLuminanceBalanceCof(CoefYUV *lb_result)
{
    AVMData::GetInstance()->m_lumin_para->SetLuminanceCofYUVReslt(lb_result);

}
void UpdateTexture()
{

}

void ProcApa(APAOverlayStruct *pApaResult)
{
	if(pApaResult == NULL) return;
	
    g_APA_Result.drive_dirction_indicat = pApaResult->drive_dirction_indicat;
	g_APA_Result.end_parking_sign_flag = pApaResult->end_parking_sign_flag;
	g_APA_Result.online_detect_flag = pApaResult->online_detect_flag;
	g_APA_Result.parking_lot_detect_flag = pApaResult->parking_lot_detect_flag;
	g_APA_Result.park_lot_flag = pApaResult->park_lot_flag;
	for(int i = 0;i<8;i++)
	{
	    g_APA_Result.pParkLotPos[i] = pApaResult->pParkLotPos[i];
	}
	g_APA_Result.parking_lot_type = pApaResult->parking_lot_type;
	g_APA_Result.scroll_rate = pApaResult->scroll_rate;
	g_APA_Result.stop_sign_flag = pApaResult->stop_sign_flag;
	g_APA_Result.vP_GearR_Text = pApaResult->vP_GearR_Text;
	// udpate Gear_R indicate text when vertical parking first turn
	g_GearRText.show_flag = pApaResult->vP_GearR_Text;
	g_GearRText.height = 155;
	g_GearRText.width = 636;
	g_GearRText.show_icon_num = 0;
	g_GearRText.icon_file_name[0] = Indicatefile;
	g_GearRText.pos[0]= 20;
	g_GearRText.pos[1] = 150;
}

void ProcCta(CtaResultT* pCtaResult)
{
	if(pCtaResult == NULL) return;

	app.UpdateCtaResult(pCtaResult->ctaStatus, pCtaResult->ctaResult);
}

void ProcStitch(StitchResultT* pStitchResult)
{
	if(pStitchResult == NULL) return;

    float *pData;
	int   unstitch_point_num = pStitchResult->sticherResult->gpu_2dlut_param->gpu_lut_config[1]
	  + pStitchResult->sticherResult->gpu_2dlut_param->gpu_lut_config[3]
	  + pStitchResult->sticherResult->gpu_2dlut_param->gpu_lut_config[5]
	  + pStitchResult->sticherResult->gpu_2dlut_param->gpu_lut_config[7];

	pData = pStitchResult->sticherResult->gpu_2dlut_param->gpu_lut_data + unstitch_point_num * 7;

    app.UpdateStichAngle(pStitchResult->seamChangeFlag,pData);
}

void ProcAlgoStatus(unsigned char* pAlgoStatus)
{
	if(pAlgoStatus == NULL) return;

	app.SetCurrentAlgoStatus(*pAlgoStatus);
}

void ProcSonarPld(Radar_PLD_Result* pReslt)
{
	pReslt->iParkLotBitFlag = g_radar_pld_reslt.iParkLotBitFlag;
	pReslt->iParkLotNum = g_radar_pld_reslt.iParkLotNum;
	for(int i = 0; i < 4; i++)
	{
		pReslt->sFrontMarginGround_Points[i] = g_radar_pld_reslt.sFrontMarginGround_Points[i];
		pReslt->sGround_Points[i].x = g_radar_pld_reslt.sGround_Points[i].x/1000.0;

		pReslt->sGround_Points[i].y = g_radar_pld_reslt.sGround_Points[i].y/1000.0;
		pReslt->sTruePLD_Points[i] = g_radar_pld_reslt.sTruePLD_Points[i];
		pReslt->sRearMarginGround_Points[i] = g_radar_pld_reslt.sRearMarginGround_Points[i];

	}
	pReslt->sGround_Points[0].x = g_radar_pld_reslt.sGround_Points[2].x/1000.0;

	pReslt->sGround_Points[0].y = g_radar_pld_reslt.sGround_Points[2].y/1000.0;

	pReslt->sGround_Points[1].x = g_radar_pld_reslt.sGround_Points[0].x/1000.0;

	pReslt->sGround_Points[1].y = g_radar_pld_reslt.sGround_Points[0].y/1000.0;
	pReslt->sGround_Points[2].x = g_radar_pld_reslt.sGround_Points[1].x/1000.0;

	pReslt->sGround_Points[2].y = g_radar_pld_reslt.sGround_Points[1].y/1000.0;

		 
}

void ProcShutdownDisplay()
{
    app.MockTouchEvent(1,0);
    app.DisableCar();
}

void ProcLuminanceBalance(CoefYUV *lb_result)
{
    AVMData::GetInstance()->m_lumin_para->SetLuminanceCofYUVReslt(lb_result);
}

void ProcCalibRslt(GpuCalibResultT* pCalibResult)
{
	float gpu_format_pose[24];

	//  log_message("LUT changed, GPU will update its internal data...");
	for(int i =0;i<6;i++)
	{
		gpu_format_pose[i] = pCalibResult->pose.front_pose[i];
	}
	for(int i =0;i<6;i++)
	{
		gpu_format_pose[6*1+i] = pCalibResult->pose.right_pose[i];
	}
	for(int i =0;i<6;i++)
	{
		gpu_format_pose[6*2+i] = pCalibResult->pose.rear_pose[i];
	}
	for(int i =0;i<6;i++)
	{
		gpu_format_pose[6*3+i] = pCalibResult->pose.left_pose[i];
	}

	app.Update3DParam(gpu_format_pose);
	app.Update2DParam((void *)(pCalibResult->dataBuffer),(void *)(pCalibResult->guiIndexBuffer));

}

void ProcCanData(CAN_DATA* pCanData)
{
    pCanData->radar_alarm[0]=0;
	pCanData->radar_alarm[3]=0;
	pCanData->radar_alarm[5]=0;
	pCanData->radar_alarm[6]=0;
    AVMData::GetInstance()->m_p_can_data->UpdateCANData(*pCanData);
}

int UpdateRenderDvrData(void* renderData, unsigned int dataLength)
{
	CAvmRenderDataBase::GetInstance()->SetDvrData((DVR_GUI_LAYOUT_INST_EXT*)renderData);
}


int UpdateRenderData(RenderDataTypeT dataTypeId, void* renderData, unsigned int dataLength)
{
	unsigned char currentViewStatus = 0;
	switch(dataTypeId)
	{
		case RENDER_DATA_VIEW_CMD:
			static unsigned char lastViewStatus = 254;
			currentViewStatus = *((unsigned char*)renderData);
		
			//Log_Error("--------RENDER_DATA_VIEW_CMD: %d", currentViewStatus);
			if(currentViewStatus != lastViewStatus)
			{
				CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(currentViewStatus);
				lastViewStatus = currentViewStatus;
			}
			//Log_Error("-----------current view: %d", currentViewStatus);
		break;
		case RENDER_DATA_MAIN_MENU:
			CAvmRenderDataBase::GetInstance()->SetMainMenuStatus((MainMenuDataT*)renderData);

		break;
		case RENDER_DATA_DVR:
			UpdateRenderDvrData(renderData, dataLength);
			//CAvmRenderDataBase::GetInstance()->SetDvrData((DVR_GUI_LAYOUT_INST_EXT*)renderData);
		break;
		//case RENDER_DATA_S302_MAIN_MENU:
		//	CAvmRenderDataBase::GetInstance()->SetS302MainMenuStatus((S302MainMenuDataT*)renderData);
		//break;
		case RENDER_DATA_CAN:
			
			ProcCanData((CAN_DATA*)renderData);

		break;
		case RENDER_DATA_CALIB_RESULT:

			ProcCalibRslt((GpuCalibResultT*)renderData);

		break;
		case RENDER_DATA_LUMB_RESULT:

			ProcLuminanceBalance((CoefYUV*)renderData);

		break;
		case RENDER_DATA_STITCH_ANGLE:
			ProcStitch((StitchResultT*)renderData);

		break;
		case RENDER_DATA_APA_RESULT:
			ProcApa((APAOverlayStruct*)renderData);
			CAvmRenderDataBase::GetInstance()->SetApaResult((APAOverlayStruct*)renderData);

		break;
		case RENDER_DATA_CTA_RESULT:
			
			ProcCta((CtaResultT *)renderData);

		break;
		case RENDER_DATA_ALGO_STATUS:

			ProcAlgoStatus((unsigned char*)renderData);
			
		break;		
		case RENDER_DATA_SONAR_PLD_RESULT:

			ProcSonarPld((Radar_PLD_Result*)renderData);

		break;	
		case RENDER_DATA_SONAR_RESULT:

			CAvmRenderDataBase::GetInstance()->SetSonarResult((PLDRadarResult*)renderData);

		break;	
		case RENDER_DATA_SHUT_DOWN_DISPLAY:
			
			ProcShutdownDisplay();

		break;
		case RENDER_DATA_LKA_LC_RESULT:
			CAvmRenderDataBase::GetInstance()->SetLkaLcResult((LkaLcResultT*)renderData);
		break;
		case RENDER_DATA_TP_RESULT:
			CAvmRenderDataBase::GetInstance()->SetTpResult((Tp_Result*)renderData);
		break;
		case RENDER_DATA_SEA_RESULT:
			CAvmRenderDataBase::GetInstance()->SetSeaResult((Sea_Result_T*)renderData);
		break;
		case RENDER_DATA_MOD_RESULT:
			CAvmRenderDataBase::GetInstance()->SetModResult((Mod_Result_T*)renderData);
		break;
		case RENDER_DATA_EOL_RESULT:
			CAvmRenderDataBase::GetInstance()->SetEolResult((EolResultT*)renderData);

			//debug code;need delete;
			//EolResultT tmpTestResult;
			//tmpTestResult.eolStatus = EOL_CALIBRATION_PROCESS;
			//CAvmRenderDataBase::GetInstance()->SetEolResult(&tmpTestResult);
		break;
		case RENDER_DATA_MOUSE_ICON:
			if(renderData)
			{
				MouseDataT* mouseData = (MouseDataT*)renderData;
				TouchDataT touchData;
				
				if(mouseData->touchData.touchAction == TOUCH_ACTION_MOVE)
				{
					touchData.x = mouseData->touchData.x;
					touchData.y = mouseData->touchData.y;
					touchData.touchAction = TouchEvent_Move;
					CAvmRenderDataBase::GetInstance()->SetTouchData(&touchData);
				}
				CAvmRenderDataBase::GetInstance()->SetMouseIconVisibility(mouseData->visibility);
			}
		break;
		default:
		break;
	}
	return RENDER_INTERFACE_NO_ERROR;

}

int SetRenderData(RenderDataT* pRenderData)
{
	switch(pRenderData->dataHeader.dataTypeId)
	{
		case RENDER_DATA_VIEW_CMD:

			CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(*((unsigned char*) pRenderData->data));

		break;
		case RENDER_DATA_MAIN_MENU:
			CAvmRenderDataBase::GetInstance()->SetMainMenuStatus((MainMenuDataT*)pRenderData->data);
		break;
		case RENDER_DATA_CAN:
			ProcCanData((CAN_DATA*)pRenderData->data);

		break;
		case RENDER_DATA_CALIB_RESULT:

			ProcCalibRslt((GpuCalibResultT*)pRenderData->data);

		break;
		case RENDER_DATA_LUMB_RESULT:

			ProcLuminanceBalance((CoefYUV*)pRenderData->data);

		break;
		case RENDER_DATA_STITCH_ANGLE:
			
			ProcStitch((StitchResultT*)pRenderData->data);

		break;
		case RENDER_DATA_APA_RESULT:
			
			ProcApa((APAOverlayStruct*) pRenderData->data);

		break;
		case RENDER_DATA_CTA_RESULT:
			
			ProcCta((CtaResultT *) pRenderData->data);

		break;
		case RENDER_DATA_ALGO_STATUS:

			ProcAlgoStatus((unsigned char*) pRenderData->data);
			
		break;		
		case RENDER_DATA_SONAR_PLD_RESULT:

			ProcSonarPld((Radar_PLD_Result*) pRenderData->data);

		break;	
		case RENDER_DATA_SHUT_DOWN_DISPLAY:
			
			ProcShutdownDisplay();

		break;
		case RENDER_DATA_LKA_LC_RESULT:
			CAvmRenderDataBase::GetInstance()->SetLkaLcResult((LkaLcResultT*) pRenderData->data);
		default:
		break;
	}
	return RENDER_INTERFACE_NO_ERROR;
}



void MockTouchEvent(unsigned char key_value, unsigned char key_mode)
{
    app.MockTouchEvent(key_mode, key_value);
}

#ifdef __cplusplus
}
#endif

int OnMouseSingleMove_CPP(int x,int y)
{
    app.SingleTouchMove( x, y);

	printf("\r\ncpp touch move, [%d,%d]",x,y);
    return 0;

}

int OnMouseSingleDown_CPP(int x,int y)
{
    app.SingleTouchDown( x, y);

	printf("\r\ncpp touch down, [%d,%d]",x,y);
    return 0;
}

int OnMouseSingleUp_CPP(int x,int y)
{
    app.SingleTouchUp(x, y);

	printf("\r\ncpp touch up, [%d,%d]",x,y);
    return 0;
}
int SwitchView_CPP(int viewIndex)
{
    //app.SingleTouchUp(x, y);
    app.SwitchViewButton(viewIndex);
	printf("\r\n switch view %d",viewIndex);
    return 0;
}


