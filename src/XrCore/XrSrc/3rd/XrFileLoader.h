#ifndef __FILE_LOADER_H__
#define __FILE_LOADER_H__

#include "../External/xrIntrinsic.h"
#include "../Platform/XrOS.h"

xr_state XRCreateTextureFromFile(ConstString fileName, UInt32 type, class CTexture* pTexture);
xr_state LoadTextFromFile(String fileName, String* pString);

//xr_state LoadTextureFromFile(String fileName, UInt32 texOption, Texture* pTex);
//xr_state ReleaseTexture(UInt32 id);
xr_state _LoadModelFromFile(String fileName, class CMesh* pMesh, Float32 scale, Boolean reserve);
//xr_state LoadSkeletonFromFile(String fileName,class CSkeletonAnimation* pSkeleton);
//xr_state LoadMeshFromArray(Float32* pData, Int16* pIndex, Int32 format, Int32 datanum, class CMesh* pMesh);

xr_state UnloadModel(class CMesh* pMesh);
//xr_state LoadTextFromFile(String fileName, String* pString);
//xr_state LoadTextureFromArray(Int32 width, Int32 height, TexFormat format, UInt32 texOption, Texture* pTex, Void* pData);
//xr_state ReloadTexture(Void* pData, Texture* pTex);
xr_state LockMeshData(class CMesh* pMesh, Float32** ppData, XRVertexLayout* layout, Int32* vertexCount);
xr_state UnLockMeshData(CMesh* pMesh);
#endif //__FILE_LOADER_H__
