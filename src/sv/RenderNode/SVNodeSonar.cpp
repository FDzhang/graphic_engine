
#include "../AVMData.h"
#include "SVNodeSonar.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

extern char BLUETEX[];
extern char OVERLAYTEX[];
extern char ParkLot[];
char SONAR_WAVE_TEX[] = XR_RES"sonar_wave.dds";
extern st_text_box_data_T gpu_debug_texbox;
char SONAR_PARK_LOT_VERTICAL[]=XR_RES"sonar_park_v.dds";
char SONAR_PARK_LOT_PARALLEL[]=XR_RES"sonar_park_p.dds";
unsigned char guc_reset_parkLot;
extern unsigned int Get_Frame_TimeStamp(void);
extern "C" Radar_PLD_Result* GetSonarPLDDataPointer(void);
 SVNodeSonar:: SVNodeSonar()
{


	
}


int SVNodeSonar::UpdateVertexBuffer(float*pVertex,int index)
{
	unsigned int slotid=0;;
	unsigned int obj_num;
	float world_coord[3]={0,0,0};
	float model_coord[3];
	

    if(m_sonar_draw_obj_list_start[index]<=m_sonar_draw_obj_list_end[index])
    {
        obj_num = m_sonar_draw_obj_list_end[index]-m_sonar_draw_obj_list_start[index];
    }
	else
	{
        obj_num = m_sonar_draw_obj_list_end[index]-m_sonar_draw_obj_list_start[index]+MAX_SONAR_OBJ_NUM;	
	}
	
    for(int i =0;i<obj_num;i++)
	{

		slotid = (m_sonar_draw_obj_list_start[index]+i)%MAX_SONAR_OBJ_NUM;
	    AVMData::GetInstance()->cvtWorldPoint2Stich2DPoint(model_coord,&(m_sonar_draw_obj_list[index][2*slotid]),1);
		pVertex[i*8+0]= model_coord[0];
		pVertex[i*8+1]= model_coord[1];
		pVertex[i*8+2]= model_coord[2];
    
	}
    
	
    return obj_num;

}
int SVNodeSonar::ProcessPreviousParkingLot(COMMON_VEHICLE_DATA_SIMPLE vehicle_state)
{
	Point2f inPoint;
	CvPoint2D32f outPoint;
	sonar_parking_lot_t *pParkinglot;
    for(int i =0;i<MAX_PARKING_LOT_NUM;i++)
    {
        pParkinglot=&m_sonar_parking_lot[i];
        if(pParkinglot->show_flag)
        {
            for(int j=0;j<4;j++)
            {
            
                inPoint.x=pParkinglot->lot_point[2*j];
    			inPoint.y=pParkinglot->lot_point[2*j+1];
    	        m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
                pParkinglot->lot_point[2*j]= inPoint.x;
                pParkinglot->lot_point[2*j+1]= inPoint.y;
            }
			#if 0
            inPoint.x=pParkinglot->lot_start_pos[0];
			inPoint.y=pParkinglot->lot_start_pos[1];
	        m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
            pParkinglot->lot_start_pos[0]= inPoint.x;
            pParkinglot->lot_start_pos[1]= inPoint.y;
            
			if (inPoint.x <VIEW_RANGE_BOTTOM)
			{
			     pParkinglot->show_flag = 0;
			}

			inPoint.x=pParkinglot->lot_end_pos[0];
			inPoint.y=pParkinglot->lot_end_pos[1];
	        m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
            pParkinglot->lot_end_pos[0]= inPoint.x;
            pParkinglot->lot_end_pos[1]= inPoint.y;
			#endif
        }
    }
	return 0;
}
	

int  SVNodeSonar::ProcessPreviousPos(COMMON_VEHICLE_DATA_SIMPLE vehicle_state)
{

	static int init_flag = 0;
	int present_time=0;
	Point2f inPoint;
	CvPoint2D32f outPoint;
	int update_key_frame_flag;
	int out_range_index=0;
    int out_range_index_part;
    present_time = XrGetTime();
		

	//m_vehicle_motion->revMotion2KframePredictVCS(vehicle_state,40000,m_track,m_t,m_Move_Matrix,update_key_frame_flag,0.3);
	update_key_frame_flag = 0;

    for(int j=0;j<max_sonar_num;j++)
    {
        if(j!=front_left_side_sonar &&j != front_right_side_sonar)
        {
            continue;
        }
		out_range_index = m_sonar_obj_list_start[j];
        if(m_sonar_obj_list_start[j]<=m_sonar_obj_list_end[j])
        {
            for (int i= m_sonar_obj_list_start[j];i<m_sonar_obj_list_end[j];i++)
            {
                inPoint.x = m_sonar_obj_list[j][2*i];
                inPoint.y = m_sonar_obj_list[j][2*i+1];				
        
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
                 m_sonar_obj_list[j][2*i]=inPoint.x;
                 m_sonar_obj_list[j][2*i+1]=inPoint.y;	      
				 if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }
				// printf("\r\n 111 m_sonar_obj_list[%d][%d]=(%f,%f)",j,i,m_sonar_obj_list[j][2*i],m_sonar_obj_list[j][2*i+1]);
            }
			m_sonar_obj_list_start[j] = out_range_index;
			
        }
		else
		{
            for (int i= m_sonar_obj_list_start[j];i<MAX_SONAR_OBJ_NUM;i++)
            {
                inPoint.x = m_sonar_obj_list[j][2*i];
                inPoint.y = m_sonar_obj_list[j][2*i+1];				
        
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
				m_sonar_obj_list[j][2 * i] = inPoint.x;
				m_sonar_obj_list[j][2 * i + 1] = inPoint.y;
				if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }
				
				//printf("\r\n 222 m_sonar_obj_list[%d][%d]=(%f,%f)",j,i,m_sonar_obj_list[j][2*i],m_sonar_obj_list[j][2*i+1]);
            }
			for(int i = 0;i<m_sonar_obj_list_end[j];i++)
			{
                inPoint.x = m_sonar_obj_list[j][2*i];
                inPoint.y = m_sonar_obj_list[j][2*i+1];				
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
				m_sonar_obj_list[j][2 * i] = inPoint.x;
				m_sonar_obj_list[j][2 * i + 1] = inPoint.y;
				if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }
			//	printf("\r\n 333 m_sonar_obj_list[%d][%d]=(%f,%f)",j,i,m_sonar_obj_list[j][2*i],m_sonar_obj_list[j][2*i+1]);


			}
			m_sonar_obj_list_start[j] = out_range_index;
		}
    }

	//process draw_list

	
    for(int j=0;j<max_sonar_num;j++)
    {
        if(j!=front_left_side_sonar &&j != front_right_side_sonar)
		{
			continue;
		}
		out_range_index = m_sonar_draw_obj_list_start[j];
        if(m_sonar_draw_obj_list_start[j]<=m_sonar_draw_obj_list_end[j])
        {
            for (int i= m_sonar_draw_obj_list_start[j];i<m_sonar_draw_obj_list_end[j];i++)
            {
                inPoint.x = m_sonar_draw_obj_list[j][2*i];
                inPoint.y = m_sonar_draw_obj_list[j][2*i+1];				
        
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
                 m_sonar_draw_obj_list[j][2*i]=inPoint.x;
                 m_sonar_draw_obj_list[j][2*i+1]=inPoint.y;	      
				 if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }
            }
			m_sonar_draw_obj_list_start[j] = out_range_index;
			
        }
		else
		{
            for (int i= m_sonar_draw_obj_list_start[j];i<MAX_SONAR_OBJ_NUM;i++)
            {
                inPoint.x = m_sonar_draw_obj_list[j][2*i];
                inPoint.y = m_sonar_draw_obj_list[j][2*i+1];				
        
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
				m_sonar_draw_obj_list[j][2 * i] = inPoint.x;
				m_sonar_draw_obj_list[j][2 * i + 1] = inPoint.y;
				if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }
            }
			for(int i = 0;i<m_sonar_draw_obj_list_end[j];i++)
			{
                inPoint.x = m_sonar_draw_obj_list[j][2*i];
                inPoint.y = m_sonar_draw_obj_list[j][2*i+1];				
				m_vehicle_motion->get_new_point_from_Vhichle_data(&inPoint, &vehicle_state, (float)Get_Frame_TimeStamp() / 1000000.0);
    			
				m_sonar_draw_obj_list[j][2 * i] = inPoint.x;
				m_sonar_draw_obj_list[j][2 * i + 1] = inPoint.y;
				if (inPoint.x <VIEW_RANGE_BOTTOM)
                 {
                     out_range_index = i; 
                 }


			}
			m_sonar_draw_obj_list_start[j] = out_range_index;
		    
		}
    }
    return update_key_frame_flag;
		
}


int SVNodeSonar::InitLineMesh(void)
{

    IMaterial* tempcarmtl;
	Int32 tempmaterialid;
	XRVertexLayout data_format;
	int lisenceMeshId;
	int groundId;
	float pos[3]={0.0,0.0,0.0};


    

    for(int i =0;i<max_sonar_num;i++)
    {
		tempmaterialid = m_pStichNode->CreateMaterial(Material_Color_Plot, &tempcarmtl);
		
		tempcarmtl->SetDiffuseMap(OVERLAYTEX);
		tempcarmtl->SetEnvironmentMap(BLUETEX);
        tempcarmtl->SetAmbientColor(m_sonar_color_list[3*i],m_sonar_color_list[3*i+1],m_sonar_color_list[3*i+2]);
	m_sonar_data[i].show_flag = 0;
	    lisenceMeshId = m_pStichNode->CreateMesh(ModelType_Plane_Dynamic,2,  MAX_SONAR_OBJ_NUM/2,0, "sonar", &m_sonar_data[i].pLineMesh);
	    groundId = m_pStichNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &m_sonar_data[i].pNode);
		m_sonar_data[i].pNode->SetMesh(lisenceMeshId);
		m_sonar_data[i].pNode->SetEnable(m_sonar_data[i].show_flag);
		m_sonar_data[i].pLineMesh->LockData(&m_sonar_data[i].pdatabuffer,&data_format,&m_sonar_data[i].element_num);
		m_sonar_data[i].pLineMesh->SetRenderPlot(1);
		m_sonar_data[i].pLineMtl = tempcarmtl;
		
    }
	return 0;

}

