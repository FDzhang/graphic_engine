#ifndef __XR_DATE_STRUCT_H__
#define __XR_DATE_STRUCT_H__
#include "../Platform/XrOS.h"
#include "../External/xrIntrinsic.h"
//#include "../3rd/mathlib.h"

class CXrRef {
public:

    CXrRef() : m_refCnt(1) {}

    ~CXrRef() { XrASSERT(m_refCnt == 1); }
	void RefInit() {
		m_refCnt = 1;
	}

	//virtual void Release() { delete this; }
    inline Int32 GetRefCnt() { return m_refCnt; }

    inline void AddRef() {
		XrASSERT(m_refCnt > 0);
		m_refCnt++;
	}
	inline Int32 DecRef() {
		return --m_refCnt;
	}

    //void Release() {
    //    XrASSERT(m_refCnt > 0);
    //    if (--m_refCnt == 1) {
    //        delete this;
    //    }
    //}

private:
    Int32 m_refCnt;
};

/////////////////////Link List Class///////////////////////////////////////
template <typename T> class CUniLinkIterator;

template <typename T>
class CUniLinkNode
{
public:
    CUniLinkNode()
    {
        m_pNext = 0;
        m_payload = 0;
    }
    inline void* GetPayLoad() { return m_payload; }
    inline void SetPayLoad(void* payload) { m_payload = payload; }

    inline T* GetNext() { return (T*)m_pNext; }
    inline void SetNext(CUniLinkNode* next) { m_pNext = next; }
	virtual void VPTRHolder() {};
    void Append(CUniLinkNode* node);            //append as last node
    void InsertAfter(CUniLinkNode* node);       //insert after given node
    void Remove(T** head);                      //header pointer is needed for fixing when removed element was header
    void Delete(T** head);
    void RemoveAllAfter(T** head);
    void DeleteAllAfter(T** head);

protected:
    void*               m_payload;
    CUniLinkNode*       m_pNext;
};

class UniLinkNode : public CUniLinkNode<UniLinkNode>
{
};

template <typename T>
class CBiLinkNode : public CUniLinkNode<T>
{
public:
    CBiLinkNode()
    {
        m_pPrev = 0;
    }

    inline T* GetNext() { return (T*)CUniLinkNode<T>::GetNext(); }
    inline void SetNext(CBiLinkNode* next) { CUniLinkNode<T>::SetNext(next); }
    inline T* GetPrev() { return (T*)m_pPrev; }
    inline void SetPrev(CBiLinkNode* Prev) { m_pPrev = Prev; }

    void Append(CBiLinkNode* node);             //append as last node
    void InsertAfter(CBiLinkNode* node);        //insert after given node
	void InsertBefore(CBiLinkNode* node);       //insert before given node
    void Remove(T** head);
    void Remove();
    void CutBefore();
    void CutAfter();
    //void Delete();

//  header points to "this" and cut node before this and finally paste to tail
//  void ReLinkAsHeader(CBiLinkNode* header);

protected:
    CBiLinkNode*  m_pPrev;
};

class BiLinkNode : public CBiLinkNode<BiLinkNode>
{
};

template <typename T>
class CTreeNode : public CBiLinkNode<T>
{
public:
    CTreeNode()
    {
        m_pSub = 0;
        m_pSuper =0;
    }

    inline T* GetNext() { return (T*)CUniLinkNode<T>::GetNext(); }
    inline void SetNext(CTreeNode<T>* next) { CUniLinkNode<T>::SetNext((CUniLinkNode<T>*)next); }

    inline T* GetPrev() { return (T*)CBiLinkNode<T>::GetPrev(); }
    inline void SetPrev(CTreeNode<T>* Prev) { CBiLinkNode<T>::SetPrev((CBiLinkNode<T>*)Prev); }

    inline T* GetSub() { return (T*)m_pSub; }
    inline void SetSub(CTreeNode* sub) { m_pSub = sub; }

    inline T* GetSuper() { return (T*)m_pSuper; }
    inline void SetSuper(CTreeNode* super) { m_pSuper = super; }

    T* GetRoot();

    void Append(CTreeNode* node);                   //append as last node
    void InsertAfter(CTreeNode* node);              //insert after given node
    void InsertBefore(CTreeNode* node);             //insert before given node
    void AppendAsChild(CTreeNode* childNode);
    void InsertAsChild(CTreeNode* childNode);
    void Remove();
    void Isolate();
    void CutBefore();

