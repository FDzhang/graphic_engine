#include "SVUI.h"
#include "SVScene.h"
#include "SVCalibration.h"
//#include "vld.h"
SVCalibration caliui;

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
extern IAnimationManager* am;
extern float* exparam;
extern float EX_PARAM[24];
extern char exParamFile[];


#define HMI_OFFSET  0
//#define WINDOW_WIDTH  1024
#define WINDOW_WIDTH  1280
#define TOP_ALI_DOCK_HEIGHT  40
#define WINDOW_HEIGHT  720
#define MODEPANEL_W 200
#define MODEPANEL_H 620
#define MODEPANEL_X_FADEIN
#define MODEPANEL_Y 60+HMI_OFFSET
#define MODEPANEL_X_FADEOUT

#define ITEM_X	65
#define ITEM_Y  20
#define ITEM_W	98
#define ITEM_H	98
#define ITEM_INTVAL	55

#define SETTINGSPANEL_X 2*(WINDOW_WIDTH/5)
#define SETTINGSPANEL_Y_FADEIN 32+HMI_OFFSET
#define SETTINGSPANEL_Y_FADEOUT -700
#define SETTINGSPANEL_WIDTH (WINDOW_WIDTH/5)
#define SETTINGSPANEL_HEIGHT  200
#define PRODUCT_BUTTON_WIDTH   128
#define PRODUCT_BUTTON_HEIGHT   32
#define PRODUCT_BUTTON_INT  12
#define SIDE_PRODUCT_BUTTON_WIDTH   60
#define SIDE_PRODUCT_BUTTON_HEIGHT  60
#define SIDE_PRODUCT_BUTTON_INT  -5

#define SIDE_PRODUCT_PANEL_X  (WINDOW_WIDTH*9/10+30)
//#define SIDE_PRODUCT_PANEL_Y  (WINDOW_HEIGHT*2/3)-50
#define SIDE_PRODUCT_PANEL_Y  (WINDOW_HEIGHT/2-30)
#define SIDE_PRODUCT_WIDTH    (WINDOW_WIDTH/20+10)
//#define SIDE_PRODUCT_HEIGHT   (WINDOW_HEIGHT/5+80)
#define SIDE_PRODUCT_HEIGHT   (WINDOW_HEIGHT/2-20)
#define SIDE_PRODUCT_PANEL_X_FADEOUT  (WINDOW_WIDTH+30)

#define SIDE_ZOOM_PANEL_Y  (SIDE_PRODUCT_PANEL_Y-180)
#define SIDE_ZOOM_HEIGHT   (180)


#define POSITIONPANEL_X 4*(WINDOW_WIDTH/5)
#define POSITIONPANEL_Y_FADEIN 32+HMI_OFFSET
#define POSITIONPANEL_Y_FADEOUT -700
#define POSITIONPANEL_WIDTH (WINDOW_WIDTH/5)
#define POSITIONPANEL_HEIGHT  350
#define POSITION_BUTTON_WIDTH   50
#define POSITION_BUTTON_HEIGHT   32
#define POSITION_BUTTON_INT  12



#define STYLEPANEL_X (2*WINDOW_WIDTH/6)
#define STYLEPANEL_Y_FADEIN HMI_OFFSET
#define STYLEPANEL_Y_FADEOUT -700

#define LISCENSEPANEL_X 240
#define LISCENSEPANEL_Y_FADEIN 250
#define LISCENSEPANEL_Y_FADEOUT -700
#define LISCENSEPANEL_WIDTH 880
#define LISCENSEPANEL_HEIGHT 360


#define CANSIMPANEL_X (5*WINDOW_WIDTH/6)
#define CANSIMPANEL_Y_FADEIN HMI_OFFSET
#define CANSIMPANEL_Y_FADEOUT -700
#define CANSIMPANEL_WIDTH  WINDOW_WIDTH/6
#define CANSIMPANEL_HEIGHT 350

#define CAMDIRPANEL_X (WINDOW_WIDTH/6)
#define CAMDIRPANEL_Y_FADEIN HMI_OFFSET
#define CAMDIRPANEL_Y_FADEOUT -700
#define CAMDIRPANEL_WIDTH  WINDOW_WIDTH/6
#define CAMDIRPANEL_HEIGHT 230


#define MODESELPANEL_X 0
#define MODESELPANEL_Y_FADEIN HMI_OFFSET
#define MODESELPANEL_Y_FADEOUT -700
#define MODESELPANEL_WIDTH  WINDOW_WIDTH/6
#define MODESELPANEL_HEIGHT 270



#define ZOOMPANEL_X (4*WINDOW_WIDTH/6)
#define ZOOMPANEL_Y_FADEIN CANSIMPANEL_Y_FADEIN
#define ZOOMPANEL_Y_FADEOUT -700
#define ZOOMPANEL_WIDTH  WINDOW_WIDTH/6
#define ZOOMPANEL_HEIGHT 150



#define COLOR_Y  40+HMI_OFFSET
#define COLOR_X_FADE_OUT  850
#define COLOR_X_FADE_IN   470
#define MODEL_Y 80+HMI_OFFSET
#define MODEL_X_FADE_OUT  850
#define MODEL_X_FADE_IN   470
#define BUTTON_OPACITY 0.5
#define TOP_DOCK_BUTTON_NUM  5
#define PRODUCT_AMOUNT_ALL 3
#if 0
//camera direction at bottom 
#define CAMERA_DIRECTION_LAYER_X   220
#define CAMERA_DIRECTION_LAYER_Y   630
#define CAMERA_DIRECTION_LAYER_W   800
#define CAMERA_DIRECTION_LAYER_H   64
#define CAMERA_DIRECT_BUTTON_ROW  1
#define CAMERA_DIRECT_BUTTON_COL  4
#define CAMERA_DIRECT_BUTTON_X  0
#define CAMERA_DIRECT_BUTTON_Y  16
#define CAMERA_DIRECT_BUTTON_INT_X  200
#define CAMERA_DIRECT_BUTTON_INT_Y  0
#define CAMERA_DIRECT_BUTTON_W   160
#define CAMERA_DIRECT_BUTTON_H  32
#endif

#define CAMERA_DIRECTION_LAYER_X   220
#define CAMERA_DIRECTION_LAYER_Y   672
#define CAMERA_DIRECTION_LAYER_W   800
#define CAMERA_DIRECTION_LAYER_H   64
#define CAMERA_DIRECT_BUTTON_ROW  4
#define CAMERA_DIRECT_BUTTON_COL  1
#define CAMERA_DIRECT_BUTTON_X  0
#define CAMERA_DIRECT_BUTTON_Y  16
#define CAMERA_DIRECT_BUTTON_INT_X  0
#define CAMERA_DIRECT_BUTTON_INT_Y  65
#define CAMERA_DIRECT_BUTTON_W   60
#define CAMERA_DIRECT_BUTTON_H  60

static CXrPanel* panel;
static CXrCellular* cellular;
static CXrNavigator* navigator;
static CXrSelector* selector;
static CXrSelector* AliCtrlSelFB;
static CXrSelector* AliCtrlSelLR;

static CXrSelector* keyboard[7];
static CXrSelector* Tempselector;
static CXrSelector* Productselector;
static CXrSelector* ProductPositionselector;
static CXrNavigator* sideproductbar;
static CXrNavigator* sidezoombar;



static CXrPanel* settingspanel;
static CXrPanel* settingspanel_back;
static CXrPanel* stylepanel_back;
static CXrPanel* stylepanel;
static CXrPanel* CamDirPanel;
static CXrPanel* ModeSelectPanel;

static CXrPanel* CANSimpanel;
static CXrPanel* CANSimpanel_back;
static CXrPanel* Zoompanel;
static CXrPanel* Zoompanel_back;

static CXrPanel *pColorPanel;
static CXrPanel* liscensePanel;
static CXrTextLable* TextOutput;
static CXrTextLable* ChineseTextOutput;
static CXrPanel* positionpanel;
static CXrPanel* sideproductpanel;
static CXrPanel* sidezoompanel;

static CXrButton* settingsbutton[4];
static CXrButton* dockbuttombutton[TOP_DOCK_BUTTON_NUM];

static ILayer* BottomRootLayer=0;
static ILayer* settingsRootLayer=0;
static ISpirit* settingsSubContentLayer=0;
static ISpirit* styleSubContentLayer=0;
static ISpirit* liscenceSubContentLayer=0;
static ISpirit* PositionSubContentLayer=0;
static ISpirit* SideProductContentLayer=0;
static ISpirit* CANSimContentLayer=0;
static ISpirit* ZoomContentLayer=0;
static ISpirit* CamDirLayer=0;
static ISpirit* ModeSelLayer=0;

static char* liscenceText[] = {
"1", "2", "3", "4","5", "6", "7", "8","9","0",
"Q", "W", "E", "R","T", "Y", "U", "I","O","P", 
"A", "S", "D", "F","G", "H", "J", "K","L",
"Z", "X", "C", "V","B", "N", "M","Cancel","Enter","Space"};

class AdjustPanelTrigger : public IActionTrigger
{
public:
	AdjustPanelTrigger(class SVCalibration* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		//m_app->TriggerAdjustPanel();
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->ToggleShow();
	}
private:
	SVCalibration* m_app;
};
AdjustPanelTrigger* adjustPanelTrigger;

