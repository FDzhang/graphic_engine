
#include "AVMData.h"
#include "SVNodeAdasHmi.h"

/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
extern Region CenterReg;
extern Region RightReg;

st_text_box_data_T gpu_debug_texbox;

void SVNodeAdasHMI::Init(BEV_CONFIG_T  pConfig,ISceneNode *pSencenode,ISceneNode *pStichSencenode,st_ADAS_Mdl_HMI_T **pAdasMdlHmiHandleHead,int HmiMdlNum)
{
    int nodeId,temp;
	int j=0;
	st_ADAS_Mdl_HMI_T *pAdasMdlHmiHandle;
    gpu_debug_texbox.line_num=6;
	gpu_debug_texbox.font_size =40;
	gpu_debug_texbox.pos[0] =870;
	gpu_debug_texbox.pos[1] = 100;
	gpu_debug_texbox.show_flag = 1;
	gpu_debug_texbox.text_color[0]=0.0;
	gpu_debug_texbox.text_color[1]=1.0;
	gpu_debug_texbox.text_color[2]=0.0;
    gpu_debug_texbox.width = 600;
    gpu_debug_texbox.text_content[0] = new char [200];
    gpu_debug_texbox.text_content[1] = new char [200];
	gpu_debug_texbox.text_content[2] = new char [200];
	gpu_debug_texbox.text_content[3] = new char [200];
	gpu_debug_texbox.text_content[4] = new char [200];
	gpu_debug_texbox.text_content[5] = new char [200];
	if(NULL==pAdasMdlHmiHandleHead)
	{
	    m_hmi_enable = 0;
        return;
	}
	
	pAdasMdlHmiHandle = *pAdasMdlHmiHandleHead;
	m_hmi_enable = 1;



	
    m_pTextBox = new HMITextBox(CenterReg,RightReg);

	nodeId = g_pIXrCore->CreateRenderNodeUI(RenderNodeType_UI2D, 0, &m_AdasHMINode);
	m_pIconBox = new HMIIconBox(CenterReg,RightReg);
    m_pIconBox->Init(m_AdasHMINode);
	
	m_pTextBox->Init(m_AdasHMINode,XR_RES"text_frame.dds",XR_RES"text_box.ttf");
	
	m_pScrollBox = new HMIScrollBox(CenterReg,RightReg);
	m_pScrollBox->Init(pSencenode);

	m_pLdwLine = new HMILDWLine(CenterReg,RightReg);
	m_pLdwLine->Init(pStichSencenode,0,-4,8);

	m_pSingleviewRect = new HMISingleviewRect(CenterReg,RightReg);
    m_pSingleviewRect->Init(pSencenode,0);
	m_pBSDRadarIcon = new HMIBSDRadarIcon(CenterReg,RightReg);
	m_pBSDRadarIcon->Init(m_AdasHMINode);

    for(int i =0;i<HmiMdlNum;i++)
    {
    
	    pAdasMdlHmiHandle = *(pAdasMdlHmiHandleHead+i);
        for(j=0;j<pAdasMdlHmiHandle->icon_num;j++)
        {
            m_pIconBox->Add(m_AdasHMINode,&(pAdasMdlHmiHandle->pStaticIcon[j]));
        }

    	for(j=0;j<pAdasMdlHmiHandle->text_box_num;j++)
    	{
    		m_pTextBox->Add(m_AdasHMINode,&(pAdasMdlHmiHandle->pTextBox[j]),&temp);
    	}

    	for(j=0;j<pAdasMdlHmiHandle->ldw_line_num;j++)
    	{
    		m_pLdwLine->Add(pStichSencenode,&(pAdasMdlHmiHandle->pLDWLine[j]));
    	}

    	for(j=0;j<pAdasMdlHmiHandle->single_view_rect_num;j++)
    	{
    		m_pSingleviewRect->Add(pSencenode,&(pAdasMdlHmiHandle->pSingleviewRect[j]));
    	}

    	for(j=0;j<pAdasMdlHmiHandle->scroll_rect_num;j++)
    	{
    		m_pScrollBox->Add(pSencenode,&(pAdasMdlHmiHandle->pScrollRect[j]));
    	}

    	for(j=0;j<pAdasMdlHmiHandle->BSD_radar_num;j++)
    	{
    		m_pBSDRadarIcon->Add(m_AdasHMINode,&(pAdasMdlHmiHandle->pBSDRadar[j]));
    	}
		
    }
	
	//m_pTextBox->Add(m_AdasHMINode,&gpu_debug_texbox,&temp);
	
}
int SVNodeAdasHMI::Update(void)
{
	if(0==m_hmi_enable)
	{
	   
        return 0;
	}

    m_pTextBox->Update();
	m_pIconBox->Update();
	m_pScrollBox->Update();
	m_pLdwLine->Update();
	m_pSingleviewRect->Update();
	m_pBSDRadarIcon->Update();

	m_AdasHMINode->SetEnable(0);
	return 0;
}
void SVNodeAdasHMI::SetEnable(unsigned char flag)
{
     m_AdasHMINode->SetEnable(flag);
     //m_pSingleviewRect->SetEnable(flag);

    // m_pScrollBox->SetEnable(flag);
}

