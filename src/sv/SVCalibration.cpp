#include "SVCalibration.h"
//a#include "XrUILibrary.h"

static CXrButton* TButton[6];
static CXrButton* RButton[6];
static CXrButton* pCButton[2];
static CXrSelector* channelSelector;
static CXrButton* IButton[2];
static char* RButtonText[] = {
	"Q", "W", "E", "A", "S", "D", };
static char* TButtonText[] = {
	"Y", "U", "I", "H", "J", "K", };
static char CButtonText[]="Save";

static int RButtonId[6];
static int TButtonId[6];
static int CButtonId[2];
static CXrPanel* rootpanel;
#define TOTAL_BEV_WIDTH 1280.0
#define TOTAL_BEV_HEIGHT  720.0
#define BUTTON_OPACITY 0.5
#define X_SCALE  (TOTAL_BEV_WIDTH/1024.0)
#define Y_SCALE  (TOTAL_BEV_HEIGHT/768.0)
#define ButtonSize (64*TOTAL_BEV_WIDTH/1024.0)
#define RPosX  (36*TOTAL_BEV_WIDTH/1024.0)
#define RPosY  (380*TOTAL_BEV_HEIGHT/768.0)
#define Interval  8
#define TPosX ( 520*TOTAL_BEV_WIDTH/1024.0)
#define TPosY  RPosY

#define RootX (220*TOTAL_BEV_WIDTH/1024.0)
#define RootWidth (760*TOTAL_BEV_WIDTH/1024.0)

