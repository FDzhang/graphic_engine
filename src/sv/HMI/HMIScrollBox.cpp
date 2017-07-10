

#include "HMIScrollBox.h"

#include <math.h>



/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/







/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


HMIScrollBox::HMIScrollBox(Region Global,Region Part,int slot_num)
{
    m_global_region = Global;
	m_text_aera_region = Part;	
	m_text_box_slot_num = slot_num;
} 
void HMIScrollBox::Init(ISceneNode *pSeneNode)
{

	m_p_box_slot = new st_scroll_box_data_slot_T [m_text_box_slot_num];
    m_text_box_cur_index = 0;
}
int HMIScrollBox::InitRectNode(float *pose,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer)
{
    
    int tempmaterialid;
    IMaterial *tempcarmtl;
    IMesh *pMeshTemp;
	Int32 iSize;
	XRVertexLayout data_format;
    int slotid=0;
	float textrue[8] = {0.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0};
    tempmaterialid = pSeneNode->CreateMaterial(MtlType, &tempcarmtl);
   
    tempcarmtl->SetDiffuseMap(pTextureName);
    
   
    
    int lisenceMeshId = pSeneNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "ground", &pMeshTemp);
    int groundId = pSeneNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0.0,0.0,0.0, 1.0,pNode);
    
    (*pNode)->SetMesh(lisenceMeshId);
    pMeshTemp->LockData(pBuffer,&data_format,&iSize);
    for(int i =0;i<4;i++)
    {
        (*pBuffer)[slotid+0] = pose[2*i];
		 (*pBuffer)[slotid+1] = pose[2*i+1]; 
		 (*pBuffer)[slotid+2] = 0;
		 
		 (*pBuffer)[slotid+6] = textrue[2*i];
		 (*pBuffer)[slotid+7] = 1.0-textrue[2*i+1]; 

		 

		slotid +=8;
    }
	pMeshTemp->UnLockData();
	return 0;
}
int HMIScrollBox::CalcPose(float *pPoseOutNomal,float *pPoseIn,float width,float height)
{

    float nomal_pose[2];
	float center[2];
	float normal_size[2];
	
	center[0] = (m_text_aera_region.right+m_text_aera_region.left)/2.0;
	center[1] = (m_text_aera_region.top+m_text_aera_region.bottom)/2.0;

	nomal_pose[0] = 2.0*(pPoseIn[0]-center[0])/(m_text_aera_region.right-m_text_aera_region.left);
	nomal_pose[1] = 2.0*(pPoseIn[1]-center[1])/(m_text_aera_region.bottom-m_text_aera_region.top);
	
    normal_size[0] = 2.0*width/(m_text_aera_region.right-m_text_aera_region.left);
	normal_size[1] = 2.0*height/(m_text_aera_region.bottom-m_text_aera_region.top);

	pPoseOutNomal[0] = nomal_pose[0];
	pPoseOutNomal[1] = nomal_pose[1]-normal_size[1];
	pPoseOutNomal[2] = nomal_pose[0]+normal_size[0];
	pPoseOutNomal[3] = nomal_pose[1]-normal_size[1];
	pPoseOutNomal[4] = nomal_pose[0];
	pPoseOutNomal[5] = nomal_pose[1];
	pPoseOutNomal[6] = nomal_pose[0]+normal_size[0];
	pPoseOutNomal[7] = nomal_pose[1];

	return 0;
}

