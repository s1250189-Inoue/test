#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define WINDOW_SIZE                (512)

#include "common.h"
#include "coord.h"
#include "glsl.h"

// shader objects
static unsigned int vertexShader;
static unsigned int fragmentShader;
static unsigned int gl2Program;


// vertices and surface normals
int nVertices = 0;
coord vertex[ MAX_VERTICES ];
coord normal[ MAX_VERTICES ];
// edges
int nEdges = 0;
winged edge[ MAX_EDGES ];
// faces
int nFaces = 0;
facet face[ MAX_FACES ];

// angles of incidence and azimuth
double incidence	= 45.0;
double azimuth		= 15.0;
// aspect ratio
double aspect		=  1.0;
// distance between the eye and origin
double distance		=  3.6;

// flags for mouse button ON/OFF (OFF = 0, ON = 1)
int left_mouse = 0, middle_mouse = 0, right_mouse = 0;
// previous coordinates of the mouse pointer
int last_pointer_x, last_pointer_y;

// Position of the Light No. 0 (Directional light)
float light0_position[] =   {-1.0,-1.0, 1.0, 0.0 };
// material colors
float light_diffuse[] =     { 1.0, 1.0, 1.0, 1.0 };
float light_ambient[] =     { 0.5, 0.5, 0.5, 1.0 };
float light_specular[] =    { 1.0, 1.0, 1.0, 1.0 };
float material_ambient[] =  { 0.3, 0.3, 0.3, 1.0 };
float material_diffuse[] =  { 0.4, 0.5, 0.6, 1.0 };
float material_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// search an existing edge
static int search_edge( int orig, int dest )
{
    int i;			// loop counter

    for ( i = 0; i < nEdges; i++ )
	if ( ( edge[ i ].vidO == orig ) && ( edge[ i ].vidD == dest ) )
	    return i;
    // If the edge cannot be found, return NO_INDEX
    return NO_INDEX;
}

// load an object
void load_object( char * filename )
{
    int i, j, k;         // loop counters
    FILE * fp_r = NULL;  // file pointer
    char buf[ 256 ];     // temporary buffer
    int nCorners = 0;
    int corner[ MAX_CORNERS ];
                                // array of corner vertex IDs
    // two edge vectors that are perpendicular to each face
    coord	edgeL, edgeR;

    // initialize the global variables
    nVertices = nEdges = nFaces = 0;

    // open the file
    if (( fp_r = fopen( filename, "r" ) ) == NULL) {
	fprintf( stderr, "cannot open the file: %s\n", filename );
	return;
    }

    // load the number of vertices
    fgets( buf, sizeof( buf ), fp_r );
    sscanf( buf, "%d", &nVertices );
    fprintf( stderr, "Number of vertices = %d\n", nVertices );
    if ( nVertices > MAX_VERTICES ) {
        fprintf( stderr, "Too many vertices\n" );
        return;
    }

    // load coordinates of each vertex
    for ( i = 0; i < nVertices; i++ ) {
	fgets( buf, sizeof( buf ), fp_r );
	sscanf( buf, "%lf %lf %lf",
		&( vertex[ i ].v[ 0 ] ), &( vertex[ i ].v[ 1 ] ), &( vertex[ i ].v[ 2 ] ) );
	// initialize the normal vector
	for ( j = 0; j < 3; j++ ) normal[ i ].v[ j ] = 0.0;
    }

    // load the number of faces
    fgets( buf, sizeof( buf ), fp_r );
    sscanf( buf, "%d", &nFaces );
    if ( nFaces > MAX_FACES ) {
	fprintf( stderr, "Too many faces\n" );
	nVertices = 0;
    }

    // load corner vertices of each face
    for ( i = 0; i < nFaces; i++ ) {

	// load the number of edges for each face
	fgets( buf, sizeof( buf ), fp_r );
	sscanf( buf, "%d", &nCorners );
        // load the corner vertex IDs of each face
	fgets( buf, sizeof( buf ), fp_r );
	k = 0;
	for ( j = 0; j < nCorners; j++ ) {
	    while ( ( buf[ k ] == ' ' || buf[ k ] == '\t' ) ) k++;
	    sscanf( &( buf[ k ] ), "%d", &( corner[ j ] ) );
	    while ( ( '0' <= buf[ k ] ) && ( buf[ k ] <= '9' ) ) k++;
	}

	// generate winged-edge data structures
	for ( j = 0; j < nCorners; j++ ) {
	    face[ i ].eid[ j ] = corner[ j ];
	    int eidT = search_edge( corner[ (j+1)%nCorners ], corner[ j ] );
	    // If the counter part does not exist, generate a new edge.
	    if ( eidT == NO_INDEX ) {
		edge[ nEdges ].vidO = corner[ j ];
		edge[ nEdges ].vidD = corner[ (j+1)%nCorners ];
		edge[ nEdges ].fidL = i;
		nEdges++;
	    }
	    // Otherwise
	    else {
		edge[ eidT ].fidR = i;
	    }
	}

	// generate a new face
	face[ i ].nV = nCorners;
	edgeL = subtract_vectors( vertex[ corner[ 0 ] ], vertex[ corner[ 1 ] ] );
	edgeR = subtract_vectors( vertex[ corner[ 2 ] ], vertex[ corner[ 1 ] ] );
	face[ i ].normal = normalize( outer_prod( edgeR, edgeL ) );
	// propagate the calculation to the corner vertices
	for ( j = 0; j < nCorners; j++ ) {
	    normal[ corner[ j ] ] = add_vectors( normal[ corner[ j ] ], face[ i ].normal );
	}
    }
    // finalize the normals at vertices
    for ( i = 0; i < nVertices; i++ ) {
	normal[ i ] = normalize( normal[ i ] );
    }

    fclose( fp_r );

    fprintf( stderr, "Number of edges = %d\n", nEdges );
#ifdef DEBUG
    for ( i = 0; i < nEdges; ++i ) {
	fprintf( stderr,
		 "Edge No. %3d is incident to Faces No. %3d and No. %3d\n",
		 i, edge[ i ].fidL, edge[ i ].fidR );
    }
#endif // DEBUG
    fprintf( stderr, "Number of faces = %d\n", nFaces );
#ifdef DEBUG
    for ( i = 0; i < nFaces; ++i ) {
        fprintf( stderr, "Face No. %3d has Vertices ", i );
        for ( j = 0; j < face[ i ].nV; ++j ) {
            fprintf( stderr, "No. %3d", face[ i ].vid[ j ] );
            if ( j == face[ i ].nV - 2 ) fprintf( stderr, " and " );
            else if ( j == face[ i ].nV - 1 ) fprintf( stderr, "." );
            else fprintf( stderr, ", " );
        }
        fprintf( stderr, "\n" );
    }
#endif // DEBUG
}

