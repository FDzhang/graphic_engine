#include "XrMathEx.h"
#include "XrAABBox.h"

Boolean operator <(const XRVec3& v1,const XRVec3& v2)
{
	return (v1.x < v2.x && v1.y < v2.y && v1.z < v2.z );
}
Boolean operator >(const XRVec3& v1,const XRVec3& v2)
{
	return (v1.x > v2.x && v1.y > v2.y && v1.z > v2.z );
}
namespace  MathLib
{
typedef XRVec3 vec3;

Void computeAABBox(AABBox& bbox,Float32* data,UInt32 nvtxStride,UInt32 nVtxNum)
{
	vec3 vmin(1000.0f,1000.0f,1000.0f);
	vec3 vmax(-1000.0f,-1000.0f,-1000.0f);
	for( UInt32 i = 0 ; i < nVtxNum ; ++i){
		vec3 v(data[i*nvtxStride],data[i*nvtxStride+1],data[i*nvtxStride+2]);
		if( v.x < vmin.x ) vmin.x = v.x;
		else if( v.x > vmax.x ) vmax.x = v.x;
		if( v.y < vmin.y ) vmin.y = v.y;
		else if( v.y > vmax.y ) vmax.y = v.y;
		if( v.z < vmin.z) vmin.z = v.z;
		else if( v.z > vmax.z ) vmax.z = v.z;
	}
	bbox.Max() = vmax;
	bbox.Min() = vmin;
}
Boolean intersect_point_aabb(const XRVec3& pt,const AABBox& bbox)
{
	return ( ( pt.x <= bbox.Max().x && pt.x >= bbox.Min().x) &&
		   ( pt.y <= bbox.Max().y && pt.y >= bbox.Min().y)&&
		   ( pt.z <= bbox.Max().z && pt.x >= bbox.Min().z));
}
Boolean intersect_aabb_ray(const AABBox& aabb,const Ray& ray,Float32& dist)
{
	//const Float32* const orig = (Float32*)(&ray.orig.x);
	//const Float32* const dir = (Float32*)(&ray.dir.x);
	//Float32 t_near = Float32(-1e10);
	//Float32 t_far = Float32(+1e10);
	//const Float32* const vmin = (Float32*)(&aabb.Min().x);
	//const Float32* const vmax = (Float32*)(&aabb.Max().x);

	//for (UInt32 i = 0; i < 3; ++i)
	//{
	//	if (dir[i] == 0.0f)
	//	{
	//		if ((dir[i] < vmin[i]) || (dir[i] > vmax[i]))
	//		{
	//			return false;
	//		}
	//	}
	//	else
	//	{
	//		float t1 = (vmin[i] - orig[i]) / dir[i];
	//		float t2 = (vmax[i] - orig[i]) / dir[i];
	//		if (t1 > t2)
	//		{
	//			swap(t1, t2);
	//		}
	//		if (t1 > t_near)
	//		{
	//			t_near = t1;
	//		}
	//		if (t2 < t_far)
	//		{
	//			t_far = t2;
	//		}

	//		if (t_near > t_far)
	//		{
	//			// box is missed
	//			return false;
	//		}
	//		if (t_far < 0)
	//		{
	//			// box is behind ray
	//			return false;
	//		}
	//	}
	//}

	//return true;
	Float32 lowt = 0.0f; //store the nearest intersect point
	Float32 t;
	Boolean hit = FALSE;
	vec3 hitpoint;
	const vec3& vmin = aabb.Min();
	const vec3& vmax = aabb.Max();
	const vec3& rayorig = ray.orig;
	const vec3& raydir = ray.dir;

	//test if ray is in aabb
	if(rayorig > vmin && rayorig < vmax)
	{
		dist = 0;
		return TRUE;
	}

	//test if ray intersects with one of six planes of these aabb
	if(rayorig.x < vmin.x && raydir.x > 0)
	{
		t = (vmin.x - rayorig.x)/raydir.x; //ray and plane intersect
											 //
		if(t>0){
			hitpoint = rayorig + raydir * t;
			if(hitpoint.y>=vmin.y && hitpoint.y<=vmax.y && hitpoint.z>=vmin.z && hitpoint.z<=vmax.z && (!hit || t<lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	}

	if(rayorig.x > vmax.x && raydir.x < 0){
		t = (vmax.x - rayorig.x)/raydir.x;
		if(t>0){
			hitpoint = rayorig + raydir*t;
			if(hitpoint.y>vmin.y && hitpoint.y<=vmax.y &&
				hitpoint.z>=vmin.z && hitpoint.z<=vmax.z &&
				(!hit || t<lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	}

	if(rayorig.y<vmin.y && raydir.y>0)
	{
		t = (vmin.y-rayorig.y)/raydir.y;
		if(t>0){
			hitpoint = rayorig + raydir*t;
			if (hitpoint.x >= vmin.x && hitpoint.x <= vmax.x &&
				hitpoint.z >= vmin.z && hitpoint.z <= vmax.z &&
				(!hit || t < lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	}

	if (rayorig.y > vmax.y && raydir.y < 0)
	{
		t = (vmax.y - rayorig.y) / raydir.y;
		if (t > 0){
			hitpoint = rayorig + raydir * t;
			if (hitpoint.x >= vmin.x && hitpoint.x <= vmax.x &&
				hitpoint.z >= vmin.z && hitpoint.z <= vmax.z &&
				(!hit || t < lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	}

	if (rayorig.z < vmin.z && raydir.z > 0)
	{
		t = (vmin.z - rayorig.z) / raydir.z;
		if (t > 0){
			hitpoint = rayorig + raydir * t;
			if (hitpoint.x >= vmin.x && hitpoint.x <= vmax.x &&
				hitpoint.y >= vmin.y && hitpoint.y <= vmax.y &&
				(!hit || t < lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	}

	if (rayorig.z > vmax.z && raydir.z < 0)
	{
		t = (vmax.z - rayorig.z) / raydir.z;
		if (t > 0)
		{
			hitpoint = rayorig + raydir * t;
			if (hitpoint.x >= vmin.x && hitpoint.x <= vmax.x &&
				hitpoint.y >= vmin.y && hitpoint.y <= vmax.y &&
				(!hit || t < lowt)){
				hit = TRUE;
				lowt = t;
			}
		}
	} 

	dist = lowt;
	return hit;


}


Void transform_ray(const Ray& ray,const XRMat4& mat,Ray& out)
{
	//XRVec4 outdir;
	XRVec4 dir(ray.dir,0.0f);
	out.orig = mat * XRVec4(ray.orig,1.0f);
	out.dir = (mat * dir);
	//out.dir.x = outdir.x;
	//out.dir.y = outdir.y;
	//out.dir.z = outdir.z;

}
void esUnProject(  Float32   winX,  
  Float32   winY,    
  const XRMat4&  eyeMatrix,  
  const XRMat4&  proj,  
  const Int32 *   view,  
  Ray* ray)
{
	if( view && ray )
	{
		XRMat4 inverseEyeMatrix = (eyeMatrix).inverse();
		///
		Float32 xw = (winX-view[0])*2 / view[2]-1;
		Float32 yw = (winY-view[1])*2 / view[3]-1;
		Float32 zw = - 1.0f;
	
		XRVec4 viewpt ;	///viewpt--in the eye space the farest plane
		XRVec4 worldpt;	///viewpt in the world space,
		XRVec4 eyept;
		viewpt.x = xw/(proj)(0,0);
		viewpt.y = yw/(proj)(1,1);
		viewpt.z = -1.0f;
		viewpt.w = 1.0f;
		
		eyept.x = inverseEyeMatrix(0,3);
		eyept.y = inverseEyeMatrix(1,3);
		eyept.z = inverseEyeMatrix(2,3);
		
		ray->orig.x = eyept.x;
		ray->orig.y = eyept.y;
		ray->orig.z = eyept.z;
		//ray.dir ;
		worldpt = inverseEyeMatrix * viewpt;
		ray->dir.x = worldpt.x - eyept.x;
		ray->dir.y = worldpt.y - eyept.y;
		ray->dir.z = worldpt.z - eyept.z;
	}
}

}