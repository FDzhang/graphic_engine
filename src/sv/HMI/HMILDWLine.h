#ifndef __HMI_LDW_LINE_H__
#define __HMI_LDW_LINE_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/DataStruct.h"

typedef struct st_ldw_line_data_slot_Tag
{
	int icon_box_id;
	st_LDW_line_data_T *p_ldw_line_data;
	Float32 *pdatabuffer;
	unsigned int data_size;
    int element_num;
	INode *pNode;
	IMaterial *pLineMtl;
	IMesh *pLineMesh;
}st_ldw_line_data_slot_T;

#define MAX_LINE_NUM 5
#define LDW_LINE_POINT_NUM 50


#define SCENCE_NODE_TYPE_2D_STICH  0
class HMILDWLine
{
public:
	HMILDWLine(Region Global,Region Part,int slot_num =4);
	void Init(ISceneNode *pSeneNode,unsigned char seconode_type,float view_world_bottom,float view_world_top );
	int Add(ISceneNode *pSeneNode,st_LDW_line_data_T *ldw_line_cfg,unsigned char seconode_type=0);
    void CvtPointCoordinate(float *out_model_Coord,float *in_world_coord);
	int Update(void);
    void GenerateLDWLinePlane(float curv,float slop,float L_offset,float R_offset,int total_num,float*pVertex);


private:


    int m_text_box_slot_num;

	int m_text_box_cur_index;
	ISceneNode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;
	unsigned char m_calib_mode;
    float m_view_world_bottom;
	float m_view_wolrd_top;
	st_ldw_line_data_slot_T *m_p_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
