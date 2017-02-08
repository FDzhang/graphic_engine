#ifndef __CBASEANIMATION_H__
#define __CBASEANIMATION_H__
#include "CSeriesGenerator.h"

class CBaseAnimation : public CSeriesGenerator
{
public:
	CBaseAnimation():m_receiveEvent(FALSE) {}
	virtual ~CBaseAnimation() {};
	virtual Boolean Update(UInt32 timeStamp);
	Boolean IsActive() { return m_active; }
	Void Deactive() { m_active = FALSE; }
	Int32	GetId() { return m_id; }
	Void SetId(Int32 id) { m_id = id; }
protected:
	Boolean			m_active;
	Boolean			m_receiveEvent;
	Int32			m_id;
};

#endif  //__CBASEANIMATION_H__