class RippleTrigger : public IActionTrigger
{
public:
	RippleTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->ToggleRipple();
	}
private:
	SVUI* m_app;
};

class FrostTrigger : public IActionTrigger
{
public:
	FrostTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->ToggleFrost();
	}
private:
	SVUI* m_app;
};

class NavigatorTrigger : public IActionTrigger
{
public:
	NavigatorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		if (id==0) {
			m_app->svscn->EnterFreeView(CameraPosition_Free);
			selector->ClearSelect();
		}
		else if (id==1) {
			m_app->svscn->EnterTopView(CameraPosition_Front);
			selector->ClearSelect();
		}
		else if (id==2) {
			m_app->svscn->EnterCrossView(CameraPosition_Front);
			selector->ClearSelect();
		}
		else if (id==3) {
			m_app->svscn->EnterPanorama(CameraPosition_Front);
			selector->ClearSelect();
		}
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

		if (m_app->m_modeAutoHide) m_app->TriggerShowMode();
	}
private:
	SVUI* m_app;
};
static NavigatorTrigger*	navigatorTrigger;

class SelectorTrigger : public IActionTrigger
{
public:
	SelectorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		Int32 camPos;
		if (id==0) camPos = CameraPosition_Front;
		else if (id==1) camPos = CameraPosition_Back;
		else if (id==2) camPos = CameraPosition_Left;
		else if (id==3) camPos = CameraPosition_Right;
	 	m_app->svscn->SwitchCameraPosition(camPos);
        m_app->m_pCamDirSelect->ClearSelect();
		if (m_app->m_modeAutoHide) m_app->TriggerShowMode();
	}

private:
	SVUI* m_app;
};

class ModeSelectorTrigger : public IActionTrigger
{
public:
	ModeSelectorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    m_app->m_pModeSelect->ClearSelect();
		if (id==1) {
			m_app->svscn->EnterFreeView(CameraPosition_Free);
		}
		else if (id==2) {
			m_app->svscn->EnterTopView(CameraPosition_Front);
		}
		else if (id==3) {
			m_app->svscn->EnterCrossView(CameraPosition_Front);
		}
		else if (id==4) {
			m_app->svscn->EnterPanorama(CameraPosition_Front);
		}
		else if (id==0) {
			m_app->svscn->ZoomFunction(ZOOM_TURN);
		}		
	}

private:
	SVUI* m_app;
};


static SelectorTrigger*	selectorTrigger;

class AliCtrlTriggerFB : public IActionTrigger
{
public:
	AliCtrlTriggerFB(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	 	m_app->svscn->SwitchViewCtrlButton(id);
		
	    AliCtrlSelFB->ClearSelect();
		AliCtrlSelLR->ClearSelect();
	}

private:
	SVUI* m_app;
};

static AliCtrlTriggerFB*	m_AliCtrlTriggerFB;

class AliCtrlTriggerLR : public IActionTrigger
{
public:
	AliCtrlTriggerLR(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
        if(id == 0)
        {
	 	    m_app->svscn->SwitchViewCtrlButton(id+2);
        }
		else if(id == 1)
		{
		    m_app->svscn->ZoomFunction(ZOOM_TURN);

		}
		else
		{
	 	    m_app->svscn->SwitchViewCtrlButton(id+1);
		    
		}
		
	    AliCtrlSelFB->ClearSelect();
		AliCtrlSelLR->ClearSelect();
	}

private:
	SVUI* m_app;
};

static AliCtrlTriggerLR*	m_AliCtrlTriggerLR;


class TopDockSelectorTrigger : public IActionTrigger
{
public:
	TopDockSelectorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
	    //if(id<3)
	    m_app->m_dockTrigger[id]->OnPress(id);
		#if 0
		Int32 camPos;
		if (id==0) camPos = CameraPosition_Front;
		else if (id==1) camPos = CameraPosition_Back;
		else if (id==2) camPos = CameraPosition_Left;
		else if (id==3) camPos = CameraPosition_Right;
	 	m_app->svscn->SwitchCameraPosition(camPos);
		#endif
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    Tempselector->ClearSelect();
	   // if(id<3)

	    m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};

static TopDockSelectorTrigger*	topDockSelector;

