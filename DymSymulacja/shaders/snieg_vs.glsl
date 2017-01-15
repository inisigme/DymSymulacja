//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GLSL 3.30
//////////////////////////////////////////////////////////////////////
#version 330

//////////////////////////////////////////////////////////////////////
// iloczyn macierzy modelu-widoku i macierzy rzutowania
//////////////////////////////////////////////////////////////////////
uniform mat4 modelViewProjectionMatrix;

//////////////////////////////////////////////////////////////////////
// rozmiar punktu
//////////////////////////////////////////////////////////////////////
uniform float pointSize;

//////////////////////////////////////////////////////////////////////
// numery indeks?w poszczeg?lnych atrybut?w wierzcho?k?w
//////////////////////////////////////////////////////////////////////
#define POSITION  0

//////////////////////////////////////////////////////////////////////
// wsp??rz?dne wierzcho?ka i numer p?atka ?niegu
//////////////////////////////////////////////////////////////////////
layout( location = POSITION ) in vec4 inPosition;

//////////////////////////////////////////////////////////////////////
// numer tekstury p?atka ?niegu
//////////////////////////////////////////////////////////////////////
flat out float snowFlake;

//////////////////////////////////////////////////////////////////////
// program g??wny
//////////////////////////////////////////////////////////////////////
void main()
{
    // standardowe przekszta?cenie wierzcho?k?w
    gl_Position = modelViewProjectionMatrix * vec4( inPosition.xyz, 1.0 );

    // numer tekstury p?atka ?niegu
    snowFlake = inPosition.w;

    // wielko?? punktu modulowana przez warto??
    // trzeciej wsp??rz?dnej jego po?o?enia
    gl_PointSize = 70.0;
}
