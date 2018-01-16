
#include "GlSVOverlayBase.h"
#include <math.h>
#include "camera_model.h"
#include "AVMData.h"



/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/







/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/




GlSVOverlayBase::GlSVOverlayBase()
{

	
}

int GlSVOverlayBase::Init(Overlay_Para pConfig)
{
    m_config = pConfig;
	m_cam_pos = 2;
	
	return 0;
}



unsigned char GlSVOverlayBase::SolveSquareEquation(float *solve,float a ,float b,float c)
{
    float squre_root=0;
	float square=0;
	float cof=0;

	square=b*b-4*a*c;
	if(square<0)
	{
        return 1;
	}
	squre_root=sqrt(square);
	cof = 1/(2*a);

    solve[0] = (0.0-b+squre_root)*cof;
    solve[1] = (0.0-b-squre_root)*cof;
	
    return SOLUTION_AVALIBALE;
}

void GlSVOverlayBase::ConvertGroundToClinder(float *pInputCoord,float *pOutputCoord,float Clyder_radius,float Scale_y,unsigned char Pos)
{
    //x z compose clyinder
    //pos==0 means front ,pos==1 means rear
    float ratio,part;
    float a,b,c,temp;
	float solve[2];
    float pCamPos[3];
	float solve_x[2];
	float solve_y[2];
	int i=0;
    if(Pos ==0)
    {

   	   Cal_World_2_Model_Coordinate_3d(pCamPos,m_config.m_front_cam_pos_wld);
    }
	else
    {
		Cal_World_2_Model_Coordinate_3d(pCamPos,m_config.m_rear_cam_pos_wld);
    }	
	//pCamPos[0]=-48.2107315;
	//pCamPos[1]=-409.5;
	//pCamPos[2]=-747.611145;
	ratio = (pInputCoord[0]-pCamPos[0])/(pInputCoord[2]-pCamPos[2]);
	part=pCamPos[0]-ratio*pCamPos[2];
    temp = ratio*ratio;
	a=temp+4;
	b=2*ratio*part;
	c=part*part-Clyder_radius*Clyder_radius;

	SolveSquareEquation(solve,a,b,c);
	for(i=0;i<2;i++)
	{
		ratio = (pInputCoord[0]-pCamPos[0])/(pInputCoord[2]-pCamPos[2]);
	    c=solve[i];
        solve_x[i]=ratio*c+part; 
    	ratio = (pInputCoord[1]-pCamPos[1])/(pInputCoord[2]-pCamPos[2]);
        solve_y[i]=ratio*c-ratio*pCamPos[2]+pCamPos[1];			
	}

    //select one solution 
    if(solve[0]*solve[1]<0)
    {
        if(Pos == 0)
        {
            i=1;
        }
		else
		{
		    i=0;
		}
    }
	else
	{
        if((pCamPos[1]-pInputCoord[1])*(pInputCoord[1]-solve_y[0])>0)
        {
            i=0;
        }
    	else
    	{
            i=1;
    	}
	}
    
	pOutputCoord[0]=solve_x[i];
	pOutputCoord[1]=solve_y[i];
	pOutputCoord[2]=solve[i];


}

int GlSVOverlayBase::SetUpBuffer(void *pData,unsigned int size,unsigned int element_num,unsigned char CalibMode)
{

    m_pdata = pData;
	m_data_size = size;
	m_element_num = element_num;
    m_calib_mode = CalibMode;
	return 0;
}

int GlSVOverlayBase::GetVertexBuffer(int Index,float **pVertexBuffer, unsigned int *BufSize)
{

	    
     *pVertexBuffer= (float *)m_pdata;


	return 0;
}
int GlSVOverlayBase::GetIndexBuffer(int Index,GLushort **pIndexBuffer, unsigned int *BufSize)
{
   
	return 0;
}




