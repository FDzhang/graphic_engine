#ifndef __XR_OS_H__
#define __XR_OS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include "../External/xrTypes.h"

#define XrMemset memset
#define XrAssert assert
#define XrMemcpy memcpy
#define LINUX_J6
UInt32 XrGetTime();
#ifdef LINUX_J6|| #ifdef WIN_32
#define xrprintf //
#endif
#ifdef WIN_32
void xrprintf(const char * format,...);
#endif
void Debug();

#define XrFile FILE

inline XrFile* XrFOpen(String path, String mode=0) { return fopen(path, mode); }
inline Void XrFClose(XrFile* file) { fclose(file); }
inline Int32 XrFSeek(XrFile* stream, Int32 offset, Int32 type) { return fseek(stream, offset, type); }
inline Int32 XrFTell(XrFile* stream) { return ftell(stream); }
inline Int32 XrFRead(Void* ptr, Int32 size, Int32 nmemb, XrFile* stream) { return fread(ptr, size, nmemb, stream); }
inline Int32 XrFWrite(Void* ptr, Int32 size, Int32 nmemb, XrFile* stream) { return fwrite(ptr, size, nmemb, stream); }
inline Int32 XrFEOF(XrFile *stream) { return feof(stream); }
inline String XrFGets(String s, Int32 size, XrFile* stream) { return fgets(s, size, stream); }
inline Int32 XrFGetc(XrFile *stream) { return fgetc(stream); }

#endif //__XR_OS_H__