int SVNodeSonar::InitParkinglotRect(void)
{
   float pos[3] = {0,};   
   IMaterial* tempcarmtl;
   Int32 tempmaterialid,lisenceMeshId,groundId;
   XRVertexLayout data_format;

   
   for(int i =0;i<MAX_PARKING_LOT_NUM;i++)
   {
       tempmaterialid = m_pStichNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
       tempcarmtl->SetDiffuseMap(ParkLot);
       lisenceMeshId = m_pStichNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "stichview_rect", &m_sonar_parking_lot_hmi[i].pRectMesh);
       groundId = m_pStichNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &m_sonar_parking_lot_hmi[i].pNode);
       
       m_sonar_parking_lot_hmi[i].pNode->SetMesh(lisenceMeshId);
       m_sonar_parking_lot_hmi[i].pNode->SetEnable(0);
       m_sonar_parking_lot_hmi[i].pRectMesh->LockData(&m_sonar_parking_lot_hmi[i].pdatabuffer,&data_format,&m_sonar_parking_lot_hmi[i].element_num);        
       InitParkingLotTexture(i,m_sonar_parking_lot_hmi[i].pdatabuffer);
       m_sonar_parking_lot_hmi[i].pRectMtl = tempcarmtl;
   }
	
	
	return 0;
}
void SVNodeSonar::InitParkingLotTexture(int sonar_index,Float32 *pDataBuffer)
{
     if(sonar_index==front_left_side_sonar)
     {
		 pDataBuffer[8*rect_point_near_bottom+6]= 1.0;
		 pDataBuffer[8*rect_point_near_bottom+7]=0.0;
		 
		  pDataBuffer[8*rect_point_near_top+6]= 1.0;
		  pDataBuffer[8*rect_point_near_top+7]=1.0;
		 
		  pDataBuffer[8*rect_point_far_bottom+6]= 0.0;
		  pDataBuffer[8*rect_point_far_bottom+7]=0.0;
		 
		   pDataBuffer[8*rect_point_far_top+6]= 0.0;
		   pDataBuffer[8*rect_point_far_top+7]=1.0;


     }
	 else
	 {
        pDataBuffer[8*rect_point_near_bottom+6]= 0.0;
		pDataBuffer[8*rect_point_near_bottom+7]=0.0;

    	 pDataBuffer[8*rect_point_near_top+6]= 0.0;
    	 pDataBuffer[8*rect_point_near_top+7]=1.0;

    	 pDataBuffer[8*rect_point_far_bottom+6]= 1.0;
    	 pDataBuffer[8*rect_point_far_bottom+7]=0.0;
	 
    	  pDataBuffer[8*rect_point_far_top+6]= 1.0;
    	  pDataBuffer[8*rect_point_far_top+7]=1.0;
	 
	 }


}
void SVNodeSonar::DrawParkLot(void)
{

    for(int i=0;i<MAX_PARKING_LOT_NUM;i++)
    {
        if(m_sonar_parking_lot[i].show_flag == 1)
        {
           // fprintf(stdout,"draw %d parklot",m_sonar_parking_lot[i].show_flag );
             GenerateParkLotRect(&m_sonar_parking_lot[i],m_sonar_parking_lot_hmi[i].pdatabuffer);

			 m_sonar_parking_lot_hmi[i].pRectMesh->UnLockData();
			 m_sonar_parking_lot_hmi[i].pNode->SetEnable(1);
             if(m_sonar_parking_lot[i].parking_lot_type == PARKING_LOT_NOT_SIUTABLE)
             {
                 m_sonar_parking_lot_hmi[i].pRectMtl->SetDiffuseMap(OVERLAYTEX);
             }
			 else if(m_sonar_parking_lot[i].parking_lot_type == PARKING_LOT_VERTICAL)
			 {
                 m_sonar_parking_lot_hmi[i].pRectMtl->SetDiffuseMap(SONAR_PARK_LOT_VERTICAL);
			 
			 }
			 else
			 {			     
                 m_sonar_parking_lot_hmi[i].pRectMtl->SetDiffuseMap(SONAR_PARK_LOT_PARALLEL);
			 }
        }
		else
		{
		
		    m_sonar_parking_lot_hmi[i].pNode->SetEnable(0);
		}
    }
    


}
void SVNodeSonar::SetRadarPLDReslt()
{
    Radar_PLD_Result *pRadarPldRslt=NULL;
    
	pRadarPldRslt= GetSonarPLDDataPointer();
    //right park lot has higher priority
    if((m_sonar_parking_lot[front_right_side_sonar].parking_lot_type != PARKING_LOT_NOT_SIUTABLE)&&m_sonar_parking_lot[front_right_side_sonar].show_flag==1)
    {
        pRadarPldRslt->iParkLotBitFlag = m_sonar_parking_lot[front_right_side_sonar].parking_lot_type;
		pRadarPldRslt->iParkLotNum = 1;
       #if 0
		pRadarPldRslt->sGround_Points[0].x = m_sonar_parking_lot[front_right_side_sonar].lot_start_pos[0];
		pRadarPldRslt->sGround_Points[0].y = m_sonar_parking_lot[front_right_side_sonar].lot_start_pos[1];	
		pRadarPldRslt->sGround_Points[1].x = m_sonar_parking_lot[front_right_side_sonar].lot_start_pos[0];
		pRadarPldRslt->sGround_Points[1].y = m_sonar_parking_lot[front_right_side_sonar].lot_start_pos[1]+m_sonar_parking_lot[front_right_side_sonar].lot_width;
		pRadarPldRslt->sGround_Points[2].x = m_sonar_parking_lot[front_right_side_sonar].lot_end_pos[0];
		pRadarPldRslt->sGround_Points[2].y = m_sonar_parking_lot[front_right_side_sonar].lot_end_pos[1];	
		pRadarPldRslt->sGround_Points[3].x = pRadarPldRslt->sGround_Points[2].x ;
		pRadarPldRslt->sGround_Points[3].y = pRadarPldRslt->sGround_Points[1].y;

    #endif
	
    	pRadarPldRslt->sGround_Points[0].x = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_near_bottom];
    	pRadarPldRslt->sGround_Points[0].y = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_near_bottom+1];	
		
    	pRadarPldRslt->sGround_Points[1].x = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_far_bottom];
    	pRadarPldRslt->sGround_Points[1].y = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_far_bottom+1];
		
    	pRadarPldRslt->sGround_Points[2].x = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_near_top];
    	pRadarPldRslt->sGround_Points[2].y = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_near_top+1];	
		
    	pRadarPldRslt->sGround_Points[3].x = m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_far_top] ;
    	pRadarPldRslt->sGround_Points[3].y =  m_sonar_parking_lot[front_right_side_sonar].lot_point[2*rect_point_far_top+1];

		
    }
	#if 0
	else if(m_sonar_parking_lot[front_left_side_sonar].parking_lot_type != PARKING_LOT_NOT_SIUTABLE&&m_sonar_parking_lot[front_left_side_sonar].show_flag==1)
	{

    	pRadarPldRslt->iParkLotBitFlag = m_sonar_parking_lot[front_left_side_sonar].parking_lot_type;
    	pRadarPldRslt->iParkLotNum = 1;

		pRadarPldRslt->sGround_Points[0].x = m_sonar_parking_lot[front_left_side_sonar].lot_start_pos[0];
		pRadarPldRslt->sGround_Points[0].y = m_sonar_parking_lot[front_left_side_sonar].lot_start_pos[1];	
		pRadarPldRslt->sGround_Points[1].x = m_sonar_parking_lot[front_left_side_sonar].lot_start_pos[0];
		pRadarPldRslt->sGround_Points[1].y = m_sonar_parking_lot[front_left_side_sonar].lot_start_pos[1]-m_sonar_parking_lot[front_left_side_sonar].lot_width;
		pRadarPldRslt->sGround_Points[2].x = m_sonar_parking_lot[front_left_side_sonar].lot_end_pos[0];
		pRadarPldRslt->sGround_Points[2].y = m_sonar_parking_lot[front_left_side_sonar].lot_end_pos[1];	
		pRadarPldRslt->sGround_Points[3].x = pRadarPldRslt->sGround_Points[2].x ;
		pRadarPldRslt->sGround_Points[3].y = pRadarPldRslt->sGround_Points[1].y;
		

	
	}
	#endif
	else
	{
    	pRadarPldRslt->iParkLotBitFlag = m_sonar_parking_lot[front_right_side_sonar].parking_lot_type;
    	pRadarPldRslt->iParkLotNum = 0;
		
		pRadarPldRslt->sGround_Points[0].x = 0.0;
		pRadarPldRslt->sGround_Points[0].y = 0.0;	
		pRadarPldRslt->sGround_Points[1].x = 0.0;
		pRadarPldRslt->sGround_Points[1].y = 0.0;
		pRadarPldRslt->sGround_Points[2].x = 0.0;
		pRadarPldRslt->sGround_Points[2].y = 0.0;	
		pRadarPldRslt->sGround_Points[3].x = 0.0;
		pRadarPldRslt->sGround_Points[3].y = 0.0;

	}
	
	
}
void SVNodeSonar::GenerateParkLotRect(sonar_parking_lot_t *park_lot_state,float *pVertex)
{

    float park_width = DEFAULT_PARALLEL_LOT_WIDTH;
	float model_coord[3]={0,0,0};
	float sign = 1.0;
	float park_lot_pos[8];
     if(park_lot_state->parking_lot_type == SONAR_PARKING_LOT_VERTICAL)
    {
        park_width = DEFAULT_VERTICAL_LOT_WIDTH;
		
    }
	if (park_lot_state->lot_start_pos[1]<0)
	{
		sign = -1.0;
	}

	park_width = park_lot_state->lot_width;
	park_lot_pos[0]=park_lot_state->lot_point[2*rect_point_near_bottom];	
	park_lot_pos[1]=park_lot_state->lot_point[2*rect_point_near_bottom+1];
	
	park_lot_pos[2]=park_lot_state->lot_point[2*rect_point_far_bottom]; 
	park_lot_pos[3] = park_lot_state->lot_point[2*rect_point_far_bottom+1];
	
	park_lot_pos[4]=park_lot_state->lot_point[2*rect_point_near_top];
	park_lot_pos[5]=park_lot_state->lot_point[2*rect_point_near_top+1];

	park_lot_pos[6] = park_lot_state->lot_point[2*rect_point_far_top];
	park_lot_pos[7] = park_lot_state->lot_point[2*rect_point_far_top+1];


    for(int i =0;i<4;i++)
	{
		AVMData::GetInstance()->cvtWorldPoint2Stich2DPoint(model_coord,&(park_lot_pos[2*i]),1);
		pVertex[i*8+0]= model_coord[0];
		pVertex[i*8+1]= model_coord[1];
		pVertex[i*8+2]= model_coord[2];   
	}


}

