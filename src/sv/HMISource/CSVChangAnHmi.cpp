#include "CSVChangAnHmi.h"
#include "gpu_log.h"

extern float car_rect[4];

typedef enum ChanganViewType {
	CCAG_FRONT_SINGLE_VIEW			= 0x00000000,
	CCAG_REAR_SINGLE_VIEW			= 0x00000001,
    CCAG_LEFT_SINGLE_VIEW		    = 0x00000002,
	CCAG_RIGHT_SINGLE_VIEW			= 0x00000003,
	CCAG_FRONT_3D_VIEW       		= 0x00000004,
	CCAG_REAR_3D_VIEW				= 0x00000005,
	CCAG_LEFT_FRONT_3D_VIEW                =0x0000006,
	CCAG_RIGHT_FRONT_3D_VIEW				=0x0000007,	
	CCAG_LEFT_REAR_3D_VIEW           =0x0008,
	CCAG_RIGHT_REAR_3D_VIEW          = 0x00009,
	CCAG_LEFT_TURN_SIGNAL_3D_VIEW,
	CCAG_RIGHT_TURN_SIGNAL_3D_VIEW,
	CCAG_LEFT_REAR_TURN_SIGNAL_3D_VIEW,
	CCAG_RIGHT_REAR_TURN_SIGNAL_3D_VIEW,	
	CCAG_LEFT_HIGHT_SPEED_TURN_3D_VIEW,
	CCAG_RIGHT_HIGHT_SPEED_TURN_3D_VIEW,
	CCAG_TOUR_VIEW,
	CCAG_BOSH_FRONT_VIEW,
	CCAG_BOSH_FRONT_VIEW_TOP,	
	CCAG_BOSH_REAR_VIEW_TOP,
	CCAG_LEFT_MIRROR_VIEW,
	CCAG_RIGHT_MIRROR_VIEW,	
	CCAG_CROSS_IMAGE_VIEW,	
	CCAG_BMW_REAR_VIEW,
	CCAG_BMW_LEFT_VIEW,
	CCAG_BMW_RIGHT_VIEW,
	CCAG_BMW_LEFT_FRONT_VIEW,
	CCAG_BMW_RIGHT_FRONT_VIEW,
	CCAG_BMW_LEFT_REAR_VIEW,
	CCAG_BMW_RIGHT_REAR_VIEW,
	CCAG_TOTAL_VIEW_NUM,
};

static void OnPressTrackCam();
static void OnPressFrontCam();
static void OnPressRearCam();
static void OnPressLeftCam();
static void OnPressRightCam();

unsigned char CSVChanganHmi::m_trackCamVisibility = 1;
unsigned char CSVChanganHmi::m_trackVisibility = 0;
unsigned char CSVChanganHmi::m_frontCamVisibility = 1;
unsigned char CSVChanganHmi::m_rearCamVisibility = 1;
unsigned char CSVChanganHmi::m_leftCamVisibility = 1;
unsigned char CSVChanganHmi::m_rightCamVisibility = 1;

unsigned char CSVChanganHmi::m_trackCamColor = 0;
unsigned char CSVChanganHmi::m_trackColor = 0;

unsigned char CSVChanganHmi::m_frontCamColor = 0;
unsigned char CSVChanganHmi::m_rearCamColor = 0;
unsigned char CSVChanganHmi::m_leftCamColor = 0;
unsigned char CSVChanganHmi::m_rightCamColor = 0;

float CSVChanganHmi::m_trackCamPosX = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_X];
float CSVChanganHmi::m_trackCamPosY = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_Y];
unsigned int CSVChanganHmi::m_currentTrackCamRegionIndex = 0;

unsigned int CSVChanganHmi::m_isTrackRegion = 0;
unsigned int CSVChanganHmi::m_isCarRegion = 0;

unsigned char CSVChanganHmi::m_currentViewState = 0;

CSVChanganHmi::CSVChanganHmi():m_storeTrackRegion(0)
{


}

int CSVChanganHmi::Init(int window_width, int window_height)
{
	m_stitchRegionWidth = 216.0/704.0 * window_width;
	m_stitchRegionHeight = window_height;
	SetSurroundViewCamElem();
    return true;
}

