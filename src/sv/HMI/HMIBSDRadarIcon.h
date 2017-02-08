#ifndef __HMI_BSD_RADAR_ICON_H__
#define __HMI_BSD_RADAR_ICON_H__

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"

typedef struct st_BSD_radar_box_data_slot_Tag
{	
	int icon_box_id;
	st_BSD_radar_icon_data_T *p_icon_box_data;
	IMaterial *pIconMtl[MAX_MOVING_RECT_NUM];	
	IUINode*	p_ui_node;
	int back_ground_id;
	int target_back_ground_id[MAX_MOVING_RECT_NUM];
}st_BSD_radar_box_data_slot_T;



class HMIBSDRadarIcon
{
public:
	HMIBSDRadarIcon(Region Global,Region Part,int slot_num = 2);
	void Init(IUINode *pSeneNode);

	int Add(IUINode *pSeneNode,st_BSD_radar_icon_data_T *icon_box_cfg);
	
	int Update(void);


private:


    int m_text_box_slot_num;

	int m_text_box_cur_index;
	IUINode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;

	st_BSD_radar_box_data_slot_T *m_p_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