int  SVNodeSonar::Init(BEV_CONFIG_T *pConfig,ISceneNode *pStichNode)
{

     memcpy(m_sonar_pos,&(pConfig->smc_hmi.REAR_LEFT_CONOR_SONAR_POS_X),max_sonar_num*sizeof(Sonar_Pos));
	 
     memcpy(m_sonar_color_list,&(pConfig->smc_hmi.REAR_LEFT_CONOR_SONAR_COLOR_R ),max_sonar_num*3*sizeof(float));
	 for(int i = 0;i<max_sonar_num;i++)
	 {
	     m_sonar_obj_list_start[i]=0;
		 m_sonar_obj_list_end[i] = 0;
		 m_sonar_draw_obj_list_start[i]=0;
		 m_sonar_draw_obj_list_end[i] = 0;
		 for(int j=0;j<max_sonar_num;j++)
		 {
		     m_sonar_overlap_flag[i][j]=0;
		 }
	 }
	 for(int i =0;i<9;i++)
	 {
		 if(i == 0||i==4||i==8)
		 {
		     m_t[i]=1.00;
		     m_Move_Matrix[i]=1.0;
		 }
		 else
		 {

		     m_t[i]=0;
		     m_Move_Matrix[i]=0;
		 }
	 }	 
	 m_vehicle_motion = new VehicleMotion;
	 m_pStichNode = pStichNode;
	 InitLineMesh();
	 InitParkinglotRect();
	 InitSoarArc();
	 m_track=0;
	 m_parking_lot_pos = 0;
	 m_track_park_lot_flag=0;
	 ResetParkSlotInfo();
	 TestVehicleMovment();
	 return 0;
}
int SVNodeSonar::TestVehicleMovment(void)
{
    //return 0;
	m_sonar_parking_lot[front_left_conor_sonar].show_flag = 1;
     m_sonar_parking_lot[front_left_conor_sonar].parking_lot_type =PARKING_LOT_PARALLEL;

	 m_sonar_parking_lot[front_left_conor_sonar].lot_length = 5000;
	 m_sonar_parking_lot[front_left_conor_sonar].lot_width= 2000;
	 m_sonar_parking_lot[front_left_conor_sonar].lot_end_pos[0]=3776;// m_sonar_parking_lot[front_left_conor_sonar].lot_start_pos[0]-;
	 m_sonar_parking_lot[front_left_conor_sonar].lot_end_pos[1] = 1839/2.0+800;


     m_sonar_parking_lot[front_left_conor_sonar].lot_start_pos[0] = m_sonar_parking_lot[front_left_conor_sonar].lot_end_pos[0]-m_sonar_parking_lot[front_left_conor_sonar].lot_length;
     m_sonar_parking_lot[front_left_conor_sonar].lot_start_pos[1] =  m_sonar_parking_lot[front_left_conor_sonar].lot_end_pos[1];
	// fprintf(stdout,"testtesttestprint");
	int park_lot_index=front_left_conor_sonar;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_top]=m_sonar_parking_lot[park_lot_index].lot_end_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_bottom]=m_sonar_parking_lot[park_lot_index].lot_start_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_start_pos[1] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top]=m_sonar_parking_lot[park_lot_index].lot_end_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom]=m_sonar_parking_lot[park_lot_index].lot_start_pos[0] ;

	if(m_sonar_parking_lot[park_lot_index].lot_end_pos[0]>0)
	{
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]+m_sonar_parking_lot[park_lot_index].lot_width ;
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]+m_sonar_parking_lot[park_lot_index].lot_width ;

	}
	else
	{
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]-m_sonar_parking_lot[park_lot_index].lot_width ;
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]-m_sonar_parking_lot[park_lot_index].lot_width ;
	   
	}

	 return 0;


}
int SVNodeSonar::InitSoarArc(void)
{

    IMaterial* tempcarmtl;
	Int32 tempmaterialid;
	XRVertexLayout data_format;
	int lisenceMeshId;
	int groundId;
	float pos[3]={0.0,0.0,0.0};


    

    for(int i =0;i<max_sonar_num;i++)
    {
		tempmaterialid = m_pStichNode->CreateMaterial(Material_Rigid_Blend, &tempcarmtl);
		
		tempcarmtl->SetDiffuseMap(SONAR_WAVE_TEX);
		tempcarmtl->SetEnvironmentMap(BLUETEX);
        tempcarmtl->SetAmbientColor(m_sonar_color_list[3*i],m_sonar_color_list[3*i+1],m_sonar_color_list[3*i+2]);
	
	    lisenceMeshId = m_pStichNode->CreateMesh(ModelType_Plane_ARC,2000, 60,120, "sonar_arc", &m_sonar_arc_data[i].pLineMesh);
	    groundId = m_pStichNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,pos[0],pos[1],pos[2], 1.0, &m_sonar_arc_data[i].pNode);
		m_sonar_arc_data[i].pNode->SetMesh(lisenceMeshId);
		m_sonar_arc_data[i].pNode->SetEnable(m_sonar_arc_data[i].show_flag);
		m_sonar_arc_data[i].pLineMesh->LockData(&m_sonar_arc_data[i].pdatabuffer,&data_format,&m_sonar_arc_data[i].element_num);
		//m_sonar_arc_data[i].pLineMesh->SetRenderPlot(1);
		m_sonar_arc_data[i].pLineMtl = tempcarmtl;
    }
	return 0;

}


