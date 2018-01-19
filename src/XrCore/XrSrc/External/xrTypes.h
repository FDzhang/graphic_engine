#ifndef __XRTYPES_H__
#define __XRTYPES_H__

typedef int								        Int32;
typedef unsigned int							UInt32;
typedef unsigned short							UInt16;
typedef long long int							Int64;
typedef unsigned char							UInt8;
typedef char									Int8;
typedef float									Float32;
typedef double									Float64;
typedef int							            xr_state;
typedef void									Void;
typedef bool									Boolean;
typedef	short		                            Int16;
typedef	char                                    CHAR;
typedef unsigned char							UChar;
typedef long									Long;
#ifdef WIN_32
typedef int								        int32;
typedef float									float32;
#endif

#define XrMemset memset
#define XrAssert assert
#define XrMemcpy memcpy

//#ifdef _WIN32
//#include <Windows.h>
//#endif
//typedef WCHAR*									WString;
typedef char*									String;
typedef const char*								ConstString;

#define MIN_8U 0x00
#define MID_8U 0x7F
#define MAX_8U 0xFF

#define MIN_16U 0x0000
#define MID_16U 0x7FFF
#define MAX_16U 0xFFFF

#define MIN_32U 0x00000000
#define MID_32U 0x7FFFFFFF
#define MAX_32U 0xFFFFFFFF

#define DOUBLE_BUFFER 0x02
#define TRIPLE_BUFFER 0x03

#define Pi 3.14159265f

#define Deg2Rad(x) ( x/180.0f*Pi)

#define XrASSERT(cond) {}

#define XRFAILED(x) (x<0)
#define XR_SUCCEEDED(x) (x>=0)
#define BYTES_PER_PIXEL(x) ((15&x)*3+((x&240)>>8))

#define IsFloatEqual(x,y,epsilon) (((x)==(y))?true:\
	(fabs((x)-(y))<(epsilon))?true:\
	(fabs(x)>fabs(y))?\
	((fabs(((x)-(y))/(x))<(epsilon))?true:false):\
	((fabs(((x)-(y))/(y))<(epsilon))?true:false))

#define XR_ERROR_MESSAGE printf
#define XR_WARNING_MESSAGE printf

#define MAKECOLOR(x) (*((Pixel*)(&x)))

#define SAFE_RELEASE(x) { if (x) x->Release(); x = 0; }
#define SAFE_DELETE(x) { if (x) delete x; x = 0; }
#define SAFE_FREE(x) { if (x) free(x); x = 0; }

//#define XrXRFAILED(x) x
//#define INLINE inline
#define	TRUE true
#define	FALSE false
//#define NULL 0
#define	NOERROR 0
#define	debug _asm int 3

#define E_NOT_EXIST    -1
#define E_NOT_MATCH    -1
#define E_INVALID_ARGUMENT    -1
#define E_OUT_OF_MEMORY    -1
#define E_LAYER_FULL    -1
#define E_WRONG_LAYER_TYPE    -1
#define XR_FAILED    -1
#define E_NOT_WINDOW    -1
#define E_NOT_ACTIVE_WINDOW    -1
#define E_NOT_SUPPORTED    -1
#define E_NOT_INITIALIZE    -1
#define E_INTERRUPTED    -1
#define E_OUT_OF_MEMORY    -1
#define E_OUT_OF_RANGE    -1
#define E_NOT_IMPLEMENTED    -1
#define E_INVALID_INDEX    -1
#define E_NOT_AVAILABLE    -1

#define E_INVALID_LAYER_FORMAT    -1
#define E_LAYER_NOT_EXIST    -1

#define S_RENDERED_ALL_SUB 1
#define S_ABORT 1
#define S_EXCEPTION_CONTINUE 1

#define XR_OK 0


#define	Pixel RGBA32_U8
#define Point Point2Df
#define Color RGBA32


typedef struct tagRGBA32 {
	Void Set(Float32 _r, Float32 _g, Float32 _b, Float32 _a) 
	{
		r=_r;g=_g;b=_b;a=_a;
	}
	Void operator=(tagRGBA32& src)
	{
		r = src.r;
		g = src.g;
		b = src.b;
		a = src.a;
	}
	Boolean operator==(tagRGBA32& src)
	{
		return (r==src.r)&&(g==src.g)&&(b==src.b)&&(a==src.a);
	}

	Float32 	r;
	Float32		g;
	Float32		b;
	Float32		a;
} RGBA32;

typedef struct tagRGBA32_U8 {
	Void Set(UInt8 _r, UInt8 _g, UInt8 _b, UInt8 _a) 
	{
		r=_r;g=_g;b=_b;a=_a;
	}
	Void operator=(tagRGBA32_U8& src)
	{
		r = src.r;
		g = src.g;
		b = src.b;
		a = src.a;
	}
	Boolean operator==(tagRGBA32& src)
	{
		return (r==src.r)&&(g==src.g)&&(b==src.b)&&(a==src.a);
	}

	UInt8 		r;
	UInt8		g;
	UInt8		b;
	UInt8		a;
} RGBA32_U8;

typedef struct tagARGB32_U8 {
	UInt8 		a;
	UInt8		r;
	UInt8		g;
	UInt8		b;
} ARGB32_U8;

typedef struct tagRGB24_U8 {
	UInt8		r;
	UInt8		g;
	UInt8		b;
} RGB24_U8;

typedef struct tagPoint2Di {
	Int32	x;
	Int32	y;
} Point2Di;

typedef struct tagPoint2Df {
	Float32	    x;
	Float32 	y;
} Point2Df;

#define Xr_malloc(TYPE,size)	static_cast<TYPE*>(malloc(size))

#define Xr_free(pBuf)	if( pBuf ) free(pBuf);

#define Xr_Self_H	\
	public:\
		Void* GetRealType(){ return m_self; }\
	protected:\
		Void* m_self;
#define Xr_Self_Src		m_self = this;

#define etou(data)	(UInt32)(data)

#define MAX_PATH 256
#define MAX_NAME 128
#endif//__XRTYPES_H__