

#include "HMILDWLine.h"

#include <math.h>
#include "../AVMData.h"


/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/







/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


HMILDWLine::HMILDWLine(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMILDWLine::Init(ISceneNode *pSeneNode,unsigned char seconode_type,float view_world_bottom,float view_world_top )
{
	m_calib_mode = seconode_type;
    m_view_world_bottom = view_world_bottom;
	m_view_wolrd_top = view_world_top;
	m_p_box_slot = new st_ldw_line_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}
int HMILDWLine::Add(ISceneNode *pSeneNode,st_LDW_line_data_T *ldw_line_cfg,unsigned char seconode_type)
{
   float pos[3] = {0,};   
   IMaterial* tempcarmtl;
   Int32 tempmaterialid;
   XRVertexLayout data_format;
   tempmaterialid = pSeneNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
   tempcarmtl->SetDiffuseMap(ldw_line_cfg->icon_file_name[ldw_line_cfg->alarm_state]);
   
   
   
   int lisenceMeshId = pSeneNode->CreateMesh(ModelType_Plane_Dynamic,2,  LDW_LINE_POINT_NUM,0, "ldw_line", &m_p_box_slot[m_text_box_cur_index].pLineMesh);
   int groundId = pSeneNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &m_p_box_slot[m_text_box_cur_index].pNode);
   
   m_p_box_slot[m_text_box_cur_index].pNode->SetMesh(lisenceMeshId);
   //m_overlay->RotateDX(90);  
   m_p_box_slot[m_text_box_cur_index].pNode->SetEnable(ldw_line_cfg->show_flag);
   
   m_p_box_slot[m_text_box_cur_index].pLineMesh->LockData(&m_p_box_slot[m_text_box_cur_index].pdatabuffer,&data_format,&m_p_box_slot[m_text_box_cur_index].element_num);
     
   m_p_box_slot[m_text_box_cur_index].p_ldw_line_data = ldw_line_cfg;
   m_p_box_slot[m_text_box_cur_index].icon_box_id = m_text_box_cur_index;
   m_p_box_slot[m_text_box_cur_index].pLineMtl = tempcarmtl;

	m_pSeneNode = pSeneNode;
	
	
	m_text_box_cur_index++;
	return 0;
}
void HMILDWLine::CvtPointCoordinate(float *out_model_Coord,float *in_world_coord)
{

     AVMData::GetInstance()->cvtWorldPoint2Stich2DPoint(out_model_Coord,in_world_coord);

}

/*LDW line function :  y=0.5*curv*x*x + slop*x+offset*/
void HMILDWLine::GenerateLDWLinePlane(float curv,float slop,float L_offset,float R_offset,int total_num,float*pVertex)
{

	float yLeft;
	float yRight;

	unsigned int slotid=0;;
	
	float world_coord[3]={0,0,0};
	float model_coord[3];
    float x_step = (m_view_wolrd_top-m_view_world_bottom)/total_num;
	float x_pos = m_view_world_bottom;
	float y_base =0;
	for(int i =0;i<total_num;i++)
	{
        
        x_pos=m_view_world_bottom+i*x_step;
		y_base = 0.5*curv*x_pos*x_pos+slop*x_pos;
		yLeft = y_base+L_offset;
		yRight = y_base+R_offset;
        world_coord[0]=x_pos;
		world_coord[1]=yLeft;
        CvtPointCoordinate(model_coord,world_coord);
		pVertex[slotid+0]= model_coord[0];
		pVertex[slotid+1]= model_coord[1];
		pVertex[slotid+2]= model_coord[2];

        slotid+=8;
    	world_coord[0]=x_pos;
    	world_coord[1]=yRight;
    	CvtPointCoordinate(model_coord,world_coord);
		
		pVertex[slotid+0]= model_coord[0];
		pVertex[slotid+1] = model_coord[1];
		pVertex[slotid+2] = model_coord[2];
		slotid+=8;

		

	}
	


}
int HMILDWLine::Update(void)
{
    ISpirit *pBackgroundLayer;
	float pOutput[4];
	IMesh *pMeshTemp;
	for(int i =0;i<m_text_box_cur_index;i++)
	{
	    if(m_p_box_slot[i].p_ldw_line_data->show_flag == 0)
	    {
			m_p_box_slot[i].pNode->SetEnable(0);

	    }
		else
		{
		
		    m_p_box_slot[i].pNode->SetEnable(1);
			m_p_box_slot[i].pLineMtl->SetDiffuseMap(m_p_box_slot[i].p_ldw_line_data->icon_file_name[m_p_box_slot[i].p_ldw_line_data->alarm_state]);

			GenerateLDWLinePlane(m_p_box_slot[i].p_ldw_line_data->curv,m_p_box_slot[i].p_ldw_line_data->slope,m_p_box_slot[i].p_ldw_line_data->L_offset,
				m_p_box_slot[i].p_ldw_line_data->R_offset,LDW_LINE_POINT_NUM,m_p_box_slot[i].pdatabuffer);
	         m_p_box_slot[i].pLineMesh->UnLockData();
		}
	}
	return 0;
}