class ProductSelectorTrigger : public IActionTrigger
{
public:
	ProductSelectorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{


	 	m_app->svscn->ShowProduct(id);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    Productselector->ClearSelect();

	   // m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};

static ProductSelectorTrigger*	pProductSelectTrigger;
class ZoomSelectorTrigger : public IActionTrigger
{
public:
	ZoomSelectorTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{


	 	m_app->svscn->ZoomFunction(id);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	   // Productselector->ClearSelect();

	   // m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};

static ZoomSelectorTrigger*	pZoomSelectTrigger;


class ProductPositionTrigger : public IActionTrigger
{
public:
	ProductPositionTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{


	 	m_app->svscn->AdjustProductPosition(id);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    ProductPositionselector->ClearSelect();

	   // m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};

static ProductPositionTrigger*	pProductPositionTrigger;

class HMIPositionTrigger : public IActionTrigger
{
public:
	HMIPositionTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{


	 	m_app->TriggerShowPosition();
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    ProductPositionselector->ClearSelect();

	   // m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};
class SideProductTrigger : public IActionTrigger
{
public:
	SideProductTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{


	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    ProductPositionselector->ClearSelect();
	 	m_app->TriggerShowSideProduct();

	   // m_app->m_dockTrigger[id]->OnRelease(id,isIn);
	}

private:
	SVUI* m_app;
};

class DockTriggerMode : public IActionTrigger
{
public:
	DockTriggerMode(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowMode();
	}
private:
	SVUI* m_app;
};

class DockTriggerCANSim : public IActionTrigger
{
public:
	DockTriggerCANSim(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowCANSim();
	}
private:
	SVUI* m_app;
};
class DockTriggerCamDir : public IActionTrigger
{
public:
	DockTriggerCamDir(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowCamDir();
	}
private:
	SVUI* m_app;
};
class DockTriggerModeSel : public IActionTrigger
{
public:
	DockTriggerModeSel(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowModeSelect();
	}
private:
	SVUI* m_app;
};

class DockTriggerZoomSim : public IActionTrigger
{
public:
	DockTriggerZoomSim(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowZoom();
	}
private:
	SVUI* m_app;
};

class DockTriggerSettings : public IActionTrigger
{
public:
	DockTriggerSettings(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowSettings();
	}
private:
	SVUI* m_app;
};
class DockTriggerStyle : public IActionTrigger
{
public:
	DockTriggerStyle(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowStyle();
	}
private:
	SVUI* m_app;
};

class DockTriggerLiscense : public IActionTrigger
{
public:
	DockTriggerLiscense(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowLiscence();
	}
private:
	SVUI* m_app;
};

class DockTriggerReset : public IActionTrigger
{
public:
	DockTriggerReset(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->svscn->ResetStyleSetting();
	}
private:
	SVUI* m_app;
};

class DockTriggerModelButton : public IActionTrigger
{
public:
	DockTriggerModelButton(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowModel();
	}
private:
	SVUI* m_app;
};
class DockTriggerColorButton : public IActionTrigger
{
public:
	DockTriggerColorButton(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowColor();
	}
private:
	SVUI* m_app;
};

class DockTriggerLiscenseKeyboard4 : public IActionTrigger
{
public:
	DockTriggerLiscenseKeyboard4(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
         m_app->TriggerShowKeyboard(id+29);
	}
private:
	SVUI* m_app;
};
class DockTriggerLiscenseKeyboard5 : public IActionTrigger
{
public:
	DockTriggerLiscenseKeyboard5(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
         m_app->TriggerShowKeyboard(id+36);
	}
private:
	SVUI* m_app;
};

class DockTriggerLiscenseKeyboard3 : public IActionTrigger
{
public:
	DockTriggerLiscenseKeyboard3(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowKeyboard(id+20);
	}
private:
	SVUI* m_app;
};
class DockTriggerLiscenseKeyboard1 : public IActionTrigger
{
public:
	DockTriggerLiscenseKeyboard1(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowKeyboard(id);

	}
private:
	SVUI* m_app;
};
class DockTriggerModelPanel : public IActionTrigger
{
public:
	DockTriggerModelPanel(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    m_app->m_pModelSelect->ClearSelect();
		m_app->svscn->SwitchCarModel(id);

	}
private:
	SVUI* m_app;
};
class DockTriggerColorPanel : public IActionTrigger
{
public:
	DockTriggerColorPanel(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    m_app->m_pCANSimSelect->ClearSelect();
		if(id ==0)
		m_app->svscn->ZoomFunction(ZOOM_TYRE);
		else if(id<5)
		m_app->svscn->DoorAction(id-1);
		else
		m_app->svscn->TurnLightAction(id-5);

	}
private:
	SVUI* m_app;
};
class DockTriggerStyleAliPanel : public IActionTrigger
{
public:
	DockTriggerStyleAliPanel(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    m_app->m_pStyleSelect->ClearSelect();
		if(id ==0)
		    m_app->svscn->ZoomFunction(ZOOM_COLOR);
		else if(id==1)
			m_app->svscn->ZoomFunction(ZOOM_MODEL);
		else
			m_app->svscn->ResetStyleSetting();
			

	}
private:
	SVUI* m_app;
};


class DockTriggerZoomPanel : public IActionTrigger
{
public:
	DockTriggerZoomPanel(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	    m_app->m_pZoomSimSelect->ClearSelect();
		m_app->svscn->ZoomFunction(id);

	}
private:
	SVUI* m_app;
};


class DockTriggerLiscenseChinese : public IActionTrigger
{
public:
	DockTriggerLiscenseChinese(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerChineseKeyboard(id);

	}
private:
	SVUI* m_app;
};

class DockTriggerLiscenseKeyboard2 : public IActionTrigger
{
public:
	DockTriggerLiscenseKeyboard2(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowKeyboard(id+10);
	}
private:
	SVUI* m_app;
};


class ModeTrigger : public IActionTrigger
{
public:
	ModeTrigger(class SVUI* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_app->TriggerShowMode();
	}
private:
	SVUI* m_app;
};


class ADOnSettingsShowHide : public IAnimationDelegate
{
public:
	ADOnSettingsShowHide(class SVUI* app) { m_app = app; }
	virtual Boolean OnFinish(class IAProperty* caller)
	{
		m_app->OnSettingsShowHide(caller->Get());
		return TRUE;
	}
private:
	SVUI* m_app;
};
static ADOnSettingsShowHide*	pADOnSettingsShowHide;


static char* dockText[] = {
	"MODE", "ADJUST", "STYLE", "POSITION","SETTINGS", };
static char* AlidockText[] = {
	"View Mode", "Camera Direction", "Style", "Menu","Zoom","CAN" };
static char* buttonText[] = {
	"FRONT",  "BACK", "LEFT", "RIGHT"};

int SVUI::InitNode(BEV_CONFIG_T  pConfig,int width,int height)
{
	InitEffect();
	m_node = 0;
	m_nodeId = g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_node);
	m_showPosition=0;

	m_dockTrigger[0]= new DockTriggerModeSel(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_dockTrigger[1]= new DockTriggerCamDir(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	//m_dockTrigger[2]= new HMIPositionTrigger(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_dockTrigger[2]= new DockTriggerStyle(this);
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_dockTrigger[3] = new DockTriggerLiscense(this);
    m_dockTrigger[4] = new DockTriggerZoomSim(this);
   m_dockTrigger[5] = new DockTriggerCANSim(this);
	m_modeTrigger = new ModeTrigger(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_showModel = false;
	m_showColor=false;
	m_showSideProduct=true;
    m_bev_config = pConfig;
	m_screen_width = width;
	m_screen_height = height;
	
	InitLogo();
	InitUI();
	return 0;
}



void SVUI::OnSettingsShowHide(float position)
{
	if (position == SETTINGSPANEL_Y_FADEIN) {
		for (int i=0;i<4;i++) {
			settingsSubContentLayer->SetOpacity(1.0);
			//settingsbutton[i]->SetOpacity(BUTTON_OPACITY);
		}
	}
	else if  (position == SETTINGSPANEL_Y_FADEOUT) {
		for (int i=0;i<4;i++) {
			settingsSubContentLayer->SetOpacity(0);
			//settingsbutton[i]->SetOpacity(0);
		}
	}
}

void SVUI::TriggerShowSettings()
{
	if (!m_showSettings) {
		settingspanel->SetPosition(SETTINGSPANEL_X,SETTINGSPANEL_Y_FADEIN);
		//settingspanel->SetSize(400, 512);
		m_showSettings = true;
	}
	else {
		settingspanel->SetPosition(SETTINGSPANEL_X,SETTINGSPANEL_Y_FADEOUT);
		//settingspanel->SetSize(256, 640);
		m_showSettings = false;
	}
}
void SVUI::TriggerShowPosition()
{
	if (!m_showPosition) {
		positionpanel->SetPosition(POSITIONPANEL_X,POSITIONPANEL_Y_FADEIN);
		PositionSubContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showPosition = true;
	}
	else {
		
		PositionSubContentLayer->SetOpacity(0.0);	
		positionpanel->SetPosition(POSITIONPANEL_X,POSITIONPANEL_Y_FADEOUT);
		

		//settingspanel->SetSize(256, 640);
		m_showPosition = false;
	}
}
void SVUI::TriggerShowSideProduct()
{
	if (!m_showSideProduct) {
		sideproductpanel->SetPosition(SIDE_PRODUCT_PANEL_X,SIDE_PRODUCT_PANEL_Y);
		//SideProductContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showSideProduct = true;
	}
	else {
		
		//SideProductContentLayer->SetOpacity(0.0);	
		sideproductpanel->SetPosition(SIDE_PRODUCT_PANEL_X_FADEOUT,SIDE_PRODUCT_PANEL_Y);
		

		//settingspanel->SetSize(256, 640);
		m_showSideProduct = false;
	}
}

void SVUI::TriggerShowStyle()
{
	if (!m_showStyle) {
		stylepanel->SetPosition(STYLEPANEL_X,STYLEPANEL_Y_FADEIN);
		
		styleSubContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showStyle = true;
	}
	else {
		stylepanel->SetPosition(STYLEPANEL_X,STYLEPANEL_Y_FADEOUT);
		
		styleSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showStyle = false;
		#if 0
		liscensePanel->SetPosition(LISCENSEPANEL_X,LISCENSEPANEL_Y_FADEOUT);
		liscenceSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showLiscence = false;
		
		m_pCarModelPanel->SetPosition(MODEL_X_FADE_OUT,MODEL_Y);
		
		m_pCarModelPanel->SetOpacity(0.0);
		m_ModelSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showModel = false;
		
		m_pCarColorPanel->SetPosition(COLOR_X_FADE_OUT,COLOR_Y);
		
		m_pCarColorPanel->SetOpacity(0.0);
		m_ColorSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showColor = false;
		#endif

		
	}
}
void SVUI::TriggerShowLiscence()
{
	if (!m_showLiscence) {
		liscensePanel->SetPosition(LISCENSEPANEL_X,LISCENSEPANEL_Y_FADEIN);
		
		liscenceSubContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showLiscence = true;
	}
	else {
		liscensePanel->SetPosition(LISCENSEPANEL_X,LISCENSEPANEL_Y_FADEOUT);
		
		liscenceSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showLiscence = false;
	}
}

void SVUI::TriggerShowModel()
{
	if (!m_showModel) {
		m_pCarModelPanel->SetPosition(MODEL_X_FADE_IN,MODEL_Y);
		m_pCarModelPanel->SetOpacity(0.4);
		m_ModelSubContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showModel = true;
	}
	else {
		m_pCarModelPanel->SetPosition(MODEL_X_FADE_OUT,MODEL_Y);
		
		m_pCarModelPanel->SetOpacity(0.0);
		m_ModelSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showModel = false;
	}
}
void SVUI::TriggerShowColor()
{

	if (!m_showColor) {
		m_pCarColorPanel->SetPosition(COLOR_X_FADE_IN,COLOR_Y);
		m_pCarColorPanel->SetOpacity(0.4);
		m_ColorSubContentLayer->SetOpacity(1.0);
		//settingspanel->SetSize(400, 512);
		m_showColor = true;
	}
	else {
		m_pCarColorPanel->SetPosition(COLOR_X_FADE_OUT,COLOR_Y);
		
		m_pCarColorPanel->SetOpacity(0.0);
		m_ColorSubContentLayer->SetOpacity(0.0);
		//settingspanel->SetSize(256, 640);
		m_showColor = false;
	}
}

void SVUI::TriggerShowMode()
{
	if (!m_showMode) {
		panel->SetPosition(-30,MODEPANEL_Y);
		BottomRootLayer->SetOpacity(1);
		//cellular->SetOpacity(1.0);
		m_showMode = true;
	}
	else {
		panel->SetPosition(-MODEPANEL_W-30,MODEPANEL_Y);
		BottomRootLayer->SetOpacity(0);
		//cellular->SetOpacity(0);
		m_showMode = false;
	}
}
void SVUI::TriggerShowCANSim()
{
	if (!m_showCANSim) {
		CANSimpanel->SetPosition(CANSIMPANEL_X,CANSIMPANEL_Y_FADEIN);
		CANSimContentLayer->SetOpacity(1.0);
		m_showCANSim = true;
	}
	else {
		CANSimpanel->SetPosition(CANSIMPANEL_X,CANSIMPANEL_Y_FADEOUT);
		CANSimContentLayer->SetOpacity(0);
		m_showCANSim = false;
	}
}

void SVUI::TriggerShowCamDir()
{
	if (!m_showCamDir) {
		CamDirPanel->SetPosition(CAMDIRPANEL_X,CAMDIRPANEL_Y_FADEIN);
		CamDirLayer->SetOpacity(1.0);
		m_showCamDir = true;
	}
	else {
		CamDirPanel->SetPosition(CAMDIRPANEL_X,CAMDIRPANEL_Y_FADEOUT);
		CamDirLayer->SetOpacity(0);
		svscn->EnterFreeView(CameraPosition_Free);
		m_showCamDir = false;
	}
}
void SVUI::TriggerShowModeSelect()
{
	if (!m_showModeSel) {
		ModeSelectPanel->SetPosition(MODESELPANEL_X,MODESELPANEL_Y_FADEIN);
		ModeSelLayer->SetOpacity(1.0);
		m_showModeSel = true;
	}
	else {
		ModeSelectPanel->SetPosition(MODESELPANEL_X,MODESELPANEL_Y_FADEOUT);
		ModeSelLayer->SetOpacity(0);
		svscn->EnterFreeView(CameraPosition_Free);
		m_showModeSel = false;
	}
}

void SVUI::TriggerShowZoom()
{
	if (!m_showZoomSim) {
		Zoompanel->SetPosition(ZOOMPANEL_X,ZOOMPANEL_Y_FADEIN);
		ZoomContentLayer->SetOpacity(1.0);
		m_showZoomSim = true;
	}
	else {
		Zoompanel->SetPosition(ZOOMPANEL_X,ZOOMPANEL_Y_FADEOUT);
		ZoomContentLayer->SetOpacity(0);
		m_showZoomSim = false;
	}
}

void SVUI::TriggerShowKeyboard(int Id)
{
    int len=0;
	
	len = strlen(m_selected_liscense);
	
    for(int i=0;i<5;i++)
    {
        keyboard[i]->ClearSelect();
    }

	if(Id<36)
	{
		if(len == 9)
	{
	    return;
	}
		if(len == 1)
			{
			strcat(m_selected_liscense," - ");

			}
    	//m_selected_liscense+="s";
    	strcat(m_selected_liscense,liscenceText[Id]);
    	//strcat(m_selected_liscense,"s");
    
    	
	}
	else
	{
	    if(Id == 36)
	    {
			m_selected_liscense[len-1]=0;
	        
	    }
		else if(Id == 37)
		{
		TriggerShowLiscence();
		svscn->UpdateLisceseText(m_selected_liscense,m_chinese_index);
	    }
		else
		{
		
		}
	}
	
	TextOutput->SetText(m_selected_liscense);
}
void SVUI::TriggerChineseKeyboard(int Id)
{
	

        keyboard[5]->ClearSelect();
		m_chinese_index=Id;



	
	ChineseTextOutput->SetText(Id);
}
int SVUI::InitSideProductPanel()
{

	char *Text[5]={"WHEEL","TOUR","WHITE","GRAY","YELLOW"};

    sideproductpanel = new CXrPanel(2);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	sideproductpanel->Add(m_node, -1, InsertFlag_Default,SIDE_PRODUCT_PANEL_X, SIDE_PRODUCT_PANEL_Y, SIDE_PRODUCT_WIDTH, SIDE_PRODUCT_HEIGHT, 0.4, XR_RES"BC64.dds");
	Int32 panelId = sideproductpanel->GetRootId();
	//sideproductpanel->SetPosition(-30,MODEPANEL_Y);
	

	
	// buffer file %s,line %d",__FILE__,__LINE__);

	sideproductbar = new CXrNavigator();

	// buffer file %s,line %d",__FILE__,__LINE__);
    sideproductbar->SetInitSelect(NONE_INIT_SELECT,SWITCH_TYPE_BUTTON);
    sideproductbar->SetButtonTexture(m_node,1, XR_RES"esr.dds",  XR_RES"radar_back_init.dds", XR_RES"blackrect.dds");
    sideproductbar->SetButtonTexture(m_node,2, XR_RES"ifv_300.dds",  XR_RES"radar_back_init.dds", XR_RES"blackrect.dds");	
    sideproductbar->SetButtonTexture(m_node,3, XR_RES"MRR_init.dds",  XR_RES"radar_back_init.dds", XR_RES"blackrect.dds");	
    sideproductbar->SetButtonTexture(m_node,4, XR_RES"tyre.dds",  XR_RES"radar_back_init.dds", XR_RES"blackrect.dds");
    sideproductbar->SetButtonTexture(m_node,5, XR_RES"cameraico.dds",  XR_RES"radar_back_init.dds", XR_RES"blackrect.dds");	
	
	sideproductbar->Add(m_node, panelId, InsertFlag_Child, 0, 2, SIDE_PRODUCT_BUTTON_WIDTH, SIDE_PRODUCT_BUTTON_HEIGHT, SIDE_PRODUCT_BUTTON_INT, 1.0, XR_RES"bev_camera.dds",  XR_RES"connerframe.dds", XR_RES"conerback.dds", 6,0);
	//sideproductbar->SetItemText(0,"Surround");

	sideproductbar->SetOnClickDelegate(pProductSelectTrigger);
	#if 0
	CXrDivider* paneldiv[TOP_DOCK_BUTTON_NUM];
	for (int i=1;i<TOP_DOCK_BUTTON_NUM; i++) { 
		paneldiv[i] = new CXrDivider(MODEPANEL_W*0.75 ,1, 1);
		
		// buffer file %s,line %d",__FILE__,__LINE__);
		paneldiv[i]->Add(m_node, panelId, InsertFlag_Child, MODEPANEL_W*0.2, i*(ITEM_H+ITEM_INTVAL));
		paneldiv[i]->SetOpacity(0.8);
	}
	#endif
#if 0
	 m_pShowFuncSelect = new CXrSelector(4);
	 
	 m_pShowFuncSelect->Add(m_node, panelId, InsertFlag_Child, 0, 4*(SIDE_PRODUCT_BUTTON_HEIGHT+SIDE_PRODUCT_BUTTON_INT), SIDE_PRODUCT_BUTTON_WIDTH, SIDE_PRODUCT_BUTTON_HEIGHT, 0, SIDE_PRODUCT_BUTTON_HEIGHT, BUTTON_OPACITY, XR_RES"connerframe.dds", XR_RES"conerback.dds", 2, 1);

         for(int i=0;i<2;i++)
         {
             m_pShowFuncSelect->SetTextSize(15);
    	     m_pShowFuncSelect->SetItemText(i, Text[i]);
    	 }
#endif
	//m_pShowFuncSelect->SetOnClickDelegate(style_trigger_temp);
	 


	
	return 0;

}
int SVUI::InitModeSelectPanel()
{

    int panel_x, panel_y,panel_width,panel_height;
	int button_start_x,button_start_y,button_width,button_height,button_interval;
	
    panel_x = m_screen_width*m_bev_config.smc_hmi.LEFT_PANEL_POSITION_X;
	panel_y = m_screen_height*m_bev_config.smc_hmi.LEFT_PANEL_POSITION_Y;

    panel_width = m_screen_width*m_bev_config.smc_hmi.LEFT_PANEL_WIDTH;
	panel_height = panel_width*4*1.05;
	

    button_start_x =panel_width*0.15+30;
	button_start_y = panel_width*0.1;
	button_width = panel_width*0.7;
	button_height = panel_width*0.7;
	button_interval =panel_width*0.35;


	/////////////Left Select Mode////////////////////
	panel = new CXrPanel(16);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	panel->Add(m_node, -1, InsertFlag_Default, panel_x-30, panel_y, panel_width+30, panel_height, 0.4, XR_RES"BC64.dds");
	Int32 panelId = panel->GetRootId();


	navigatorTrigger = new NavigatorTrigger(this);
	
	navigator = new CXrNavigator();
	
    navigator->SetInitSelect(0);
	navigator->Add(m_node, panelId, InsertFlag_Child, button_start_x, button_start_y, button_width, button_height, button_interval, 1.0, XR_RES"modebutton.dds",  XR_RES"cd128.dds", XR_RES"WC64.dds", 4);

	navigator->SetItemText(0,"Surround");
	navigator->SetItemText(1,"TopView");
	navigator->SetItemText(2,"CrossView");
	navigator->SetItemText(3,"Panorama");
	navigator->SetOnClickDelegate(navigatorTrigger);
	
	CXrDivider* paneldiv[TOP_DOCK_BUTTON_NUM];
	paneldiv[0] = new CXrDivider(panel_width*0.9 ,1, 1);
	
	paneldiv[0]->Add(m_node, panelId, InsertFlag_Child, panel_width*0.05+30, panel_width*1.05,3,panel_width*1.05);
	paneldiv[0]->SetOpacity(0.8);
	#if 0
	panel->SetOpacity(0.0);
	navigator->SetOpacity(0.0);
	#endif

	return 0;

}
int SVUI::InitStylePanel()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	static char* styleText[] = {
	"Color", "Model", "License", "Reset" };
	
	stylepanel = new CXrPanel(3);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	stylepanel->Add(m_node, -1, InsertFlag_Default, STYLEPANEL_X, STYLEPANEL_Y_FADEIN, 205, 200, 0.4, XR_RES"BC64.dds");
	lid = m_node->CreateSpirit(stylepanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 205, 640);
	styleSubContentLayer = m_node->GetSpirit(lid);
	styleSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);
	IActionTrigger* style_trigger_temp[4];
	CXrButton* stylebutton[4];
	style_trigger_temp[0]= new DockTriggerColorButton(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	style_trigger_temp[1]= new DockTriggerModelButton(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	style_trigger_temp[2]= new DockTriggerLiscense(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	style_trigger_temp[3]= new DockTriggerReset(this);
	for (int i=0;i<4; i++) {

		stylebutton[i] = new CXrButton(4);;
		
		// buffer file %s,line %d",__FILE__,__LINE__);
		stylebutton[i]->Add(m_node, lid, InsertFlag_Child, 38, 12+i*44, 128, 32, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");;
		stylebutton[i]->SetText(styleText[i]);
		stylebutton[i]->SetActionDelegate(style_trigger_temp[i]);

	}
	return 0;

}
#define STYLE_PANEL_NUM  3
int SVUI::InitStylePanelAli()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	static char* styleText[] = {
	"Color", "Model", "Reset", "Reset" };
	IActionTrigger* style_trigger_temp;
	stylepanel = new CXrPanel(-1);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	stylepanel->Add(m_node, -1, InsertFlag_Default, STYLEPANEL_X, STYLEPANEL_Y_FADEOUT, 205, 200, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(stylepanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 205, 640);
	
	styleSubContentLayer = m_node->GetSpirit(lid);
	styleSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);
	style_trigger_temp =new DockTriggerStyleAliPanel(this);


	 m_pStyleSelect = new CXrSelector(-1);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pStyleSelect->Add(m_node, lid, InsertFlag_Child, CANSIMPANEL_WIDTH*0.1, 10+TOP_ALI_DOCK_HEIGHT, CANSIMPANEL_WIDTH*0.8, 32, 50, 42, BUTTON_OPACITY, XR_RES"frame.dds", XR_RES"button.dds", STYLE_PANEL_NUM, 1);

         for(int i=0;i<STYLE_PANEL_NUM;i++)
         {
             m_pStyleSelect->SetTextSize(15);
    	     m_pStyleSelect->SetItemText(i, styleText[i]);
    	 }

	m_pStyleSelect->SetOnClickDelegate(style_trigger_temp);
	m_showCANSim =false;

	return 0;
	
	
}
#define CAMDIR_PANEL_NUM  4
int SVUI::InitCamDirPanel()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	static char* styleText[] = {
	"Front", "Rear", "Left", "Right" };
	IActionTrigger* style_trigger_temp;
	CamDirPanel = new CXrPanel(-1);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	CamDirPanel->Add(m_node, -1, InsertFlag_Default, CAMDIRPANEL_X, CAMDIRPANEL_Y_FADEOUT, CAMDIRPANEL_WIDTH, CAMDIRPANEL_HEIGHT, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(CamDirPanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, CAMDIRPANEL_WIDTH, CAMDIRPANEL_HEIGHT);
	CamDirLayer = m_node->GetSpirit(lid);
	CamDirLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);

	style_trigger_temp =new SelectorTrigger(this);


	 m_pCamDirSelect = new CXrSelector(-1);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pCamDirSelect->Add(m_node, lid, InsertFlag_Child, CAMDIRPANEL_WIDTH*0.1, 10+TOP_ALI_DOCK_HEIGHT, CAMDIRPANEL_WIDTH*0.8, 32, 50, 42, BUTTON_OPACITY, XR_RES"frame.dds", XR_RES"button.dds", CAMDIR_PANEL_NUM, 1);

         for(int i=0;i<CAMDIR_PANEL_NUM;i++)
         {
             m_pCamDirSelect->SetTextSize(15);
    	     m_pCamDirSelect->SetItemText(i, styleText[i]);
    	 }

	m_pCamDirSelect->SetOnClickDelegate(style_trigger_temp);
	m_showCamDir =false;


	return 0;
	
	
}
#define MODE_PANEL_NUM  5
int SVUI::InitModeSelPanel()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	static char* styleText[] = {
	"Rotate", "Surround View", "Top View", "Cross View","Panarama View" };
	IActionTrigger* style_trigger_temp;
	ModeSelectPanel = new CXrPanel(-1);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	ModeSelectPanel->Add(m_node, -1, InsertFlag_Default, MODESELPANEL_X, MODESELPANEL_Y_FADEOUT, MODESELPANEL_WIDTH, MODESELPANEL_HEIGHT, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(ModeSelectPanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, MODESELPANEL_WIDTH, MODESELPANEL_HEIGHT);
	ModeSelLayer = m_node->GetSpirit(lid);
	ModeSelLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);

	style_trigger_temp =new ModeSelectorTrigger(this);


	 m_pModeSelect = new CXrSelector(-1);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pModeSelect->Add(m_node, lid, InsertFlag_Child, MODESELPANEL_WIDTH*0.1, 10+TOP_ALI_DOCK_HEIGHT, MODESELPANEL_WIDTH*0.8, 32, 50, 42, BUTTON_OPACITY, XR_RES"frame.dds", XR_RES"button.dds", MODE_PANEL_NUM, 1);

         for(int i=0;i<MODE_PANEL_NUM;i++)
         {
             m_pModeSelect->SetTextSize(15);
    	     m_pModeSelect->SetItemText(i, styleText[i]);
    	 }

	m_pModeSelect->SetOnClickDelegate(style_trigger_temp);
	m_showModeSel=false;


	return 0;
	
	
}


#define CAN_SIM_SIG_NUM  7
int SVUI::InitCANSimulatePanel()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	
	IActionTrigger* style_trigger_temp;
	static char* styleText[] = {
	"wheel turn", "driver door", "front right door", "rear left door","rear right door" ,"turn left","turn right"};
	
	CANSimpanel = new CXrPanel(-1);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	CANSimpanel->Add(m_node, -1, InsertFlag_Default, CANSIMPANEL_X, CANSIMPANEL_Y_FADEOUT, CANSIMPANEL_WIDTH, CANSIMPANEL_HEIGHT, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(CANSimpanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, CANSIMPANEL_WIDTH, CANSIMPANEL_HEIGHT);
	CANSimContentLayer = m_node->GetSpirit(lid);
	CANSimContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);
	style_trigger_temp =new DockTriggerColorPanel(this);


	 m_pCANSimSelect = new CXrSelector(-1);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pCANSimSelect->Add(m_node, lid, InsertFlag_Child, CANSIMPANEL_WIDTH*0.1, 10+TOP_ALI_DOCK_HEIGHT, CANSIMPANEL_WIDTH*0.8, 32, 50, 42, BUTTON_OPACITY, XR_RES"frame.dds", XR_RES"button.dds", CAN_SIM_SIG_NUM, 1);

         for(int i=0;i<CAN_SIM_SIG_NUM;i++)
         {
             m_pCANSimSelect->SetTextSize(15);
    	     m_pCANSimSelect->SetItemText(i, styleText[i]);
    	 }

	m_pCANSimSelect->SetOnClickDelegate(style_trigger_temp);
	m_showCANSim =false;
	return 0;

}

#define ZOOM_SIG_NUM  2
int SVUI::InitZoomPanel()
{
	////////////////////////style panel////////////////////////
	Int32 lid;
	
	IActionTrigger* style_trigger_temp;
	static char* styleText[] = {
	"Zoom In", "Zoom Out", "front right door", "rear left door","rear right door" };
	
	Zoompanel = new CXrPanel(-1);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	Zoompanel->Add(m_node, -1, InsertFlag_Default, ZOOMPANEL_X, ZOOMPANEL_Y_FADEOUT, ZOOMPANEL_WIDTH, ZOOMPANEL_HEIGHT, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(Zoompanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, ZOOMPANEL_WIDTH, ZOOMPANEL_HEIGHT);
	ZoomContentLayer = m_node->GetSpirit(lid);
	ZoomContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);
	style_trigger_temp =new DockTriggerZoomPanel(this);


	 m_pZoomSimSelect = new CXrSelector(-1);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pZoomSimSelect->Add(m_node, lid, InsertFlag_Child, ZOOMPANEL_WIDTH*0.1, 10+TOP_ALI_DOCK_HEIGHT, ZOOMPANEL_WIDTH*0.8, 32, 50, 42, BUTTON_OPACITY, XR_RES"frame.dds", XR_RES"button.dds", ZOOM_SIG_NUM, 1);

         for(int i=0;i<ZOOM_SIG_NUM;i++)
         {
             m_pZoomSimSelect->SetTextSize(15);
    	     m_pZoomSimSelect->SetItemText(i, styleText[i]);
    	 }

	m_pZoomSimSelect->SetOnClickDelegate(style_trigger_temp);
	m_showZoomSim =false;
	return 0;

}

int SVUI::InitSideControltPanel()
{
    int side_panel_x, side_panel_y,side_panel_width,side_panel_height;
	int button_start_x,button_start_y,button_width,button_height,button_interval;
    side_panel_x = m_screen_width*m_bev_config.smc_hmi.RIGHT_PANEL_POSITION_X;
	side_panel_y = m_screen_height*m_bev_config.smc_hmi.RIGHT_PANEL_POSITION_Y;

    side_panel_width = m_screen_width*m_bev_config.smc_hmi.RIGHT_PANEL_WIDTH;
	side_panel_height = m_screen_height*m_bev_config.smc_hmi.RIGHT_PANEL_HEIGHT;
	

    button_start_x =side_panel_width*0.05;
	button_start_y = side_panel_height/6.0*0.05;
	button_width = side_panel_width*0.9;
	button_height = side_panel_height/6.0*0.9;
	button_interval =side_panel_height/6.0*0.1;
    sidezoompanel = new CXrPanel(2);
	

	sidezoompanel->Add(m_node, -1, InsertFlag_Default,side_panel_x, side_panel_y, side_panel_width, side_panel_height, 0.0, XR_RES"BC64.dds");
	Int32 panelId = sidezoompanel->GetRootId();
	
	pZoomSelectTrigger= new ZoomSelectorTrigger(this);

	

	sidezoombar = new CXrNavigator();

    sidezoombar->SetInitSelect(NONE_INIT_SELECT,PULSE_TYPE_BUTTON);
    sidezoombar->SetButtonTexture(m_node,1, XR_RES"zoomout.dds",  XR_RES"zoomout.dds", XR_RES"zoomout.dds");
    sidezoombar->SetButtonTexture(m_node,2, XR_RES"cameraico.dds",  XR_RES"cameraico.dds", XR_RES"cameraico.dds");	
    sidezoombar->SetButtonTexture(m_node,3, XR_RES"tyre.dds",  XR_RES"tyre.dds", XR_RES"tyre.dds");	
    sidezoombar->SetButtonTexture(m_node,4, XR_RES"car_model.dds",  XR_RES"car_model.dds", XR_RES"car_model.dds");	
    sidezoombar->SetButtonTexture(m_node,5, XR_RES"color.dds",  XR_RES"color.dds", XR_RES"color.dds");	
	
	sidezoombar->Add(m_node, panelId, InsertFlag_Child, button_start_x, button_start_y, button_width, button_height, button_interval, 1.0, XR_RES"zoomin.dds",  XR_RES"zoomin.dds", XR_RES"zoomin.dds", 6,0);


	sidezoombar->SetOnClickDelegate(pZoomSelectTrigger);
	
	 
    //sidezoombar->SetOpacity(0.0);

	
	return 0;

}

int SVUI::InitTopPanelAli()
{

    selectorTrigger = new SelectorTrigger(this);
    // buffer file %s,line %d",__FILE__,__LINE__);
    
    //////////////////////////Top Dock //////////////////////////
    Int32 dockLayerId = m_node->CreateSpirit(-1, InsertFlag_Default, -1, 1.0, 0, HMI_OFFSET, 0 ,WINDOW_WIDTH,32); 
    Float32 opacity = 0.2;
    CXrButton* button[ALI_TOP_DOCK_BUTTON_NUM];
    CXrDivider* div[ALI_TOP_DOCK_BUTTON_NUM];
    
    Tempselector = new CXrSelector(0);
    
    // buffer file %s,line %d",__FILE__,__LINE__);
    Tempselector->Add(m_node, dockLayerId, InsertFlag_Child, 0, 0, WINDOW_WIDTH/ALI_TOP_DOCK_BUTTON_NUM, TOP_ALI_DOCK_HEIGHT, WINDOW_WIDTH/ALI_TOP_DOCK_BUTTON_NUM, 0, BUTTON_OPACITY, XR_RES"through.dds", XR_RES"WC64.dds", 1, ALI_TOP_DOCK_BUTTON_NUM);
	//Tempselector->SetOpacity(0.0);

	Tempselector->SetItemText(0, AlidockText[0]);
    Tempselector->SetItemText(1,AlidockText[1]);
    Tempselector->SetItemText(2, AlidockText[2]);
    Tempselector->SetItemText(3, AlidockText[3]);	
    Tempselector->SetItemText(4, AlidockText[4]);
    Tempselector->SetItemText(5, AlidockText[5]);
	
    Tempselector->SetTextSize(TOP_ALI_DOCK_HEIGHT/2);
    topDockSelector = new TopDockSelectorTrigger(this);
    
    // buffer file %s,line %d",__FILE__,__LINE__);
    Tempselector->SetOnClickDelegate(topDockSelector);
    
    div[0] = new CXrDivider(40, 0, 0);
    // buffer file %s,line %d",__FILE__,__LINE__);
    div[0]->Add(m_node, dockLayerId, InsertFlag_Child, WINDOW_WIDTH/ALI_TOP_DOCK_BUTTON_NUM,0,ALI_TOP_DOCK_BUTTON_NUM-1,WINDOW_WIDTH/ALI_TOP_DOCK_BUTTON_NUM); 		
    div[0]->SetOpacity(0.6);	

	return 0;
}

int SVUI::InitTopPanel()
{

    selectorTrigger = new SelectorTrigger(this);
    // buffer file %s,line %d",__FILE__,__LINE__);
    
    //////////////////////////Top Dock //////////////////////////
    Int32 dockLayerId = m_node->CreateSpirit(-1, InsertFlag_Default, -1, 1.0, 0, HMI_OFFSET, 0 ,1024,32); 
    Float32 opacity = 0.2;
    CXrButton* button[TOP_DOCK_BUTTON_NUM];
    CXrDivider* div[TOP_DOCK_BUTTON_NUM];
    
    Tempselector = new CXrSelector(0);
    
    // buffer file %s,line %d",__FILE__,__LINE__);
    Tempselector->Add(m_node, dockLayerId, InsertFlag_Child, 0, 0, WINDOW_WIDTH/4, 32, WINDOW_WIDTH/4, 0, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 4);
    Tempselector->SetItemText(0, dockText[0]);
    Tempselector->SetItemText(1,dockText[1]);
    Tempselector->SetItemText(2, dockText[2]);
    Tempselector->SetItemText(3, dockText[3]);	
    //Tempselector->SetItemText(4, dockText[4]);
    Tempselector->SetTextSize(15);
    topDockSelector = new TopDockSelectorTrigger(this);
    
    // buffer file %s,line %d",__FILE__,__LINE__);
    Tempselector->SetOnClickDelegate(topDockSelector);
    
    div[0] = new CXrDivider(40, 0, 0);
    // buffer file %s,line %d",__FILE__,__LINE__);
    div[0]->Add(m_node, dockLayerId, InsertFlag_Child, WINDOW_WIDTH/4, 6,TOP_DOCK_BUTTON_NUM-2,WINDOW_WIDTH/4); 		
    div[0]->SetOpacity(0.6);	

	return 0;
}
int SVUI::InitBottomPanel()
{
    int panel_x, panel_y,panel_width,panel_height;
	int button_start_x,button_start_y,button_width,button_height,button_interval;
    panel_x = m_screen_width*m_bev_config.smc_hmi.BOTTOM_PANEL_POSITION_X;
	panel_y = m_screen_height*m_bev_config.smc_hmi.BOTTOM_PANEL_POSITION_Y;

    panel_width = m_screen_width*m_bev_config.smc_hmi.BOTTOM_PANEL_WIDTH;
	panel_height = m_screen_height*m_bev_config.smc_hmi.BOTTOM_PANEL_HEIGHT;
	

    button_start_x =panel_width/4.0*0.2;
	button_start_y = panel_height*0.05;
	button_width = panel_width/4*0.6;
	button_height = panel_height*0.9;
	button_interval =panel_width/4.0;



	Int32 bottomLayerId = m_node->CreateSpirit(-1, InsertFlag_Default, -1, 1.0, panel_x, panel_y, 0 ,panel_width, panel_height); 
	BottomRootLayer = m_node->GetLayer(bottomLayerId);
	BottomRootLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);


	selector = new CXrSelector(8);
	selector->Add(m_node, bottomLayerId, InsertFlag_Child, button_start_x, button_start_y, button_width, button_height, button_interval, 0, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 4);

	selector->SetItemText(0, buttonText[0]);
	selector->SetItemText(1,buttonText[1]);
	selector->SetItemText(2, buttonText[2]);
	selector->SetItemText(3, buttonText[3]);	
	selectorTrigger = new SelectorTrigger(this);
	selector->SetOnClickDelegate(selectorTrigger);


	CXrDivider* divider;
	divider = new CXrDivider(panel_width*0.8, 1, 0);
	ITextLayer* text;
	divider->Add(m_node, bottomLayerId, InsertFlag_Child, button_start_x, -15);
	Int32 textMtlId = m_node->CreateUIFontMaterial(XR_RES"mcg.ttf", 0);

	int textId = m_node->CreateTextLayer(bottomLayerId, InsertFlag_Child,textMtlId, 1.0, button_start_x, -60, &text, 26);
 	text->SetText("Camera Direction");
#if 0
    BottomRootLayer->SetOpacity(0.0);
	selector->SetOpacity(0.0);
#endif

    return 0;
}
#define ALI_BUTTON_SIZE_WIDTH 90
#define ALI_BUTTON_SIZE_HEIGHT 85
#define ALI_BUTTON_START_Y_FR  30
#define ALI_BUTTON_START_X_LR  25
#define ALI_BUTTON_BLACK_RATIO_X 0.28
#define ALI_BUTTON_BLACK_RATIO_Y  0.36
int SVUI::InitAliCtrlPanel()
{
	int panel_x, panel_y,panel_width,panel_height;
	int button_start_x_fr,button_start_y_fr,button_width,button_height,button_interval_fr;
	int button_start_x_lr,button_start_y_lr,button_interval_lr;
	ILayer *pAliCtrlLayer;
	panel_x = 0;//*m_bev_config.smc_hmi.BOTTOM_PANEL_POSITION_X;
	panel_y = m_screen_height/2;//*m_bev_config.smc_hmi.BOTTOM_PANEL_POSITION_Y;

	panel_width = m_screen_width/2;//*m_bev_config.smc_hmi.BOTTOM_PANEL_WIDTH;
	panel_height = m_screen_height/2;//*m_bev_config.smc_hmi.BOTTOM_PANEL_HEIGHT;
	

	button_start_x_fr =panel_width/2.0-ALI_BUTTON_SIZE_WIDTH/2.0;
	button_start_y_fr = ALI_BUTTON_START_Y_FR;
	button_width = ALI_BUTTON_SIZE_WIDTH;
	button_height = ALI_BUTTON_SIZE_HEIGHT;
	button_interval_fr =(1.0-ALI_BUTTON_BLACK_RATIO_Y)*panel_height;



	Int32 CtrlLayrId = m_node->CreateSpirit(-1, InsertFlag_Default, -1, 1.0, panel_x, panel_y, 0 ,panel_width, panel_height); 
	pAliCtrlLayer = m_node->GetLayer(CtrlLayrId);
	pAliCtrlLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);

	

	AliCtrlSelFB  = new CXrSelector(8);
	AliCtrlSelFB->Add(m_node, CtrlLayrId, InsertFlag_Child, button_start_x_fr, button_start_y_fr, button_width, button_height, 0, button_interval_fr, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 2, 1);

	AliCtrlSelFB->SetItemText(0, buttonText[0]);
	AliCtrlSelFB->SetItemText(1,buttonText[1]);

	button_start_x_fr =ALI_BUTTON_START_X_LR;
	button_start_y_fr = panel_height/2-ALI_BUTTON_SIZE_HEIGHT/2.0-18;

	button_interval_fr =(1.0-ALI_BUTTON_BLACK_RATIO_X)*panel_width/2;

    AliCtrlSelLR = new CXrSelector(8);
	AliCtrlSelLR->Add(m_node, CtrlLayrId, InsertFlag_Child, button_start_x_fr, button_start_y_fr, button_width, button_height, button_interval_fr, 0, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 3);
	
	
	AliCtrlSelLR->SetItemText(0, buttonText[2]);
	AliCtrlSelLR->SetItemText(1, buttonText[3]);
	
	m_AliCtrlTriggerFB = new AliCtrlTriggerFB(this);
	AliCtrlSelFB->SetOnClickDelegate(m_AliCtrlTriggerFB);


    m_AliCtrlTriggerLR= new AliCtrlTriggerLR(this);
    AliCtrlSelLR->SetOnClickDelegate(m_AliCtrlTriggerLR);

pAliCtrlLayer->SetOpacity(0.0);
AliCtrlSelLR->SetOpacity(0.0);
AliCtrlSelFB->SetOpacity(0.0);

#if 0
	BottomRootLayer->SetOpacity(0.0);
	selector->SetOpacity(0.0);
#endif

	return 0;
}

int SVUI::InitAutoshowProductPanel()
{
	static char* settingText[] = {
	"SSR", "IFV", "ESR", "BEV" };

	Int32 lid = m_node->CreateSpirit(settingspanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, SETTINGSPANEL_WIDTH, SETTINGSPANEL_HEIGHT);
	settingsSubContentLayer = m_node->GetSpirit(lid);
	settingsSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);


	Productselector= new CXrSelector(2);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	Productselector->Add(m_node, lid, InsertFlag_Child, (SETTINGSPANEL_WIDTH-PRODUCT_BUTTON_WIDTH)/2, PRODUCT_BUTTON_INT, PRODUCT_BUTTON_WIDTH, PRODUCT_BUTTON_HEIGHT, 0, PRODUCT_BUTTON_INT+PRODUCT_BUTTON_HEIGHT, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 4, 1);
	Productselector->SetItemText(0, settingText[0]);
	Productselector->SetItemText(1,settingText[1]);
	Productselector->SetItemText(2, settingText[2]);
	Productselector->SetItemText(3, settingText[3]);	
	Productselector->SetTextSize(15);
	
	pProductSelectTrigger= new ProductSelectorTrigger(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	Productselector->SetOnClickDelegate(pProductSelectTrigger);
    return 0;
}
int SVUI::InitPositionAdjustPanel()
{
	 int lid;
	 /////////////Position Panel////////////////////
	 positionpanel = new CXrPanel(4);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 positionpanel->Add(m_node, -1, InsertFlag_Default, POSITIONPANEL_X, POSITIONPANEL_Y_FADEOUT, POSITIONPANEL_WIDTH, POSITIONPANEL_HEIGHT, 0.4, XR_RES"BC64.dds");
	 lid = m_node->CreateSpirit(positionpanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, POSITIONPANEL_WIDTH, POSITIONPANEL_HEIGHT);
	 PositionSubContentLayer = m_node->GetSpirit(lid);
	 PositionSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);
	 
	 static char* PositionText[] = {
	 "X+", "Y+","Z+", "RotX+","RotY+","RotZ+","Save","ZoomIn" "X-","Y-", "Z-", "RotX-", "RotY-","RotZ-","Cancel","ZoomOut"};
	 
	 
	 
	 ProductPositionselector= new CXrSelector(2);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 ProductPositionselector->Add(m_node, lid, InsertFlag_Child, (POSITIONPANEL_WIDTH-2*POSITION_BUTTON_WIDTH)/3, POSITION_BUTTON_INT, POSITION_BUTTON_WIDTH, POSITION_BUTTON_HEIGHT, (POSITIONPANEL_WIDTH+POSITION_BUTTON_WIDTH)/3, POSITION_BUTTON_INT+POSITION_BUTTON_HEIGHT, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 8, 2);
	 for(int i =0;i<16;i++)
	 {
		 ProductPositionselector->SetItemText(i, PositionText[i]);
	
	 }
	
	 ProductPositionselector->SetTextSize(15);
	 
	 pProductPositionTrigger= new ProductPositionTrigger(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	// ProductPositionselector->SetOnClickDelegate(pProductPositionTrigger);
	 return 0;


}

int SVUI::InitUI()
{


	
	/////////////Settings Panel////////////////////
	settingspanel = new CXrPanel(4);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	settingspanel->Add(m_node, -1, InsertFlag_Default, SETTINGSPANEL_X, SETTINGSPANEL_Y_FADEOUT, SETTINGSPANEL_WIDTH, SETTINGSPANEL_HEIGHT, 0.4, XR_RES"BC64.dds");
    Int32 lid;
	

	IAProperty* ap_y=0;
	settingsRootLayer = settingspanel->GetRoot();
	settingsRootLayer->GetCAProperty(AP_Y, &ap_y);
	pADOnSettingsShowHide = new ADOnSettingsShowHide(this);
	
	// buffer file %s,line %d",__FILE__,__LINE__);
	ap_y->SetAPDelegate(pADOnSettingsShowHide);
    //InitAutoshowProductPanel();
	//InitStylePanel();
	InitStylePanelAli();
    InitCamDirPanel();
	InitModeSelPanel();
	//InitLiscenseKeyboard();
    //InitModelPanel();
    //InitColorPanel();

	//InitSideProductPanel();

//	InitModeSelectPanel();

//      InitSideControltPanel();
	InitZoomPanel();

    InitCANSimulatePanel();
   InitTopPanelAli();
   InitLiscenseKeyboard();
//	InitBottomPanel();
	//InitAliCtrlPanel();
	


	return 0;
}
#define KEY_BOARD_CONER_SIZE 3
void SVUI::InitLiscenseKeyboard()
{
	Int32 lid;
	IActionTrigger* style_trigger_temp[4];

//m_chinese_index = 1;

#define KEY_BOARD_X_OFFSET 360
#define KEY_BOARD_Y_OFFSET 80


     liscensePanel=new CXrPanel(16,1,TRUE);
	 // buffer file %s,line %d",__FILE__,__LINE__);

	 liscensePanel->Add(m_node, -1, InsertFlag_Default, LISCENSEPANEL_X, LISCENSEPANEL_Y_FADEOUT, LISCENSEPANEL_WIDTH, LISCENSEPANEL_HEIGHT, 0.4, XR_RES"c128b1.dds");
#if 0

	 liscensePanel=new CXrPanel(-1,1,TRUE);
	 // buffer file %s,line %d",__FILE__,__LINE__);

	 liscensePanel->Add(m_node, -1, InsertFlag_Default, LISCENSEPANEL_X, LISCENSEPANEL_Y_FADEOUT, 840, 360, 0.4, XR_RES"test.dds");
#endif


	 lid = m_node->CreateSpirit(liscensePanel->GetRootId(), InsertFlag_Child, -1, 0.0, 0, 0, 0, LISCENSEPANEL_WIDTH, LISCENSEPANEL_HEIGHT);
	 liscenceSubContentLayer = m_node->GetSpirit(lid);
	 liscenceSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);

	 CXrDivider* keyborddivide[10];
	 
	 keyborddivide[0] = new CXrDivider(780, 1, 0);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyborddivide[0]->Add(m_node, lid, InsertFlag_Child, 30, 70);

	 keyborddivide[1] = new CXrDivider(250, 0, 0);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyborddivide[1]->Add(m_node, lid, InsertFlag_Child, 335, 90);
	 style_trigger_temp[0]=new DockTriggerLiscenseKeyboard1(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 style_trigger_temp[1]=new DockTriggerLiscenseKeyboard2(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 style_trigger_temp[2]=new DockTriggerLiscenseKeyboard3(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 style_trigger_temp[3]=new DockTriggerLiscenseKeyboard4(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);

     for(int j=0;j<2;j++)
     {
    	 keyboard[j] = new CXrSelector(KEY_BOARD_CONER_SIZE);
		 
		 // buffer file %s,line %d",__FILE__,__LINE__);
    	 keyboard[j]->Add(m_node, lid, InsertFlag_Child, 10+KEY_BOARD_X_OFFSET, 16+50*j+KEY_BOARD_Y_OFFSET, 32, 32, 50, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 10);

             for(int i=0;i<10;i++)
             {
        	     keyboard[j]->SetItemText(i, liscenceText[i+10*j]);
        	 }

    	 keyboard[j]->SetOnClickDelegate(style_trigger_temp[j]);
     }
	 
	 keyboard[2] = new CXrSelector(KEY_BOARD_CONER_SIZE);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyboard[2]->Add(m_node, lid, InsertFlag_Child, 35+KEY_BOARD_X_OFFSET, 16+50*2+KEY_BOARD_Y_OFFSET, 32, 32, 50, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 9);
     for(int i=0;i<9;i++)
     {
	     keyboard[2]->SetItemText(i, liscenceText[i+20]);
	 }    
	 keyboard[2]->SetOnClickDelegate(style_trigger_temp[2]);	

	 keyboard[3] = new CXrSelector(KEY_BOARD_CONER_SIZE);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyboard[3]->Add(m_node, lid, InsertFlag_Child, 70+KEY_BOARD_X_OFFSET, 16+50*3+KEY_BOARD_Y_OFFSET, 32, 32, 50, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 7);
     for(int i=0;i<7;i++)
     {
	     keyboard[3]->SetItemText(i, liscenceText[i+29]);
	 }    
	 keyboard[3]->SetOnClickDelegate(style_trigger_temp[3]);	 
     for(int i=0;i<30;i++)
     {
         m_selected_liscense[i]=0;
     }
	 keyboard[4] = new CXrSelector(KEY_BOARD_CONER_SIZE);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyboard[4]->Add(m_node, lid, InsertFlag_Child, 120+KEY_BOARD_X_OFFSET, 16+50*4+KEY_BOARD_Y_OFFSET, 100, 32,120, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 2);
     for(int i=0;i<2;i++)
     {
	     keyboard[4]->SetItemText(i, liscenceText[i+36]);
	 }    
	 style_trigger_temp[3] = new DockTriggerLiscenseKeyboard5(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyboard[4]->SetOnClickDelegate(style_trigger_temp[3]);	 	 
	 TextOutput = new CXrTextLable(KEY_BOARD_CONER_SIZE);;
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 TextOutput->Add(m_node, lid, InsertFlag_Child, 480, 12, 200, 40, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");;
    // m_selected_liscense = "Lalala";
	 TextOutput->SetText(m_selected_liscense);


	 style_trigger_temp[3] = new DockTriggerLiscenseChinese(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
     
	 keyboard[5] = new CXrSelector(KEY_BOARD_CONER_SIZE);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 keyboard[5]->AddChinese(m_node, lid, InsertFlag_Child, 30,16+KEY_BOARD_Y_OFFSET, 32, 32, 40, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 5, 7);
     for(int i=0;i<35;i++)
     {
	    keyboard[5]->SetChineseItemText(i,i);
	   // keyboard[5]->SetItemText(i,liscenceText[i]);
	 }    
	 keyboard[5]->SetOnClickDelegate(style_trigger_temp[3]);	 	 

	  ChineseTextOutput = new CXrTextLable(KEY_BOARD_CONER_SIZE);;
	  
	  // buffer file %s,line %d",__FILE__,__LINE__);
	  ChineseTextOutput->AddChinese(m_node, lid, InsertFlag_Child,420, 12, 50, 40, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");;
	 // ChineseTextOutput->SetText(50);

//divder

}

void SVUI::InitModelPanel()
{
	Int32 lid;
	IActionTrigger* style_trigger_temp[4];
     char *Text[4]={"SUV","CAR","TRUCK","UFO"};

#define MODEL_PANEL_X_OFFSET 20
#define MODEL_PANEL_Y_OFFSET 10
   //step one create panel
     m_pCarModelPanel=new CXrPanel(4);
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pCarModelPanel->Add(m_node, -1, InsertFlag_Default, MODEL_X_FADE_OUT, MODEL_Y, 140,200, 0.0, XR_RES"BC64.dds");
	 lid = m_node->CreateSpirit(m_pCarModelPanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 140, 200);

	 m_ModelSubContentLayer = m_node->GetSpirit(lid);
	 m_ModelSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);

	 style_trigger_temp[0]=new DockTriggerModelPanel(this);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 style_trigger_temp[1]=0;
	 style_trigger_temp[2]=0;
	 style_trigger_temp[3]=0;


	 m_pModelSelect = new CXrSelector(4);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pModelSelect->Add(m_node, lid, InsertFlag_Child, MODEL_PANEL_X_OFFSET, MODEL_PANEL_Y_OFFSET, 100, 32, 50, 50, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 4, 1);

         for(int i=0;i<4;i++)
         {
             m_pModelSelect->SetTextSize(15);
    	     m_pModelSelect->SetItemText(i, Text[i]);
    	 }

	m_pModelSelect->SetOnClickDelegate(style_trigger_temp[0]);
	 
	 // ChineseTextOutput->SetText(50);

//divder

}
void SVUI::InitColorPanel()
{
	Int32 lid;
	IActionTrigger* style_trigger_temp;
     char *Text[5]={"RED","BLACK","WHITE","GRAY","YELLOW"};

#define COLOR_PANEL_X_OFFSET 20
#define COLOR_PANEL_Y_OFFSET 10
   //step one create panel
     m_pCarColorPanel=new CXrPanel(4);
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pCarColorPanel->Add(m_node, -1, InsertFlag_Default, COLOR_X_FADE_OUT, COLOR_Y, 140,230, 0.0, XR_RES"BC64.dds");
	 lid = m_node->CreateSpirit(m_pCarColorPanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 140, 230);

	 m_ColorSubContentLayer = m_node->GetSpirit(lid);
	 m_ColorSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);

	 style_trigger_temp =new DockTriggerColorPanel(this);

	 // buffer file %s,line %d",__FILE__,__LINE__);


	 m_pColorSelect = new CXrSelector(4);
	 
	 // buffer file %s,line %d",__FILE__,__LINE__);
	 m_pColorSelect->Add(m_node, lid, InsertFlag_Child, COLOR_PANEL_X_OFFSET, COLOR_PANEL_Y_OFFSET, 100, 32, 50, 42, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 5, 1);

         for(int i=0;i<5;i++)
         {
             m_pColorSelect->SetTextSize(15);
    	     m_pColorSelect->SetItemText(i, Text[i]);
    	 }

	m_pColorSelect->SetOnClickDelegate(style_trigger_temp);
	 
	 // ChineseTextOutput->SetText(50);

//divder

}

int SVUI::Update(int param1, int param2)
{
	navigator->Update();
	return 0;
}



void SVUI::OnMouseDown(int x, int y)
{
	m_prevX = x;
	m_prevY = y;
}

void SVUI::OnMouseUp(int x, int y)
{
	m_prevX = x;
	m_prevY = y;
}

void SVUI::OnMouseMove(int x, int y)
{
	m_prevX = x;
	m_prevY = y;
}
#define LOGO_WIDTH 200
#define LOGO_HEIGHT 100
void SVUI::InitLogo()
{
	m_pLogoPanel=new CXrPanel(-1);
	int lid;
	ILayer *ptemp;


	#if 0
	// buffer file %s,line %d",__FILE__,__LINE__);
	stylepanel->Add(m_node, -1, InsertFlag_Default, STYLEPANEL_X, STYLEPANEL_Y_FADEIN, 205, 200, 0.4, XR_RES"test.dds");
	lid = m_node->CreateSpirit(stylepanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 205, 640);
	
	styleSubContentLayer = m_node->GetSpirit(lid);
	styleSubContentLayer->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_OPACITY);	
	#endif
	// buffer file %s,line %d",__FILE__,__LINE__);
	m_pLogoPanel->Add(m_node, -1, InsertFlag_Default, 640-LOGO_WIDTH/2, 360-LOGO_HEIGHT/2, LOGO_WIDTH,LOGO_HEIGHT, 0.2, XR_RES"ofilm.dds");
	lid = m_node->CreateSpirit(m_pLogoPanel->GetRootId(), InsertFlag_Child, -1, 0, 0, 0, 0, 140, 230);
	ptemp = m_node->GetLayer(lid);
	ptemp->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_X | AP_Y | AP_OPACITY);

ptemp->SetOpacity(1.0);



}


void SVUI::InitEffect()
{
	Int32 nodeId;
	//nodeId = g_pIXrCore->CreateRenderNodeEffect(RenderNodeType_Effect_Ripple, &m_rippleNode);
	//nodeId = g_pIXrCore->CreateRenderNodeEffect(RenderNodeType_Effect_Frost, &m_frostNode);

	//m_frostNode->SetEnable(FALSE);
	//m_rippleNode->SetEnable(FALSE);
	m_ripple = FALSE;
	m_frost = FALSE;
}
void SVUI::ToggleFrost()
{
	if (m_frost) {
		//m_frostNode->SetEnable(FALSE);
		m_frost = FALSE;
	}
	else {
		m_frost = TRUE;
		//m_frostNode->SetEnable(TRUE);
	}
}
void SVUI::ToggleRipple()
{
	if (m_ripple) {
		//m_rippleNode->SetEnable(FALSE);
		m_ripple = FALSE;
	}
	else {
		m_ripple = TRUE;
		//m_rippleNode->SetEnable(TRUE);
	}
}
