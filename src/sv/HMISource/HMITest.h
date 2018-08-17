#ifndef _HMI_TEST_H_
#define _HMI_TEST_H_

#include "sv/DataStruct.h"
#include "XrCore/XrSrc/External/XrHeaders.h"

#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"

#include "sv/HMI/HMITextBox.h"
#include "sv/HMI/HMIIconBox.h"
#include "sv/HMI/HMIScrollBox.h"
#include "sv/HMI/HMILDWLine.h"
#include "sv/HMI/HMISingleviewRect.h"
#include "sv/HMI/HMIBSDRadarIcon.h"

class SVNodeTestHMI
{
public:
	SVNodeTestHMI();
	
	void InitHMI(int window_width, int window_height);
	void SetHMIParams();
	st_ADAS_Mdl_HMI_T* SVNodeTestHMI::GetHMI();
	void UpdateHMIData(float steer_angle, float vehicle_speed, float yaw_rage);

	void UpdateHMIChainStatus(int chain_status);

	void UpdateHMINextChainsStatus(int next_chain_status);
	void setIconStatus();	
	void UpdateHMIChainProcessingStatus(float fps, float avg_latency, float max_latency, float alg_average_cost, float alg_max_cost);
	
public:
	static int alg_status;
	static int demo_status;
	
private:
	void SetHMIText();
	void SetHMIIcon();
	void SetHMILDWLine();
	void SetHMIBSDRegion();
	void SetBSDRadarIcon();
	void SetHMIScroll();
	void SelectNextChainsStatus(int chains_mode);
	void HmiReappear();
	void HmiDisappear();

private:
	st_ADAS_Mdl_HMI_T m_test_hmi;
	st_text_box_data_T m_text[8];
	st_static_icon_box_data_T m_icon[17]; // 0:²âËÙÌõ£¬1£º×´Ì¬°´Å¥±³¾°£¬2-14£º×´Ì¬°´Å¥£¬15-16£ºCF-±³¾°
	st_scroll_box_data_T m_scroll[11];
	st_LDW_line_data_T m_LDWData[4];
	st_singleview_rect_data_T m_BSDRectData[8];
	st_BSD_radar_icon_data_T m_BSDRadarData[1];

	int m_current_chains_status;
	int m_last_selected_chains;
	
	int text_frame_ratio_pos[2];
	int text_frame_ratio_width;
	int text_frame_ratio_fontsize;

	int text_frame_latency_pos[2];
	int text_frame_latency_width;
	int text_frame_latency_fontsize;

	int text_alg_time_pos[2];
	int text_alg_time_width;
	int text_alg_time_fontsize;

	int text_steering_angle_pos[2];
	int text_steering_angle_width;
	int text_steering_angle_fontsize;

	int text_vd_avg_time_pos[2];
	int text_vd_avg_time_width;
	int text_vd_avg_time_fontsize;

	int text_yaw_rate_pos[2];
	int text_yaw_rate_width;
	int text_yaw_rate_fontsize;

	int text_camera_frame_title_pos[2];
	int text_camera_frame_title_width;
	int text_camera_frame_title_fontsize;

	int text_vehicle_data_title_pos[2];
	int text_vehicle_data_title_width;
	int text_vehicle_data_title_fontsize;

	int text_cameraframe_items_pos[2];
	int text_cameraframe_items_width;
	int text_cameraframe_items_fontsize;

	int text_cameraframe_items_value_pos[2];
	int text_cameraframe_items_value_width;
	int text_cameraframe_items_value_fontsize;

	int text_vehicledata_items_pos[2];
	int text_vehicledata_items_width;
	int text_vehicledata_items_fontsize;

	int text_vehicledata_items_value_pos[2];
	int text_vehicledata_items_value_width;
	int text_vehicledata_items_value_fontsize;

	int text_vehicledata_speed_value_pos[2];
	int text_vehicledata_speed_value_width;
	int text_vehicledata_speed_value_fontsize;

	int display_cameraframe_icon_pos[2];
	int display_cameraframe_icon_width;
	int display_cameraframe_icon_height;

	int display_cameraframe_background_icon_pos[2];
	int display_cameraframe_background_icon_width;
	int display_cameraframe_background_icon_height;

	int display_vehicledata_icon_pos[2];
	int display_vehicledata_icon_width;
	int display_vehicledata_icon_height;

	int display_vehicledata_background_icon_pos[2];
	int display_vehicledata_background_icon_width;
	int display_vehicledata_background_icon_height;

	int status_icon_speed_pos[2];
	int status_icon_speed_width;
	int status_icon_speed_height;

	int status_icon_background_pos[2];
	int status_icon_background_width;
	int status_icon_background_height;

	int status_icon_ldw_pos[2];
	int status_icon_ldw_width;
	int status_icon_ldw_height;

	int status_icon_bsd_pos[2];
	int status_icon_bsd_width;
	int status_icon_bsd_height;

	int status_icon_online_pos[2];
	int status_icon_online_width;
	int status_icon_online_height;

	int status_icon_park_pos[2];
	int status_icon_park_width;
	int status_icon_park_height;

	int status_icon_playback_pos[2];
	int status_icon_playback_width;
	int status_icon_playback_height;

	int status_icon_record_pos[2];
	int status_icon_record_width;
	int status_icon_record_height;

	int status_icon_wifi_pos[2];
	int status_icon_wifi_width;
	int status_icon_wifi_height;

	int bsd_radar_pos[2];
	int bsd_radar_width;
	int bsd_radar_height;
	int bsd_radar_target_width;
	int bsd_radar_target_height;

	int scroll_1_pos[2];
	int scroll_1_width;
	int scroll_1_height;
	
	int scroll_2_pos[2];
	int scroll_2_width;
	int scroll_2_height;
	
	int scroll_3_pos[2];
	int scroll_3_width;
	int scroll_3_height;

	int scroll_frame_ratio_pos[2];
	int scroll_frame_ratio_width;
	int scroll_frame_ratio_height;

	int scroll_frame_latency_pos[2];
	int scroll_frame_latency_width;
	int scroll_frame_latency_height;

	int scroll_alg_time_pos[2];
	int scroll_alg_time_width;
	int scroll_alg_time_height;

	int scroll_steering_ang_pos[2];
	int scroll_steering_ang_width;
	int scroll_steering_ang_height;

	int scroll_yaw_rate_pos[2];
	int scroll_yaw_rate_width;
	int scroll_yaw_rate_height;

	int scroll_vd_avg_time_pos[2];
	int scroll_vd_avg_time_width;
	int scroll_vd_avg_time_height;
};


#endif
