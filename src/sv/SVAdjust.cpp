#include "SVAdjust.h"


#define CALIDELTA 0.0014
#define CALIDELTAT 5


void SVAdjust::Init( float* exparam,int exparamsize,char *pexparamname)
{
	m_exparam = exparam;
	m_exparam_size = exparamsize;
	m_pFileName= pexparamname;
	for(int i =0;i<24;i++)
	{
	    m_preParam[i] = m_exparam[i];
	}

}


void SVAdjust::SelectChnl(int id)
{
    SetChannel(id);
}

void SVAdjust::AdjustParam(int id)
{
    switch(id)
    {
        case ADJ_ROTX_POS:
			SetChangeRX(CALIDELTA);
		break;
        case ADJ_ROTX_NEG:
			SetChangeRX(-CALIDELTA);
		break;
        case ADJ_ROTY_POS:			
			SetChangeRY(CALIDELTA);
		break;
        case ADJ_ROTY_NEG:
			SetChangeRY(-CALIDELTA);		
		break;
        case ADJ_ROTZ_POS:
			SetChangeRZ(CALIDELTA);			
		break;
        case ADJ_ROTZ_NEG:
			SetChangeRZ(-CALIDELTA);			
		break;
        case ADJ_TRANSX_POS:
			SetChangeTX(CALIDELTAT);		
		break;
        case ADJ_TRANSX_NEG:
			SetChangeTX(-CALIDELTAT);					
		break;
        case ADJ_TRANSY_POS:
			SetChangeTY(CALIDELTAT);					
		break;
        case ADJ_TRANSY_NEG:
			SetChangeTY(-CALIDELTAT);					
		break;
        case ADJ_TRANSZ_POS:
			SetChangeTZ(CALIDELTAT);								
		break;
        case ADJ_TRANSZ_NEG:
			SetChangeTZ(-CALIDELTAT);					
		break;																
    }
	Update();
}

void SVAdjust::SaveExParam()
{
    FILE* FP = fopen(m_pFileName, "wb");
    fwrite(m_exparam, m_exparam_size, 1, FP);
    fclose(FP);


}


