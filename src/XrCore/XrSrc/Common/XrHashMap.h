#ifndef _XRHASHMAP_H
#define _XRHASHMAP_H
#include "../Platform/XrOS.h"
#include "XrInternal.h"

template<class Node>
Void FreeLink(Node* node)
{
	while( node ){
		Node* prev = node;
		node = node->GetNext();
		delete prev;
	}
}

 #define _XRHASH_SEED	(UInt32)0xdeadbeef

template <class _InIt>
	inline size_t _XrHash_value(_InIt _Begin, _InIt _End)
	{	// hash range of elements
		size_t _Val = 2166136261U;
		while(_Begin != _End)
			_Val = 16777619U * _Val ^ (size_t)*_Begin++;
		return (_Val);
	}
template<class _Kty> inline
	UInt32 xrhash_value(const _Kty& _Keyval)
	{	// hash _Keyval to size_t value one-to-one
	return ((UInt32)_Keyval ^ _XRHASH_SEED);
	}

inline UInt32 xrhash_value(const char *_Str)
	{	// hash NTBS to size_t value
	return (_XrHash_value(_Str, _Str + ::strlen(_Str)));
	}

inline UInt32 xrhash_value(const wchar_t *_Str)
	{	// hash NTWCS to size_t value
        return 0;//(_XrHash_value(_Str, _Str + wcslen(_Str)));
	}
inline UInt32 xrhash_value(const CXRString& str)
{
	return xrhash_value(str.c_str());
}

template<class KeyType>
class XrHash_Func
{
public:
	UInt32 operator()(const KeyType& key) const
	{
		UInt32 ret = xrhash_value(key);
		return ret;
	}
};

template<class KeyType,class ValueType,class HashFunc=XrHash_Func<KeyType> >
class XrHashMap
{
public:
	
	template <class _KeyType,class _ValueType>
	struct Node : public CBiLinkNode<Node<_KeyType,_ValueType> >
	{
		_KeyType		_key;
		_ValueType	_value;
		
	};
	enum {DefaultSize=8};
	enum { npos = -1 };
	
	typedef Node<KeyType,ValueType>	_Node;
	typedef Node<KeyType,ValueType>*	_NodePtr;
	typedef Node<KeyType,ValueType>&	_NodeRef;
	
	typedef XrHashMap<KeyType,ValueType>	Self;


	template <class _KeyType,class _ValueType>
	struct Entry
	{
		typedef Node<_KeyType,_ValueType>*		NodePtr;
		NodePtr		_ptr;
		UInt32		_num;
		Entry() : _ptr(NULL),_num(0){}
		Void Reset()
		{
			_ptr = NULL;
			_num = 0;
		}
		Boolean Empty() const
		{
			return (_num == 0 );
		}
	};

	typedef Entry<KeyType,ValueType>	_Entry;
	
	template <class _KeyType,class _ValueType>
	class _Iterator
	{
	public:
		
		typedef XrHashMap<_KeyType,_ValueType>	HashMap;
		typedef _Iterator<_KeyType,_ValueType>	iterator;
		typedef Node<_KeyType,_ValueType>*		NodePtr;

		//friend class HashMap;
		_Iterator(NodePtr ptr,HashMap& hashmap):
		  _ptr(ptr),_hashmap(&hashmap)
		  {}
		_Iterator(const iterator& srcit):
		  _ptr(srcit._ptr)
		  {}
		const _ValueType& operator*() const
		{
			XrAssert(_ptr);
			return (_ptr->_value);
		}
		_ValueType& operator*()
		{
			XrAssert(_ptr);
			return (_ptr->_value);
		}
		iterator operator++()
		{
			XrAssert(_ptr);
			
			_ptr = _ptr->GetNext();
			
			return (*this);
		}
		iterator operator++(Int32)
		{
			iterator ret = (*this);
			XrAssert(_ptr);
			
			_ptr = _ptr->next;
			
			return ret;
		}
		Boolean operator==(const iterator& it){
			return ( (_ptr == it._ptr)&& (_hashmap) == (it._hashmap) );
		}
		Boolean operator!=(const iterator& it){
			return ( (_ptr != it._ptr) || (_hashmap) != (it._hashmap) );
		}
		iterator operator=(iterator it)
		{
			_ptr = it._ptr;
			_hashmap = it._hashmap;
			XrAssert(_hashmap);
			return (*this);
		}
		_KeyType& Key()
		{
			return _ptr->_key;
		}
	protected:
		NodePtr	_ptr;
		HashMap*_hashmap;
	};
	XrHashMap()
		:loadfactor(0.75f),m_Size(0),m_head(NULL)
	{
		m_Array.Resize(DefaultSize);
		for(UInt32 i = 0 ; i < m_Array.GetCount(); ++i){
			m_Array[i].Reset();
		}
	}
	~XrHashMap()
	{
		_Release();
	}

