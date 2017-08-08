#include "HMITest.h"

static int SVNodeTestHMI::alg_status = 0;
static int SVNodeTestHMI::demo_status = 0;

enum Function_Mode_Tag
{
	LDW_MODE,
	BSD_MODE,
	ONLINE_CALIBRATION,
	APA_MODE,
	PLAY_BACK_MODE,
	RECORD_MODE,
	WIFI_MODE,
	LDW_BSD_MODE,
	NONE_MODE
};

SVNodeTestHMI::SVNodeTestHMI()
{
	m_current_chains_status = -100;
	m_last_selected_chains = -100;

}
void SVNodeTestHMI::InitHMI(int window_width, int window_height)
{

	text_camera_frame_title_pos[0] = 456;
	text_camera_frame_title_pos[1] = 300;

	text_camera_frame_title_width = 130;
	text_camera_frame_title_fontsize = 30;

	text_vehicle_data_title_pos[0] = 1150;
	text_vehicle_data_title_pos[1] = 300;
	
	text_vehicle_data_title_width = 130;
	text_vehicle_data_title_fontsize = 30;

	text_cameraframe_items_pos[0] = 456;
	text_cameraframe_items_pos[1] = 380;
	text_cameraframe_items_width = 83;
	text_cameraframe_items_fontsize = 20;

	text_cameraframe_items_value_pos[0] = 456 + 83;
	text_cameraframe_items_value_pos[1] = 380;
	text_cameraframe_items_value_width = 45;
	text_cameraframe_items_value_fontsize = 20;

	text_vehicledata_items_pos[0] = 1150;
	text_vehicledata_items_pos[1] = 380;
	text_vehicledata_items_width = 83;
	text_vehicledata_items_fontsize = 20;

	text_vehicledata_items_value_pos[0] = 1150 + 83;
	text_vehicledata_items_value_pos[1] = 380;
	text_vehicledata_items_value_width = 45;
	text_vehicledata_items_value_fontsize = 20;
	
	status_icon_speed_width = 0.2 * window_width;
	status_icon_speed_height = 0.2 * window_height;	
	status_icon_speed_pos[0] = 0.35 * window_width - 10;
	status_icon_speed_pos[1] = 0.95 * window_height - status_icon_speed_height + 3;

	text_vehicledata_speed_value_pos[0] = status_icon_speed_pos[0] + 0.3 * status_icon_speed_width - 11;//15;
	text_vehicledata_speed_value_pos[1] = window_height - 0.80 * status_icon_speed_height;
	text_vehicledata_speed_value_width = 1;
	text_vehicledata_speed_value_fontsize = 36;

	status_icon_background_width =  0.75 * window_width - status_icon_speed_width;
	status_icon_background_height = 0.57 * status_icon_speed_height;
	status_icon_background_pos[0] = status_icon_speed_pos[0] + status_icon_speed_width - 6;//10;
	status_icon_background_pos[1] = 0.95 * window_height - status_icon_background_height + 3;
	

	display_cameraframe_icon_pos[0] = 0.35 * window_width + 8;
	display_cameraframe_icon_pos[1] = 0.35 * window_height;
	display_cameraframe_icon_width = 0.14 * window_width;
	display_cameraframe_icon_height = 0.1  * window_height;

	display_cameraframe_background_icon_pos[0] = display_cameraframe_icon_pos[0];
	display_cameraframe_background_icon_pos[1] = display_cameraframe_icon_pos[1] + display_cameraframe_icon_height;
	display_cameraframe_background_icon_width = display_cameraframe_icon_width;
	display_cameraframe_background_icon_height = 0.2 * window_height;

	display_vehicledata_icon_width = 0.14 * window_width;
	display_vehicledata_icon_height = 0.07  * window_height +5;
	display_vehicledata_icon_pos[0] = window_width - display_vehicledata_icon_width;
	display_vehicledata_icon_pos[1] = display_cameraframe_icon_pos[1] + 17;


	display_vehicledata_background_icon_pos[0] = display_vehicledata_icon_pos[0];
	display_vehicledata_background_icon_pos[1] = display_vehicledata_icon_pos[1] + display_vehicledata_icon_height;
	display_vehicledata_background_icon_width = display_vehicledata_icon_width;
	display_vehicledata_background_icon_height = 0.2  * window_height;

	int text_width = 1;
	int text_fontsize = 24;

	text_frame_ratio_pos[0] = display_cameraframe_background_icon_pos[0];
	text_frame_ratio_pos[1] = display_cameraframe_background_icon_pos[1] + 17;
	text_frame_ratio_width = text_width;
	text_frame_ratio_fontsize = text_fontsize;

	text_frame_latency_pos[0] = text_frame_ratio_pos[0];
	text_frame_latency_pos[1] = text_frame_ratio_pos[1] + 37;
	text_frame_latency_width = text_width;
	text_frame_latency_fontsize = text_fontsize;
	
	text_alg_time_pos[0] = text_frame_latency_pos[0];
	text_alg_time_pos[1] = text_frame_latency_pos[1] + 37;
	text_alg_time_width = text_width;
	text_alg_time_fontsize = text_fontsize;

	text_steering_angle_pos[0] = display_vehicledata_background_icon_pos[0] + 18;
	text_steering_angle_pos[1] = display_vehicledata_background_icon_pos[1] + 15;
	text_steering_angle_width = text_width;
	text_steering_angle_fontsize = text_fontsize;

	text_vd_avg_time_pos[0] = text_steering_angle_pos[0] + 24;
	text_vd_avg_time_pos[1] = text_steering_angle_pos[1] + 37;
	text_vd_avg_time_width = text_width;
	text_vd_avg_time_fontsize = text_fontsize;

	text_yaw_rate_pos[0] = text_steering_angle_pos[0] + 24;
	text_yaw_rate_pos[1] = text_vd_avg_time_pos[1] + 37;
	text_yaw_rate_width = text_width;
	text_yaw_rate_fontsize = text_fontsize;
	
	int icon_width = status_icon_background_width / 9;
	status_icon_ldw_pos[0] = status_icon_speed_pos[0] + status_icon_speed_width + 8;
	status_icon_ldw_pos[1] = status_icon_background_pos[1] + 15;
	status_icon_ldw_width = icon_width;
	status_icon_ldw_height = icon_width;

	status_icon_bsd_pos[0] = status_icon_ldw_pos[0] + icon_width;
	status_icon_bsd_pos[1] = status_icon_ldw_pos[1];
	status_icon_bsd_width = icon_width;
	status_icon_bsd_height = icon_width;

	status_icon_online_pos[0] = status_icon_bsd_pos[0] + icon_width;
	status_icon_online_pos[1] = status_icon_ldw_pos[1];
	status_icon_online_width = icon_width;
	status_icon_online_height = icon_width;

	status_icon_park_pos[0] = status_icon_online_pos[0] + icon_width;
	status_icon_park_pos[1] = status_icon_ldw_pos[1];
	status_icon_park_width = icon_width; 
	status_icon_park_height = icon_width;

	status_icon_playback_pos[0] = status_icon_park_pos[0] + icon_width;
	status_icon_playback_pos[1] = status_icon_ldw_pos[1];
	status_icon_playback_width = icon_width;
	status_icon_playback_height = icon_width;

	status_icon_record_pos[0] = status_icon_playback_pos[0] + icon_width;
	status_icon_record_pos[1] = status_icon_ldw_pos[1];
	status_icon_record_width = icon_width;
	status_icon_record_height = icon_width;

	status_icon_wifi_pos[0] = status_icon_record_pos[0] + icon_width;
	status_icon_wifi_pos[1] = status_icon_ldw_pos[1];
	status_icon_wifi_width = icon_width ;
	status_icon_wifi_height = icon_width ;
	
	bsd_radar_pos[0] = 0.35 * window_width + 18;
	bsd_radar_pos[1] = 50;
	bsd_radar_width = 170;
	bsd_radar_height = 250;
	bsd_radar_target_width = 15;
	bsd_radar_target_height = 15;

	scroll_1_pos[0] = 0.35 * window_width + 21 + 0.5 * status_icon_speed_width ;
	scroll_1_pos[1] = window_height - (status_icon_speed_pos[1] + 0.7 * status_icon_speed_height) + 28;
	scroll_1_width = status_icon_speed_width * 0.4-20;
	scroll_1_height = 30;
	
	scroll_2_pos[0] = scroll_1_pos[0];
	scroll_2_pos[1] = scroll_1_pos[1] - 24;
	scroll_2_width = scroll_1_width;
	scroll_2_height = scroll_1_height;
	
	scroll_3_pos[0] = scroll_2_pos[0];
	scroll_3_pos[1] = scroll_2_pos[1] - 24;
	scroll_3_width = scroll_1_width;
	scroll_3_height = scroll_1_height;

	int cf_scroll_width = 0.75 * display_cameraframe_background_icon_width;
	int cf_scroll_height = 0.09 * display_cameraframe_background_icon_height;//20;
	scroll_frame_ratio_pos[0] = display_cameraframe_icon_pos[0];
	scroll_frame_ratio_pos[1] = window_height - (text_frame_ratio_pos[1] + text_frame_ratio_fontsize * 2.0) + 25;
	scroll_frame_ratio_width = cf_scroll_width;
	scroll_frame_ratio_height = cf_scroll_height;

	scroll_frame_latency_pos[0] = text_frame_ratio_pos[0];
	scroll_frame_latency_pos[1] = scroll_frame_ratio_pos[1] - 35;
	scroll_frame_latency_width = cf_scroll_width;
    scroll_frame_latency_height = cf_scroll_height;
	
	scroll_alg_time_pos[0] = text_frame_ratio_pos[0];
	scroll_alg_time_pos[1] = scroll_frame_latency_pos[1] - 35;
	scroll_alg_time_width = cf_scroll_width;
	scroll_alg_time_height = cf_scroll_height;

	scroll_steering_ang_pos[0] = text_steering_angle_pos[0] + 12;
	scroll_steering_ang_pos[1] = window_height - (text_steering_angle_pos[1] + text_steering_angle_fontsize * 2.0) + 25;
	scroll_steering_ang_width = cf_scroll_width;
	scroll_steering_ang_height = cf_scroll_height;
		
	scroll_vd_avg_time_pos[0] = text_steering_angle_pos[0] + 12;
	scroll_vd_avg_time_pos[1] = scroll_steering_ang_pos[1] - 35;
	scroll_vd_avg_time_width = cf_scroll_width;
	scroll_vd_avg_time_height = cf_scroll_height;
		
	scroll_yaw_rate_pos[0] = text_steering_angle_pos[0] + 12;
	scroll_yaw_rate_pos[1] = scroll_vd_avg_time_pos[1] - 35;
	scroll_yaw_rate_width = cf_scroll_width;
	scroll_yaw_rate_height = cf_scroll_height;

}