void GlSVOverlayBase::Cal_World_2_Model_Coordinate(float *out_Model_Coord,float *in_world_coord)
{

    float internel_image[2];
    //out_Model_Coord[1] = 0.0-m_config.model_scale*(in_world_coord[1]-((m_config.vehicle_length/2)-m_config.vehicle_rear_wheel2bumper_length));
	//out_Model_Coord[0] =m_config.model_scale*(in_world_coord[0]);
	if(m_calib_mode == calib_3D||m_calib_mode == calib_2D_SINGLE)
	{
        out_Model_Coord[1] = -m_config.model_scale*(in_world_coord[1]-((m_config.vehicle_length/2)-m_config.vehicle_rear_wheel2bumper_length));
	    out_Model_Coord[0] = m_config.model_scale*(in_world_coord[0]);
    }
    else if(m_calib_mode == calib_2D_STICH)
	{   
	   out_Model_Coord[1] = 1.0-(((in_world_coord[1])/(0.0-m_config.m_calib_mmpp_y)+m_config.m_calib_center_y)/240.0);
	   out_Model_Coord[0] =((in_world_coord[0])/m_config.m_calib_mmpp_x+m_config.m_calib_center_x-108.0)/108.0;	   
    }

}
void GlSVOverlayBase::Cal_World_2_Model_Coordinate_3d(float *out_Model_Coord,float *in_world_coord)
{
	float texture[2];
    float pZone[4];

	if(m_calib_mode == calib_3D)
	{  
        out_Model_Coord[2] = -m_config.model_scale*(in_world_coord[0]-((m_config.vehicle_length/2)-m_config.vehicle_rear_wheel2bumper_length));
		out_Model_Coord[1] = m_config.m_model_bottom-m_config.model_scale*in_world_coord[2];
	    out_Model_Coord[0] = m_config.model_scale*(in_world_coord[1]);
    }
	else if(m_calib_mode == calib_2D_SINGLE)
	{
	   // m_cam_pos=2;
		if(m_cam_pos == rear_camera_index)
		{
			in_world_coord[0] = -in_world_coord[0];
            in_world_coord[2] = -in_world_coord[2];
		}
		AVMData::GetInstance()->CalcUVTextureSV(in_world_coord,texture,m_cam_pos);


        if(m_cam_pos == rear_camera_index)
        {
			memcpy(pZone,m_pRearCamZone,4*sizeof(float));
            out_Model_Coord[2] = 0.0;
		    out_Model_Coord[1] = -(texture[1]-pZone[CAM_ZONE_TOP])/(pZone[CAM_ZONE_BOTTOM]-pZone[CAM_ZONE_TOP])/0.5+1;
	        out_Model_Coord[0] = (-texture[0]+pZone[CAM_ZONE_LEFT])/(pZone[CAM_ZONE_LEFT]-pZone[CAM_ZONE_RIGHT])/0.5-1;
			//out_Model_Coord[0] =-out_Model_Coord[0];
        }
        else
        {

		    memcpy(pZone,m_pFrontCamZone,4*sizeof(float));
        out_Model_Coord[2] = 0.0;
		out_Model_Coord[1] = -(texture[1]-pZone[CAM_ZONE_TOP])/(pZone[CAM_ZONE_BOTTOM]-pZone[CAM_ZONE_TOP])/0.5+1;
	    out_Model_Coord[0] = (texture[0]-pZone[CAM_ZONE_LEFT])/(pZone[CAM_ZONE_RIGHT]-pZone[CAM_ZONE_LEFT])/0.5-1;
		
        }
		
	
	}
	
   
}

void GlSVOverlayBase::SaveVertexData(void)
{
    int Loop =0;
	int slotid = 0;
    FILE* FP = fopen("./svres/overlay.txt", "wb");
 	for(Loop = 0;Loop <m_data_size*2*8;Loop++)
	{
 	    fprintf(FP,"%f ",*((float *)m_pdata+Loop));
		if(Loop %8 == 7)
		{
		    fprintf(FP,"\n");
		}

		

	} 
  fclose(FP);


   

}
void GlSVOverlayBase::Set_Cam_Pos(unsigned char pos,float *pCam)
{
    if(pos == 0)
    {
        m_config.m_front_cam_pos_wld[0]=pCam[0];
		m_config.m_front_cam_pos_wld[1]=pCam[1];
		m_config.m_front_cam_pos_wld[2]=pCam[2];
    }
	else
	{
        m_config.m_rear_cam_pos_wld[0]=pCam[0];
        m_config.m_rear_cam_pos_wld[1]=pCam[1];
        m_config.m_rear_cam_pos_wld[2]=pCam[2];
	    
	}
	
	//else if(m_calib_mode == calib_2D_SINGLE)
	//if(m_calib_mode !=calib_2D_SINGLE )
	m_cam_pos = pos;


}
void GlSVOverlayBase::Set_Cam_Zone(unsigned char pos,float *pCamZone)
{
   // 2 means front
	if(m_calib_mode == calib_2D_SINGLE)
	{
    if(pos == 2)
    {
       memcpy(m_pFrontCamZone,pCamZone,4*sizeof(float));
    }
	else
	{
       memcpy(m_pRearCamZone,pCamZone,4*sizeof(float));	    
	}
	//m_cam_pos = pos;

	}
}



