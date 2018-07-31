#ifndef __SV_DELEGATE_H__
#define __SV_DELEGATE_H__
#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"

#include "../XrCore/XrSrc/XrCore/CDeviceManager.h"

#include "videoloader.h"
#include "fileloader.h"
#include "GlSVLuminance.h"


#include "bev_config.h"
#include "AVMData.h"


#define LUMINANCE_BALANCE_ENABLE

//#define ADJUST_BYHAND
extern CRenderDevice* g_pXrRenderDevice;
extern CRenderContext* g_pXrRenderContext;
#define LUMINANCE_BALANCE_ENABLE

extern GLfloat fCarView[];





 extern GLfloat *pfDataTotal;
 extern GLushort *pucIndexTotal;


 struct SV_PARAM_CB {
	XRMat4 myPMVMatrix;
	XRMat4 uvPMVMatrix;	
    XRVec2 Point_Gate;
    XRVec3 Pos_Select;
    XRVec3 Lumin_Gate_Min;
    XRVec3 Lumin_Gate_Max;	
};

  struct SV2D_PARAM_CB {
     XRMat4 myPMVMatrix;	
     XRVec3 InputCofL1;
	 XRVec3 InputCofL2;
     XRVec2 PointTopLeft;
     XRVec2 PointBottomRight;
     Float32 direction;	 
	 Float32 InputFlag;	 
 };


#ifdef ADJUST_BYHAND
XRMat4      uvAdjustTransfom[4];
#endif



//caculate luminance balance cof


