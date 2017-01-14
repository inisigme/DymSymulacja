
#version 150

//////////////////////////////////////////////////////////////////////
// prototyp funkcji zwracaj¹cej maskê filtra 3×3
//////////////////////////////////////////////////////////////////////
//mat3x3 Filter3x3( const int filter );

//////////////////////////////////////////////////////////////////////
// uchwyt tekstury 2D
//////////////////////////////////////////////////////////////////////
uniform sampler2D tex;

//////////////////////////////////////////////////////////////////////
// rodzaj filtra
//////////////////////////////////////////////////////////////////////
uniform int filterType;

//////////////////////////////////////////////////////////////////////
// interpolowane wspó³rzêdne tekstury
//////////////////////////////////////////////////////////////////////
in vec2 inoutTexCoord;

//////////////////////////////////////////////////////////////////////
// wyjœciowy kolor fragmentu
//////////////////////////////////////////////////////////////////////
out vec4 outColor;

//////////////////////////////////////////////////////////////////////
// program g³ówny
//////////////////////////////////////////////////////////////////////
void main()
{
    // pocz¹tkowy kolor wynikowy operacji splotu
  //  outColor = vec4( 0.0 );

    // maska filtra
  //  mat3x3 filter = Filter3x3( filterType );

    // obliczenie wartoœci sk³adowych teksela po filtracji
  //  outColor += mat3x4( textureOffset( tex, inoutTexCoord, ivec2( -1, -1 ) ),
  //                      textureOffset( tex, inoutTexCoord, ivec2(  0, -1 ) ),
  //                      textureOffset( tex, inoutTexCoord, ivec2(  1, -1 ) ) ) * filter[0];
  //  outColor += mat3x4( textureOffset( tex, inoutTexCoord, ivec2( -1,  0 ) ),
 //                       textureOffset( tex, inoutTexCoord, ivec2(  0,  0 ) ),
 //                       textureOffset( tex, inoutTexCoord, ivec2(  1,  0 ) ) ) * filter[1];
 //  outColor += mat3x4( textureOffset( tex, inoutTexCoord, ivec2( -1,  1 ) ),
  //                      textureOffset( tex, inoutTexCoord, ivec2(  0,  1 ) ),
   //                     textureOffset( tex, inoutTexCoord, ivec2(  1,  1 ) ) ) * filter[2];
	//outColor = vec4(1.0,0.0,1.0,1.0);
	outColor = textureOffset(tex, inoutTexCoord, ivec2(0,0));
	if(outColor.x + outColor.y + outColor.z < 1.2) discard;
}
