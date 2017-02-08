#include "XRString.h"

#ifdef _USING_XRSTRING_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../Platform/XrOS.h"

const size_t CXRString::npos = (size_t) -1;

/*!***********************************************************************
@Function			CXRString
@Input				_Ptr	A string
@Input				_Count	Length of _Ptr
@Description		Constructor
************************************************************************/
CXRString::CXRString(const char* _Ptr, size_t _Count) :
m_pString(0), m_Capacity(0)
{
	if (_Count == npos)
		assign(_Ptr);
	else
		assign(_Ptr, _Count);
}

/*!***********************************************************************
@Function			CXRString
@Input				_Right	A string
@Input				_Roff	Offset into _Right
@Input				_Count	Number of chars from _Right to assign to the new string
@Description		Constructor
************************************************************************/
CXRString::CXRString(const CXRString& _Right, size_t _Roff, size_t _Count) :
m_pString(0), m_Capacity(0)
{
	assign(_Right, _Roff, _Count);
}

/*!***********************************************************************
@Function			CXRString
@Input				_Count	Length of new string
@Input				_Ch		A char to fill it with
@Description		Constructor
*************************************************************************/
CXRString::CXRString(size_t _Count, char _Ch) :
m_pString(0), m_Capacity(0)
{
	assign(_Count,_Ch);
}

/*!***********************************************************************
@Function			CXRString
@Input				_Ch	A char
@Description		Constructor
*************************************************************************/
CXRString::CXRString(const char _Ch) :
m_pString(0), m_Capacity(0)
{
	assign( 1, _Ch);
}

/*!***********************************************************************
@Function			CXRString
@Description		Constructor
*************************************************************************/
CXRString::CXRString() :
m_Size(0), m_Capacity(1)
{
	m_pString = (char*)calloc(1, 1);
}

/*!***********************************************************************
@Function			~CXRString
@Description		Destructor
*************************************************************************/
CXRString::~CXRString()
{
	free(m_pString);
}

/*!***********************************************************************
@Function			append
@Input				_Ptr	A string
@Returns			Updated string
@Description		Appends a string
*************************************************************************/
CXRString& CXRString::append(const char* _Ptr)
{
	return append(_Ptr,strlen(_Ptr));
}

/*!***********************************************************************
@Function			append
@Input				_Ptr	A string
@Input				_Count	String length
@Returns			Updated string
@Description		Appends a string of length _Count
*************************************************************************/
CXRString& CXRString::append(const char* _Ptr, size_t _Count)
{
	char* pString = m_pString;
	size_t newCapacity = _Count + m_Size + 1;	// +1 for null termination

	// extend CXRString if necessary
	if (m_Capacity < newCapacity)
	{
		pString = (char*)malloc(newCapacity);
		m_Capacity = newCapacity;
		memmove(pString, m_pString, m_Size);
		pString[m_Capacity-1]='\0';
	}

	// append chars from _Ptr
	memmove(pString + m_Size, _Ptr, _Count);
	m_Size += _Count;
	pString[m_Size] = 0;

	// remove old CXRString if necessary
	if (pString != m_pString)
	{
		free(m_pString);
		m_pString = pString;
	}
	return *this;
}

/*!***********************************************************************
@Function			append
@Input				_Str	A string
@Returns			Updated string
@Description		Appends a string
*************************************************************************/
CXRString& CXRString::append(const CXRString& _Str)
{
	return append(_Str.m_pString,_Str.m_Size);
}

/*!***********************************************************************
@Function			append
@Input				_Str	A string
@Input				_Off	A position in string
@Input				_Count	Number of letters to append
@Returns			Updated string
@Description		Appends _Count letters of _Str from _Off in _Str
*************************************************************************/
CXRString& CXRString::append(const CXRString& _Str, size_t _Off, size_t _Count)
{
	return append(_Str.m_pString+_Off,_Count);
}

/*!***********************************************************************
@Function			append
@Input				_Ch		A char
@Input				_Count	Number of times to append _Ch
@Returns			Updated string
@Description		Appends _Ch _Count times
*************************************************************************/
CXRString& CXRString::append(size_t _Count, char _Ch)
{
	char* pString = m_pString;
	size_t newCapacity = _Count + m_Size + 1;	// +1 for null termination
	// extend CXRString if necessary
	if (m_Capacity < newCapacity)
	{
		pString = (char*)malloc(newCapacity);
		m_Capacity = newCapacity;
		memmove(pString, m_pString, m_Size+1);
	}

	char* newChar = &pString[m_Size];
	// fill new space with _Ch
	for(size_t i=0;i<_Count;++i)
	{
		*newChar++ = _Ch;
	}
	*newChar = '\0';		// set null terminato
	m_Size+=_Count;			// adjust length of string for new characters

	// remove old CXRString if necessary
	if (pString != m_pString)
	{
		free(m_pString);
		m_pString = pString;
	}
	return *this;
}

