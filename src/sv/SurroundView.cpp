//----------------------------------------------------------------------------------
// File:        hdr_app.cpp
// SDK Version: v10.10
// Email:       jackh@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2007-2012, NVIDIA CORPORATION.  All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------
#include "SurroundView.h"
#include "SVScene.h"
#include "SVUI.h"
#include "stdio.h"
#include "stdlib.h"

#include "commondef.h"
//#include "XrCore\XrSrc\External\XrHeaders.h"
//#include "XrCore\XrSrc\XrUILibrary\XrUILibrary.h"

#include "SVAdjust.h"
#include "gpu_log.h"

#include "HMISource/CSVChangAnHmi.h"

SVUI* svui;
SVScene* svscn;
#define VK_A 0x41
#define VK_D 0x44
#define VK_F 0x46
#define VK_G 0x47

#define VK_W 0x57
#define VK_S 0x53
#define VK_Q 0x51
#define VK_E 0x45
#define VK_Z 0x5A
#define VK_X 0x58
#define VK_C 0x43
#define VK_V 0x56

#define VK_H 0x48
#define VK_K 0x4B
#define VK_Y 0x59
#define VK_I 0x49
#define VK_U 0x55
#define VK_J 0x4A

#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38

#define VK_0 0x30

#define VK_INSERT  45
#define VK_HOME      36
#define VK_PAGE_UP   33

#define VK_LEFT   37
#define VK_RIGHT  39
#define VK_UP     38
#define VK_DOWN   40

#define VK_SPACE  32

 float ADJUST_PARAM[24];
char exAdjustFile[]	= XR_RES"ex_param_adj.bin";
char exConfigFile[]	= XR_RES"camera_parameter.smc";
char exConfigHMIFile[]	= XR_RES"sv_hmi.smc";
typedef unsigned short index_type;




char ex2DCalibResult[]="pose.txt";  // 2D calibration result
char exManualAdjustFile[]	= "manual_adjust.txt";
char c_bcParam[]  = "Lumin_Balance_Para.txt";
char LutConfig[]="config.bin";
char LutData[]="data.bin";
char LutIndex[]="index.bin";
char CarPose[]="car_pose.txt";
char CarPoseAdjust[]="car_shadow_adjust.txt";
char CarCalibFileName[]="pgs.txt";

#define _CONFIGBINFILE_ _BEVPATH_"config.bin"
#define _DATABINFILE_ _BEVPATH_"data.bin"
#define _INDEXBINFILE_ _BEVPATH_"index.bin"
#define _DATACARPOSE_ _BEVPATH_"car_pose.txt"


//for vehicle state simulation
float g_vehicle_speed=0;
float g_steering_wheel_angle=0;
unsigned char g_gear_pos=0;
unsigned char g_turn_light=0;
unsigned char g_object_state[8]={0,};
unsigned int g_frame_time=40000;

#define STEERING_WHEEL_TURN_STEP  20

IXrCore* g_pIXrCore=0;
IDeviceManager* rm=0;
IAnimationManager* am=0;
static IUINode* pUI=0;
static ISceneNode* pScene=0;
static IPostProcessingNode* pPost=0;
static IMaterial* pMtl=0;
static ICamera* pCamera=0;
static IMesh* pMesh=0;
static INode* pBox=0;
static INode* pChara=0;
static INode* pHead=0;
static INode* pCtrl=0;
static ILight* pLight=0;
static CSwapChain* g_pXrSwapChain=0;
CRenderDevice* g_pXrRenderDevice=0;
CRenderContext* g_pXrRenderContext=0;
CRenderTarget*	pFrame_buffer;
extern float g_TextureStep;
BEV_CONFIG_T sv_config;

 extern GLuint uiConfigBin[4][9];
 extern GLfloat *pfDataTotal;
 extern GLushort *pucIndexTotal;

 extern GLfloat *pfDataSecond;
 extern GLushort *pucIndexSecond;


 extern GLfloat *pfDataThird;
extern GLushort *pucIndexThird;



unsigned int Get_Frame_TimeStamp(void)
{

    return g_frame_time;

}
void Set_Frame_TimeStamp(unsigned int time_frame_ms)
{
    g_frame_time = time_frame_ms;//unit  us
	return;
}

PFUpdateJointParamCallback XRSV::UpdateJonintParam = NULL;


