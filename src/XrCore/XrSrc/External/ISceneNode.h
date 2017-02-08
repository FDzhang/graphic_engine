#ifndef __IRENDER_NODE_SCENE_H__
#define __IRENDER_NODE_SCENE_H__
#include "IRenderNode.h"
#include "ICamera.h"

class ISceneNode : virtual public IRenderNode
{
public:

	virtual Int32 CreateNode(
		/* [in] */ Int32 targetIndex,
		/* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 z,
		/* [out] */ class INode** ppINode=0)=0;


    virtual Int32 CreateModel(
        /* [in] */ Int32 type,
		/* [in] */ Int32 materialId,
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 z,
        /* [in] */ Float32 scale,
		/* [out] */ class INode** ppINode=0)=0;

	virtual Int32 CreateMaterialEx(
		/* [in] */ MaterialBlock* pDesc,
		/* [in] */ Int32 meshId,
		/* [out] */ IMaterial** ppMtl=0)=0;

	virtual Int32 LoadNodeFromFile(
		/* [in] */ Int32 targetIndex,
		/* [in] */ InsertFlag flag,		
		/* [in] */ ConstString fileName,
		/* [out] */INode** ppINode=0)=0;

	virtual Int32 LoadModelFromFile(
        /* [in] */ String name,
		/* [in] */ Int32 materialId,
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 z,
        /* [in] */ Float32 scale,
		/* [out] */ class INode** ppINode)=0;

	virtual xr_state ReleaseModel(
		/* [in] */ Int32 modelId)=0;

	virtual Int32 RemoveModel(
		/* [in] */ Int32 modelId)=0;

    virtual Int32 CreateSubdivision(
        /* [in] */ ModelType type,
		/* [in] */ Int32 materialId,
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 sx,
        /* [in] */ Float32 sy,
        /* [in] */ Float32 sz,
        /* [in] */ Int32 dx,
		/* [in] */ Int32 dy,
		/* [in] */ Int32 dz,
		/* [out] */ class INode** ppINode)=0;

   virtual Int32 CreateCamera(
		/* [in] */ Float32 fovx, 
		/* [in] */ Float32 aspect, 
		/* [in] */ Float32 znear, 
		/* [in] */ Float32 zfar,
		/* [out] */ ICamera** ppCamera)=0;

   virtual xr_state SetCamera(
		/* [in] */ Int32 camId)=0;

   virtual Int32 CreateLight(
		/* [in] */ LightType type,
        /* [in] */ Int32 x,
		/* [in] */ Int32 y,
		/* [in] */ Int32 z,
	    /* [in] */ Int32 vx,
		/* [in] */ Int32 vy,
		/* [in] */ Int32 vz,
		/* [out] */ class ILight** ppILight)=0;

   virtual xr_state EnableLighting(
		/* [in] */ Boolean flag)=0;


   virtual xr_state EnableShadowVolume(
		/* [in] */ Boolean flag)=0;

   virtual INode* FindNode(
	   /* [in] */ Int32 parentId,
	   /* [in] */ ConstString name)=0;
};

#endif  //__IRENDER_NODE_SCENE_H__

