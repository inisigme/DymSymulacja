#version 420
uniform sampler2DArray tex;
in vec2 texCoord;
flat in float snowFlake;
out vec4 outColor;
flat in float l;
uniform vec3 kolorDymu;
uniform float alpha;
void main()
{
    vec4 color = texture( tex, vec3( texCoord, snowFlake ) );

   float dis = length(color.xyz);
    if(dis < 1.5)
        discard;
    else
    outColor = vec4(kolorDymu*dis,alpha);

//  outColor = vec4(color.w * vec4(kolorDymu,1.0));;
}
