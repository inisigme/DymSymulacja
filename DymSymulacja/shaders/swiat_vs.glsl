#version 330
layout( location = 0 ) in vec4 inPosition2;
layout( location = 1) in vec2 inTexCoord2;
layout( location = 2) in vec3 normals;

out vec4 inPosition;
out vec2 inTexCoord;
void main()
{
    inPosition = inPosition2;
    inTexCoord = inTexCoord2;
}
