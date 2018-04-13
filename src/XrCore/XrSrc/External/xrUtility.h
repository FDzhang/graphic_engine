#ifndef __XR_UTILITY_H__
#define __XR_UTILITY_H__

#include "xrTypes.h"
#include "xrEnum.h"

#define VERTTYPEMUL(a,b)			( (Float32)((a)*(b)) )
#define VERTTYPEDIV(a,b)			( (Float32)((a)/(b)) )

#define f2vt(x)						(x)
#define vt2f(x)						(x)
#define	XRCOS(x)					((Float32)cos(x))
#define	XRSIN(x)					((Float32)sin(x))
#define	XRTAN(x)					((Float32)tan(x))
#define	XRACOS(x)					((Float32)acos(x))
#define XRABS(a)					((a) <= 0 ? -(a) : (a) )

#define XR_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define XR_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define XR_CLAMP(x, l, h)      (PVRT_MIN((h), PVRT_MAX((x), (l))))

#define XR_PI						(3.1415926535f)
#define XR_HALF_PI						(XR_PI / 2.0f)

#define XR_DEG2RAD(x)						(x/180.0*XR_PI)
#define XR_RAD2DEG(x)						(x/XR_PI*180.0)


//#undef max
//#undef min
////////////// math /////////////////
//template<class T>
//inline T max(T a, T b)
//{
//    return a > b ? a:b;
//}
//template<class T>
//inline T min(T a, T b)
//{
//    return a< b ? a:b;
//}

inline float xrfabs(float x)
{
	if (x>=0.0) return x;
	else return -x;
}

inline bool isCloseEnough(float f1, float f2)
    {
        // Determines whether the two floating-point values f1 and f2 are
        // close enough together that they can be considered equal.

        return xrfabs((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < 1e-6f;
    }
inline Int32 getSign(Int32 a)
{
    if (a>=0) return 1;
    else return -1;
}


template<class T>
inline Void swap(T& t1,T& t2)
{
	T tmp = t1;
	t1 = t1;
	t2 = tmp;
}

inline Int32 XR_BUFFER_ELEMENT_SIZE(Int32 fmt)
{
	Int32 size = 0;
	if (fmt & XR_R32) size+=4;
	if (fmt & XR_G32) size+=4;
	if (fmt & XR_B32) size+=4;
	if (fmt & XR_A32) size+=4;

	if (fmt & XR_R16) size+=2;
	if (fmt & XR_G16) size+=2;
	if (fmt & XR_B16) size+=2;
	if (fmt & XR_A16) size+=2;

	if (fmt & XR_R8) size+=1;
	if (fmt & XR_G8) size+=1;
	if (fmt & XR_B8) size+=1;
	if (fmt & XR_A8) size+=1;

	return size;
}

inline Int32 XR_VERTEX_SIZE(XRVertexLayout layout)
{
	Int32 size=0;

	//switch (layout) {
	//case XR_VERTEX_LAYOUT_P:
	//	return 3*4;
	//case XR_VERTEX_LAYOUT_PT:
	//	return 5*4;
	//case XR_VERTEX_LAYOUT_PNT:
	//	return 8*4;
	//case XR_VERTEX_LAYOUT_PNTWI:
	//	return 10*4;
	//default:
	//	return 0;
	//}

	if (layout & XR_VERTEX_LAYOUT_P) size += 3*4;
	if (layout & XR_VERTEX_LAYOUT_N) size += 3*4;
	if (layout & XR_VERTEX_LAYOUT_B) size += 4*4;
	if (layout & XR_VERTEX_LAYOUT_T) size += 2*4;
	if (layout & XR_VERTEX_LAYOUT_W) size += 1*4;
	if (layout & XR_VERTEX_LAYOUT_I) size += 1*4;
	if (layout & XR_VERTEX_LAYOUT_A) size += 1*4;
	if (layout & XR_VERTEX_LAYOUT_K) size += 1*4;
    if (layout & XR_VERTEX_LAYOUT_C) size += 2 * 4;
	if (layout & XR_VERTEX_LAYOUT_D) size += 1 * 4;
	if (layout & XR_VERTEX_LAYOUT_E) size += 2 * 4;
	if (layout & XR_VERTEX_LAYOUT_F) size += 1 * 4;
	if (layout & XR_VERTEX_LAYOUT_G) size += 2 * 4;
	if (layout & XR_VERTEX_LAYOUT_H) size += 1 * 4;
	if (layout & XR_VERTEX_LAYOUT_J) size += 2 * 4;
	if (layout & XR_VERTEX_LAYOUT_L) size += 1 * 4;
	
	return size;
}

inline Int32 GetAPCount(UInt32 AP)
{
	Int32 count = 0;
	if (AP & AP_X) count++;
	if (AP & AP_Y) count++;
	if (AP & AP_Z) count++;
	if (AP & AP_RX) count++;
	if (AP & AP_RY) count++;
	if (AP & AP_RZ) count++;
	if (AP & AP_SX) count++;
	if (AP & AP_SY) count++;
	if (AP & AP_SZ) count++;
	return count;
}

inline Int32 PadTo16(Int32 size) 
{
	return size + 16 - (size % 16);
}
#endif//__XR_UTILITY_H__