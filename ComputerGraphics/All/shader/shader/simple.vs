#version 120
// simple.vs

void main( void )
{
    // compute screen coordinates of each vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
