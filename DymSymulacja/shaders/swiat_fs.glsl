#version 420
uniform sampler2D tex;
in vec2 outTexCoord;
out vec4 outColor;

void main()
{
  outColor = vec4(texture( tex, outTexCoord).xyz,1.0);
  //outColor = vec4(0.0,1.0,0.0,1.0);
  //if( outTexCoord.x < 0.5)
   //   outColor = vec4(0.0,1.0,0.0,0.5);
  //else
   //   outColor = vec4(1.0,0.0,0.0,0.5);*/
  // outColor = vec4(1.0, 1.0, 0.0, 1.0);
  // outColor = vec4(outTexCoord.x,outTexCoord.x,outTexCoord.x,1);
    // discard;
   // outColor = vec4( length(outColor),length(outColor),length(outColor),length(outColor));
   // outColor = texture(tex,outTexCoord);

}