void SVNodeTestHMI::SetHMIText()
{
	int title_items_interval = 90;
	char title1[100] = "   Camera";
	char title2[100] = "    Frame";

	char frame_ratio[100] = "FR : 0.00";
	char frame_ratio_value[100] = "25.00";
	char frame_latency[100] = "LAT : 0.00 , 0.00";
	char frame_latency_value[100] = "0.00";
	char alg_time[100]   = "ALG : 0.00 , 0.00";
	char alg_time_value[100] = "0.00";

	char title3[100] = "   Vehicle";
	char title4[100] = "    Data";

	char speed[100] = "Speed : ";
	char speed_value[100] = "432 / 0";
	char yaw_rate[100] = "Yaw-Rate : -1.60  ";
	char yaw_rate_value[100] = "-1.60";
	char steering_ang[100] = "Steering-Ang : -1.06  ";
	char steering_ang_value[100] = "0.70";
	char avg_time_vehicle_data[100] = "Avg-Time : 3.00  ";
	char avg_time_value_vehicle_data[100] = "3.00";

	char speed_current_value[100] = "00";

	m_text[0].pos[0] = text_frame_ratio_pos[0];
	m_text[0].pos[1] = text_frame_ratio_pos[1];
	m_text[0].line_num = 1;
	m_text[0].width = text_frame_ratio_width;
	m_text[0].font_size = text_frame_ratio_fontsize;
	m_text[0].text_color[0] = 1.0;
	m_text[0].text_color[1] = 1.0;
	m_text[0].text_color[2] = 1.0;
	m_text[0].show_flag = 1;
	m_text[0].text_content[0] = new char[50];
	sprintf(m_text[0].text_content[0],"%s",frame_ratio);

	m_text[1].pos[0] = text_frame_latency_pos[0];
	m_text[1].pos[1] = text_frame_latency_pos[1];
	m_text[1].line_num = 1;
	m_text[1].width = text_frame_latency_width;
	m_text[1].font_size = text_frame_latency_fontsize;
	m_text[1].text_color[0] = 1.0;
	m_text[1].text_color[1] = 1.0;
	m_text[1].text_color[2] = 1.0;
	m_text[1].show_flag = 1;
	m_text[1].text_content[0] = new char[50];
	sprintf(m_text[1].text_content[0],"%s",frame_latency);

	m_text[2].pos[0] = text_alg_time_pos[0];
	m_text[2].pos[1] = text_alg_time_pos[1];
	m_text[2].line_num = 1;
	m_text[2].width = text_alg_time_width;
	m_text[2].font_size = text_alg_time_fontsize;
	m_text[2].text_color[0] = 1.0;
	m_text[2].text_color[1] = 1.0;
	m_text[2].text_color[2] = 1.0;
	m_text[2].show_flag = 1;
	m_text[2].text_content[0] = new char[50];
	sprintf(m_text[2].text_content[0],"%s",alg_time);

	m_text[4].pos[0] = text_vehicledata_speed_value_pos[0];
	m_text[4].pos[1] = text_vehicledata_speed_value_pos[1];
	m_text[4].line_num = 1;
	m_text[4].width = text_vehicledata_speed_value_width;
	m_text[4].font_size = text_vehicledata_speed_value_fontsize;
	m_text[4].text_color[0] = 1.0;
	m_text[4].text_color[1] = 1.0;
	m_text[4].text_color[2] = 1.0;
	m_text[4].show_flag = 1;
	m_text[4].text_content[0] = new char[50];
	sprintf(m_text[4].text_content[0],"%s",speed_current_value);

	m_text[5].pos[0] = text_steering_angle_pos[0];
	m_text[5].pos[1] = text_steering_angle_pos[1];
	m_text[5].line_num = 1;
	m_text[5].width = text_steering_angle_width;
	m_text[5].font_size = text_steering_angle_fontsize;
	m_text[5].text_color[0] = 1.0;
	m_text[5].text_color[1] = 1.0;
	m_text[5].text_color[2] = 1.0;
	m_text[5].show_flag = 1;
	m_text[5].text_content[0] = new char[50];
	sprintf(m_text[5].text_content[0],"%s",steering_ang);

	m_text[6].pos[0] = text_vd_avg_time_pos[0];
	m_text[6].pos[1] = text_vd_avg_time_pos[1];
	m_text[6].line_num = 1;
	m_text[6].width = text_vd_avg_time_width;
	m_text[6].font_size = text_vd_avg_time_fontsize;
	m_text[6].text_color[0] = 1.0;
	m_text[6].text_color[1] = 1.0;
	m_text[6].text_color[2] = 1.0;
	m_text[6].show_flag = 1;
	m_text[6].text_content[0] = new char[50];
	sprintf(m_text[6].text_content[0],"%s",avg_time_vehicle_data);
		
	m_text[7].pos[0] = text_yaw_rate_pos[0];
	m_text[7].pos[1] = text_yaw_rate_pos[1];
	m_text[7].line_num = 1;
	m_text[7].width = text_yaw_rate_width;
	m_text[7].font_size = text_yaw_rate_fontsize;
	m_text[7].text_color[0] = 1.0;
	m_text[7].text_color[1] = 1.0;
	m_text[7].text_color[2] = 1.0;
	m_text[7].show_flag = 1;
	m_text[7].text_content[0] = new char[50];
	sprintf(m_text[7].text_content[0],"%s",yaw_rate);


/*	int title_items_interval = 90;
	char title1[100] = "   Camera";
	char title2[100] = "    Frame";

	char frame_num[100] = "Frame-Num : ";
	char frame_num_value[100] = "432 / 0";
	char frame_drop[100] = "Frame-Drop : ";
	char frame_drop_value[100] = "-1.80";
	char total_time[100] = "Total-Time : ";
	char total_time_value[100] = "0.70";
	char avg_time[100]   = "Avg-Time : ";
	char avg_time_value[100] = "3.00";

	char title3[100] = "   Vehicle";
	char title4[100] = "    Data";

	char speed[100] = "Speed : ";
	char speed_value[100] = "432 / 0";
	char yaw_rate[100] = "Yaw-Rate : ";
	char yaw_rate_value[100] = "-1.60";
	char steering_ang[100] = "Steering-Ang : ";
	char steering_ang_value[100] = "0.70";
	char avg_time_vehicle_data[100] = "Avg-Time : ";
	char avg_time_value_vehicle_data[100] = "3.00";

	char speed_current_value[100] = "60";

	m_text[0].pos[0] = text_camera_frame_title_pos[0];
	m_text[0].pos[1] = text_camera_frame_title_pos[1];
	m_text[0].line_num = 2;
	m_text[0].width = text_camera_frame_title_width;
	m_text[0].font_size = text_camera_frame_title_fontsize;
	m_text[0].text_color[0] = 1.0;
	m_text[0].text_color[1] = 1.0;
	m_text[0].text_color[2] = 1.0;
	m_text[0].show_flag = 1;
	m_text[0].text_content[0] = new char[50];
	m_text[0].text_content[1] = new char[50];
	sprintf(m_text[0].text_content[0],"%s",title1);
	sprintf(m_text[0].text_content[1],"%s",title2);

	m_text[1].pos[0] = text_cameraframe_items_pos[0];
	m_text[1].pos[1] = text_cameraframe_items_pos[1];
	m_text[1].line_num = 4;
	m_text[1].width = text_cameraframe_items_width;
	m_text[1].font_size = text_cameraframe_items_fontsize;
	m_text[1].text_color[0] = 1.0;
	m_text[1].text_color[1] = 1.0;
	m_text[1].text_color[2] = 1.0;
	m_text[1].show_flag = 1;
	m_text[1].text_content[0] = new char[50];
	m_text[1].text_content[1] = new char[50];
	m_text[1].text_content[2] = new char[50];
	m_text[1].text_content[3] = new char[50];
	sprintf(m_text[1].text_content[0],"%s",frame_num);
	sprintf(m_text[1].text_content[1],"%s",frame_drop);
	sprintf(m_text[1].text_content[2],"%s",total_time);
	sprintf(m_text[1].text_content[3],"%s",avg_time);

	m_text[2].pos[0] = text_cameraframe_items_value_pos[0];
	m_text[2].pos[1] = text_cameraframe_items_value_pos[1];
	m_text[2].line_num = 4;
	m_text[2].width = text_cameraframe_items_value_width;
	m_text[2].font_size = text_cameraframe_items_value_fontsize;
	m_text[2].text_color[0] = 0.38;
	m_text[2].text_color[1] = 0.71;
	m_text[2].text_color[2] = 0.69;
	m_text[2].show_flag = 1;
	m_text[2].text_content[0] = new char[50];
	m_text[2].text_content[1] = new char[50];
	m_text[2].text_content[2] = new char[50];
	m_text[2].text_content[3] = new char[50];
	sprintf(m_text[2].text_content[0],"%s",frame_num_value);
	sprintf(m_text[2].text_content[1],"%s",frame_drop_value);
	sprintf(m_text[2].text_content[2],"%s",total_time_value);
	sprintf(m_text[2].text_content[3],"%s",avg_time_value);

	m_text[3].pos[0] = text_vehicle_data_title_pos[0];
	m_text[3].pos[1] = text_vehicle_data_title_pos[1];
	m_text[3].line_num = 2;
	m_text[3].width = text_vehicle_data_title_width;
	m_text[3].font_size = text_vehicle_data_title_fontsize;
	m_text[3].text_color[0] = 1.0;
	m_text[3].text_color[1] = 1.0;
	m_text[3].text_color[2] = 1.0;
	m_text[3].show_flag = 1;
	m_text[3].text_content[0] = new char[50];
	m_text[3].text_content[1] = new char[50];
	sprintf(m_text[3].text_content[0],"%s",title3);
	sprintf(m_text[3].text_content[1],"%s",title4);

	m_text[4].pos[0] = text_vehicledata_items_pos[0];
	m_text[4].pos[1] = text_vehicledata_items_pos[1];
	m_text[4].line_num = 4;
	m_text[4].width = text_vehicledata_items_width;
	m_text[4].font_size = text_vehicledata_items_fontsize;
	m_text[4].text_color[0] = 1.0;
	m_text[4].text_color[1] = 1.0;
	m_text[4].text_color[2] = 1.0;
	m_text[4].show_flag = 1;
	m_text[4].text_content[0] = new char[50];
	m_text[4].text_content[1] = new char[50];
	m_text[4].text_content[2] = new char[50];
	m_text[4].text_content[3] = new char[50];
	sprintf(m_text[4].text_content[0],"%s",speed);
	sprintf(m_text[4].text_content[1],"%s",yaw_rate);
	sprintf(m_text[4].text_content[2],"%s",steering_ang);
	sprintf(m_text[4].text_content[3],"%s",avg_time_vehicle_data);

	m_text[5].pos[0] = text_vehicledata_items_value_pos[0];
	m_text[5].pos[1] = text_vehicledata_items_value_pos[1];
	m_text[5].line_num = 4;
	m_text[5].width = text_vehicledata_items_value_width;
	m_text[5].font_size = text_vehicledata_items_value_fontsize;
	m_text[5].text_color[0] = 0.38;
	m_text[5].text_color[1] = 0.71;
	m_text[5].text_color[2] = 0.69;
	m_text[5].show_flag = 1;
	m_text[5].text_content[0] = new char[50];
	m_text[5].text_content[1] = new char[50];
	m_text[5].text_content[2] = new char[50];
	m_text[5].text_content[3] = new char[50];
	sprintf(m_text[5].text_content[0],"%s",speed_value);
	sprintf(m_text[5].text_content[1],"%s",yaw_rate_value);
	sprintf(m_text[5].text_content[2],"%s",steering_ang_value);
	sprintf(m_text[5].text_content[3],"%s",avg_time_value_vehicle_data);

	m_text[6].pos[0] = text_vehicledata_speed_value_pos[0];
	m_text[6].pos[1] = text_vehicledata_speed_value_pos[1];
	m_text[6].line_num = 2;
	m_text[6].width = text_vehicledata_speed_value_width;
	m_text[6].font_size = text_vehicledata_speed_value_fontsize;
	m_text[6].text_color[0] = 1.0;
	m_text[6].text_color[1] = 1.0;
	m_text[6].text_color[2] = 1.0;
	m_text[6].show_flag = 1;
	m_text[6].text_content[0] = new char[50];
	m_text[6].text_content[1] = new char[50];
	sprintf(m_text[6].text_content[0],"%s",speed_current_value);
	*/
}
void SVNodeTestHMI::SetHMIIcon()
{
	int icon_interval = 100;
	m_icon[0].pos[0] = status_icon_speed_pos[0];
	m_icon[0].pos[1] = status_icon_speed_pos[1];
	m_icon[0].width = status_icon_speed_width;
	m_icon[0].height = status_icon_speed_height;
	m_icon[0].show_flag = 1;
	m_icon[0].show_icon_num = 0;
	m_icon[0].icon_file_name[0] = new char [50];

	sprintf(m_icon[0].icon_file_name[0],"%stest_speed.dds",XR_RES);

	m_icon[1].pos[0] = status_icon_background_pos[0];
	m_icon[1].pos[1] = status_icon_background_pos[1];
	m_icon[1].width = status_icon_background_width;
	m_icon[1].height = status_icon_background_height;
	m_icon[1].show_flag = 1;
	m_icon[1].show_icon_num = 0;
	m_icon[1].icon_file_name[0] = new char [50];

	sprintf(m_icon[1].icon_file_name[0],"%sstatus_background.dds",XR_RES);

	m_icon[2].pos[0] = status_icon_ldw_pos[0];
	m_icon[2].pos[1] = status_icon_ldw_pos[1];
	m_icon[2].width = status_icon_ldw_width;
	m_icon[2].height = status_icon_ldw_height;
	m_icon[2].show_flag = 1;
	m_icon[2].show_icon_num = 0;
	m_icon[2].icon_file_name[0] = new char [50];
	m_icon[2].icon_file_name[1] = new char [50];
	sprintf(m_icon[2].icon_file_name[0],"%sldw_unable.dds",XR_RES);
	sprintf(m_icon[2].icon_file_name[1],"%sldw_enable.dds",XR_RES);

	m_icon[3].pos[0] = status_icon_bsd_pos[0];
	m_icon[3].pos[1] = status_icon_bsd_pos[1];
	m_icon[3].width = status_icon_bsd_width;
	m_icon[3].height = status_icon_bsd_height;
	m_icon[3].show_flag = 1;
	m_icon[3].show_icon_num = 0;
	m_icon[3].icon_file_name[0] = new char [50];
	m_icon[3].icon_file_name[1] = new char [50];
	sprintf(m_icon[3].icon_file_name[0],"%sbsd_unable.dds",XR_RES);
	sprintf(m_icon[3].icon_file_name[1],"%sbsd_enable.dds",XR_RES);

	m_icon[4].pos[0] = status_icon_online_pos[0];
	m_icon[4].pos[1] = status_icon_online_pos[1];
	m_icon[4].width = status_icon_online_width;
	m_icon[4].height = status_icon_online_height;
	m_icon[4].show_flag = 1;
	m_icon[4].show_icon_num = 0;
	m_icon[4].icon_file_name[0] = new char [50];
	m_icon[4].icon_file_name[1] = new char [50];
	sprintf(m_icon[4].icon_file_name[0],"%sonline_unable.dds",XR_RES);
	sprintf(m_icon[4].icon_file_name[1],"%sonline_enable.dds",XR_RES);

	m_icon[5].pos[0] = status_icon_park_pos[0];
	m_icon[5].pos[1] = status_icon_park_pos[1];
	m_icon[5].width = status_icon_park_width;
	m_icon[5].height = status_icon_park_height;
	m_icon[5].show_flag = 1;
	m_icon[5].show_icon_num = 0;
	m_icon[5].icon_file_name[0] = new char [50];
	m_icon[5].icon_file_name[1] = new char [50];
	sprintf(m_icon[5].icon_file_name[0],"%spark_unable.dds",XR_RES);
	sprintf(m_icon[5].icon_file_name[1],"%spark_enable.dds",XR_RES);
	
	m_icon[6].pos[0] = status_icon_playback_pos[0];
	m_icon[6].pos[1] = status_icon_playback_pos[1];
	m_icon[6].width = status_icon_playback_width;
	m_icon[6].height = status_icon_playback_height;
	m_icon[6].show_flag = 1;
	m_icon[6].show_icon_num = 0;
	m_icon[6].icon_file_name[0] = new char [50];
	m_icon[6].icon_file_name[1] = new char [50];
	m_icon[6].icon_file_name[2] = new char [50];
	sprintf(m_icon[6].icon_file_name[0],"%splayback_unable.dds",XR_RES);
	sprintf(m_icon[6].icon_file_name[1],"%splayback_enable.dds",XR_RES);
	sprintf(m_icon[6].icon_file_name[2],"%splayback_next.dds",XR_RES);

	m_icon[7].pos[0] = status_icon_record_pos[0];
	m_icon[7].pos[1] = status_icon_record_pos[1];
	m_icon[7].width = status_icon_record_width;
	m_icon[7].height = status_icon_record_height;
	m_icon[7].show_flag = 1;
	m_icon[7].show_icon_num = 0;
	m_icon[7].icon_file_name[0] = new char [50];
	m_icon[7].icon_file_name[1] = new char [50];
	m_icon[7].icon_file_name[2] = new char [50];
	sprintf(m_icon[7].icon_file_name[0],"%srecord_unable.dds",XR_RES);
	sprintf(m_icon[7].icon_file_name[1],"%srecord_enable.dds",XR_RES);
	sprintf(m_icon[7].icon_file_name[2],"%srecord_next.dds",XR_RES);

	m_icon[8].pos[0] = status_icon_wifi_pos[0];
	m_icon[8].pos[1] = status_icon_wifi_pos[1];
	m_icon[8].width = status_icon_wifi_width;
	m_icon[8].height = status_icon_wifi_height;
	m_icon[8].show_flag = 1;
	m_icon[8].show_icon_num = 0;
	m_icon[8].icon_file_name[0] = new char [50];
	m_icon[8].icon_file_name[1] = new char [50];
	m_icon[8].icon_file_name[2] = new char [50];
	sprintf(m_icon[8].icon_file_name[0],"%swifi_unable.dds",XR_RES);
	sprintf(m_icon[8].icon_file_name[1],"%swifi_enable.dds",XR_RES);
	sprintf(m_icon[8].icon_file_name[2],"%swifi_next.dds",XR_RES);

	m_icon[9].pos[0] = display_cameraframe_icon_pos[0];
	m_icon[9].pos[1] = display_cameraframe_icon_pos[1];
	m_icon[9].width = display_cameraframe_icon_width;
	m_icon[9].height = display_cameraframe_icon_height;
	m_icon[9].show_flag = 1;
	m_icon[9].show_icon_num = 0;
	m_icon[9].icon_file_name[0] = new char [50];
	m_icon[9].icon_file_name[1] = new char [50];
	sprintf(m_icon[9].icon_file_name[0],"%scamera_frame.dds",XR_RES);
	
	m_icon[10].pos[0] = display_cameraframe_background_icon_pos[0];
	m_icon[10].pos[1] = display_cameraframe_background_icon_pos[1];
	m_icon[10].width = display_cameraframe_background_icon_width;
	m_icon[10].height = display_cameraframe_background_icon_height;
	m_icon[10].show_flag = 1;
	m_icon[10].show_icon_num = 0;
	m_icon[10].icon_file_name[0] = new char [50];
	m_icon[10].icon_file_name[1] = new char [50];
	sprintf(m_icon[10].icon_file_name[0],"%scamera_frame_bk.dds",XR_RES);

	m_icon[11].pos[0] = display_vehicledata_icon_pos[0];
	m_icon[11].pos[1] = display_vehicledata_icon_pos[1];
	m_icon[11].width = display_vehicledata_icon_width;
	m_icon[11].height = display_vehicledata_icon_height;
	m_icon[11].show_flag = 1;
	m_icon[11].show_icon_num = 0;
	m_icon[11].icon_file_name[0] = new char [50];
	m_icon[11].icon_file_name[1] = new char [50];
	sprintf(m_icon[11].icon_file_name[0],"%svehicle_data_title.dds",XR_RES);
	
	m_icon[12].pos[0] = display_vehicledata_background_icon_pos[0];
	m_icon[12].pos[1] = display_vehicledata_background_icon_pos[1];
	m_icon[12].width = display_vehicledata_background_icon_width;
	m_icon[12].height = display_vehicledata_background_icon_height;
	m_icon[12].show_flag = 1;
	m_icon[12].show_icon_num = 0;
	m_icon[12].icon_file_name[0] = new char [50];
	m_icon[12].icon_file_name[1] = new char [50];
	sprintf(m_icon[12].icon_file_name[0],"%svehicle_data_bk.dds",XR_RES);

}
void SVNodeTestHMI::SetBSDRadarIcon()
{
	m_BSDRadarData[0].pos[0] = bsd_radar_pos[0];
	m_BSDRadarData[0].pos[1] = bsd_radar_pos[1];
	m_BSDRadarData[0].width = bsd_radar_width;
	m_BSDRadarData[0].height = bsd_radar_height;
	m_BSDRadarData[0].target_width = bsd_radar_target_width;
    m_BSDRadarData[0].target_height = bsd_radar_target_height;
	m_BSDRadarData[0].show_flag = 1;
	m_BSDRadarData[0].max_target_num = 2;
	m_BSDRadarData[0].moving_rect_pos[0][0] = 100;
	m_BSDRadarData[0].moving_rect_pos[0][1] = 50;
	m_BSDRadarData[0].moving_rect_show_flag[0]= 1;
	m_BSDRadarData[0].alarm_state[0] = 1;
	m_BSDRadarData[0].moving_rect_alpharate[0] =1.0;
	m_BSDRadarData[0].icon_file_name[0] = new char [50];
	m_BSDRadarData[0].icon_file_name[1] = new char [50];
	m_BSDRadarData[0].icon_file_name[2] = new char [50];
	sprintf(m_BSDRadarData[0].icon_file_name[0],"%sradarfile.dds",XR_RES);
	sprintf(m_BSDRadarData[0].icon_file_name[1],"%sgreenPoint.dds",XR_RES);
	sprintf(m_BSDRadarData[0].icon_file_name[2],"%sredPoint.dds",XR_RES);
}
void SVNodeTestHMI::SetHMILDWLine()
{
	m_LDWData[0].curv = 0.00001457;
	m_LDWData[0].slope = 0.000684619823; 
	 
	m_LDWData[0].L_offset=  1.62134848;
	m_LDWData[0].R_offset=  1.74134848;

	m_LDWData[0].alarm_state = 1;
	m_LDWData[0].show_flag = 1;	 
	 
	m_LDWData[0].icon_file_name[0]=new char [50]; 
	m_LDWData[0].icon_file_name[1]=new char [50];

	sprintf(m_LDWData[0].icon_file_name[0],"%sscroll_bk.dds",XR_RES);
	sprintf(m_LDWData[0].icon_file_name[1],"%sldw_line.dds",XR_RES);

	m_LDWData[1].curv = 0.00001457;
	m_LDWData[1].slope = 0.000684619823; 
	 
	m_LDWData[1].L_offset=  -1.62134848;
	m_LDWData[1].R_offset=  -1.74134848;

	m_LDWData[1].alarm_state = 1;
	m_LDWData[1].show_flag = 1;	 
	 
	m_LDWData[1].icon_file_name[0]=new char [50]; 
	m_LDWData[1].icon_file_name[1]=new char [50];

	sprintf(m_LDWData[1].icon_file_name[0],"%sscroll_bk.dds",XR_RES);
	sprintf(m_LDWData[1].icon_file_name[1],"%sldw_line.dds",XR_RES);

}
void SVNodeTestHMI::SetHMIBSDRegion()
{
	 m_BSDRectData[0].point[0] = 50;
	 m_BSDRectData[0].point[1] = 100;
	 m_BSDRectData[0].point[2] = 350;
	 m_BSDRectData[0].point[3] = 120;
	 m_BSDRectData[0].point[4] = 320;
	 m_BSDRectData[0].point[5] = 100;
	 m_BSDRectData[0].point[6] = 50;
	 m_BSDRectData[0].point[7] = 90;

	 m_BSDRectData[0].icon_file_name[0] = new char[50];
	 m_BSDRectData[0].icon_file_name[1] = new char[50];
	 sprintf(m_BSDRectData[0].icon_file_name[0],"%sgreen.dds",XR_RES);
	 sprintf(m_BSDRectData[0].icon_file_name[1],"%sred.dds",XR_RES);
	 m_BSDRectData[0].alarm_state = 0;
	 m_BSDRectData[0].show_flag = 1;
	 m_BSDRectData[0].rear_single_view_flag = 1;
}
void SVNodeTestHMI::SetHMIScroll()
{
	 m_scroll[0].pos[0] = scroll_1_pos[0];
	 m_scroll[0].pos[1] = scroll_1_pos[1];
	 m_scroll[0].width = scroll_1_width;
	 m_scroll[0].height = scroll_1_height;
	 m_scroll[0].horizon = 1;
	 m_scroll[0].show_flag = 0;
	 m_scroll[0].scroll_rate = 1.0;
	 m_scroll[0].icon_file_name[0]=new char [50]; 
	 m_scroll[0].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[0].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[0].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[1].pos[0] = scroll_2_pos[0];
	 m_scroll[1].pos[1] = scroll_2_pos[1];
	 m_scroll[1].width = scroll_2_width;
	 m_scroll[1].height = scroll_2_height;
	 m_scroll[1].horizon = 1;
	 m_scroll[1].show_flag = 0;
	 m_scroll[1].scroll_rate = 1.0;
	 m_scroll[1].icon_file_name[0]=new char [50]; 
	 m_scroll[1].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[1].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[1].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[2].pos[0] = scroll_3_pos[0];
	 m_scroll[2].pos[1] = scroll_3_pos[1];
	 m_scroll[2].width = scroll_3_width;
	 m_scroll[2].height = scroll_3_height;
	 m_scroll[2].horizon = 1;
	 m_scroll[2].show_flag = 0;
	 m_scroll[2].scroll_rate = 1.0;
	 m_scroll[2].icon_file_name[0]=new char [50]; 
	 m_scroll[2].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[2].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[2].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[3].pos[0] = scroll_frame_ratio_pos[0];
	 m_scroll[3].pos[1] = scroll_frame_ratio_pos[1];
	 m_scroll[3].width = scroll_frame_ratio_width;
	 m_scroll[3].height = scroll_frame_ratio_height;
	 m_scroll[3].horizon = 1;
	 m_scroll[3].show_flag = 0;
	 m_scroll[3].scroll_rate = 1.0;
	 m_scroll[3].icon_file_name[0]=new char [50]; 
	 m_scroll[3].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[3].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[3].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[4].pos[0] = scroll_frame_latency_pos[0];
	 m_scroll[4].pos[1] = scroll_frame_latency_pos[1];
	 m_scroll[4].width = scroll_frame_latency_width;
	 m_scroll[4].height = scroll_frame_latency_height;
	 m_scroll[4].horizon = 1;
	 m_scroll[4].show_flag = 0;
	 m_scroll[4].scroll_rate = 1.0;
	 m_scroll[4].icon_file_name[0]=new char [50]; 
	 m_scroll[4].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[4].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[4].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[5].pos[0] = scroll_alg_time_pos[0];
	 m_scroll[5].pos[1] = scroll_alg_time_pos[1];
	 m_scroll[5].width = scroll_alg_time_width;
	 m_scroll[5].height = scroll_alg_time_height;
	 m_scroll[5].horizon = 1;
	 m_scroll[5].show_flag = 0;
	 m_scroll[5].scroll_rate = 1.0;
	 m_scroll[5].icon_file_name[0]=new char [50]; 
	 m_scroll[5].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[5].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[5].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 m_scroll[7].pos[0] = scroll_steering_ang_pos[0];
	 m_scroll[7].pos[1] = scroll_steering_ang_pos[1];
	 m_scroll[7].width = scroll_steering_ang_width;
	 m_scroll[7].height = scroll_steering_ang_height;
	 m_scroll[7].horizon = 1;
	 m_scroll[7].show_flag = 0;
	 m_scroll[7].scroll_rate = 1.0;
	 m_scroll[7].icon_file_name[0]=new char [50]; 
	 m_scroll[7].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[7].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[7].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 	
	 m_scroll[8].pos[0] = scroll_yaw_rate_pos[0];
	 m_scroll[8].pos[1] = scroll_yaw_rate_pos[1];
	 m_scroll[8].width = scroll_yaw_rate_width;
	 m_scroll[8].height = scroll_yaw_rate_height;
	 m_scroll[8].horizon = 1;
	 m_scroll[8].show_flag = 0;
	 m_scroll[8].scroll_rate = 1.0;
	 m_scroll[8].icon_file_name[0]=new char [50]; 
	 m_scroll[8].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[8].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[8].icon_file_name[1],"%sscroll_process.dds",XR_RES);

	 	 
	 m_scroll[9].pos[0] = scroll_vd_avg_time_pos[0];
	 m_scroll[9].pos[1] = scroll_vd_avg_time_pos[1];
	 m_scroll[9].width = scroll_vd_avg_time_width;
	 m_scroll[9].height = scroll_vd_avg_time_height;
	 m_scroll[9].horizon = 1;
	 m_scroll[9].show_flag = 0;
	 m_scroll[9].scroll_rate = 1.0;
	 m_scroll[9].icon_file_name[0]=new char [50]; 
	 m_scroll[9].icon_file_name[1]=new char [50];
	 sprintf(m_scroll[9].icon_file_name[0],"%sscroll_background.dds",XR_RES);
	 sprintf(m_scroll[9].icon_file_name[1],"%sscroll_process.dds",XR_RES);

}

