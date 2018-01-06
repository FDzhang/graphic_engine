#include "CSVTrainedParkingHmi.h"
#include <log/log.h>

extern Region CenterReg;
extern Region RightReg;

enum
{
 PROMPT_BOX_CAPTURE_IMAGE = 0,
 PROMPT_BOX_RESTRUCTION,
 PROMPT_BOX_SUCCESS,
 PROMPT_BOX_FAILED,
 PROMPT_BOX_SEARCHING_PATH,
 PROMPT_BOX_ASKING_CLICK,
 PROMPT_BOX_FINISHED,
 
 PROMPT_BOX_NUM,

 PROMPT_BOX_SEARCHING_SUCCESS = 0,
 PROMPT_BOX_SEARCHING_FAILED,
 PROMPT_BOX_SEARCHING_PROCESSING,
 PROMPT_BOX_START_LOCATION,
 PROMPT_BOX_LOCATION_SUCCESS,
 PROMPT_BOX_LOCATION_FAILED,

 PARKING_IN_ICON_NORMAL = 0,
 PARKING_IN_ICON_PRESS,
};

enum{
    TP_BUTTONRFLAG_ERROR = 0,//Ĭ��״̬
    TP_BUTTONRFLAG_SEARCHING_PATH_INIT = 1,//����·����
    TP_BUTTONRFLAG_SEARCHING_PATH_SUCESS,//�����ɹ�
    TP_BUTTONRFLAG_SEARCHING_PATH_FAILED,//����ʧ��
    TP_BUTTONRFLAG_LOC_INIT,//��ʼ��λ
    TP_BUTTONRFLAG_LOC_INIT_SUCESS,//��λ�ɹ�
    TP_BUTTONRFLAG_LOC_INIT_FAILED  // ��λʧ��
};


#define RadianToAngle(x) ((x) * 180.0/3.14159)

const float map_img_width = 560.0;
const float map_world_width = 80.0;
const float map_img_height = 560.0;
const float map_world_height = 80.0;
const float map_x_offside = 193.0;
const float map_y_offside = 337.0;

static void OnPressCaptureImageIcon();
static void OnPressNavigatingIcon();
static void OnPressControlIcon();
static void OnPressParkingIcon();
static void OnPressParkingInIcon();
static void OnPressParkingOutIcon();

uint8_t CSVTrainedParkingHmi::m_tpCaptureImageIconShowNum = 0;
uint8_t CSVTrainedParkingHmi::m_tpNavigatingIconShowNum = 0;
uint8_t CSVTrainedParkingHmi::m_tpControlIconShowNum = 0;
uint8_t CSVTrainedParkingHmi::m_tpParkingIconShowNum = 0;

uint8_t CSVTrainedParkingHmi::m_tpCaptureImageIconVisibility= 1;
uint8_t CSVTrainedParkingHmi::m_tpNavigatingIconVisibility = 1;
uint8_t CSVTrainedParkingHmi::m_tpControlIconVisibility = 1;
uint8_t CSVTrainedParkingHmi::m_tpParkingIconVisibility = 1;

CGpuAvmEventDelegate* CSVTrainedParkingHmi::m_tpButtonClickEvent = NULL;//new CGpuAvmEventDelegate(ALGOHMI_EVENT_NAME);

CSVTrainedParkingHmi::CSVTrainedParkingHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	m_tpButtonClickEvent = new CGpuAvmEventDelegate(TPHMI_EVENT_NAME);
	
	memset(m_trigger, NULL, TP_ICON_NUMS * sizeof(IActionTrigger*));
	memset(tpIcon, 0, sizeof(HMIButton *) * TP_ICON_NUMS);
	m_hmiScroll = NULL;
}
CSVTrainedParkingHmi::~CSVTrainedParkingHmi()
{
    for(int i = 0; i < TP_ICON_NUMS; i++)
    {
    	SAFE_DELETE(tpIcon[i])
		SAFE_DELETE(m_trigger[i]);
    }
	SAFE_DELETE(m_hmiScroll);
	SAFE_DELETE(m_pTextBox);
}

