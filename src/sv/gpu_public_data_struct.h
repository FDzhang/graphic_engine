#ifndef __GPU_PUBLIC_DATA_H__
#define __GPU_PUBLIC_DATA_H__

enum
{
    front_left_door,
    front_right_door,
    rear_left_door,
    rear_right_door,
    door_max
};


typedef struct Overlay_APA_Y
{
    unsigned char stop_sign_flag;
	unsigned char end_parking_sign_flag;
    unsigned char parking_lot_detect_flag;	
	unsigned char parking_lot_type;
    unsigned char online_detect_flag;
	int drive_dirction_indicat;
	float scroll_rate;
	unsigned char park_lot_flag;
	float pParkLotPos[8];
	int vP_GearR_Text;
}APAOverlayStruct;
typedef struct GPU_MDL_POSE_T
{
    float front_pose[6];
	float rear_pose[6];
	float left_pose[6];
	float right_pose[6];

}GPU_MDL_POSE;
typedef struct CAN_DATA_T
{
    float vehicle_speed;
	float left_wheel_speed;
	float right_wheel_speed;
	float steering_wheel_angle;
	float yaw_rate;
	unsigned char door_state[door_max];
	unsigned char turn_light_status;
	unsigned char gear_state;
	unsigned char radar_alarm[8];

}CAN_DATA;

#define MAX_TEXT_BOX_LINE_NUM  10
//for text box
typedef struct st_text_box_data_Tag
{
    float pos[2];
	float width;
	float font_size;
	int line_num;
	bool show_flag;
	float text_color[3];
	char *text_content[MAX_TEXT_BOX_LINE_NUM];
	int text_box_id;
}st_text_box_data_T;

typedef struct st_static_icon_box_data_Tag
{
    float pos[2];
	float width;
	float height;
	int show_icon_num;	
	bool show_flag;
	char *icon_file_name[MAX_TEXT_BOX_LINE_NUM];
}st_static_icon_box_data_T;

typedef struct st_scroll_box_data_Tag
{
    float pos[2];
	float width;
	float height;
	bool show_flag;
	float scroll_rate;
	bool  horizon;
	char *icon_file_name[2];   // 0 for background icon name, 1 fro scroll icon name
}st_scroll_box_data_T;

#define MAX_ALARM_STATE 3
typedef struct st_LDW_line_data_Tag
{
    float curv;
	float slope;
	float L_offset;
	float R_offset;

	bool show_flag;
    int alarm_state;
	
	char *icon_file_name[MAX_ALARM_STATE];   // 0 for background icon name, 1 fro scroll icon name
}st_LDW_line_data_T;


#define MAX_BSD_RECT 10
#define MAX_BSD_ALARM_STATE 3

enum
{
    single_view_rect_bottom_left,
    single_view_rect_bottom_right,
    single_view_rect_top_right,
    single_view_rect_top_left,
};


typedef struct st_singleview_rect_data_Tag
{
    float point[8]; //  顺序为左下，右下，右上，左上，
    int alarm_state;
	bool show_flag;
	bool rear_single_view_flag;
	char *icon_file_name[MAX_BSD_ALARM_STATE];
}st_singleview_rect_data_T;

#define MAX_MOVING_RECT_NUM 10
typedef struct st_BSD_radar_icon_data_Tag
{
    float pos[2]; 
	float width;
	float height;	
	float target_width;
	float target_height;
    int alarm_state[MAX_MOVING_RECT_NUM];
	bool show_flag;
	int max_target_num;
	float moving_rect_pos[MAX_MOVING_RECT_NUM][2];
	bool  moving_rect_show_flag[MAX_MOVING_RECT_NUM];
	float moving_rect_alpharate[MAX_MOVING_RECT_NUM];
	char *icon_file_name[MAX_BSD_ALARM_STATE+1]; //0 ---for background picture , i+1 for alarm_state i moving rect texture
}st_BSD_radar_icon_data_T;

typedef struct st_ADAS_Mdl_HMI_Tag
{

    st_LDW_line_data_T *pLDWLine;
	int ldw_line_num;
	st_static_icon_box_data_T *pStaticIcon;
	int icon_num;
	st_text_box_data_T* pTextBox;
	int text_box_num;
	st_singleview_rect_data_T* pSingleviewRect;
	int single_view_rect_num;
	st_scroll_box_data_T* pScrollRect;
	int scroll_rect_num;	
	st_BSD_radar_icon_data_T *pBSDRadar;
	int BSD_radar_num;
}st_ADAS_Mdl_HMI_T;

#if 0
typedef struct GPU_Calib_Reslt_T
{
   float cam_ex_param[24];

}GPU_Calib_Reslt;
#endif
#endif //#ifndef __GL_SV_DEMO_H__
