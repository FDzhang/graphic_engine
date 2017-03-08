#ifndef __SV_NODE_ADAS_HMI_H__
#define __SV_NODE_ADAS_HMI_H__

//#include "fileloader.h"
#include "DataStruct.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "vehicle_motion_model.h"
#include "HMI/HMITextBox.h"
#include "HMI/HMIIconBox.h"

#include "HMI/HMIScrollBox.h"
#include "HMI/HMILDWLine.h"
#include "HMI/HMISingleviewRect.h"
#include "HMI/HMIBSDRadarIcon.h"



class SVNodeAdasHMI 
{
public:
	SVNodeAdasHMI(){};

	void Init(BEV_CONFIG_T  pConfig,ISceneNode *pSencenode,ISceneNode *pStichSencenode,st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandle,int HmiMdlNum);
	int Update(void);
	void SetEnable(unsigned char flag);

private:
	HMITextBox *m_pTextBox;	
	HMIIconBox *m_pIconBox;
	HMIScrollBox *m_pScrollBox;
	HMILDWLine *m_pLdwLine;	
	HMISingleviewRect *m_pSingleviewRect;
	HMIBSDRadarIcon *m_pBSDRadarIcon;
	IUINode*			m_AdasHMINode;
	bool m_hmi_enable;
};

#endif //#ifndef __GL_SV_DEMO_H__
