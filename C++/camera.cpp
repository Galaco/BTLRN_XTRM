#include "camera.h"


float zCamPos = -250.0;


Camera::Camera(){
	posX = 0;
	posY = 0;
}

void Camera::zoom( int d ){
	zCamPos += d;
	if ( ( zCamPos > CAMERAMINZOOM ) || ( zCamPos < CAMERAMAXZOOM ) )			// Check bounds for min and max camera distance
	{
		zCamPos -= d;
	} 
}

void Camera::update( float x , float y ){
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( - x , - y - YOFFSET , zCamPos );							// Translate the camera in the X and Y direction. 
}

Camera::~Camera(){
}