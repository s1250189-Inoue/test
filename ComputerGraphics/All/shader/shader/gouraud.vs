#version 120
// gouraud.vs

void main( void )
{
    // compute the position of each vertex in the world coordinate system
    vec3 vcoord = vec3( gl_ModelViewMatrix * gl_Vertex );
    // compute the normal vector of each vertex in the world coordinate system
    vec3 normal = normalize( gl_NormalMatrix * gl_Normal );
    // compute the light direction in the world coordinate system
    vec3 light  = normalize( gl_LightSource[ 0 ].position.xyz - vcoord );

    // ambient
    gl_FrontColor = gl_LightSource[ 0 ].ambient * gl_FrontMaterial.ambient;

    // diffuse
    float cosTheta = clamp( dot( light, normal ), 0.0, 1.0 );
    float diffuse = cosTheta;
    // set diffuse color for each vertex
    gl_FrontColor += gl_LightSource[ 0 ].diffuse
                     * gl_FrontMaterial.diffuse * diffuse;

    // specular
    vec3 reflection = 2.0*dot( light, normal )*normal - light;
    reflection = normalize( reflection );
    vec3 view = normalize( vcoord );
    view *= -1.0;
    float cosAlpha = clamp( dot( view, reflection ), 0.0, 1.0 );
    float specular = pow( cosAlpha, gl_FrontMaterial.shininess );
    // set specular color for each vertex
    gl_FrontColor += gl_LightSource[ 0 ].specular
                     * gl_FrontMaterial.specular * specular;

    // compute screen coordinates of each vertex
    gl_Position = ftransform();
}
