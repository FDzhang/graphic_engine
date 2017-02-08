#ifndef __SV_CALI_H__
#define __SV_CALI_H__

#include "XrCore/XrSrc/External/XrHeaders.h"
#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"


class SVCalibration
{
public:
	SVCalibration() {
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

	void Init(IUINode* node, float* exparam,int exparamsize,char *pexparamname);

	void ToggleShow();

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
		if (m_dtx != 0) {
			m_exparam[12+m_chn*3] += m_dtx;
		}
		if (m_dty != 0) {
			m_exparam[13+m_chn*3] += m_dty;
		}
		if (m_dtz != 0) {
			m_exparam[14+m_chn*3] += m_dtz;
		}
		if (m_drx != 0) {
			m_exparam[0+m_chn] += m_drx;
		}
		if (m_dry != 0) {
			m_exparam[4+m_chn] += m_dry;
		}
		if (m_drz != 0) {
			m_exparam[8+m_chn] += m_drz;
		}
	}

	void SaveExParam(void);

private:
	IUINode*		m_node;
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
};


#endif //__SV_CALI_H__