//unit must be mm
int  SVNodeSonar::CalcSonarObjPos(float *pos,float obj_dist,sonar_index index)
{
    float rad_angle;
	rad_angle = (m_sonar_pos[index].angle/180)*SONAR_PI;
	
    pos[0]=m_sonar_pos[index].pos[0]+obj_dist*sin(rad_angle);
    pos[1]=m_sonar_pos[index].pos[1]+obj_dist*cos(rad_angle);    
    pos[2] = m_sonar_pos[index].pos[2];

	return 0;
}
int SVNodeSonar::CalcMultiSonarObj(float *pos,float *dist_list,sonar_index index)
{
    int ret =0;
    switch (index)
    {
    	case front_left_conor_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[front_left_conor_sonar],front_left_conor_sonar,dist_list[front_left_middle_sonar],front_left_middle_sonar,SONAR_INDEX_FRONT_ANTI_CLOCKWISE))
            {
                ret=1;
				
            }
			else
			{
			    ret=CalcTwoSonarObjPos(pos,dist_list[front_left_conor_sonar],front_left_conor_sonar,dist_list[front_left_side_sonar],front_left_side_sonar,SONAR_INDEX_FRONT_CLOCKWISE);
			}
    	break;	
    	case front_left_middle_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[front_left_middle_sonar],front_left_middle_sonar,dist_list[front_right_middle_sonar],front_right_middle_sonar,SONAR_INDEX_FRONT_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			    ret=CalcTwoSonarObjPos(pos,dist_list[front_left_middle_sonar],front_left_middle_sonar,dist_list[front_left_conor_sonar],front_left_conor_sonar,SONAR_INDEX_FRONT_CLOCKWISE);
			}
    	break;			
    	case front_right_middle_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[front_right_middle_sonar],front_right_middle_sonar,dist_list[front_right_conor_sonar],front_right_conor_sonar,SONAR_INDEX_FRONT_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			    ret=CalcTwoSonarObjPos(pos,dist_list[front_right_middle_sonar],front_right_middle_sonar,dist_list[front_left_middle_sonar],front_left_middle_sonar,SONAR_INDEX_FRONT_CLOCKWISE);
			}
    	break;	
    	case front_right_conor_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[front_right_conor_sonar],front_right_conor_sonar,dist_list[front_right_side_sonar],front_right_side_sonar,SONAR_INDEX_FRONT_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			   ret= CalcTwoSonarObjPos(pos,dist_list[front_right_conor_sonar],front_right_conor_sonar,dist_list[front_right_middle_sonar],front_right_middle_sonar,SONAR_INDEX_FRONT_CLOCKWISE);
			}
    	break;
    	case rear_left_conor_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[rear_left_conor_sonar],rear_left_conor_sonar,dist_list[rear_left_middle_sonar],rear_left_middle_sonar,SONAR_INDEX_REAR_CLOCKWISE))
            {
                ret=1;
            
            }
    	break;	
    	case rear_left_middle_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[rear_left_middle_sonar],rear_left_middle_sonar,dist_list[rear_left_conor_sonar],rear_left_conor_sonar,SONAR_INDEX_REAR_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			    ret=CalcTwoSonarObjPos(pos,dist_list[rear_left_middle_sonar],rear_left_middle_sonar,dist_list[rear_right_middle_sonar],rear_right_middle_sonar,SONAR_INDEX_REAR_CLOCKWISE);
			}
    	break;			
    	case rear_right_middle_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[rear_right_middle_sonar],rear_right_middle_sonar,dist_list[rear_left_middle_sonar],rear_left_middle_sonar,SONAR_INDEX_REAR_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			    ret=CalcTwoSonarObjPos(pos,dist_list[rear_right_middle_sonar],rear_right_middle_sonar,dist_list[rear_right_conor_sonar],rear_right_conor_sonar,SONAR_INDEX_REAR_CLOCKWISE);
			}
    	break;	
    	case rear_right_conor_sonar:
            if(CalcTwoSonarObjPos(pos,dist_list[rear_right_conor_sonar],rear_right_conor_sonar,dist_list[rear_right_middle_sonar],rear_right_middle_sonar,SONAR_INDEX_REAR_ANTI_CLOCKWISE))
            {
                ret=1;
                
            }
			else
			{
			    //CalcTwoSonarObjPos(pos,dist_list[front_right_conor_sonar],front_right_conor_sonar,dist_list[front_right_middle_sonar],front_right_middle_sonar);
			}
    	break;


    }
	return ret;
}
int  SVNodeSonar::CalcTwoSonarObjPos(float *pos,float obj1_dist,sonar_index obj1_index,float obj2_dist,sonar_index obj2_index,int clockwiseflag)
{
    float rad_angle;
	float alpha,beta,cosalpha,tanbeta;
    float sonar_x1,sonar_x2,sonar_y1,sonar_y2,d12;
	float x_temp,y_temp;
	sonar_x1 = m_sonar_pos[obj1_index].pos[0];
	sonar_y1 = m_sonar_pos[obj1_index].pos[1];
	sonar_x2 = m_sonar_pos[obj2_index].pos[0];
	sonar_y2 = m_sonar_pos[obj2_index].pos[1];
	int ret,temp;

	d12 = sqrt((sonar_x1-sonar_x2)*(sonar_x1-sonar_x2)+(sonar_y1-sonar_y2)*(sonar_y1-sonar_y2));
	cosalpha = (d12*d12+obj1_dist*obj1_dist-obj2_dist*obj2_dist)/(2*obj1_dist*d12);

	//check if the obj is in sonar FOV
	if (fabs(cosalpha) <= 1)
	{
		alpha = acos(cosalpha);
		temp = CheckObjInSonarFOV((int)obj1_index, (int)obj2_index, alpha, clockwiseflag);
	}
	else
	{
		temp = 0;
	}
	//if(fabs(cosalpha)<=1) // 2 sonar detect the same object
	if(temp)
	{
		#if 0
        alpha = acos(cosalpha);
		beta = atan((sonar_y2-sonar_y1)/(sonar_x2-sonar_x1));
        x_temp = obj1_dist*cosalpha;
		y_temp = obj1_dist*sin(alpha);

		pos[0] = sonar_x1+x_temp*cos(beta)-y_temp*sin(beta);
		pos[1] = -(sonar_y1+x_temp*sin(beta)+y_temp*cos(beta));		
        pos[2] = m_sonar_pos[obj1_index].pos[2];
		ret=1;
		#endif
		if (clockwiseflag == SONAR_INDEX_FRONT_ANTI_CLOCKWISE)
		{
			alpha = acos(cosalpha);
			beta = -atan((sonar_x2 - sonar_x1) / (sonar_y2 - sonar_y1));
			y_temp = obj1_dist*cosalpha;
			x_temp = obj1_dist*sin(alpha);

			pos[0] = sonar_x1 + x_temp*cos(beta) - y_temp*sin(beta);
			pos[1] = sonar_y1 + x_temp*sin(beta) + y_temp*cos(beta);
			pos[2] = m_sonar_pos[obj1_index].pos[2];
			ret = 1;
		}
		else if(clockwiseflag == SONAR_INDEX_FRONT_CLOCKWISE)
		{
			alpha = acos(cosalpha);
			beta = PI-atan((sonar_x2 - sonar_x1) / (sonar_y2 - sonar_y1));
			y_temp = obj1_dist*cosalpha; 
			x_temp = -obj1_dist*sin(alpha);

			pos[0] = sonar_x1 + x_temp*cos(beta) - y_temp*sin(beta); 
			pos[1] = sonar_y1 + x_temp*sin(beta) + y_temp*cos(beta);
			pos[2] = m_sonar_pos[obj1_index].pos[2];
 			ret = 1;
		}
		else if (clockwiseflag == SONAR_INDEX_REAR_ANTI_CLOCKWISE)
		{
			alpha = acos(cosalpha);
			beta = PI-atan((sonar_x2 - sonar_x1) / (sonar_y2 - sonar_y1));
			y_temp = obj1_dist*cosalpha;
			x_temp = obj1_dist*sin(alpha);

			pos[0] = sonar_x1 + x_temp*cos(beta) - y_temp*sin(beta);
			pos[1] = sonar_y1 + x_temp*sin(beta) + y_temp*cos(beta);
			pos[2] = m_sonar_pos[obj1_index].pos[2];
			ret = 1;
		}
		else 
		{
			alpha = acos(cosalpha);
			beta = -atan((sonar_x2 - sonar_x1) / (sonar_y2 - sonar_y1));
			y_temp = obj1_dist*cosalpha; 
			x_temp = -obj1_dist*sin(alpha);

			pos[0] = sonar_x1 + x_temp*cos(beta) - y_temp*sin(beta); 
			pos[1] = sonar_y1 + x_temp*sin(beta) + y_temp*cos(beta);
			pos[2] = m_sonar_pos[obj1_index].pos[2];
			ret = 1;
		}
	}
	else
	{
    	rad_angle = (m_sonar_pos[obj1_index].angle/180)*SONAR_PI;
    	
        pos[0]=m_sonar_pos[obj1_index].pos[0]+obj1_dist*sin(rad_angle);
        pos[1]=m_sonar_pos[obj1_index].pos[1]+obj1_dist*cos(rad_angle);    
        pos[2] = m_sonar_pos[obj1_index].pos[2];
		ret = 0;
	}

	
	m_sonar_overlap_flag[obj1_index][obj2_index]=(bool)ret;
	return ret;
}
int SVNodeSonar::CheckObjInSonarFOV(int sonar1_index,int sonar2_index,float alpha,int sonar_clockwise_flag)
{
    float rad_angle;
	float beta,cosbeta,tanbeta;
    float sonar_x1,sonar_x2,sonar_y1,sonar_y2,d12;
	float angle_delta;
	sonar_x1 = m_sonar_pos[sonar1_index].pos[0];
	sonar_y1 = m_sonar_pos[sonar1_index].pos[1];
	sonar_x2 = m_sonar_pos[sonar2_index].pos[0];
	sonar_y2 = m_sonar_pos[sonar2_index].pos[1];
	rad_angle = (m_sonar_pos[sonar1_index].angle)/180.0*PI;
	d12=sqrt((sonar_x2-sonar_x1)*(sonar_x2-sonar_x1)+(sonar_y2-sonar_y1)*(sonar_y2-sonar_y1));
	cosbeta = ((sonar_x2-sonar_x1)*sin(rad_angle)+(sonar_y2-sonar_y1)*cos(rad_angle))/d12;
	rad_angle = acos(cosbeta);
    angle_delta = SONAR_HALF_FOV/180.0*PI;

	if(alpha<=rad_angle+angle_delta&&alpha>=rad_angle-angle_delta)
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
	

	


}
float SVNodeSonar::CalcPosDist(float *pFirstPoint,float *pSecPoint)
{
    float ret;
	ret = (pFirstPoint[0] - pSecPoint[0])*(pFirstPoint[0] - pSecPoint[0]) + (pFirstPoint[1] - pSecPoint[1])*(pFirstPoint[1] - pSecPoint[1]);
	return ret;

}
float g_plot_size[2];
unsigned char SVNodeSonar::CheckParkinglotSizewithType(sonar_parking_lot_t *pParklotData)
{
	unsigned char ret = PARKING_LOT_NOT_SIUTABLE;
	if(pParklotData->lot_length>=FINAL_PARKING_LOT_PARALLEL_LENGTH)
	{
	    if(pParklotData->lot_width>=FINAL_PARKING_LOT_PARALLEL_WIDTH)
	    {
	        pParklotData->parking_lot_type = PARKING_LOT_PARALLEL;
	    }
		else
		{
		    if(pParklotData->lot_width>= MIN_VEHICLE_WIDTH)
		    {
				pParklotData->parking_lot_type = PARKING_LOT_PARALLEL;
		        if(pParklotData->lot_start_pos[1] <0)
		        {
		            pParklotData->lot_start_pos[1] = pParklotData->lot_end_pos[1]-pParklotData->lot_width+FINAL_PARKING_LOT_PARALLEL_WIDTH;
					pParklotData->lot_end_pos[1] = pParklotData->lot_start_pos[1] ; 
		        }
				else
				{
				
				    pParklotData->lot_start_pos[1] = pParklotData->lot_end_pos[1]+pParklotData->lot_width-FINAL_PARKING_LOT_PARALLEL_WIDTH;
					pParklotData->lot_end_pos[1] = pParklotData->lot_start_pos[1] ; 
					
				}
				
				pParklotData->lot_width = FINAL_PARKING_LOT_PARALLEL_WIDTH;
				pParklotData->parking_lot_type = PARKING_LOT_PARALLEL;
		    }
            else
            {
	            pParklotData->parking_lot_type = PARKING_LOT_NOT_SIUTABLE;	  
            }
		}
	}
	else if(pParklotData->lot_length>=FINAL_PARKING_LOT_VERTICAL_WIDTH)
	{
	    if(pParklotData->lot_width>=FINAL_PARKING_LOT_VERTICAL_LEGNTH)
	    {
	        pParklotData->parking_lot_type = PARKING_LOT_VERTICAL;
	    }
		else
		{

	        pParklotData->parking_lot_type = PARKING_LOT_NOT_SIUTABLE;	    
		}    
    
	}
	else
	{
		pParklotData->parking_lot_type = PARKING_LOT_NOT_SIUTABLE;		    
	}
	g_plot_size[0]=pParklotData->lot_width;
	g_plot_size[1]=pParklotData->lot_length;
	
	return ret;


}

