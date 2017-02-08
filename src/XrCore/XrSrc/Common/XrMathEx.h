#ifndef _XRMATHEX_H
#define _XRMATHEX_H

#include "../Common/XrInternal.h"
#include "XRVector.h"
#include "XRQuaternion.h"

typedef struct _Ray
{
	XRVec3 orig;
	XRVec3 dir;
}Ray;

class AABBox;

extern Boolean operator <(const XRVec3& v1,const XRVec3& v2);
extern Boolean operator >(const XRVec3& v1,const XRVec3& v2);
namespace MathLib
{
extern Void computeAABBox(AABBox& bbox,Float32* data,UInt32 nvtxStride,UInt32 nVtxNum);
extern Boolean intersect_point_aabb(const XRVec3& pt,const AABBox& bbox);
extern Boolean intersect_aabb_ray(const AABBox& bbox,const Ray& ray,Float32& dist);
extern Void transform_ray(const Ray& ray,const XRMat4& mat,Ray& out);

extern Void esUnProject( Float32   winX,  
  Float32   winY,    
  const XRMat4& eyeMatrix,  
  const XRMat4& proj,  
  const Int32 *   view,  
  Ray* ray);
}


#endif