#version 410
#define FRAME_LAYERS 1
#define MAX_VERTICES 4


layout( points, invocations = 1 ) in;
layout( triangle_strip, max_vertices = MAX_VERTICES ) out;

uniform mat4 modelViewProjectionMatrix[FRAME_LAYERS];
uniform float pointSize;
uniform mat4x3 offsets;

vec2 texCoords[MAX_VERTICES] = vec2[MAX_VERTICES]
(
    vec2( 0.0, 1.0 ),
    vec2( 0.0, 0.0 ),
    vec2( 1.0, 1.0 ),
    vec2( 1.0, 0.0 )
);
in vec4 inoutPosition[1];
out vec2 texCoord;
flat out float snowFlake;
flat out float l;
void main()
{
    gl_Layer = gl_InvocationID;
    // generowanie wierzcho�k�w
    for( int v = 0; v < MAX_VERTICES; v++ )
    {
        gl_Position = modelViewProjectionMatrix[gl_InvocationID] * (vec4( inoutPosition[0].xyz + offsets[v]*pointSize,1) );
        gl_ViewportIndex = 1;
        texCoord = texCoords[v];
        snowFlake = inoutPosition[0].w;
        l = length(vec2(8,8) - inoutPosition[0].xz);
        l /=8;
        EmitVertex();
    }

    // koniec prymitywu
    EndPrimitive();
}
