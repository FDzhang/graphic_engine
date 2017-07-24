#include "PrimitiveGenerator.h"
#include "../XrNode/Mesh/CMesh.h"


#include <stdlib.h>

#define TEX_COORD_MINX 0.0f
#define TEX_COORD_MAXX 1.0f
#define TEX_COORD_MINY 1.0f
#define TEX_COORD_MAXY 0.0f


// Interleaved vertex data
Float32 afVerticesCube[] = {
	// Front Face
	-1.0f,-1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	1.0f,-1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	-1.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY,

	// Back Face
	-1.0f,-1.0f,-1.0f,
	0.0f, 0.0f,-1.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	1.0f,-1.0f,-1.0f,
	0.0f, 0.0f,-1.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	1.0f, 1.0f,-1.0f,
	0.0f, 0.0f,-1.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	-1.0f, 1.0f,-1.0f,
	0.0f, 0.0f,-1.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY,

	// Top Face
	-1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	1.0f, 1.0f,-1.0f,
	0.0f, 1.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	-1.0f, 1.0f,-1.0f,
	0.0f, 1.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY,

	// Bottom Face
	-1.0f,-1.0f, 1.0f,
	0.0f,-1.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	1.0f,-1.0f, 1.0f,
	0.0f,-1.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	1.0f,-1.0f,-1.0f,
	0.0f,-1.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	-1.0f,-1.0f,-1.0f,
	0.0f,-1.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY,

	// Left Face
	-1.0f,-1.0f,-1.0f,
	-1.0f, 0.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 0.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 0.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY,

	// Right Face
	1.0f,-1.0f,-1.0f,
	1.0f, 0.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	1.0f,-1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	1.0f, 1.0f,-1.0f,
	1.0f, 0.0f, 0.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY
};

static unsigned short afIndicesCube[] = {0,3,1,3,2,1,
											4,5,7,7,5,6,
											8,11,9,11,10,9,
											12,13,15,15,13,14,
											16,19,17,19,18,17,
											20,21,23,23,21,22};

xr_state GenCubeMesh(Float32 xs, Float32 ys, Float32 zs, CMesh* mesh)
{

	Float32* vertexArray = (Float32*)malloc(sizeof(afVerticesCube));

	Int32 i;

	for (i=0;i<24*8;i+=8) {
		vertexArray[i+0] = afVerticesCube[i+0]*xs;
		vertexArray[i+1] = afVerticesCube[i+1]*ys;
		vertexArray[i+2] = afVerticesCube[i+2]*zs;
		vertexArray[i+3] = afVerticesCube[i+3];
		vertexArray[i+4] = afVerticesCube[i+4];
		vertexArray[i+5] = afVerticesCube[i+5];
		vertexArray[i+6] = afVerticesCube[i+6];
		vertexArray[i+7] = afVerticesCube[i+7];
	}

	mesh->SetupVB(vertexArray, XR_VERTEX_LAYOUT_PNT, sizeof(afVerticesCube)/XR_VERTEX_SIZE(XR_VERTEX_LAYOUT_PNT), XR_BUFFER_STATIC);
	mesh->SetupIB(afIndicesCube, sizeof(afIndicesCube), XR_BUFFER_STATIC);
	free(vertexArray);
	return XR_OK;
}