bool XRSV::initVehicleParam(SV_VEHICLE_PARAM_T in_veh_param)
{

    m_sv_data_config.vehicle_para = in_veh_param;
	return 0;

}
void XRSV::initAdasMdlHmi(st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum)
{
    m_pAdasMdl = pAdasMdlHmiHandle;
	m_adas_mdl_num = HmiMdlNum;

}
int XRSV::InitHmi(int screen_width, int screen_height)
{
	m_customHmi = new CSVChanganHmi();
	m_customHmi->Init(screen_width, screen_height);

	return 0;
}
int XRSV::UpdateHmiData()
{
	m_customHmi->Update(currentHmiMessage);
	unsigned char currentViewIndex = 0;
	m_customHmi->GetCurrentView(currentViewIndex);

	if(svscn)
	{
		svscn->SetTouchSelectView(currentViewIndex);
	}
}
int XRSV::SetCurrentAlgoStatus(int algo_status)
{
	m_currentAlgoStatus = algo_status;
	currentHmiMessage.algo_status = algo_status;
	return 0;
}
bool XRSV::init(int width, int height, st_GPU_Init_Config_T& gpu_init_cfg)
{
	int i,logoMtlId,logoLayerId;
	int temp =0;
	temp = InitXrSystem(width, height, 0);
	printf("\r\n InitXrSystem return %d",temp);
	printf("\r\n width=%d height = %d",width,height);
	XrGetDeviceContextAndSwapChainFB(&g_pXrRenderContext, &g_pXrRenderDevice, &g_pXrSwapChain, &pFrame_buffer);
	IUINode* rtNode;
	g_pIXrCore = GetXrCoreInterface();
	printf("\r\n g_pIXrCore = 0x%x",g_pIXrCore);
	g_pIXrCore->GetDeviceManager(&rm);
	g_pIXrCore->GetAnimationManager(&am);
	g_pIXrCore->SetClearBackground(1);
	//g_pIXrCore->SetDeferredRendering(0);
	pUI = 0;
	m_adjust = new SVAdjust;

	m_sv_data_config.front_single_view_rect[rect_left]=FRONT_SINGLE_LEFT;
	m_sv_data_config.front_single_view_rect[rect_top]=FRONT_SINGLE_TOP;
	m_sv_data_config.front_single_view_rect[rect_right]=FRONT_SINGLE_RIGHT;
	m_sv_data_config.front_single_view_rect[rect_bottom]=FRONT_SINGLE_BOTTOM;

	m_sv_data_config.rear_single_view_rect[rect_left]=REAR_SINGLE_LEFT;
	m_sv_data_config.rear_single_view_rect[rect_top]=REAR_SINGLE_TOP;
	m_sv_data_config.rear_single_view_rect[rect_right]=REAR_SINGLE_RIGHT;
	m_sv_data_config.rear_single_view_rect[rect_bottom]=REAR_SINGLE_BOTTOM;

	m_sv_data_config.platform_config = PLATFORM_J6;
	m_sv_data_config.config_file_source = CFG_FROM_SYS;
	m_adjust->Init(ADJUST_PARAM,sizeof(ADJUST_PARAM),exAdjustFile);
	bev_Load_Configure(&sv_config, exConfigFile, exConfigHMIFile, exConfigFile );
    memcpy(&(m_sv_data_config.bev_conig),&(sv_config),sizeof(BEV_CONFIG_T));
	memcpy(m_sv_data_config.exparam_file_name,ex2DCalibResult,MAX_NAME_LENGTH);
	memcpy(m_sv_data_config.exparam_adjust_file_name,exManualAdjustFile,MAX_NAME_LENGTH);
	memcpy(m_sv_data_config.lumin_pos_file_name,c_bcParam,MAX_NAME_LENGTH);
	memcpy(m_sv_data_config.lut_config_file_name,LutConfig,MAX_NAME_LENGTH);
	memcpy(m_sv_data_config.lut_data_file_name,
LutData,MAX_NAME_LENGTH);
	memcpy(m_sv_data_config.lut_index_file_name,LutIndex,MAX_NAME_LENGTH);

	memcpy(m_sv_data_config.car_pose_file_name,CarPose,MAX_NAME_LENGTH);

	memcpy(m_sv_data_config.car_pose_adjust_file_name,CarPoseAdjust,MAX_NAME_LENGTH);

	memcpy(m_sv_data_config.car_calib_name,CarCalibFileName,MAX_NAME_LENGTH);

	strcpy(m_sv_data_config.file_path,XR_RES);

	//{modified by ke.zhonghua 2017/05/08 传入gpu初始化数据
    m_sv_data_config.pSmc = gpu_init_cfg.pSys_SMC;
	m_sv_data_config.pPose = gpu_init_cfg.pPose;
    m_sv_data_config.pCamParam = gpu_init_cfg.camera_param;
	m_vehicleId =  gpu_init_cfg.vehicle_type_id;

    m_sv_data_config.pSticherResult = gpu_init_cfg.sticher_result;
    //} add end ke.zhonghua

	AVMData::GetInstance()->InitConfig(m_sv_data_config);

	svscn = new SVScene();

	svui = new SVUI();

	svui->svscn = svscn;

	temp = svscn->InitNode(sv_config,m_pAdasMdl,m_adas_mdl_num);

	InitHmi(width, height);

	#ifndef EMIRROR
	//svui->InitNode(sv_config,width,height);
	#endif

	return true;
}