    void ReLinkAsHeader(CTreeNode* header);

protected:
    CTreeNode*  m_pSub;
    CTreeNode*  m_pSuper;
};

class TreeNode : public CTreeNode<TreeNode>
{
};

/////////////////////   CLinkIterator   ////////////////////
template <typename T> class CUniLinkIterator
{
public:
    CUniLinkIterator(CUniLinkNode<T>* head)
    {
        m_pHead = head;
		m_pCurr = 0;
    }

    inline void first() { m_pCurr = m_pHead; }
    inline void next() { m_pCurr = m_pCurr->GetNext(); }
    inline bool isDone() { if (m_pCurr) return false; else return true; }
    inline T* getCurrent() { return (T*)m_pCurr; }

protected:
    CUniLinkNode<T>*       m_pHead;
    CUniLinkNode<T>*       m_pCurr;
};

template <typename T> class CBiLinkIterator
{
public:
    Void SetHeader(CBiLinkNode<T>* head)
    {
        m_pFirst = head;
		m_pCurr = 0;
    }

    inline void First() { m_pCurr = m_pFirst; }
    inline void Next() { m_pCurr = m_pCurr->GetNext(); }
    inline void Last()
	{
		m_pCurr = m_pFirst;
	    while (m_pCurr->GetNext()) m_pCurr = m_pCurr->GetNext();
	}
    inline void Prev() { m_pCurr = m_pCurr->GetPrev(); }
    inline bool IsDone() { if (m_pCurr) return false; else return true; }
    inline T* GetCurrent() { return (T*)m_pCurr; }

protected:
    CBiLinkNode<T>*       m_pFirst;
    CBiLinkNode<T>*       m_pCurr;
};

//template <typename T> class CBiLinkIteratorTest
//{
//public:
//    Void SetHeader(CBiLinkNode<T>* head)
//    {
//        m_pFirst = head;
//    }
//
//    inline void First() { m_pCurr = m_pFirst; xrprint("First:m_pCurr=%p\n", m_pCurr);}
//    inline void Next() { xrprint("Next:m_pCurr=%p\n", m_pCurr);m_pCurr = m_pCurr->GetNext(); }
//    inline bool IsDone() { xrprint("isdone:m_pCurr=%p\n", m_pCurr);if (m_pCurr) return false; else return true; }
//    inline T* GetCurrent() { return (T*)m_pCurr; }
//
//protected:
//    CBiLinkNode<T>*       m_pFirst;
//    CBiLinkNode<T>*       m_pCurr;
//};

template <typename T> class CXrBiLinkList
{
public:
	CXrBiLinkList()
	{
		m_pHead = 0;
		m_pTail = 0;
	}
	T* GetHead() { return m_pHead;}
	T* GetTail() { return m_pTail;}
	Int32 IsListEmpty() { return !m_pHead; }
	CBiLinkIterator<T>* GetBiLinkListIterator() { m_iter.SetHeader(m_pHead); return &m_iter; }
	//CBiLinkIteratorTest<T>* GetBiLinkListIteratorTest() { m_iterTest.SetHeader(m_pHead); return &m_iterTest; }
	xr_state AddNode(T*  targetNode, T* node, InsertFlag flag);
	xr_state removeNode(T* node);
	T*	Extract();		//Get a node and remove from list

protected:
	T*		m_pHead;
	T*		m_pTail;
	CBiLinkIterator<T>	m_iter;
	//CBiLinkIteratorTest<T>  m_iterTest;
};

template <typename T>
class CXrTree: public CXrBiLinkList<T>
{
	public:
		xr_state AddNode(T*  targetNode, T* node, InsertFlag flag);
		xr_state IsolateNode(T* node);
	T* GetRoot() { return CXrBiLinkList<T>::m_pHead;}
	protected:
};


template <typename T> class CXrTreeIterator
{
public:
    Void SetHeader(CTreeNode<T>* head)
    {
        m_pFirst = head;
		m_pCurr = 0;
    }

    void First() {  }
    void Next() { }
    bool IsDone() { }
    T* GetCurrent() { return (T*)m_pCurr; }

protected:
    CTreeNode<T>*       m_pFirst;
    CTreeNode<T>*       m_pCurr;
};

