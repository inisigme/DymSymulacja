#version 410
#define FRAME_LAYERS 1
#define MAX_VERTICES 3


layout( triangles  , invocations = 1 ) in;
layout( triangle_strip , max_vertices = MAX_VERTICES ) out;

uniform mat4 modelViewProjectionMatrix;

in vec2 inTexCoord[3];
in vec4 inPosition[3];
out vec2 outTexCoord;
void main()
{
    gl_Layer = gl_InvocationID;
    for( int v = 0; v < MAX_VERTICES; v++ )
    {
        gl_Position = modelViewProjectionMatrix * inPosition[v] ;
        gl_ViewportIndex = 1;
        outTexCoord = 5*inTexCoord[v];
        EmitVertex();
    }

    EndPrimitive();
}
