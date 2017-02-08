#ifndef __SV_ADJUST_H__
#define __SV_ADJUST_H__
#include "../XrCore/XrSrc/External/XrHeaders.h"


enum{

    ADJ_ROTX_POS=0,
	ADJ_ROTX_NEG,
	ADJ_ROTY_POS,
	ADJ_ROTY_NEG,
	ADJ_ROTZ_POS,
	ADJ_ROTZ_NEG,
	ADJ_TRANSX_POS,
	ADJ_TRANSX_NEG,
	ADJ_TRANSY_POS,
	ADJ_TRANSY_NEG,
	ADJ_TRANSZ_POS,
	ADJ_TRANSZ_NEG,

};

class SVAdjust
{
public:
	SVAdjust() {
		m_exparam = 0;
		m_chn = 0;
		m_dtx = 0;
		m_dty = 0;
		m_dtz = 0;
		m_drx = 0;
		m_dry = 0;
		m_drz = 0;
		m_exparam_size = 0;
	}

	void Init( float* exparam,int exparamsize,char *pexparamname);


	void SetChangeTX(float dval)
	{
		m_dtx = dval;
	}
	void SetChangeTY(float dval)
	{
		m_dty = dval;
	}
	void SetChangeTZ(float dval)
	{
		m_dtz = dval;
	}

	void SetChangeRX(float dval)
	{
		m_drx = dval;
	}
	void SetChangeRY(float dval)
	{
		m_dry = dval;
	}
	void SetChangeRZ(float dval)
	{
		m_drz = dval;
	}

	void SetChannel(int chn)
	{
		m_chn = chn;
	}

	void Update()
	{
		if (!m_exparam) return;
		if(m_chn>3) return;
		if (m_dtx != 0) {
			m_exparam[3+m_chn*6] += m_dtx;
			m_dtx=0;
		}
		if (m_dty != 0) {
			m_exparam[4+m_chn*6] += m_dty;
			m_dty=0;
		}
		if (m_dtz != 0) {
			m_exparam[5+m_chn*6] += m_dtz;
			m_dtz=0;
		}
		if (m_drx != 0) {
			m_exparam[0+m_chn*6] += m_drx;
			m_drx=0;
		}
		if (m_dry != 0) {
			m_exparam[1+m_chn*6] += m_dry;
			m_dry=0;
		}
		if (m_drz != 0) {
			m_exparam[2+m_chn*6] += m_drz;
			m_drz=0;
		}

	}
	
	void SaveExParam(void);
	
	void SelectChnl(int id);
	void AdjustParam(int id);
	int GetAdjustFlag();

private:
	Int32			m_nodeId;

	float		m_dtx;
	float		m_dty;
	float		m_dtz;
	float		m_drx;
	float		m_dry;
	float		m_drz;

	float*		m_exparam;
	int m_exparam_size;
	char *m_pFileName;
	int			m_chn;
	bool		m_show;
	int m_adjust_flag;
	float m_preParam[24];
};


#endif //__SV_CALI_H__
