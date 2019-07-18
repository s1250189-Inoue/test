#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOW_SIZE		(512)

#define NUM_OF_VERTICES		(8)
#define NUM_OF_EDGES		(12)

// cube
double vertex[NUM_OF_VERTICES][3] = {
    { -1.0, -1.0, -1.0 }, // A
    {  1.0, -1.0, -1.0 }, // B
    {  1.0,  1.0, -1.0 }, // C
    { -1.0,  1.0, -1.0 }, // D
    { -1.0, -1.0,  1.0 }, // E
    {  1.0, -1.0,  1.0 }, // F
    {  1.0,  1.0,  1.0 }, // G
    { -1.0,  1.0,  1.0 }  // H
};

int edge[NUM_OF_EDGES][2] = {
    { 0, 1 }, // A-B
    { 1, 2 }, // B-C
    { 2, 3 }, // C-D
    { 3, 0 }, // D-A
    { 0, 4 }, // A-E
    { 1, 5 }, // B-F
    { 2, 6 }, // C-G
    { 3, 7 }, // D-H
    { 4, 5 }, // E-F
    { 5, 6 }, // F-G
    { 6, 7 }, // G-H
    { 7, 4 }  // H-E
};

// angles of incidence and azimuth
double incidence        = 15.0;
double azimuth          = 30.0;
// aspect ratio
double aspect		=  1.0;
// distance between the eye and origin
double distance		=  5.0;

// flags for mouse button ON/OFF (OFF = 0, ON = 1)
int left_mouse = 0, middle_mouse = 0, right_mouse = 0;
// previous coordinates of the mouse pointer
int last_pointer_x, last_pointer_y;

// rotation angles
int shoulder = 0;

// draw the rotation axis
void draw_axis( void )
{
    // set line width
    glLineWidth( 3.0 );
    // draw the axis as a line segment
    glBegin( GL_LINES );
    glVertex3d( 0.0, 0.0,  1.0 );
    glVertex3d( 0.0, 0.0, -1.0 );
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

    // Note: transformation matrices are applied in the reverse order
    // translate the object along the view direction (z-axis)
    glTranslated( 0.0, 0.0, -distance );
    // rotate the object by the angle of incidence
    glRotated( -incidence, 1.0, 0.0, 0.0 );
    // rotate the object by the angle of azimuth
    glRotated( -azimuth, 0.0, 0.0, 1.0 );

    // start transforming the shoulder object
    glPushMatrix();
    {
	// translate the rotation axis to the z-axis
	glTranslated( -1.0, 0.0, 0.0 );
	// rotate the shoulder object
	glRotated( (double)shoulder, 0.0, 0.0, 1.0 );
	// draw the rotation axis of the shoulder object in red
	// set color to red
	glColor3d( 1.0, 0.0, 0.0 );
	// draw the rotation axis
	draw_axis();
	// translate the rotation axis back to the joint position
	glTranslated( 1.0, 0.0, 0.0 );
    
	// draw the shoulder object
        // start transforming the shoulder cube
	glPushMatrix();
	// scale the shoulder cube    
	glScaled( 1.0, 0.2, 0.5 );
	// draw a shoulder cube
	draw_object();
        // finish transforming the shoulder cube
	glPopMatrix();
    }
    // finish transforming the shoulder object
    glPopMatrix();

    
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
              // left mouse button is ON 	
	      left_mouse = 1;
	      // set the latest mouse coordinates
	      last_pointer_x = x;
	      last_pointer_y = y;
	  }
          // left mouse button is OFF
	  else left_mouse = 0;
	  break;
      // middle mouse event
      case GLUT_MIDDLE_BUTTON:
          if ( state == GLUT_DOWN ) {
              // middle mouse button is ON 	
	      middle_mouse = 1;
	      // set the latest mouse coordinates
	      last_pointer_x = x;
	      last_pointer_y = y;
	  }
          // middle mouse button is OFF
	  else middle_mouse = 0;
	  break;
      // right mouse event
      case GLUT_RIGHT_BUTTON:
          if ( state == GLUT_DOWN ) {
              // right mouse button is ON 	
	      right_mouse = 1;
	      // set the latest mouse coordinates
	      last_pointer_x = x;
	      last_pointer_y = y;
	  }
          // right mouse button is OFF
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
     
          // rotate the shoulder in CCW
     case 's':
         shoulder = (shoulder + 5) % 360;
         break;
     // rotate the shoulder in CW
     case 'S':
         shoulder = (shoulder - 5) % 360;
         break;

     // quit the program
     case 'q':
     case 'Q':
     case '\033':  // ASCII code of ESC
         exit( 0 );
         break;
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
    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
