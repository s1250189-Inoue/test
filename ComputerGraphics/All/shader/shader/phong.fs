#version 120
// phong.fs

// retrieve variables after rasterization
varying vec3 vcoord;
varying vec3 vnormal;

void main( void )
{
    // compute the unit normal vector of each pixel after rasterization
    vec3 fnormal = normalize( vnormal );
    // compute the light direction in the world coordinate system
    vec3 light  = normalize( gl_LightSource[ 0 ].position.xyz - vcoord );

    // set ambient color for each pixel
    gl_FragColor = gl_LightSource[ 0 ].ambient * gl_FrontMaterial.ambient;

    // diffuse
    float cosTheta = clamp( dot( light, fnormal ), 0.0, 1.0 );
    float diffuse = cosTheta;
    // set diffuse color for each pixel
    gl_FragColor += gl_LightSource[ 0 ].diffuse
                    * gl_FrontMaterial.diffuse * diffuse;

    // specular
    vec3 reflection = 2.0*dot( light, fnormal )*fnormal - light;
    reflection = normalize( reflection );
    vec3 view = normalize( vcoord );
    view *= -1.0;
    float cosAlpha = clamp( dot( view, reflection ), 0.0, 1.0 );
    float specular = pow( cosAlpha, gl_FrontMaterial.shininess );
    // set specular color for each pixel
    gl_FragColor += gl_LightSource[ 0 ].specular
                    * gl_FrontMaterial.specular * specular;
}
