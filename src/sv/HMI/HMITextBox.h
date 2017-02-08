#ifndef __HMI_TEXT_BOX_H__
#define __HMI_TEXT_BOX_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "sv/DataStruct.h"

typedef struct st_text_box_data_slot_Tag
{
	int text_box_id;
	st_text_box_data_T *p_text_box_data;
	ITextLayer *pText[MAX_TEXT_BOX_LINE_NUM];
	int back_ground_id;
	int text_line_num;
}st_text_box_data_slot_T;





class HMITextBox
{
public:
	HMITextBox(Region Global,Region Part,int slot_num = 30);
	void Init(IUINode *pSeneNode,char *background_name,char *font_type_Mtl);

	int Add(IUINode *pSeneNode,st_text_box_data_T *text_box_cfg,int *first_text_index);

	int InitSingleTextBox(st_text_box_data_T *text_box_cfg,IUINode *pSeneNode,ITextLayer ** text,int textMtlId,int text_index);
	int CalcCoordinate(float *pInGlobalPose,float *pOutAeraPose);
	int Update(void);


private:

	int m_font_mtl_id;
	int m_back_mtl_id;
    int m_text_box_slot_num;

	int m_text_box_cur_index;
	IUINode *m_pSeneNode;
	Region m_global_region;
	Region m_text_aera_region;

	st_text_box_data_slot_T *m_ptext_box_slot;

};

#endif //#ifndef __GL_SV_DEMO_H__