int CSVTrainedParkingHmi::Init(int window_width, int window_height)
{
    float f_stich_ratio = 0.35;
    float black_width = 80.0;
    float cutLine = 8.0;
	
    m_showRegionWidth = window_width * (1.0 - f_stich_ratio) -100 ;
    m_showRegionHeight = window_height - 2.0 * black_width;

	float tp_icon_width = 48;
	float tp_icon_height = 48;
    
    tpIconPos[TP_CAPTURE_IMAGE_ICON][0] = window_width * f_stich_ratio + 100 + m_showRegionWidth/8 - 24;
    tpIconPos[TP_CAPTURE_IMAGE_ICON][1] = black_width + 16;
    tpIconWidth[TP_CAPTURE_IMAGE_ICON] = tp_icon_width;
    tpIconHeight[TP_CAPTURE_IMAGE_ICON] = tp_icon_height;

    tpIconPos[TP_NAVIGATING_ICON][0] = window_width * f_stich_ratio + 100 + m_showRegionWidth/8 - 24 + m_showRegionWidth/4;
    tpIconPos[TP_NAVIGATING_ICON][1] = black_width + 16;
    tpIconWidth[TP_NAVIGATING_ICON] = tp_icon_width;
    tpIconHeight[TP_NAVIGATING_ICON] = tp_icon_height;

    tpIconPos[TP_CONTROL_ICON][0] = window_width * f_stich_ratio + 100 + m_showRegionWidth/8 - 24 + m_showRegionWidth/4*2;
    tpIconPos[TP_CONTROL_ICON][1] = black_width + 16;
    tpIconWidth[TP_CONTROL_ICON] = tp_icon_width;
    tpIconHeight[TP_CONTROL_ICON] = tp_icon_height;

    tpIconPos[TP_PARKING_IN_ICON][0] = window_width * f_stich_ratio + 100 + m_showRegionWidth/8 - 24+ m_showRegionWidth/4*3;
    tpIconPos[TP_PARKING_IN_ICON][1] = black_width + 16;
    tpIconWidth[TP_PARKING_IN_ICON] = tp_icon_width;
    tpIconHeight[TP_PARKING_IN_ICON] = tp_icon_height;

	tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][0] = window_width * f_stich_ratio + 100 + m_showRegionWidth/2 - 162;
    tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][1] = black_width + m_showRegionHeight/2 - 46;
    tpIconWidth[TP_CAPTURE_IMAGE_PROMPT_BOX] = 324;
    tpIconHeight[TP_CAPTURE_IMAGE_PROMPT_BOX] = 92;

    tpIconWidth[TP_CAPTURE_IMAGE_PROCESS_BAR_BK] = 224;
    tpIconHeight[TP_CAPTURE_IMAGE_PROCESS_BAR_BK] = 7;
	tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][0] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][0] + (tpIconWidth[TP_CAPTURE_IMAGE_PROMPT_BOX] - tpIconWidth[TP_CAPTURE_IMAGE_PROCESS_BAR_BK])/2;
    tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][1] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][1] + tpIconHeight[TP_CAPTURE_IMAGE_PROMPT_BOX] - tpIconHeight[TP_CAPTURE_IMAGE_PROCESS_BAR_BK] - 10;

    tpIconPos[TP_MAP_IMAGE][0] = window_width * f_stich_ratio + 100.0;
    tpIconPos[TP_MAP_IMAGE][1] = black_width;
    tpIconWidth[TP_MAP_IMAGE] = m_showRegionWidth;
    tpIconHeight[TP_MAP_IMAGE] = m_showRegionHeight;

	tpIconWidth[TP_DRIVING_CAR] = 26;
    tpIconHeight[TP_DRIVING_CAR] = 52;
	m_carIconPos[0] = window_width * f_stich_ratio + cutLine + 100.0 - 0.5 * tpIconWidth[TP_DRIVING_CAR];
	m_carIconPos[1] = black_width - 42.0;
	
    tpIconPos[TP_DRIVING_CAR][0] = m_carIconPos[0] + map_x_offside * m_showRegionWidth/map_img_width;
    tpIconPos[TP_DRIVING_CAR][1] = m_carIconPos[1] + (map_y_offside * m_showRegionHeight/map_img_height) ;
	m_anchorPointX = 0.5;
	m_anchorPointY = 0.8;
	m_rotateAlpha = 0.0;
	m_rotateShowFlag = 0;


    SetTrainedParkingElemParams();

    return HMI_SUCCESS;
}