/*!***********************************************************************
@Function			assign
@Input				_Ptr A string
@Returns			Updated string
@Description		Assigns the string to the string _Ptr
*************************************************************************/
CXRString& CXRString::assign(const char* _Ptr)
{
	return assign(_Ptr, strlen(_Ptr));
}

/*!***********************************************************************
@Function			assign
@Input				_Ptr A string
@Input				_Count Length of _Ptr
@Returns			Updated string
@Description		Assigns the string to the string _Ptr
*************************************************************************/
CXRString& CXRString::assign(const char* _Ptr, size_t _Count)
{
	char* pString = m_pString;
	if (m_Capacity <= _Count)
	{
		pString = (char*)malloc(_Count + 1);
		m_Capacity = _Count+1;
	}
	m_Size = _Count;

	memmove(pString, _Ptr, m_Size);
	pString[m_Size] = 0;

	if (pString != m_pString)
	{
		free(m_pString);
		m_pString = pString;
	}
	return *this;
}

/*!***********************************************************************
@Function			assign
@Input				_Str A string
@Returns			Updated string
@Description		Assigns the string to the string _Str
*************************************************************************/
CXRString& CXRString::assign(const CXRString& _Str)
{
	return assign(_Str.m_pString, _Str.m_Size);
}

/*!***********************************************************************
@Function			assign
@Input				_Str A string
@Input				_Off First char to start assignment from
@Input				_Count Length of _Str
@Returns			Updated string
@Description		Assigns the string to _Count characters in string _Str starting at _Off
*************************************************************************/
CXRString& CXRString::assign(const CXRString& _Str, size_t _Off, size_t _Count)
{
	if(_Count==npos)
	{
		_Count = _Str.m_Size - _Off;
	}
	return assign(&_Str.m_pString[_Off], _Count);
}

/*!***********************************************************************
@Function			assign
@Input				_Ch A string
@Input				_Count Number of times to repeat _Ch
@Returns			Updated string
@Description		Assigns the string to _Count copies of _Ch
*************************************************************************/
CXRString& CXRString::assign(size_t _Count,char _Ch)
{
	if (m_Capacity <= _Count)
	{
		free(m_pString);
		m_pString = (char*)malloc(_Count + 1);
		m_Capacity = _Count+1;
	}
	m_Size = _Count;
	memset(m_pString, _Ch, _Count);
	m_pString[m_Size] = 0;

	return *this;
}

//const_reference at(size_t _Off) const;
//reference at(size_t _Off);

/*!***********************************************************************
@Function			c_str
@Returns			const char* pointer of the string
@Description		Returns a const char* pointer of the string
*************************************************************************/
const char* CXRString::c_str() const
{
	return m_pString;
}

/*!***********************************************************************
@Function			capacity
@Returns			The size of the character array reserved
@Description		Returns the size of the character array reserved
*************************************************************************/
size_t CXRString::capacity() const
{
	return m_Capacity;
}

/*!***********************************************************************
@Function			clear
@Description		Clears the string
*************************************************************************/
void CXRString::clear()
{
	free(m_pString);
	m_pString = (char*)calloc(1, 1);
	m_Size = 0;
	m_Capacity = 1;
}

/*!***********************************************************************
@Function			compare
@Input				_Str A string to compare with
@Returns			0 if the strings match
@Description		Compares the string with _Str
*************************************************************************/
int CXRString::compare(const CXRString& _Str) const
{
	return strcmp(m_pString,_Str.m_pString);
}

/*!***********************************************************************
@Function			<
@Input				_Str A string to compare with
@Returns			True on success
@Description		Less than operator
*************************************************************************/
bool CXRString::operator<(const CXRString & _Str) const
{
	return (strcmp(m_pString, _Str.m_pString) < 0);
}

