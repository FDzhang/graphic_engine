#ifndef __PRIMITIVE_GENERATOR_H__
#define __PRIMITIVE_GENERATOR_H__
#include "../Common/XrInternal.h"

//class CGLPrimitive
//{
//public:
//	CGLPrimitive();
//	~CGLPrimitive();
//	
//	virtual xr_state InitMesh();
//	virtual xr_state SetMaterial(class CMaterial* mtl);
//private:
//	class CMaterial* m_mtl;
//};
//
//class CCUBE : public CGLPrimitive
//{
//public:
//	CCUBE();
//	~CCUBE();
//
//	xr_state InitMesh();
//	Void Draw();
//
//private:
//	class CVertexArray*	m_va;
//};

xr_state GenCubeMesh(Float32 xs, Float32 ys, Float32 zs, class CMesh* mesh);
Float32* GenPlaneMeshH(Float32 sx, Float32 sy, Int32 dx, Int32 dy, class CMesh* mesh, Region* roi);
Float32* GenPlaneMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, class CMesh* mesh, Region* roi);
Float32* GenLineMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi);
Float32* GenPlaneDynamicMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi);
Float32* GenPlaneDynamicMeshH(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi);
Float32* GenPlaneArcPlaneMeshV(Float32 r, Float32 s_a, Float32 e_a,  CMesh* mesh, Region* roi);

xr_state GenLayerMesh(Int32 sx, Int32 sy, Float32 texScaleX, Float32 texScaleY, Int32 dx, Int32 dy, CMesh* mesh);
xr_state Gen2DPath(float* inputData,int dataNum,int elemNum,float width,float midRoundRatio,float endRoundRatio,float deltaRad,float texScale,bool bLoop, CMesh* mesh);
xr_state Gen3DArrowPath(float* inputData,int dataNum,int elemNum, float width, float heigt, float arrowWidth, float arrowHeight, float midRoundRatio,float deltaRad, CMesh* mesh);
xr_state GenRoundedRect(float roundRatio,float deltaRad, CMesh* mesh);
xr_state GenLineSkeletonMesh(Float32* input,UInt32 pointNum,UInt32 vertexAttr,UInt32 stride,Float32 width,Float32 height,CMesh* mesh);

#endif // __PRIMITIVE_GENERATOR_H__