/////////////////////   CLazySlot         ////////////////////
template <typename T, Int32 defaultNum> class CLazySlot
{
public:
    CLazySlot()
    {
		m_slot = new T*[defaultNum];
		if (!m_slot) {
			m_size = 0;
			return;
		}
        for (Int32 i=0; i<defaultNum; i++) {
            m_slot[i] = 0;
        }

        m_availableSlot = 0;
        m_numberOfElement = 0;
        m_current = 0;
        m_size = defaultNum;
    }

	~CLazySlot() 
	{
		if (m_slot) delete[] m_slot;
	}

	Int32 GetCount()
	{
		return m_numberOfElement;
	}

    Int32 Add(T* element)
    {
		if (!element) return -1;
        if (m_numberOfElement >= m_size) {
			if (XRFAILED(Expand2X())) return -1;
        }
        Int32 tempId = m_availableSlot;

        m_slot[m_availableSlot] = element;
        m_numberOfElement++;

        while (m_availableSlot<m_size && m_slot[m_availableSlot] != 0) {
            m_availableSlot++;
        }

        return tempId;
    }

	Int32 Add(Int32 id, T* element)
    {
        if (!element || m_slot[id]) {
            return -1;
        }
		if (id >= m_size)  {
			Expand2N(id);
		}

        m_slot[id] = element;
        m_numberOfElement++;

		if (m_availableSlot == id) {
			while (m_availableSlot<m_size && m_slot[m_availableSlot] != 0) {
				m_availableSlot++;
			}
		}

        return id;
    }

    T* Replace(Int32 id, T* element)
    {
        T* old;
        //if (m_slot[id]) {
        old = m_slot[id];
        m_slot[id] = element;
        return old;
        //}
        //else return 0;
    }

    xr_state Delete(
        /* [in] */ Int32 id)
    {
       if (!m_slot[id]) {
            return E_NOT_EXIST;
       }

        delete m_slot[id];

        m_slot[id] = 0;

        if (m_availableSlot > id)
            m_availableSlot = id;

        m_numberOfElement--;

        return NOERROR;
    }

    xr_state Remove(
        /* [in] */ Int32 id)
    {
       if (!m_slot[id]) {
            return E_NOT_EXIST;
       }

        //m_slot[id]->SetId(-1);
        m_slot[id] = 0;

        if (m_availableSlot > id)
            m_availableSlot = id;

        m_numberOfElement--;

        return NOERROR;
    }

	xr_state Release(
        /* [in] */ Int32 id)
    {
       if (!m_slot[id]) {
            return E_NOT_EXIST;
       }
		
	   m_slot[id]->Release();
	  // if (!m_slot[id]->Release()) {
		   m_slot[id] = 0;

			if (m_availableSlot > id)
				m_availableSlot = id;

			m_numberOfElement--;
	  // }

        return NOERROR;
    }

    T* Get(Int32 id)
    {
		if (id<0) return 0;
        if (m_slot[id]) return m_slot[id];
        else return 0;
    }

    void First()
    {
        m_current = 0;
        m_elementLeft = m_numberOfElement;
        if (m_elementLeft) {
            while (!m_slot[m_current]) {
                m_current++;
            }
        }
    }

    void Next()
    {
        m_current++;
        m_elementLeft--;

        while (m_current<m_size && m_elementLeft>0 && !m_slot[m_current]) {
            m_current++;
        }
        XrASSERT(m_current < m_size);
    }

    bool IsDone()
    {
        if (m_elementLeft<=0) {
            return true;
        }
        else
            return false;
    }

    T* GetCurrent()
    {
        return m_slot[m_current];
    }

    Int32 GetNum()
    {
        return m_numberOfElement;
    }

	xr_state Expand2X()
	{
		Int32 i;
		T** temp = new T*[m_size*2];
		if (!temp) return XR_FAILED;
		for (i=0;i<m_size;i++) {
			temp[i] = m_slot[i];
		}
		for (i=m_size;i<m_size*2;i++) {
			temp[i] = 0;
		}
		delete[] m_slot;
		m_slot = temp;
		m_size *= 2;
		return XR_OK;
	}
	xr_state Expand2N(Int32 num)
	{
		Int32 val=2, i;
		while (val<num) val*=2;
		T** temp = new T*[val];
		if (!temp) return XR_FAILED;
		for (i=0;i<val;i++) {
			temp[i] = m_slot[i];
		}
		for (i=val;i<val*2;i++) {
			temp[i] = 0;
		}
		delete[] m_slot;
		m_slot = temp;
		m_size = val;
		return XR_OK;
	}

	Void RemoveCurrent()
	{
		Remove(m_current);
	}
	Void Clear(Boolean bDelete=FALSE)
	{
		for (Int32 i=0; i<defaultNum; i++) {
			
			m_slot[i] = 0;
        }
		if( bDelete )	 delete[] m_slot;
		
        m_availableSlot = 0;
        m_numberOfElement = 0;
        m_current = 0;
        m_size = defaultNum;
	}
protected:
    T**             m_slot;
	Int32			m_size;
    Int32           m_availableSlot;
    Int32           m_numberOfElement;
    Int32           m_current;
    Int32           m_elementLeft;
};