extern CDeviceManager *XRDM;
class RenderDelegateSV : public IRenderDelegate
{ 
public:
	RenderDelegateSV() {

	}
	virtual ~RenderDelegateSV()
	{

	}
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject)
	{
		CShaderObject* pShader;
		CUniformBlock* pUB;
		CRenderState* pRS;
		CVertexLayout* pLayout;
               //printf("render\r\n");
		static int cnt = 0;
		float luminance[3] = {1.0,1.0,1.0};
		int Index;
	    int i;	
		XRMat4 tempRotate = XRMat4::Scale(-1.0,1.0,1.0);
		float yuv_temp[24];
        float yuv_ratio[24];	
		float pos_select[3];
		float pos_gate[2];




		pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
		g_pXrRenderContext->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

		char id = pIObject->GetName()[0];
		XRMat4 mModel = XRMat4::Scale(1.0f, 1.0f, 1.0f);
        int chn;
		switch (id) {
			case '0':
			case '1':
				 chn = id-48;
				 #if 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, pMtl->GetDiffuseMap()->texid);

				glActiveTexture(GL_TEXTURE1);
				
				glBindTexture(GL_TEXTURE_2D, pMtl->GetAmbientMap()->texid);
				#endif
				pRS->Set(XR_CULLMODE_FRONT | m_front_face_config| XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT );

				pos_select[0] = 1.0;
				pos_select[1] = 0.0;
				pos_select[2] = 0.0;

				break;
			case '2':
			case '3':
                chn = id-48;
				#if 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, pMtl->GetDiffuseMap()->texid);

				glActiveTexture(GL_TEXTURE1);
				
				glBindTexture(GL_TEXTURE_2D, pMtl->GetAmbientMap()->texid);
				#endif


				pos_select[0] = 0.0;
				pos_select[1] = 0.0;
				pos_select[2] = 1.0;

				pRS->Set(XR_CULLMODE_FRONT | m_front_face_config | XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT);


				break;
			case '4':
			case '5':
                chn = id-52;
				pRS->Set(XR_CULLMODE_FRONT | m_front_face_config | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT| XR_BLEND_DEFAULT );
				//| XR_BLEND_DEFAULT
                #if 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, pMtl->GetDiffuseMap()->texid);
				
				glActiveTexture(GL_TEXTURE1);
				
				glBindTexture(GL_TEXTURE_2D, pMtl->GetAmbientMap()->texid);
                #endif
				pos_select[0] = 1.0;
				pos_select[1] = 0.0;
				pos_select[2] = 0.0;
			break;
			case '6':
			case '7':
					chn = id-52;
					#if 0
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, pMtl->GetDiffuseMap()->texid);
				
					glActiveTexture(GL_TEXTURE1);
					
					glBindTexture(GL_TEXTURE_2D, pMtl->GetAmbientMap()->texid);
				#endif
				
				pRS->Set(XR_CULLMODE_FRONT | XR_FRONTFACE_CCW | XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT);
					pos_select[0] = 1.0;
					pos_select[1] = 0.0;
					pos_select[2] = 0.0;
				
				
				
			break;

				
			
		}
		
		
		String ModelName = pIObject->GetName();


        if(m_update_flag[id-48])
        {

    		    ProcessModel(m_pNode[id-48],ModelName);  
    			m_update_flag[id-48]=0;

        }
		
		SV_PARAM_CB sv_param;
		Lumin_para *m_lumin_para;
		AVMData::GetInstance()->m_lumin_para->GetLuminCof(&m_lumin_para);
		AVMData::GetInstance()->m_cam_source->UseCameraTexture(chn);
        AVMData::GetInstance()->m_cam_source->UseCameraMaskTexture(chn);		
        if(chn == rear_camera_index)
        {
            sv_param.Lumin_Gate_Min.Set(&m_lumin_para->K_BR[0]);
			sv_param.Lumin_Gate_Max.Set(&m_lumin_para->K_BL[0]);

				pos_gate[0] = m_lumin_para->Lumin_point_TL[0];
				pos_gate[1] = m_lumin_para->Lumin_point_TR[0];			
        }
		else if(chn ==front_camera_index)
		{
            sv_param.Lumin_Gate_Min.Set(&m_lumin_para->K_FL[0]);
			sv_param.Lumin_Gate_Max.Set(&m_lumin_para->K_FR[0]);

				pos_gate[0] = m_lumin_para->Lumin_point_TL[0];
				pos_gate[1] = m_lumin_para->Lumin_point_TR[0];			

		}
		else if(chn ==left_camera_index)
		{
		    sv_param.Lumin_Gate_Min.Set(&m_lumin_para->K_LB[0]);
			sv_param.Lumin_Gate_Max.Set(&m_lumin_para->K_LF[0]);
			pos_gate[0] = m_lumin_para->Lumin_point_RB[2];
			pos_gate[1] = m_lumin_para->Lumin_point_RT[2];			
		}
		else
		{
            sv_param.Lumin_Gate_Min.Set(&m_lumin_para->K_RF[0]);
			sv_param.Lumin_Gate_Max.Set(&m_lumin_para->K_RB[0]);		
			pos_gate[0] = m_lumin_para->Lumin_point_RB[2];
			pos_gate[1] = m_lumin_para->Lumin_point_RT[2];			
		}
		
        if(id == '4'||id == '5')
        {
             // sv_param.Lumin_Gate_Min.x*=1.02;
              //sv_param.Lumin_Gate_Max.x*=1.02;
		
        }
		

         XRMat4 *uvTransform;
		 XRMat4 *modeltransform;
		
        if(chn<=3)
        {
            sv_param.Pos_Select.Set(pos_select);
    		sv_param.Point_Gate.Set(pos_gate);
			AVMData::GetInstance()->m_exParam->GetModelTransform(&modeltransform,chn);
    		        
    		mModel = (*pModelMatrix)*(*modeltransform);
    		mModel = m_ModelFlipMatrix*mModel;
    		mModel = (*pViewMatrix)*mModel;
    		sv_param.myPMVMatrix = (*pProjMatrix)*mModel;
    	    AVMData::GetInstance()->m_exParam->GetTransformMatrix(&uvTransform,chn);
    	    sv_param.uvPMVMatrix = m_ModelFlipMatrix*(*uvTransform);
        }
		else
		{
			sv_param.Lumin_Gate_Min.Set(luminance);
			sv_param.Lumin_Gate_Max.Set(luminance); 

	        sv_param.Pos_Select.Set(pos_select);
    		sv_param.Point_Gate.Set(pos_gate);
			AVMData::GetInstance()->m_exParam->GetModelTransform(&modeltransform,chn-2);
    		        
    		mModel = (*pModelMatrix)*(*modeltransform);
    		mModel = m_ModelFlipMatrix*mModel;
    		mModel = (*pViewMatrix)*mModel;
    		sv_param.myPMVMatrix = (*pProjMatrix)*mModel;
    	    AVMData::GetInstance()->m_exParam->GetTransformMatrix(&uvTransform,chn-2);
    	    sv_param.uvPMVMatrix = m_ModelFlipMatrix*(*uvTransform);	
		}
			

		g_pXrRenderContext->UpdateUniformBlock(pUB, &sv_param);
		g_pXrRenderContext->VSSetUniformBlock(0, pUB);
		g_pXrRenderContext->PSSetUniformBlock(0, pUB);

		return 0;
	}
    
	virtual Void ProcessModel(INode* mdl, String modelName)
	{
		IMesh* mesh=0;
		Float32* pData;
		Float32 maxy=0.0f,miny=0.0f;
		Int32 count, i,chanelID,pos=0;
		if(modelName !=NULL)
		mdl->SetName(modelName);
		mdl->GetMesh(&mesh);
		mesh->LockData(&pData, 0, &count);
        switch(*modelName)
        {
	        case '0':
			case '1':		
            case '2':
			case '3':
				chanelID = (*modelName)-48;
			    m_pNode[chanelID]=mdl;

			break;	
			case '4':
			case '5':
				chanelID = (*modelName)-52;
				
			    m_pNode[(*modelName)-48]=mdl;
			break;
			case '6':
			case '7':
				pos = (*modelName)-50;     //pos for model
				chanelID = (*modelName)-52;  //front/rear chanle
				
			   // m_pNode[pos]=mdl;
			break;

				
        }
		for (i=0;i<count;i++) {
			pData[8*i+3] = pData[8*i+0];
			pData[8*i+4] = pData[8*i+1];
			pData[8*i+5] = pData[8*i+2];
			//pData[8*i+6] = 0.2;

			if (maxy < pData[8*i+1]) maxy = pData[8*i+1];
			if (miny > pData[8*i+1]) miny = pData[8*i+1];
            AVMData::GetInstance()->CalcUVTextureSV(&pData[8*i+0],&pData[8*i+3], chanelID);
		}
		
		mesh->UnLockData();
	}
	void UpdateExParamCalibRslt(float *pose)			
	{

		for(int i =0;i<6;i++)
		{
		    m_update_flag[i] = 1;
		}
	}

	
	void SetMirrorFlipEnable(unsigned char flag)			

	{
        if(flag == 1)
        {

            m_front_face_config = XR_FRONTFACE_CW;
			m_ModelFlipMatrix = XRMat4::Scale(-1.0,1.0,1.0);
        }
		else
		{
		    m_front_face_config = XR_FRONTFACE_CCW;

			
			m_ModelFlipMatrix = XRMat4::Scale(1.0,1.0,1.0);
		}
        


	}



	Void Init(BEV_CONFIG_T  pConfig)
	{
		int i;
   		    m_front_face_config = XR_FRONTFACE_CCW;
			
			m_ModelFlipMatrix = XRMat4::Scale(1.0,1.0,1.0);  
		for(i=0;i<6;i++)
		{

		        m_update_flag[i] = 0;

		}

        
	}

	INode*  m_pNode[6];
	unsigned char m_update_flag[6];
	XRMat4 m_ModelFlipMatrix;
	unsigned char m_front_face_config;
	
};

