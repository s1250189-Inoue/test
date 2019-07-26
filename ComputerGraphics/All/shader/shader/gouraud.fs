#version 120
// gouraud.fs

void main( void )
{
    // retrieve color after rasterization
    gl_FragColor = gl_Color;
}
