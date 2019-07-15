#include <GL/glut.h>

// display callback function
void display( void )
{
    // clear buffer to preset color
    glClear( GL_COLOR_BUFFER_BIT );
    
    
    // set the width of the line(s)
    glLineWidth( 3.0 );                      //線の太さ
    // set the color of the primitive(s)
    glColor3d( 0.0, 0.0, 1.0 );              //線の色(red,green,blue)

    
    // set the primitive as polygon          //色々な結びかた
    glBegin( GL_LINE_STRIP );
    // plot the vertices of the primitive(s) //各点の座標
    glVertex2d( -0.3, -0.5 );
    glVertex2d(  0.3, -0.5 );
    glVertex2d(  0.6,  0.0 );
    glVertex2d(  0.3,  0.5 );
    glVertex2d( -0.3,  0.5 );
    glVertex2d( -0.6,  0.0 );
    
    // end of plotting vertices
    glEnd();

    // swap the front and back buffers
    glutSwapBuffers();
}

// no changes





// initialize OpenGL setups
void init( void )
{
    // specify color for clearing frame buffer //背景の色
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