bool XRSV::draw()
{
	return true;
}
extern IKeyAnimation* bevSecTour[2];

bool XRSV::update(unsigned int view_control_flag)
{
    static int temp=0;
    static unsigned int pre_time_start=0;
	unsigned int start, timestamp1,timestamp2,end;
	static unsigned int endl = 0;
	static int cnt=0, total=0;
	static int init_flag = 0;
	if (g_pIXrCore) {
		start = XrGetTime();
		//Set_Frame_TimeStamp(start-pre_time_start);
		Set_Frame_TimeStamp(AVMData::GetInstance()->m_p_can_data->GetTimeStamp());
        switch(view_control_flag)
        {
            case 2:
				m_customHmi->SetVisibility(0);
                svscn->SwitchCrossView();
                g_pIXrCore->ProcessEvent();
                g_pIXrCore->Update();
                g_pIXrCore->Render();
                g_pXrSwapChain->Swap();
                return 0;
            case 0xf0:
            case 0xf1:
            case 0xf2:
            case 0xf3:
				m_customHmi->SetVisibility(0);
                svscn->SwitchSingleView(view_control_flag);
                g_pIXrCore->ProcessEvent();
                g_pIXrCore->Update();
                g_pIXrCore->Render();
                g_pXrSwapChain->Swap();
                return 0;
            default:
				m_customHmi->SetVisibility(1);
				if(m_currentAlgoStatus == ALGO_LDW
				|| m_currentAlgoStatus == ALGO_BSD
				|| m_currentAlgoStatus == ALGO_ONLINE_CALIBRATION
				|| m_currentAlgoStatus == ALGO_APA
				|| m_currentAlgoStatus == ALGO_CTA
				|| m_currentAlgoStatus == ALGO_LDW_BSD)
				{
					m_customHmi->SetVisibility(0);
				}
                break;
        }

    UpdateHmiData();

        svscn->Update(view_control_flag,0);
        
		//svui->Update(0,0);
		g_pIXrCore->ProcessEvent();
		timestamp1 = XrGetTime();
#ifndef EMIRROR
        if(init_flag ==1)
        {
            if(cnt>= START_UP_TURN_TIME)
            {
                bevSecTour[0]->Stop();
    			bevSecTour[1]->Stop();
				//svscn->SwitchViewLogic(BOSH_FRONT_VIEW);
				//svscn->SwitchViewLogic(REAR_SINGLE_VIEW);
				svscn->SwitchViewLogic(FRONT_3D_VIEW);
				init_flag =2;

            }
        }
        if(init_flag==0)
        {
            bevSecTour[0]->Start();
			bevSecTour[1]->Start();
			svscn->SwitchViewLogic(TOUR_VIEW);

			init_flag = 1;
        }
#endif

		g_pIXrCore->Update();
		timestamp2 = XrGetTime();
		g_pIXrCore->Render();
		end = XrGetTime();
		g_TextureStep+=0.1;
		temp++;
		if(temp%100==99)
		{
		    #if 0
			printf("\r\nprepare cost=%d \n", timestamp1-start);
    		printf("\r\nupdate cost=%d \n", timestamp2 -timestamp1);
    		printf("\r\nrender cost=%d \n", end -timestamp2);
			printf("\r\ntotally cost=%d \n", end -start);
			printf("\r\nframe rame time = %d\n",start-endl);
			#endif



		}

		cnt++;
	}
	endl = XrGetTime();
	pre_time_start = start;
	g_pXrSwapChain->Swap();
	
	endl = XrGetTime();
	//Log_Debug("frame_process[%d]",endl-start);
	return true;
}

void XRSV::Update3DParam(float *pose)
{
	svscn->UpdateExternCalibReslt(pose);
}

