const int FRAME_LAYERS = 1;
uniform sampler2DArray tex;
uniform int texnr;
in vec2 inoutTexCoord;
out vec4 outColor;
void main()
{
    outColor = vec4( 0.0 );

  for( int layer = 0; layer < FRAME_LAYERS; layer++ )
    {
        outColor += (FRAME_LAYERS - layer) * texture( tex, vec3( inoutTexCoord, layer ) );
    
    }
		
    outColor /= outColor.a;
}
