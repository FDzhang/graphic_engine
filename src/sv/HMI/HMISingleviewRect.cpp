

#include "HMISingleviewRect.h"

#include <math.h>
#include "../AVMData.h"

#include "gpu_log.h"
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/







/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


HMISingleviewRect::HMISingleviewRect(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMISingleviewRect::Init(ISceneNode *pSeneNode,unsigned char seconode_type)
{
	m_calib_mode = seconode_type;

	m_p_box_slot = new st_singleview_rect_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}
int HMISingleviewRect::Add(ISceneNode *pSeneNode,st_singleview_rect_data_T *singleview_rect_line_cfg,unsigned char seconode_type)
{
   float pos[3] = {0,};   
   IMaterial* tempcarmtl;
   Int32 tempmaterialid;
   XRVertexLayout data_format;
   tempmaterialid = pSeneNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
   tempcarmtl->SetDiffuseMap(singleview_rect_line_cfg->icon_file_name[singleview_rect_line_cfg->alarm_state]);
   
   
   
   int lisenceMeshId = pSeneNode->CreateMesh(ModelType_Plane_Dynamic,2,  RECT_POINT_NUM,0, "singleview_rect", &m_p_box_slot[m_text_box_cur_index].pRectMesh);
   int groundId = pSeneNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &m_p_box_slot[m_text_box_cur_index].pNode);
   
   m_p_box_slot[m_text_box_cur_index].pNode->SetMesh(lisenceMeshId);
   //m_overlay->RotateDX(90);  
   m_p_box_slot[m_text_box_cur_index].pNode->SetEnable(singleview_rect_line_cfg->show_flag);
   
   m_p_box_slot[m_text_box_cur_index].pRectMesh->LockData(&m_p_box_slot[m_text_box_cur_index].pdatabuffer,&data_format,&m_p_box_slot[m_text_box_cur_index].element_num);
     
   m_p_box_slot[m_text_box_cur_index].p_singleview_rect_data = singleview_rect_line_cfg;
   m_p_box_slot[m_text_box_cur_index].icon_box_id = m_text_box_cur_index;
   m_p_box_slot[m_text_box_cur_index].pRectMtl = tempcarmtl;

	m_pSeneNode = pSeneNode;
	
	
	m_text_box_cur_index++;
	return 0;
}
void HMISingleviewRect::CvtPointCoordinate(float *out_model_Coord,float *in_world_coord,bool rear_single_view)
{
     AVMData::GetInstance()->cvtSingleViewImagePoint2GpuPoint(out_model_Coord,in_world_coord,rear_single_view);
}

void HMISingleviewRect::GenerateSingleviewRectPlane(float *point,float*pVertex,bool rear_single_view)
{

	float yLeft;
	float yRight;

	unsigned int slotid=0;;
	int index;
	float image_coord[3]={0,0,0};
	float gpu_model_coord[3];
	float y_base =0;
	
	for(int i =0;i<4;i++)
	{
        if(i == 0)
        {
            index = single_view_rect_bottom_left;
	    }
		else if(i == 1)
		{
			index = single_view_rect_bottom_right;
		}
		else if( i ==2)
		{
			index = single_view_rect_top_left;
		}
		else 
		{
			index = single_view_rect_top_right;
		}	    
		
		image_coord[0] = point[2*index];
		image_coord[1] = point[2*index+1];		
        
        CvtPointCoordinate(gpu_model_coord,image_coord,rear_single_view);
		pVertex[slotid+0]= gpu_model_coord[0];
		pVertex[slotid+1]= gpu_model_coord[1];
		pVertex[slotid+2]= gpu_model_coord[2];

        slotid+=8;

	}
	


}

int HMISingleviewRect::Update(void)
{
    ISpirit *pBackgroundLayer;
    float pOutput[4];
    IMesh *pMeshTemp;
    for(int i =0;i<m_text_box_cur_index;i++)
    {
        if(m_p_box_slot[i].p_singleview_rect_data->show_flag == 0)
        {
            m_p_box_slot[i].pNode->SetEnable(0);

        }
        else
        {
		
            m_p_box_slot[i].pNode->SetEnable(1);
            m_p_box_slot[i].pRectMtl->SetDiffuseMap(m_p_box_slot[i].p_singleview_rect_data->icon_file_name[m_p_box_slot[i].p_singleview_rect_data->alarm_state]);

            GenerateSingleviewRectPlane(m_p_box_slot[i].p_singleview_rect_data->point,m_p_box_slot[i].pdatabuffer,m_p_box_slot[i].p_singleview_rect_data->rear_single_view_flag);
            m_p_box_slot[i].pRectMesh->UnLockData();
        }
    }

	return 0;
}

void HMISingleviewRect::SetEnable(bool flag)
{
    for(int i =0;i<m_text_box_cur_index;i++)
    {
        m_p_box_slot[i].pNode->SetEnable(flag);
    }
}