void SVNodeTestHMI::SetHMIParams()
{
	SetHMIText();
	SetHMIIcon();
	SetHMILDWLine();
	SetBSDRadarIcon();
	SetHMIBSDRegion();
	SetHMIScroll();
//2,1,1
	m_test_hmi.icon_num = 0;
	m_test_hmi.pStaticIcon = m_icon;
	m_test_hmi.ldw_line_num = 0;
	m_test_hmi.pLDWLine = m_LDWData;
	m_test_hmi.single_view_rect_num = 0;
	m_test_hmi.pSingleviewRect = m_BSDRectData;
	m_test_hmi.text_box_num = 0;
	m_test_hmi.pTextBox = m_text;
	m_test_hmi.scroll_rect_num = 0;
	m_test_hmi.pScrollRect = m_scroll;
	m_test_hmi.BSD_radar_num = 0;
	m_test_hmi.pBSDRadar = m_BSDRadarData;
}

void SVNodeTestHMI::HmiDisappear()
{
    for (int i=0;i<17;i++)
    {
        m_icon[i].show_flag = 0;
    }
    
    for (int i=0;i<11;i++)
    {
        m_scroll[i].show_flag = 0;
    }
    
    for (int i=0;i<8;i++)
    {
        m_text[i].show_flag = 0;
    }
}

