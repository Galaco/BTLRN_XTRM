#ifndef ENVOBJ_H
#define ENVOBJ_H

#include "object.h"

class Prop : public Object
{
public:
	Prop();
	Prop( std::string, std::string , int , int , int );		// our constructor. arguments are x,y
	void draw();							// draws the object
	void setPosition( float , float , float );		// sets X and Y position

	float getPosZ();				// returns Y position
	
protected:


private:
	// Setup model information
	float posZ;	
};
#endif