unsigned char SVNodeSonar::JudgeObjLine(int filter_num,int sonar_index,int *obj_id,int park_lot_index,int empty_flag)
{

    unsigned char point_type=0;
    //static unsigned char pre_line_type[MAX_PARKING_LOT_NUM]={0,};
	static unsigned char obstacle_appeared_flag[MAX_PARKING_LOT_NUM] = { 0, };
	static unsigned char slot_ok_cnt[MAX_PARKING_LOT_NUM]={0,};
	static float enter_top_bottom_dist[MAX_PARKING_LOT_NUM] = {0,};
	static unsigned char pre_point_type[MAX_PARKING_LOT_NUM]={0,};
	static unsigned char uc_no_top_bottom_turn_flag [MAX_PARKING_LOT_NUM]= {0,};
	static unsigned char uc_top_no_bottom_last_empty_flag[MAX_PARKING_LOT_NUM] ={0,};
	static unsigned char line_flag[MAX_PARKING_LOT_NUM]={0,};
	static float first_enter_state_dist[MAX_PARKING_LOT_NUM]={0,};
	unsigned char line_type;
	unsigned char edge_type;
	void *pSetData;
	float slop=1.0;
	float fdata;
	int idata;
	if(empty_flag == 1)
	{
	     point_type = NO_POINT;
		 
		 *obj_id = MAX_SONAR_OBJ_NUM+1;
	}
	else if(m_new_obj_flag[sonar_index]==1)
	{
	    point_type = JudgeJumpPoint(filter_num,sonar_index,obj_id,&slop);
	}
	else
	{
		point_type = JUMP_POINT_IGNORE;
		*obj_id =(m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;
	}

    if(point_type != NO_POINT&&pre_point_type[park_lot_index] == NO_POINT)
    {
	    point_type = JUMP_POINT_IGNORE;
    }

	if(JUMP_POINT_IGNORE != point_type)
	{
	    if(pre_line_type[park_lot_index] == EDGE_TYPE_NO_TOP_BOTTOM)
    	{
    	    slot_ok_cnt[park_lot_index]=0;
            switch(point_type)
            {
    			case JUMP_POINT_TOP_EDGE:
    			    idata = *obj_id;
					obstacle_appeared_flag[park_lot_index] = 1; 
    			    SetParkSlotInfo(park_lot_index,park_lot_top_before_turn_id,(void *)&idata);	
					fdata = m_sonar_obj_list[sonar_index][2 * (*obj_id ) + 1];
					if(fabs(fdata)<m_slot_data[park_lot_index].dist_cross)
					{
					    SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
					}
					line_type = EDGE_TYPE_TOP_TURN;	
					
    			break;
    			case JUMP_POINT_BOTTOM_EDGE:
					obstacle_appeared_flag[park_lot_index] = 1;
    			    idata = *obj_id;
    			   fdata = m_sonar_obj_list[sonar_index][2*((*obj_id+1)%MAX_SONAR_OBJ_NUM)+1];			   
    			   SetParkSlotInfo(park_lot_index,park_lot_dist_width,(void *)&fdata);	
    			   if(fdata>0)
    			   {
    			       fdata =fdata-DEFAULT_PARALLEL_LOT_WIDTH-100;//  m_sonar_obj_list[sonar_index][2*(*obj_id+1)+1];
    			   }
    			   else
    			   {
    			       fdata =fdata+DEFAULT_PARALLEL_LOT_WIDTH-100;
    			   }
    			   SetParkSlotInfo(park_lot_index,park_lot_dist_cross,(void *)&fdata);	
    			   SetParkSlotInfo(park_lot_index,park_lot_bottom_before_turn_id,(void *)&idata);		
				   idata = MAX_SONAR_OBJ_NUM+1;
				   SetParkSlotInfo(park_lot_index,park_lot_top_before_turn_id,(void *)&idata);
				   SetParkSlotInfo(park_lot_index,park_lot_top_after_turn_id,(void *)&idata);
				   uc_no_top_bottom_turn_flag[sonar_index] = 1;
    			   line_type = EDGE_TYPE_BOTTOM_TURN;
    			break;
    			case JUMP_POINT_NON:
					obstacle_appeared_flag[park_lot_index] = 1;
					fdata = m_sonar_obj_list[sonar_index][2 * (*obj_id+1 ) + 1];					
					SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
    			   line_type = EDGE_TYPE_NO_TOP_BOTTOM;
    			break;
    			case NO_POINT:
					if (obstacle_appeared_flag[park_lot_index] == 1)
					{
    			   idata = (m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;			   
    			   SetParkSlotInfo(park_lot_index,park_lot_top_before_turn_id,(void *)&idata);	
				   fdata = m_sonar_obj_list[sonar_index][2 * (idata)+1];
				   SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
				   fdata = EMPTY_POINT_DEFAULT_DIST;
				   SetParkSlotInfo(park_lot_index, park_lot_dist_width, (void *)&fdata);
    			   line_type = EDGE_TYPE_TOP_NO_BOTTOM;			   
					}
					else
					{                      
						line_type = EDGE_TYPE_NO_TOP_BOTTOM;
					}
    			break;
            }
    	}
     	else if(pre_line_type[park_lot_index] == EDGE_TYPE_TOP_TURN)
    	{
            switch(point_type)
            {
    			case JUMP_POINT_TOP_EDGE:
    			    line_type = EDGE_TYPE_TOP_TURN;			   
    			break;
    			case JUMP_POINT_BOTTOM_EDGE:
    			case JUMP_POINT_NON:
    				//judge_width
    			   idata = ((*obj_id+1)%MAX_SONAR_OBJ_NUM);
    			   fdata = m_sonar_obj_list[sonar_index][2*((*obj_id+1)%MAX_SONAR_OBJ_NUM)+1];
    			   if(fabs(fdata)-fabs(m_slot_data[park_lot_index].dist_cross)>DEFAULT_PARALLEL_LOT_WIDTH)
    			   {
    				   SetParkSlotInfo(park_lot_index,park_lot_top_after_turn_id,(void *)&idata);			   
    				   SetParkSlotInfo(park_lot_index,park_lot_dist_width,(void *)&fdata);		
    				   
    				   line_type = EDGE_TYPE_TOP_NO_BOTTOM;			  
    			   }
    			   else
    			   {
    			       if(fabs(fdata)<fabs(m_slot_data[park_lot_index].dist_cross)
					   	&& (*obj_id != MAX_SONAR_OBJ_NUM+1)) 
    				       SetParkSlotInfo(park_lot_index,park_lot_dist_cross,(void *)&fdata);	
    				   line_type = EDGE_TYPE_NO_TOP_BOTTOM;	
    			   }
    
    			break;
    			case NO_POINT:
    			   idata = (m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;			   
    			   SetParkSlotInfo(park_lot_index,park_lot_top_after_turn_id,(void *)&idata);			   
    			   line_type = EDGE_TYPE_TOP_NO_BOTTOM;			   
    			break;			
            }
    	}   
     	else if(pre_line_type[park_lot_index] == EDGE_TYPE_TOP_NO_BOTTOM)
    	{
			uc_no_top_bottom_turn_flag[sonar_index] = 0;
            switch(point_type)
    		{
    			case JUMP_POINT_NON:
    				idata = (*obj_id+1)%MAX_SONAR_OBJ_NUM;
    				fdata = m_sonar_obj_list[sonar_index][2*idata+1];
					if (uc_top_no_bottom_last_empty_flag[sonar_index] == 1 && fabs(fabs(fdata) - fabs(m_slot_data[park_lot_index].dist_cross)) <1500)
					{
						if (AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist() - first_enter_state_dist[park_lot_index] >= FINAL_PARKING_LOT_VERTICAL_WIDTH)
					    {
						    SetParkSlotInfo(park_lot_index, park_lot_bottom_after_turn_id, (void *)&idata);
						    line_type = EDGE_TYPE_TOP_BOTTOM;
					    }
						else
						{
						    line_type = EDGE_TYPE_NO_TOP_BOTTOM;
						}
					}
					else
					{
        				if(fabs(fdata)<fabs(m_slot_data[park_lot_index].dist_width))
        				{
        					SetParkSlotInfo(park_lot_index,park_lot_dist_width,(void *)&fdata); 	 
        				}			
        			    line_type = EDGE_TYPE_TOP_NO_BOTTOM;
					}


					uc_top_no_bottom_last_empty_flag[sonar_index] = 0;
    			break;	
    			case JUMP_POINT_TOP_EDGE:
    			case NO_POINT:
    				fdata = fabs(m_slot_data[park_lot_index].dist_cross )+ DEFAULT_PARALLEL_LOT_WIDTH + 100;
    			    line_type = EDGE_TYPE_TOP_NO_BOTTOM;	
					uc_top_no_bottom_last_empty_flag[sonar_index] = 1;
    			break;
    			case JUMP_POINT_BOTTOM_EDGE:
    				//judge_width
    			   idata = *obj_id;
				   uc_top_no_bottom_last_empty_flag[sonar_index] = 0;
    				fdata = m_sonar_obj_list[sonar_index][2*((*obj_id+1)%MAX_SONAR_OBJ_NUM)+1];
    			   SetParkSlotInfo(park_lot_index,park_lot_bottom_before_turn_id,(void *)&idata);			   
                   line_type = EDGE_TYPE_BOTTOM_TURN;
    			break;
            }	
            if(line_type == EDGE_TYPE_TOP_BOTTOM)
            {
                if(AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist()-first_enter_state_dist[park_lot_index]<FINAL_PARKING_LOT_PARALLEL_WIDTH)
                {
					line_type = EDGE_TYPE_NO_TOP_BOTTOM; 
                    
                }
            }
            
    	}  	
     	else if(pre_line_type[park_lot_index] == EDGE_TYPE_BOTTOM_TURN)
    	{
            switch(point_type)
    		{
    			case JUMP_POINT_NON:
    			case JUMP_POINT_TOP_EDGE:
    				 //judge_width
    				idata = (*obj_id+1)%MAX_SONAR_OBJ_NUM;
    				fdata = m_sonar_obj_list[sonar_index][2*idata+1];
					if (uc_no_top_bottom_turn_flag[sonar_index] == 0)
					{
						if (fabs(fdata) - fabs(m_slot_data[park_lot_index].dist_cross) >= DEFAULT_PARALLEL_LOT_WIDTH)
						{
							if (fabs(fdata) < fabs(m_slot_data[park_lot_index].dist_width))
							{
								SetParkSlotInfo(park_lot_index, park_lot_dist_width, (void *)&fdata);
							}
							idata = MAX_SONAR_OBJ_NUM+1;
							
							SetParkSlotInfo(park_lot_index,park_lot_bottom_before_turn_id,(void *)&idata);									
							line_type = EDGE_TYPE_TOP_NO_BOTTOM;
						}
						else
						{
							SetParkSlotInfo(park_lot_index, park_lot_bottom_after_turn_id, (void *)&idata);
							if(fabs(m_sonar_obj_list[sonar_index][2*(*obj_id)])<fabs(m_slot_data[park_lot_index].dist_cross)
								&& (*obj_id != MAX_SONAR_OBJ_NUM+1))
							{
								fdata = m_sonar_obj_list[sonar_index][2*(*obj_id)];							    
								SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
							}
							line_type = EDGE_TYPE_TOP_BOTTOM;
						}
					}
					else
					{
						if (-fabs(fdata) + fabs(m_slot_data[park_lot_index].dist_width) < DEFAULT_PARALLEL_LOT_WIDTH)
						{
							if (fabs(fdata) < fabs(m_slot_data[park_lot_index].dist_width))
							{
								SetParkSlotInfo(park_lot_index, park_lot_dist_width, (void *)&fdata);
							}
							line_type = EDGE_TYPE_NO_TOP_BOTTOM;
						}
						else
						{
							SetParkSlotInfo(park_lot_index, park_lot_bottom_after_turn_id, (void *)&idata);
							if(fabs(m_sonar_obj_list[sonar_index][2*(*obj_id)])<fabs(m_slot_data[park_lot_index].dist_cross)
								&& (*obj_id != MAX_SONAR_OBJ_NUM+1))
							{
								fdata = m_sonar_obj_list[sonar_index][2*(*obj_id)];							    
								SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
							}
							line_type = EDGE_TYPE_TOP_BOTTOM;
						}
					}  
    				
    			break;	
    			case NO_POINT:
    				idata = (m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;
    				fdata = m_sonar_obj_list[sonar_index][2*((*obj_id+1)%MAX_SONAR_OBJ_NUM)+1];
    				if(fabs(fdata)-fabs(m_slot_data[park_lot_index].dist_cross)>=DEFAULT_PARALLEL_LOT_WIDTH)
    				{
    					if(fabs(fdata)<fabs(m_slot_data[park_lot_index].dist_width))
    					{
    					    SetParkSlotInfo(park_lot_index,park_lot_dist_width,(void *)&fdata); 	 
    					}
    					line_type = EDGE_TYPE_TOP_NO_BOTTOM;			   
    				}
    				else
    				{
    					SetParkSlotInfo(park_lot_index,park_lot_bottom_after_turn_id,(void *)&idata);								    
    					line_type = EDGE_TYPE_TOP_BOTTOM; 
    				}
    	   
    			break;
    			case JUMP_POINT_BOTTOM_EDGE:
                   line_type = EDGE_TYPE_BOTTOM_TURN;
    			break;
            }	
            if(line_type == EDGE_TYPE_TOP_BOTTOM)
            {
                if(AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist()-first_enter_state_dist[park_lot_index]<FINAL_PARKING_LOT_PARALLEL_WIDTH)
                {
					line_type = EDGE_TYPE_NO_TOP_BOTTOM; 
                    
                }
            }
    	} 
    	else
    	{
    	    if(fabs(slop) < 0.1)
    	    {
    	        
    			slot_ok_cnt[park_lot_index]++;
				if(slot_ok_cnt[park_lot_index]>=3)
				{
    	            line_flag[park_lot_index] = 1;
				}
    	    }
			else
			{

			    slot_ok_cnt[park_lot_index]=0;
			}
			if(line_flag[park_lot_index] ==1)
			{
               // if(slot_ok_cnt[park_lot_index] == 0)
                //{
                  //  enter_top_bottom_dist[park_lot_index] = AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist();
                
                //}
			}
			else
			{
			     //slot_ok_cnt[park_lot_index]=0;
				 enter_top_bottom_dist[park_lot_index] = AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist();

			}
			
			if(fabs(m_sonar_obj_list[sonar_index][2*(((*obj_id-1)+1)%MAX_SONAR_OBJ_NUM)+1])<fabs(m_slot_data[park_lot_index].dist_cross)
				&& (*obj_id != MAX_SONAR_OBJ_NUM+1))
			{
				fdata = m_sonar_obj_list[sonar_index][2 * (*obj_id - 1) + 1];
				SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
			}

    		if(AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist()-enter_top_bottom_dist[park_lot_index]>700)
    		{
    		    line_type = EDGE_TYPE_NO_TOP_BOTTOM;
    		}	
    		else
    		{
    		    
    		    line_type = pre_line_type[park_lot_index] ;
    		}	
    	}
	}
	else
    {
    		    
        line_type = pre_line_type[park_lot_index] ;

	    if(line_type == EDGE_TYPE_TOP_BOTTOM)
	    {
		    if(line_flag [park_lot_index]==1)
			{
    		    //slot_ok_cnt[park_lot_index]++;

		
    		
        		if(AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist()-enter_top_bottom_dist[park_lot_index]>1000)
    		{
    			line_type = EDGE_TYPE_NO_TOP_BOTTOM;
    		}	
    		else
    		{
    			
    			line_type = pre_line_type[park_lot_index] ;
    		}	
	
		    }
	    }

    }		
	edge_type = JUMP_POINT_NON;
	 

    if(pre_line_type[park_lot_index] != EDGE_TYPE_TOP_BOTTOM&&(line_type == EDGE_TYPE_TOP_BOTTOM))
    {
		edge_type = JUMP_POINT_BOTTOM_EDGE;
    }
	else if(pre_line_type[park_lot_index] != EDGE_TYPE_TOP_NO_BOTTOM&&(line_type == EDGE_TYPE_TOP_NO_BOTTOM))
	{       
        edge_type = JUMP_POINT_TOP_EDGE;
	}
	else if(pre_line_type[park_lot_index] != EDGE_TYPE_NO_TOP_BOTTOM&&(line_type == EDGE_TYPE_NO_TOP_BOTTOM))
	{    
		if (pre_line_type[park_lot_index] == EDGE_TYPE_TOP_BOTTOM)
		{
			ProcessLotData(sonar_index, park_lot_index);
			line_flag[park_lot_index] =0;
		}
		//else
		//AVMData::GetInstance()->m_p_can_data->ResetDriveDist();  	
		idata=MAX_SONAR_OBJ_NUM+1;
		
		SetParkSlotInfo(park_lot_index,park_lot_bottom_after_turn_id,(void *)&idata);									
		SetParkSlotInfo(park_lot_index,park_lot_bottom_before_turn_id,(void *)&idata);									
		SetParkSlotInfo(park_lot_index,park_lot_top_before_turn_id,(void *)&idata);									
		SetParkSlotInfo(park_lot_index,park_lot_top_after_turn_id,(void *)&idata);	
		idata = (m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;
		obstacle_appeared_flag[park_lot_index] = 0;
		
		if (*obj_id >= MAX_SONAR_OBJ_NUM || *obj_id <0)
		{
			fdata = EMPTY_POINT_DEFAULT_DIST;
		}
		else
		{
			fdata = m_sonar_obj_list[sonar_index][2 * (*obj_id) + 1];
		}
		SetParkSlotInfo(park_lot_index,park_lot_dist_width,(void *)&fdata); 	 
		SetParkSlotInfo(park_lot_index,park_lot_dist_cross,(void *)&fdata); 	 
		
	}
    else if(line_type == EDGE_TYPE_NO_TOP_BOTTOM&&pre_line_type[park_lot_index]!= EDGE_TYPE_NO_TOP_BOTTOM)
    {

    }

	if(line_type==EDGE_TYPE_TOP_NO_BOTTOM&&pre_line_type[park_lot_index]<EDGE_TYPE_TOP_NO_BOTTOM)
	{
		first_enter_state_dist[park_lot_index] = AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist();
	}
	pre_line_type[park_lot_index]=line_type;
	pre_point_type[park_lot_index]=point_type;

    return edge_type;
}


void SVNodeSonar::ResetParkSlotInfo(void)
{   
    float fdata;
	int idata;
	int park_lot_index;
    AVMData::GetInstance()->m_p_can_data->ResetDriveDist(); 	
    idata=MAX_SONAR_OBJ_NUM+1;
	for (park_lot_index = 0; park_lot_index < MAX_PARKING_LOT_NUM; park_lot_index++)
	{
	    if(park_lot_index == front_left_conor_sonar)
	    {
	        continue;
	    }
		SetParkSlotInfo(park_lot_index, park_lot_bottom_after_turn_id, (void *)&idata);
		SetParkSlotInfo(park_lot_index, park_lot_bottom_before_turn_id, (void *)&idata);
		SetParkSlotInfo(park_lot_index, park_lot_top_before_turn_id, (void *)&idata);
		SetParkSlotInfo(park_lot_index, park_lot_top_after_turn_id, (void *)&idata);

		m_sonar_parking_lot[park_lot_index].show_flag=0;
		m_sonar_parking_lot[park_lot_index].parking_lot_type = PARKING_LOT_NOT_SIUTABLE;

        pre_line_type[park_lot_index]= EDGE_TYPE_NO_TOP_BOTTOM;
		fdata = EMPTY_POINT_DEFAULT_DIST;
		m_sonar_obj_list_end[park_lot_index]=0;
		m_sonar_obj_list_start[park_lot_index]=0;
		SetParkSlotInfo(park_lot_index, park_lot_dist_width, (void *)&fdata);
		SetParkSlotInfo(park_lot_index, park_lot_dist_cross, (void *)&fdata);
		m_sonar_parking_lot[park_lot_index].show_flag = 0;
	}
}
void SVNodeSonar::SetParkSlotInfo(int park_lot_index,park_lot_property property_index,void *pData)
{
    int *pIntValue;
	float *pfloatValue;
	
    switch (property_index)
    {
        case park_lot_dist_cross:
			m_slot_data[park_lot_index].dist_cross=*((float *)pData);
        break;
        case park_lot_dist_width:			
			m_slot_data[park_lot_index].dist_width=*((float *)pData);
        break;				
        case park_lot_dist_cross_avg:
			m_slot_data[park_lot_index].dist_cross=(*((float *)pData)+m_slot_data[park_lot_index].dist_cross)/2.0;
        break;
        case park_lot_dist_width_avg:			
			m_slot_data[park_lot_index].dist_width=(*((float *)pData)+m_slot_data[park_lot_index].dist_width)/2.0;
        break;		
        case park_lot_top_before_turn_id:
			m_slot_data[park_lot_index].top_edge_index=*((int *)pData);
        break;
        case park_lot_top_after_turn_id:			
			m_slot_data[park_lot_index].top_edge_after_turn_index=*((int *)pData);
        break;
        case park_lot_bottom_before_turn_id:			
			m_slot_data[park_lot_index].bottom_edge_index=*((int *)pData);
        break;
        case park_lot_bottom_after_turn_id:			
			m_slot_data[park_lot_index].bottom_edge_after_turn_index=*((int *)pData);
        break;
        case park_lot_width:			
			m_slot_data[park_lot_index].park_lot_width=*((float *)pData);
        break;
        case park_lot_length:			
			m_slot_data[park_lot_index].park_lot_length=*((float *)pData);
        break;

    }

}

void SVNodeSonar::ProcessSearchingSlot(int filter_time,float *dist,int sonar_index)
{
    unsigned char jump_point_type,park_lot_flag;
	int point_index;
	static int empty_path_cnt[2]={0,0};	
	static int non_empty_path_cnt[2]={0,0};
	static unsigned char empty_path_flag[2]={0,0};
	static float pre_distance[2]={0,0};
	
	static unsigned char pre_empty_path_flag[2]={0,0}; 
	int internal_index;
	if(sonar_index == front_left_side_sonar)
	{
	    internal_index=0;
	}
	else
	{
		internal_index = 1;
	}
	//FiltObjData(filter_time);
	AVMData::GetInstance()->m_p_can_data->CalcDriveDist();

	//StMc_Event_Dispatch(USPLD_SIG_SEARCH_START);
	//to see if there is a part with no object at all
	if (dist[sonar_index] == INVALID_OBJ_DIST)
	{
        empty_path_cnt[internal_index]++;
		non_empty_path_cnt[internal_index]=0;

	}
	else
	{
	    empty_path_cnt[internal_index]=0;		
		non_empty_path_cnt[internal_index]++;
		if(non_empty_path_cnt[internal_index]>=EMPTY_PATH_CNT_THRESHOLD/2)
		{
		    empty_path_flag[internal_index]=0;
		}

		pre_distance[internal_index]=AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist();
	}
    float distance = AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist()-pre_distance[internal_index];
	if(distance > EMPTY_PATH_DIST_THERESHOLD)
	{
		empty_path_flag[internal_index]=1;	
	}
	
	if(empty_path_cnt[internal_index]>=EMPTY_PATH_CNT_THRESHOLD)
	{
	    empty_path_flag[internal_index]=1;
	}
	
	jump_point_type = JudgeObjLine(filter_time, sonar_index, &point_index, sonar_index, empty_path_flag[internal_index]);

	
   pre_empty_path_flag[0]=empty_path_flag[0];
   pre_empty_path_flag[1]=empty_path_flag[1];
}
void SVNodeSonar::ProcessLotData(int sonar_index,int park_lot_index)
{
    float start_pos_x,end_pos_x;


    if(m_slot_data[park_lot_index].bottom_edge_index>MAX_SONAR_OBJ_NUM+1
		||m_slot_data[park_lot_index].bottom_edge_index<0
		||m_slot_data[park_lot_index].top_edge_index<0
		||m_slot_data[park_lot_index].top_edge_index>MAX_SONAR_OBJ_NUM+1)
    {
        return;
    }

	if(m_slot_data[park_lot_index].bottom_edge_index == MAX_SONAR_OBJ_NUM+1)
	{
		end_pos_x = m_sonar_obj_list[sonar_index][2 * m_slot_data[park_lot_index].bottom_edge_after_turn_index];
	}
	else
	{
		end_pos_x = m_sonar_obj_list[sonar_index][2 * m_slot_data[park_lot_index].bottom_edge_index];
	}

	if(m_slot_data[park_lot_index].top_edge_after_turn_index == MAX_SONAR_OBJ_NUM+1)
	{
		start_pos_x = m_sonar_obj_list[sonar_index][2 * m_slot_data[park_lot_index].top_edge_index];
	}
	else if(m_slot_data[park_lot_index].top_edge_index != MAX_SONAR_OBJ_NUM+1)
	{
		start_pos_x = m_sonar_obj_list[sonar_index][2 * m_slot_data[park_lot_index].top_edge_after_turn_index];
	}
	else
	{
		start_pos_x = end_pos_x-AVMData::GetInstance()->m_p_can_data->Get_Drive_Dist();    
	}	
	
	//normal parking lot
	m_sonar_parking_lot[park_lot_index].lot_start_pos[0] = start_pos_x;
	m_sonar_parking_lot[park_lot_index].lot_end_pos[0] = end_pos_x;
	m_sonar_parking_lot[park_lot_index].lot_start_pos[1] = m_slot_data[park_lot_index].dist_cross;
	m_sonar_parking_lot[park_lot_index].lot_end_pos[1] = m_slot_data[park_lot_index].dist_cross;
	m_sonar_parking_lot[park_lot_index].lot_width = fabs(m_slot_data[park_lot_index].dist_width)-fabs(m_slot_data[park_lot_index].dist_cross);
	m_sonar_parking_lot[park_lot_index].lot_length = m_sonar_parking_lot[park_lot_index].lot_end_pos[0]-m_sonar_parking_lot[park_lot_index].lot_start_pos[0];

	
  

    m_sonar_parking_lot[park_lot_index].show_flag=1;

    CheckParkinglotSizewithType(&m_sonar_parking_lot[park_lot_index]);
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_top]=m_sonar_parking_lot[park_lot_index].lot_end_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_bottom]=m_sonar_parking_lot[park_lot_index].lot_start_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_near_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_start_pos[1] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top]=m_sonar_parking_lot[park_lot_index].lot_end_pos[0] ;
	m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom]=m_sonar_parking_lot[park_lot_index].lot_start_pos[0] ;

	if(m_sonar_parking_lot[park_lot_index].lot_end_pos[1]>0)
	{
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]+m_sonar_parking_lot[park_lot_index].lot_width ;
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]+m_sonar_parking_lot[park_lot_index].lot_width ;

	}
	else
	{
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_top+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]-m_sonar_parking_lot[park_lot_index].lot_width ;
	    m_sonar_parking_lot[park_lot_index].lot_point[2*rect_point_far_bottom+1]=m_sonar_parking_lot[park_lot_index].lot_end_pos[1]-m_sonar_parking_lot[park_lot_index].lot_width ;
	   
	}

}



