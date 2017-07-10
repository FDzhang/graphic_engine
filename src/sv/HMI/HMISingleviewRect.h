#ifndef __HMI_SINGLE_VIEW_RECT_H__
#define __HMI_SINGLE_VIEW_RECT_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/DataStruct.h"

typedef struct st_singleview_rect_data_slot_Tag
{
	int icon_box_id;
	st_singleview_rect_data_T *p_singleview_rect_data;
	Float32 *pdatabuffer;
	unsigned int data_size;
    int element_num;
	INode *pNode;
	IMaterial *pRectMtl;
	IMesh *pRectMesh;
}st_singleview_rect_data_slot_T;

#define MAX_RECT_NUM 30
#define RECT_POINT_NUM 2




class HMISingleviewRect
{
public:
	HMISingleviewRect(Region Global,Region Part,int slot_num =20);
	void Init(ISceneNode *pSeneNode,unsigned char seconode_type);
	int Add(ISceneNode *pSeneNode,st_singleview_rect_data_T *ldw_line_cfg,unsigned char seconode_type=0);
    void CvtPointCoordinate(float *out_model_Coord,float *in_world_coord,bool rear_single_view);
	int Update(void);
    void GenerateSingleviewRectPlane(float *point,float*pVertex,bool rear_single_view);
    void SetEnable(bool flag);

private:

    int m_text_box_slot_num;
	int m_text_box_cur_index;
	ISceneNode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;
	unsigned char m_calib_mode;
	st_singleview_rect_data_slot_T *m_p_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