bool CSVChanganHmi::SetCustomView(unsigned char viewIndex)
{
	unsigned char tempViewIndex;
	tempViewIndex = viewIndex;
	if(m_isTrackRegion == 1)
	{
	        tempViewIndex = m_storeTrackRegion;
		if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_FRONT)
		{
			tempViewIndex = CCAG_BOSH_FRONT_VIEW_TOP; //front 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_REAR)
		{
			tempViewIndex = CCAG_REAR_3D_VIEW; //rear 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_LEFT)
		{
			tempViewIndex = CCAG_BMW_LEFT_VIEW; //left front 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_RIGHT)
		{
			tempViewIndex = CCAG_BMW_RIGHT_VIEW; //right front 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_FRONT_LEFT)
		{
			tempViewIndex = CCAG_BMW_LEFT_FRONT_VIEW; //left front 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT)
		{
			tempViewIndex = CCAG_BMW_RIGHT_FRONT_VIEW; //right front 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_REAR_LEFT)
		{
			tempViewIndex = CCAG_BMW_LEFT_REAR_VIEW; //left rear 3d
		}
		else if(tempViewIndex == CCAG_TRACK_CAMERA_REGION_REAR_RIGHT)
		{
			tempViewIndex = CCAG_BMW_RIGHT_REAR_VIEW; //right rear 3d
		}
	}
        else if(m_isTrackRegion == 0 || m_isCarRegion == 1)
        {
            if(tempViewIndex == CCAG_CAMERA_REGION_FRONT)
            {
            	tempViewIndex = CCAG_FRONT_SINGLE_VIEW; //front 3d
            }
            else if(tempViewIndex == CCAG_CAMERA_REGION_REAR)
            {
            	tempViewIndex = CCAG_REAR_SINGLE_VIEW; //rear 3d          	
            }
            else if(tempViewIndex == CCAG_CAMERA_REGION_LEFT)
            {
            	tempViewIndex = CCAG_LEFT_SINGLE_VIEW; //left front 3d
            }
            else if(tempViewIndex == CCAG_CAMERA_REGION_RIGHT)
            {
            	tempViewIndex = CCAG_RIGHT_SINGLE_VIEW; //right front 3d
            }
        }
	
	SetCurrentView(tempViewIndex);
}
int CSVChanganHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
 
    return true;
}

int CSVChanganHmi::ProcessIconTouchEvent()
{
	int x = 0;
	int y = 0;
	int touchType = 0;
	if(GetTouchEventInfo(x,y,touchType))
	{  
		if(m_isTrackRegion && m_isCarRegion == 0)
		{
			ProcessTrackCamRegionTouchEvent(x,y,touchType);
			ProcessCarRegionTouchEvent(x,y,touchType);
		}
		ccagIcon[CCAG_RED_TRACK_CAMERA]->onClickListener(x,y,touchType);
		if(m_isTrackRegion == 0 || m_isCarRegion == 1)
		{
			ccagIcon[CCAG_CAMERA_FRONT]->onClickListener(x,y,touchType);
			ccagIcon[CCAG_CAMERA_REAR]->onClickListener(x,y,touchType);
			ccagIcon[CCAG_CAMERA_LEFT]->onClickListener(x,y,touchType);
			ccagIcon[CCAG_CAMERA_RIGHT]->onClickListener(x,y,touchType);
		}
		SetCustomView(m_currentViewState);

	}
	

	return 0;
}
int CSVChanganHmi::Update(Hmi_Message_T& hmiMsg)
{   
	if(m_visibilityStatus == 0)
	{
		return 0;
	}
	
	ProcessIconTouchEvent();
	ProcessAvmStatus();
	SetElemProperty();

	ccagIcon[CCAG_RED_TRACK]->Update();
	ccagIcon[CCAG_RED_TRACK_CAMERA]->Update();

	ccagIcon[CCAG_CAMERA_FRONT]->Update();
	ccagIcon[CCAG_CAMERA_REAR]->Update();
	ccagIcon[CCAG_CAMERA_LEFT]->Update();
	ccagIcon[CCAG_CAMERA_RIGHT]->Update();

    return 0;
}

int CSVChanganHmi::SetSurroundViewCamElem()
{
	float leftPanelWidth = 120.0;

	ccagIconData[CCAG_RED_TRACK].width = 378.0;
	ccagIconData[CCAG_RED_TRACK].height = 487.0;
	ccagIconData[CCAG_RED_TRACK].pos[0] = (m_stitchRegionWidth - ccagIconData[CCAG_RED_TRACK].width)/2.0 + leftPanelWidth;
    ccagIconData[CCAG_RED_TRACK].pos[1] = (m_stitchRegionHeight - ccagIconData[CCAG_RED_TRACK].height)/2.0 + 0.0;
	ccagIconData[CCAG_RED_TRACK].show_flag = 1;
    ccagIconData[CCAG_RED_TRACK].icon_type = STATIC_ICON;
    ccagIconData[CCAG_RED_TRACK].show_icon_num = 0;
    ccagIconData[CCAG_RED_TRACK].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_RED_TRACK].icon_file_name[1] = new char [50];

	sprintf(ccagIconData[CCAG_RED_TRACK].icon_file_name[0],"%sCar/red_track.dds",XR_RES);  //white_track
    sprintf(ccagIconData[CCAG_RED_TRACK].icon_file_name[1],"%sCar/white_track.dds",XR_RES);

	ccagIcon[CCAG_RED_TRACK] = new HMIButton(&ccagIconData[CCAG_RED_TRACK], m_uiNode);

	ccagIconData[CCAG_RED_TRACK_CAMERA].pos[0] = 0.0;
    ccagIconData[CCAG_RED_TRACK_CAMERA].pos[1] = 0.0;
	ccagIconData[CCAG_RED_TRACK_CAMERA].width = 64.0;
	ccagIconData[CCAG_RED_TRACK_CAMERA].height = 64.0;

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + (ccagIconData[CCAG_RED_TRACK].width - ccagIconData[CCAG_RED_TRACK_CAMERA].width)/2.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] - ccagIconData[CCAG_RED_TRACK_CAMERA].height/2.0 + 10.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT][CCAG_ELEM_Y];
	
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + (ccagIconData[CCAG_RED_TRACK].width - ccagIconData[CCAG_RED_TRACK_CAMERA].width)/2.0 + 5.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + ccagIconData[CCAG_RED_TRACK].height - ccagIconData[CCAG_RED_TRACK_CAMERA].height/2.0 - 10.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR][CCAG_ELEM_Y];
	
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] - 8.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + (ccagIconData[CCAG_RED_TRACK].height)/2.0 - 25.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_LEFT][CCAG_ELEM_Y];

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + ccagIconData[CCAG_RED_TRACK].width - ccagIconData[CCAG_RED_TRACK_CAMERA].width + 8.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + (ccagIconData[CCAG_RED_TRACK].height)/2.0 - 25.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_RIGHT][CCAG_ELEM_Y];

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + 10.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + ccagIconData[CCAG_RED_TRACK].height/6.5;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_LEFT][CCAG_ELEM_Y];

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + ccagIconData[CCAG_RED_TRACK].width* 2.4/3.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + ccagIconData[CCAG_RED_TRACK].height/6.5;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT][CCAG_ELEM_Y];

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + 15.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + ccagIconData[CCAG_RED_TRACK].height* 2.2/3.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_LEFT][CCAG_ELEM_Y];

	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_X] = ccagIconData[CCAG_RED_TRACK].pos[0] + ccagIconData[CCAG_RED_TRACK].width* 2.4/3.0;
	m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_Y] = ccagIconData[CCAG_RED_TRACK].pos[1] + ccagIconData[CCAG_RED_TRACK].height* 2.2/3.0;
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_X] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_X];
	m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_Y] = m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_REAR_RIGHT][CCAG_ELEM_Y];

	ccagIconData[CCAG_RED_TRACK_CAMERA].show_flag = 1;
    ccagIconData[CCAG_RED_TRACK_CAMERA].icon_type = DYNAMIC_ICON;
    ccagIconData[CCAG_RED_TRACK_CAMERA].show_icon_num = 0;
    ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[1] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[2] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[3] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[4] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[5] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[6] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[7] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[8] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[9] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[10] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[11] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[12] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[13] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[14] = new char [50];
	ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[15] = new char [50];

    sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[0],"%sCar/front_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[1],"%sCar/rear_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[2],"%sCar/left_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[3],"%sCar/right_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[4],"%sCar/front_left_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[5],"%sCar/front_right_white_camera.dds",XR_RES);
    sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[6],"%sCar/rear_left_white_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[7],"%sCar/rear_right_white_camera.dds",XR_RES);
    sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[8],"%sCar/front_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[9],"%sCar/rear_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[10],"%sCar/left_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[11],"%sCar/right_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[12],"%sCar/front_left_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[13],"%sCar/front_right_yellow_camera.dds",XR_RES);
    sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[14],"%sCar/rear_left_yellow_camera.dds",XR_RES);
	sprintf(ccagIconData[CCAG_RED_TRACK_CAMERA].icon_file_name[15],"%sCar/rear_right_yellow_camera.dds",XR_RES);

	ccagIconData[CCAG_RED_TRACK_CAMERA].delegate_func = OnPressTrackCam;
	ccagIcon[CCAG_RED_TRACK_CAMERA] = new HMIButton(&ccagIconData[CCAG_RED_TRACK_CAMERA], m_uiNode);

	float pos_x = (m_stitchRegionWidth)/2.0 + leftPanelWidth;
	float pos_y = (1.0 - car_rect[1]) * (m_stitchRegionHeight)/2.0;

	ccagIconData[CCAG_CAMERA_FRONT].width = 64.0;
	ccagIconData[CCAG_CAMERA_FRONT].height = 64.0;
	ccagIconData[CCAG_CAMERA_FRONT].pos[0] = pos_x - ccagIconData[CCAG_CAMERA_FRONT].width/2.0;
    ccagIconData[CCAG_CAMERA_FRONT].pos[1] =  pos_y;
	ccagIconData[CCAG_CAMERA_FRONT].show_flag = 1;
    ccagIconData[CCAG_CAMERA_FRONT].icon_type = STATIC_ICON;
    ccagIconData[CCAG_CAMERA_FRONT].show_icon_num = 0;
    ccagIconData[CCAG_CAMERA_FRONT].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_CAMERA_FRONT].icon_file_name[1] = new char [50];

	sprintf(ccagIconData[CCAG_CAMERA_FRONT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(ccagIconData[CCAG_CAMERA_FRONT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);

	ccagIcon[CCAG_CAMERA_FRONT] = new HMIButton(&ccagIconData[CCAG_CAMERA_FRONT], m_uiNode);
	ccagIconData[CCAG_CAMERA_FRONT].delegate_func = OnPressFrontCam;

	pos_x = (1.0 + car_rect[0]) * (m_stitchRegionWidth)/2.0 + leftPanelWidth;
	pos_y = (1.0 - car_rect[3]) * (m_stitchRegionHeight)/2.0;

	ccagIconData[CCAG_CAMERA_LEFT].width = 64.0;
	ccagIconData[CCAG_CAMERA_LEFT].height = 64.0;
	ccagIconData[CCAG_CAMERA_LEFT].pos[0] = pos_x - ccagIconData[CCAG_CAMERA_LEFT].width;
    ccagIconData[CCAG_CAMERA_LEFT].pos[1] = pos_y - 2.0 * ccagIconData[CCAG_CAMERA_LEFT].height;
	ccagIconData[CCAG_CAMERA_LEFT].show_flag = 1;
    ccagIconData[CCAG_CAMERA_LEFT].icon_type = STATIC_ICON;
    ccagIconData[CCAG_CAMERA_LEFT].show_icon_num = 0;
    ccagIconData[CCAG_CAMERA_LEFT].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_CAMERA_LEFT].icon_file_name[1] = new char [50];

	sprintf(ccagIconData[CCAG_CAMERA_LEFT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(ccagIconData[CCAG_CAMERA_LEFT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);

	ccagIcon[CCAG_CAMERA_LEFT] = new HMIButton(&ccagIconData[CCAG_CAMERA_LEFT], m_uiNode);
	ccagIconData[CCAG_CAMERA_LEFT].delegate_func = OnPressLeftCam;

	pos_x = (1.0 + car_rect[2]) * (m_stitchRegionWidth)/2.0 + leftPanelWidth;
	pos_y = (1.0 - car_rect[3]) * (m_stitchRegionHeight)/2.0;

	ccagIconData[CCAG_CAMERA_RIGHT].width = 64.0;
	ccagIconData[CCAG_CAMERA_RIGHT].height = 64.0;
	ccagIconData[CCAG_CAMERA_RIGHT].pos[0] = pos_x + ccagIconData[CCAG_CAMERA_RIGHT].width/3.5;
    ccagIconData[CCAG_CAMERA_RIGHT].pos[1] = pos_y - 2.0 * ccagIconData[CCAG_CAMERA_RIGHT].height;
	ccagIconData[CCAG_CAMERA_RIGHT].show_flag = 1;
    ccagIconData[CCAG_CAMERA_RIGHT].icon_type = STATIC_ICON;
    ccagIconData[CCAG_CAMERA_RIGHT].show_icon_num = 0;
    ccagIconData[CCAG_CAMERA_RIGHT].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_CAMERA_RIGHT].icon_file_name[1] = new char [50];

	sprintf(ccagIconData[CCAG_CAMERA_RIGHT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(ccagIconData[CCAG_CAMERA_RIGHT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);

	ccagIcon[CCAG_CAMERA_RIGHT] = new HMIButton(&ccagIconData[CCAG_CAMERA_RIGHT], m_uiNode);
	ccagIconData[CCAG_CAMERA_RIGHT].delegate_func = OnPressRightCam;

	pos_x = (m_stitchRegionWidth)/2.0 + leftPanelWidth;;
	pos_y = (1.0 - car_rect[3]) * (m_stitchRegionHeight)/2.0;

	ccagIconData[CCAG_CAMERA_REAR].width = 64.0;
	ccagIconData[CCAG_CAMERA_REAR].height = 64.0;
	ccagIconData[CCAG_CAMERA_REAR].pos[0] = pos_x - ccagIconData[CCAG_CAMERA_REAR].width/3.0;
    ccagIconData[CCAG_CAMERA_REAR].pos[1] = pos_y - ccagIconData[CCAG_CAMERA_REAR].height;
	ccagIconData[CCAG_CAMERA_REAR].show_flag = 1;
    ccagIconData[CCAG_CAMERA_REAR].icon_type = STATIC_ICON;
    ccagIconData[CCAG_CAMERA_REAR].show_icon_num = 0;
    ccagIconData[CCAG_CAMERA_REAR].icon_file_name[0] = new char [50];
	ccagIconData[CCAG_CAMERA_REAR].icon_file_name[1] = new char [50];

	sprintf(ccagIconData[CCAG_CAMERA_REAR].icon_file_name[0],"%sCar/front_white_camera.dds",XR_RES);  //white_track
    sprintf(ccagIconData[CCAG_CAMERA_REAR].icon_file_name[1],"%sCar/front_yellow_camera.dds",XR_RES);

	ccagIcon[CCAG_CAMERA_REAR] = new HMIButton(&ccagIconData[CCAG_CAMERA_REAR], m_uiNode);
	ccagIconData[CCAG_CAMERA_REAR].delegate_func = OnPressRearCam;

	return BUTTON_NORMAL;
}

int CSVChanganHmi::ProcessAvmStatus()
{
	static unsigned char lastAvmDisplayView = 100;
	unsigned char currentAvmDisplayView = 0;
	GetAvmDisplayView(currentAvmDisplayView);
	if(lastAvmDisplayView != currentAvmDisplayView)
	{
		switch(currentAvmDisplayView)
		{
			case CCAG_FRONT_3D_VIEW:
			case CCAG_FRONT_SINGLE_VIEW:
				ccagIcon[CCAG_CAMERA_FRONT]->ButtonEffectClick();
			break;
			case CCAG_REAR_3D_VIEW:
			case CCAG_REAR_SINGLE_VIEW:
				ccagIcon[CCAG_CAMERA_REAR]->ButtonEffectClick();
				break;
			case CCAG_LEFT_SINGLE_VIEW:
			case CCAG_LEFT_REAR_3D_VIEW:
			case CCAG_LEFT_TURN_SIGNAL_3D_VIEW:
			case CCAG_LEFT_FRONT_3D_VIEW:
				ccagIcon[CCAG_CAMERA_LEFT]->ButtonEffectClick();
			break;
			case CCAG_RIGHT_REAR_3D_VIEW:
			case CCAG_RIGHT_FRONT_3D_VIEW:
			case CCAG_RIGHT_TURN_SIGNAL_3D_VIEW:
			case CCAG_RIGHT_SINGLE_VIEW:
				ccagIcon[CCAG_CAMERA_RIGHT]->ButtonEffectClick();
				break;
			default:
			break;
		}
	}

	lastAvmDisplayView = currentAvmDisplayView;
}
int CSVChanganHmi::ProcessCarRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action)
{
	static int  touch_action = action;
	static int  touch_pos_x = 0;
	static int  touch_pos_y = 0;
	

	if(SCREEN_TOUCHED == touch_action)
	{
		touch_pos_x = pos_x;
		touch_pos_y = pos_y;
	}
	else
	{
		return BUTTON_NORMAL; 
	}


    if(touch_pos_x > CAR_RECT_X 
            && touch_pos_x < CAR_RECT_X  + CAR_RECT_WIDTH
            && touch_pos_y > CAR_RECT_Y  
            && touch_pos_y < CAR_RECT_Y +CAR_RECT_HEIGHT )
    {
        m_trackColor = 1;
        m_isCarRegion = 1;
        m_frontCamVisibility = 1;
        m_rearCamVisibility = 1;
        m_leftCamVisibility = 1;
        m_rightCamVisibility = 1;
        m_frontCamColor = 0;
        m_rearCamColor = 0;
        m_leftCamColor = 0;
        m_rightCamColor = 0;
    }

	return BUTTON_NORMAL;
}

int CSVChanganHmi::ProcessTrackCamRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action)
{
	static int  touch_action = action;
	static int  touch_pos_x = 0;
	static int  touch_pos_y = 0;

	if(SCREEN_TOUCHED == touch_action)
	{
		touch_pos_x = pos_x;
		touch_pos_y = pos_y;
	}
	else
	{
		return BUTTON_NORMAL; 
	}

	for(int index = 0; index < CCAG_TRACK_CAMERA_REGION_NUMS;index++)
	{
		if(touch_pos_x > m_trackCamRegion[index][CCAG_ELEM_X] 
				&& touch_pos_x < m_trackCamRegion[index][CCAG_ELEM_X]  + m_trackCamRegion[index][CCAG_ELEM_WIDTH]
				&& touch_pos_y > m_trackCamRegion[index][CCAG_ELEM_Y]  
				&& touch_pos_y < m_trackCamRegion[index][CCAG_ELEM_Y]  + m_trackCamRegion[index][CCAG_ELEM_HEIGHT] )
		{
			m_currentTrackCamRegionIndex = index;
			m_currentViewState = m_currentTrackCamRegionIndex;
                        m_storeTrackRegion = m_currentTrackCamRegionIndex;
		}
	}
	return BUTTON_NORMAL;
}
int CSVChanganHmi::SetElemProperty()
{
	ccagIcon[CCAG_RED_TRACK]->SetVisibility(m_trackVisibility);
	ccagIcon[CCAG_RED_TRACK_CAMERA]->SetVisibility(m_trackCamVisibility);
	ccagIcon[CCAG_CAMERA_FRONT]->SetVisibility(m_frontCamVisibility);
	ccagIcon[CCAG_CAMERA_REAR]->SetVisibility(m_rearCamVisibility);
	ccagIcon[CCAG_CAMERA_LEFT]->SetVisibility(m_leftCamVisibility);
	ccagIcon[CCAG_CAMERA_RIGHT]->SetVisibility(m_rightCamVisibility);

	ccagIconData[CCAG_RED_TRACK_CAMERA].show_icon_num = m_currentTrackCamRegionIndex + m_isTrackRegion*CCAG_TRACK_CAMERA_REGION_NUMS;
	
	ccagIconData[CCAG_RED_TRACK].show_icon_num = m_trackColor;

	ccagIconData[CCAG_CAMERA_FRONT].show_icon_num = m_frontCamColor;
	ccagIconData[CCAG_CAMERA_REAR].show_icon_num = m_rearCamColor;
	ccagIconData[CCAG_CAMERA_LEFT].show_icon_num = m_leftCamColor;
	ccagIconData[CCAG_CAMERA_RIGHT].show_icon_num = m_rightCamColor;

	switch(m_currentTrackCamRegionIndex)
	{
	case CCAG_TRACK_CAMERA_REGION_FRONT:
	case CCAG_TRACK_CAMERA_REGION_REAR:
	case CCAG_TRACK_CAMERA_REGION_LEFT:
	case CCAG_TRACK_CAMERA_REGION_RIGHT:
	case CCAG_TRACK_CAMERA_REGION_FRONT_LEFT:
	case CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT:
	case CCAG_TRACK_CAMERA_REGION_REAR_LEFT:
	case CCAG_TRACK_CAMERA_REGION_REAR_RIGHT:
		m_trackCamPosX = m_trackCamIconRegion[m_currentTrackCamRegionIndex][CCAG_ELEM_X];
		m_trackCamPosY = m_trackCamIconRegion[m_currentTrackCamRegionIndex][CCAG_ELEM_Y];
		break;
	default:
		break;
	}

	ccagIconData[CCAG_RED_TRACK_CAMERA].pos[0] = m_trackCamPosX;
	ccagIconData[CCAG_RED_TRACK_CAMERA].pos[1] = m_trackCamPosY;


	return BUTTON_NORMAL;
}

void OnPressTrackCam()
{
	//CSVChanganHmi::m_frontTrackCamVisibility = 0;
	CSVChanganHmi::m_isTrackRegion = 1;
	CSVChanganHmi::m_trackCamColor = 1;
	CSVChanganHmi::m_trackColor = 0;
	CSVChanganHmi::m_trackVisibility = 1;
	CSVChanganHmi::m_frontCamVisibility = 0;
	CSVChanganHmi::m_rearCamVisibility = 0;
	CSVChanganHmi::m_leftCamVisibility = 0;
	CSVChanganHmi::m_rightCamVisibility = 0;
	CSVChanganHmi::m_frontCamColor = 0;
	CSVChanganHmi::m_rearCamColor = 0;
	CSVChanganHmi::m_leftCamColor = 0;
	CSVChanganHmi::m_rightCamColor = 0;
	CSVChanganHmi::m_isCarRegion = 0;

}
void OnPressFrontCam()
{
	CSVChanganHmi::m_isTrackRegion = 0;
	CSVChanganHmi::m_trackVisibility = 0;
	CSVChanganHmi::m_frontCamColor = 1;
	CSVChanganHmi::m_rearCamColor = 0;
	CSVChanganHmi::m_leftCamColor = 0;
	CSVChanganHmi::m_rightCamColor = 0;
	CSVChanganHmi::m_isCarRegion = 0;
	CSVChanganHmi::m_frontCamVisibility = 1;
	CSVChanganHmi::m_rearCamVisibility = 1;
	CSVChanganHmi::m_leftCamVisibility = 1;
	CSVChanganHmi::m_rightCamVisibility = 1;
	CSVChanganHmi::m_currentViewState = CCAG_CAMERA_REGION_FRONT;
}
void OnPressRearCam()
{
	CSVChanganHmi::m_isTrackRegion = 0;
	CSVChanganHmi::m_trackVisibility = 0;
	CSVChanganHmi::m_rearCamColor = 1;
	CSVChanganHmi::m_frontCamColor = 0;
	CSVChanganHmi::m_leftCamColor = 0;
	CSVChanganHmi::m_rightCamColor = 0;
	CSVChanganHmi::m_isCarRegion = 0;
	
	CSVChanganHmi::m_frontCamVisibility = 1;
	CSVChanganHmi::m_rearCamVisibility = 1;
	CSVChanganHmi::m_leftCamVisibility = 1;
	CSVChanganHmi::m_rightCamVisibility = 1;

	CSVChanganHmi::m_currentViewState = CCAG_CAMERA_REGION_REAR;

}
void OnPressLeftCam()
{
	CSVChanganHmi::m_isTrackRegion = 0;
	CSVChanganHmi::m_trackVisibility = 0;
	CSVChanganHmi::m_leftCamColor = 1;
	CSVChanganHmi::m_frontCamColor = 0;
	CSVChanganHmi::m_rearCamColor = 0;
	CSVChanganHmi::m_rightCamColor = 0;
	CSVChanganHmi::m_isCarRegion = 0;
	CSVChanganHmi::m_frontCamVisibility = 1;
	CSVChanganHmi::m_rearCamVisibility = 1;
	CSVChanganHmi::m_leftCamVisibility = 1;
	CSVChanganHmi::m_rightCamVisibility = 1;
	CSVChanganHmi::m_currentViewState = CCAG_CAMERA_REGION_LEFT;

}
void OnPressRightCam()
{
	CSVChanganHmi::m_isTrackRegion = 0;
	CSVChanganHmi::m_trackVisibility = 0;
	CSVChanganHmi::m_rightCamColor = 1;
	CSVChanganHmi::m_frontCamColor = 0;
	CSVChanganHmi::m_rearCamColor = 0;
	CSVChanganHmi::m_leftCamColor = 0;
	CSVChanganHmi::m_isCarRegion = 0;
	CSVChanganHmi::m_frontCamVisibility = 1;
	CSVChanganHmi::m_rearCamVisibility = 1;
	CSVChanganHmi::m_leftCamVisibility = 1;
	CSVChanganHmi::m_rightCamVisibility = 1;
	CSVChanganHmi::m_currentViewState = CCAG_CAMERA_REGION_RIGHT;

}