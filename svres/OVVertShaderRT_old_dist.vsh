attribute highp vec4	myVertex;
attribute highp vec4	myNormal;
attribute mediump vec2	myUV;

uniform highp float coeff[24];
uniform highp vec2 CP;
uniform mediump float zDepth;
uniform mediump mat4	myPMVMatrix;
uniform mediump mat4	uvPMVMatrix;
uniform int Nums;
uniform highp vec3 Trans;
uniform highp vec2 Bound;

varying mediump vec2  TexCoord;
varying mediump vec2  TexCoord2;
varying mediump vec3 Lumin_coef;

void main(void)
{
	gl_Position = myPMVMatrix * myVertex;

	highp vec4 temp = myNormal;
	float interpolate;
	if (myNormal.y < Bound[0]) {
		interpolate = (Bound[0]-myNormal.y)/Bound[1];
		temp+=vec4(Trans, 0.0)*interpolate;
	}

	highp vec4 UV = uvPMVMatrix * temp;

	highp float invnorm = 1.0/length(vec2(UV.xy));
	highp float theta = atan(UV.z*invnorm);
	highp float t_i = 1.0;
	highp float rho = coeff[0];

	for (int i = 1; i < Nums; i++) {
		t_i *= theta;
	        rho += t_i*coeff[i]; 
              // rho += t_i;
    }
  
	//TexCoord = UV.xy*rho*invnorm + CP;
        TexCoord = UV.xy*rho*invnorm + CP;
	TexCoord.x /= 640.0;
	TexCoord.y /= 480.0;
	//TexCoord.x = myNormal.x;
	//TexCoord.y = myNormal.y;//480.0;
	TexCoord2 = vec2(1.0,1.0);
        Lumin_coef = vec3(1.0,1.0,1.0);
}

