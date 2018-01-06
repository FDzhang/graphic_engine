#ifndef _CSV_TRAINEDPARKING_H_
#define _CSV_TRAINEDPARKING_H_

#include "ISVHmi.h"
#include "../CGpuAvmEventDelegate.h"
#include "IF_Algo.h"

typedef enum TrainedParkingHmiTag
{
    TP_CAPTURE_IMAGE_ICON = 0,
    TP_NAVIGATING_ICON,
    TP_CONTROL_ICON,
	TP_PARKING_IN_ICON,
	TP_CAPTURE_IMAGE_PROMPT_BOX,
	TP_CAPTURE_IMAGE_PROCESS_BAR_BK,
	TP_PARKING_IN_PROMPT_BOX,
	TP_MAP_IMAGE,
	TP_DRIVING_CAR,
    TP_ICON_NUMS,
}
TrainedParkingHmiT;

typedef enum TrainedParkingStatusTag
{
	TRAINED_PARKING_NOMAL = 0,
	TRAINED_PARKING_CAPTURE_IMG,
	TRAINED_PARKING_ENTER_RESTRUCTION,
	TRAINED_PARKING_RESTRUCTION_PART1,
	TRAINED_PARKING_RESTRUCTION_PART2,
	TRAINED_PARKING_RESTRUCTION_PART3,
	TRAINED_PARKING_RESTRUCTION_PART4,	
	TRAINED_PARKING_SEARCHING_PATH,
	TRAINED_PARKING_FINISH_SEARCHING_PATH,
	TRAINED_PARKING_AUTO_MOVING,

	TRAINED_PARKING_STATUS_NUM,
}
TrainedParkingStatusT;

class CSVTrainedParkingHmi : public ISVHmi
{
public:
    CSVTrainedParkingHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    virtual ~CSVTrainedParkingHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()


public:
	static unsigned char m_tpCaptureImageIconVisibility;
	static unsigned char m_tpNavigatingIconVisibility;
	static unsigned char m_tpControlIconVisibility;
	static unsigned char m_tpParkingIconVisibility;
	
	static unsigned char m_tpCaptureImageIconShowNum;
	static unsigned char m_tpNavigatingIconShowNum;
	static unsigned char m_tpControlIconShowNum;
	static unsigned char m_tpParkingIconShowNum;
	static CGpuAvmEventDelegate* m_tpButtonClickEvent;

private:
    int SetTrainedParkingElemParams();
    int ProcessIconTouchEvent();
    int RefreshHmiIcon();
	int UpdateTpElem(Hmi_Message_T* hmiMsg);
	int AdapteTpPointCoord(float &pX, float &pY);
	    
private:
    Hmi_Button_Data_T tpIconData[TP_ICON_NUMS];
    HMIButton* tpIcon[TP_ICON_NUMS];

	HMITextBox *m_pTextBox;
	st_text_box_data_T m_text[8];

    unsigned char m_tpCaptureImagePromptBoxVisibility;
    unsigned char m_tpCaptureImagePromptBoxShowNum;
	unsigned char m_tpParkingInPromptBoxVisibility;
	unsigned char m_tpParkingInPromptBoxShowNum;

    unsigned char m_tpCaptureImageProcessBarVisibility;
	float 		  m_tpCaptureImageProcessBarRate;

	unsigned char m_tpMapImageVisibility;
	unsigned char m_tpDrivingCarVisibility;

	float m_anchorPointX;
	float m_anchorPointY;
	float m_rotateAlpha;
	unsigned char m_rotateShowFlag;

    float m_showRegionWidth;
    float m_showRegionHeight;

    float tpIconPos[TP_ICON_NUMS][2];
    float tpIconWidth[TP_ICON_NUMS];
    float tpIconHeight[TP_ICON_NUMS];

	float m_carIconPos[2];

	HMIScroll* m_hmiScroll;

	ISceneNode* m_referencePathNode;
	int			m_referencePathNodeId;
	float       m_referencePathRegion[4];
	
	HMIPolygonBoxDataT m_polygonBoxData;
	HMIPolygonBox*	   m_polygonBox;

	IActionTrigger*	m_trigger[TP_ICON_NUMS];


};

#endif //_CSV_TRAININGPARKING_H_
