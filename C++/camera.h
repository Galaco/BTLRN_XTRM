#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/OpenGL.hpp>
#include <iostream>



class Camera
{
public:
	Camera();						// Default constructor
	void zoom( int );				// Zooms the camera in the z direction
	void update( float , float );	// Updates camera (basically just its position)
	
	float getZoom();

	~Camera();

protected:


private:
	static const int CAMERAMINZOOM = -150;
	static const int CAMERAMAXZOOM = -380;
	static const int YOFFSET = 50;
	float posX , posY;
};
#endif