Float32* GenPlaneMeshH(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi)
{
	Int32 x, y;
	Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
	UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);
	XrRect uv;
	if (roi) uv = *roi;
	else uv.Set(0,0,1,1);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return 0;
    }

	Int32 slotId=0;
	for (y=0; y<dy; y++) {
		for (x=0; x<dx; x++) {
			PlaneVBO[slotId+0] = (((Float32)x)/(dx-1)-0.5)*2*sx;
			PlaneVBO[slotId+1] = 0.0;
			PlaneVBO[slotId+2] = (((Float32)y)/(dy-1)-0.5)*2*sy;
			
			PlaneVBO[slotId+3] = 0;
			PlaneVBO[slotId+4] = 1.0;
			PlaneVBO[slotId+5] = 0;
			
			PlaneVBO[slotId+6] = uv.x + ((Float32)x)/(dx-1)*uv.width;
			PlaneVBO[slotId+7] = uv.y + ((Float32)y)/(dy-1)*uv.height;

			slotId+=8;
		}
	}

	slotId = 0;

	for (y=0; y<dy-1; y++) {
		for (x=0; x<dx-1; x++) {
			PlaneIBO[slotId] = y*dx+x;
			PlaneIBO[slotId+2] = y*dx+x+1;
			PlaneIBO[slotId+1] = (y+1)*dx+x;
			PlaneIBO[slotId+3] = y*dx+x+1;
			PlaneIBO[slotId+5] = (y+1)*dx+x+1;
			PlaneIBO[slotId+4] = (y+1)*dx+x;
			slotId+=6;
		}
	}
	
	if (mesh) {
		mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy, XR_BUFFER_STATIC);
		mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_STATIC);
		free(PlaneVBO);
		free(PlaneIBO);
	}
	else {
		free(PlaneIBO);
		return PlaneVBO;
	}

	return XR_OK;

}

Float32* GenPlaneMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi)
{


	Int32 x, y;
	Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
	UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);
	XrRect uv;
	if (roi) uv = *roi;
	else uv.Set(0,0,1,1);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return 0;
    }

	Int32 slotId=0;
	for (y=0; y<dy; y++) {
		for (x=0; x<dx; x++) {
			PlaneVBO[slotId+0] = (((Float32)x)/(dx-1)-0.5)*2*sx;
			PlaneVBO[slotId+1] = (((Float32)y)/(dy-1)-0.5)*2*sy;
			//#define PlaneHeight 0.0
			PlaneVBO[slotId+2] = 0.0;

			PlaneVBO[slotId+3] = 0;
			PlaneVBO[slotId+4] = 0;
			PlaneVBO[slotId+5] = 1.0;
			
			PlaneVBO[slotId+6] = uv.x + ((Float32)x)/(dx-1)*uv.width;
			PlaneVBO[slotId+7] = uv.y + ((Float32)y)/(dy-1)*uv.height;

			slotId+=8;
		}
	}

	slotId = 0;

	for (y=0; y<dy-1; y++) {
		for (x=0; x<dx-1; x++) {
			PlaneIBO[slotId] = y*dx+x;
			PlaneIBO[slotId+2] = y*dx+x+1;
			PlaneIBO[slotId+1] = (y+1)*dx+x;
			PlaneIBO[slotId+3] = y*dx+x+1;
			PlaneIBO[slotId+5] = (y+1)*dx+x+1;
			PlaneIBO[slotId+4] = (y+1)*dx+x;
			slotId+=6;
		}
	}

	if (mesh) {
		mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy, XR_BUFFER_STATIC);
		mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_STATIC);
		free(PlaneVBO);
		free(PlaneIBO);
	}
	else {
		free(PlaneIBO);
		return PlaneVBO;
	}

	return XR_OK;

}

