#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOW_SIZE	(512)

// maximum limit of elements
#define MAX_VERTICES	(16384)
#define MAX_EDGES	(16384)
#define MAX_FACES	(16384)
#define MAX_CORNERS	(64)

// dummy index
#define NO_INDEX        (-1)

// *** Simple winged-edge data structure ***
// structure for vertex coordinates
typedef struct {
    double v[ 3 ];      // 3D coordinates
} coord;

// structure for a winged edge
typedef struct {
    int vidO;           // origin vertex ID of the edge
    int vidD;           // destination vertex ID of the edge
    int fidL;           // left face ID
    int fidR;           // right face ID
} winged;

// structure for a face
typedef struct {
  coord normal;	// unit normal vector
    int vid[ MAX_CORNERS ];
                        // IDs of vertices on the face
                        // (Note that this data structure is
                        // redundant. Retaining a pointer to
                        // an edge on the face is sufficient.
    int nV;             // number of vertices on the face
} facet;

// vertices
int nVertices = 0;
coord vertex[ MAX_VERTICES ];

// edges
int nEdges = 0;
winged edge[ MAX_EDGES ];
// faces
int nFaces = 0;
facet face[ MAX_FACES ];
// vertex normals
coord normal[ MAX_VERTICES ];
// angles of incidence and azimuth
double incidence        = 45.0;
double azimuth          = 30.0;
// aspect ratio
double aspect		=  1.0;
// distance between the eye and origin
double distance		=  4.0;

// Position of the Light No. 0 (Directional light)
float light0_position[] = { 1.0, 1.0, 1.0, 0.0 };
// Position of the Light No. 1 (Directional light)
float light1_position[] = {-1.0,-1.0,-1.0, 0.0 };
// colors
float red[] =             { 1.0, 0.0, 0.0, 1.0 };
float green[] =           { 0.0, 1.0, 0.0, 1.0 };
float blue[] =            { 0.0, 0.0, 1.0, 1.0 };
float yellow[] =          { 1.0, 1.0, 0.0, 1.0 };
float cyan[] =            { 0.0, 1.0, 1.0, 1.0 };
float white[] =           { 1.0, 1.0, 1.0, 1.0 };



// flags for mouse button ON/OFF (OFF = 0, ON = 1)
int left_mouse = 0, middle_mouse = 0, right_mouse = 0;
// previous coordinates of the mouse pointer
int last_pointer_x, last_pointer_y;

//------------------------------------------------------------------------------
//	Functions for vector calculations
//------------------------------------------------------------------------------
// add vectors
coord add_vectors( coord a, coord b )
{
    int k;		// loop counter
    coord sum;		// sum of the two input vectors
    for ( k = 0; k < 3; ++k ) {
	sum.v[ k ] = a.v[ k ] + b.v[ k ];
    }
    return sum;
}

// subtract vectors
coord subtract_vectors( coord a, coord b )
{
    int k;		// loop counter
    coord diff;		// difference between the two input vectors
    for ( k = 0; k < 3; ++k ) {
	diff.v[ k ] = a.v[ k ] - b.v[ k ];
    }
    return diff;
}

// inner product
double inner_prod( coord a, coord b )
{
    int k;		// loop counter
    double iprod = 0.0;	// inner product of the two input vectors
    for ( k = 0; k < 3; ++k ) {
	iprod += a.v[ k ] * b.v[ k ];
    }
    return iprod;
}

// outer product
coord outer_prod( coord a, coord b )
{
    int k;		// loop counter
    coord oprod;	// outer product of the two input vectors
    for ( k = 0; k < 3; ++k ) {
	oprod.v[ k ] = a.v[ (k+1)%3 ] * b.v[ (k+2)%3 ] - a.v[ (k+2)%3 ] * b.v[ (k+1)%3 ];
    }
    return oprod;
}

