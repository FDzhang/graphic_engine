#ifndef __STRING_HASH_H__
#define __STRING_HASH_H__
#include "../External/xrIntrinsic.h"

#define HASH_OFFSET     0
#define HASH_A          1
#define HASH_B          2

////////////////////// hash /////////////////////////
void prepareHashInfoTable();
unsigned long HashString(const char* lpszFileName, unsigned long dwHashType);
unsigned long HashString(wchar_t* lpszFileName, unsigned long dwHashType);

#endif  //__STRING_HASH_H__
