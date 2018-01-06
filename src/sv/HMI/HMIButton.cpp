#include "HMIButton.h"
#include "gpu_log.h"
extern IXrCore* g_pIXrCore;
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/
static IActionTrigger* trigger = NULL;

HMIButton:: HMIButton(Hmi_Button_Data_T* pButtonData,IUINode* uiNode)
{
    //m_uiNodeId = g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_uiNode);
    m_rotateFlag = 0;
    m_uiNode = uiNode;
    m_buttonSlot = new Hmi_Button_Slot_T();
    if(pButtonData != NULL)
    m_buttonSlot->buttonData = pButtonData;

    Init();
}

HMIButton::~HMIButton()
{

    ISpirit* ButtonLayer = m_uiNode->GetSpirit(m_buttonId);
	if(ButtonLayer && m_buttonSlot->iconMtl)
	{
    	ButtonLayer->Release();
    	//m_buttonSlot->iconMtl->Release();
	}
    delete m_buttonSlot;
}

int HMIButton::Init()
{
    int mtlId = 0;
    mtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, 
                                         m_buttonSlot->buttonData->icon_file_name[m_buttonSlot->buttonData->show_icon_num],
                                         0,
                                         &m_buttonSlot->iconMtl);
    
    m_buttonId = m_uiNode->CreateSpirit(-1, 
                                        InsertFlag_Default, 
                                        mtlId, 
                                        1.0, 
                                        m_buttonSlot->buttonData->pos[0], 
                                        m_buttonSlot->buttonData->pos[1], 
                                        0,
                                        m_buttonSlot->buttonData->width,
                                        m_buttonSlot->buttonData->height);

    m_buttonVisibleStatus = BUTTON_SHOW;

    if(m_buttonSlot->buttonData->trigger)
    {
        SetOnClickDelegate(m_buttonSlot->buttonData->trigger);
    }
    return BUTTON_NORMAL;                                                                
}

int HMIButton::Update()
{
    ISpirit *buttonLayer = m_uiNode->GetSpirit(m_buttonId);
    if(m_buttonVisibleStatus == BUTTON_HIDE)
    {
        buttonLayer->SetEnable(0);
    }
    else if(m_buttonVisibleStatus == BUTTON_SHOW) 
    {
        buttonLayer->SetEnable(1);
        m_buttonSlot->iconMtl->SetDiffuseMap(m_buttonSlot->buttonData->icon_file_name[m_buttonSlot->buttonData->show_icon_num]);
        if(m_buttonSlot->buttonData->icon_type == DYNAMIC_ICON)
        {
            if(m_rotateFlag == 1)
			{
              buttonLayer->SetAnchorPoint(m_anchorPointX, m_anchorPointY);
              buttonLayer->RotateZ(m_rotateZ);

            }
		
            buttonLayer->SetX(m_buttonSlot->buttonData->pos[0] + m_rotateFlag * m_anchorPointX * m_buttonSlot->buttonData->width);
            buttonLayer->SetY(m_buttonSlot->buttonData->pos[1] + m_rotateFlag * m_anchorPointY * m_buttonSlot->buttonData->height);
                
		    buttonLayer->SetWidth(m_buttonSlot->buttonData->width);
            buttonLayer->SetHeight(m_buttonSlot->buttonData->height);            
        }
    }
    
    return BUTTON_NORMAL;          
}
int HMIButton::onClickListener(unsigned int pos_x, unsigned int pos_y, unsigned char action)
{
    if(BUTTON_HIDE == m_buttonVisibleStatus)
    {
        return BUTTON_NORMAL;
    }
	static int  touch_action = action;
	static int  touch_pos_x = 0;
	static int  touch_pos_y = 0;

    if(SCREEN_TOUCHED == touch_action)
    {
        touch_pos_x = pos_x;
        touch_pos_y = pos_y;
    }
	else
	{
		return BUTTON_NORMAL; 
	}
	if(touch_pos_x > m_buttonSlot->buttonData->pos[0] 
            && touch_pos_x < m_buttonSlot->buttonData->pos[0] + m_buttonSlot->buttonData->width
            && touch_pos_y > m_buttonSlot->buttonData->pos[1] 
            && touch_pos_y < m_buttonSlot->buttonData->pos[1] + m_buttonSlot->buttonData->height)
    {
        ButtonEffectClick();
    }

	return BUTTON_NORMAL;
}
int HMIButton::ButtonEffectClick()
{
	if(m_buttonSlot->buttonData->delegate_func != NULL)
    {
        m_buttonSlot->buttonData->delegate_func();
    }
	return BUTTON_NORMAL;
}
int HMIButton::SetShowIconNum(unsigned int index)
{
    m_buttonSlot->buttonData->show_icon_num = index;
	
	m_buttonSlot->iconMtl->SetDiffuseMap(m_buttonSlot->buttonData->icon_file_name[m_buttonSlot->buttonData->show_icon_num]);
    return BUTTON_NORMAL; 
}
int HMIButton::SetX(float pos)
{
    m_buttonSlot->buttonData->pos[0] = pos;
    return BUTTON_NORMAL; 
}
int HMIButton::SetY(float pos)
{
    m_buttonSlot->buttonData->pos[1] = pos;
    return BUTTON_NORMAL; 
}
int HMIButton::SetRotateZ(float rZ, float anchorPointX, float anchorPointY, int flag)
{
	m_rotateFlag = flag;

	if(flag == 0)
	{
		return BUTTON_NORMAL;
	}
	m_rotateZ = rZ;
	m_anchorPointX = anchorPointX;
	m_anchorPointY = anchorPointY;
	
	return BUTTON_NORMAL; 
}

