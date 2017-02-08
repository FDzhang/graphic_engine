

#include "HMIBSDRadarIcon.h"

#include <math.h>

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;


/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/




/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


HMIBSDRadarIcon::HMIBSDRadarIcon(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMIBSDRadarIcon::Init(IUINode *pSeneNode)
{

	m_p_box_slot = new st_BSD_radar_box_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}

int HMIBSDRadarIcon::Add(IUINode *pSeneNode,st_BSD_radar_icon_data_T *icon_box_cfg)
{
	IRenderTarget* tempRt;
    IUINode *pTempUINode;
    IMaterial *pTmpMtl;
   int mtl_id = rm->CreateRenderTarget(icon_box_cfg->width, icon_box_cfg->height, XR_R8G8B8A8, XR_NONE, &tempRt);   
   
   int m_lisenceNodeId = g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, mtl_id, &pTempUINode);
   pTempUINode->SetClear(true,false);
   //draw_back_ground
   int logoMtlId = pTempUINode->CreateUIMaterial(Material_UI_Spirit, icon_box_cfg->icon_file_name[0]);
   int logoLayerId = pTempUINode->CreateSpirit( -1, InsertFlag_Default, logoMtlId, 1.0, 0, 0, 0,icon_box_cfg->width,icon_box_cfg->height); 
   

   for(int i=0;i<icon_box_cfg->max_target_num;i++)
   {
        
		int moving_target_mtl_id = pTempUINode->CreateUIMaterial(Material_UI_Spirit, icon_box_cfg->icon_file_name[1],0,&m_p_box_slot[m_text_box_cur_index].pIconMtl[i]);
		int logoLayerId = pTempUINode->CreateSpirit( -1, InsertFlag_Default, moving_target_mtl_id, 1.0,icon_box_cfg->moving_rect_pos[i][0], 
			icon_box_cfg->moving_rect_pos[i][1],0,icon_box_cfg->target_width, icon_box_cfg->target_height); 
		m_p_box_slot[m_text_box_cur_index].target_back_ground_id[i]= logoLayerId;

   }
   
	mtl_id = pSeneNode->CreateUIMaterial(Material_UI_Spirit, icon_box_cfg->icon_file_name[1],0,&pTmpMtl);

   logoLayerId = pSeneNode->CreateSpirit( -1, InsertFlag_Default, mtl_id, 1.0, icon_box_cfg->pos[0], icon_box_cfg->pos[1], 0,icon_box_cfg->width,icon_box_cfg->height); 

   	pTmpMtl->SetDiffuseMap(tempRt->GetTextureId());
   
   m_p_box_slot[m_text_box_cur_index].p_icon_box_data = icon_box_cfg;
   m_p_box_slot[m_text_box_cur_index].icon_box_id = m_text_box_cur_index;
   m_p_box_slot[m_text_box_cur_index].p_ui_node = pTempUINode;
      m_p_box_slot[m_text_box_cur_index].back_ground_id = logoLayerId;
   m_pSeneNode = pSeneNode;

	
	m_text_box_cur_index++;
	return 0;
}

int HMIBSDRadarIcon::Update(void)
{
    ISpirit *pBackgroundLayer;
	for(int i =0;i<m_text_box_cur_index;i++)
	{
	    if(m_p_box_slot[i].p_icon_box_data->show_flag == 0)
	    {
	       pBackgroundLayer = m_pSeneNode->GetSpirit(m_p_box_slot[i].back_ground_id);
		   pBackgroundLayer->SetEnable(0);
		   m_p_box_slot[i].p_ui_node->SetEnable(0);

	    }
		else
		{
		
    		pBackgroundLayer = m_pSeneNode->GetSpirit(m_p_box_slot[i].back_ground_id);
    		pBackgroundLayer->SetEnable(1);			
			m_p_box_slot[i].p_ui_node->SetEnable(1);
           for(int j=0;j<m_p_box_slot[i].p_icon_box_data->max_target_num;j++)
           {
			    pBackgroundLayer =  m_p_box_slot[i].p_ui_node->GetSpirit(m_p_box_slot[i].target_back_ground_id[j]);
                if(m_p_box_slot[i].p_icon_box_data->moving_rect_show_flag[j]==1)
                {
                
    				pBackgroundLayer->SetEnable(1);
					
					m_p_box_slot[i].pIconMtl[j]->SetDiffuseMap(m_p_box_slot[i].p_icon_box_data->icon_file_name[m_p_box_slot[i].p_icon_box_data->alarm_state[j]+1]);
					pBackgroundLayer->SetPosition(m_p_box_slot[i].p_icon_box_data->moving_rect_pos[j][0],m_p_box_slot[i].p_icon_box_data->height-m_p_box_slot[i].p_icon_box_data->moving_rect_pos[j][1]);
					pBackgroundLayer->SetOpacity(m_p_box_slot[i].p_icon_box_data->moving_rect_alpharate[j]);
                }
				else
				{
				    pBackgroundLayer->SetEnable(0);
				}
           }			
		}
	}
	return 0;
}