int CSVTrainedParkingHmi::SetTrainedParkingElemParams()
{
	tpIconData[TP_MAP_IMAGE].pos[0] = tpIconPos[TP_MAP_IMAGE][0];
	tpIconData[TP_MAP_IMAGE].pos[1] = tpIconPos[TP_MAP_IMAGE][1];
	tpIconData[TP_MAP_IMAGE].width= tpIconWidth[TP_MAP_IMAGE];
	tpIconData[TP_MAP_IMAGE].height= tpIconHeight[TP_MAP_IMAGE];
	tpIconData[TP_MAP_IMAGE].show_flag = 0;
    tpIconData[TP_MAP_IMAGE].icon_type = STATIC_ICON;
    tpIconData[TP_MAP_IMAGE].show_icon_num = 0;
    tpIconData[TP_MAP_IMAGE].icon_file_name[0] = new char [50];
	tpIconData[TP_MAP_IMAGE].trigger = m_trigger[TP_MAP_IMAGE];

	sprintf(tpIconData[TP_MAP_IMAGE].icon_file_name[0],"%sCar/mapUP.dds",XR_RES); 
	tpIcon[TP_MAP_IMAGE] = new HMIButton(&tpIconData[TP_MAP_IMAGE], m_uiNode);
	m_tpMapImageVisibility = 0;

	tpIconData[TP_DRIVING_CAR].pos[0] = tpIconPos[TP_DRIVING_CAR][0];
	tpIconData[TP_DRIVING_CAR].pos[1] = tpIconPos[TP_DRIVING_CAR][1];
	tpIconData[TP_DRIVING_CAR].width= tpIconWidth[TP_DRIVING_CAR];
	tpIconData[TP_DRIVING_CAR].height= tpIconHeight[TP_DRIVING_CAR];
	tpIconData[TP_DRIVING_CAR].show_flag = 0;
    tpIconData[TP_DRIVING_CAR].icon_type = DYNAMIC_ICON;
    tpIconData[TP_DRIVING_CAR].show_icon_num = 0;
    tpIconData[TP_DRIVING_CAR].icon_file_name[0] = new char [50];
	tpIconData[TP_DRIVING_CAR].trigger = m_trigger[TP_DRIVING_CAR];

	sprintf(tpIconData[TP_DRIVING_CAR].icon_file_name[0],"%sCar/driving_alpha_car.dds",XR_RES); 
	tpIcon[TP_DRIVING_CAR] = new HMIButton(&tpIconData[TP_DRIVING_CAR], m_uiNode);
	m_tpDrivingCarVisibility = 0;

	char current_pos_value[100] = "x,y";
	m_text[0].pos[0] = tpIconPos[TP_DRIVING_CAR][0] - 120;
	m_text[0].pos[1] = tpIconPos[TP_DRIVING_CAR][1] + 20;
	m_text[0].line_num = 1;
	m_text[0].width = 1;
	m_text[0].font_size = 24;
	m_text[0].text_color[0] = 0.0;
	m_text[0].text_color[1] = 1.0;
	m_text[0].text_color[2] = 0.0;
	m_text[0].show_flag = 0;
	m_text[0].text_content[0] = new char[50];
	sprintf(m_text[0].text_content[0],"%0.2f,%0.2f",m_text[0].pos[0], m_text[0].pos[1]);

	m_pTextBox = new HMITextBox(CenterReg,RightReg);
	m_pTextBox->Init(m_uiNode,XR_RES"text_frame.dds",XR_RES"text_box.ttf");
	int temp;
	m_pTextBox->Add(m_uiNode,&(m_text[0]),&temp);

    tpIconData[TP_CAPTURE_IMAGE_ICON].pos[0] = tpIconPos[TP_CAPTURE_IMAGE_ICON][0];
	tpIconData[TP_CAPTURE_IMAGE_ICON].pos[1] = tpIconPos[TP_CAPTURE_IMAGE_ICON][1];
	tpIconData[TP_CAPTURE_IMAGE_ICON].width= tpIconWidth[TP_CAPTURE_IMAGE_ICON];
	tpIconData[TP_CAPTURE_IMAGE_ICON].height= tpIconHeight[TP_CAPTURE_IMAGE_ICON];
	tpIconData[TP_CAPTURE_IMAGE_ICON].show_flag = 0;
    tpIconData[TP_CAPTURE_IMAGE_ICON].icon_type = STATIC_ICON;
	tpIconData[TP_CAPTURE_IMAGE_ICON].delegate_func = OnPressCaptureImageIcon;
    tpIconData[TP_CAPTURE_IMAGE_ICON].show_icon_num = 0;
    tpIconData[TP_CAPTURE_IMAGE_ICON].icon_file_name[0] = new char [50];
	tpIconData[TP_CAPTURE_IMAGE_ICON].icon_file_name[1] = new char [50];	
	tpIconData[TP_CAPTURE_IMAGE_ICON].trigger = m_trigger[TP_CAPTURE_IMAGE_ICON];
	m_tpCaptureImageIconShowNum = 0;
	m_tpCaptureImageIconVisibility =1;

	sprintf(tpIconData[TP_CAPTURE_IMAGE_ICON].icon_file_name[0],"%sCar/capture_image_disable.dds",XR_RES); 
    sprintf(tpIconData[TP_CAPTURE_IMAGE_ICON].icon_file_name[1],"%sCar/capture_image_enable.dds",XR_RES);

	tpIcon[TP_CAPTURE_IMAGE_ICON] = new HMIButton(&tpIconData[TP_CAPTURE_IMAGE_ICON], m_uiNode);

	tpIconData[TP_NAVIGATING_ICON].pos[0] = tpIconPos[TP_NAVIGATING_ICON][0];
	tpIconData[TP_NAVIGATING_ICON].pos[1] = tpIconPos[TP_NAVIGATING_ICON][1];
	tpIconData[TP_NAVIGATING_ICON].width= tpIconWidth[TP_NAVIGATING_ICON];
	tpIconData[TP_NAVIGATING_ICON].height= tpIconHeight[TP_NAVIGATING_ICON];
	tpIconData[TP_NAVIGATING_ICON].show_flag = 0;
    tpIconData[TP_NAVIGATING_ICON].icon_type = STATIC_ICON;
	tpIconData[TP_NAVIGATING_ICON].delegate_func = OnPressNavigatingIcon;
    tpIconData[TP_NAVIGATING_ICON].show_icon_num = 0;
    tpIconData[TP_NAVIGATING_ICON].icon_file_name[0] = new char [50];
	tpIconData[TP_NAVIGATING_ICON].icon_file_name[1] = new char [50];	
	tpIconData[TP_NAVIGATING_ICON].trigger = m_trigger[TP_NAVIGATING_ICON];
	m_tpNavigatingIconShowNum = 0;
	m_tpNavigatingIconVisibility = 1;

	sprintf(tpIconData[TP_NAVIGATING_ICON].icon_file_name[0],"%sCar/navigating_disable.dds",XR_RES); 
    sprintf(tpIconData[TP_NAVIGATING_ICON].icon_file_name[1],"%sCar/navigating_enable.dds",XR_RES);

	tpIcon[TP_NAVIGATING_ICON] = new HMIButton(&tpIconData[TP_NAVIGATING_ICON], m_uiNode);

	tpIconData[TP_CONTROL_ICON].pos[0] = tpIconPos[TP_CONTROL_ICON][0];
	tpIconData[TP_CONTROL_ICON].pos[1] = tpIconPos[TP_CONTROL_ICON][1];
	tpIconData[TP_CONTROL_ICON].width= tpIconWidth[TP_CONTROL_ICON];
	tpIconData[TP_CONTROL_ICON].height= tpIconHeight[TP_CONTROL_ICON];
	tpIconData[TP_CONTROL_ICON].show_flag = 0;
    tpIconData[TP_CONTROL_ICON].icon_type = STATIC_ICON;
	tpIconData[TP_CONTROL_ICON].delegate_func = OnPressControlIcon;
    tpIconData[TP_CONTROL_ICON].show_icon_num = 0;
    tpIconData[TP_CONTROL_ICON].icon_file_name[0] = new char [50];
	tpIconData[TP_CONTROL_ICON].icon_file_name[1] = new char [50];	
	tpIconData[TP_CONTROL_ICON].trigger = m_trigger[TP_CONTROL_ICON];
	m_tpControlIconShowNum = 0;
	m_tpControlIconVisibility = 1;

	sprintf(tpIconData[TP_CONTROL_ICON].icon_file_name[0],"%sCar/control_disable.dds",XR_RES); 
    sprintf(tpIconData[TP_CONTROL_ICON].icon_file_name[1],"%sCar/control_enable.dds",XR_RES);

	tpIcon[TP_CONTROL_ICON] = new HMIButton(&tpIconData[TP_CONTROL_ICON], m_uiNode);

	tpIconData[TP_PARKING_IN_ICON].pos[0] = tpIconPos[TP_PARKING_IN_ICON][0];
	tpIconData[TP_PARKING_IN_ICON].pos[1] = tpIconPos[TP_PARKING_IN_ICON][1];
	tpIconData[TP_PARKING_IN_ICON].width= tpIconWidth[TP_PARKING_IN_ICON];
	tpIconData[TP_PARKING_IN_ICON].height= tpIconHeight[TP_PARKING_IN_ICON];
	tpIconData[TP_PARKING_IN_ICON].show_flag = 0;
    tpIconData[TP_PARKING_IN_ICON].icon_type = STATIC_ICON;
	tpIconData[TP_PARKING_IN_ICON].delegate_func = OnPressParkingInIcon;
    tpIconData[TP_PARKING_IN_ICON].show_icon_num = 0;
    tpIconData[TP_PARKING_IN_ICON].icon_file_name[0] = new char [50];
	tpIconData[TP_PARKING_IN_ICON].icon_file_name[1] = new char [50];	
	tpIconData[TP_PARKING_IN_ICON].trigger = m_trigger[TP_PARKING_IN_ICON];
	m_tpParkingIconShowNum = 0;
	m_tpParkingIconVisibility= 1;

	sprintf(tpIconData[TP_PARKING_IN_ICON].icon_file_name[0],"%sCar/parking_in_normal.dds",XR_RES); 
    sprintf(tpIconData[TP_PARKING_IN_ICON].icon_file_name[1],"%sCar/parking_in_press.dds",XR_RES);

	tpIcon[TP_PARKING_IN_ICON] = new HMIButton(&tpIconData[TP_PARKING_IN_ICON], m_uiNode);

	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].pos[0] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][0];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].pos[1] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][1];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].width= tpIconWidth[TP_CAPTURE_IMAGE_PROMPT_BOX];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].height= tpIconHeight[TP_CAPTURE_IMAGE_PROMPT_BOX];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].show_flag = 0;
    tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_type = STATIC_ICON;
    tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].show_icon_num = 0;
    tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[0] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[1] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[2] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[3] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[4] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[5] = new char [100];
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[6] = new char [100];	
	tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].trigger = m_trigger[TP_CAPTURE_IMAGE_PROMPT_BOX];
	m_tpCaptureImagePromptBoxShowNum = 0;
	m_tpCaptureImagePromptBoxVisibility = 0;

	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[0],"%sCar/capture_image_prompt_box_capture_img.dds",XR_RES); 
    sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[1],"%sCar/capture_image_prompt_box_restruction.dds",XR_RES);
	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[2],"%sCar/capture_image_prompt_box_succeeded.dds",XR_RES);
	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[3],"%sCar/capture_image_prompt_box_failed.dds",XR_RES);
	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[4],"%sCar/capture_image_prompt_box_searching_path.dds",XR_RES);
	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[5],"%sCar/capture_image_prompt_box_asking_click.dds",XR_RES);
	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX].icon_file_name[6],"%sCar/capture_image_prompt_box_finished.dds",XR_RES);


	tpIcon[TP_CAPTURE_IMAGE_PROMPT_BOX] = new HMIButton(&tpIconData[TP_CAPTURE_IMAGE_PROMPT_BOX], m_uiNode);

	tpIconData[TP_PARKING_IN_PROMPT_BOX].pos[0] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][0];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].pos[1] = tpIconPos[TP_CAPTURE_IMAGE_PROMPT_BOX][1];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].width= tpIconWidth[TP_CAPTURE_IMAGE_PROMPT_BOX];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].height= tpIconHeight[TP_CAPTURE_IMAGE_PROMPT_BOX];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].show_flag = 0;
    tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_type = STATIC_ICON;
    tpIconData[TP_PARKING_IN_PROMPT_BOX].show_icon_num = 0;
    tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[0] = new char [100];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[1] = new char [100];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[2] = new char [100];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[3] = new char [100];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[4] = new char [100];
	tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[5] = new char [100];
	sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[0],"%sCar/parking_in_prompt_box_searching_success.dds",XR_RES); 
    sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[1],"%sCar/parking_in_prompt_box_searching_failed.dds",XR_RES);
	sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[2],"%sCar/parking_in_prompt_box_searching_path.dds",XR_RES);
	sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[3],"%sCar/parking_in_prompt_box_location.dds",XR_RES);
	sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[4],"%sCar/parking_in_prompt_box_location_succeeded.dds",XR_RES);
	sprintf(tpIconData[TP_PARKING_IN_PROMPT_BOX].icon_file_name[5],"%sCar/parking_in_prompt_box_location_failed.dds",XR_RES);	
	tpIconData[TP_PARKING_IN_PROMPT_BOX].trigger = m_trigger[TP_PARKING_IN_PROMPT_BOX];
	tpIcon[TP_PARKING_IN_PROMPT_BOX] = new HMIButton(&tpIconData[TP_PARKING_IN_PROMPT_BOX], m_uiNode);
	m_tpParkingInPromptBoxVisibility = 0;

	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].pos[0] = tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][0];
	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].pos[1] = tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][1];
	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].width= tpIconWidth[TP_CAPTURE_IMAGE_PROCESS_BAR_BK];
	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].height= tpIconHeight[TP_CAPTURE_IMAGE_PROCESS_BAR_BK];
	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].show_flag = 0;
    tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].icon_type = STATIC_ICON;
    tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].show_icon_num = 0;
    tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].icon_file_name[0] = new char [50];
	tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].trigger = m_trigger[TP_CAPTURE_IMAGE_PROCESS_BAR_BK];

	sprintf(tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK].icon_file_name[0],"%sCar/scroll_bk.dds",XR_RES); 
	tpIcon[TP_CAPTURE_IMAGE_PROCESS_BAR_BK] = new HMIButton(&tpIconData[TP_CAPTURE_IMAGE_PROCESS_BAR_BK], m_uiNode);


	HmiScrollDataT hmiScrollData;
	hmiScrollData.pos[0] = tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][0];
	hmiScrollData.pos[1] = tpIconPos[TP_CAPTURE_IMAGE_PROCESS_BAR_BK][1];
	hmiScrollData.height = tpIconHeight[TP_CAPTURE_IMAGE_PROCESS_BAR_BK];
	hmiScrollData.width = tpIconWidth[TP_CAPTURE_IMAGE_PROCESS_BAR_BK];
	hmiScrollData.showFlag = 0;
	hmiScrollData.scrollType = SCROLL_HORIZONTAL;
	hmiScrollData.scrollImageName[0] = new char[50];
	sprintf(hmiScrollData.scrollImageName[0],"%sCar/scroll_bar.dds",XR_RES);//
	hmiScrollData.scrollImageNum = 0;

	m_hmiScroll = NULL;
	m_hmiScroll = new HMIScroll(&hmiScrollData);
	//hmiScroll->SetVisibility(0);
	m_hmiScroll->Update(1.0);

	m_polygonBoxData.renderRegion = REGION_FULL_SCREEN;
	m_polygonBoxData.renderNode = NULL;
	m_polygonBoxData.polygonVertexNum = REF_POINTS;
	m_polygonBoxData.fillTextureName[0] = new char[50];
	sprintf(m_polygonBoxData.fillTextureName[0],"%sCar/tp_path.dds",XR_RES);	
	m_polygonBoxData.fillTextureIndex = 0;
	m_polygonBoxData.materialType = Material_Rigid_Blend;

	m_polygonBox = new HMIPolygonBox(&m_polygonBoxData);

