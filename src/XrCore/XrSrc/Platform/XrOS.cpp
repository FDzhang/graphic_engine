#include "XrOS.h"
#include <time.h>
#ifdef WIN_32
#include <Windows.h>
#endif
#ifdef LINUX_J6
#include <sys/time.h>
#endif

UInt32 XrGetTime()
{
#ifdef WIN_32
    return (GetTickCount()); 
#endif

#ifdef LINUX_J6
      /* static struct timespec rt;
	clock_gettime(CLOCK_REALTIME, &rt);
	return (rt.tv_sec * 1000 + rt.tv_nsec/1000000);*/
      static struct timeval tv;
      gettimeofday(&tv,NULL);
      return (tv.tv_sec * 1000 + tv.tv_usec/1000);
#endif
}

void GetFileFullPath(char* in, char* out)
{
	strcpy(out, in);
}

#ifdef WIN_32
void __cdecl xrprintf(const char *format, ...)
{
char    buf[4096], *p = buf;
va_list args;
int     n;

        va_start(args, format);
        n = _vsnprintf(p, sizeof buf - 3, format, args); // buf-3 is room for CR/LF/NUL
        va_end(args);

        p += (n < 0) ? sizeof buf - 3 : n;

        while ( p > buf  &&  isspace(p[-1]) )
                *--p = '\0';

        *p++ = '\r';
        *p++ = '\n';
        *p   = '\0';

        OutputDebugStringA(buf);
}
#endif
