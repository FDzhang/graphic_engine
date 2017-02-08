#include "CAnimationManager.h"
#include "../XrNode/Animation/CAProperty.h"
#include "../XrNode/Animation/CScrollingAnimation.h"
#include "../XrNode/Animation/CKeyAnimation.h"
#include "../Common/xrDataStruct.cpp"
#include "../External/IUpdateDelegate.h"

CAnimationManager::CAnimationManager()
: m_PrevTime(0)
{
	ActiveHeader = 0;
	FreeHeader = 0;
	QueueHeader = 0;
}

CAnimationManager::~CAnimationManager()
{
    CATransition* temp;
    XrASSERT(!ActiveHeader);

    while (FreeHeader) {
        temp = FreeHeader;
        FreeHeader = FreeHeader->GetNext();
        delete temp;
    }

	for (m_animation.First();!m_animation.IsDone();m_animation.Next()) {
		CBaseAnimation* ani = m_animation.GetCurrent();
		delete ani;
	}
}

Int32 CAnimationManager::CreateAnimation(            
		/* [in] */ Int32 from,
        /* [in] */ Int32 to,
        /* [in] */ Int32 beginFrame,
        /* [in] */ Int32 repeatCount,
        /* [in] */ Boolean autoReverse,
        /* [in] */ Int32 style,
        /* [in] */ Int32 duration,
		/* [in] */ Int32 animeType)
{
	return XR_OK;
}


Int32 CAnimationManager::CreateScrollingAnimation(
    /* [out] */ class IScrollingAnimation**  ppIScrollingAnimation)
{
	CScrollingAnimation* scroll = new CScrollingAnimation();
	if (scroll) {
		*ppIScrollingAnimation = scroll;
		return AddAnimation(scroll);
	}
	else return -1;
}

Int32 CAnimationManager::CreateAnimationStack(CAnimationStack** ppStack)
{
	CAnimationStack* stack = new CAnimationStack();
	if (ppStack) {
		*ppStack = stack;
		return AddAnimation(stack);
	}
	else return -1;
}


Int32 CAnimationManager::CreateKeyAnimation(            
		/* [in] */ Float32 *key, 
		/* [in] */ Int32 keyNum, 
		/* [in] */ Int32 timeLineNum,
		/* [out] */ IKeyAnimation** ppIKeyAnimation,
        /* [in] */ AnimationStyle style,
		/* [in] */ Boolean loop)
{
	CKeyAnimation* keyAnimation = new CKeyAnimation();
	if (keyAnimation) {
		keyAnimation->CreateTimeLines(key, keyNum, timeLineNum, style, loop);
		if (ppIKeyAnimation) *ppIKeyAnimation = keyAnimation;
		return AddAnimation(keyAnimation);
	}
	else return -1;
}

CATransition* CAnimationManager::AquireTransition(AnimationStyle style, UInt32 duration, TransitionInfo* updater)
{
	CATransition* returned=0;
	CATransition* temp=QueueHeader;
	Boolean Merged = FALSE;
	while (temp) {
		if (temp->TryAdd(style, duration, updater)) {
			Merged = TRUE;
			break;
		}
		else {
			temp = temp->GetNext();
		}
	}

	if (Merged) return temp;

    if (FreeHeader) {
        returned = FreeHeader;
        FreeHeader->Remove(&FreeHeader);
    }
    else {
        returned = new CATransition;
    };

	if (QueueHeader) QueueHeader->InsertAfter(returned);
	else QueueHeader = returned;
	returned->SetNew(style, duration, updater);
    return returned;
}

Void CAnimationManager::ReleaseTransition(CATransition* tran)
{
	tran->Remove(&ActiveHeader);

    if (FreeHeader) {
        FreeHeader->InsertAfter(tran);
    }
    else {
        FreeHeader = tran;
    }
}

Void CAnimationManager::FlushTransition()
{
	if (QueueHeader) {
		if (ActiveHeader) ActiveHeader->Append(QueueHeader);
		else ActiveHeader = QueueHeader;
		QueueHeader = 0;
	}
}

Void CAnimationManager::Update()
{
	UInt32 time = XrGetTime();
	UInt32 deltatime = time - m_PrevTime;
	m_PrevTime = time;
	CATransition* pTransition, *temp;
	FlushTransition();
	//xrprint("update time = %d!!!\n", time);
	pTransition = ActiveHeader;

	if (pTransition) {
		do {
			temp = pTransition;
			pTransition = pTransition->GetNext();
			if (!temp->Update(time)) ReleaseTransition(temp);
		} while (pTransition);
	}
    for (m_animation.First(); !m_animation.IsDone(); m_animation.Next()) {
        if (m_animation.GetCurrent()->IsActive()) {
            m_animation.GetCurrent()->Update(time);
        }
    }

	for (m_update.First(); !m_update.IsDone(); m_update.Next()) {
           m_update.GetCurrent()->OnUpdate();
    }
}



Int32 CAnimationManager::AddAnimation(CBaseAnimation* animation)
{
	return m_animation.Add(animation);
}

Void CAnimationManager::RemoveAnimation(Int32 animeId)
{
	m_animation.Remove(animeId);
}

Int32 CAnimationManager:: AddUpdate(IUpdateDelegate* update)
{
	return m_update.Add(update);
}

Void CAnimationManager::RemoveUpdate(Int32 updateId)
{
	m_update.Remove(updateId);
}
