#ifndef _ISVHMI_H_
#define _ISVHMI_H_

#include "../DataStruct.h"
#include "../SVScene.h"
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../HMI/HMIButton.h"
#include "../HMI/HMITextBox.h"
#include "../HMI/HMIIconBox.h"
#include "../HMI/HMIScrollBox.h"
#include "../HMI/HMILDWLine.h"
#include "../HMI/HMISingleviewRect.h"
#include "../HMI/HMIBSDRadarIcon.h"

enum
{
    HMI_SUCCESS = 0,
    HMI_NO_MOCK_DATA= 1,
};

enum
{
     INVISIBLE = 0,
     VISIBLE = 1,
};

enum
{
    ALGO_LDW = 1,
    ALGO_BSD = 2,
    ALGO_ONLINE_CALIBRATION = 4,
    ALGO_APA = 5,
    ALGO_CTA,
    ALGO_LDW_BSD = 3,
};

typedef struct HmiKeyCtrlEventTag
{
    unsigned char changeViewMode;
    unsigned char changeViewKeyStatus;
}
HmiKeyCtrlEventT;

typedef struct Hmi_Message_Tag
{
    unsigned char view_model;
    unsigned char guide_line_model;
    unsigned char sys_language;
    unsigned char hmi_cmd;
    
    int algo_status;

	HmiKeyCtrlEventT keyCtrlEvent;
    
}
Hmi_Message_T;

class ISVHmi
{
public:
    ISVHmi();
    virtual ~ISVHmi();
    virtual int Init(int window_width, int window_height);
    virtual int Update(Hmi_Message_T& hmiMsg);
    virtual int ReturnHmiMsg(Hmi_Message_T* pHmiMsg);
    virtual int DestroyHmiElems();

	virtual int MockTouchEvent(Hmi_Message_T& hmiMsg);

public:
    int SetVisibility(unsigned int flag);  
    bool SetSingleTouchDownEvent(int x, int y);
    bool GetTouchEventInfo(int &x, int &y, int &type);
    bool SetCurrentView(unsigned char viewIndex);
    bool GetCurrentView(unsigned char &viewIndex);
    bool SetAvmDisplayView(unsigned char viewIndex);
    bool GetAvmDisplayView(unsigned char &viewIndex);
public:
    IUINode* m_uiNode;	
    int      m_uiNodeId;
    unsigned int m_visibilityStatus;

private:
	int m_touchEventFlag;
	int m_touchDownEventPosX;
	int m_touchDownEventPosY;

    unsigned char m_viewState;
    unsigned char m_avmDisplayViewState;

};


#endif //_ISVHMI_H_