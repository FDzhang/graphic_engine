attribute highp vec4	myVertex;
attribute highp vec4	myNormal;
attribute mediump vec2	myUV;


uniform mediump mat4	myPMVMatrix;
uniform mediump mat4	uvPMVMatrix;
uniform mediump float focal;
uniform mediump float width;
uniform mediump float height;
uniform mediump float pixelsize;
uniform highp vec3 Trans;
uniform highp vec2 Bound;

varying mediump vec2  TexCoord;
varying mediump vec2  TexCoord2;
varying mediump vec3 Lumin_coef;

void main()
{
	gl_Position = myPMVMatrix * myVertex;
	
	vec4 temp=myNormal;
	float interpolate;
	if (myNormal.y < Bound[0]) {
		interpolate = (Bound[0]-myNormal.y)/Bound[1];
		temp+=vec4(Trans, 0.0)*interpolate;
	}
	//temp+=vec4(Trans, 0.0);
	//temp+=vec4(0.0,-6000.0,0.0, 0.0);
        vec4 UV = uvPMVMatrix * temp;
	float theta ;


	float invnorm = 1.0/length(vec2(UV.xy));
	theta = abs(atan(length(vec2(UV.xy))/(UV.z+0.001)));

	TexCoord = UV.xy*invnorm*(theta)*focal/(pixelsize);

	TexCoord.x = TexCoord.x;//*720.0/640.0;
	TexCoord.y = TexCoord.y;//*720.0/640.0;
	TexCoord = TexCoord + vec2(640,360);
	TexCoord.x /= width;
	TexCoord.y /= height;

	
	TexCoord2 = vec2(1.0,1.0);
	Lumin_coef.xyz = vec3(1.0,1.0,1.0);
        if(TexCoord.x <0.0||TexCoord.y<=0.0 )
        {
            Lumin_coef.xyz = vec3(0.0,0.0,0.0);
        }
        else if(TexCoord.x >1.0||TexCoord.y>1.0 )
        {
            Lumin_coef.xyz = vec3(0.0,0.0,0.0);
        }
	
}
