#ifndef _XRAABBOX_H
#define _XRAABBOX_H
#include "XrMathEx.h"

class AABBox
{
public:
		AABBox()
		{
		}
		AABBox(XRVec3 const & vMin, XRVec3 const & vMax)
				: m_min(vMin), m_max(vMax)
		{
			XrAssert(vMin.x <= vMax.x);
			XrAssert(vMin.y <= vMax.y);
			XrAssert(vMin.z <= vMax.z);
		}
		AABBox(AABBox const & rhs)
				:m_min(rhs.m_min), m_max(rhs.m_max)
		{
		}

		AABBox& operator+=(XRVec3 const & rhs)
		{
			m_min += rhs;
			m_max += rhs;
			return *this;
		}
		AABBox& operator-=(XRVec3 const & rhs)
		{
			m_min -= rhs;
			m_max -= rhs;
			return *this;
		}
		AABBox& operator*=(Float32 const & rhs)
		{
			this->Min() *= rhs;
			this->Max() *= rhs;
			return *this;
		}
		AABBox& operator/=(Float32 const & rhs)
		{
			return this->operator*=(1.0f / rhs);
		}
		AABBox& operator&=(AABBox const & rhs)
		{
			m_min = XR_MAX(this->Min(), rhs.Min());
			m_max = XR_MIN(this->Max(), rhs.Max());
			return *this;
		}
		AABBox& operator|=(AABBox const & rhs)
		{
			m_min = XR_MIN(this->Min(), rhs.Min());
			m_max = XR_MAX(this->Max(), rhs.Max());
			return *this;
		}

		AABBox& operator=(AABBox const & rhs)
		{
			if (this != &rhs)
			{
				this->Min() = rhs.Min();
				this->Max() = rhs.Max();
			}
			return *this;
		}

		// 一元操作符
		AABBox const operator+() const
		{
			return *this;
		}
		AABBox const operator-() const
		{
			return AABBox(-this->Max(), -this->Min());
		}

		XRVec3 operator[](UInt32 i) const
		{
			XrAssert(i < 8);

			return XRVec3((i & 1UL) ? this->Max().x : this->Min().x,
				(i & 2UL) ? this->Max().y : this->Min().y,
				(i & 4UL) ? this->Max().z : this->Min().z);
		}

		// 属性
		Float32 Width() const
		{
			return this->Max().x - this->Min().x;
		}
		Float32 Height() const
		{
			return this->Max().y - this->Min().y;
		}
		Float32 Depth() const
		{
			return this->Max().z - this->Min().z;
		}
		bool IsEmpty() const
		{
			return this->Min() == this->Max();
		}

		XRVec3 const LeftBottomNear() const
		{
			return this->Min();
		}
		XRVec3 const LeftTopNear() const
		{
			return XRVec3(this->Min().x, this->Max().y, this->Min().z);
		}
		XRVec3 const RightBottomNear() const
		{
			return XRVec3(this->Max().x, this->Min().y, this->Min().z);
		}
		XRVec3 const RightTopNear() const
		{
			return XRVec3(this->Max().x, this->Max().y, this->Min().z);
		}
		XRVec3 const LeftBottomFar() const
		{
			return XRVec3(this->Min().x, this->Min().y, this->Max().z);
		}
		XRVec3 const LeftTopFar() const
		{
			return XRVec3(this->Min().x, this->Max().y, this->Max().z);
		}
		XRVec3 const RightBottomFar() const
		{
			return XRVec3(this->Max().x, this->Min().y, this->Max().z);
		}
		XRVec3 const RightTopFar() const
		{
			return this->Max();
		}

		XRVec3& Min()
		{
			return m_min;
		}
		XRVec3 const & Min() const
		{
			return m_min;
		}
		XRVec3& Max()
		{
			return m_max;
		}
		XRVec3 const & Max() const
		{
			return m_max;
		}
		XRVec3 Center() const
		{
			return (m_min + m_max) / 2.0f;
		}
		XRVec3 HalfSize() const
		{
			return (m_max - m_min) / 2.0f;
		}

		Boolean VecInBound(XRVec3 const & v) const
		{
			return MathLib::intersect_point_aabb(v, *this);
		}
		//Float32 MaxRadiusSq() const
		//{
		//	return std::max<T>(MathLib::length_sq(this->Max()), MathLib::length_sq(this->Min()));
		//}

		//bool Intersect(AABBox const & aabb) const
		//{
		//	return MathLib::intersect_aabb_aabb(*this, aabb);
		//}
		//bool Intersect(OBBox_T<T> const & obb) const
		//{
		//	return MathLib::intersect_aabb_obb(*this, obb);
		//}
		//bool Intersect(Sphere_T<T> const & sphere) const
		//{
		//	return MathLib::intersect_aabb_sphere(*this, sphere);
		//}
		//bool Intersect(Frustum_T<T> const & frustum) const
		//{
		//	return MathLib::intersect_aabb_frustum(*this, frustum);
		//}

		friend Boolean
		operator==(AABBox const & lhs, AABBox const & rhs)
		{
			return (lhs.Min() == rhs.Min()) && (rhs.Max() == rhs.Max());
		}

protected:
	XRVec3 m_min;
	XRVec3 m_max;
};


#endif