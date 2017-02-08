

#include "HMIIconBox.h"

#include <math.h>



/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/


#define LINE_SPACE_HALF  3
#define LINE_SPACE_START  6




/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


HMIIconBox::HMIIconBox(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMIIconBox::Init(IUINode *pSeneNode)
{

	m_p_box_slot = new st_icon_box_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}

int HMIIconBox::Add(IUINode *pSeneNode,st_static_icon_box_data_T *icon_box_cfg)
{
   int mtl_id;   
   mtl_id= pSeneNode->CreateUIMaterial(Material_UI_Spirit, icon_box_cfg->icon_file_name[icon_box_cfg->show_icon_num],0,&m_p_box_slot[m_text_box_cur_index].pIconMtl); 
   int logoLayerId = pSeneNode->CreateSpirit( -1, InsertFlag_Default, mtl_id, 1.0, icon_box_cfg->pos[0], icon_box_cfg->pos[1], 0,icon_box_cfg->width,icon_box_cfg->height); 
   m_p_box_slot[m_text_box_cur_index].p_icon_box_data = icon_box_cfg;
   m_p_box_slot[m_text_box_cur_index].icon_box_id = m_text_box_cur_index;

	m_pSeneNode = pSeneNode;

	m_p_box_slot[m_text_box_cur_index].back_ground_id= logoLayerId;
	
	m_text_box_cur_index++;
	return 0;
}

int HMIIconBox::Update(void)
{
    ISpirit *pBackgroundLayer;
	for(int i =0;i<m_text_box_cur_index;i++)
	{
	    if(m_p_box_slot[i].p_icon_box_data->show_flag == 0)
	    {
	       pBackgroundLayer = m_pSeneNode->GetSpirit(m_p_box_slot[i].back_ground_id);
		   pBackgroundLayer->SetEnable(0);

	    }
		else
		{
		
    		pBackgroundLayer = m_pSeneNode->GetSpirit(m_p_box_slot[i].back_ground_id);
    		pBackgroundLayer->SetEnable(1);
			m_p_box_slot[i].pIconMtl->SetDiffuseMap(m_p_box_slot[i].p_icon_box_data->icon_file_name[m_p_box_slot[i].p_icon_box_data->show_icon_num]);
		}
	}
	return 0;
}
