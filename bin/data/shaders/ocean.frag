
uniform vec3 uAmbient;
uniform vec3 uDiffuse;
uniform vec3 uSpecular;
uniform float uSpecIntensity;

uniform vec3 uSunPos;
uniform vec3 uEyePos;
varying vec3 varEyeNormal;
varying float fogFactor;

void main (void)
{
	
    vec3 N = varEyeNormal;
    vec3 L = normalize(uSunPos);
    vec3 H = normalize(L + uEyePos);
	
    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
	
    sf = pow(sf, uSpecIntensity);
	
    vec3 col = uAmbient + uDiffuse * df + uSpecular * sf;
	
	//gl_FragColor = vec4(col*gl_Color.xyz,fogFactor);
	gl_FragColor = vec4(varEyeNormal*.5 + .5,fogFactor);
}

