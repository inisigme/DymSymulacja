//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GLSL 1.50
//////////////////////////////////////////////////////////////////////
#version 150

//////////////////////////////////////////////////////////////////////
// uchwyt tekstury sze�ciennej
//////////////////////////////////////////////////////////////////////
uniform samplerCube tex;

//////////////////////////////////////////////////////////////////////
// interpolowane wsp�rz�dne tekstury
//////////////////////////////////////////////////////////////////////
in vec3 outTexCoord;

//////////////////////////////////////////////////////////////////////
// wyj�ciowy kolor fragmentu
//////////////////////////////////////////////////////////////////////
out vec4 outColor;

void main()
{
    // pr�bkowanie tekstury
    outColor = vec4(texture( tex, outTexCoord ).xyz,0.5);
//	outColor = vec4(0.0,1.0,0.0,0.5);
}
