#include <GL/glut.h>

#define WINDOW_SIZE	(512)

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

        // set the line width
    glLineWidth( 1.0 );
    // change color to white
    glColor3d(  1.0,  1.0,  1.0 );
    // draw a wireframe teapot model
    glutWireTeapot( 0.5 );


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
    // clearing frame buffer
    init();
    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