/*!***********************************************************************
@Function			compare
@Input				_Pos1	Position to start comparing from
@Input				_Num1	Number of chars to compare
@Input				_Str 	A string to compare with
@Returns			0 if the strings match
@Description		Compares the string with _Str
*************************************************************************/
int CXRString::compare(size_t _Pos1, size_t _Num1, const CXRString& _Str) const
{
	assert(_Pos1<=m_Size);	// check comparison starts within lhs CXRString

	int i32Ret;	// value to return if no difference in actual comparisons between chars
	size_t stLhsLength = m_Size-_Pos1;
	size_t stSearchLength = XR_MIN(stLhsLength,XR_MIN(_Str.m_Size,_Num1));	// number of comparisons to do
	if(XR_MIN(stLhsLength,_Num1)<XR_MIN(_Str.m_Size,_Num1))
	{
		i32Ret = -1;
	}
	else if(XR_MIN(stLhsLength,_Num1)>XR_MIN(_Str.m_Size,_Num1))
	{
		i32Ret = 1;
	}
	else
	{
		i32Ret = 0;
	}

	// do actual comparison
	const char* lhptr = &m_pString[_Pos1];
	const char* rhptr = _Str.m_pString;
	for(size_t i=0;i<stSearchLength;++i)
	{
		if(*lhptr<*rhptr)
			return -1;
		else if (*lhptr>*rhptr)
			return 1;
		lhptr++;rhptr++;
	}
	// no difference found in compared characters
	return i32Ret;
}

/*!***********************************************************************
@Function			compare
@Input				_Pos1	Position to start comparing from
@Input				_Num1	Number of chars to compare
@Input				_Str 	A string to compare with
@Input				_Off 	Position in _Str to compare from
@Input				_Count	Number of chars in _Str to compare with
@Returns			0 if the strings match
@Description		Compares the string with _Str
*************************************************************************/
int CXRString::compare(size_t _Pos1, size_t _Num1, const CXRString& _Str, size_t /*_Off*/, size_t _Count) const
{
	assert(_Pos1<=m_Size);	// check comparison starts within lhs CXRString

	int i32Ret;	// value to return if no difference in actual comparisons between chars
	size_t stLhsLength = m_Size-_Pos1;
	size_t stSearchLength = XR_MIN(stLhsLength,XR_MIN(_Str.m_Size,XR_MIN(_Num1,_Count)));	// number of comparisons to do
	if(XR_MIN(stLhsLength,_Num1)<XR_MIN(_Str.m_Size,_Count))
	{
		i32Ret = -1;
	}
	else if(XR_MIN(stLhsLength,_Num1)>XR_MIN(_Str.m_Size,_Count))
	{
		i32Ret = 1;
	}
	else
	{
		i32Ret = 0;
	}


	// do actual comparison
	char* lhptr = &m_pString[_Pos1];
	char* rhptr = _Str.m_pString;
	for(size_t i=0;i<stSearchLength;++i)
	{
		if(*lhptr<*rhptr)
			return -1;
		else if (*lhptr>*rhptr)
			return 1;
		lhptr++;rhptr++;
	}
	// no difference found in compared characters
	return i32Ret;
}

/*!***********************************************************************
@Function			compare
@Input				_Ptr A string to compare with
@Returns			0 if the strings match
@Description		Compares the string with _Ptr
*************************************************************************/
int CXRString::compare(const char* _Ptr) const
{
	return strcmp(m_pString,_Ptr);
}

/*!***********************************************************************
@Function			compare
@Input				_Pos1	Position to start comparing from
@Input				_Num1	Number of chars to compare
@Input				_Ptr 	A string to compare with
@Returns			0 if the strings match
@Description		Compares the string with _Ptr
*************************************************************************/
int CXRString::compare(size_t _Pos1, size_t _Num1, const char* _Ptr) const
{
	assert(_Pos1<=m_Size);	// check comparison starts within lhs CXRString

	int i32Ret;	// value to return if no difference in actual comparisons between chars
	size_t stLhsLength = m_Size-_Pos1;
	size_t stRhsLength = strlen(_Ptr);
	size_t stSearchLength = XR_MIN(stLhsLength,XR_MIN(stRhsLength,_Num1));	// number of comparisons to do
	if(XR_MIN(stLhsLength,_Num1)<XR_MIN(stRhsLength,_Num1))
	{
		i32Ret = -1;
	}
	else if(XR_MIN(stLhsLength,_Num1)>XR_MIN(stRhsLength,_Num1))
	{
		i32Ret = 1;
	}
	else
	{
		i32Ret = 0;
	}

	// do actual comparison
	const char* lhptr = &m_pString[_Pos1];
	const char* rhptr = _Ptr;
	for(size_t i=0;i<stSearchLength;++i)
	{
		if(*lhptr<*rhptr)
			return -1;
		else if (*lhptr>*rhptr)
			return 1;
		lhptr++;rhptr++;
	}
	// no difference found in compared characters
	return i32Ret;
}