int HMIButton::SetWidth(float width)
{
    m_buttonSlot->buttonData->width = width;
    return BUTTON_NORMAL; 
}
int HMIButton::SetHeight(float height)
{
    m_buttonSlot->buttonData->height = height;
    return BUTTON_NORMAL; 
}

int HMIButton::GetButtonId()
{   
    return m_buttonId;
}
int HMIButton::SetVisibility(unsigned int flag)
{
    if(flag > 1)
    {
        flag = 1;
    }
    m_buttonVisibleStatus = flag;
	ISpirit *buttonLayer = m_uiNode->GetSpirit(m_buttonId);
	buttonLayer->SetEnable(m_buttonVisibleStatus);
	
    return BUTTON_NORMAL; 
}
int HMIButton::ButtonShow()
{
    m_buttonVisibleStatus = BUTTON_SHOW;
	ISpirit *buttonLayer = m_uiNode->GetSpirit(m_buttonId);
	buttonLayer->SetEnable(m_buttonVisibleStatus);
    return BUTTON_NORMAL;  
}

int HMIButton::ButtonHide()
{
    m_buttonVisibleStatus = BUTTON_HIDE;
	ISpirit *buttonLayer = m_uiNode->GetSpirit(m_buttonId);
	buttonLayer->SetEnable(m_buttonVisibleStatus);
    return BUTTON_NORMAL;  
}

Boolean HMIButton::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		if(m_buttonSlot->buttonData->animationStyle == BUTTON_FLASH_HIGHLIGHT)
		{
			m_buttonSlot->iconMtl->SetDiffuseMap(m_buttonSlot->buttonData->icon_file_name[BUTTON_ON_IMAGE]);
		}
		if (m_trigger) m_trigger->OnPress(layerId);
	}
	else if (type == TouchEvent_Up) {
		if(m_buttonSlot->buttonData->animationStyle == BUTTON_FLASH_HIGHLIGHT)
		{
			m_buttonSlot->iconMtl->SetDiffuseMap(m_buttonSlot->buttonData->icon_file_name[BUTTON_OFF_IMAGE]);		
		}
		if (m_trigger) m_trigger->OnRelease(layerId, true);
	}
	else if (type == TouchEvent_Move)
	{
		if(m_buttonSlot->buttonData->animationStyle == BUTTON_FLASH_HIGHLIGHT)
		{
			m_buttonSlot->iconMtl->SetDiffuseMap(m_buttonSlot->buttonData->icon_file_name[BUTTON_ON_IMAGE]);		
		}
	}

	return TRUE;
}

Void HMIButton::SetOnClickDelegate(IActionTrigger* trigger)
{
	ISpirit *buttonLayer = m_uiNode->GetSpirit(m_buttonId);
	if (buttonLayer) buttonLayer->SetEventResponder(this);
	m_trigger = trigger;
}
String HMIButton::GetName()
{
	return m_name;
}

Void HMIButton::SetName(String name)
{
	if (!m_name) {m_name = new CHAR[MaxNameLen];
	}
	if (!m_name) return;
	strcpy(m_name, name);
}


