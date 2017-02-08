#ifndef __GL_SV_OVERLAY_APA_H__
#define __GL_SV_OVERLAY_APA_H__

#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "DataStruct.h"

#define DRIVE_BACKWARD  -1
#define DRIVE_FOWARD 1
#define DRIVE_NONE_DIRECT 0

#define NO_PARK_LOT  0
#define PARK_LOT_RECT 1


class GlSVOverlayAPA
{
public:
	GlSVOverlayAPA();

	int Init(ISceneNode *pSeneNode,char *pFilePath,AVM_Calib_2D_T calib_rslt);
	int InitRectNode(float *pose,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer);
	int Update(APAOverlayStruct OverlayReslt);
	void ProcessStopSign(unsigned char sopt_flag,unsigned char end_flag,unsigned char park_lot_flag,unsigned char online_detect_flag);
	void ProcessArrowSign(int direct_indicate);
	void ProcessScrollSign(int direct_indicate,float scroll_rate);
	void CalScrollPos(float scroll_rate,float *Inrect,float*pOutputRect,int direct);
	void Cal_World_2_Image_Coordinate(float *out_Model_Coord,float *in_world_coord)	;
	void ProcessParkLotSign(int park_lot_flag,float *lot_pos);


private:

    APAOverlayStruct m_APA_result;
    char m_stop_sign_texture[MAX_NAME_LENGTH];
	char m_end_sign_texture[MAX_NAME_LENGTH];
	char m_foward_arrow_texture[MAX_NAME_LENGTH];
	char m_backward_arrow_texture[MAX_NAME_LENGTH];
	char m_scroll_texture[MAX_NAME_LENGTH];
	char m_scroll_backward_texture[MAX_NAME_LENGTH];	
	char m_parklot_texture[MAX_NAME_LENGTH];
	char m_parklotdetect_texture[MAX_NAME_LENGTH];
	char m_online_enable_texture[MAX_NAME_LENGTH];
	char m_online_apa_conflict_texture[MAX_NAME_LENGTH];

	INode *m_pSignNode;
	INode *m_pArrowNode;
	INode *m_pScrollNode;
	INode *m_pParkLotNode;

	float *m_Scroll_buffer;
	float *m_Parklot_buffer;
	

    AVM_Calib_2D_T m_calib_rslt;

};

#endif //#ifndef __GL_SV_DEMO_H__
