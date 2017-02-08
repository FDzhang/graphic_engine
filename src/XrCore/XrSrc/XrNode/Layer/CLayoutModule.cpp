#include "CLayoutModule.h"
#include "CLayer.h"

CLayoutModule2D::CLayoutModule2D(LayoutMode mode)
{
    m_marginX = 0;
    m_marginY = 0;
    m_intervalX = 0;
    m_intervalY = 0;
    m_mode = mode;
    m_alignModeX = XrAlignMode_Center;
    m_alignModeY = XrAlignMode_Center;
    m_alignedLayerMarginX = 0;
    m_alignedLayerMarginY = 0;
    m_autoSize = 1;
	m_currentX = 0;
	m_currentY = 0;

}

CLayoutModule2D::~CLayoutModule2D()
{

}

Void CLayoutModule2D::Arrange(CLayer* layer)
{
	Float32 width, height, hostWidth;
	Int32 colNum = 0;

    switch (m_mode) {
    case LayoutMode_StackX: 
		m_currentX = 0;
		m_recommendHeight = 0;
		while (layer) {
			ArrangeStackX(layer);
			layer = layer->GetNext();
		}
		if (m_autoSize) {
			m_moduleHost->SetWidth(m_currentX-m_intervalX);
			m_moduleHost->SetHeight(m_recommendHeight);
		}
		break;
	case LayoutMode_StackY: 
		m_currentY = 0;
		m_recommendWidth = 0;
		while (layer) {
			ArrangeStackY(layer);
			layer = layer->GetNext();
		}
		if (m_autoSize) {
			m_moduleHost->SetHeight(m_currentY-m_intervalY);
			m_moduleHost->SetWidth(m_recommendWidth);
		}
		break;
	case LayoutMode_WrapX: 
        hostWidth = m_moduleHost->width.GetDst();
        width, height = layer->height.GetDst();
      	m_currentX = m_marginX;
		m_currentY = m_marginY;  

		while (layer) {
            if (layer->GetEnable()) {
                width = layer->width.GetDst();
                if (m_currentX + width > hostWidth) {
                    m_currentX = m_marginX;
                    m_currentY += height+m_intervalY;
                }
                layer->SetX(m_currentX);
				layer->SetY(m_currentY);
                m_currentX+= layer->width.GetDst() + m_intervalX;
            }
		}
		if (m_autoSize) {
			m_moduleHost->SetHeight(m_currentY-m_intervalY);
		}
		break;
	case LayoutMode_WrapY: 
		break;
	case LayoutMode_Grid:
		while (layer) {
			ArrangeGrid(layer);
			layer = layer->GetNext();
		}
	default:
		break;
	}

}

Void CLayoutModule2D::ArrangeStackX(CLayer* layer)
{
	Float32 width, height;

	layer->MeasureSize(&width, &height);
	layer->SetX(m_currentX);

	//layer->SetY((panelHeight - height - 2*m_marginY)*(m_alignModeY)/2  + m_pHost->m_offset.y + m_marginY);
	
	m_currentX +=width+m_intervalX;
	if (m_recommendHeight < height) m_recommendHeight = height;
}

Void CLayoutModule2D::ArrangeStackY(CLayer* layer)
{
	Float32 width, height;

	layer->MeasureSize(&width, &height);
	layer->SetY(m_currentY);

	//layer->SetY((panelHeight - height - 2*m_marginY)*(m_alignModeY)/2  + m_pHost->m_offset.y + m_marginY);
	
	m_currentY +=height+m_intervalY;
	if (m_recommendWidth < width) m_recommendWidth = width;
}
Void CLayoutModule2D::ArrangeGrid(CLayer* layer)
{
}

Void CLayoutModule2D::ArrangeDock(CLayer* layer)
{
}
