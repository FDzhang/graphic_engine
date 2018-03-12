
#include "GlSVOverlayAPA.h"

#include <math.h>

#include "gpu_log.h"

/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

char StopSignName[MAX_NAME_LENGTH] = "stop_sign.dds";
char EndSignName[MAX_NAME_LENGTH] = "end_sign.dds";
char ArrowFoward[MAX_NAME_LENGTH] = "arror_foward.dds";
char ArrowBackward[MAX_NAME_LENGTH] = "arror_backward.dds";
char Scroll[MAX_NAME_LENGTH] = "scroll.dds";
char Scroll_Backward[MAX_NAME_LENGTH] = "scroll_backward.dds";
char ParkLot[MAX_NAME_LENGTH] = "park_lot.dds";
char UnParkLot[MAX_NAME_LENGTH] = "lock_park_lot.dds";
char ParkLotDetect[MAX_NAME_LENGTH] = "parking_lot_detection.dds";
char OnlineEnable[MAX_NAME_LENGTH] = "online_calib_enable.dds";
char OnlineAPAConflict[MAX_NAME_LENGTH] = "online_conflict.dds";
char UnLockParkLot[MAX_NAME_LENGTH] = "unlock_park_lot.dds";

#define CENTER_ICON_POS_X  0.0
#define CENTER_ICON_POS_Y  -0.1
#define CENTER_ICON_WIDTH_HALF  0.23
#define CENTER_ICON_HEIGHT_HALF 0.23


#define ARROW_ICON_POS_X  0.0
#define ARROW_ICON_POS_Y  -0.15
#define ARROR_ICON_WIDTH_HALF  0.1
#define ARROR_ICON_HEIGHT_HALF  0.2

#define SCROLL_WIDTH_HALF  ARROR_ICON_WIDTH_HALF
#define SCROLL_HEIGHT_HALF  ARROR_ICON_HEIGHT_HALF





/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


GlSVOverlayAPA::GlSVOverlayAPA()
{

	
}

int GlSVOverlayAPA::Init(ISceneNode *pSeneNode,char *pFilePath,AVM_Calib_2D_T calib_rslt)
{

	m_APA_result.drive_dirction_indicat = 0;
	m_APA_result.end_parking_sign_flag = 0;
	m_APA_result.stop_sign_flag = 0;
	m_APA_result.scroll_rate = 0.0;
	m_APA_result.park_lot_flag = 0;
	m_APA_result.parking_lot_detect_flag = 0;
	
	m_APA_result.online_detect_flag= 0;
	int tempmaterialid;
	IMaterial *tempcarmtl;
	IMesh *pMeshTemp;
	float *TempBuffer;
	float stop_sign_pose[8]={CENTER_ICON_POS_X-CENTER_ICON_WIDTH_HALF,CENTER_ICON_POS_Y-CENTER_ICON_HEIGHT_HALF,
		                     CENTER_ICON_POS_X+CENTER_ICON_WIDTH_HALF,CENTER_ICON_POS_Y-CENTER_ICON_HEIGHT_HALF,
		                     CENTER_ICON_POS_X-CENTER_ICON_WIDTH_HALF,CENTER_ICON_POS_Y+CENTER_ICON_HEIGHT_HALF,
		                     CENTER_ICON_POS_X+CENTER_ICON_WIDTH_HALF,CENTER_ICON_POS_Y+CENTER_ICON_HEIGHT_HALF};
	float arror_icon_pose[8] = {ARROW_ICON_POS_X-ARROR_ICON_WIDTH_HALF,ARROW_ICON_POS_Y-ARROR_ICON_HEIGHT_HALF,
		                     ARROW_ICON_POS_X+ARROR_ICON_WIDTH_HALF,ARROW_ICON_POS_Y-ARROR_ICON_HEIGHT_HALF,
	                     	ARROW_ICON_POS_X-ARROR_ICON_WIDTH_HALF,ARROW_ICON_POS_Y+ARROR_ICON_HEIGHT_HALF,
		                    ARROW_ICON_POS_X+ ARROR_ICON_WIDTH_HALF,ARROW_ICON_POS_Y+ARROR_ICON_HEIGHT_HALF};
	float scroll_icon_pose[8] = {ARROW_ICON_POS_X-SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y-SCROLL_HEIGHT_HALF,
		                     ARROW_ICON_POS_X+SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y-SCROLL_HEIGHT_HALF,
	                    	ARROW_ICON_POS_X-SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y+SCROLL_HEIGHT_HALF,
		                     ARROW_ICON_POS_X+SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y+SCROLL_HEIGHT_HALF};	
	
	sprintf(m_stop_sign_texture,"%s%s",pFilePath,StopSignName);
	sprintf(m_end_sign_texture,"%s%s",pFilePath,EndSignName);
	sprintf(m_foward_arrow_texture,"%s%s",pFilePath,ArrowFoward);
	sprintf(m_backward_arrow_texture,"%s%s",pFilePath,ArrowBackward);
	sprintf(m_scroll_texture,"%s%s",pFilePath,Scroll);
	sprintf(m_scroll_backward_texture,"%s%s",pFilePath,Scroll_Backward);
	sprintf(m_parklot_texture,"%s%s",pFilePath,ParkLot);
	
	sprintf(m_parklot_unpark_texture,"%s%s",pFilePath,UnParkLot);
	sprintf(m_parklotdetect_texture,"%s%s",pFilePath,ParkLotDetect);
	
	sprintf(m_parklot_unlockpark_texture,"%s%s",pFilePath,UnLockParkLot);
	sprintf(m_online_enable_texture,"%s%s",pFilePath,OnlineEnable);
    sprintf(m_online_apa_conflict_texture,"%s%s",pFilePath,OnlineAPAConflict);	
	InitRectNode(stop_sign_pose,&m_pSignNode,pSeneNode,m_stop_sign_texture,Material_Rigid_Blend,&TempBuffer);
	InitRectNode(arror_icon_pose,&m_pArrowNode,pSeneNode,m_foward_arrow_texture,Material_Rigid_Blend,&TempBuffer);
	InitRectNode(scroll_icon_pose,&m_pScrollNode,pSeneNode,m_scroll_texture,Material_Rigid_Blend,&m_Scroll_buffer);
	InitRectNode(scroll_icon_pose,&m_pParkLotNode,pSeneNode,m_parklot_texture,Material_Rigid_Blend,&m_Parklot_buffer);

    
	ProcessStopSign(m_APA_result.stop_sign_flag,m_APA_result.end_parking_sign_flag,m_APA_result.parking_lot_detect_flag,m_APA_result.online_detect_flag);
	ProcessArrowSign(m_APA_result.drive_dirction_indicat);
	ProcessScrollSign(m_APA_result.drive_dirction_indicat,m_APA_result.scroll_rate);
	ProcessParkLotSign(m_APA_result.park_lot_flag,m_APA_result.pParkLotPos,m_APA_result.parking_lot_type);
	m_calib_rslt = calib_rslt;

	
	return 0;
}

