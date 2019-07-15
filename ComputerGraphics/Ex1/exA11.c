#include <math.h>
#include <GL/glut.h>

#define WINDOW_SIZE     (512)

// draw a Koch curve segment
void drawKoch( double x0, double y0, double x1, double y1, int level )
{
    if ( level == 0 ) {
        glBegin( GL_LINES );
        glVertex2d( x0, y0 );
        glVertex2d( x1, y1 );
        glEnd();
    }
    else {
      // divide the line segment into three subsegments
      double xl = 2.0/3.0 * x0 + 1.0/3.0 * x1;
      double yl = 2.0/3.0 * y0 + 1.0/3.0 * y1;
      double xr = 1.0/3.0 * x0 + 2.0/3.0 * x1;
      double yr = 1.0/3.0 * y0 + 2.0/3.0 * y1;
      // calculate the normal
      double xn = -1.0/3.0 * ( y1 - y0 );
      double yn =  1.0/3.0 * ( x1 - x0 );
      // calculate the position of new vertex
      double xm = 1.0/2.0 * x0 + 1.0/2.0 * x1 + sqrt( 3.0 )/2.0 * xn;
      double ym = 1.0/2.0 * y0 + 1.0/2.0 * y1 + sqrt( 3.0 )/2.0 * yn;
      // draw the left subsegment
      drawKoch( x0, y0, xl, yl, level - 1 );
      // draw the new segments
      drawKoch( xl, yl, xm, ym, level - 1 );
      drawKoch( xm, ym, xr, yr, level - 1 );
      // draw the right subsegment
      drawKoch( xr, yr, x1, y1, level - 1 );
    }
}

// display callback function
void display( void )
{
    // clear buffer to preset color
    glClear( GL_COLOR_BUFFER_BIT );

    // specify the width of the line 
    glLineWidth( 1.0 );
    // draw in white
    glColor3d( 1.0, 1.0, 1.0 );
    // draw a Koch curve
    drawKoch( -1.6, -0.4, 1.6, -0.4, 1);
    
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
