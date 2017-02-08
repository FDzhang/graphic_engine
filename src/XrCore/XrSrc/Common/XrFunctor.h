#ifndef _XR_FUNCTOR_H
#define _XR_FUNCTOR_H

#include "XrInternal.h"
class BaseFunctor
{
public:
	//virtual Void operator()() {}
	
};

class GlobalFunctor0 : public BaseFunctor
{
public:
	typedef Void (*Func)();
	GlobalFunctor0(Func f) : m_Func(f) {}
	virtual Void operator()()
	{
		XrAssert(m_Func);
		this->m_Func();
	}

protected:
	Func	m_Func;
};

template<class Arg1>
class GlobalFunctor1 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1);
	GlobalFunctor1(Func f) : m_Func(f) {}
	virtual Void operator()(Arg1 arg1)
	{
		XrAssert(m_Func);
		this->m_Func(arg1);
	}

protected:
	Func	m_Func;
};

template<class Arg1,class Arg2>
class GlobalFunctor2 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1,Arg2 arg2);
	GlobalFunctor2(Func f) : m_Func(f) {}
	Void operator()(Arg1 arg1,Arg2 arg2)
	{
		XrAssert(m_Func);
		this->m_Func(arg1,arg2);
	}

protected:
	Func	m_Func;
};

template<class Arg1,class Arg2>
Void DoGlobalFunctor2(BaseFunctor* functor,Arg1 arg1,Arg2 arg2) 
{
	XrAssert(functor);
	GlobalFunctor2<Arg1,Arg2>* p = static_cast<GlobalFunctor2<Arg1,Arg2>*>(functor);
	(*p)(arg1,arg2);
}
template<class Arg1,class Arg2,class Arg3>
class GlobalFunctor3 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1,Arg2 arg2,Arg3 arg3);
	GlobalFunctor3(Func f) : m_Func(f) {}
	Void operator()(Arg1 arg1,Arg2 arg2,Arg3 arg3)
	{
		XrAssert(m_Func);
		this->m_Func(arg1,arg2,arg3);
	}

protected:
	Func	m_Func;
};

template<class Arg1,class Arg2,class Arg3>
Void DoGlobalFunctor3(BaseFunctor* functor,Arg1 arg1,Arg2 arg2,Arg3 arg3) 
{
	XrAssert(functor);
	GlobalFunctor3<Arg1,Arg2,Arg3>* p = static_cast<GlobalFunctor3<Arg1,Arg2,Arg3>*>(functor);
	(*p)(arg1,arg2,arg3);
}


template<class Arg1,class Arg2,class Arg3,class Arg4>
class GlobalFunctor4 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4);
	GlobalFunctor4(Func f) : m_Func(f) {}
	virtual Void operator()(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4)
	{
		XrAssert(m_Func);
		this->m_Func(arg1,arg2,arg3,arg4);
	}

protected:
	Func	m_Func;
};

template<class Arg1,class Arg2,class Arg3,class Arg4,class Arg5>
class GlobalFunctor5 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5);
	GlobalFunctor5(Func f) : m_Func(f) {}
	virtual Void operator()(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5)
	{
		XrAssert(m_Func);
		this->m_Func(arg1,arg2,arg3,arg4,arg5);
	}

protected:
	Func	m_Func;
};


template<class Arg1,class Arg2,class Arg3,class Arg4,class Arg5,class Arg6>
class GlobalFunctor6 : public BaseFunctor
{
public:
	typedef Void (*Func)(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5,Arg6 arg6);
	GlobalFunctor6(Func f) : m_Func(f) {}
	virtual Void operator()(Arg1 arg1,Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5,Arg6 arg6)
	{
		XrAssert(m_Func);
		this->m_Func(arg1,arg2,arg3,arg4,arg5,arg6);
	}

protected:
	Func	m_Func;
};

inline GlobalFunctor0* make_functor(Void (*f)())
{
	XrAssert(f);
	return new GlobalFunctor0(f);
}
template<class Arg1>
inline GlobalFunctor1<Arg1>* make_functor(Void (*f)(Arg1))
{
	XrAssert(f);
	return new GlobalFunctor1<Arg1>(f);
}
template<class Arg1,class Arg2>
inline GlobalFunctor2<Arg1,Arg2>* make_functor(Void (*f)(Arg1,Arg2))
{
	XrAssert(f);
	return new GlobalFunctor2<Arg1,Arg2>(f);
}

template<class Arg1,class Arg2,class Arg3>
inline GlobalFunctor3<Arg1,Arg2,Arg3>* make_functor(Void (*f)(Arg1,Arg2,Arg3))
{
	XrAssert(f);
	return new GlobalFunctor3<Arg1,Arg2,Arg3>(f);
}

template<class Arg1,class Arg2,class Arg3,class Arg4>
inline GlobalFunctor4<Arg1,Arg2,Arg3,Arg4>* make_functor(Void (*f)(Arg1,Arg2,Arg3,Arg4))
{
	XrAssert(f);
	return new GlobalFunctor4<Arg1,Arg2,Arg3,Arg4>(f);
}

template<class Arg1,class Arg2,class Arg3,class Arg4,class Arg5>
inline GlobalFunctor5<Arg1,Arg2,Arg3,Arg4,Arg5>* make_functor(Void (*f)(Arg1,Arg2,Arg3,Arg4,Arg5))
{
	XrAssert(f);
	return new GlobalFunctor5<Arg1,Arg2,Arg3,Arg4,Arg5>(f);
}

template<class Arg1,class Arg2,class Arg3,class Arg4,class Arg5,class Arg6>
inline GlobalFunctor6<Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>* make_functor(Void (*f)(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6))
{
	XrAssert(f);
	return new GlobalFunctor6<Arg1,Arg2,Arg3,Arg4,Arg5,Arg6>(f);
}

#endif