void SVNodeSonar::FiltObjData(int filter_num)
{
    int sonar_index=front_right_side_sonar;
	int obj_index=0;
	int sonar_loop=0;
	int start_index, end_index, obj_num, current_index;
	float sum_x,sum_y=0;

	for(sonar_loop=0;sonar_loop<2;sonar_loop++)
	{
        if(sonar_loop == LEFT_SONAR_MEAN_OBJ_INDEX)
        {
            sonar_index = front_left_side_sonar;
        }
         
        start_index = m_sonar_obj_list_start[sonar_index];
		end_index = m_sonar_obj_list_end[sonar_index];
		if(start_index>=end_index)
		{
    		obj_num = end_index-start_index+MAX_SONAR_OBJ_NUM;
		}
		else
		{
            obj_num = end_index-start_index;
		}
		for(obj_index=0;obj_index<obj_num;obj_index++)
		{
		    sum_x=0;sum_y=0;
			current_index = start_index + obj_index;
            for(int i=-filter_num;i<filter_num+1;i++)
            {
				if (current_index + filter_num<start_index)
                {
					current_index = start_index - filter_num;
                }
				else if ((current_index + filter_num) % MAX_SONAR_OBJ_NUM>=end_index)
				{
					current_index = end_index + MAX_SONAR_OBJ_NUM - filter_num;
				}
				sum_x += m_sonar_obj_list[sonar_index][2 * ((current_index + filter_num) % MAX_SONAR_OBJ_NUM)];
				sum_y += m_sonar_obj_list[sonar_index][2 * ((current_index + filter_num) % MAX_SONAR_OBJ_NUM) + 1];
            }   

			m_sonar_filter_obj_list[sonar_loop][2 * ((current_index) % MAX_SONAR_OBJ_NUM)] = sum_x / (float)(2 * (float)filter_num + 1.0);
			m_sonar_filter_obj_list[sonar_loop][2 * ((current_index) % MAX_SONAR_OBJ_NUM) + 1] = sum_y / (float)(2 * (float)filter_num + 1.0);
		
		}

	}

}
float g_debug_slop=0;
extern int g_debug_index;
unsigned char  SVNodeSonar::JudgeJumpPoint(int filter_num,int sonar_index,int *obj_id,float *slop)
{
    int sonar_loop = front_right_side_sonar;
	int obj_index=0;
	static int last_obj_index = 0;

	int start_index, end_index, obj_num, current_index;
	float sum_x,sum_y=0;
    float current_point[2];
	float last_point[2];
    float k_slop,delta_width;
	unsigned char point_type = JUMP_POINT_IGNORE;
    if(sonar_index == front_left_side_sonar)
    {
		sonar_loop = front_left_side_sonar;
    }


	obj_index=(m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-filter_num-1)%MAX_SONAR_OBJ_NUM;
	obj_index=(m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-2)%MAX_SONAR_OBJ_NUM;
	if(m_sonar_obj_list_end[sonar_index]-m_sonar_obj_list_start[sonar_index]<2*filter_num+1
		&&m_sonar_obj_list_end[sonar_index]-m_sonar_obj_list_start[sonar_index]>0)
	{
	   //point not enough
	   *obj_id=m_sonar_obj_list_end[sonar_index]-2;
	   if(slop != NULL)
	   {
	       slop =0;

	   }
	   return point_type;
	}
	point_type = JUMP_POINT_NON;

	current_point[0]=m_sonar_obj_list[sonar_loop][2 * (obj_index+1)];
	current_point[1]=m_sonar_obj_list[sonar_loop][2 * (obj_index+1)+1];
	last_point[0]=m_sonar_obj_list[sonar_loop][2 * (obj_index)];
	last_point[1]=m_sonar_obj_list[sonar_loop][2 * (obj_index)+1];	

	if((fabs(current_point[1]-last_point[1])>JUMP_POINT_DIST_GATE||fabs(current_point[0]-last_point[0])>JUMP_POINT_DIST_GATE)
		&&(obj_index!=last_obj_index))
	{
    	k_slop=(fabs(current_point[1])-fabs(last_point[1]))/(current_point[0]-last_point[0]);
		g_debug_slop = k_slop;
		g_debug_index=g_debug_index;
        if(k_slop<-K_SLOP_GATE)
        {
            point_type = JUMP_POINT_BOTTOM_EDGE;
        }
    	else if(k_slop>K_SLOP_GATE)
    	{
            point_type = JUMP_POINT_TOP_EDGE;	
    	}
	}
	if(slop != NULL)
	{
	    if(current_point[0]-last_point[0]!=0)
	    {
	        *slop = (fabs(current_point[1])-fabs(last_point[1]))/(current_point[0]-last_point[0]);
	    }
		else
		{
		    *slop = 1000;
    	}
	}
   *obj_id=obj_index;
   last_obj_index=obj_index;
	return point_type;
    
	
}
int SVNodeSonar::FilterDistData(float *pNewPoint,int sonar_index)
{
    static int stable_cnt[max_sonar_num]={0,0,0,0,0,0,0,0,0,0,0,0};
    float   last_pos[2];
	int new_obj_flag=0;
	int obj_index = (m_sonar_obj_list_end[sonar_index]+MAX_SONAR_OBJ_NUM-1)%MAX_SONAR_OBJ_NUM;
	last_pos[0]=m_sonar_obj_list[sonar_index][2*obj_index];	
	last_pos[1]=m_sonar_obj_list[sonar_index][2*obj_index+1];
   /* if(fabs(last_pos[1]-pNewPoint[1])>FILTER_DIST_THRESHOLD)
	{
		stable_cnt[sonar_index]++;
		if (stable_cnt[sonar_index]>FILTER_CNT_THERESHOLD)
    	{
            m_sonar_obj_list[sonar_index][2*m_sonar_obj_list_end[sonar_index]] = pNewPoint[0];
            m_sonar_obj_list[sonar_index][2*m_sonar_obj_list_end[sonar_index]+1] = pNewPoint[1];
            m_sonar_obj_list_end[sonar_index]++;
			stable_cnt[sonar_index] = 0;
    		new_obj_flag=1;
    	}	
    }
	else
	{*/
        m_sonar_obj_list[sonar_index][2*m_sonar_obj_list_end[sonar_index]] = pNewPoint[0];
        m_sonar_obj_list[sonar_index][2*m_sonar_obj_list_end[sonar_index]+1] = pNewPoint[1];
        m_sonar_obj_list_end[sonar_index]++;
		stable_cnt[sonar_index] = 0;
		new_obj_flag=1;
	//}


	return new_obj_flag;
}