#define TRANS_Z 520
#define TRANS_X 520

class RenderDelegateCV : public IRenderDelegate
{
public:
	RenderDelegateCV() {
	}
	virtual ~RenderDelegateCV()
	{
	}

	Void SetChannel(Int32 id) { channelId = id; }
	Void Init()
	{
	}
	
	virtual Void ProcessMirrorModel(INode* mdl, String modelName)
	{
		IMesh* mesh=0;
		Float32* pData;
		Float32 maxy=1.0f,miny=0.0f;	
		Float32 maxx=1.0f,minx=0.0f;
		//range value store as positive minx miny maxx max y,negtive minx miny maxx maxy
		Float32 range_value[8];
		float texture[2];
		Int32 count, i=0,chanelID=0;
		XRMat4 uvModel;
		mdl->SetName(modelName);
		mdl->GetMesh(&mesh);
		mesh->LockData(&pData, 0, &count);
		float Rot[3]={-1.57,0,0};
		float ratio = 0.95;
		float topdownrate = 0.05;
		if(*modelName != 'M')
		{
            return;
		}
		range_value[0]=400.0;
		range_value[1] =400.0;
			range_value[5]=400.0;
		range_value[4] =600.0;	
		//find range of vertex		
	    for (i=0;i<count;i++)	
	    {
	        if(pData[8*i+3] > 0)
	        {
    			if (range_value[0] > pData[8*i+0]) range_value[0] = pData[8*i+0] ;
    			if (range_value[2] < pData[8*i+0]) range_value[2] = pData[8*i+0] ;
    			if (range_value[1] > pData[8*i+1]) range_value[1] = pData[8*i+1] ;
    			if (range_value[3] < pData[8*i+1]) range_value[3] = pData[8*i+1] ;
	        }
			else
			{
    			if (range_value[4] > pData[8*i+0]) range_value[4] = pData[8*i+0] ;
    			if (range_value[6] < pData[8*i+0]) range_value[6] = pData[8*i+0] ;
    			if (range_value[5] > pData[8*i+1]) range_value[5] = pData[8*i+1] ;
    			if (range_value[7] < pData[8*i+1]) range_value[7] = pData[8*i+1] ;

			}
	    }

		
		for (i=0;i<count;i++) {
			
	        if(pData[8*i+3] > 0)
	        {
				texture[0]=(pData[8*i+0]-range_value[0])/(range_value[2]-range_value[0])*ratio;
				texture[1]=topdownrate+(pData[8*i+1]-range_value[1])/(range_value[3]-range_value[1])*(1.0-topdownrate);

	        }
			else
			{
				texture[0]=(pData[8*i+0]-range_value[4])/(range_value[6]-range_value[4])*ratio;
				texture[1]=topdownrate+(pData[8*i+1]-range_value[5])/(range_value[7]-range_value[5])*(1.0-topdownrate);

			}

			
			pData[8*i+3] =ratio- texture[0];
			pData[8*i+4] = 1.0-texture[1];
			pData[8*i+5] = pData[8*i+2];
			


			if (maxy < pData[8*i+3]) pData[8*i+3] = maxy ;
			if (miny > pData[8*i+3]) pData[8*i+3] = miny;
			if (maxy < pData[8*i+4]) pData[8*i+4] = maxy ;
			if (miny > pData[8*i+4]) pData[8*i+4] = miny;			
			//CalcCrossViewUVTexture(&pData[8*i+0],&pData[8*i+3], 2,uvModel,bev_config.smc.DISTORTION_MODEL);
			//xrprintf("\r\n Vertex[%f,%f,%f],texture[%f,%f]",pData[8*i+0],pData[8*i+1],pData[8*i+2],pData[8*i+3],pData[8*i+4],pData[8*i+5]);
		}


		mesh->UnLockData();
	}

	
	
