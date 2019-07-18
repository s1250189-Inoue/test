#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOW_SIZE                (512)

// maximum limit of elements
#define MAX_VERTICES     (16384)
#define MAX_EDGES        (16384)
#define MAX_FACES        (16384)
#define MAX_CORNERS      (64)

// *** Simple winged-edge data structure ***
// vertices
int nVertices = 0;
double vertex[ MAX_VERTICES ][ 3 ];
// edges
int nEdges = 0;
int edge[ MAX_EDGES ][ 2 ];
// faces
int nFaces = 0;

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
                &( vertex[ i ][ 0 ] ), &( vertex[ i ][ 1 ] ), &( vertex[ i ][ 2 ] ) );
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
            edge[ nEdges ][ 0 ] = corner[ j ];
            edge[ nEdges ][ 1 ] = corner[ (j+1)%nCorners ];
            nEdges++;
        }
    }

    fclose( fp_r );

    fprintf( stderr, "Number of edges = %d\n", nEdges );
    fprintf( stderr, "Number of faces = %d\n", nFaces );
}

// draw the object 
void draw_object( void )
{
    // loop counter
    int i;

    // set the line width
    glLineWidth( 3.0 );

    // change color to white
    glColor3d(  1.0,  1.0,  1.0 );

    // draw a list of line segments
    glBegin( GL_LINES );

    // for each edge
    for ( i = 0; i < nEdges; ++i ) {
        // draw the edge
        glVertex3dv( vertex[ edge[ i ][ 0 ] ] );
        glVertex3dv( vertex[ edge[ i ][ 1 ] ] );
    }
    glEnd();
}

// display callback function
void display( void )
{
    // clear buffer to preset color
    glClear( GL_COLOR_BUFFER_BIT );

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
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
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
    // set initial display mode
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
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

    // load the cube data file
    load_object( "cube.dat" );

    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