/*	float pVertex[8];

	//0 - 1
	pVertex[0] = 0.0;
	pVertex[1] = 400.0;

	//1 - 0
	pVertex[2] = 340.0;
	pVertex[3] = 400.0;

	//2 - 2
	pVertex[4] = 480.0;
	pVertex[5] = 500.0;

	//3 - 7
	pVertex[6] = 640.0;
	pVertex[7] = 600.0;

	m_polygonBox->SetVisibility(1);

	m_polygonBox->Update(pVertex, 0);
*/

	Log_Error("--------Finish Tp Hmi init---------");

	return HMI_SUCCESS;
}

int CSVTrainedParkingHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return true;
}

int CSVTrainedParkingHmi::Update(Hmi_Message_T& hmiMsg)
{
	if(tpIcon[TP_CAPTURE_IMAGE_ICON]
		&& tpIcon[TP_NAVIGATING_ICON]
		&& tpIcon[TP_CONTROL_ICON]
		&& tpIcon[TP_PARKING_IN_ICON]
		&& m_hmiScroll)
	{
	    ProcessIconTouchEvent();

		UpdateTpElem(&hmiMsg);

	    RefreshHmiIcon();

    	return HMI_SUCCESS;
	}
	else
	{
		return HMI_ELEMENT_NULL;
	}
}