void XRSV::Update2DParam(void *pdata,void *pIndex)
{
    int data_size = 0;
	int index_size = 0;
	data_size = AVMData::GetInstance()->m_2D_lut->GetDataTotalCnt();
	index_size = AVMData::GetInstance()->m_2D_lut->GetIndexTotalCnt();
	svscn->UpdateExternCalib2DReslt((GLfloat*)pdata,data_size,(GLushort *)pIndex,index_size);
}


void XRSV::SingleTouchDown(int x, int y)
{
	if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Down);
	//svscn->OnMouseDown(x,y);
	m_customHmi->SetSingleTouchDownEvent(x, y);
}

void XRSV::SingleTouchMove(int x, int y)
{
	//if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Move);
	//svscn->OnMouseMove(x,y);
}

void XRSV::SingleTouchUp(int x, int y)
{
	//if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Up);
	//svscn->OnMouseUp(x,y);
}

void XRSV::SwitchViewButton(int buttonid)
{
	//svscn->ButtonSwitchViewJ6(buttonid);
}


void XRSV::Pinch(float distance)
{
	pCamera->SetFOVDelta(distance);
}
void XRSV::UpdateStichAngle(unsigned char seam_change_flag[],float *pVertex)
{
	svscn->UpdateStich2DReslt(seam_change_flag,pVertex);
}

void XRSV::DoubleTouchDown(int x, int y)
{
	if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Down);
	prevX = x;
	prevY = y;
}

void XRSV::DoubleTouchMove(int x, int y)
{
	pCamera->MoveAroundDelta(float(prevX-x)*0.2, float(y-prevY)*0.2);
	//camX->Delta(x-prevX);
	//camY->Delta(y-prevY);
	if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Move);
	prevX = x;
	prevY = y;
}

void XRSV::DoubleTouchUp(int x, int y)
{
	if (g_pIXrCore) g_pIXrCore->OnTouchEvent(x, y, TouchEvent_Up);
	prevX = x;
	prevY = y;
}

