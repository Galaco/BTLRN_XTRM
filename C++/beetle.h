#ifndef BEETLE_H
#define BEETLE_H


#include "object.h"

class Beetle : public Object
{
public:
	Beetle();
	Beetle( int , int , int , int );		// our constructor. arguments are x,y
	void draw();							// draws the object
	void update();

	void setSpeed( int );
	void setDir( bool );
	void reverseDir();

	void checkPlayerVis( float , float );

	// GETTERS
	bool getDirection();
	char getSpeed();
	
protected:


private:
	// Setup model information
	int min , max , velocity;
	bool boost;
	GLuint t_run[4];
};
#endif