int GlSVOverlayAPA::InitRectNode(float *pose,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer)
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

int GlSVOverlayAPA::Update(APAOverlayStruct inOverlayResult)
{
    m_APA_result = inOverlayResult;

	ProcessStopSign(m_APA_result.stop_sign_flag,m_APA_result.end_parking_sign_flag,m_APA_result.parking_lot_detect_flag,m_APA_result.online_detect_flag);
	ProcessArrowSign(m_APA_result.drive_dirction_indicat);	
	ProcessScrollSign(m_APA_result.drive_dirction_indicat,m_APA_result.scroll_rate);
	ProcessParkLotSign(m_APA_result.park_lot_flag,m_APA_result.pParkLotPos,m_APA_result.parking_lot_type);


	return 0;
}
void GlSVOverlayAPA::ProcessStopSign(unsigned char sopt_flag,unsigned char end_flag,unsigned char park_lot_flag,unsigned char online_detect_flag)
{
    IMaterial *pTempMaterial;	
	m_pSignNode->GetMaterial(&pTempMaterial);
   if((sopt_flag == 1)&&(end_flag == 1))
   {
       m_pSignNode->SetEnable(0);
	   pTempMaterial->SetDiffuseMap(m_stop_sign_texture);
   }
   else if((sopt_flag == 1)&&(end_flag == 0))
   {

       m_pSignNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_stop_sign_texture);
  
   }
   else if((sopt_flag ==0)&&(end_flag == 1))
   {

       m_pSignNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_end_sign_texture);
  
   }
   else if(park_lot_flag == 1&&(online_detect_flag == 0))
   {
       m_pSignNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_parklotdetect_texture);
   }  
   else if(park_lot_flag == 0&&(online_detect_flag == 1))
   {
       m_pSignNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_online_enable_texture);
   }  
   else if(park_lot_flag == 1&&(online_detect_flag == 1))
   {
       m_pSignNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_online_apa_conflict_texture);
   }    
   else
   {
     m_pSignNode->SetEnable(0);
   }

	
}
void GlSVOverlayAPA::ProcessArrowSign(int direct_indicate)
{
    IMaterial *pTempMaterial;	
	m_pArrowNode->GetMaterial(&pTempMaterial);
   if(direct_indicate ==DRIVE_BACKWARD)
   {
       m_pArrowNode->SetEnable(0);
	   pTempMaterial->SetDiffuseMap(m_backward_arrow_texture);
   }
   else if(direct_indicate ==DRIVE_FOWARD)
   {

       m_pArrowNode->SetEnable(0);
       pTempMaterial->SetDiffuseMap(m_foward_arrow_texture);
  
   }
   else
   {
     m_pArrowNode->SetEnable(0);
   }

	
}
void GlSVOverlayAPA::ProcessScrollSign(int direct_indicate,float scroll_rate)
{
    IMaterial *pTempMaterial;	
	IMesh *pMeshTemp;
	float pOutput[4];
    float pInput[4] = {ARROW_ICON_POS_X-SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y+SCROLL_HEIGHT_HALF,ARROW_ICON_POS_X+SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y-SCROLL_HEIGHT_HALF};
	if(direct_indicate == DRIVE_NONE_DIRECT)
	{	    
		m_pScrollNode->SetEnable(0);
	    return;
	}
	m_pScrollNode->GetMaterial(&pTempMaterial);
    if(direct_indicate == DRIVE_FOWARD)
    {

	    pTempMaterial->SetDiffuseMap(m_scroll_texture);
    }
	else
	{

	    pTempMaterial->SetDiffuseMap(m_scroll_backward_texture);	
	}
	
	m_pScrollNode->SetEnable(0);
	CalScrollPos(scroll_rate,pInput,pOutput,direct_indicate);


    m_pScrollNode->GetMesh(&pMeshTemp);
	pMeshTemp->UnLockData();
	

	
}

