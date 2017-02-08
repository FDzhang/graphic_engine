#ifndef __HMI_ICON_BOX_H__
#define __HMI_ICON_BOX_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/DataStruct.h"

typedef struct st_icon_box_data_slot_Tag
{
	int icon_box_id;
	st_static_icon_box_data_T *p_icon_box_data;
	IMaterial *pIconMtl;
	int back_ground_id;
}st_icon_box_data_slot_T;



class HMIIconBox
{
public:
	HMIIconBox(Region Global,Region Part,int slot_num = 30);
	void Init(IUINode *pSeneNode);

	int Add(IUINode *pSeneNode,st_static_icon_box_data_T *icon_box_cfg);

	int Update(void);


private:


    int m_text_box_slot_num;

	int m_text_box_cur_index;
	IUINode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;

	st_icon_box_data_slot_T *m_p_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