int CSVTrainedParkingHmi::UpdateTpElem(Hmi_Message_T* hmiMsg)
{
	Tp_Result tpReslt;
	CAvmRenderDataBase::GetInstance()->GetTpResult(&tpReslt);
	
    if(hmiMsg->algoResult.tpStatus == 1
		&& hmiMsg->algoResult.tpResult != NULL
	  )
	{		
		m_tpCaptureImageProcessBarVisibility = 0;

		if(m_tpCaptureImageIconShowNum == 1)
	    {
		    if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag == TRAINED_PARKING_NOMAL)
		    {
		        m_tpCaptureImagePromptBoxVisibility = 0;
		    }
			else if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag == TRAINED_PARKING_CAPTURE_IMG)
			{
				m_tpCaptureImagePromptBoxVisibility = 1;
				m_tpCaptureImagePromptBoxShowNum= PROMPT_BOX_CAPTURE_IMAGE;
			}
			else if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag >= TRAINED_PARKING_ENTER_RESTRUCTION 
				&& hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag < TRAINED_PARKING_RESTRUCTION_PART4)
		    {
				m_tpCaptureImagePromptBoxVisibility = 1;
				m_tpCaptureImagePromptBoxShowNum= PROMPT_BOX_RESTRUCTION;
				m_tpCaptureImageProcessBarVisibility = 1;
				
				m_tpCaptureImageProcessBarRate = ((float)(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag - TRAINED_PARKING_ENTER_RESTRUCTION))/4.0;
		    }
			else if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag == TRAINED_PARKING_RESTRUCTION_PART4)
			{
				m_tpCaptureImagePromptBoxVisibility = 1;
				m_tpCaptureImageProcessBarVisibility = 1;
				m_tpCaptureImagePromptBoxShowNum= PROMPT_BOX_SUCCESS;
				m_tpCaptureImageProcessBarRate = ((float)(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag - TRAINED_PARKING_ENTER_RESTRUCTION))/4.0;
			}
			else if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonA_flag == -1)
		    {
				m_tpCaptureImagePromptBoxVisibility = 1;
				m_tpCaptureImagePromptBoxShowNum= PROMPT_BOX_FAILED;
		    }
		}
		else if(m_tpCaptureImageIconShowNum == 0)
		{
			m_tpCaptureImagePromptBoxVisibility= 0;
			m_tpCaptureImageProcessBarVisibility = 0;
		}

		if(m_tpNavigatingIconShowNum == 1)
		{
			m_tpCaptureImagePromptBoxVisibility = 1;
			if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonD_flag == TRAINED_PARKING_FINISH_SEARCHING_PATH)
			{				
				m_tpCaptureImagePromptBoxShowNum = PROMPT_BOX_ASKING_CLICK;				
			}
			else
			{				
				m_tpCaptureImagePromptBoxShowNum = PROMPT_BOX_SEARCHING_PATH;
			}
		}
				
		static float tpPathPoint[REF_POINTS*2];

		if(m_tpControlIconShowNum == 1)
		{
			m_tpCaptureImagePromptBoxVisibility = 0;
			hmiMsg->algoResult.tpResult->tp_button.tp_buttonD_flag = TRAINED_PARKING_FINISH_SEARCHING_PATH;
			if(hmiMsg->algoResult.tpResult->tp_button.tp_buttonD_flag == TRAINED_PARKING_FINISH_SEARCHING_PATH)
			{
				m_tpMapImageVisibility = 1;

				float loc_x = hmiMsg->algoResult.tpResult->slam_x;
				float loc_y = hmiMsg->algoResult.tpResult->slam_y;
				
				sprintf(m_text[0].text_content[0]," %0.2f, %0.2f",loc_x, loc_y);
				
				m_rotateAlpha = hmiMsg->algoResult.tpResult->slam_heading;
				m_rotateShowFlag = 1;
				AdapteTpPointCoord(loc_x, loc_y); 
				
				tpIconPos[TP_DRIVING_CAR][0] = m_carIconPos[0] + loc_x;
				tpIconPos[TP_DRIVING_CAR][1] = m_carIconPos[1] + loc_y;

				m_text[0].pos[0] = tpIconPos[TP_DRIVING_CAR][0] + 35;
				m_text[0].pos[1] = tpIconPos[TP_DRIVING_CAR][1] + 20;

				if(((-1.0 * RadianToAngle(m_rotateAlpha)) < 2.0
					&& (-1.0 * RadianToAngle(m_rotateAlpha)) > -2.0))
				{
					//m_rotateShowFlag = 0;
				}

				for(int i = 0; i < REF_POINTS; i++)
				{
					loc_x = hmiMsg->algoResult.tpResult->tp_ref_points[i].x;
					loc_y = hmiMsg->algoResult.tpResult->tp_ref_points[i].y;
					AdapteTpPointCoord(loc_x, loc_y); 
					tpPathPoint[2*i] = m_carIconPos[0] + 0.5 * tpIconWidth[TP_DRIVING_CAR] + loc_x;
					tpPathPoint[2*i + 1] = m_carIconPos[1] + 42.0  + loc_y;
				}
				m_polygonBox->Update(tpPathPoint, 0);
			}
			else
			{
				m_tpMapImageVisibility = 0;
			}
			
		}
		else
		{
			m_tpMapImageVisibility = 0;
		}

		m_tpParkingInPromptBoxVisibility = 1;
		static int m_tpParkingInPromptBoxVisibilityCnt = 0;
		switch(hmiMsg->algoResult.tpResult->tp_button.tp_buttonR_flag)
		{
		case TP_BUTTONRFLAG_ERROR:
			m_tpParkingInPromptBoxVisibility = 0;
			m_tpParkingInPromptBoxVisibilityCnt = 0;

		break;
		case TP_BUTTONRFLAG_SEARCHING_PATH_INIT:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_SEARCHING_PROCESSING;
			
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		case TP_BUTTONRFLAG_SEARCHING_PATH_SUCESS:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_SEARCHING_SUCCESS;
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		case TP_BUTTONRFLAG_SEARCHING_PATH_FAILED:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_SEARCHING_FAILED;
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		case TP_BUTTONRFLAG_LOC_INIT:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_START_LOCATION;
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		case TP_BUTTONRFLAG_LOC_INIT_SUCESS:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_LOCATION_SUCCESS;
			if(m_tpParkingInPromptBoxVisibilityCnt > 20)
			{
				m_tpParkingInPromptBoxVisibility = 0;
				m_tpMapImageVisibility = 1;

				float loc_x = hmiMsg->algoResult.tpResult->slam_x;
				float loc_y = hmiMsg->algoResult.tpResult->slam_y;
				
				sprintf(m_text[0].text_content[0]," %0.2f, %0.2f",loc_x, loc_y);
				
				m_rotateAlpha = hmiMsg->algoResult.tpResult->slam_heading;
				m_rotateShowFlag = 1;
				AdapteTpPointCoord(loc_x, loc_y); 
				
				tpIconPos[TP_DRIVING_CAR][0] = m_carIconPos[0] + loc_x;
				tpIconPos[TP_DRIVING_CAR][1] = m_carIconPos[1] + loc_y;

				m_text[0].pos[0] = tpIconPos[TP_DRIVING_CAR][0] + 35;
				m_text[0].pos[1] = tpIconPos[TP_DRIVING_CAR][1] + 20;

				if(((-1.0 * RadianToAngle(m_rotateAlpha)) < 2.0
					&& (-1.0 * RadianToAngle(m_rotateAlpha)) > -2.0))
				{
					//m_rotateShowFlag = 0;
				}
				for(int i = 0; i < REF_POINTS; i++)
				{
					loc_x = hmiMsg->algoResult.tpResult->tp_ref_points[i].x;
					loc_y = hmiMsg->algoResult.tpResult->tp_ref_points[i].y;
					AdapteTpPointCoord(loc_x, loc_y); 
					tpPathPoint[2*i] = m_carIconPos[0] + 0.5 * tpIconWidth[TP_DRIVING_CAR] + loc_x;
					tpPathPoint[2*i + 1] = m_carIconPos[1] + 42.0  + loc_y;
				}
				m_polygonBox->Update(tpPathPoint, 0);
			}
			else
			{
				m_tpParkingInPromptBoxVisibilityCnt++;
			}
		
		break;
		case TP_BUTTONRFLAG_LOC_INIT_FAILED:
			m_tpParkingInPromptBoxShowNum = PROMPT_BOX_LOCATION_FAILED;
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		default:
			m_tpParkingInPromptBoxVisibility = 0;
			m_tpParkingInPromptBoxVisibilityCnt = 0;
		break;
		}

		
		m_tpDrivingCarVisibility = m_tpMapImageVisibility;		
		m_text[0].show_flag = m_tpDrivingCarVisibility;

		
	}
	else
	{
		m_tpMapImageVisibility = 0;
		m_tpDrivingCarVisibility = 0;
		m_tpParkingInPromptBoxVisibility = 0;
		m_tpCaptureImagePromptBoxVisibility= 0;
		m_tpCaptureImageProcessBarVisibility = 0;
	}
    return HMI_SUCCESS;
}

