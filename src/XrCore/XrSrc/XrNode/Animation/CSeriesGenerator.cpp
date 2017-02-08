#include "CSeriesGenerator.h"

Void CSeriesGenerator::Generate(Float32 fromVal, Float32 toVal, Int32 duration, AnimationStyle style)
{
	m_from = fromVal;
    m_dx = (toVal - fromVal);
    m_startTime = XrGetTime();
    m_active = TRUE;
	m_style = style;
	//xrprint("fromVal = %f, toVal = %f!!!\n", fromVal, toVal);

}

Boolean CSeriesGenerator::GetStyle(Int32 timeStamp, Float32* result)
{
	if (!(m_style & AnimationStyle_Transition)) {
		return FALSE;
	}
    Int32 curTime = timeStamp - m_startTime;
		Float32 interpolate;
		Int32 timeSquare = (m_totalTime * m_totalTime);
	
		switch (m_style) {
			case AnimationStyle_EaseOut:
				interpolate = Float32(((m_totalTime<<1) - curTime) * curTime) / timeSquare;
				break;
			case AnimationStyle_EaseIn:
				interpolate = Float32(curTime * curTime) / timeSquare;
				break;
			case AnimationStyle_EaseInOut:
	            if (curTime < (m_totalTime>>1)) {
	                interpolate = Float32(2 * curTime * curTime) / timeSquare;
	            }
	            else {
	                interpolate = Float32(2 * curTime * (2 * m_totalTime - curTime) - timeSquare) / timeSquare;
	            }
				break;
			case AnimationStyle_Default:
			default:
				interpolate = Float32(curTime) / m_totalTime;
				break;
		}

    if (curTime >= m_totalTime) {
        m_active = FALSE;
        *result = m_from+m_dx;
		return m_active;
    }
    else m_active = TRUE;

	*result =m_from+m_dx * interpolate;
	//xrprint("value = %f!!!\n", m_host->m_curValue);
	return m_active;
}

static signed char coefs[16] = {
    -1, 2,-1, 0,
     3,-5, 0, 2,
    -3, 4, 1, 0,
     1,-1, 0, 0 };

Void CSeriesGenerator::SetKeyFrameData(Float32 *key, Int32 num, Int32 dim, AnimationStyle style)
{
	this->m_key = key;
	this->m_num = num;
	this->m_dim = dim;
	m_style = style;
}

Boolean CSeriesGenerator::GetSpline(Float32 t, Float32* result)
{
	if (!(m_style & AnimationStyle_KeySpline)) return FALSE;
    const int size = m_dim + 1;

    // find key
    int k = 0; while( m_key[k*size] < t ) k++;

    // interpolant
    const float h = (t-m_key[(k-1)*size])/(m_key[k*size]-m_key[(k-1)*size]);

    // init result
    for( int i=0; i < m_dim; i++ ) result[i] = 0.0f;

    // add basis functions
    for( int i=0; i<4; i++ )
    {
        int kn = k+i-2; if( kn<0 ) kn=0; else if( kn>(m_num-1) ) kn=m_num-1;

        const signed char *co = coefs + 4*i;

        const float b  = 0.5f*(((co[0]*h + co[1])*h + co[2])*h + co[3]);

        for( int j=0; j < m_dim; j++ ) result[j] += b * m_key[kn*size+j+1];
    }

	return TRUE;
}

Boolean CSeriesGenerator::GetLinear(Float32 t, Float32* result)
{
	if (!(m_style & AnimationStyle_KeyLinear)) return FALSE;
    const int size = m_dim + 1;

    // find key
    int k = 0; while( m_key[k*size] < t ) k++;

    // interpolant
	const float h = (t-m_key[(k-1)*size])/(m_key[k*size]-m_key[(k-1)*size]);

    // init result
    for( int i=0; i < m_dim; i++ ) {
		result[i] = m_key[(k-1)*size+i+1]*(1-h)+m_key[k*size+i+1]*h;
	}

	//xrprint("%dst key, h=%f, fromVal=%f, dstVal=%f\n", k-1, h, key[(k-1)*size+2], key[k*size+2]);
	return TRUE;
}

Boolean CSeriesGenerator::GetSimpleLinear(Float32 t, Float32* result)
{
	if (!(m_style & AnimationStyle_KeySimpleLinear)) return FALSE;
    const int size = m_dim + 1;

    // find key
    int k = 0; while( m_key[k*size] < t ) k++;

    // interpolant
	const float h = (t-m_key[(k-1)*size])/(m_key[k*size]-m_key[(k-1)*size]);

    // init result
    for( int i=0; i < m_dim; i++ ) {
		result[i] = m_key[(k-1)*size+i+1]*(1-h)+m_key[k*size+i+1]*h;
	}

	//xrprint("%dst key, h=%f, fromVal=%f, dstVal=%f\n", k-1, h, key[(k-1)*size+2], key[k*size+2]);
	return TRUE;
}
Boolean CSeriesGenerator::GetSpline(Float32 t, Float32* result, Float32* key, Int32 num, Int32 dim, Int32* pos)
{
    const int size = dim + 1;
	if (num==1 || t<=0.0) {
		for( int i=0; i < dim; i++ ) {
			result[i] = key[i+1];
		}
		return TRUE;
	}
    // find key
    int k = 0;
	if (pos) k=*pos;
	while( key[k*size] < t ) {
		k++;
	}
	if (pos) *pos= k;
    // interpolant
    const float h = (t-key[(k-1)*size])/(key[k*size]-key[(k-1)*size]);

    // init result
    for( int i=0; i < dim; i++ ) {
		result[i] = 0.0f;
	}

    // add basis functions
    for( int i=0; i<4; i++ )
    {
        int kn = k+i-2;
		if( kn<0 ) kn=0;
		else if( kn>(num-1) ) kn=num-1;

        const signed char *co = coefs + 4*i;
        const float b  = 0.5f*(((co[0]*h + co[1])*h + co[2])*h + co[3]);
        for( int j=0; j < dim; j++ ) {
			result[j] += b * key[kn*size+j+1];
		}
    }
	return TRUE;
}

Boolean CSeriesGenerator::GetLinear(Float32 t, Float32* result, Float32* key, Int32 num, Int32 dim, Int32* pos)
{
    const int size = dim + 1;

	if (num==1 || t<=0.0) {
		for( int i=0; i < dim; i++ ) {
			result[i] = key[i+1];
		}
		return TRUE;
	}
    // find key
    int k = 0;
	if (pos) k=*pos;
	while( key[k*size] < t ) k++;
	if (pos) *pos= k;
    // interpolant
	const float h = (t-key[(k-1)*size])/(key[k*size]-key[(k-1)*size]);
	
    // init result
    for( int i=0; i < dim; i++ ) {
		result[i] = key[(k-1)*size+i+1]*(1-h)+key[k*size+i+1]*h;
	}
	//xrprintf("1st=%f,2nd=%f, h=%f\n",  key[(k-1)*size+1],key[k*size+1], h);
	//xrprint("%dst key, h=%f, fromVal=%f, dstVal=%f\n", k-1, h, key[(k-1)*size+2], key[k*size+2]);
	return TRUE;
}