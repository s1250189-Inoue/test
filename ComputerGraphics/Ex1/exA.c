#include <GL/glut.h>

// display callback function
void display( void )
{
    // clear buffer to preset color
    glClear( GL_COLOR_BUFFER_BIT );
    // swap the front and back buffers
    glutSwapBuffers();
}

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

