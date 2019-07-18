#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

// min and max
#define MIN2( x, y )           (( (x)>(y) )? (y) : (x) )
#define MAX2( x, y )           (( (x)<(y) )? (y) : (x) )


#define WINDOW_SIZE                (512)

// maximum limit of elements
#define MAX_VERTICES     (16384)
#define MAX_EDGES        (16384)
#define MAX_FACES        (16384)
#define MAX_CORNERS      (64)

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
  int vid[ MAX_CORNERS ];
  // IDs of vertices on the face
  // (Note that this data structure is
  // redundant. Retaining a pointer to 
  // an edge on the face is sufficient.
  int nV;             // number of vertices on the face
  int	fid[ MAX_CORNERS ];
  // IDs of neighboring faces
  int nF;		// number of neighboring faces
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
// face colors
coord fcolor[ MAX_FACES ];

// angles of incidence and azimuth
double incidence        = 45.0;
double azimuth          = 30.0;
// aspect ratio
double aspect           =  1.0;
// distance between the eye and origin
double distance         =  6.0;

// flags for mouse button ON/OFF (OFF = 0, ON = 1)
int left_mouse = 0, middle_mouse = 0, right_mouse = 0;
// previous coordinates of the mouse pointer
int last_pointer_x, last_pointer_y;

// prior declaration of functions
void set_color( int idF );

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
  int i, j, k;        // loop counters
  FILE * fp_r = NULL;  // file pointer
  char buf[ 256 ];     // temporary buffer
  int nCorners = 0;
  int corner[ MAX_CORNERS ];
  // array of corner vertex IDs

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

    // initializle the color of the face
    set_color( i );
  }


  // initialize the number of neighbors for each face
  for ( i = 0; i < nFaces; ++i ) 
    face[ i ].nF = 0;
  // collect the neighboring faces by referring to edges

  for(i=0;i< nEdges; i++){
    face[edge[i].fidL].fid[face[i].fidL].nF=edge[i].fidR;
    face[edge[i].fidR].fid[face[i].fidR].nF=edge[i].fidL;

    face[edge[i].fidL].nF++;
    face[edge[i].fidR].nF++;
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

// set color according to the face ID
void set_color( int idF )
{
  // RGB colors
  double R = 0.0, G = 0.0, B = 0.0;

  // set the color of the face
  switch ( idF % 6 ) {
  case 0:   // red
    R = 1.0; G = 0.0; B = 0.0;
    break;
  case 1:   // green
    R = 0.0; G = 1.0; B = 0.0;
    break;
  case 2:   // blue
    R = 0.0; G = 0.0; B = 1.0;
    break;
  case 3:   // yellow
    R = 1.0; G = 1.0; B = 0.0;
    break;
  case 4:   // cyan
    R = 0.0; G = 1.0; B = 1.0;
    break;
  case 5:   // violet
    R = 1.0; G = 0.0; B = 1.0;
    break;
  }
  fcolor[ idF ].v[ 0 ] = R;
  fcolor[ idF ].v[ 1 ] = G;
  fcolor[ idF ].v[ 2 ] = B;
}

// blend the face color by referring to its adjacent ones
void update_color( int idF )
{
  // weight for color blending
  const double weight = 0.5;
  // average color of neighboring faces
  static coord ave;
  // loop counters
  int i, k; 

  // for each neighboring faces
  for ( k = 0; k < 3; ++k ) ave.v[ k ] = 0.0;

  for ( i = 0; i < face[ idF ].nF; ++i ) {
    int idNF = face[ idF ].fid[ i ];
    // blend the color of the face to those of neighbors
    for ( k = 0; k < 3; ++k ) 
      ave.v[ k ] += fcolor[ idNF ].v[ k ];
  }
  for ( k = 0; k < 3; ++k ) 
    ave.v[ k ] /= ( double )face[ idF ].nF;

  for ( k = 0; k < 3; ++k ) 
    fcolor[ idF ].v[ k ] =
      weight * fcolor[ idF ].v[ k ] + ( 1.0 - weight ) * ave.v[ k ];
}

// draw the object 
void draw_object( void )
{
  // loop counter
  int i, j;

  // 10% of face colors will be updated
  for ( i = 0; i < MAX2( 1, nFaces/10 ); ++i )
    update_color( ( int )( round( drand48()*nFaces + 0.5 ) - 1.0 ) );

  // set the line width
  glLineWidth( 1.0 );


  // draw a list of edges
  // set the color of the edges
  glColor3d( 1.0, 1.0, 1.0 );
  // set rasterization type and polygon facing
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  // for each face
  for ( i = 0; i < nFaces; ++i ) {
    // outline the face
    glBegin( GL_POLYGON );
    // for each corner vertex
    for ( j = 0; j < face[ i ].nV; ++j ) {
      glVertex3dv( vertex[ face[ i ].vid[ j ] ].v );
    }
    glEnd();
  }

  // hide the invisible lines by filling the face with the background color

  // set rasterization type and polygon facing
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  // enable polygon offset to avoid conflict with the polygon outlines
  glEnable( GL_POLYGON_OFFSET_FILL );
  glPolygonOffset( 1.0, 2.0 );
  // for each face
  for ( i = 0; i < nFaces; ++i ) {
    // set the color of each face
    glColor3dv( fcolor[ i ].v );
    // fill the face
    glBegin( GL_POLYGON );
    // for each corner vertex
    for ( j = 0; j < face[ i ].nV; ++j ) {
      glVertex3dv( vertex[ face[ i ].vid[ j ] ].v );
    }
    glEnd();
  }
  // disable polygon offset
  glDisable( GL_POLYGON_OFFSET_FILL );
}

// display callback function
void display( void )
{
  // clear the color and depth buffer simultaneously
  glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT );

  // set modelview matrix mode
  glMatrixMode( GL_MODELVIEW );
  // initialize with an identity matrix
  glLoadIdentity();

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
    break;
    // default
  default:
    break;
  }
  glutPostRedisplay();
}

// initialize OpenGL setups
void init( void )
{
  // specify black color for clearing frame buffer
  glClearColor( 0.0, 0.0, 0.0, 0.0 );  // specify black color for clearing frame buffer

  // enable hidden surface removal by depth test
  glEnable( GL_DEPTH_TEST );

  // Enable back face culling
  glEnable( GL_CULL_FACE );
  glCullFace( GL_BACK );
}

// main function
int main( int argc, char *argv[] )
{
  // initialize the seed for random numbers
  srand48( ( int )time( NULL ) );

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
