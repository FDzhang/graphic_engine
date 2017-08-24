
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

void TestCustomHMI(void)
{
	//test_hmi = new SVNodeTestHMI;
	//test_hmi.InitHMI(1920, 1080);
	//test_hmi.SetHMIParams();
	//pTestHMI[0] = test_hmi.GetHMI();
	//InitADASMdlHMI(pTestHMI,1);
}
  
void TestAdasHMI(void)
{
    int nodeId,temp;

	char test1[100]="HAHASUCCEED!";

	char test2[100]="Again SUCCEED!";

	//char test3[100]="Again SUCCEED!";
	//char test4[100]="Again SUCCEED!";

	tempText[0].pos[0]=440;
	tempText[0].pos[1]=360;
	tempText[0].width = 200;
	tempText[0].font_size = 20;
	tempText[0].line_num=2;

	tempText[0].text_color[0]=1.0;
	tempText[0].text_color[1]=1.0;
	tempText[0].text_color[2]=0.0;

	tempText[0].show_flag = 1;
	tempText[0].text_content[0]=new char [50];

	tempText[0].text_content[1]=new char [50];
	sprintf(tempText[0].text_content[0],"%s",test1);
	sprintf(tempText[0].text_content[1],"%s",test2);





	tempText[1].pos[0]=940;
	tempText[1].pos[1]=560;
	tempText[1].width = 100;
	tempText[1].font_size = 30;
	tempText[1].line_num=4;

	tempText[1].show_flag = 1;
	tempText[1].text_color[0]=1.0;
	tempText[1].text_color[1]=0.0;
	tempText[1].text_color[2]=0.2;

	tempText[1].text_content[0]=new char [50];
	tempText[1].text_content[1]=new char [50];
	tempText[1].text_content[2]=new char [50];
	tempText[1].text_content[3]=new char [50];

	sprintf(tempText[1].text_content[0],"test2 start");
	sprintf(tempText[1].text_content[1],"test date 0914");
	sprintf(tempText[1].text_content[2],"test result pass");
	sprintf(tempText[1].text_content[3],"mid autumn");



	 tempIcon[0].pos[0] = 120;
	 tempIcon[0].pos[1] = 400;
	 tempIcon[0].width = 60;
	 tempIcon[0].height =80;
	 tempIcon[0].show_flag = 1;
	 tempIcon[0].show_icon_num = 1;

	tempIcon[0].icon_file_name[0]=new char [50];
	tempIcon[0].icon_file_name[1]=new char [50];
	tempIcon[0].icon_file_name[2]=new char [50];
	sprintf(tempIcon[0].icon_file_name[0],"%sgreen.dds",XR_RES);
	sprintf(tempIcon[0].icon_file_name[1],"%sred.dds",XR_RES);
	sprintf(tempIcon[0].icon_file_name[2],"%sgreen.dds",XR_RES);
	  tempIcon[1].pos[0] =420;
	  tempIcon[1].pos[1] = 400;
	  tempIcon[1].width = 80;
	  tempIcon[1].height =80;
	  tempIcon[1].show_flag = 1;
	  tempIcon[1].show_icon_num = 1;

	 tempIcon[1].icon_file_name[0]=new char[50];
	 tempIcon[1].icon_file_name[1]=new char[50];
	 tempIcon[1].icon_file_name[2]=new char[50];
	 sprintf(tempIcon[1].icon_file_name[0],"%sgreen.dds",XR_RES);
	 sprintf(tempIcon[1].icon_file_name[1],"%sred.dds",XR_RES);
	 sprintf(tempIcon[1].icon_file_name[2],"%sgreen.dds",XR_RES);


	 tempScroll[0].pos[0] = 600;
	 tempScroll[0].pos[1] = 400;
	 tempScroll[0].width = 128;
	 tempScroll[0].height = 100;
	 tempScroll[0].horizon = 0;
	 tempScroll[0].show_flag = 1;
	 tempScroll[0].icon_file_name[0]=new char [50];
	 tempScroll[0].icon_file_name[1]=new char [50];
	 sprintf(tempScroll[0].icon_file_name[0],"%sscroll_bk.dds",XR_RES);
	 sprintf(tempScroll[0].icon_file_name[1],"%sscroll_adas.dds",XR_RES);


	 tempLDWData[0].curv = 0.00001457;
	 tempLDWData[0].slope = 0.000684619823;

	 tempLDWData[0].L_offset=  -1.52134848;
	 tempLDWData[0].R_offset=  -1.40134848;
	 tempLDWData[0].alarm_state = 0;
	 tempLDWData[0].show_flag = 1;

    tempLDWData[0].icon_file_name[0]=tempScroll[0].icon_file_name[0];
	tempLDWData[0].icon_file_name[1]=tempScroll[0].icon_file_name[1];
	 tempLDWData[1].curv = 0.00001457;
	 tempLDWData[1].slope = 0.000684619823;

	 tempLDWData[1].L_offset=  1.62134848;
	 tempLDWData[1].R_offset=  1.74134848;

	 tempLDWData[1].alarm_state = 1;
	 tempLDWData[1].show_flag = 1;

	 tempLDWData[1].icon_file_name[0]=new char [50];
	 tempLDWData[1].icon_file_name[1]=new char [50];
	 sprintf(tempLDWData[1].icon_file_name[0],"%sscroll_bk.dds",XR_RES);
	 sprintf(tempLDWData[1].icon_file_name[1],"%sldw_line.dds",XR_RES);

	 tempBSDRectData[0].point[0] = 50;
	 tempBSDRectData[0].point[1] = 100;
	 tempBSDRectData[0].point[2] = 350;
	 tempBSDRectData[0].point[3] = 120;
	 tempBSDRectData[0].point[4] = 320;
	 tempBSDRectData[0].point[5] = 100;
	 tempBSDRectData[0].point[6] = 50;
	 tempBSDRectData[0].point[7] = 90;
	 tempBSDRectData[0].icon_file_name[0] = tempIcon[0].icon_file_name[0];
	 tempBSDRectData[0].icon_file_name[1] = tempIcon[0].icon_file_name[1];

	 tempBSDRectData[0].alarm_state = 1;
	 tempBSDRectData[0].show_flag = 1;
	 tempBSDRectData[0].rear_single_view_flag = 1;

	 tempBSDRectData[1].point[0] = 250;
	 tempBSDRectData[1].point[1] = 200;
	 tempBSDRectData[1].point[2] = 300;
	 tempBSDRectData[1].point[3] = 200;
	 tempBSDRectData[1].point[4] = 300;
	 tempBSDRectData[1].point[5] = 150;
	 tempBSDRectData[1].point[6] = 250;
	 tempBSDRectData[1].point[7] = 150;
	 tempBSDRectData[1].icon_file_name[0] = tempIcon[0].icon_file_name[0];
	 tempBSDRectData[1].icon_file_name[1] = tempIcon[0].icon_file_name[1];

	 tempBSDRectData[1].alarm_state = 1;
	 tempBSDRectData[1].show_flag = 1;
	 tempBSDRectData[1].rear_single_view_flag = 1;

	 tempBSDRectData[2].point[0] = 300;
	 tempBSDRectData[2].point[1] = 200;
	 tempBSDRectData[2].point[2] = 400;
	 tempBSDRectData[2].point[3] = 180;
	 tempBSDRectData[2].point[4] = 400;
	 tempBSDRectData[2].point[5] = 130;
	 tempBSDRectData[2].point[6] = 300;
	 tempBSDRectData[2].point[7] = 150;
	 tempBSDRectData[2].icon_file_name[0] = tempIcon[0].icon_file_name[0];
	 tempBSDRectData[2].icon_file_name[1] = tempIcon[0].icon_file_name[1];

	 tempBSDRectData[2].alarm_state = 1;
	 tempBSDRectData[2].show_flag = 1;
	 tempBSDRectData[2].rear_single_view_flag = 1;

	 BSD_Mdel_HMI.icon_num=0;
	 BSD_Mdel_HMI.ldw_line_num=0;
	 BSD_Mdel_HMI.scroll_rect_num=1;
	 BSD_Mdel_HMI.pScrollRect = tempScroll;
	 BSD_Mdel_HMI.single_view_rect_num=3;

	 BSD_Mdel_HMI.pSingleviewRect = tempBSDRectData;
	 BSD_Mdel_HMI.text_box_num=1;
	 BSD_Mdel_HMI.pTextBox = &tempText[1];

	 pHMIArray[0] = &BSD_Mdel_HMI;
	 pHMIArray[1] = &LDW_MDEL_HMI;

#if 1
	 LDW_MDEL_HMI.icon_num=2;
	 LDW_MDEL_HMI.pStaticIcon=tempIcon;
	 LDW_MDEL_HMI.ldw_line_num=2;
	 LDW_MDEL_HMI.pLDWLine=tempLDWData;
	 LDW_MDEL_HMI.scroll_rect_num=0;
	 LDW_MDEL_HMI.pScrollRect = tempScroll;
	 LDW_MDEL_HMI.single_view_rect_num=0;
	 LDW_MDEL_HMI.text_box_num=1;
	 LDW_MDEL_HMI.pTextBox = &tempText[0];
#endif
	 InitADASMdlHMI(pHMIArray,2);



}
 
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