/////////////////////   CFlushQueue         ////////////////////
template <typename T, Int32 defaultNum> class CFlushQueue
{
public:
	CFlushQueue()
    {
        m_numberOfElement = 0;
        m_current = 0;
		m_queue = new T[defaultNum];
		if (!m_queue) {
			m_size = 0;
			return;
		}
		m_size = defaultNum;
    }

	~CFlushQueue()
	{
		if (m_queue) delete m_queue;
	}

	Int32 GetCount()
	{
		return m_numberOfElement;
	}

    Boolean Add(T* element)
    {
        if (m_numberOfElement >= m_size ) {
			if (XRFAILED(Expand2X()))
            return FALSE;
        }
		m_queue[m_numberOfElement] = *element;
        m_numberOfElement++;
		return TRUE;
    }

    void First()
    {
        m_current = 0;
    }

    void Next()
    {
        m_current++;
    }

    bool IsDone()
    {
        if (m_current<m_numberOfElement) {
            return false;
        }
        else
            return true;
    }

    T* GetCurrent()
    {
        return &m_queue[m_current];
    }

    inline Int32 GetNum()
    {
        return m_numberOfElement;
    }

    Void Reset()
    {
        m_numberOfElement = 0;
		m_current = 0;
    }

	xr_state Expand2X()
	{
		Int32 i;
		T* temp = new T[m_size*2];
		if (!temp) return XR_FAILED;
		for (i=0;i<m_size;i++) {
			temp[i] = m_queue[i];
		}
		delete m_queue;
		m_queue = temp;
		m_size *= 2;
		return XR_OK;
	}

private:
	T*				m_queue;
    Int32           m_numberOfElement;
    Int32           m_current;
	Int32			m_size;
};

////////////////////// Rendering stack Record Datastruct ///////////////////////
template <typename T, Int32 num> class CStack
{
public:
    CStack<T, num>()
    {
        m_top = 0;
    }

    ~CStack<T, num>()
    {
    }

    inline Boolean Push(T& t)
    {
        XrASSERT(m_top != num);
        if (m_top == num)
            return FALSE;
        m_stack[m_top] = t;
        m_top++;
        return TRUE;
    }

    inline Boolean Pop(T& t)
    {
        m_top--;
        if (m_top < 0)
            return FALSE;
        t = m_stack[m_top];
        return TRUE;
    }

    inline Boolean Pop()
    {
        m_top--;
        if (m_top < 0) {
            m_top = 0;
            return FALSE;
        }
        return TRUE;
    }

    inline void Clean()
    {
        m_top = 0;
    }

    inline Boolean IsEmpty()
    {
        return m_top == 0 ? TRUE : FALSE;
    }

private:
    Int32   m_top;
    T       m_stack[num];
};


///////////////////RBTree relative////////////////////////

#define    RB_RED               0
#define    RB_BLACK             1

class ListEntry {
public:
    ListEntry(int key)
    {
        key1 = key;
    }

    ListEntry()
    {
    }

    inline void SetKey(int key)
    {
        key1 = key;
    }

    inline int cmp(ListEntry * left, ListEntry * right) {
        return left->key1 - right->key1;
    }
    int         KeyId;
    int         key1;
    int         key2;
    //WString     m_data2;
};

/********************   Class RBNode   ********************/
template <typename T>
class RBNode {
public:
    RBNode()
    {
        rb_parent = 0;
        rb_right = 0;
        rb_left = 0;
    }

