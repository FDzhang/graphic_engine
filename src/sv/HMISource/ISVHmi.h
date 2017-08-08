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
};

enum
{
     INVISIBLE = 0,
     VISIBLE = 1,
};

typedef struct Hmi_Message_Tag
{
    unsigned char view_model;
    unsigned char guide_line_model;
    unsigned char sys_language;
    unsigned char hmi_cmd;
}
Hmi_Message_T;

class ISVHmi
{
public:
    ISVHmi();
    virtual ~ISVHmi();
    virtual int Init(int window_width, int window_height);
    virtual int Update();
    virtual int ReturnHmiMsg(Hmi_Message_T* pHmiMsg);
    virtual int DestroyHmiElems();

public:
    int SetVisibility(unsigned int flag);  
    bool SetSingleTouchDownEvent(int x, int y);
    bool GetTouchEventInfo(int &x, int &y, int &type);
    bool SetCurrentView(unsigned char viewIndex);
    bool GetCurrentView(unsigned char &viewIndex);
public:
    IUINode* m_uiNode;	
    int      m_uiNodeId;
    unsigned int m_visibilityStatus;

private:
	int m_touchEventFlag;
	int m_touchDownEventPosX;
	int m_touchDownEventPosY;

        unsigned char m_viewState;

};


#endif //_ISVHMI_H_