void TestAdasHMIUpdate(void)
{

float steer_angle;
float vehicle_speed;

AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);
AVMData::GetInstance()->m_p_can_data->Get_Vehicle_Speed(&vehicle_speed);
sprintf(tempText[0].text_content[0],"Steering wheel angle: %f",steer_angle);

sprintf(tempText[0].text_content[1],"vehicle speed: %f",vehicle_speed);
if(vehicle_speed >50)
{
	tempText[1].text_color[0]=1.0;
	tempText[1].text_color[1]=1.0;
	tempText[1].text_color[2]=0.2;

	tempIcon[0].show_flag = 0;
	tempIcon[1].show_flag = 0;
	 tempBSDRectData[0].point[0] = 50;
 tempBSDRectData[0].point[1] = 100;
 tempBSDRectData[0].point[2] = 350;
 tempBSDRectData[0].point[3] = 120;
 tempBSDRectData[0].point[4] = 320;
 tempBSDRectData[0].point[5] = 100;
 tempBSDRectData[0].point[6] = 50;
 tempBSDRectData[0].point[7] = 90;
}
else if(vehicle_speed<20)
{
	tempText[1].text_color[0]=1.0;
	tempText[1].text_color[1]=0.0;
	tempText[1].text_color[2]=0.2;
	tempIcon[0].show_flag = 1;

	tempIcon[1].show_flag = 0;

 tempBSDRectData[0].point[0] = 50;
 tempBSDRectData[0].point[1] = 300;
 tempBSDRectData[0].point[2] = 350;
 tempBSDRectData[0].point[3] = 320;
 tempBSDRectData[0].point[4] = 320;
 tempBSDRectData[0].point[5] = 200;
 tempBSDRectData[0].point[6] = 50;
 tempBSDRectData[0].point[7] = 20;

}
else
{

	tempText[1].text_color[0]=1.0;
	tempText[1].text_color[1]=0.0;
	tempText[1].text_color[2]=0.2;
	tempIcon[0].show_flag = 1;

	tempIcon[1].show_flag = 1;

	tempBSDRectData[0].point[0] = 250;
tempBSDRectData[0].point[1] = 100;
tempBSDRectData[0].point[2] = 550;
tempBSDRectData[0].point[3] = 120;
tempBSDRectData[0].point[4] = 520;
tempBSDRectData[0].point[5] = 100;
tempBSDRectData[0].point[6] = 250;
tempBSDRectData[0].point[7] = 90;


}

