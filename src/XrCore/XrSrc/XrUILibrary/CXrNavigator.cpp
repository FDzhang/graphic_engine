#include "CXrNavigator.h"
#include "CXrDivider.h"
#define UNSELOPACITY 0.7
#define SELOPACITY 1.0
#define CIRCLE_OPACITY 0.3
xr_state CXrNavigator::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 interval, Float32 opacity, String tex1, String tex2, String tex3, Int32 count,bool tex_same_flag)
{
	IMaterial* pMtl=0;
	ISpirit* pLayer=0;
	Int32 mtlIndex[3];
	Int32 posx, posy, len;
	m_itemW = w;
	m_itemH = h;
	m_interval = interval;
	m_itemNum = count;
	m_node = node;
	m_mtl1[0] = node->CreateUIMaterial(Material_AlphaShape, tex1);
	m_mtl2[0] = node->CreateUIMaterial(Material_AlphaShape, tex2);
	m_mtl3[0] = node->CreateUIMaterial(Material_AlphaShape, tex3);
	m_textMtl = node->CreateUIFontMaterial(XR_RES"zephyrea.ttf", 0);

	m_item = new NavigatorItem[count];
	
	Int32 dx=0;
	if (m_isHorizontal)  m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,(w+interval)*count,h);
	else m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w,(h+interval)*count);
	m_root = node->GetLayer(m_rootId);

	for (Int32 cnt=0;cnt<count;cnt++) {

#define INNER_SCALE 1.14
		if (m_isHorizontal) {
			posx = w/2+dx;
			posy = h/2;
			len = w;
		}
		else {
			posx = w/2;
			posy = h/2+dx;
			len = h;
		}
				
		if(tex_same_flag)
		{
			mtlIndex[0]=m_mtl1[0];
			mtlIndex[1]=m_mtl2[0];
			mtlIndex[2]=m_mtl3[0];
		}
        else
        {
            mtlIndex[0]=m_mtl1[cnt];
			mtlIndex[1]=m_mtl2[cnt];
			mtlIndex[2]=m_mtl3[cnt];
        }

		m_item[cnt].m_layerId1 = node->CreateSpirit(m_rootId, InsertFlag_Child, mtlIndex[0], UNSELOPACITY, posx, posy, 0 ,w,h);
		pLayer = node->GetSpirit(m_item[cnt].m_layerId1);
		pLayer->SetAnchorPoint(0.5,0.5);
		pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);
		pLayer->SetOpacity(UNSELOPACITY);
		//m_item[cnt].m_layerId2 = node->CreateSpirit(m_rootId, InsertFlag_Child, mtlIndex[1], UNSELOPACITY, posx, posy, 0 ,w/INNER_SCALE,h/INNER_SCALE);
		//pLayer = node->GetSpirit(m_item[cnt].m_layerId2);
		//pLayer->SetAnchorPoint(0.5,0.5);
		//pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);
		//pLayer->SetOpacity(UNSELOPACITY);

		m_item[cnt].m_baseId = node->CreateSpirit(m_rootId, InsertFlag_Child, mtlIndex[2], 0.3, posx, posy,0 ,w/INNER_SCALE,h/INNER_SCALE);
		pLayer = node->GetSpirit(m_item[cnt].m_baseId);
		pLayer->SetAnchorPoint(0.5,0.5);
		pLayer->SetEventResponder(this);
		pLayer->SetOpacity(0);

		pLayer->SetTransitionStyle(500, AnimationStyle_EaseOut);
		m_item[cnt].m_fontLayerId = node->CreateTextLayer(m_rootId, InsertFlag_Child, m_textMtl, UNSELOPACITY, posx, posy, &m_item[cnt].text, h/4);
		m_item[cnt].text->SetTransitionStyle(500, AnimationStyle_EaseOut);

		dx+= interval+len;

	}
    if(m_selected>=0)
    {
    	pLayer = node->GetSpirit(m_item[m_selected].m_layerId1);
    	pLayer->SetOpacity(1);
    	//pLayer = node->GetSpirit(m_item[m_selected].m_layerId2);
    	//pLayer->SetOpacity(1);
    	pLayer = m_node->GetSpirit(m_item[m_selected].m_baseId);
    	pLayer->SetOpacity(CIRCLE_OPACITY);
    }
	return XR_OK;
}
xr_state CXrNavigator::SetButtonTexture(class IUINode* node ,Int32 count,String tex1, String tex2, String tex3)
{

	m_mtl1[count] = node->CreateUIMaterial(Material_AlphaShape, tex1);
	m_mtl2[count] = node->CreateUIMaterial(Material_AlphaShape, tex2);
	m_mtl3[count] = node->CreateUIMaterial(Material_AlphaShape, tex3);
	return XR_OK;
}
xr_state CXrNavigator::SetInitSelect(Int32 count,unsigned char button_type)
{

    m_selected = count;
	m_pre_selected = count;
	m_button_type = button_type;
	for(int i=0;i<10;i++)
	{
	    m_isSelected[i]=0;
	}

	if(count>=0)
	{
        m_isSelected[count] =1;
	}
	return XR_OK;


}