int HMIScrollBox::Add(ISceneNode *pSeneNode,st_scroll_box_data_T *icon_box_cfg)
{
   int mtl_id;  
   IMesh *pTempMesh;
   float scroll_icon_pose[8] = {0,};   

   CalcPose(scroll_icon_pose,icon_box_cfg->pos,icon_box_cfg->width,icon_box_cfg->height);   
   InitRectNode(scroll_icon_pose,&m_pNode[2*m_text_box_cur_index],pSeneNode,icon_box_cfg->icon_file_name[0],Material_Rigid_Blend,&m_Scroll_buffer[m_text_box_cur_index]);
   InitRectNode(scroll_icon_pose,&m_pNode[2*m_text_box_cur_index+1],pSeneNode,icon_box_cfg->icon_file_name[1],Material_Rigid_Blend,&m_Scroll_buffer[m_text_box_cur_index]);
   
  
   m_p_box_slot[m_text_box_cur_index].p_icon_box_data = icon_box_cfg;
   m_p_box_slot[m_text_box_cur_index].icon_box_id = m_text_box_cur_index;
   m_p_box_slot[m_text_box_cur_index].rect_point[0] = scroll_icon_pose[0];
   m_p_box_slot[m_text_box_cur_index].rect_point[1] = scroll_icon_pose[5];   
   m_p_box_slot[m_text_box_cur_index].rect_point[2] = scroll_icon_pose[2];
   m_p_box_slot[m_text_box_cur_index].rect_point[3] = scroll_icon_pose[1];

	m_pSeneNode = pSeneNode;
	
	m_text_box_cur_index++;
	return 0;
}
void HMIScrollBox::CalScrollPos(float scroll_rate,float *Inrect,float*pOutputRect,bool isHorizen,int index)
{
    float top = Inrect[1];
	float left = Inrect[0];
	float bottom = Inrect[3];
	float right = Inrect[2];
    if(scroll_rate>1.0)
    {
        scroll_rate=1.0;
    }
	else if(scroll_rate<0.0)
	{
	    scroll_rate=0.0;
	}
	float height_scroll= (top-bottom)*scroll_rate;
	float *pBuffer = m_Scroll_buffer[index];

    pOutputRect[0] = left;
	pOutputRect[2] = right;
	if(isHorizen == 1)
	{
	    height_scroll= (right-left)*scroll_rate;
		pOutputRect[0] = left;
		pOutputRect[2] = left+height_scroll;
	
    	pOutputRect[1] = top;
    	pOutputRect[3] = bottom;	  
		
		pBuffer[6]=0.0;
		pBuffer[14]=scroll_rate;
		pBuffer[22]=0.0;
		pBuffer[30]=scroll_rate;
		pBuffer[0]=pOutputRect[0];
    	pBuffer[1]=pOutputRect[3];

        pBuffer[8]=pOutputRect[2];
        pBuffer[9]=pOutputRect[3];
    
        pBuffer[16]=pOutputRect[0];
        pBuffer[17]=pOutputRect[1];
    
        pBuffer[24]=pOutputRect[2];
        pBuffer[25]=pOutputRect[1];

		
		
	}
	else
	{
    	pOutputRect[1] = height_scroll+bottom;
    	pOutputRect[3] = bottom;
		pBuffer[7]=1.0;
		pBuffer[15]=1.0;
		pBuffer[23]=1.0-scroll_rate;
		pBuffer[31]=1.0-scroll_rate;
		pBuffer[0]=pOutputRect[0];
    	pBuffer[1]=pOutputRect[3];

        pBuffer[8]=pOutputRect[2];
        pBuffer[9]=pOutputRect[3];
    
        pBuffer[16]=pOutputRect[0];
        pBuffer[17]=pOutputRect[1];
    
        pBuffer[24]=pOutputRect[2];
        pBuffer[25]=pOutputRect[1];

		
	}
	


	return;

}

int HMIScrollBox::Update(void)
{
    ISpirit *pBackgroundLayer;
	float pOutput[15];
	IMesh *pMeshTemp;
	for(int i =0;i<m_text_box_cur_index;i++)
	{
	    if(m_p_box_slot[i].p_icon_box_data->show_flag == 0)
	    {
			m_pNode[2*i]->SetEnable(0);
			m_pNode[2*i+1]->SetEnable(0);


	    }
		else
		{
		
    		m_pNode[2*i]->SetEnable(1);
    		m_pNode[2*i+1]->SetEnable(1);

			CalScrollPos(m_p_box_slot[i].p_icon_box_data->scroll_rate,m_p_box_slot[i].rect_point,pOutput,m_p_box_slot[i].p_icon_box_data->horizon,i);
			
            m_pNode[2*i+1]->GetMesh(&pMeshTemp);
	        pMeshTemp->UnLockData();
		}
	}
	return 0;
}
void HMIScrollBox::SetEnable(bool flag)
{
    for(int i =0;i<m_text_box_cur_index;i++)
    {
        m_pNode[2*i]->SetEnable(flag);
        m_pNode[2*i+1]->SetEnable(flag);
    }
}
