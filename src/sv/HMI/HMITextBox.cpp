
#include "HMITextBox.h"

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


HMITextBox::HMITextBox(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMITextBox::Init(IUINode *pSeneNode,char *background_name,char *font_type_Mtl)
{

    m_back_mtl_id= pSeneNode->CreateUIMaterial(Material_UI_Spirit, background_name); 
    m_font_mtl_id = pSeneNode->CreateUIFontMaterial(font_type_Mtl, 0);
	m_ptext_box_slot = new st_text_box_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}

int HMITextBox::Add(IUINode *pSeneNode,st_text_box_data_T *text_box_cfg,int *first_text_index)
{
   ITextLayer *pText;
   
   int logoLayerId = pSeneNode->CreateSpirit( -1, InsertFlag_Default, m_back_mtl_id, 1.0, text_box_cfg->pos[0], text_box_cfg->pos[1], 0,text_box_cfg->width,text_box_cfg->font_size*text_box_cfg->line_num); 
   m_ptext_box_slot[m_text_box_cur_index].p_text_box_data = text_box_cfg;
   m_ptext_box_slot[m_text_box_cur_index].text_box_id = m_text_box_cur_index;
   m_ptext_box_slot[m_text_box_cur_index].text_line_num = text_box_cfg->line_num;

	m_pSeneNode = pSeneNode;

	m_ptext_box_slot[m_text_box_cur_index].back_ground_id= logoLayerId;
    for(int j=0;j<text_box_cfg[0].line_num;j++)
    {
        InitSingleTextBox(&text_box_cfg[0],pSeneNode,&pText,m_font_mtl_id,j);
		
		m_ptext_box_slot[m_text_box_cur_index].pText[j]= pText;
    }
	
	
	m_text_box_cur_index++;
	return 0;
}

int HMITextBox::InitSingleTextBox(st_text_box_data_T *text_box_cfg,IUINode *pSeneNode,ITextLayer ** text,int textMtlId,int text_index)
{
    float pose[2];
	float height;
	//height = text_box_cfg->height/(float)text_box_cfg->line_num;
	CalcCoordinate(text_box_cfg->pos,pose);
	pose[0] = pose[0]+LINE_SPACE_START;
	pose[1]=pose[1]+text_index*text_box_cfg->font_size+LINE_SPACE_HALF;
	
	int textId = pSeneNode ->CreateTextLayer(-1, InsertFlag_Default, textMtlId, 1.0, pose[0], pose[1], text, text_box_cfg->width,text_box_cfg->font_size-2*LINE_SPACE_HALF);
	(*text)->SetText(text_box_cfg->text_content[text_index]);
	(*text)->SetFontSize(text_box_cfg->font_size-2*LINE_SPACE_HALF);
	(*text)->SetColor(text_box_cfg->text_color[0],text_box_cfg->text_color[1],text_box_cfg->text_color[2]);

	return 0;
}

int HMITextBox::CalcCoordinate(float *pInGlobalPose,float *pOutAeraPose)
{
   pOutAeraPose[0]= pInGlobalPose[0];//-m_text_aera_region.left;
   pOutAeraPose[1]= pInGlobalPose[1];//-m_text_aera_region.top;


    return 0;
}
int HMITextBox::Update(void)
{
    ISpirit *pBackgroundLayer;
	for(int i =0;i<m_text_box_cur_index;i++)
	{
	    if(m_ptext_box_slot[i].p_text_box_data->show_flag == 0)
	    {
	       pBackgroundLayer = m_pSeneNode->GetSpirit(m_ptext_box_slot[i].back_ground_id);
		   pBackgroundLayer->SetEnable(0);
		   

		    for(int j=0;j<m_ptext_box_slot[i].text_line_num;j++)
    	    {
    	        m_ptext_box_slot[i].pText[j]->SetEnable(0);
    	    }
	    }
		else
		{
		
    		pBackgroundLayer = m_pSeneNode->GetSpirit(m_ptext_box_slot[i].back_ground_id);
    		pBackgroundLayer->SetEnable(0);
    	    for(int j=0;j<m_ptext_box_slot[i].text_line_num;j++)
    	    {
    	    
			    m_ptext_box_slot[i].pText[j]->SetEnable(1);
				if(m_ptext_box_slot[i].text_line_num == 1)
    	    	{
					m_ptext_box_slot[i].pText[j]->SetX(m_ptext_box_slot[i].p_text_box_data->pos[0]);
					m_ptext_box_slot[i].pText[j]->SetY(m_ptext_box_slot[i].p_text_box_data->pos[1]);
				}
        	    m_ptext_box_slot[i].pText[j]->SetText(m_ptext_box_slot[i].p_text_box_data->text_content[j]);
                m_ptext_box_slot[i].pText[j]->SetColor(m_ptext_box_slot[i].p_text_box_data->text_color[0],m_ptext_box_slot[i].p_text_box_data->text_color[1],m_ptext_box_slot[i].p_text_box_data->text_color[2]);
    	    }
		}
	}
	return 0;
}