void SVNodeTestHMI::HmiReappear()
{
    for (int i=0;i<17;i++)
    {
        m_icon[i].show_flag = 1;
    }
    
    for (int i=0;i<11;i++)
    {
        m_scroll[i].show_flag = 1;
    }
    
    for (int i=0;i<8;i++)
    {
        m_text[i].show_flag = 1;
    }
}

void SVNodeTestHMI::setIconStatus()
{	
	static uint32_t last_status = 0;
	
	if (demo_status == 0) // only algo
	{
		if (last_status == 4)
		{
			HmiReappear();
			last_status = demo_status;
		}
		
		m_icon[6].show_icon_num = 0;
		m_icon[7].show_icon_num = 0;
		m_icon[8].show_icon_num = 0;
	}
	else if (demo_status == 1) //playback 
	{
		if (last_status == 4)
		{
			HmiReappear();
			last_status = demo_status;
		}
        
		m_icon[6].show_icon_num = 1;
		m_icon[7].show_icon_num = 0;
		m_icon[8].show_icon_num = 0;
	}
	else if (demo_status == 2) //record 
	{
		if (last_status == 4)
		{
			HmiReappear();
			last_status = demo_status;
		}
		
		m_icon[6].show_icon_num = 0;
		m_icon[7].show_icon_num = 1;
		m_icon[8].show_icon_num = 0;
	}
	else if (demo_status == 3) //mobile 
	{
		if (last_status == 4)
		{
			HmiReappear();
			last_status = demo_status;
		}
		
		m_icon[6].show_icon_num = 0;
		m_icon[7].show_icon_num = 0;
		m_icon[8].show_icon_num = 1;
	}
	else if (demo_status == 4) //playback 
	{
		if (last_status != demo_status)
		{
			HmiDisappear();
			last_status = demo_status;
		}
	}

	switch(alg_status)
	{
		case 0: //none
			m_icon[2].show_icon_num = 0; //ldw
			m_icon[3].show_icon_num = 0; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 0; //apa
			break;
		case 1: //ldw
			m_icon[2].show_icon_num = 1; //ldw
			m_icon[3].show_icon_num = 0; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 0; //apa
			break;
		case 2: //bsd
			m_icon[2].show_icon_num = 0; //ldw
			m_icon[3].show_icon_num = 1; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 0; //apa
			break;
		case 3: //ldw+bsd
			m_icon[2].show_icon_num = 1; //ldw
			m_icon[3].show_icon_num = 1; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 0; //apa
			break;
		case 4: //oc
			m_icon[2].show_icon_num = 0; //ldw
			m_icon[3].show_icon_num = 0; //bsd
			m_icon[4].show_icon_num = 1; //oc
			m_icon[5].show_icon_num = 0; //apa
			break;
		case 5: //apa
			m_icon[2].show_icon_num = 0; //ldw
			m_icon[3].show_icon_num = 0; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 1; //apa
			break;
		default:
			m_icon[2].show_icon_num = 0; //ldw
			m_icon[3].show_icon_num = 0; //bsd
			m_icon[4].show_icon_num = 0; //oc
			m_icon[5].show_icon_num = 0; //apa
			
	}
}
void SVNodeTestHMI::SelectNextChainsStatus(int chains_mode)
{
	switch(chains_mode)
	{
	case PLAY_BACK_MODE:
		m_icon[6].show_icon_num = 2;
		break;
	case PLAY_BACK_MODE + 10:
		m_icon[6].show_icon_num = 0;
		break;
	case RECORD_MODE:
		m_icon[7].show_icon_num = 2;
		break;
	case RECORD_MODE + 10:
		m_icon[7].show_icon_num = 0;
		break;
	case WIFI_MODE:
		m_icon[8].show_icon_num = 2;
		break;
	case WIFI_MODE + 10:
		m_icon[8].show_icon_num = 0;
		break;
	default:
		//m_icon[6].show_icon_num = 0;
		//m_icon[7].show_icon_num = 0;
		//m_icon[8].show_icon_num = 0;
		break;
	}

}

