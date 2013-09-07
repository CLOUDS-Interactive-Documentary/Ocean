
//varying float positionValid;
const float epsilon = 1e-6;
varying float fogFactor;

void main (void)
{
	gl_FragColor = vec4(gl_Color.xyz,fogFactor);	
}