void GlSVOverlayAPA::ProcessParkLotSign(int park_lot_flag,float *lot_pos,unsigned char park_lot_type)
{
    IMaterial *pTempMaterial;	
	IMesh *pMeshTemp;
	float pCoordImage[2];
    float pInput[4] = {ARROW_ICON_POS_X-SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y+SCROLL_HEIGHT_HALF,ARROW_ICON_POS_X+SCROLL_WIDTH_HALF,ARROW_ICON_POS_Y-SCROLL_HEIGHT_HALF};
	IMaterial *pNodeMtl;
	static unsigned char pre_park_lot_type=PARKABLE_PARK_LOT;
	if(park_lot_flag == NO_PARK_LOT)
	{	    
		m_pParkLotNode->SetEnable(0);
	    return;
	}
	
    m_pParkLotNode->SetEnable(0);

	for(int i =0;i<4;i++)
	{

         Cal_World_2_Image_Coordinate(pCoordImage,&(lot_pos[2*i]));
		 m_Parklot_buffer[8*i] = pCoordImage[0];
		 m_Parklot_buffer[8*i+1] = pCoordImage[1];
		 	    
	}
 
    m_pParkLotNode->GetMesh(&pMeshTemp);
	pMeshTemp->UnLockData();

   if(pre_park_lot_type != park_lot_type)
   {
       m_pParkLotNode->GetMaterial(&pNodeMtl);
       if(park_lot_type == PARKABLE_PARK_LOT)
       {
           pNodeMtl->SetDiffuseMap(m_parklot_texture);
       }
	   else if(park_lot_type == UNPARKABLE_PORK_LOT)
	   {
           pNodeMtl->SetDiffuseMap(m_parklot_unpark_texture);
	       
	   }
	   else
	   {
           pNodeMtl->SetDiffuseMap(m_parklot_unlockpark_texture);
	   
	   }
   }
   pre_park_lot_type = park_lot_type;
	
}

void GlSVOverlayAPA::Cal_World_2_Image_Coordinate(float *out_Model_Coord,float *in_world_coord)
{

  
	   out_Model_Coord[0] =((in_world_coord[1]*1000)/m_calib_rslt.ppmm_y+m_calib_rslt.center_y-108.0)/108.0;
	   out_Model_Coord[1] = 1.0-(((in_world_coord[0]*1000)/(0.0-m_calib_rslt.ppmm_x)+m_calib_rslt.center_x)/240.0);
	   

}

void GlSVOverlayAPA::CalScrollPos(float scroll_rate,float *Inrect,float*pOutputRect,int direct)
{
    float top = Inrect[1];
	float left = Inrect[0];
	float bottom = Inrect[3];
	float right = Inrect[2];

	float height_scroll= (top-bottom)*scroll_rate;

    pOutputRect[0] = left;
	pOutputRect[2] = right;
	if(direct == DRIVE_BACKWARD)
	{
    	pOutputRect[1] = top;
    	pOutputRect[3] = top-height_scroll;	  
		
		m_Scroll_buffer[7]=scroll_rate;
		m_Scroll_buffer[15]=scroll_rate;
		m_Scroll_buffer[23]=0.0;
		m_Scroll_buffer[31]=0.0;
		
	}
	else
	{
    	pOutputRect[1] = height_scroll+bottom;
    	pOutputRect[3] = bottom;
		m_Scroll_buffer[7]=1.0;
		m_Scroll_buffer[15]=1.0;
		m_Scroll_buffer[23]=1.0-scroll_rate;
		m_Scroll_buffer[31]=1.0-scroll_rate;

		
	}
	
	m_Scroll_buffer[0]=pOutputRect[0];
	m_Scroll_buffer[1]=pOutputRect[3];

    m_Scroll_buffer[8]=pOutputRect[2];
    m_Scroll_buffer[9]=pOutputRect[3];

    m_Scroll_buffer[16]=pOutputRect[0];
    m_Scroll_buffer[17]=pOutputRect[1];

    m_Scroll_buffer[24]=pOutputRect[2];
    m_Scroll_buffer[25]=pOutputRect[1];

	return;

}




