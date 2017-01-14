#version 420
uniform sampler2D tex;
in vec2 outTexCoord;
out vec4 outColor;

void main()
{
    outColor = texture2D( tex, outTexCoord)/5;
   // outColor = vec4(1.0, 0.0, 0.0, 0.0);
}
