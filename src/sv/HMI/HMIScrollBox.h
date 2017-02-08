#ifndef __HMI_SCROLL_BOX_H__
#define __HMI_SCROLL_BOX_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/DataStruct.h"

typedef struct st_scroll_box_data_slot_Tag
{
	int icon_box_id;
	st_scroll_box_data_T *p_icon_box_data;
    float rect_point[4];
}st_scroll_box_data_slot_T;

#define MAX_SCROLL_NUM 12

class HMIScrollBox
{
public:
	HMIScrollBox(Region Global,Region Part,int slot_num = 12);
	void Init(ISceneNode *pSeneNode);
	int InitRectNode(float *pose,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer);
	int CalcPose(float *pPoseOutNomal,float *pPoseIn,float width,float height);

	void CalScrollPos(float scroll_rate,float *Inrect,float*pOutputRect,bool isHorizen,int index);
	int Add(ISceneNode *pSeneNode,st_scroll_box_data_T *icon_box_cfg);

	int Update(void);


private:
	INode *m_pNode[MAX_SCROLL_NUM*2];

	float *m_Scroll_buffer[MAX_SCROLL_NUM];

    int m_text_box_slot_num;

	int m_text_box_cur_index;
	ISceneNode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;

	st_scroll_box_data_slot_T *m_p_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