int CSVTrainedParkingHmi::ProcessIconTouchEvent()
{
    int x = 0;
	int y = 0;
	int touchType = 0;

	if(GetTouchEventInfo(x,y,touchType))
	{  
		tpIcon[TP_CAPTURE_IMAGE_ICON]->onClickListener(x,y,touchType);
		if(m_tpCaptureImagePromptBoxVisibility == 0
			|| m_tpCaptureImagePromptBoxShowNum == PROMPT_BOX_SUCCESS
			|| m_tpCaptureImagePromptBoxShowNum == PROMPT_BOX_ASKING_CLICK)
		{
	        tpIcon[TP_NAVIGATING_ICON]->onClickListener(x,y,touchType);
        	tpIcon[TP_CONTROL_ICON]->onClickListener(x,y,touchType);
       	 	tpIcon[TP_PARKING_IN_ICON]->onClickListener(x,y,touchType);
		}
		else
		{
			if(m_tpParkingInPromptBoxVisibility == 0
				||m_tpParkingInPromptBoxShowNum == PROMPT_BOX_SEARCHING_FAILED
				|| m_tpParkingInPromptBoxShowNum == PROMPT_BOX_LOCATION_FAILED)
			{		
				tpIcon[TP_PARKING_IN_ICON]->onClickListener(x,y,touchType);
			}
		}
	}
	
	return HMI_SUCCESS;
}