// draw the object
void draw_object( void )
{
    // loop counters
    int i, j;

    // for each face
    for ( i = 0; i < nFaces; ++i ) {
	// fill the face
	glBegin( GL_POLYGON );
	// for each corner vertex
	for ( j = 0; j < face[ i ].nV; ++j ) {
	    // set the normal vector
	    glNormal3dv( normal[ face[ i ].eid[ j ] ].v );
	    // set the vertex coordinates
	    glVertex3dv( vertex[ face[ i ].eid[ j ] ].v );
	}
	glEnd();
    }
}

// display callback function
void display( void )
{
    // clear the color and depth buffer simultaneously
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // set modelview matrix mode
    glMatrixMode( GL_MODELVIEW );
    // initialize with an identity matrix
    glLoadIdentity();

    // set up the positions of lights
    glLightfv( GL_LIGHT0, GL_POSITION, light0_position );

    // Note: transformation matrices are applied in the reverse order
    // translate the object along the view direction (z-axis)
    glTranslated( 0.0, 0.0, -distance );
    // rotate the object by the angle of incidence
    glRotated( -incidence, 1.0, 0.0, 0.0 );
    // rotate the object by the angle of azimuth
    glRotated( -azimuth, 0.0, 0.0, 1.0 );

    // draw the object
    draw_object();

    // swap the foreground and background buffers
    glutSwapBuffers();
}

// reshape callback function
void reshape( int w, int h )
{
    // calculate the aspect ratio of the window
    aspect = ( double )w/( double )h;

    // specify the viewport
    glViewport( 0, 0, w, h );
    // set projection matrix mode
    glMatrixMode( GL_PROJECTION );
    // initialize the transformation matrix
    glLoadIdentity ();
    // set the viewing angle, distances from the near and far
    // clipping planes from the viewpoint
    gluPerspective( 65.0, aspect, 0.1, 100.0 );

    // additionally inserted
    // glMatrixMode( GL_MODELVIEW );
}

// callback function for redrawing scene as the background task
void idle( void )
{
    // Update the screen scene
    glutPostRedisplay();
}

// callback function for handling mouse clicking
void mouse( int button, int state, int x, int y )
{
    // switch according to the mouse event
    switch ( button ) {
      // left mouse event
      case GLUT_LEFT_BUTTON:
          if ( state == GLUT_DOWN ) {
              left_mouse = 1;
              last_pointer_x = x;
              last_pointer_y = y;
          }
          else left_mouse = 0;
          break;
      // middle mouse event
      case GLUT_MIDDLE_BUTTON:
          if ( state == GLUT_DOWN ) {
              middle_mouse = 1;
              last_pointer_x = x;
              last_pointer_y = y;
          }
          else middle_mouse = 0;
          break;
      // right mouse event
      case GLUT_RIGHT_BUTTON:
          if ( state == GLUT_DOWN ) {
              right_mouse = 1;
              last_pointer_x = x;
              last_pointer_y = y;
          }
          else right_mouse = 0;
          break;
      // default
      default:
          printf( "Unknown button " );
          break;
    }
}