	virtual Void ProcessModel(INode* mdl, String modelName)
	{
		IMesh* mesh=0;
		Float32* pData;
		Float32 maxy=0.0f,miny=0.0f;
		Int32 count, i,chanelID=0;
		XRMat4 uvModel;
		mdl->SetName(modelName);
		mdl->GetMesh(&mesh);
		mesh->LockData(&pData, 0, &count);
		float Rot[3]={-1.57,0,0};
		
#define SIDEMIRRORDEGREE 0.0
		switch (*modelName) {
			case 'L':
				uvModel =XRMat4::RotationY(3.1415926*(-SIDEMIRRORDEGREE));
				break;
			case 'R':
				uvModel = XRMat4::RotationY(3.1415926*(SIDEMIRRORDEGREE));
				break;
			case 'C':
				uvModel = XRMat4::RotationY(3.1415926*(0));
				break;
			default:
				uvModel = XRMat4::RotationY(3.1415926*(0));

				break;

		}
		//CalcCrossViewTransform(Rot);
        
		for (i=0;i<count;i++) {
			pData[8*i+3] = pData[8*i+0];
			pData[8*i+4] = pData[8*i+1];
			pData[8*i+5] = pData[8*i+2];

			if (maxy < pData[8*i+1]) maxy = pData[8*i+1];
			if (miny > pData[8*i+1]) miny = pData[8*i+1];
            //CalcCrossViewUVTexture(&pData[8*i+0],&pData[8*i+3], 2,uvModel,bev_config.smc.DISTORTION_MODEL);
		}


		mesh->UnLockData();
	}
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject)
	{
		CShaderObject* pShader;
		CUniformBlock* pUB;
		CRenderState* pRS;
		CVertexLayout* pLayout;
		pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

		char id = pIObject->GetName()[0];
		XRMat4 mModel, uvModel = XRMat4::Scale(1.0f, 1.0f, 1.0f);

        float pos_select[3]={0.0,1.0,0.0};
        float pos_gate[2]={1.0,2.0};
		float cof[3] = {1.0,1.0,1.0};
		
#define SIDEMIRRORDEGREE -0.25
#define SIDEMIRRORZ -0.0
		switch (id) {
			case 'L':
				mModel = XRMat4::RotationY(3.1415926*(0));
				uvModel = XRMat4::Translation(-TRANS_X,0,-TRANS_Z) *XRMat4::RotationX(3.1415926*(SIDEMIRRORZ))*XRMat4::RotationY(3.1415926*(-SIDEMIRRORDEGREE))*XRMat4::Translation(TRANS_X,0,TRANS_Z);
				break;
			case 'R':
				mModel = XRMat4::RotationY(3.1415926*(0));
				uvModel = XRMat4::Translation(TRANS_X,0,-TRANS_Z)* XRMat4::RotationX(3.1415926*(SIDEMIRRORZ))*XRMat4::RotationY(3.1415926*(SIDEMIRRORDEGREE))*XRMat4::Translation(-TRANS_X,0,TRANS_Z);	
				break;
			case 'C':
				mModel = XRMat4::RotationY(3.1415926*(0));
				uvModel = XRMat4::Translation(0,0,-TRANS_Z)* XRMat4::RotationX(3.1415926*(SIDEMIRRORZ))*XRMat4::RotationY(3.1415926*(0))*XRMat4::Translation(-0,0,TRANS_Z);
				break;
			case 'M':
				mModel = XRMat4::RotationY(3.1415926*(0));
				uvModel = XRMat4::RotationY(3.1415926*(0));
				break;				
			default:
				return DrawFace_None;

		}

		switch (id) {
			case 'C':
			case 'L':
			case 'R':
				pRS->Set(XR_CULLMODE_NONE | XR_FRONTFACE_CCW);
				AVMData::GetInstance()->m_cam_source->UseCameraTexture(channelId);

			break;
			case 'M':
				
				pRS->Set(XR_CULLMODE_NONE | XR_FRONTFACE_CCW| XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT);
				AVMData::GetInstance()->m_cam_source->UseCameraTexture(rear_camera_index);


				
				break;
		}

		static float interpolate[2]={-3000,-3000};

		SV_PARAM_CB sv_param;
		sv_param.Lumin_Gate_Min.Set(cof);
		sv_param.Lumin_Gate_Max.Set(cof);
        sv_param.Point_Gate.Set(pos_gate);
		sv_param.Pos_Select.Set(pos_select);
		
		mModel = (*pModelMatrix)*mModel;
		mModel = (*pViewMatrix)*mModel;
		sv_param.myPMVMatrix = (*pProjMatrix)*uvModel;
		sv_param.uvPMVMatrix =  uvModel;

		g_pXrRenderContext->UpdateUniformBlock(pUB, &sv_param);
		g_pXrRenderContext->VSSetUniformBlock(0, pUB);

		return 0;
	}
	Int32 channelId;
};
//render luminance texture
class RenderDelegateSV2D : public IRenderDelegate
{
public:
	RenderDelegateSV2D() {
	}
	virtual ~RenderDelegateSV2D()
	{
	}