int CSVTrainedParkingHmi::RefreshHmiIcon()
{
    tpIcon[TP_CAPTURE_IMAGE_ICON]->SetShowIconNum(m_tpCaptureImageIconShowNum);
    tpIcon[TP_CAPTURE_IMAGE_ICON]->SetVisibility(m_tpCaptureImageIconVisibility);

	tpIcon[TP_NAVIGATING_ICON]->SetShowIconNum(m_tpNavigatingIconShowNum);
    tpIcon[TP_NAVIGATING_ICON]->SetVisibility(m_tpNavigatingIconVisibility);

	tpIcon[TP_CONTROL_ICON]->SetShowIconNum(m_tpControlIconShowNum);
    tpIcon[TP_CONTROL_ICON]->SetVisibility(m_tpControlIconVisibility);

    tpIcon[TP_PARKING_IN_ICON]->SetVisibility(m_tpParkingIconVisibility);

	static int parkingInPressCnt = 0;
	if(m_tpParkingIconShowNum == PARKING_IN_ICON_PRESS)
	{
		if(parkingInPressCnt > 5)
		{
			tpIcon[TP_PARKING_IN_ICON]->SetShowIconNum(PARKING_IN_ICON_NORMAL);
		}
		else
		{
			tpIcon[TP_PARKING_IN_ICON]->SetShowIconNum(PARKING_IN_ICON_PRESS);
			parkingInPressCnt ++;
		}
	}
	else
	{	
		tpIcon[TP_PARKING_IN_ICON]->SetShowIconNum(PARKING_IN_ICON_NORMAL);
		parkingInPressCnt = 0;
	}

	tpIcon[TP_CAPTURE_IMAGE_PROMPT_BOX]->SetShowIconNum(m_tpCaptureImagePromptBoxShowNum);
    tpIcon[TP_CAPTURE_IMAGE_PROMPT_BOX]->SetVisibility(m_tpCaptureImagePromptBoxVisibility);

	tpIcon[TP_PARKING_IN_PROMPT_BOX]->SetShowIconNum(m_tpParkingInPromptBoxShowNum);
    tpIcon[TP_PARKING_IN_PROMPT_BOX]->SetVisibility(m_tpParkingInPromptBoxVisibility);
    
	tpIcon[TP_CAPTURE_IMAGE_PROCESS_BAR_BK]->SetShowIconNum(0);
    tpIcon[TP_CAPTURE_IMAGE_PROCESS_BAR_BK]->SetVisibility(m_tpCaptureImageProcessBarVisibility);

	tpIcon[TP_MAP_IMAGE]->SetVisibility(m_tpMapImageVisibility);
	m_polygonBox->SetVisibility(m_tpMapImageVisibility);

	if(m_tpDrivingCarVisibility == 1)
	{
		tpIconData[TP_DRIVING_CAR].pos[0] = tpIconPos[TP_DRIVING_CAR][0];
		tpIconData[TP_DRIVING_CAR].pos[1] = tpIconPos[TP_DRIVING_CAR][1];	
		tpIcon[TP_DRIVING_CAR]->SetRotateZ(-1.0 * RadianToAngle(m_rotateAlpha + 3.14/2.0), m_anchorPointX, m_anchorPointY,m_rotateShowFlag);
		//Log_Error("---------RadianToAngle: %0.5f, m_rotateShowFlag: %d", RadianToAngle(m_rotateAlpha), m_rotateShowFlag);
	}
	tpIcon[TP_DRIVING_CAR]->SetVisibility(m_tpDrivingCarVisibility);

	m_hmiScroll->SetVisibility(m_tpCaptureImageProcessBarVisibility);
	if(m_tpCaptureImageProcessBarVisibility)
	{	
		m_hmiScroll->Update(m_tpCaptureImageProcessBarRate);
	}
	
    for(int i=0;i<TP_ICON_NUMS;i++)
    {
        tpIcon[i]->Update();
    }

	m_pTextBox->Update();
	
	return HMI_SUCCESS;
}
int CSVTrainedParkingHmi::SetElementsVisibility(unsigned char pFlag)
{


	return HMI_SUCCESS;
}