if(steer_angle >200)
{

	tempText[1].show_flag = 0;

	tempIcon[0].show_icon_num = 0;

	tempIcon[1].show_icon_num = 2;
			tempLDWData[0].show_flag = 1;
	tempLDWData[0].alarm_state=1;
	tempBSDRectData[0].rear_single_view_flag =0;
	tempBSDRectData[0].show_flag = 1;
}
else if(steer_angle>100)
{
	tempText[1].show_flag = 1;
	tempIcon[0].show_icon_num = 1;
	tempIcon[1].show_icon_num = 1;
	tempLDWData[0].show_flag = 0;
	tempLDWData[0].alarm_state=1;

	tempBSDRectData[0].rear_single_view_flag =1;
	tempBSDRectData[0].show_flag = 1;

}
else
{
	tempText[1].show_flag = 1;
	tempIcon[0].show_icon_num = 1;
	tempIcon[1].show_icon_num = 0;
			tempLDWData[0].show_flag = 1;
	tempLDWData[0].alarm_state=0;

	tempBSDRectData[0].rear_single_view_flag =0;
	tempBSDRectData[0].show_flag = 0;

}
tempScroll[0].scroll_rate = vehicle_speed/100.0;
static float LDW_test= 0;
if(LDW_test>0.2)
{
	LDW_test = -1.0;
}
else
{
	//LDW_test+=0.001;
}
tempLDWData[1].L_offset+=LDW_test;
tempLDWData[1].R_offset+=LDW_test;
tempLDWData[0].L_offset+=LDW_test;
tempLDWData[0].R_offset+=LDW_test;

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
	g_GearRText.show_flag = pAPAReslt->vP_GearR_Text;
	g_GearRText.height = 155;
	g_GearRText.width = 636;
	g_GearRText.show_icon_num = 0;
	g_GearRText.icon_file_name[0] = Indicatefile;
	g_GearRText.pos[0]= 20;
	g_GearRText.pos[1] = 150;
}

void UpdateGpuLuminanceBalanceCof(CoefYUV *lb_result)
{
    AVMData::GetInstance()->m_lumin_para->SetLuminanceCofYUVReslt(lb_result);

}
void UpdateTexture()
{

}

void MockTouchEvent(unsigned char key_value)
{
	app.MockTouchEvent(key_value);	
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


