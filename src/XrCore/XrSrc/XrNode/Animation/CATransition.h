#ifndef __CATRANSITION_H__
#define __CATRANSITION_H__
#include "CSeriesGenerator.h"
class CAProperty;

class CATransition : public CBiLinkNode<CATransition>, public CSeriesGenerator
{
public:
	CATransition() { m_updateLinkHeader = 0; }
	Void Reset()  { m_updateLinkHeader = 0; }
	Boolean TryAdd(AnimationStyle style, UInt32 duration, class TransitionInfo* updater);
	Void SetNew(AnimationStyle style, UInt32 duration, TransitionInfo* updater);
	Boolean Update(UInt32 timeStamp);
	Boolean ExcludeSharing(TransitionInfo* updater);

private:
	TransitionInfo*				m_updateLinkHeader;
};

#endif  //__CATRANSITION_H__

