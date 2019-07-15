#include <stdio.h>
#include <GL/glut.h>

#define WINDOW_SIZE	(512)

#define NUM_OF_VERTICES         (5)
#define NUM_OF_EDGES             (8)

// (quadrangular) pyramid
double vertex[][3] = {
    {  0.0,  0.0,  0.3 }, // Vertex A
    { -0.7, -0.5, -0.3 }, // Vertex B
    { -0.7,  0.5, -0.3 }, // Vertex C
    {  0.7,  0.5, -0.3 }, // Vertex D
    {  0.7, -0.5, -0.3 }  // Vertex E
};

int edge[][2] = {
    { 1, 0 }, // Edge B-A
    { 4, 0 }, // Edge E-A
    { 3, 0 }, // Edge D-A
    { 2, 0 }, // Edge C-A
    { 1, 4 }, // Edge B-E
    { 4, 3 }, // Edge E-D
    { 3, 2 }, // Edge D-C
    { 2, 1 }  // Edge C-B
};

// draw coordinate axes
void draw_axes( void )
{
    // set the line width
    glLineWidth( 3.0 );

    // draw the coordinate axes
    glBegin( GL_LINES );

    // change color to red
    glColor3d (  1.0,  0.0,  0.0 );
    // draw the x-axis
    glVertex3d(  0.0,  0.0,  0.0 );
    glVertex3d(  0.8,  0.0,  0.0 );

    // change color to green
    glColor3d (  0.0,  1.0,  0.0 );
    // draw the y-axis
    glVertex3d(  0.0,  0.0,  0.0 );
    glVertex3d(  0.0,  0.8,  0.0 );

    // change color to blue
    glColor3d (  0.0,  0.5,  1.0 );
    // draw the z-axis
    glVertex3d(  0.0,  0.0,  0.0 );
    glVertex3d(  0.0,  0.0,  0.8 );

    glEnd();
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
    for ( i = 0; i < NUM_OF_EDGES; ++i ) {
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

    // rotate the scene around the x-axis by 30 degrees 
    glRotated( 30.0, 1.0, 0.0, 0.0 );

    // draw coordinate axes
    draw_axes();

    // draw the object
    draw_object();

    // swap the foreground and background buffers
    glutSwapBuffers();
}

// reshape callback function
void reshape( int w, int h )
{
    // specify the viewport
    glViewport( 0, 0, w, h );
    // initialize the transformation matrix
    glLoadIdentity();

    // calculate the aspect ratio of the window
    double aspect = ( double )w/( double )h;
    // smaller size
    int ss;
    // If the window is wide,
    if ( aspect >= 1.0 ) ss = h;
    // Otherwise
    else ss = w;
    // keep the aspect ratio irrespective of
    // the size of the window
    glOrtho( -2.0*(double)w/(double)ss,
              2.0*(double)w/(double)ss,
             -2.0*(double)h/(double)ss,
              2.0*(double)h/(double)ss,
             -1.0, 1.0 );
}
// callback function for handling mouse clicking
void mouse( int button, int state, int x, int y )
{
    // switch according to the mouse event
    switch ( button ) {
      // left mouse event
      case GLUT_LEFT_BUTTON:
	  printf( "Left" );
	  break;
      // middle mouse event
      case GLUT_MIDDLE_BUTTON:
	  printf( "Middle" );
	  break;
      // right mouse event
      case GLUT_RIGHT_BUTTON:
	  printf( "Right" );
	  break;
      default:
	  printf( "Unknown button" );
	  break;
    }

    printf(" is ");

    switch ( state ) {
      // mouse button is released
      case GLUT_UP:
	  printf( "released" );
	  break;
      // mouse button is pressed
      case GLUT_DOWN:
	  printf( "pressed" );
	  break;
      default:
	  printf( "manipulated" ); 
	  break;
    }

    // print the screen coordinates of the mouse event
    printf( " at the screen coordinates (%d, %d)\n", x, y );
}

// callback founction for handling mouse dragging
void motion( int x, int y )
{
    // print the current screen coordinates of the mouse pointer
    printf( "Mouse pointer is dragged to the screen coordinates (%d, %d)\n",
            x, y );
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
    // clearing frame buffer
    init();
    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