    T key;
    int         rb_color;
    RBNode<T> *rb_parent;
    RBNode<T> *rb_right;
    RBNode<T> *rb_left;
    int         weight;
};

/********************   Class RBTree   ********************/
template <typename T>
class RBTree{
public:
    RBTree() : root(NULL) {m_size = 0;}
    ~RBTree()
    {
        _DeleteTree(root);
    }

    bool Insert(T & t);
    void Remove(RBNode<T> *node);
    bool RemoveByRank(int rank);
    RBNode<T>* Select(int order);
    int Rank(T * w);

    void First();
    void Last();
    void Next();
    void Prev();

    inline bool IsFirst()
    {
        return m_IsFirst;
    }

    inline bool IsLast()
    {
        return m_IsLast;
    }

    inline T GetCurrent() {
        return current->key;
    }

    inline int GetSize() {
        return m_size;
    }

private:
    // delete_tree;
    void _RBEraseColor(RBNode<T> *node, RBNode<T> *parent);
    void _RBRotateLeft(RBNode<T> *node);
    void _RBRotateRight(RBNode<T> *node);
    void _RBInsertColor(RBNode<T> *node);
    void _DeleteTree(RBNode<T>* node);

    RBNode<T>*    root;
    RBNode<T>*    current;
    bool        m_IsFirst;
    bool        m_IsLast;
    int         m_size;
};


template <typename T>
class CPool
{
public:
	CPool();
    ~CPool();

    T* Get();
    Void Release(T* t);
	Void Release();

public:
    T* FreeHeader;
};

struct LayerTraverseInfo {
    LayerTraverseInfo()
    {
        layer = 0;
        x = 0;
        y = 0;
		z = 0;
		opacity = 1.0;
    }

    class CLayer*     layer;
    Rect   clipRect;
    Float32       x;
    Float32       y;
	Float32       z;
	Float32       opacity;
};


inline Boolean IsValid(UInt32 num)
{
	return (num!=0xffffffff);
}

template <class T,UInt32 defaultCapacity=8U>
class CArray
{
public:
	enum { npos = -1 };
	CArray() : m_uSize(0),m_uCapacity(defaultCapacity),m_current(0)
	{
		m_pData = new T[m_uCapacity];
	}
	CArray(UInt32 num) : m_uSize(0),m_uCapacity(num),m_current(0)
	{
		XrASSERT(num!=0);
		m_pData = new T[m_uCapacity];
	}
	CArray(UInt32 num,const T &value): m_uSize(num),m_uCapacity(num),m_current(0)
	{
		XrASSERT(num!=0);
		m_pData = new T[m_uCapacity];
		for( UInt32 i = 0 ; i < num ; ++i ){
			m_pData[i] = value;
		}
	}
	template<class U>
	CArray(const CArray<U>& src) : m_uSize(src.GetCount()), m_uCapacity(src.m_uCapacity),m_current(src.m_current)
	{
		m_pData = new T[m_uCapacity];
		for(UInt32 i=0 ; i < m_uSize; ++i){
			m_pData[i] = src.m_pData[i];
		}
	}
	CArray(const CArray<T>& src) : m_uSize(src.GetCount()), m_uCapacity(src.m_uCapacity),m_current(src.m_current)
	{
		m_pData = new T[m_uCapacity];
		for(UInt32 i=0 ; i < m_uSize; ++i){
			m_pData[i] = src.m_pData[i];
		}
	}
	~CArray()
	{
		delete[] m_pData;
		m_pData = NULL;
	}

public:
	
	UInt32 GetCount() const { return m_uSize; }
	UInt32 GetCapacity() const { return m_uCapacity; }
	Boolean Empty() const { return (m_uSize == 0 ); }
	UInt32 Push_back(const T& value)
	{
		UInt32 uIndex = Append();
		if( IsValid(uIndex) ){	
			m_pData[uIndex] = value;
		}
		return uIndex;
	}
	
	
	UInt32 Append()
	{
		if( Reserve(m_uSize+1) ){
			UInt32 index = m_uSize;
			++m_uSize;
			return index;
		}
		return 0xffffffff;
	}

