#include "CLayoutPanel.h"

CLayoutPanel::CLayoutPanel(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, LayoutMode mode, CMaterial* pMtl, Float32 opacity):
	CLayer(x, y, z, width, height, pMtl, opacity),
	CLayoutModule2D(mode)
{
	m_layerType = LayerType_LayoutPanel;
	m_moduleHost = this;
	m_self = (Void*)this;
}

CLayoutPanel::~CLayoutPanel()
{

}

Void CLayoutPanel::ReArrange()
{
	Arrange(GetSub());
}

xr_state CLayoutPanel::SetLayoutMode(LayoutMode mode)
{
    m_mode = mode;
	return XR_OK;
}

void CLayoutPanel::SetRowColumnNum(Int32 rowNum, Int32 columnNum)
{
    m_rowNum = rowNum;
    m_columnNum = columnNum;
}

void CLayoutPanel::SetAlignMode(Int32 alignMode, Int32 vhMode)
{
    if (vhMode & VHMode_X) {
        m_alignModeX = alignMode;
    }
    if (vhMode & VHMode_Y) {
        m_alignModeY = alignMode;
    }
}

void CLayoutPanel::SetMargin(Float32 x, Float32 y)
{
    m_marginX = x;
    m_marginY = y;
}

void CLayoutPanel::SetInterval(Float32 x, Float32 y)
{
    m_intervalX = x;
    m_intervalY = y;
}
