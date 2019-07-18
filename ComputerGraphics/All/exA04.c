#include <GL/glut.h>

// display callback function
void display( void )
{
    // clear buffer to preset color
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Specify the primitive(s) to be drawn
    glBegin( GL_LINE_LOOP );
    // plot the vertices of the primitive(s)
    glVertex2d( -0.9, -0.9 );
    glVertex2d(  0.8, -0.8 );
    glVertex2d(  0.9,  0.9 );
    glVertex2d( -0.8,  0.8 );
    // end of plotting vertices
    glEnd();

    // swap the front and back buffers
    glutSwapBuffers();
}

// no changes





// initialize OpenGL setups
void init( void )
{
    // specify color for clearing frame buffer
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
}

// main function
int main( int argc, char *argv[] )
{
    // initialize GLUT 
    glutInit( &argc, argv );
    // set initial display mode
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    // create a window
    glutCreateWindow( argv[0] );
    // set a pointer to the display callback function
    glutDisplayFunc( display );
    // clearing frame buffer
    init();                             
    // get into the main interaction loop
    glutMainLoop();

    return 0;
}
