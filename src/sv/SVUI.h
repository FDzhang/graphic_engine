#ifndef __SV_UI_H__
#define __SV_UI_H__
#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "bev_config.h"

#define TOP_DOCK_BUTTON_NUM 5
#define ALI_TOP_DOCK_BUTTON_NUM  6
class SVUI
{
	// The program object containing the 2 shader objects

public:
	SVUI() 
	{
		m_showMode = true;
		m_showSettings = false;
		m_adjustMode =false;
		m_modeAutoHide = false;
		m_showStyle = false;
	    m_showLiscence = false;	
	}
	int InitNode(BEV_CONFIG_T  pConfig,int width,int height);
	int InitUI();
	int UpdateAnimation();
	int Update(int param1, int param2);
	void InitLogo();
	void InitEffect();
	int InitSideControltPanel();
	int InitTopPanelAli();

	void Draw();
	void OnMouseDown(int x, int y);
	void OnMouseUp(int x, int y);
	void OnMouseMove(int x, int y);
	int InitPositionAdjustPanel();
	int InitModeSelectPanel();
	int InitStylePanel();
	int InitAutoshowProductPanel();
	int InitTopPanel();
	int InitBottomPanel();
	int InitAliCtrlPanel();
	int InitCANSimulatePanel();
	void TriggerShowCANSim();

	void TriggerShowMode();
	void TriggerShowSettings();
	void TriggerShowKeyboard(int Id);
	void TriggerShowSideProduct();
	
	void TriggerShowModeSelect();
	int InitSideProductPanel();
	void TriggerShowPosition();
	void TriggerShowLiscence();
	void TriggerShowStyle();
	void OnSettingsShowHide(float position);
	void TriggerAdjustPanel();

	void ToggleRipple();
	void ToggleFrost();
	
	int InitModeSelPanel();
	void InitLiscenseKeyboard();
	void TriggerChineseKeyboard(int Id);
	void InitModelPanel();
	void InitColorPanel();
	void TriggerShowModel();
	
	int InitStylePanelAli();
	void TriggerShowColor();
	int InitZoomPanel();
	void TriggerShowZoom();
	
	void TriggerShowCamDir();
	int InitCamDirPanel();
	CXrSelector* m_pModelSelect;
	CXrSelector* m_pColorSelect;
	CXrSelector* m_pShowFuncSelect;
	CXrSelector* m_pStyleSelect;
	CXrSelector* m_pCamDirSelect;
	CXrSelector* m_pModeSelect;

	CXrSelector* m_pCANSimSelect;
	CXrSelector* m_pZoomSimSelect;

	class SVScene*  svscn;
	Boolean			m_modeAutoHide;
	
	IActionTrigger*				m_dockTrigger[ALI_TOP_DOCK_BUTTON_NUM];
private:
	IUINode*	m_node;
	Int32			m_nodeId;
	CXrPanel *m_pCarModelPanel;
	ISpirit* m_ModelSubContentLayer;
	CXrPanel *m_pCarColorPanel;
	
	CXrPanel *m_pLogoPanel;
	ISpirit* m_ColorSubContentLayer;

	//IRenderNodeEffect*	m_rippleNode;
	//IRenderNodeEffect*	m_frostNode;

	class IActionTrigger*	onPressMode;
	class IActionTrigger*	onPressInfo;
	IActionTrigger*				m_settingTrigger[4];
	IActionTrigger*				m_modeTrigger;
	Boolean		m_showMode;
	Boolean		m_showCANSim;
	Boolean		m_showZoomSim;
	Boolean		m_showCamDir;
	Boolean		m_showModeSel;
	
	char  m_selected_liscense[30];
	unsigned int m_chinese_index;
	Boolean		m_showStyle;
	Boolean		m_showLiscence;
	Boolean		m_showModel;
	Boolean		m_showColor;
	BEV_CONFIG_T m_bev_config;
    int m_screen_width;
	int m_screen_height;
	Boolean		m_showSettings;
	
	Boolean		m_showPosition;
	Boolean		m_showSideProduct;	
	Boolean		m_adjustMode;
	bool				m_frost;
	bool				m_ripple;

	int m_prevX;
	int m_prevY;
};


#endif //__SV_UI_H__