Float32* GenPlaneDynamicMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi)
{


	Int32 x, y;
	Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
	UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);
	XrRect uv;
	if (roi) uv = *roi;
	else uv.Set(0,0.1,1,0.9);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return 0;
    }

	Int32 slotId=0;
	for (y=0; y<dy; y++) {
		for (x=0; x<dx; x++) {
			PlaneVBO[slotId+0] = (((Float32)x)/(dx-1)-0.5)*2*sx;
			PlaneVBO[slotId+1] = (((Float32)y)/(dy-1)-0.5)*2*sy;
			//#define PlaneHeight 0.0
			PlaneVBO[slotId+2] = 0.0;

			PlaneVBO[slotId+3] = 0;
			PlaneVBO[slotId+4] = 0;
			PlaneVBO[slotId+5] = 1.0;
			
			PlaneVBO[slotId+6] = uv.x + ((Float32)x)/(dx-1)*uv.width;
			PlaneVBO[slotId+7] = uv.y + ((Float32)y)/(dy-1)*uv.height;

			slotId+=8;
		}
	}

	slotId = 0;

	for (y=0; y<dy-1; y++) {
		for (x=0; x<dx-1; x++) {
			PlaneIBO[slotId] = y*dx+x;
			PlaneIBO[slotId+2] = y*dx+x+1;
			PlaneIBO[slotId+1] = (y+1)*dx+x;
			PlaneIBO[slotId+3] = y*dx+x+1;
			PlaneIBO[slotId+5] = (y+1)*dx+x+1;
			PlaneIBO[slotId+4] = (y+1)*dx+x;
			slotId+=6;
		}
	}

	if (mesh) {
		mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy, XR_BUFFER_DYNAMIC);
		mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_STATIC);
		//free(PlaneVBO);
		free(PlaneIBO);
	}
	else {
		free(PlaneIBO);
		return PlaneVBO;
	}

	return XR_OK;

}
//first point record circle center,
//unit of angle is degree
#define ARC_ANGLE_STEP  3
#define PI 3.1415926
Float32* GenPlaneArcPlaneMeshV(Float32 r, Float32 s_a, Float32 e_a,  CMesh* mesh, Region* roi)
{


	Int32 x, y;
	Int32 point_num;
	int start_angle = (int)s_a;
	int end_angle = (int)e_a;
    int add_num = 0;
    float angle_step = (float)ARC_ANGLE_STEP/180.0*PI;
	float start_angle_rad = s_a/180.0*PI;
	float end_angle_rad = e_a/180.0*PI;
	
	if((end_angle-start_angle)%ARC_ANGLE_STEP !=0)
	{
	    add_num = 1;
	}


    point_num = add_num+(end_angle-start_angle)/ARC_ANGLE_STEP+1;
	
	Float32* PlaneVBO = (Float32*)malloc((point_num+1)*8*4);
	UInt16* PlaneIBO = (UInt16*)malloc((point_num-1)*3*2);
	XrRect uv;
	if (roi) uv = *roi;
	else uv.Set(0,0.0,1,1.0);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return 0;
    }

	Int32 slotId=0;
	//circle center point
	PlaneVBO[slotId+0] = 0;
	PlaneVBO[slotId+1] = 0;
	PlaneVBO[slotId+2] = 0.0;
	
	PlaneVBO[slotId+3] = 0;
	PlaneVBO[slotId+4] = 0;
	PlaneVBO[slotId+5] = 1.0;
	
	PlaneVBO[slotId+6] =0;
	PlaneVBO[slotId+7] =0;
	
	slotId+=8;
    
	
	for(x=0;x<point_num;x++)
    {
	    
		PlaneVBO[slotId+0] =r*cos(start_angle_rad);
		PlaneVBO[slotId+1] = r*sin(start_angle_rad);
		//#define PlaneHeight 0.0
		PlaneVBO[slotId+2] = 0.0;

		PlaneVBO[slotId+3] = 0;
		PlaneVBO[slotId+4] = 0;
		PlaneVBO[slotId+5] = 1.0;
		
		PlaneVBO[slotId+6] = (float)x/(float)(point_num-1);
		PlaneVBO[slotId+7] = 1.0;

		slotId+=8;
		start_angle_rad+=angle_step;
		if(start_angle_rad>end_angle_rad)
		{
		    start_angle_rad = end_angle_rad;
		}
	}

	slotId = 0;

	for (y=0; y<point_num-1; y++) {
	
			PlaneIBO[slotId] = 0;
			PlaneIBO[slotId+2] = y+1;
			PlaneIBO[slotId+1] = y+2;
			slotId+=3;
		
	}

	if (mesh) {
		mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, (point_num+1), XR_BUFFER_DYNAMIC);
		mesh->SetupIB(PlaneIBO, (point_num-1)*3*2, XR_BUFFER_STATIC);
		//free(PlaneVBO);
		free(PlaneIBO);
	}
	else {
		free(PlaneIBO);
		return PlaneVBO;
	}

	return XR_OK;

}
Float32* GenPlaneDynamicMeshH(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi)
	{
		Int32 x, y;
		Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
		UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);
		XrRect uv;
		if (roi) uv = *roi;
		else uv.Set(0,0.1,1,0.9);
	
		if ( !PlaneVBO || !PlaneIBO) {
			if (PlaneVBO) free(PlaneVBO);
			if (PlaneIBO) free(PlaneIBO);
			return 0;
		}
	
		Int32 slotId=0;
		for (y=0; y<dy; y++) {
			for (x=0; x<dx; x++) {
				PlaneVBO[slotId+0] = (((Float32)x)/(dx-1)-0.5)*2*sx;
				PlaneVBO[slotId+1] = 0.0;
				PlaneVBO[slotId+2] = (((Float32)y)/(dy-1)-0.5)*2*sy;
				
				PlaneVBO[slotId+3] = 0;
				PlaneVBO[slotId+4] = 1.0;
				PlaneVBO[slotId+5] = 0;
				
				PlaneVBO[slotId+6] = uv.x + ((Float32)x)/(dx-1)*uv.width;
				PlaneVBO[slotId+7] = uv.y + ((Float32)y)/(dy-1)*uv.height;
	
				slotId+=8;
			}
		}
	
		slotId = 0;
	
		for (y=0; y<dy-1; y++) {
			for (x=0; x<dx-1; x++) {
				PlaneIBO[slotId] = y*dx+x;
				PlaneIBO[slotId+2] = y*dx+x+1;
				PlaneIBO[slotId+1] = (y+1)*dx+x;
				PlaneIBO[slotId+3] = y*dx+x+1;
				PlaneIBO[slotId+5] = (y+1)*dx+x+1;
				PlaneIBO[slotId+4] = (y+1)*dx+x;
				slotId+=6;
			}
		}
		
		if (mesh) {
			mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy, XR_BUFFER_DYNAMIC);
			mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_STATIC);
			//free(PlaneVBO);
			free(PlaneIBO);
		}
		else {
			free(PlaneIBO);
			return PlaneVBO;
		}
	
		return XR_OK;
	
	}