// callback founction for handling mouse dragging
void motion( int x, int y )
{
    const double ratio = 0.1;
    const double extent = 0.1;

    // dragging the right mouse button
    if ( right_mouse ) {
	azimuth -= ratio * ( double )( x - last_pointer_x );
	incidence -= ratio * ( double )( y - last_pointer_y );
    }
    // dragging the middle mouse button
    else if ( middle_mouse ) {
	distance -= extent * ( double )( y - last_pointer_y );
    }

    // update the latest mouse coordinates
    last_pointer_x = x;
    last_pointer_y = y;
    // redraw the 3D scene
    glutPostRedisplay();
}

// callback function for inputs from keyboard
void keyboard( unsigned char key, int x, int y )
{
   // switch according to the input from the keyboard
   switch ( key ) {
     // quit the program
     case 'q':
     case 'Q':
     case '\033':  // ASCII code of ESC
         exit( 0 );
         break;
     // cube
     case '1':
         load_object( "cube.dat" );
         break;
     // icosahedron
     case '2':
         load_object( "icosa.dat" );
         break;
     // approximate sphere
     case '3':
         load_object( "sphere.dat" );
         break;
     // bunny
     case '4':
         load_object( "bunny.dat" );
         break;
     // mannequin
     case '5':
         load_object( "mannequin.dat" );
         break;
     // cat ornament
     case '6':
         load_object( "cat.dat" );
         break;
     // golfclub
     case '7':
         load_object( "golfclub.dat" );
         break;
     // horse
     case '8':
         load_object( "horse.dat" );
         break;     // default
     default:
         break;
   }
   glutPostRedisplay();
}

// initialize shader programs
void init_shaders( void )
{
    // variables for compling and linking shader programs
    int compiled, linked;

    // ########## Step 1 ##########
    // create shader objects
    vertexShader   = glCreateShader( GL_VERTEX_SHADER );
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

    // ########## Step 2 ##########
    // load the shader program sources
    if ( readShaderSource( vertexShader,   "diffuse.vs" ) ) exit( 1 );
    if ( readShaderSource( fragmentShader, "diffuse.fs" ) ) exit( 1 );

    // ########## Step 3 ##########
    // compile the source program of vertex shader
    glCompileShader	( vertexShader );
    glGetShaderiv	( vertexShader, GL_COMPILE_STATUS, &compiled );
    printShaderInfoLog	( vertexShader );
    if ( compiled == GL_FALSE ) {
	fprintf( stderr, "Compile error in vertex shader.\n" );
	exit( 1 );
    }
    // compile the source program of fragment shader
    glCompileShader	( fragmentShader );
    glGetShaderiv	( fragmentShader, GL_COMPILE_STATUS, &compiled );
    printShaderInfoLog	( fragmentShader );
    if ( compiled == GL_FALSE ) {
	fprintf( stderr, "Compile error in fragment shader.\n" );
	exit( 1 );
    }

    // ########## Step 4 ##########
    // create the program object
    gl2Program = glCreateProgram();

    // ########## Step 5 ##########
    // register the shader objects as shader programs
    glAttachShader( gl2Program, vertexShader );
    glAttachShader( gl2Program, fragmentShader );
    // delete shader objects
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    // ########## Step 6 ##########
    // link the shader program
    glLinkProgram( gl2Program );
    glGetProgramiv( gl2Program, GL_LINK_STATUS, &linked );
    printProgramInfoLog( gl2Program );
    if ( linked == GL_FALSE ) {
	fprintf( stderr, "Link error.\n" );
	exit( 1 );
    }

    // ########## Step 7 ##########
    // apply the shader program
    glUseProgram( gl2Program );
}

// initialize OpenGL setups
void init( void )
{
    // specify black color for clearing frame buffer
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // enable hidden surface removal by depth test
    glEnable( GL_DEPTH_TEST );

    // Disable back face culling
    glDisable( GL_CULL_FACE );

    // Enable lighting
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // set up the colors of lights
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    // set up the colors of the material
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, material_specular );
    glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, 50.0 );

    // initialize shader programs
    init_shaders();
}

//
// main program
//
int main( int argc, char *argv[] )
{
    // initialize GLUT
    glutInit( &argc, argv );
    // locate the top-left corner of the window
    glutInitWindowPosition( 50, 50 );
    // set the window size
    glutInitWindowSize( WINDOW_SIZE, WINDOW_SIZE );
    // set initial display mode while enable depth buffer simultaneously
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    // create a window
    glutCreateWindow( argv[0] );
    glutDisplayFunc( display );
    // set a pointer to the idle callback function
    // glutIdleFunc		( idle );
    // set a pointer to the reshape callback function
    glutReshapeFunc( reshape );
    // set a pointer to the mouse callback function
    glutMouseFunc( mouse );
    // set a pointer to the motion callback function
    glutMotionFunc( motion );
    // set a pointer to the keyboard callback function
    glutKeyboardFunc( keyboard );
    // clearing frame buffer
    init();

    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
