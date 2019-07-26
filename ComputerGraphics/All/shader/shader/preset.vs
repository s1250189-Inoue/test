// preset.vs

void main( void )
{
    // set color to green
    gl_FrontColor = vec4( 0.0, 1.0, 0.0, 1.0 );

    // compute screen coordinates of each vertex
    gl_Position = ftransform();
}
