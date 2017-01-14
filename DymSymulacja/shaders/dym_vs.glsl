#version 330
#define POSITION  0
layout( location = POSITION ) in vec4 inPosition;

out vec4 inoutPosition;

void main()
{
    inoutPosition = inPosition;
}