	UInt32 Append(UInt32 cnt,const T& value)
	{
		UInt32 oldSize = m_uSize;
		if( Resize(m_uSize+cnt) ){
			for( UInt32 i = 0 ; i < cnt ; ++i ){
				m_pData[oldSize+i] = value;
			}
		}
		return npos;
	}
	Boolean Reserve(UInt32 uSize)
	{
		if( uSize <= m_uCapacity )
			return TRUE;
		else
		{
			UInt32 uNewCapacity = 0;
			if( uSize < 2*m_uCapacity )
				uNewCapacity = 2 * m_uCapacity;
			else
				uNewCapacity = uSize;
			T* pNewArray = new T[uNewCapacity];		// New Array
			if(!pNewArray)
				return FALSE;						// Failed to allocate memory! C++ standard needs new fail to throw out an exception,but we may use our own memory management,so it 
													// may not throw out bad_alloc exception. maybe I should throw out an exception

			// Copy source data to new array
			XrMemcpy(pNewArray,m_pData,sizeof(T)*m_uSize);///sometimes ,memcpy does not equal with operate = ,maybe I should change this to =

			// Switch pointers and free memory
			m_uCapacity	= uNewCapacity;
			T* pOldArray	= m_pData;
			m_pData		= pNewArray;
			delete [] pOldArray;
			return TRUE;
		}

	}
	Boolean Resize(UInt32 uSize)
	{
		if( Reserve(uSize) ){
			m_uSize = uSize;
			return TRUE;
		}
		return FALSE;

	}
	Boolean Copyfrom(const CArray<T>& src,UInt32 begin,UInt32 length)
	{
		XrASSERT(src.GetCount() >= length);
		XrASSERT(begin != 0 && length != 0 );
		if( Reserve(begin+length) ){
			UInt32 uNewSize = begin+length;
			//memcpy(m_pData+begin,&src[0],length*sizeof(T));///sometimes ,memcpy does not equal with operate = ,maybe I should change this to =
			for( UInt32 i = 0 ; i < length ; ++i ){
				m_pData[begin+i] = src[i];
			}
			if( uNewSize > m_uSize ) m_uSize = uNewSize;
			return TRUE;
		}
		return FALSE;
	}
	Boolean Copyfrom(const T* psrc,UInt32 begin,UInt32 length)
	{
		XrASSERT(psrc != NULL );
		if(length == 0 ) 
			return TRUE;
		if( Reserve(begin+length) ){
			UInt32 uNewSize = begin+length;
			memcpy(m_pData+begin,psrc,length*sizeof(T));///sometimes ,memcpy does not equal with operate = ,maybe I should change this to =
			if( uNewSize > m_uSize ) m_uSize = uNewSize;
			return TRUE;
		}
		return FALSE;
	}
	CArray<T>& operator=(const CArray<T>& src)
	{
		if( &src != this ){
			Clear();
			
			Copyfrom(src,0,src.GetCount());
			
		}
		return *this;
	}
	const T& operator[](UInt32 index) const
	{
		XrASSERT(index < m_uSize);
		return m_pData[index];
	}
	T& operator[](UInt32 index)
	{
		XrASSERT(index < m_uSize);
		return m_pData[index];
	}
	Void Clear()
	{
		m_uSize = 0U;
	}
	Void Pop_back()
	{
		XrASSERT(m_uSize != 0);
		--m_uSize;
	}
	Void Erase(UInt32 index)
	{
		XrASSERT(m_uSize != 0);
		if( index > m_uSize-1)
			return;
		else if( index == m_uSize-1 ){
			Pop_back();
		}
		else{
			//UInt32 length = m_uSize - index;
			for( UInt32 i = index; i < (m_uSize-1) ; ++i )
			{
				m_pData[i] = m_pData[i+1];
			}
			--m_uSize;
		}
	}
	Void Remove(const T& value)
	{
		UInt32 index = find(value);
		if( IsValid(index) )
			Erase(index);
	}
	UInt32 find(const T& value)
	{
		for( UInt32 i = 0; i < m_uSize; ++i ){
			if( m_pData[i] == value ){
				return i;
			}
		}
		return npos;
	}



	void First()
    {
        m_current = 0;
    }

    void Next()
    {
        m_current++;
    }

    bool IsDone()
    {
       return ( m_current >= m_uSize );
    }

    T& GetCurrent()
    {
        return m_pData[m_current];
    }

	
protected:
	UInt32 m_uSize;
	UInt32 m_uCapacity;
	T* m_pData;
	UInt32 m_current;

};

#endif  //__XR_DATE_STRUCT_H__
