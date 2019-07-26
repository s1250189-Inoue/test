#version 120
// phong.vs

// prepare variables for the use in fragment shader
varying vec3 vcoord;
varying vec3 vnormal;

void main( void )
{
    // compute the position of each vertex in the world coordinate system
    vcoord = vec3( gl_ModelViewMatrix * gl_Vertex );
    // compute the normal vector of each vertex in the world coordinate system
    vnormal = normalize( gl_NormalMatrix * gl_Normal );

    // compute screen coordinates of each vertex
    gl_Position = ftransform();
}