//static Int32 prevSelect=0;
Void CXrNavigator::Update()
{
	ISpirit* pLayer=0;
	#if 0
	if (prevSelect != m_selected) {
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_layerId1);
		pLayer->SetOpacity(UNSELOPACITY);
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_layerId2);
		pLayer->SetOpacity(UNSELOPACITY);
		m_item[prevSelect].text->SetOpacity(UNSELOPACITY);
		pLayer = m_node->GetSpirit(m_item[prevSelect].m_baseId);
		pLayer->SetOpacity(0);

		pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId1);
		pLayer->SetOpacity(SELOPACITY);
		pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId2);
		pLayer->SetOpacity(SELOPACITY);
		m_item[m_selected].text->SetOpacity(SELOPACITY);
	}
#endif
	//static Float32 delta=0.0;
#if 0
	if (m_selected>=0) {
			pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId1);
			pLayer->RotateDZ(-1);
		//m_item[m_selected].rotation-=1;
	}
#endif
}

Boolean CXrNavigator::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	ILayer* pLayer=0;
	
	for (Int32 i=0;i<m_itemNum;i++) {
		if (layerId==m_item[i].m_baseId) {
			pLayer = m_node->GetSpirit(layerId);
			if (type == TouchEvent_Down) {
				m_selected = i;
				pLayer->SetOpacity(0.7);
				m_trigger->OnPress(i);
			}
			else if (type == TouchEvent_Up) {
				pLayer->SetOpacity(CIRCLE_OPACITY);
				m_trigger->OnRelease(i, true);
        		for(int m=0;m<m_itemNum;m++)
        		{   
					if (m != m_selected)
					{
					
					    m_isSelected[m]= 0;
					}
			    }
				
			    if( m_isSelected[m_selected]==1)
        	    {
        	        m_isSelected[m_selected]= 0;
        	    }
        		else
        		{
        	        m_isSelected[m_selected]= 1;
        		
        		}	
			}

		}
	}
	
	if (m_pre_selected != m_selected&&PULSE_TYPE_BUTTON == m_button_type) 
	{
	    if(-1!= m_pre_selected)
        {
		pLayer = m_node->GetSpirit(m_item[m_pre_selected].m_layerId1);
		pLayer->SetOpacity(UNSELOPACITY);
		//pLayer = m_node->GetSpirit(m_item[m_pre_selected].m_layerId2);
		//pLayer->SetOpacity(UNSELOPACITY);

    		m_item[m_pre_selected].text->SetOpacity(UNSELOPACITY);
    		pLayer = m_node->GetSpirit(m_item[m_pre_selected].m_baseId);
    		pLayer->SetOpacity(0);
        }
		pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId1);
		pLayer->SetOpacity(SELOPACITY);
		//pLayer = m_node->GetSpirit(m_item[m_selected].m_layerId2);
		//pLayer->SetOpacity(SELOPACITY);
		m_item[m_selected].text->SetOpacity(SELOPACITY);
	}
	else if(SWITCH_TYPE_BUTTON == m_button_type)
	{

		for(int i=0;i<m_itemNum;i++)
		{
		    if(m_isSelected[i])
		    {
        		pLayer = m_node->GetSpirit(m_item[i].m_layerId1);
        		pLayer->SetOpacity(SELOPACITY);
        		//pLayer = m_node->GetSpirit(m_item[i].m_layerId2);
        		//pLayer->SetOpacity(SELOPACITY);
        		m_item[i].text->SetOpacity(SELOPACITY);		    
		    }
			else
			{
        		pLayer = m_node->GetSpirit(m_item[i].m_layerId1);
        		pLayer->SetOpacity(UNSELOPACITY);
        		//pLayer = m_node->GetSpirit(m_item[i].m_layerId2);
        		//pLayer->SetOpacity(UNSELOPACITY);
        		m_item[i].text->SetOpacity(UNSELOPACITY);
        		pLayer = m_node->GetSpirit(m_item[i].m_baseId);
        		pLayer->SetOpacity(0);			
			}
		}
	}
		m_pre_selected = m_selected;
	return TRUE;
}

Void CXrNavigator::SetItemText(Int32 num, String text)
{
	Float32 tw, th;
	if (num<0 || num>m_itemNum) return;
	m_item[num].text->SetText(text);
	m_item[num].text->GetTextWH(&tw,&th);
	if (m_isHorizontal) m_item[num].text->SetPosition((m_itemW-tw)/2+(m_interval+m_itemW)*num,th+m_itemH*1.1);
	else m_item[num].text->SetPosition((m_itemW-tw)/2,th+m_itemH*0.9+(m_interval+m_itemH)*num);
}

Void CXrNavigator::Select(Int32 id)
{
	m_selected = id;
	m_trigger->OnPress(id);
	m_node->GetSpirit(m_item[id].m_baseId)->SetOpacity(CIRCLE_OPACITY);
}