// normalize a vector
coord normalize( coord v )
{
    int k;		// loop counter
    double norm = sqrt( inner_prod( v, v ) );
			// norm of the input vector
    coord unit;		// normalized (unit) vector
    for ( k = 0; k < 3; ++k ) {
	unit.v[ k ] = v.v[ k ] / norm;
    }
    return unit;
}

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
    coord edgeL, edgeR;	 // edge vectors on each face
    // initialize the global variables
    nVertices = nEdges = nFaces = 0;

    // open the file
    if ( ( fp_r = fopen( filename, "r" ) ) == NULL ) {
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
	// initialize the vertex normal
	for ( j = 0; j < 3; ++j ) normal[ i ].v[ j ] = 0.0;
    }

    // load the number of faces
    fgets( buf, sizeof( buf ), fp_r );
    sscanf( buf, "%d", &nFaces );
    if ( nFaces > MAX_FACES ) {
        fprintf( stderr, "Too many faces\n" );
        nFaces = 0;
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

        // generate winged-edge data elements
        for ( j = 0; j < nCorners; j++ ) {
            face[ i ].vid[ j ] = corner[ j ];
            int eidT = search_edge( corner[ (j+1)%nCorners ], corner[ j ] );
            // If the counter part does not exist, generate a new edge.
            if ( eidT == NO_INDEX ) {
                edge[ nEdges ].vidO = corner[ j ];
                edge[ nEdges ].vidD = corner[ (j+1)%nCorners ];
		edge[ nEdges ].fidL = i;
                nEdges++;
            }
            // Otherwise, the opposite face of an existing edge
            else {
                edge[ eidT ].fidR = i;
            }
        }
	// generate a new face
	face[ i ].nV = nCorners;
  // obtain the two edge vectors outgoing from the 1st vertex of the face
	edgeL = subtract_vectors( vertex[ corner[ 0 ] ], vertex[ corner[ 1 ] ] );
	edgeR = subtract_vectors( vertex[ corner[ 2 ] ], vertex[ corner[ 1 ] ] );
	// compute the unit normal vector of the face
	face[ i ].normal = normalize( outer_prod( edgeR, edgeL ) );
	// distribute the normal of the face to the corner vertices
	for ( j = 0; j < nCorners; ++j )
	  normal[ corner[ j ] ] = add_vectors( normal[ corner[ j ] ], face[ i ].normal );
    }

    // finalize the vertex normals by normalizing them
    for ( i = 0; i < nVertices; ++i )
	normal[ i ] = normalize( normal[ i ] );

    fclose( fp_r );

    fprintf( stderr, "Number of edges = %d\n", nEdges );
    fprintf( stderr, "Number of faces = %d\n", nFaces );
#ifdef DEBUG
    for ( i = 0; i < nFaces; ++i ) {
        fprintf( stderr,
                 "Face No. %3d has the unit normal vector: (%6.3f, %6.3f, %6.3f)\n",
                 i,
                 face[ i ].normal.v[ 0 ],
                 face[ i ].normal.v[ 1 ],
                 face[ i ].normal.v[ 2 ] );
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
	  // set the normal vector at each vertex
	  glNormal3dv( normal[ face[ i ].vid[ j ] ].v );
	  glVertex3dv( vertex[ face[ i ].vid[ j ] ].v );
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

    // set up the directions of lights
    glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv( GL_LIGHT1, GL_POSITION, light1_position );

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
      //[ -- write your code to update the viewing parameters such as incidence and azimuth -- ]
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

// keyboard callback function
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

// initialize OpenGL setups
void init( void )
{
    // specify black color for clearing frame buffer
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // enable hidden surface removal by depth test
    glEnable( GL_DEPTH_TEST );

    // Enable back face culling
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    // set up the colors of lights
    glLightfv( GL_LIGHT0, GL_DIFFUSE, yellow );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, blue );

    // set up the colors of the material
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, cyan );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, cyan );
    
    // Enable lighting
    glEnable( GL_LIGHTING );
    // Activate Light No. 0
    glEnable( GL_LIGHT0 );
    // Activate Light No. 1
    glEnable( GL_LIGHT1 );
}

// main function
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
    // set a pointer to the display callback function
    glutDisplayFunc( display );
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
