#include <GL/glut.h>

#define WINDOW_SIZE     (512)

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
    // specify color for clearing frame buffer //背景の色
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