int CSVTrainedParkingHmi::AdapteTpPointCoord(float &pX, float &pY) //Unit: m
{
	//Log_Message("pX_0: %0.5f,pY_0 : %0.5f ",pX,pY);
	
	pX = map_x_offside + map_img_width/map_world_width * pX;
	pY = map_y_offside + map_img_height/map_world_height * pY;
	//Log_Message("pX_1: %0.5f,pY_1 : %0.5f ",pX,pY);
	pX = pX * m_showRegionWidth / map_img_width;
	pY = pY * m_showRegionHeight / map_img_height;
	//Log_Message("pX_2: %0.5f,pY_2 : %0.5f ",pX,pY);
	
	return HMI_SUCCESS;
}
int CSVTrainedParkingHmi::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

void OnPressCaptureImageIcon()
{
	Layout_Event_Payload_T* tmp_payload = NULL;
	tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
	memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
	tmp_payload->header.msg_id = ALGO_TP_CAPTURE_IMAGE_ICON;
    tmp_payload->body.tp_body.capture_image_status = 1;
	tmp_payload->body.tp_body.navigating_status = 0;
	tmp_payload->body.tp_body.control_status = 0;
	//tmp_payload->body.tp_body.parking_status = 0;

	//Log_Error("OnPressCaptureImageIcon");
	CSVTrainedParkingHmi::m_tpCaptureImageIconShowNum = tmp_payload->body.tp_body.capture_image_status;
	CSVTrainedParkingHmi::m_tpNavigatingIconShowNum = tmp_payload->body.tp_body.navigating_status;
	CSVTrainedParkingHmi::m_tpControlIconShowNum = tmp_payload->body.tp_body.control_status;
	//CSVTrainedParkingHmi::m_tpParkingIconShowNum = tmp_payload->body.tp_body.parking_status;
	CSVTrainedParkingHmi::m_tpButtonClickEvent->PostEventPayload(tmp_payload);
	free(tmp_payload);
}

void OnPressNavigatingIcon()
{
    Layout_Event_Payload_T* tmp_payload = NULL;
	tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
	memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
	tmp_payload->header.msg_id = ALGO_TP_NAVIGATING_ICON;
    tmp_payload->body.tp_body.capture_image_status = 0;
	tmp_payload->body.tp_body.navigating_status = 1;
	tmp_payload->body.tp_body.control_status = 0;

	//Log_Error("OnPressNavigatingIcon");
	CSVTrainedParkingHmi::m_tpCaptureImageIconShowNum = tmp_payload->body.tp_body.capture_image_status;
	CSVTrainedParkingHmi::m_tpNavigatingIconShowNum = tmp_payload->body.tp_body.navigating_status;
	CSVTrainedParkingHmi::m_tpControlIconShowNum = tmp_payload->body.tp_body.control_status;
	CSVTrainedParkingHmi::m_tpButtonClickEvent->PostEventPayload(tmp_payload);
	free(tmp_payload);
}

void OnPressControlIcon()
{
    Layout_Event_Payload_T* tmp_payload = NULL;
	tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
	memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
	tmp_payload->header.msg_id = ALGO_TP_CONTROL_ICON;
    tmp_payload->body.tp_body.capture_image_status = 0;
	tmp_payload->body.tp_body.navigating_status = 0;
	tmp_payload->body.tp_body.control_status = 1;

	//Log_Error("OnPressControlIcon");
	CSVTrainedParkingHmi::m_tpCaptureImageIconShowNum = tmp_payload->body.tp_body.capture_image_status;
	CSVTrainedParkingHmi::m_tpNavigatingIconShowNum = tmp_payload->body.tp_body.navigating_status;
	CSVTrainedParkingHmi::m_tpControlIconShowNum = tmp_payload->body.tp_body.control_status;
	CSVTrainedParkingHmi::m_tpButtonClickEvent->PostEventPayload(tmp_payload);
	free(tmp_payload);
}

void OnPressParkingIcon()
{
    Layout_Event_Payload_T* tmp_payload = NULL;
	tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
	memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
	tmp_payload->header.msg_id = ALGO_TP_PARKING_ICON;
	static unsigned char parking_status = 0;
	parking_status = 1 - parking_status;
	tmp_payload->body.tp_body.parking_status = parking_status;

	//Log_Error("OnPressParkingIcon");
	CSVTrainedParkingHmi::m_tpParkingIconShowNum = tmp_payload->body.tp_body.parking_status;
	CSVTrainedParkingHmi::m_tpButtonClickEvent->PostEventPayload(tmp_payload);
	free(tmp_payload);
}
void OnPressParkingInIcon()
{
    Layout_Event_Payload_T* tmp_payload = NULL;
	tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
	memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
	tmp_payload->header.msg_id = ALGO_TP_PARKING_ICON;
	static unsigned char parking_status = 0;
	parking_status = 1 - parking_status;
	tmp_payload->body.tp_body.parking_status = parking_status;

	CSVTrainedParkingHmi::m_tpParkingIconShowNum = tmp_payload->body.tp_body.parking_status;
	CSVTrainedParkingHmi::m_tpButtonClickEvent->PostEventPayload(tmp_payload);
	free(tmp_payload);
}

