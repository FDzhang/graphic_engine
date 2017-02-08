#ifndef __CLAYOUTMODULE_H__
#define __CLAYOUTMODULE_H__
#include "../../Common/XrInternal.h"

class CLayoutModule2D
{
public:
	CLayoutModule2D(LayoutMode mode);
    ~CLayoutModule2D();

    Void Arrange(CLayer* layer);
	Void AddElement(CLayer* layer);

protected:

	Void ArrangeStackX(CLayer* layer);
	Void ArrangeStackY(CLayer* layer);
	Void ArrangeGrid(CLayer* layer);
	Void ArrangeDock(CLayer* layer);
	//Void ArrangeSquareUp(CLayer* layer);

	CLayer*			m_moduleHost;
    LayoutMode		m_mode;
    Int32           m_alignModeX;
    Int32           m_alignModeY;
    Int32           m_alignedLayerMarginX;
    Int32           m_alignedLayerMarginY;

    Float32         m_marginX;
    Float32         m_marginY;
    Float32         m_intervalX;
    Float32         m_intervalY;
	Float32			m_currentX;
	Float32			m_currentY;
	Float32			m_recommendWidth;
	Float32			m_recommendHeight;

    Int32           m_rowNum;
    Int32           m_columnNum;
    Boolean         m_autoSize;
    Region          m_dockSpace;
};

#endif  //__CLAYOUTMODULE_H__