#define RootY -60*Y_SCALE
#define RootDY (120.0*TOTAL_BEV_HEIGHT/768.0)
class ChannelSelectorTrigger : public IActionTrigger
{
public:
	ChannelSelectorTrigger(class SVCalibration* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		m_app->SetChannel(id);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

private:
	SVCalibration* m_app;
};
ChannelSelectorTrigger* selectorTrigger;



#define CALIDELTA 0.0014
#define CALIDELTAT 0.5
class RTButtonTrigger : public IActionTrigger
{
public:
	RTButtonTrigger(SVCalibration* app) { m_app = app; }
	virtual Void OnPress(Int32 id)
	{
		if (id == RButtonId[0])      m_app->SetChangeRZ(CALIDELTA);
		else if (id == RButtonId[1]) m_app->SetChangeRX(CALIDELTA);
		else if (id == RButtonId[2]) m_app->SetChangeRZ(-CALIDELTA);
		else if (id == RButtonId[3]) m_app->SetChangeRY(CALIDELTA);
		else if (id == RButtonId[4]) m_app->SetChangeRX(-CALIDELTA);
		else if (id == RButtonId[5]) m_app->SetChangeRY(-CALIDELTA);
		else if (id == TButtonId[0]) m_app->SetChangeTY(CALIDELTAT);
		else if (id == TButtonId[1]) m_app->SetChangeTX(-CALIDELTAT);
		else if (id == TButtonId[2]) m_app->SetChangeTY(-CALIDELTAT);
		else if (id == TButtonId[3]) m_app->SetChangeTZ(CALIDELTAT);
		else if (id == TButtonId[4]) m_app->SetChangeTX(CALIDELTAT);
		else if (id == TButtonId[5]) m_app->SetChangeTZ(-CALIDELTAT);
		else if (id == CButtonId[0]) m_app->SaveExParam();
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		if (id == RButtonId[0]) m_app->SetChangeRZ(0);
		else if (id == RButtonId[1]) m_app->SetChangeRX(0);
		else if (id == RButtonId[2]) m_app->SetChangeRZ(0);
		else if (id == RButtonId[3]) m_app->SetChangeRY(0);
		else if (id == RButtonId[4]) m_app->SetChangeRX(0);
		else if (id == RButtonId[5]) m_app->SetChangeRY(0);
		else if (id == TButtonId[0]) m_app->SetChangeTY(0);
		else if (id == TButtonId[1]) m_app->SetChangeTX(0);
		else if (id == TButtonId[2]) m_app->SetChangeTY(0);
		else if (id == TButtonId[3]) m_app->SetChangeTZ(0);
		else if (id == TButtonId[4]) m_app->SetChangeTX(0);
		else if (id == TButtonId[5]) m_app->SetChangeTZ(0);
	}

private:
	SVCalibration* m_app;
};
RTButtonTrigger* rtButtonTrigger;

void SVCalibration::Init(IUINode* node, float* exparam,int exparamsize,char *pexparamname)
{
	m_node = node;
	m_exparam = exparam;
	m_exparam_size = exparamsize;
	m_pFileName= pexparamname;
	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	channelSelector = new CXrSelector(8);
	m_show = FALSE;
	/////////////Root Panel////////////////////
	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	rootpanel = new CXrPanel(16, 1, TRUE);
	rootpanel->Add(m_node, -1, InsertFlag_Default, RootX, RootY, RootWidth, 32*Y_SCALE, 1, XR_RES"c128b1.dds");
	//rootpanel->SetOnClickDelegate(rootPanelTrigger);

	Int32 rootId = rootpanel->GetRootId();
	channelSelector->Add(m_node, rootId, InsertFlag_Child, 32*X_SCALE, 20*Y_SCALE, 140*X_SCALE, 32*Y_SCALE, 182*X_SCALE, 0, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds", 1, 4);
	channelSelector->SetItemText(0, "CH0");
	channelSelector->SetItemText(1, "CH1");
	channelSelector->SetItemText(2, "CH2");
	channelSelector->SetItemText(3, "Ch3");
	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	selectorTrigger = new ChannelSelectorTrigger(this);
	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	rtButtonTrigger = new RTButtonTrigger(this);
	channelSelector->SetOnClickDelegate(selectorTrigger);

	CXrDivider* divider;
	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	divider = new CXrDivider(680*Y_SCALE, 1, 0);
	divider->Add(m_node, rootId, InsertFlag_Child, 35*X_SCALE, 67*Y_SCALE);

	for (int i=0;i<6;i++) {
		xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
		RButton[i] = new CXrButton(4);
		RButton[i]->Add(m_node, rootId, InsertFlag_Child, RPosX+(i%3)*(ButtonSize+Interval), RPosY+(i/3)*(ButtonSize+Interval), ButtonSize, ButtonSize, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");
		RButton[i]->SetText(RButtonText[i]);
		RButton[i]->SetActionDelegate(rtButtonTrigger);
		RButtonId[i] = RButton[i]->GetRootId();
	}

	for (int i=0;i<6;i++) {
		xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
		TButton[i] = new CXrButton(4);
		TButton[i]->Add(m_node, rootId, InsertFlag_Child, TPosX+(i%3)*(ButtonSize+Interval), TPosY+(i/3)*(ButtonSize+Interval), ButtonSize, ButtonSize, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");
		TButton[i]->SetText(TButtonText[i]);
		TButton[i]->SetActionDelegate(rtButtonTrigger);
		TButtonId[i] = TButton[i]->GetRootId();
	}

	xrprintf("generate buffer file %s,line %d",__FILE__,__LINE__);
	pCButton[0] = new CXrButton(4);
	pCButton[0]->Add(m_node, rootId, InsertFlag_Child, RPosX+4*(ButtonSize+Interval), TPosY+1*(ButtonSize+Interval),2* ButtonSize, ButtonSize, BUTTON_OPACITY, XR_RES"BC64.dds", XR_RES"WC64.dds");
	pCButton[0]->SetText(CButtonText);
	pCButton[0]->SetActionDelegate(rtButtonTrigger);
	CButtonId[0] = pCButton[0]->GetRootId();

}


void SVCalibration::ToggleShow()
{
	if (!m_show) {
		rootpanel->SetSize(RootWidth,560*Y_SCALE);
		rootpanel->SetDY(RootDY);
		m_show = true;
	}
	else {
		rootpanel->SetSize(RootWidth,32*Y_SCALE);
		rootpanel->SetDY(-RootDY);
		m_show = false;
	}
}
void SVCalibration::SaveExParam()
{
    FILE* FP = fopen(m_pFileName, "wb");
    fwrite(m_exparam, m_exparam_size, 1, FP);
    fclose(FP);

}