int SVNodeSonar::UpdateSonarArc(float dist,sonar_index sonar_pos)
{
    Int32 x, y;
	Int32 point_num;
    float s_a,e_a;
	s_a = m_sonar_pos[sonar_pos].angle - SONAR_HALF_FOV;
	e_a = m_sonar_pos[sonar_pos].angle + SONAR_HALF_FOV;
    int add_num = 0;
    float angle_step = 0;
	float start_angle_rad = s_a/180.0*PI;
	float end_angle_rad = e_a/180.0*PI;
	float *PlaneVBO;
	float WorldPos[3];
	float model_coord[3];

    point_num = m_sonar_arc_data[sonar_pos].element_num-1;
	
    angle_step = (end_angle_rad-start_angle_rad)/(float)(point_num-1);
	
	PlaneVBO=m_sonar_arc_data[sonar_pos].pdatabuffer;
	
	


	Int32 slotId=0;
	
	AVMData::GetInstance()->cvtWorldPoint2Stich2DPoint(model_coord,m_sonar_pos[sonar_pos].pos,1);
	//circle center point
	PlaneVBO[slotId+0] = model_coord[0];
	PlaneVBO[slotId+1] = model_coord[1];
	PlaneVBO[slotId+2] = model_coord[2];
	
	
	slotId+=8;
    
	
	for(x=0;x<point_num;x++)
    {

		WorldPos[0] = m_sonar_pos[sonar_pos].pos[0]+dist*sin(start_angle_rad);
		WorldPos[1] = m_sonar_pos[sonar_pos].pos[1]+dist*cos(start_angle_rad);
		WorldPos[2] = m_sonar_pos[sonar_pos].pos[2];
		
		AVMData::GetInstance()->cvtWorldPoint2Stich2DPoint(model_coord, WorldPos, 1);

		
		PlaneVBO[slotId+0] =model_coord[0];
		PlaneVBO[slotId+1] =model_coord[1];
		PlaneVBO[slotId+2] = model_coord[2]-0.1;

		slotId+=8;
		start_angle_rad+=angle_step;
		if(start_angle_rad>end_angle_rad)
		{
		    start_angle_rad = end_angle_rad;
		}
	}

	slotId = 0;


	return XR_OK;



}
int  SVNodeSonar::Update(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed,float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate,float *obj_dist)
{
    static unsigned int cnt = 0;
    float pTemp[8]={0.2,0.2,0.8,0.2,0.2,1.0,0.8,1.0};
	unsigned char update_key_flag=0;
	static unsigned char update_key_frame_sures = 0;
	static COMMON_VEHICLE_DATA_SIMPLE vehicle_state;
    float new_obj_pos[3];
	unsigned char parking_lot_type;
	static unsigned int testcnt=0;
	static unsigned char pre_track_flag=0;
	vehicle_state.steering_angle =steering_wheel_angle;
	vehicle_state.vehicle_speed = vehicle_speed;
	vehicle_state.wheel_speed_fl = left_wheel_speed;
	vehicle_state.wheel_speed_rl = left_wheel_speed;
	vehicle_state.wheel_speed_fr = right_wheel_speed;
	vehicle_state.wheel_speed_rr = right_wheel_speed;
	vehicle_state.shift_pos = gear_state;
	vehicle_state.yaw_rate = yaw_rate;
	
	int new_store_obj_flag[max_sonar_num] = { 0,};
	static unsigned char pre_turn_light_state=TURN_LIGHT_OFF;
    unsigned char turn_light_state;
	AVMData::GetInstance()->m_p_can_data->Get_Turn_Signal(&turn_light_state);
	AVMData::GetInstance()->m_p_can_data->Get_Wheel_Pulse(vehicle_state.wheel_pulse);
	if(TURN_LIGHT_LEFT == turn_light_state&&pre_turn_light_state == TURN_LIGHT_OFF)
	{
	    ResetParkSlotInfo();
		
	    m_track_park_lot_flag =0;
		TestVehicleMovment();
	}	
	if(TURN_LIGHT_OFF == turn_light_state&&pre_turn_light_state == TURN_LIGHT_RIGHT)
	{
	    m_track_park_lot_flag =1;
	}
	m_sonar_data[front_left_side_sonar].show_flag = 1;
	m_sonar_data[front_right_side_sonar].show_flag = 1;
	pre_turn_light_state = turn_light_state;
    //m_sonar_data[rear_left_conor_sonar].show_flag = 1;
	//m_sonar_data[rear_right_conor_sonar].show_flag = 1;


	ProcessPreviousParkingLot(vehicle_state);
	for(unsigned char i=0;i<max_sonar_num;i++)
	{
	   m_sonar_data[i].show_flag = 1;
	   m_sonar_arc_data[i].show_flag = 1;
		//obj_dist[i] = 3000.0;
	    if(obj_dist[i] < INVALID_OBJ_DIST-0.1)
	    {
	        CalcSonarObjPos(new_obj_pos,obj_dist[i],(sonar_index)i);
			if(i == front_left_side_sonar || i == front_right_side_sonar)
			{
                if(CalcPosDist(new_obj_pos,&m_sonar_obj_list[i][2*(m_sonar_obj_list_end[i]-1)])>10000)
                {
    				m_new_obj_flag[i] = FilterDistData(new_obj_pos,i);
        				m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i]] = new_obj_pos[0];
        				m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i] + 1] = new_obj_pos[1];
        				m_sonar_draw_obj_list_end[i]++;
        
    
    
        			if(m_sonar_draw_obj_list_end[i]<MAX_SONAR_OBJ_NUM)
        			{
    
        			}
    				else
    				{
    				    m_sonar_draw_obj_list_end[i]=m_sonar_draw_obj_list_end[i]%MAX_SONAR_OBJ_NUM;
    				}
    
                    if(m_sonar_draw_obj_list_end[i]<=m_sonar_draw_obj_list_start[i])
                    {
                        m_sonar_draw_obj_list_start[i]=(m_sonar_draw_obj_list_end[i]+1)%MAX_SONAR_OBJ_NUM;
                    }
    
    
        			if(m_sonar_obj_list_end[i]<MAX_SONAR_OBJ_NUM)
        			{
    
        			}
    				else
    				{
    				    m_sonar_obj_list_end[i]=m_sonar_obj_list_end[i]%MAX_SONAR_OBJ_NUM;
    				}
    
                    if(m_sonar_obj_list_end[i]<=m_sonar_obj_list_start[i])
                    {
                        m_sonar_obj_list_start[i]=(m_sonar_obj_list_end[i]+1)%MAX_SONAR_OBJ_NUM;
                    }
                }	
			}

			if(i != front_left_side_sonar&&i != front_right_side_sonar)
			 {	

				if( CalcMultiSonarObj(new_obj_pos, obj_dist, (sonar_index)i))
				{
				 m_sonar_draw_obj_list_end[i]=0;

				 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i]] = new_obj_pos[0];
				 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i] + 1] = new_obj_pos[1];
				 m_sonar_draw_obj_list_end[i]++;

					 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i]] = new_obj_pos[0];
					 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i] + 1] = new_obj_pos[1];
					 m_sonar_draw_obj_list_end[i]++;

					 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i]] = new_obj_pos[0];
					 m_sonar_draw_obj_list[i][2 * m_sonar_draw_obj_list_end[i] + 1] = new_obj_pos[1];
					 m_sonar_draw_obj_list_end[i]++;


    				if(i== front_left_conor_sonar)
    				{
    					//sprintf(gpu_debug_texbox.text_content[0],"FLC dist(%f),",obj_dist[i]);
    					sprintf(gpu_debug_texbox.text_content[1],"FLC point(%f,%f),",new_obj_pos[0],new_obj_pos[1]);
    					printf("update dist");
    				}
    				
    				if(i== front_left_middle_sonar)
    				{
    					//sprintf(gpu_debug_texbox.text_content[3],"FLM dist(%f),",obj_dist[i]);
    					sprintf(gpu_debug_texbox.text_content[4],"FLM point(%f,%f),",new_obj_pos[0],new_obj_pos[1]);
    				}


				}
				else
				{
				    m_sonar_data[i].show_flag = 0;
				}

			 }
			

	    }
		else
		{
		
		    if(i!= front_left_side_sonar&&i!=front_right_side_sonar)
		    {
				m_sonar_data[i].show_flag = 0;
				m_sonar_arc_data[i].show_flag =0;

		    }
		}
	
	}
	ProcessPreviousPos(vehicle_state);
	//FiltObjData(2);

	if(fabs(steering_wheel_angle)<SEACHING_SLOT_STEERING_GATE)
	{
		if (pre_track_flag == 1 && m_track_park_lot_flag == 0)
		{
			ResetParkSlotInfo();
		}
		
	    if(m_track_park_lot_flag == 0)
	    {
            ProcessSearchingSlot(2,obj_dist,front_left_side_sonar);
	
            ProcessSearchingSlot(2,obj_dist,front_right_side_sonar);
	    }
	}
	else
	{
	    if(m_track_park_lot_flag ==0)
	    {
            ResetParkSlotInfo();
			
	    }
	}
	pre_track_flag = m_track_park_lot_flag;
		
	m_filter_time =2;
	int obj_num;
	
	m_sonar_data[front_right_side_sonar].show_flag = 1;
	
	m_sonar_data[front_left_side_sonar].show_flag = 1;
    for(int j=0;j<max_sonar_num;j++)
    {
		//m_sonar_data[j].show_flag = 1;
        if(m_sonar_data[j].show_flag ==0)
        {
            m_sonar_data[j].pNode->SetEnable(0);
			
        }
		else
		{
		  if(0==UpdateVertexBuffer(m_sonar_data[j].pdatabuffer,j))
		  {
			  m_sonar_data[j].pNode->SetEnable(0);		  
		  }
		  else
		  {
    			  if(m_sonar_draw_obj_list_start[j]<=m_sonar_draw_obj_list_end[j])
    			  {
    				  obj_num = m_sonar_draw_obj_list_end[j]-m_sonar_draw_obj_list_start[j];
    			  }
    			  else
    			  {
    				  obj_num = m_sonar_draw_obj_list_end[j]-m_sonar_draw_obj_list_start[j]+MAX_SONAR_OBJ_NUM;  
    			  }
             
			  m_sonar_data[j].pLineMesh->UpdateVertexNum(obj_num+1);
		  
			  m_sonar_data[j].pNode->SetEnable(1);
              m_sonar_data[j].pLineMesh->UnLockData();		  

		  }

		  	
		}
		if(j!=front_left_side_sonar&&j!=front_right_side_sonar&&m_sonar_arc_data[j].show_flag == 1) 
		{
		   UpdateSonarArc(obj_dist[j],(sonar_index)j);
		
		   m_sonar_arc_data[j].pLineMesh->UpdateVertexNum(m_sonar_arc_data[j].element_num);
		
		   m_sonar_arc_data[j].pNode->SetEnable(1);
		   m_sonar_arc_data[j].pLineMesh->UnLockData(); 
		   
		   if(j== front_left_conor_sonar)
		   {
			   sprintf(gpu_debug_texbox.text_content[0],"FLC dist(%f),",obj_dist[j]);
			   //sprintf(gpu_debug_texbox.text_content[1],"FLC point(%f,%f),",new_obj_pos[0],new_obj_pos[1]);
			   //printf("update dist");
		   }
		   
		   if(j== front_left_middle_sonar)
		   {
			   sprintf(gpu_debug_texbox.text_content[3],"FLM dist(%f),",obj_dist[j]);
			   //sprintf(gpu_debug_texbox.text_content[4],"FLM point(%f,%f),",new_obj_pos[0],new_obj_pos[1]);
		   }


		   
		} 
		else
		{
			m_sonar_arc_data[j].pNode->SetEnable(0);
		}

		
    }
	DrawParkLot();

	SetRadarPLDReslt();
	
    for(int i=0;i<max_sonar_num;i++)
    {
        for(int j=0;j<max_sonar_num;j++)
        {
            m_sonar_overlap_flag[i][j]=0;
        }
    }

	for(int i=0;i<4;i++)
	{
	
	  //  fprintf(stdout,"\r\n wheelpulse[%d]=%d,%d,%d",i,vehicle_state.pre_wheel_pulse[i],vehicle_state.wheel_pulse[i],vehicle_state.wheel_pulse[i]-vehicle_state.pre_wheel_pulse[i]);
	    vehicle_state.pre_wheel_pulse[i]= vehicle_state.wheel_pulse[i];
		
	}
	if(m_track_park_lot_flag ==0 )
	{
	    TestVehicleMovment();
	}
	float delta_wheel=vehicle_state.wheel_pulse[rear_left_whl]-vehicle_state.pre_wheel_pulse[rear_left_whl];
   // fprintf(stdout,"\r\n timeoffset %d",time_offset);
	//fprintf(stdout,"\r\n wheelspeed[lr,rr]=%f,%f",left_wheel_speed,right_wheel_speed);
   // fprintf(stdout,"left_wheel_dist_pulse[%f],dist_speed[%f]",(float)delta_wheel*0.046,left_wheel_speed*time_offset/1000000.0/3.6);
	//fprintf(stdout,"\r\n====================================");

	
	return 0;

}