xr_state GenLayerMesh(Int32 sx, Int32 sy, Float32 texScaleX, Float32 texScaleY, Int32 dx, Int32 dy, CMesh* mesh)
{


	Int32 x, y;
	Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
	UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return XR_FAILED;
    }

	Int32 slotId=0;
	for (y=0; y<dy; y++) {
		for (x=0; x<dx; x++) {
			PlaneVBO[slotId+0] = (((Float32)x)/(dx-1))*sx;
			PlaneVBO[slotId+1] = (((Float32)y)/(dy-1))*sy;
			//PlaneHeight 2.1
			PlaneVBO[slotId+2] = 2.1;
			
			PlaneVBO[slotId+3] = 1.0;
			PlaneVBO[slotId+4] = ((Float32)x)/(dx-1);
			PlaneVBO[slotId+5] = ((Float32)y)/(dy-1);
			
			PlaneVBO[slotId+6] = ((Float32)x)/(dx-1)*texScaleX;
			PlaneVBO[slotId+7] = ((Float32)y)/(dy-1)*texScaleY;

			slotId+=8;
		}
	}

	slotId = 0;

	for (y=0; y<dy-1; y++) {
		for (x=0; x<dx-1; x++) {
			PlaneIBO[slotId] = y*dx+x;
			PlaneIBO[slotId+1] = y*dx+x+1;
			PlaneIBO[slotId+2] = (y+1)*dx+x;
			PlaneIBO[slotId+3] = y*dx+x+1;
			PlaneIBO[slotId+4] = (y+1)*dx+x+1;
			PlaneIBO[slotId+5] = (y+1)*dx+x;
			slotId+=6;
		}
	}

	mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy,XR_BUFFER_STATIC);
	mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_STATIC);

	free(PlaneVBO);
	free(PlaneIBO);

	return XR_OK;

}
Float32* GenLineMeshV(Float32 sx, Float32 sy, Int32 dx, Int32 dy, CMesh* mesh, Region* roi)
{


	Int32 x, y;
	Float32* PlaneVBO = (Float32*)malloc(dx*dy*8*4);
	// buffer file %s,line %d",__FILE__,__LINE__);
	UInt16* PlaneIBO = (UInt16*)malloc((dx-1)*(dy-1)*6*2);
	// buffer file %s,line %d",__FILE__,__LINE__);
	XrRect uv;
	if (roi) uv = *roi;
	else uv.Set(0,0,1,1);

	if ( !PlaneVBO || !PlaneIBO) {
        if (PlaneVBO) free(PlaneVBO);
        if (PlaneIBO) free(PlaneIBO);
        return 0;
    }

	Int32 slotId=0;
	for (y=0; y<dy; y++) {
		for (x=0; x<dx; x++) {
			PlaneVBO[slotId+0] = (Float32)x*sx/(dx-1);//(((Float32)x)/(dx-1)-0.5)*2*sx;
			PlaneVBO[slotId+1] = 1.0;//(((Float32)y)/(dy-1)-0.5)*2*sy;
			//#define PlaneHeight 0.0
			PlaneVBO[slotId+2] = (Float32)y*sy/(dy-1);

			PlaneVBO[slotId+3] = 0;
			PlaneVBO[slotId+4] = 0;
			PlaneVBO[slotId+5] = 1.0;
			
			PlaneVBO[slotId+6] = uv.x + ((Float32)x)/(dx-1)*uv.width;
			PlaneVBO[slotId+7] = uv.y + ((Float32)y)/(dy-1)*uv.height;

			slotId+=8;
		}
	}

	slotId = 0;

	for (y=0; y<dy-1; y++) {
		for (x=0; x<dx-1; x++) {
			PlaneIBO[slotId] = y*dx+x;
			PlaneIBO[slotId+2] = y*dx+x+1;
			PlaneIBO[slotId+1] = (y+1)*dx+x;
			PlaneIBO[slotId+3] = y*dx+x+1;
			PlaneIBO[slotId+5] = (y+1)*dx+x+1;
			PlaneIBO[slotId+4] = (y+1)*dx+x;
			slotId+=6;
		}
	}

	if (mesh) {
		mesh->SetupVB(PlaneVBO, XR_VERTEX_LAYOUT_PNT, dx*dy, XR_BUFFER_DYNAMIC);
		mesh->SetupIB(PlaneIBO, (dx-1)*(dy-1)*6 * 2, XR_BUFFER_DYNAMIC);
		//free(PlaneVBO);
		//free(PlaneIBO);
	}
	else {
		free(PlaneIBO);
		return PlaneVBO;
	}

	return XR_OK;

}

#define TZ  3.0
Float32 afVertices[] = {
	// Front Face
	100.0f,100.0f, TZ,
	1.0f, 0.0f, 1.0f,
	TEX_COORD_MINX, TEX_COORD_MINY,
	100.0f,400.0f, TZ,
	1.0f, 0.0f, 1.0f,
	TEX_COORD_MAXX, TEX_COORD_MINY,
	400.0f, 400.0f, TZ,
	1.0f, 0.0f, 1.0f,
	TEX_COORD_MAXX, TEX_COORD_MAXY,
	400.0f, 100.0f, TZ,
	1.0f, 0.0f, 1.0f,
	TEX_COORD_MINX, TEX_COORD_MAXY};

static unsigned short afIndices[] = {0,1,3,3,1,2};