	typedef _Iterator<KeyType,ValueType> iterator;
public:	
	//iterator Find(const KeyType& key) const
	//{
	//	UInt32 idx = HashKey(key);
	//	const _NodeRef ref = m_Array[idx];
	//	if( ref._key == key )
	//		return iterator(&ref,*this);
	//	else{
	//		_NodePtr p = _FindInLink(ref,key);
	//		if( p ) return iterator(p,*this);
	//		else return end();
	//	}

	//}
	Boolean Empty()
	{
		return (m_Size == 0 );
	}
	iterator Find(const KeyType& key)
	{
		if( Empty() )	return end();
		UInt32 idx = HashKey(key);
		_Entry& entry = m_Array[idx];
		if( !entry._ptr )
			return end();
		else{
			_NodePtr p = _FindInLink(entry,key);
			if( p ) return iterator(p,*this);
			else return end();
		}
	}
	iterator Insert(const KeyType& key,const ValueType& value)
	{
		
		UInt32 idx = HashKey(key);

		_Entry& entry = m_Array[idx];
		_NodePtr retptr = _AddAsLink(entry,key,value);

		if( LoadFactor(m_Size) > loadfactor ){
			Expand2Size(m_Size);
		}
		
		return iterator(retptr,*this);
	}
	iterator Erase(iterator it)
	{
		XrAssert(it != end());
		
		_NodePtr p = it._ptr;
		UInt32 idx = HashKey(p->_key);
		_Entry& entry = m_Array[idx];
		Boolean bHead = ( entry._ptr == p );
		_NodePtr next = p->GetNext();
		--entry._num;
		if( bHead ){
			if( !entry.Empty() ) entry._ptr = next;
			else entry._ptr = NULL;
		}
		--m_Size;
		p->Remove();
		delete p;
		if( Empty() )	m_head = NULL;
		return iterator(next,*this);
	}
	iterator Remove(const KeyType& key)
	{
		iterator it = Find(key);
		it = Erase(it);
		return it;
	}
	
	//UInt32 Shrink()
	//{
	//	//const Float32 ratio = 0.5f;
	//	//if( LoadFactor(m_Size+m_ArrayRealSize) < ratio ){
	//	//	UInt32 from = m_Array.GetCount();
	//	//	for( UInt32 i = from; i >= 1 ; --i){
	//	//		_NodeRef ref = m_Array[i-1];
	//	//		if( ref.IsValid() ){
	//	//			from = i;
	//	//			break;
	//	//		}	
	//	//	}
	//	//	///shrink to from
	//	//}
	//	return 0;
	//}


	iterator begin()
	{
		if( m_head )
			return iterator(m_head,*this);
		else
			return end();
		
	}
	iterator end()
	{
		return iterator(_EndPtr(),*this);
	}

	Void Clear()
	{
		_Release();
		
		m_Size = 0U;
		//Shrink();
	}

protected:
	UInt32  HashKey(const KeyType&key) const
	{
		UInt32 key1 = this->m_HashFunc(key);
		return (key1 &(m_Array.GetCount()-1));
	}
	Float32 LoadFactor(UInt32 size) const
	{
		return (Float32)size/(m_Array.GetCount()+m_Size);
	}
	
	
	_NodePtr _AddAsLink(_Entry& entry,const KeyType& key,const ValueType& value)
	{
		_NodePtr newptr = new _Node;
		newptr->_key = key;
		newptr->_value = value;
		
		if( entry._ptr ){
			_NodePtr ptr = entry._ptr;
			UInt32 i = 1;
			while( ptr && i < entry._num ){
				ptr = ptr->GetNext();
				++i;
			}

			ptr->InsertAfter(newptr);
		}
		else{
			entry._ptr = newptr;
			if( !m_head )
				m_head = newptr;
			else{
				m_head->Append(newptr);
			}
		}
		++entry._num;
		
		
		++m_Size;
		return newptr;
	}



	UInt32 Expand2Size(UInt32 size)
	{
		UInt32 oldsize = m_Array.GetCount();
		m_Array.Resize(size);
		for(UInt32 i = oldsize ; i < size; ++i ){
			m_Array[i].Reset();
		}
		return m_Array.GetCapacity();
	}
	_NodePtr _FindInLink(const _Entry& entry,const KeyType& key)
	{
		_NodePtr p = entry._ptr;
		UInt32 i = 0;
		while( p && i < entry._num ){
			if( p->_key == key )
				return p;
			p = p->GetNext();
			++i;
		}
		return _EndPtr();
	}

	Void _Release()
	{
		
		FreeLink(m_head);
		m_head = NULL;
		for(UInt32 i = 0 ; i < m_Array.GetCount(); ++i){
			m_Array[i].Reset();
		}
		//memset(&m_Array[0],0,sizeof(_Entry)*m_Array.GetCapacity());
		//m_Array.Clear();
	}
	_NodePtr _EndPtr()
	{
		return _NodePtr(NULL);
	}
protected:
	CArray<_Entry>					m_Array;
	_NodePtr						m_head;			
	UInt32							m_Size;
	HashFunc						m_HashFunc;		
	Float32							loadfactor;

};

#endif