void XRSV::RightTouchUp(int x, int y)
{
	m_adjust_eanble = 0;
	m_adjust->SaveExParam();

}
void XRSV::RightTouchDown(int x, int y)
{
	m_adjust_eanble = 1;

}
void XRSV::KeyDown(int x)
{
   static unsigned char  i=0;
   static unsigned char mirrorview=0;

   float pos[24]={
	   1.170699, -0.094849, 1.493127,
	   993.452, -9.550, -233.251,
	   1.064245, 0.085009, -2.941903,
	   349.695, 344.585, -424.599,
	   0.827318, -0.004211, -1.581904,
	   -352.584, 11.922, -433.059,
	   1.118334, -0.050154, -0.168691,
	   343.248, -383.008, -415.574,
   	};
   float pos_correct[24]={
	   1.225362, -0.004475, 1.599155,
	   4093.517788, -7.401903, -872.861730,
	   0.681853, -0.106849, -3.021532,
	   2462.087728, 906.934644, -995.097588,
	   1.172445, 0.051222, -1.594060,
	   -882.554416, 36.725972, -842.631225,
	   0.649207, 0.001564, -0.026723,
	   2473.182756, -936.647979, -994.176156,


   	};
   switch(x)
   {
	   case VK_1:
	   	//svscn->SwitchViewLogic(i%TOTAL_VIEW_NUM);
       break;
       case VK_LEFT:
	   	  g_steering_wheel_angle += STEERING_WHEEL_TURN_STEP;

		//  svscn->SwitchView();
	   break;
	   case VK_RIGHT:

		  g_steering_wheel_angle -= STEERING_WHEEL_TURN_STEP;

		  //svscn->SwitchView();

	   break;
	   case VK_UP:
           g_vehicle_speed +=10;

		//   svscn->SwitchView();
	   break;
	   case VK_DOWN:
           g_vehicle_speed -= 10;

		 //  svscn->SwitchView();
	   break;
       case VK_Z:
	   	  g_gear_pos = GEAR_P;

		 // svscn->SwitchView();
	   break;
	   case VK_X:
		   g_gear_pos = GEAR_R;

		 //  svscn->SwitchView();

	   break;
	   case VK_C:
		   g_gear_pos = GEAR_N;

		 //  svscn->SwitchView();
	   break;
	   case VK_V:
		   g_gear_pos = GEAR_D;
		//   svscn->SwitchView();
	   break;
	   case VK_INSERT:
	   	   g_turn_light = TURN_LIGHT_LEFT;

		  // svscn->SwitchView();
	   break;
	   case VK_HOME:
	   	   g_turn_light = TURN_LIGHT_OFF;

		   //svscn->SwitchView();

	   break;
	   case VK_PAGE_UP:
	   	   g_turn_light = TURN_LIGHT_RIGHT;

		 //  svscn->SwitchView();
	   break;
	   		case VK_SPACE:
			svscn->SaveOverlayData();
	   break;
	   case VK_2:
			svscn->UpdateExternCalibReslt(pos);
		break;
	   case VK_3:
			svscn->UpdateExternCalibReslt(pos_correct);
		break;
	   case VK_4:
			svscn->UpdateExternCalib2DReslt(pfDataThird,AVMData::GetInstance()->m_2D_lut->GetDataTotalCnt(),pucIndexThird,AVMData::GetInstance()->m_2D_lut->GetIndexTotalCnt());
		break;
	   case VK_5:
			svscn->UpdateExternCalib2DReslt(pfDataSecond,AVMData::GetInstance()->m_2D_lut->GetDataTotalCnt(),pucIndexSecond,AVMData::GetInstance()->m_2D_lut->GetIndexTotalCnt());
		break;
	   case VK_6:
			svscn->SwitchViewLogic(BOSH_FRONT_VIEW);
		break;
	   case VK_7:
	   	    if(0==mirrorview)
	   	    {
			svscn->SwitchViewLogic(LEFT_MIRROR_VIEW);
			mirrorview =1;
	   	    }
			else if(1==mirrorview)
	   	    {
			svscn->SwitchViewLogic(RIGHT_MIRROR_VIEW);
			mirrorview =2;
	   	    }
			else if(2==mirrorview)
	   	    {
			svscn->SwitchViewLogic(FRONT_3D_VIEW);
			mirrorview =0;
	   	    }

		break;
	   case VK_8:

			svscn->SwitchViewLogic(BOSH_FRONT_VIEW_TOP);


		break;
	   case VK_A:

			g_object_state[0]++;
		    if(g_object_state[0]>=5)
		    {
		         g_object_state[0]=0;
		    }

		break;
	   case VK_S:

			g_object_state[1]++;
		    if(g_object_state[1]>=5)
		    {
		         g_object_state[1]=0;
		    }

		break;
	   case VK_D:

			g_object_state[2]++;
		    if(g_object_state[2]>=5)
		    {
		         g_object_state[2]=0;
		    }

		break;
	   case VK_F:

			g_object_state[3]++;
		    if(g_object_state[3]>=5)
		    {
		         g_object_state[3]=0;
		    }

		break;
       case VK_G:

			g_object_state[4]++;
		    if(g_object_state[4]>=5)
		    {
		         g_object_state[4]=0;
		    }

		break;
	   case VK_H:

			g_object_state[5]++;
		    if(g_object_state[5]>=5)
		    {
		         g_object_state[5]=0;
		    }

		break;
	   case VK_J:

			g_object_state[6]++;
		    if(g_object_state[6]>=5)
		    {
		         g_object_state[6]=0;
		    }

		break;
	   case VK_K:

			g_object_state[7]++;
		    if(g_object_state[7]>=5)
		    {
		         g_object_state[7]=0;
		    }

		break;
   }

   i++;



    if(m_adjust_eanble == 0)
		return;

    switch(x)
    {
        case VK_1:
		case VK_2:
	    case VK_3:
	    case VK_4:
		case VK_5:
            m_adjust->SetChannel(x-VK_1);
			break;
		case VK_A:
			m_adjust->AdjustParam(ADJ_ROTX_NEG);
		break;
		case VK_D:
			m_adjust->AdjustParam(ADJ_ROTX_POS);
		break;
		case VK_W:
			m_adjust->AdjustParam(ADJ_ROTY_NEG);
		break;
		case VK_S:
			m_adjust->AdjustParam(ADJ_ROTY_POS);
		break;
		case VK_Q:
			m_adjust->AdjustParam(ADJ_ROTZ_NEG);
		break;
		case VK_E:
			m_adjust->AdjustParam(ADJ_ROTZ_POS);
		break;
		case VK_H:
			m_adjust->AdjustParam(ADJ_TRANSX_NEG);
		break;
		case VK_K:
			m_adjust->AdjustParam(ADJ_TRANSX_POS);
		break;
		case VK_U:
			m_adjust->AdjustParam(ADJ_TRANSY_NEG);
		break;
		case VK_J:
			m_adjust->AdjustParam(ADJ_TRANSY_POS);
		break;
		case VK_Y:
			m_adjust->AdjustParam(ADJ_TRANSZ_NEG);
		break;
		case VK_I:
			m_adjust->AdjustParam(ADJ_TRANSZ_POS);
		break;

    }

}