	Void SetChannel(Int32 id) { channelId = id; }
	int GetChannel(void){ return channelId; }
	
	Void Init()
	{

	    int i=0;
		for(int i=0;i<4;i++)
		{
            AVMData::GetInstance()->m_2D_lut->GetCarRect(&m_CarRect[i],i);
		   
		}

	}

	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject)
	{
		CShaderObject* pShader;
		CUniformBlock* pUB; 
		CRenderState* pRS;
		CVertexLayout* pLayout;
		//XRVec3 VecCofL1,VecCofL2;
		float fLumCofL1[3];
		float fLumCofL2[3];
        int camera_index=0;
		pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

		char id = pIObject->GetName()[0];
		XRMat4 mModel, uvModel = XRMat4::Scale(1.0f, 1.0f, 1.0f);
		SV2D_PARAM_CB sv2D_param;
		unsigned int chn = id -48;
		float luminance_direct;
		int mtl_id;

		// first config OpenGL
        switch(id)
        {
            case '0':
			case '1':
			case '2':
			case '3':				
			//case '8':	
			    sv2D_param.InputFlag=0.0;
			
			    pRS->Set(XR_CULLMODE_NONE | XR_FRONTFACE_CCW);	



			break;	
			case '4':
		    case '5':
			case '6':
			case '7':
			case '8':
				sv2D_param.InputFlag=0.0;
				pRS->Set(XR_BLEND_DEFAULT|XR_CULLMODE_NONE | XR_FRONTFACE_CCW); 	

				
			break;
			case '9':
			case 'b':
			case 'a':
			case 's':
				sv2D_param.InputFlag=1.0;
				
				pRS->Set(XR_CULLMODE_NONE | XR_FRONTFACE_CCW);
				
		    break;	
				

        }
		//config luminance balance paramter

		Lumin_para *m_lumin_para;
		AVMData::GetInstance()->m_lumin_para->GetLuminCof(&m_lumin_para);

switch(id)
        {

			case '0':
				             
					
							AVMData::GetInstance()->m_cam_source->UseCameraTexture(front_camera_index);
                            for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=m_lumin_para->K_FL[i];
								fLumCofL2[i]=m_lumin_para->K_FR[i];
                            }
							luminance_direct = 0.0;

			break;
			case '1':
							
							AVMData::GetInstance()->m_cam_source->UseCameraTexture(rear_camera_index);
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=m_lumin_para->K_BL[i];
								fLumCofL2[i]=m_lumin_para->K_BR[i];
                            }
                            luminance_direct = 0.0; 
			break;            
			case '2':
			case '6':
			case '4':
							 
							 AVMData::GetInstance()->m_cam_source->UseCameraTexture(left_camera_index);
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=m_lumin_para->K_LB[i];
								fLumCofL2[i]=m_lumin_para->K_LF[i];
                            }
                            luminance_direct = 1.0; 
                             
			break;         
			case '3':
            case '5':
            case '7':
							
							AVMData::GetInstance()->m_cam_source->UseCameraTexture(right_camera_index);
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=m_lumin_para->K_RB[i];
								fLumCofL2[i]=m_lumin_para->K_RF[i];
                            }
                            luminance_direct = 1.0; 
			break;                     
			case '8':
			case 'a':
						XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
						

							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=1.0;
								fLumCofL2[i]=1.0;
                            }
                            luminance_direct = 1.0; 
                     //   printf("\r\n texture channel(%c),texture id(0x%x)",id,pMtl->GetDiffuseMap()->texid);
             break;
            case '9':
						   XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
						   AVMData::GetInstance()->m_cam_source->UseCameraTexture(channelId);
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=1.0;
								fLumCofL2[i]=1.0;
                            }
                            luminance_direct = 1.0; 						   

             break;
			case 's':
				
						//XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
						XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
						mtl_id = pMtl->GetDiffuseMap()->texid;
						for(camera_index=0;camera_index<4;camera_index++)
						{
						    if(mtl_id == AVMData::GetInstance()->m_cam_source->GetCameraSourceTextureId(camera_index))
						    {
						        break;
						    }
							
						}
						AVMData::GetInstance()->m_cam_source->UseCameraTexture(camera_index);
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=1.0;
								fLumCofL2[i]=1.0;
                            }
                            luminance_direct = 1.0; 
             break;
             default:
			 	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 


						   if(channelId == four_camera_index)
						{
							mtl_id = pMtl->GetDiffuseMap()->texid;
							for(camera_index=0;camera_index<4;camera_index++)
							{
								if(mtl_id == AVMData::GetInstance()->m_cam_source->GetCameraSourceTextureId(camera_index))
								{
									break;
								}
							
							}
							AVMData::GetInstance()->m_cam_source->UseCameraTexture(camera_index);
						}
						else if(channelId == left_right_camera_index)
						{
							mtl_id = pMtl->GetDiffuseMap()->texid;
							for(camera_index=left_camera_index;camera_index<= right_camera_index;camera_index++)
							{
								if(mtl_id == AVMData::GetInstance()->m_cam_source->GetCameraSourceTextureId(camera_index))
								{
									break;
								}
							
							}
							AVMData::GetInstance()->m_cam_source->UseCameraTexture(camera_index);
						}
						else
						{
						   AVMData::GetInstance()->m_cam_source->UseCameraTexture(channelId);
						}
						
							for(int i=0;i<3;i++)
                            {
							    fLumCofL1[i]=1.0;
								fLumCofL2[i]=1.0;
                            }
                            luminance_direct = 1.0; 						   

              break;
				

        }		



               



			
		sv2D_param.InputCofL1.Set(fLumCofL1);
		sv2D_param.InputCofL2.Set(fLumCofL2);
		sv2D_param.direction = luminance_direct;
        
		sv2D_param.PointTopLeft.Set(m_CarRect[rect_left],m_CarRect[rect_top]);
		sv2D_param.PointBottomRight.Set(m_CarRect[rect_right],m_CarRect[rect_bottom]);	
		sv2D_param.myPMVMatrix= XRMat4::Scale(1.0f, 1.0f, 1.0f);






		g_pXrRenderContext->UpdateUniformBlock(pUB, &sv2D_param);
		g_pXrRenderContext->VSSetUniformBlock(0, pUB);

		return 0;
	}
	Int32 channelId;
	
	float m_CarRect[4];
};

#endif //__SV_DELEGATE_H__