/*!***********************************************************************
@Function			compare
@Input				_Pos1	Position to start comparing from
@Input				_Num1	Number of chars to compare
@Input				_Ptr 	A string to compare with
@Input				_Count	Number of char to compare
@Returns			0 if the strings match
@Description		Compares the string with _Str
*************************************************************************/
int CXRString::compare(size_t _Pos1, size_t _Num1, const char* _Ptr, size_t _Count) const
{
	assert(_Pos1<=m_Size);	// check comparison starts within lhs CXRString

	int i32Ret;	// value to return if no difference in actual comparisons between chars
	size_t stLhsLength = m_Size-_Pos1;
	size_t stRhsLength = strlen(_Ptr);
	size_t stSearchLength = XR_MIN(stLhsLength,XR_MIN(stRhsLength,XR_MIN(_Num1,_Count)));	// number of comparisons to do
	if(XR_MIN(stLhsLength,_Num1)<XR_MIN(stRhsLength,_Count))
	{
		i32Ret = -1;
	}
	else if(XR_MIN(stLhsLength,_Num1)>XR_MIN(stRhsLength,_Count))
	{
		i32Ret = 1;
	}
	else
	{
		i32Ret = 0;
	}


	// do actual comparison
	char* lhptr = &m_pString[_Pos1];
	const char* rhptr = _Ptr;
	for(size_t i=0;i<stSearchLength;++i)
	{
		if(*lhptr<*rhptr)
			return -1;
		else if (*lhptr>*rhptr)
			return 1;
		lhptr++;rhptr++;
	}
	// no difference found in compared characters
	return i32Ret;
}

/*!***********************************************************************
@Function			==
@Input				_Str 	A string to compare with
@Returns			True if they match
@Description		== Operator
*************************************************************************/
bool CXRString::operator==(const CXRString& _Str) const
{
	return strcmp(m_pString, _Str.m_pString)==0;
}

/*!***********************************************************************
@Function			==
@Input				_Ptr 	A string to compare with
@Returns			True if they match
@Description		== Operator
*************************************************************************/
bool CXRString::operator==(const char* const _Ptr) const
{
	return strcmp(m_pString, _Ptr)==0;
}

/*!***********************************************************************
@Function			!=
@Input				_Str 	A string to compare with
@Returns			True if they don't match
@Description		!= Operator
*************************************************************************/
bool CXRString::operator!=(const CXRString& _Str) const
{
	return strcmp(m_pString, _Str.m_pString)!=0;
}

/*!***********************************************************************
@Function			!=
@Input				_Ptr 	A string to compare with
@Returns			True if they don't match
@Description		!= Operator
*************************************************************************/
bool CXRString::operator!=(const char* const _Ptr) const
{
	return strcmp(m_pString, _Ptr)!=0;
}

/*!***********************************************************************
@Function			copy
@Modified			_Ptr 	A string to copy to
@Input				_Count	Size of _Ptr
@Input				_Off	Position to start copying from
@Returns			Number of bytes copied
@Description		Copies the string to _Ptr
*************************************************************************/
size_t CXRString::copy(char* _Ptr, size_t _Count, size_t _Off) const
{
	if(memcpy(_Ptr, &m_pString[_Off], XR_MIN(_Count, m_Size - _Off)))
		return _Count;

	return 0;
}

/*!***********************************************************************
@Function			data
@Returns			A const char* version of the string
@Description		Returns a const char* version of the string
*************************************************************************/
const char* CXRString::data() const
{
	return m_pString;
}

/*!***********************************************************************
@Function			empty
@Returns			True if the string is empty
@Description		Returns true if the string is empty
*************************************************************************/
bool CXRString::empty() const
{
	return (m_Size == 0);
}

/*!***********************************************************************
@Function			erase
@Input				_Pos	The position to start erasing from
@Input				_Count	Number of chars to erase
@Returns			An updated string
@Description		Erases a portion of the string
*************************************************************************/
CXRString& CXRString::erase(size_t _Pos, size_t _Count)
{
	if (_Count == npos || _Pos + _Count >= m_Size)
	{
		resize(_Pos, 0);
	}
	else
	{
		memmove(&m_pString[_Pos], &m_pString[_Pos + _Count], m_Size + 1 - (_Pos + _Count));
	}
	return *this;
}

