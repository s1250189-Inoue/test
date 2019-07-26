#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "glsl.h"

//
// Load a shader source program into memory
//
int readShaderSource( unsigned int shader, const char *file )
{
    FILE *fp;
    const GLchar *source;
    GLsizei length;
    int ret;
  
    // open the file
    fp = fopen( file, "rb" );
    if ( fp == NULL ) {
	perror( file );
	return -1;
    }
    
    // seek the file from the begininng to end to obtain the file size
    fseek( fp, 0L, SEEK_END );
    length = ftell( fp );
  
    // spare the memory of the file size
    source = ( GLchar * )malloc( length );
    if ( source == NULL ) {
	fprintf( stderr, "Could not allocate read buffer.\n" );
	return (-1);
    }
  
    // read the file from the beginning and close the file
    fseek( fp, 0L, SEEK_SET );
    ret = fread( ( void * )source, 1, length, fp) != (size_t)length;
    fclose( fp );
  
    // Load the source program into the shader object
    if ( ret )
	fprintf( stderr, "Could not read file: %s.\n", file );
    else
	glShaderSource( shader, 1, &source, &length );
  
    // release the spared memory
    free( (void *)source );
    
    return ret;
}

//
// print the information about the shader
//
void printShaderInfoLog( unsigned int shader )
{
    GLsizei bufSize;
  
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &bufSize );
    
    if ( bufSize > 1 ) {
	GLchar *infoLog;
    
	infoLog = (GLchar *)malloc( bufSize );
	if ( infoLog != NULL ) {
	    GLsizei length;
      
	    glGetShaderInfoLog( shader, bufSize, &length, infoLog );
	    fprintf( stderr, "InfoLog:\n%s\n\n", infoLog );
	    free( infoLog );
	}
	else
	    fprintf( stderr, "Could not allocate InfoLog buffer.\n" );
    }
}

//
// print the information about the program
//
void printProgramInfoLog( unsigned int program )
{
    GLsizei bufSize;
  
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &bufSize );
  
    if ( bufSize > 1 ) {
	GLchar *infoLog;
    
	infoLog = ( GLchar * )malloc( bufSize );
	if ( infoLog != NULL ) {
	    GLsizei length;
      
	    glGetProgramInfoLog( program, bufSize, &length, infoLog );
	    fprintf( stderr, "InfoLog:\n%s\n\n", infoLog );
	    free( infoLog );
	}
	else
	    fprintf( stderr, "Could not allocate InfoLog buffer.\n" );
    }
}