st_ADAS_Mdl_HMI_T* SVNodeTestHMI::GetHMI()
{
	return &m_test_hmi;
}


void SVNodeTestHMI::UpdateHMIData(float steer_angle, float vehicle_speed, float yaw_rage)
{	
	sprintf(m_text[5].text_content[0],"Steering-Ang : %.2f  ",steer_angle);	
	sprintf(m_text[7].text_content[0],"Yaw-Rate : %.2f  ",yaw_rage);
	if(vehicle_speed < 10)
	{
		sprintf(m_text[4].text_content[0],"0%d",(int)vehicle_speed);
	}
	else 
	{
		sprintf(m_text[4].text_content[0],"%d",(int)vehicle_speed);
	}
}

void SVNodeTestHMI::UpdateHMIChainStatus(int chain_status)
{
	m_current_chains_status = chain_status;
}

void SVNodeTestHMI::UpdateHMIChainProcessingStatus(float fps, float avg_latency, float max_latency, float alg_average_cost, float alg_max_cost)
{
	sprintf(m_text[0].text_content[0],"FR : %.2f", fps);	
	sprintf(m_text[1].text_content[0],"LAT : %.2f , %.2f",avg_latency, max_latency);
	sprintf(m_text[2].text_content[0],"ALG : %.2f , %.2f",alg_average_cost, alg_max_cost);
}

void SVNodeTestHMI::UpdateHMINextChainsStatus(int next_chain_status)
{
	static bool flash_flag = true;
	static int flash_count = 0;
	flash_count ++;

	if(next_chain_status != m_last_selected_chains)
	{
		//flash_flag = false;
		
		if(m_last_selected_chains != m_current_chains_status)
		{
			SelectNextChainsStatus(m_last_selected_chains + 10);
		}

		m_last_selected_chains = next_chain_status;
	}

	if(flash_count % 5 == 0)
	{
		if(flash_flag)
		{	
			flash_flag = false;
			SelectNextChainsStatus(next_chain_status);
		}
		else
		{
			flash_flag = true;
			SelectNextChainsStatus(next_chain_status + 10);
		}
	}	

	if(flash_count > 1001)
	{	
		flash_count = 1;
	}


}