/*!***********************************************************************
@Function			find_first_not_of
@Input				_Ch		A char
@Input				_Off	Start position of the find
@Returns			Position of the first char that is not _Ch
@Description		Returns the position of the first char that is not _Ch
*************************************************************************/
size_t CXRString::find_first_not_of(char _Ch, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		if(m_pString[i]!=_Ch)
			return i;
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_not_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Returns			Position of the first char that is not in _Ptr
@Description		Returns the position of the first char that is not in _Ptr
*************************************************************************/
size_t CXRString::find_first_not_of(const char* _Ptr, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		bool bFound = false;
		// compare against each char from _Ptr
		for(size_t j=0;_Ptr[j]!=0;++j)
		{
			bFound = bFound || (m_pString[i]==_Ptr[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_not_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Input				_Count	Number of chars in _Ptr
@Returns			Position of the first char that is not in _Ptr
@Description		Returns the position of the first char that is not in _Ptr
*************************************************************************/
size_t CXRString::find_first_not_of(const char* _Ptr, size_t _Off, size_t _Count) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		bool bFound = false;
		// compare against each char from _Ptr
		for(size_t j=0;j<_Count;++j)
		{
			bFound = bFound || (m_pString[i]==_Ptr[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_not_of
@Input				_Str	A string
@Input				_Off	Start position of the find
@Returns			Position of the first char that is not in _Str
@Description		Returns the position of the first char that is not in _Str
*************************************************************************/
size_t CXRString::find_first_not_of(const CXRString& _Str, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		bool bFound = false;
		// compare against each char from _Str
		for(size_t j=0;j<_Str.m_Size;++j)
		{
			bFound = bFound || (m_pString[i]==_Str[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_of
@Input				_Ch		A char
@Input				_Off	Start position of the find
@Returns			Position of the first char that is _Ch
@Description		Returns the position of the first char that is _Ch
*************************************************************************/
size_t CXRString::find_first_of(char _Ch, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		if(m_pString[i]==_Ch)
			return i;
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Returns			Position of the first char that matches a char in _Ptr
@Description		Returns the position of the first char that matches a char in _Ptr
*************************************************************************/
size_t CXRString::find_first_of(const char* _Ptr, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		// compare against each char from _Ptr
		for(size_t j=0;_Ptr[j]!=0;++j)
		{
			if(m_pString[i]==_Ptr[j])
				return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Input				_Count	Size of _Ptr
@Returns			Position of the first char that matches a char in _Ptr
@Description		Returns the position of the first char that matches a char in _Ptr
*************************************************************************/
size_t CXRString::find_first_of(const char* _Ptr, size_t _Off, size_t _Count) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		// compare against each char from _Ptr
		for(size_t j=0;j<_Count;++j)
		{
			if(m_pString[i]==_Ptr[j])
				return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_first_of
@Input				_Str	A string
@Input				_Off	Start position of the find
@Returns			Position of the first char that matches a char in _Str
@Description		Returns the position of the first char that matches a char in _Str
*************************************************************************/
size_t CXRString::find_first_of(const CXRString& _Str, size_t _Off) const
{
	for(size_t i=_Off;i<m_Size;++i)
	{
		// compare against each char from _Ptr
		for(size_t j=0;j<_Str.m_Size;++j)
		{
			if(m_pString[i]==_Str[j])
				return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_not_of
@Input				_Ch		A char
@Input				_Off	Start position of the find
@Returns			Position of the last char that is not _Ch
@Description		Returns the position of the last char that is not _Ch
*************************************************************************/
size_t CXRString::find_last_not_of(char _Ch, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		if(m_pString[i]!=_Ch)
		{
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_not_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Returns			Position of the last char that is not in _Ptr
@Description		Returns the position of the last char that is not in _Ptr
*************************************************************************/
size_t CXRString::find_last_not_of(const char* _Ptr, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		bool bFound = false;
		// compare against each char from _Ptr
		for(size_t j=0;_Ptr[j]!=0;++j)
		{
			bFound = bFound || (m_pString[i]!=_Ptr[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_not_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Input				_Count	Length of _Ptr
@Returns			Position of the last char that is not in _Ptr
@Description		Returns the position of the last char that is not in _Ptr
*************************************************************************/
size_t CXRString::find_last_not_of(const char* _Ptr, size_t _Off, size_t _Count) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		bool bFound = false;
		// compare against each char from _Ptr
		for(size_t j=0;j<_Count;++j)
		{
			bFound = bFound || (m_pString[i]!=_Ptr[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_not_of
@Input				_Str	A string
@Input				_Off	Start position of the find
@Returns			Position of the last char that is not in _Str
@Description		Returns the position of the last char that is not in _Str
*************************************************************************/
size_t CXRString::find_last_not_of(const CXRString& _Str, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		bool bFound = false;
		// compare against each char from _Ptr
		for(size_t j=0;j<_Str.m_Size;++j)
		{
			bFound = bFound || (m_pString[i]!=_Str[j]);
		}
		if(!bFound)
		{	// return if no match
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_of
@Input				_Ch		A char
@Input				_Off	Start position of the find
@Returns			Position of the last char that is _Ch
@Description		Returns the position of the last char that is _Ch
*************************************************************************/
size_t CXRString::find_last_of(char _Ch, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		if(m_pString[i]==_Ch)
		{
			return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Returns			Position of the last char that is in _Ptr
@Description		Returns the position of the last char that is in _Ptr
*************************************************************************/
size_t CXRString::find_last_of(const char* _Ptr, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		// compare against each char from _Ptr
		for(size_t j=0;_Ptr[j]!=0;++j)
		{
			if(m_pString[i]==_Ptr[j])
				return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_of
@Input				_Ptr	A string
@Input				_Off	Start position of the find
@Input				_Count	Length of _Ptr
@Returns			Position of the last char that is in _Ptr
@Description		Returns the position of the last char that is in _Ptr
*************************************************************************/
size_t CXRString::find_last_of(const char* _Ptr, size_t _Off, size_t _Count) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		// compare against each char from _Ptr
		for(size_t j=0;j<_Count;++j)
		{
			if(m_pString[i]!=_Ptr[j])
				return i;
		}
	}
	return npos;
}

/*!***********************************************************************
@Function			find_last_of
@Input				_Str	A string
@Input				_Off	Start position of the find
@Returns			Position of the last char that is in _Str
@Description		Returns the position of the last char that is in _Str
*************************************************************************/
size_t CXRString::find_last_of(const CXRString& _Str, size_t _Off) const
{
	for(size_t i=m_Size-_Off-1;i<m_Size;--i)
	{
		// compare against each char from _Str
		for(size_t j=0;j<_Str.m_Size;++j)
		{
			if(m_pString[i]!=_Str[j])
				return i;
		}
	}
	return npos;
}

//CXRString& CXRString::insert(size_t _P0, const char* _Ptr)
//{
//	return replace(_P0, 0, _Ptr);
//}

//CXRString& CXRString::insert(size_t _P0, const char* _Ptr, size_t _Count)
//{
//	return replace(_P0, 0, _Ptr, _Count);
//}

//CXRString& CXRString::insert(size_t _P0, const CXRString& _Str)
//{
//	return replace(_P0, 0, _Str);
//}

//CXRString& CXRString::insert(size_t _P0, const CXRString& _Str, size_t _Off, size_t _Count)
//{
//	return replace(_P0, 0, _Str, _Off, _Count);
//}

//CXRString& CXRString::insert(size_t _P0, size_t _Count, char _Ch)
//{
//	return replace(_P0, 0, _Count, _Ch);
//}

/*!***********************************************************************
@Function			length
@Returns			Length of the string
@Description		Returns the length of the string
*************************************************************************/
size_t CXRString::length() const
{
	return m_Size;
}

/*!***********************************************************************
@Function			max_size
@Returns			The maximum number of chars that the string can contain
@Description		Returns the maximum number of chars that the string can contain
*************************************************************************/
size_t CXRString::max_size() const
{
	return 0x7FFFFFFF;
}

/*!***********************************************************************
@Function			push_back
@Input				_Ch A char to append
@Description		Appends _Ch to the string
*************************************************************************/
void CXRString::push_back(char _Ch)
{
	append(_Ch, 1);
}

//CXRString& replace(size_t _Pos1, size_t _Num1, const char* _Ptr)
//CXRString& replace(size_t _Pos1, size_t _Num1, const CXRString& _Str)
//CXRString& replace(size_t _Pos1, size_t _Num1, const char* _Ptr, size_t _Num2)
//CXRString& replace(size_t _Pos1, size_t _Num1, const CXRString& _Str, size_t _Pos2, size_t _Num2)
//CXRString& replace(size_t _Pos1, size_t _Num1, size_t _Count, char _Ch)

/*!***********************************************************************
@Function			reserve
@Input				_Count Size of string to reserve
@Description		Reserves space for _Count number of chars
*************************************************************************/
void CXRString::reserve(size_t _Count)
{
	if (_Count >= m_Capacity)
	{
		m_pString = (char*)realloc(m_pString, _Count + 1);
		m_Capacity = _Count + 1;
	}
}

/*!***********************************************************************
@Function			resize
@Input				_Count 	Size of string to resize to
@Input				_Ch		Character to use to fill any additional space
@Description		Resizes the string to _Count in length
*************************************************************************/
void CXRString::resize(size_t _Count, char _Ch)
{
	if (_Count <= m_Size)
	{
		m_Size = _Count;
		m_pString[m_Size] = 0;
	}
	else
	{
		append(_Count - m_Size,_Ch);
	}
}

//size_t rfind(char _Ch, size_t _Off = npos) const;
//size_t rfind(const char* _Ptr, size_t _Off = npos) const;
//size_t rfind(const char* _Ptr, size_t _Off = npos, size_t _Count) const;
//size_t rfind(const CXRString& _Str, size_t _Off = npos) const;

/*!***********************************************************************
@Function			size
@Returns			Size of the string
@Description		Returns the size of the string
*************************************************************************/
size_t CXRString::size() const
{
	return m_Size;
}

/*!***********************************************************************
@Function			substr
@Input				_Off	Start of the substring
@Input				_Count	Length of the substring
@Returns			A substring of the string
@Description		Returns the size of the string
*************************************************************************/
CXRString CXRString::substr(size_t _Off, size_t _Count) const
{
	return CXRString(*this, _Off, _Count);
}

/*!***********************************************************************
@Function			swap
@Input				_Str	A string to swap with
@Description		Swaps the contents of the string with _Str
*************************************************************************/
void CXRString::swap(CXRString& _Str)
{
	size_t Size = _Str.m_Size;
	size_t Capacity = _Str.m_Capacity;
	char* pString = _Str.m_pString;
	_Str.m_Size = m_Size;
	_Str.m_Capacity = m_Capacity;
	_Str.m_pString = m_pString;
	m_Size = Size;
	m_Capacity = Capacity;
	m_pString = pString;
}

/*!***********************************************************************
@Function			toLower
@Returns			An updated string
@Description		Converts the string to lower case
*************************************************************************/
CXRString&  CXRString::toLower()
{
	int i = 0;
	while ( (m_pString[i] = (m_pString[i]>='A'&&m_pString[i]<='Z') ? ('a'+m_pString[i])-'A': m_pString[i]) != 0) i++;
	return *this;
}

/*!***********************************************************************
@Function			+=
@Input				_Ch A char
@Returns			An updated string
@Description		+= Operator
*************************************************************************/
CXRString& CXRString::operator+=(char _Ch)
{
	return append(_Ch, 1);
}

/*!***********************************************************************
@Function			+=
@Input				_Ptr A string
@Returns			An updated string
@Description		+= Operator
*************************************************************************/
CXRString& CXRString::operator+=(const char* _Ptr)
{
	return append(_Ptr);
}

/*!***********************************************************************
@Function			+=
@Input				_Right A string
@Returns			An updated string
@Description		+= Operator
*************************************************************************/
CXRString& CXRString::operator+=(const CXRString& _Right)
{
	return append(_Right);
}

/*!***********************************************************************
@Function			=
@Input				_Ch A char
@Returns			An updated string
@Description		= Operator
*************************************************************************/
CXRString& CXRString::operator=(char _Ch)
{
	return assign(_Ch, 1);
}

/*!***********************************************************************
@Function			=
@Input				_Ptr A string
@Returns			An updated string
@Description		= Operator
*************************************************************************/
CXRString& CXRString::operator=(const char* _Ptr)
{
	return assign(_Ptr);
}

/*!***********************************************************************
@Function			=
@Input				_Right A string
@Returns			An updated string
@Description		= Operator
*************************************************************************/
CXRString& CXRString::operator=(const CXRString& _Right)
{
	return assign(_Right);
}

/*!***********************************************************************
@Function			[]
@Input				_Off An index into the string
@Returns			A character
@Description		[] Operator
*************************************************************************/
CXRString::const_reference CXRString::operator[](size_t _Off) const
{
	return m_pString[_Off];
}

/*!***********************************************************************
@Function			[]
@Input				_Off An index into the string
@Returns			A character
@Description		[] Operator
*************************************************************************/
CXRString::reference CXRString::operator[](size_t _Off)
{
	return m_pString[_Off];
}

/*!***********************************************************************
@Function			+
@Input				_Left A string
@Input				_Right A string
@Returns			An updated string
@Description		+ Operator
*************************************************************************/
CXRString operator+ (const CXRString& _Left, const CXRString& _Right)
{
	return CXRString(_Left).append(_Right);
}

/*!***********************************************************************
@Function			+
@Input				_Left A string
@Input				_Right A string
@Returns			An updated string
@Description		+ Operator
*************************************************************************/
CXRString operator+ (const CXRString& _Left, const char* _Right)
{
	return CXRString(_Left).append(_Right);
}

/*!***********************************************************************
@Function			+
@Input				_Left A string
@Input				_Right A string
@Returns			An updated string
@Description		+ Operator
*************************************************************************/
CXRString operator+ (const CXRString& _Left, const char _Right)
{
	return CXRString(_Left).append(_Right);
}

/*!***********************************************************************
@Function			+
@Input				_Left A string
@Input				_Right A string
@Returns			An updated string
@Description		+ Operator
*************************************************************************/
CXRString operator+ (const char* _Left, const CXRString& _Right)
{
	return CXRString(_Left).append(_Right);
}

/*!***********************************************************************
@Function			+
@Input				_Left A string
@Input				_Right A string
@Returns			An updated string
@Description		+ Operator
*************************************************************************/
CXRString operator+ (const char _Left, const CXRString& _Right)
{
	return CXRString(_Left).append(_Right);
}

/*************************************************************************
* MISCELLANEOUS UTILITY FUNCTIONS
*************************************************************************/
/*!***********************************************************************
@Function			XRStringGetFileExtension
@Input				strFilePath A string
@Returns			Extension
@Description		Extracts the file extension from a file path.
					Returns an empty CXRString if no extension is found.
************************************************************************/
CXRString XRStringGetFileExtension(const CXRString& strFilePath)
{
	CXRString::size_type idx = strFilePath.find_last_of ( '.' );

    if (idx == CXRString::npos)
    	return CXRString("");
    else
    	return strFilePath.substr(idx);
}

/*!***********************************************************************
@Function			XRStringGetContainingDirectoryPath
@Input				strFilePath A string
@Returns			Directory
@Description		Extracts the directory portion from a file path.
************************************************************************/
CXRString XRStringGetContainingDirectoryPath(const CXRString& strFilePath)
{
	size_t i32sep = strFilePath.find_last_of('/');
	if(i32sep == strFilePath.npos)
	{
		i32sep = strFilePath.find_last_of('\\');
		if(i32sep == strFilePath.npos)
		{	// can't find an actual \ or / so leave it be
			return strFilePath;
		}
	}
	return strFilePath.substr(0,i32sep);
}

/*!***********************************************************************
@Function			XRStringGetFileName
@Input				strFilePath A string
@Returns			FileName
@Description		Extracts the name and extension portion from a file path.
************************************************************************/
CXRString XRStringGetFileName(const CXRString& strFilePath)
{
	size_t i32sep = strFilePath.find_last_of('/');
	if(i32sep == strFilePath.npos)
	{
		i32sep = strFilePath.find_last_of('\\');
		if(i32sep == strFilePath.npos)
		{	// can't find an actual \ or / so leave it be
			return strFilePath;
		}
	}
	return strFilePath.substr(i32sep+1,strFilePath.length());
}

/*!***********************************************************************
@Function			XRStringStripWhiteSpaceFromStartOf
@Input				strLine A string
@Returns			Result of the white space stripping
@Description		strips white space characters from the beginning of a CXRString.
************************************************************************/
CXRString XRStringStripWhiteSpaceFromStartOf(const CXRString& strLine)
{
	size_t start = strLine.find_first_not_of(" \t	");
	if(start!=strLine.npos)
		return strLine.substr(start,strLine.length()-start+1);
	return strLine;
}

///*!***************************************************************************

#endif // _USING_XRSTRING_

/*****************************************************************************
 End of file (XRString.cpp)
*****************************************************************************/

